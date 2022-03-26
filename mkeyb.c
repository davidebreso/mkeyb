/*
    mKEYB.C - minimum keyboard handler for international keyboards

    requires only ~512 byte (~600 byte with COMBI characters)
    of precious memory to do what it does.

    for details, please see readme.txt


    Copyright (C) 2002-2005 by www.tomehlert.de
*/

#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

#include "mkeyb.h"

#define MY_MEMORY_SIGNATURE "mKEYB   "

#define DBGprintf printf

void fmemcpy(void far *d, void far *s, uint len)
{
    uchar far *dc = d,far *sc = s;
    for (; len; len--)
        *dc++ = *sc++;
}
int _fmemcmp(void far *d, void far *s, uint len)
{
    uchar far *dc = d,far *sc = s;
    for (; len; len--)
        if (*dc++ != *sc++)
        	return 1;
    return 0;    	
}

/*
    this allocates memory as undisturbing as possible.
    strategy choosen:
    allocate at end of memory, in upper memory if present
*/

AllocHighMemory(uint residentsize, int makeResident)
{
    union REGS r;
    uint allocSeg;
    uint oldlink,oldstrategy;

    r.x.ax = 0x5802;     /* get UMB link state */
    int86(0x21,&r,&r);
    oldlink = r.h.al;

    r.x.ax = 0x5800;     /* get allocation strategy */
    int86(0x21,&r,&r);
    oldstrategy = r.h.al;

    r.x.ax = 0x5803;     /* set UMB link state */
    r.x.bx = 0x0001;
    int86(0x21,&r,&r);

    r.x.ax = 0x5801;     /* set allocation strategy */
    r.x.bx = 0x82;       /* last fit, try high, then low */
    int86(0x21,&r,&r);

    r.x.ax = 0x4800;                       /* dosAllocMem */
    r.x.bx = (residentsize + 15) / 16;     /* size in paragraphs */
    int86(0x21,&r,&r);

    if (r.x.cflag) { printf("can't allocate memory\n");exit(1); }

    allocSeg = r.x.ax;

    if (makeResident)
        {
        *(short far*)MK_FP(allocSeg-1, 1) = allocSeg;   /* makes it selfreferencing */
        fmemcpy(MK_FP(allocSeg-1, 8), MY_MEMORY_SIGNATURE, 8);   /* mark our name */
        }

    r.x.ax = 0x5803;     /* reset UMB link state */
    r.x.bx = oldlink;
    int86(0x21,&r,&r);

    r.x.ax = 0x5801;         /* reset UMB allocation strategy */
    r.x.bx = oldstrategy;
    int86(0x21,&r,&r);

    return allocSeg;
}

/*
    VerifyScancodeTableForCorrectness();
    this is in theory not needed.
    in practice, it's better to check, that the tables are setup correctly
    at least as there are yet many missing keyboard definitions
*/

void VerifyScancodeTableForCorrectness(	struct KeyboardDefinition *kb,int print)
{
    extern uchar RESIDENT nibble_length[];
    unsigned flags;
    uchar *tbl, *tblnext, *lasttbl;
    int loopdetect = 0;
    void *scancode_end;
    
    scancode_end = kb->CombicodeTables[0];
    if (scancode_end == NULL)
	scancode_end = kb;

    
    

    for (   tbl = kb->ScancodeTable;
                tbl[0] != 0;
                tbl = tblnext)
        {
        if (print)
	    printf("offset %02x scancode %02x flags %02x \n",
                tbl-kb->ScancodeTable, tbl[0], tbl[1]);

	if (++loopdetect > 200)
            {
	    printf("loop detected\n");
            goto error;
	    }

        flags = tbl[1];

        tblnext = tbl+(flags & SIZEFIELD);

        if (tblnext > scancode_end)
            {
	    printf("scancode table error <SIZE> offset 0x%2x, scancode = 0x%02x, flags = 0x%02x\n",
                tbl-kb->ScancodeTable, tbl[0],flags);
            goto error;
            }

        if (tblnext[0])
            if ((tblnext[1] & SIZEFIELD) <= 2)
                {
		printf("scancode table error <FLAGS> offset 0x%2x, scancode = 0x%02x, flags = 0x%02x\n",
                    tbl-kb->ScancodeTable, tbl[0],flags);
                goto error;
                }

        lasttbl = tbl;
        }

    if (tbl + 1 != scancode_end)
        {
	printf("scancode table error: early zero found at offset 0x%2x last scan 0x%02x\n",
                tbl-kb->ScancodeTable, lasttbl[0]);
        goto error;
        }
return;

error:
    if (!print)
	VerifyScancodeTableForCorrectness(kb,1);
    exit(1);
}

