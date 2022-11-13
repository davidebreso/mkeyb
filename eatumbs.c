/*
    eatumbs.c - A small program to reserve upper memory blocks

    Copyright (C) 2022 by github.com/davidebreso
*/

#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MY_MEMORY_SIGNATURE "eatUMBS "
#define MY_VERSION_TEXT "v0.1"

/* these things are imported from the resident part */
extern void (interrupt far *far OldInt2D)();
extern void interrupt far int2d_handler();
extern void far END_int2d_handler(void);

/*
    this allocates a block of memory with the given strategy
*/

unsigned int AllocMemory(unsigned int residentsize, unsigned int strategy)
{
    union REGS r;
    int allocSeg;
    int oldlink,oldstrategy;

    r.x.ax = 0x5802;    /* get UMB link state */
    int86(0x21,&r,&r);
    oldlink = r.h.al;

    r.x.ax = 0x5800;    /* get allocation strategy */
    int86(0x21,&r,&r);
    oldstrategy = r.h.al;

    r.x.ax = 0x5803;    /* set UMB link state */
    r.x.bx = 1;         /* 0 = no UMB link, 1 = set UMB link */
    int86(0x21,&r,&r);

    r.x.ax = 0x5801;     /* set allocation strategy */
    r.x.bx = strategy;
    int86(0x21,&r,&r);

    r.x.ax = 0x4800;                       /* dosAllocMem */
    r.x.bx = (residentsize + 15) >> 4;     /* size in paragraphs */
    int86(0x21,&r,&r);

    if (r.x.cflag) return 0;

    allocSeg = r.x.ax;

    *(short far*)MK_FP(allocSeg-1, 1) = allocSeg;   /* makes it selfreferencing */
    _fmemcpy(MK_FP(allocSeg-1, 8), MY_MEMORY_SIGNATURE, 8);   /* mark our name */

    r.x.ax = 0x5803;     /* reset UMB link state */
    r.x.bx = oldlink;
    int86(0x21,&r,&r);

    r.x.ax = 0x5801;         /* reset UMB allocation strategy */
    r.x.bx = oldstrategy;
    int86(0x21,&r,&r);

    return allocSeg;
}

void usage()
{
	printf("eatUMBS " MY_VERSION_TEXT " [" __DATE__ "]\n" );
	printf("Usage:\n"
		   "   EATUMBS size - reserve 'size' bytes of upper memory\n"
		   "   EATUMBS U    - uninstall and release upper memory\n");
}

int main(int argc, char *argv[])
{
    unsigned int residentSeg, residentsize;
    unsigned int size = 400;
    int i;
	char *argptr;
    void far *orig2d;
    
	union  REGS r;
	struct SREGS sregs;

	
	if(argc != 2) {
	    usage();
	    return 1;
	}
	
    argptr = argv[1];
    if(toupper(argptr[0]) == 'U')
    {
        /* Get current installation info */
        r.x.ax = 0x2800;
        int86(0x2D, &r, &r);
        if(r.h.al == 0xFF) {
            /* Resident segment is in DX */
            residentSeg = r.x.dx;
            /* Restore old INT 2D handler */
            orig2d = *(void far *far*)MK_FP(residentSeg,FP_OFF(&OldInt2D));
		    r.x.ax  = 0x252D;                        /* dosSetVect */
		    r.x.dx  = FP_OFF(orig2d);
		    sregs.ds   = FP_SEG(orig2d);
		    int86x(0x21,&r,&r,&sregs);
            /* Release memory */
            _dos_freemem(residentSeg);
            // printf("eatUMBS uninstalled from segment %04x\n", residentSeg);
            return 0;
        } else {
            printf("ERROR: eatUMBS is not installed.\n");
            return 1;
        }
    }
    
    size = atoi(argptr);
    if(size == 0) {
            printf("ERROR: unknown argument %s\n", argptr);
            usage();
            return 1;        
    }
	residentsize = FP_OFF(END_int2d_handler);
	if(size < residentsize) {
	    printf("Memory block too small. \n"
	        "I need at least %d bytes for the INT 2D handler.\n", residentsize);
	    return 1;
	}
    residentSeg = AllocMemory(size, 0x40);
    if(residentSeg == 0) {
        printf("ERROR: cannot allocate memory\n");
        return 1;
    }
    // printf("%d bytes of memory allocated at %04x\n", size, residentSeg);

    /* Save existing INT 2D handler */
    OldInt2D = _dos_getvect(0x2f);

    /* Copy data to upper memory block */
	residentsize = FP_OFF(END_int2d_handler);
    						/* copy resident code and data up into (high) memory */
	_fmemcpy(MK_FP(residentSeg, 0),
		MK_FP(FP_SEG(int2d_handler),0),
		residentsize);    

    /* Install new INT 2D handler */
	r.x.ax  = 0x252d;                        /* dosSetVect */
	r.x.dx  = FP_OFF(int2d_handler);
	sregs.ds   = residentSeg;
	int86x(0x21,&r,&r,&sregs);
	// printf("INT 2D installed at %04x:%04x\n", sregs.ds, r.x.dx);
    
    return 0;
}