void UninstallKeyboard(int verbose)
{
	void far *int9handler = *(void far *far *)MK_FP(0,4*0x9);
	void far *int15handler = *(void far *far *)MK_FP(0,4*0x15);
	void far *int2fhandler = *(void far *far *)MK_FP(0,4*0x2f);
	unsigned resident;
	void far *orig9, far *orig15, far *orig2f;

    union  REGS r;
    struct SREGS sr;

	r.x.ax = 0xad82;  			// disable old keyboard driver
	r.x.bx = 0;
	int86(0x2f,&r,&r);


	// now try to disable the old

	resident = NULL;

	if (_fmemcmp(MK_FP(FP_SEG(int15handler)-1,8),MY_MEMORY_SIGNATURE,8) == 0)
		resident = FP_SEG(int15handler);


	if (_fmemcmp(MK_FP(FP_SEG(int15handler)-1,8),MY_MEMORY_SIGNATURE,8) == 0)
		resident = FP_SEG(int2fhandler);

	// printf("resident found at %x:0\n",resident);

	if (resident == 0)
		{
		if (verbose)
			printf("no previous instance of KEYB found\n");
		return;
		}
							// check that this is the same version
							// of KEYB
	if (_fmemcmp( ((char far *)&OldInt15)-8,
		      ((char far *)MK_FP(resident,FP_OFF(&OldInt15)))-8,
				8) != 0)
		{
		printf("different version of KEYB found %8lx != %8lx\n",
				  ((char far *)&OldInt15)-8,
		      ((char far *)MK_FP(resident,FP_OFF(&OldInt15)))-8
				);
		return;
		}

	orig9 = *(void far *far*)MK_FP(resident,FP_OFF(&OldInt9));
	orig15 = *(void far *far*)MK_FP(resident,FP_OFF(&OldInt15));
	orig2f = *(void far *far*)MK_FP(resident,FP_OFF(&OldInt2F));

	// printf("original values %8lx, %8lx , %8lx\n",orig9, orig15,orig2f);

	if (FP_SEG(int9handler) == resident)
		{
	r.x.ax  = 0x2509;                        /* dosSetVect */
	r.x.dx  = FP_OFF(orig9);
	sr.ds   = FP_SEG(orig9);
	int86x(0x21,&r,&r,&sr);
		// printf("int9 handler desinstalled\n");
		}

	if (FP_SEG(int15handler) == resident)
		{
	r.x.ax  = 0x2515;                        /* dosSetVect */
	r.x.dx  = FP_OFF(orig15);
	sr.ds   = FP_SEG(orig15);
	int86x(0x21,&r,&r,&sr);
		// printf("int15 handler desinstalled\n");
		}

	if (FP_SEG(int2fhandler) == resident)
		{
	r.x.ax  = 0x252f;                        /* dosSetVect */
	r.x.dx  = FP_OFF(orig2f);
	sr.ds   = FP_SEG(orig2f);
	int86x(0x21,&r,&r,&sr);
		// printf("int2f handler deinstalled\n");
		}

	if (FP_SEG(int15handler) == resident &&
	    FP_SEG(int2fhandler) == resident)
		{
					// OK. free memory also
					/* DosFree(resident) */
		r.x.ax = 0x4900;
		sr.es  = resident;
	int86x(0x21,&r,&r,&sr);

	*(short far*)MK_FP(resident-1, 1) = 0;   /* bums. DosFree(resident) */

	// printf("DOS memory at %x freed\n",resident);
		}
	if (verbose)
		printf("old KEYB deinstalled\n");

}









InstallKeyboard(struct KeyboardDefinition *kb, int GOTSR, int int9hChain)
{
    union  REGS r;
    struct SREGS sregs;
    uint residentSeg;
    uint residentsize;

    int  i;


  { /* make sure some assumptions old */
    int err = 0;

    if (FP_SEG(int2f_handler) != FP_SEG(int15_handler)) err |= 0x0001;
//    if (FP_SEG(ResidentScancodetable)  != FP_SEG(int15_handler)) err |= 0x0002;
//    if (FP_OFF(ResidentScancodetable)  > 0x800)                  err |= 0x0004;

    if (err)
	{
	printf("compile time error %x\n", err);
	printf("please check your compiler switches and recompile\n");
	return 1;
	}
  }

    VerifyScancodeTableForCorrectness(kb,0);

  { /* install the resident part */
	void far *pint15_handler;
	uint      int15_handler_size;
	uchar far *pres;

	extern int  far cint15_handler_full(int);
	extern void far END_cint15_handler_full(void);
	extern int  far cint15_handler_normal(int);
	extern void far END_cint15_handler_normal(void);
	extern int  far cint15_handler_fastswitch(int);
	extern void far END_cint15_handler_fastswitch(void);

	switch(kb->DriverFunctionRequired)
		{
		case DRIVER_FUNCTION_FULL:
				pint15_handler = (void far *)cint15_handler_full;
				int15_handler_size = FP_OFF(END_cint15_handler_full) - FP_OFF(cint15_handler_full);
				break;

		case DRIVER_FUNCTION_NORMAL:
				pint15_handler = (void far *)cint15_handler_normal;
				int15_handler_size = FP_OFF(END_cint15_handler_normal) - FP_OFF(cint15_handler_normal);
				break;

		case DRIVER_FUNCTION_FASTSWITCH:
				pint15_handler = (void far *)cint15_handler_fastswitch;
				int15_handler_size = FP_OFF(END_cint15_handler_fastswitch) - FP_OFF(cint15_handler_fastswitch);
				break;

		}

	pres = (void far *)cint15_handler_full;

	fmemcpy(pres, pint15_handler, int15_handler_size);
	pres += int15_handler_size;

	pResidentScancodetable = (char*)FP_OFF(pres);

	for (i = COMBI1; i <= COMBI6; i++)
		{
		ResidentCombiTables[i-COMBI1] = (char*)pResidentScancodetable +
						(kb->CombicodeTables[i-COMBI1] - kb->ScancodeTable);
		}

	fmemcpy(pres, kb->ScancodeTable, (char *)kb - (char *)kb->ScancodeTable);
	pres += (char *)kb - (char *)(kb->ScancodeTable);



    DecimalDingsBums = kb->DezimalDingsbums;

	if (kb->DefaultLayoutUS)
		usebiosonly_flag = 0;


    residentsize = FP_OFF(pres);

					/* fetch enough memory for the TSR part */
    residentSeg = AllocHighMemory(residentsize,GOTSR);

	printf("%s keyboard\n", (int9hChain ? "PC/XT" : "AT"));
	printf(" %s - %s\n", kb->LanguageShort, kb->Description);



#define RESPTR(x) MK_FP(residentSeg, (void near*)x)

	OldInt9 = getvect(0x9);
	OldInt15 = getvect(0x15);       /* do this before copying */
	OldInt2F = getvect(0x2f);

					/* copy code and data up into (high) memory */
	fmemcpy(RESPTR(0),
		MK_FP(FP_SEG(int15_handler),0),
		residentsize);

	if(int9hChain)	   	/* install int9 handler if requested */
	{
		r.x.ax  = 0x2509;                        /* dosSetVect */
		r.x.dx  = FP_OFF(int9_handler);
		sregs.ds   = residentSeg;
		int86x(0x21,&r,&r,&sregs);
	}
	r.x.ax  = 0x2515;                        /* dosSetVect */
	r.x.dx  = FP_OFF(int15_handler);
	sregs.ds   = residentSeg;
	int86x(0x21,&r,&r,&sregs);

	r.x.ax  = 0x252f;                        /* dosSetVect */
	r.x.dx  = FP_OFF(int2f_handler);
	sregs.ds   = residentSeg;
	int86x(0x21,&r,&r,&sregs);

  } /* done with install */

    if (GOTSR)
	{
	exit(0);
	}

    printf("\n KEYB installed at segment %04x, %u bytes\n",residentSeg, residentsize);

    printf("\n KEYB debug mode - hit ESC key to terminate test mode\n");

  { /* debug only */
    extern uchar far debug_scancode;        /* debug */

    while (*(uchar far*)RESPTR(&debug_scancode) != 1)
	{

	if (*(uchar far*)RESPTR(&debug_scancode) != 0)
	    {
	    printf("shiftstate %02x scancode    %02x\n",
		*(short far*)MK_FP(0x40,0x17), *(uchar far*)RESPTR(&debug_scancode));

	    if (*(uchar far*)RESPTR(&debug_scancode) & 0x80 && /* release key ??*/
		*(uchar far*)RESPTR(&debug_scancode) != 0xe0)
		printf("\n");

	    *(uchar far*)RESPTR(&debug_scancode) = 0;
	    }

	r.h.ah = 0x01;
	int86(0x16,&r,&r);
	if ((r.x.flags & 0x40) == 0)  /* ZF = 0 */
	    {
	    r.h.ah = 0x00;
	    int86(0x16,&r,&r);

	    printf("key pressed %04x '%c'\n",r.x.ax,r.h.al);
	    }
	}
  }

    setvect(0x9,OldInt9);
    setvect(0x15,OldInt15);
    setvect(0x2f,OldInt2F);

    printf(" KEYB - uninstalled\n");

    return 0;
}


extern struct KeyboardDefinition
	 Keyboard_BE
	,Keyboard_BG
	,Keyboard_BGP
	,Keyboard_DK
	,Keyboard_GR
	,Keyboard_GR2
	,Keyboard_IT
	,Keyboard_LA
	,Keyboard_NL
	,Keyboard_NO
	,Keyboard_PL
	,Keyboard_PO
	,Keyboard_RU
	,Keyboard_SF
	,Keyboard_SG
	,Keyboard_SP
	,Keyboard_SU
	,Keyboard_SV
	,Keyboard_UK
	,Keyboard_BR
	,Keyboard_BX
	,Keyboard_FR
	,Keyboard_HE
	,Keyboard_SL
	;
struct KeyboardDefinition *KeyDefTab[] = 
	{
	 &Keyboard_BE
	,&Keyboard_BG
	,&Keyboard_BGP
	,&Keyboard_BR
	,&Keyboard_BX
	,&Keyboard_DK
	,&Keyboard_FR
	,&Keyboard_GR
	,&Keyboard_GR2
	,&Keyboard_HE
	,&Keyboard_IT
	,&Keyboard_LA
	,&Keyboard_NL
	,&Keyboard_NO
	,&Keyboard_PL
	,&Keyboard_PO
	,&Keyboard_RU
	,&Keyboard_SF
	,&Keyboard_SG
	,&Keyboard_SL
	,&Keyboard_SP
	,&Keyboard_SU
	,&Keyboard_SV
	,&Keyboard_UK
	};

void ListLanguages(void)
	{
    struct KeyboardDefinition *kb;
	int j;

	printf("\n");
	for (j = 0; j < LENGTH(KeyDefTab); j++)
		{
		kb = KeyDefTab[j];
		printf(" %-3s- %s\n",kb->LanguageShort,kb->Description);
		}
	}


void usage(void)
{
    printf( " Copyright (c) 2002-2018 www.tomehlert.de\n");

	printf("KEYB  usage:\n"
		   "      KEYB UK - United Kingdom keyboard\n"
		   "      KEYB GR - German - deutsche Tastatur\n"
		   "      ....\n"
		   "      KEYB /L - List all available keyboards\n"
		   "      KEYB /U - uninstall previous keyboard driver\n"
		   "      KEYB /S - Silent - absorb all keyboard input\n"
		   "      KEYB /9 - Force PC/XT keyboard controller type\n"
		   "      KEYB /E - Force AT keyboard controller type\n"
		   "      KEYB GR /T - test the GERman keyboard driver, don't go resident\n"
		   "When loaded:\n"
		   "      Ctrl+Alt+F1 : International (QWERTY) keyboard\n"
	   "      Ctrl+Alt+F2 : National loaded keyboard\n"
           "      on some languages, tapping Right-Control also switches"
		   );
	exit(1);		   
}	
 

int main(int argc, char *argv[])
{
    struct KeyboardDefinition *kb = NULL;
    uint GOTSR = 1;
    uint int9hChain;
    int i;
    uchar far *pmodel;

    if (argv);
    if (argc);

    printf("mKEYB 0.46 [" __DATE__ "] - " );

    pmodel = MK_FP(0xF000, 0xFFFE);
    // printf("Machine ID %02x\n", *pmodel);
    int9hChain = (*pmodel >= 0xFD);

	for (i = 1; i < argc; i++)
		{
		char *argptr = argv[i];

		if (*argptr == '/' || *argptr == '-')
			{
			switch(toupper(argptr[1]))
				{
				case 'L': ListLanguages(); exit(0);
				case 'T': GOTSR = 0; break;

				case 'U':
						  UninstallKeyboard(1);
						  exit(0);
						  break;

				case 'S': SilentKeyboard = 1;
						  break;

				case '9': int9hChain = 1;
					break;

				case 'E': int9hChain = 0;
					break;

				default: printf("unknown argument <%s>\n", argptr+1);
				case 'H':
				case '?':usage();
						 break;

				}
			}
		else
			{
			int j;
			for (j = 0; j < LENGTH(KeyDefTab); j++)
				{
				if (stricmp(argptr,KeyDefTab[j]->LanguageShort) == 0)
					{
					kb = KeyDefTab[j];
					break;
					}
				}				

			if (kb == NULL)
				{
				if (stricmp(argptr,"US") == 0)	
					{
					printf("US keyboards don't need a keyboard handler\n");
					UninstallKeyboard(0);
					exit(0);
					}
				
				printf("unknown keyboard driver '%s'\n", argptr);
				printf("use MKEYB /L to get a list of available languages\n");
				exit(1);
				}						
			}				
		}


	UninstallKeyboard(0);
		
	if (kb == NULL)
		{
		printf("you MUST specify a keyboard language like\n"
		       "   MKEYB GR\n"
		       "   MKEYB SP\n"
		       "use MKEYB /L to get a list of available languages\n");
		exit(1);
		}						


	return InstallKeyboard(kb, GOTSR, int9hChain);
}

/*
    TE - some size optimizations for __TURBOC__

    as printf() is redefined in PRF.C to use no stream functions,
    rather calls DOS directly, these Stream operations are nowhere used,
    but happen to be in the executable.

    so we define some dummy functions here to save some precious bytes :-)

    this is in no way necessary, but saves us some 1500 bytes
*/

#ifdef __TURBOC__

    #define UNREFERENCED_PARAMETER(x) if (x);

    int     _Cdecl flushall (void){return 0;}

    int     _Cdecl fprintf  (FILE *__stream, const char *__format, ...)
                             { UNREFERENCED_PARAMETER (__stream);
                               UNREFERENCED_PARAMETER ( __format);    return 0;}
    int     _Cdecl fseek    (FILE *__stream, long __offset, int __whence)
                             { UNREFERENCED_PARAMETER (__stream);
                               UNREFERENCED_PARAMETER (__offset);
                               UNREFERENCED_PARAMETER ( __whence);
                               return 0;}

    int     _Cdecl setvbuf  (FILE *__stream, char *__buf, int __type, size_t __size)
                             { UNREFERENCED_PARAMETER (__stream);
                               UNREFERENCED_PARAMETER ( __buf);
                               UNREFERENCED_PARAMETER ( __type);
                               UNREFERENCED_PARAMETER ( __size);   return 0;}

    void    _Cdecl _xfflush (void){}
    void    _Cdecl _setupio (void){}

#endif
