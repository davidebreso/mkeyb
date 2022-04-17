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
	if(scancode_end == NULL)
		scancode_end = kb;

	for(tbl = kb->ScancodeTable;
		tbl[0] != 0;
		tbl = tblnext)
	{
		if(print)
			printf("offset %02x scancode %02x flags %02x \n",
					tbl-kb->ScancodeTable, tbl[0], tbl[1]);
		if(++loopdetect > 200)
		{
			printf("loop detected\n");
				goto error;
		}

		flags = tbl[1];
		tblnext = tbl+(flags & SIZEFIELD);
		if(tblnext > scancode_end)
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

/*
   AutodetectInt9h();
   Autodetects if a new INT9 handler is needed by reading
   feature byte 1 of the ROM configuration table
*/

int AutodetectInt9h()
{
	union REGS r;
	struct SREGS sr;

	r.h.ah = 0xc0;
	int86x(0x15, &r, &r, &sr);		/* INT 15,C0: Get system configuration */
	if ((r.x.flags & 0x01) == 0)  	/* CF = 0 */
	{
		/* ROM Table is at ES:BX, feature byte 1 at offset 5 */
		uchar fbyte = *(uchar far *)MK_FP(sr.es, r.x.bx + 5);
		// printf("Feature byte at %04x:%04x is %02x\n", sr.es, r.x.bx, fbyte);
		/* bit 4 is 1 if INT 15,4F called by INT9 */
		return ((fbyte & 0x10) == 0);
	}
	/* if carry flag is set, function is unavailable */
	return 1;		/* Chain INT9 */
}

/*
  AutodetectInt16h();
  Autodetects if BIOS provides store keystroke in keyboard buffer function
*/

int AutodetectInt16h()
{
	union REGS r;

	/* Clear keyboard buffer by setting tail = head */
	*(uint far *)MK_FP(0x40, 0x1C) = *(uint far *)MK_FP(0x40, 0x1A);
	r.h.ah = 5;
	r.x.cx = 0x0928;	/* dummy keystroke */
	int86(0x16, &r, &r);	/* try to add keystroke into buffer */
	r.h.ah = 01;
	int86(0x16, &r, &r);	/* check for keystroke */
	if((r.x.flags & 0x40) == 0)     /* ZF = 0 */
	{
		// printf("Keystroke: %04x\n", r.x.ax);
		/* Clear buffer */
		*(uint far *)MK_FP(0x40, 0x1C) = *(uint far *)MK_FP(0x40, 0x1A);
		return (r.x.ax != 0x0928);	/* check if keystroke is correct */
	}
	// printf("Empty buffer\n");
	return 1;	/* Buffer empty, chain INT16 */
}

/*
  AutodetectKeyboard();
  Autodetect if the keyboard is enhanced (101/102 keys)
  or standard (83/84 keys).
*/
uint AutodetectKeyboard()
{
	uchar status;
	status = *(uchar far *)MK_FP(0x40, 0x96);
	// printf("Keyboard status byte: %04x\n", status);
	return (status & 0x10);
}

/*
  uint DetectKeyboardDriver(uint *resident);
  Check if a keyboard driver is installed.
  Return value:
	0	no driver installed
	1	same version of mKEYB installed
	2	different version of mKEYB installed
	3	another keyboard driver installed
  resident is modifed to point to the resident code segment
*/

uint DetectKeyboardDriver(uint *resident)
{
	union REGS r;
	struct SREGS sr;

	r.x.ax = 0xad80;  		  // Check for keyboard driver
	int86x(0x2f,&r,&r,&sr);
	*resident = sr.es;

	if (r.h.al == 0xff)
	{
		// printf("Another keyboard driver is installed\n");
		return 3;
	}

	if (r.x.ax != MY_INSTALL_SIGNATURE)
	{
		// printf("No keyboard driver installed\n");
		return 0;
	}

	if (r.x.bx != MY_VERSION_SIGNATURE)
	{
		// printf("Different version of mKEYB installed\n");
		return 2;
	}

	return 1;
}

/*
  UninstallKeyboard(int verbose);
  Uninstall mKEYB if present in memory
  If verbose == 0 and another keyb driver is found, disable it
  If verbose == 1 and another keyb driver is found, terminate with
  a warning message.
*/

void UninstallKeyboard(int verbose)
{
	void far *int9handler = *(void far *far *)MK_FP(0,4*0x9);
	void far *int16handler = *(void far *far *)MK_FP(0,4*0x16);
	void far *int15handler = *(void far *far *)MK_FP(0,4*0x15);
	void far *int2fhandler = *(void far *far *)MK_FP(0,4*0x2f);
	unsigned resident = NULL;
	void far *orig9, far *orig16, far *orig15, far *orig2f;

	union  REGS r;
	struct SREGS sr;

	uint installed, freemem = 1;

	// printf("current values %8lx, %8lx, %8lx , %8lx\n",int9handler, int16handler, int15handler, int2fhandler);

	installed = DetectKeyboardDriver(&resident);

	if (installed == 0)
	{
		if(verbose)
			printf("No keyboard driver installed\n");
		return;
	}

	if (installed == 1)
	{
		/* Current version of mKEYB is installed */
		/* Check if you can uninstall it 		 */

		// printf("resident found at %x:0\n",resident);
		if (_fmemcmp( ((char far *)&OldInt15)-8,
		   ((char far *)MK_FP(resident,FP_OFF(&OldInt15)))-8, 8) != 0)
		{
			if(verbose)
			{
				printf("Different version of mKEYB found\n");
				return;
			}
			installed = 2;
		}
	} else {
		if(verbose)
		{
			printf("No previous instance of mKEYB " MY_VERSION_TEXT " found\n");
			return;
		}
	}

	if (installed > 1)
	{
		r.x.ax = 0xad82;  			// Disable current driver
		r.x.bx = 0;
		int86(0x2f,&r,&r);
		// printf("Old keyb driver disabled\n");
		return;
	}

	orig9 = *(void far *far*)MK_FP(resident,FP_OFF(&OldInt9));
	orig16 = *(void far *far*)MK_FP(resident,FP_OFF(&OldInt16));
	orig15 = *(void far *far*)MK_FP(resident,FP_OFF(&OldInt15));
	orig2f = *(void far *far*)MK_FP(resident,FP_OFF(&OldInt2F));

	// printf("original values %8lx, %8lx, %8lx , %8lx\n",orig9, orig16, orig15,orig2f);

	if (FP_SEG(int9handler) == resident)
	{
		r.x.ax  = 0x2509;                        /* dosSetVect */
		r.x.dx  = FP_OFF(orig9);
		sr.ds   = FP_SEG(orig9);
		int86x(0x21,&r,&r,&sr);
		// printf("int9 handler desinstalled\n");
	} else {
		freemem = (orig9 == NULL);
		if(!freemem)
		{
			printf("unlinking INT 9 not possible because it points to %04x:%04x which is not mKEYB\n",
					FP_SEG(orig9), FP_OFF(orig9));
		}
	}

	if (FP_SEG(int16handler) == resident)
	{
		r.x.ax  = 0x2516;                        /* dosSetVect */
		r.x.dx  = FP_OFF(orig16);
		sr.ds   = FP_SEG(orig16);
		int86x(0x21,&r,&r,&sr);
		// printf("int16 handler desinstalled\n");
	} else {
		freemem = (orig16 == NULL);
		if(!freemem)
		{
			printf("unlinking INT 16 not possible because it points to %04x:%04x which is not mKEYB\n",
					FP_SEG(orig16), FP_OFF(orig16));
		}
	}

	if (FP_SEG(int15handler) == resident)
	{
		r.x.ax  = 0x2515;                        /* dosSetVect */
		r.x.dx  = FP_OFF(orig15);
		sr.ds   = FP_SEG(orig15);
		int86x(0x21,&r,&r,&sr);
		// printf("int15 handler desinstalled\n");
	} else {
		freemem = (orig15 == NULL);
		if(!freemem)
		{
			printf("unlinking INT 15 not possible because it points to %04x:%04x which is not mKEYB\n",
					FP_SEG(orig15), FP_OFF(orig15));
		}
	}

	if (FP_SEG(int2fhandler) == resident)
	{
		r.x.ax  = 0x252f;                        /* dosSetVect */
		r.x.dx  = FP_OFF(orig2f);
		sr.ds   = FP_SEG(orig2f);
		int86x(0x21,&r,&r,&sr);
		// printf("int2f handler deinstalled\n");
	} else {
		freemem = (orig2f == NULL);
		if(!freemem)
		{
			printf("unlinking INT 2F not possible because it points to %04x:%04x which is not mKEYB\n",
					FP_SEG(orig2f), FP_OFF(orig2f));
		}
	}

	if (freemem)
	{
					// OK. free memory also
					/* DosFree(resident) */
		r.x.ax = 0x4900;
		sr.es  = resident;
		int86x(0x21,&r,&r,&sr);

		*(short far*)MK_FP(resident-1, 1) = 0;   /* bums. DosFree(resident) */
		// printf("DOS memory at %x freed\n",resident);
	} else {
		printf("working around the issue anyway...\n");
	}

	if (verbose)
		printf("old mKEYB deinstalled\n");
}

InstallKeyboard(struct KeyboardDefinition *kb,
		uint GOTSR, uint int9hChain, uint int16hChain)
{
	union  REGS r;
	struct SREGS sregs;
	uint residentSeg;
	uint residentsize;
	void far *pint9_handler;
	void far *pint16_handler;

	int  i;


	/* make sure some assumptions old */
	int err = 0;

	if (FP_SEG(int2f_handler) != FP_SEG(int16_handler)) err |= 0x0001;
//    if (FP_SEG(ResidentScancodetable)  != FP_SEG(int15_handler)) err |= 0x0002;
//    if (FP_OFF(ResidentScancodetable)  > 0x800)                  err |= 0x0004;

	if (err)
	{
		printf("compile time error %x\n", err);
		printf("please check your compiler switches and recompile\n");
		return 1;
	}

	VerifyScancodeTableForCorrectness(kb,0);

	/*
	 * Do this before copying.
	 * Save only the handlers that will be installed.
	 */
	if(int9hChain) 	OldInt9 = getvect(0x9);
	if(int16hChain) OldInt16 = getvect(0x16);
	OldInt15 = getvect(0x15);
	OldInt2F = getvect(0x2f);

  {	/* install the resident part */
	void far *pint15_handler;
	uint      int15_handler_size;
	uint	  int9_handler_size;
	uint	  int16_handler_size;
	uchar far *pres;

	extern int  far cint15_handler_full(int);
	extern void far END_cint15_handler_full(void);
	extern int  far cint15_handler_normal(int);
	extern void far END_cint15_handler_normal(void);
	extern int  far cint15_handler_fastswitch(int);
	extern void far END_cint15_handler_fastswitch(void);
	extern int  far cint15_handler_standard(int);
	extern void far END_cint15_handler_standard(void);
	extern int  far cint15_handler_stdfull(int);
	extern void far END_cint15_handler_stdfull(void);
	extern void far END_int16_handler(void);

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

		case DRIVER_FUNCTION_STANDARD:
			pint15_handler = (void far *)cint15_handler_standard;
			int15_handler_size = FP_OFF(END_cint15_handler_standard) - FP_OFF(cint15_handler_standard);
			break;

		case DRIVER_FUNCTION_STD_FULL:
			pint15_handler = (void far *)cint15_handler_stdfull;
			int15_handler_size = FP_OFF(END_cint15_handler_stdfull) - FP_OFF(cint15_handler_stdfull);
			break;
	}

	pres = (void far *)cint15_handler_full;
	fmemcpy(pres, pint15_handler, int15_handler_size);
	pres += int15_handler_size;
	if(int9hChain)
	{
		/* copy the INT9 handler */
		pint9_handler = pres;
		int9_handler_size = FP_OFF(int16_handler) - FP_OFF(int9_handler);
		fmemcpy(pres, int9_handler, int9_handler_size);
		pres += int9_handler_size;
	}
	if(int16hChain)
	{
		/* copy the INT16 handler */
		pint16_handler = pres;
		int16_handler_size = FP_OFF(END_int16_handler) - FP_OFF(int16_handler);
		fmemcpy(pres, int16_handler, int16_handler_size);
		pres += int16_handler_size;
	}

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

#define RESPTR(x) MK_FP(residentSeg, (void near*)x)

							/* copy code and data up into (high) memory */
	fmemcpy(RESPTR(0),
		MK_FP(FP_SEG(int15_handler),0),
		residentsize);

	if(int9hChain)	   	/* install int9 handler if requested */
	{
		r.x.ax  = 0x2509;                        /* dosSetVect */
		r.x.dx  = FP_OFF(pint9_handler);
		sregs.ds   = residentSeg;
		int86x(0x21,&r,&r,&sregs);
		// printf("INT9 installed at %04x:%04x\n", sregs.ds, r.x.dx);
	}
	if(int16hChain)		/* install 1nt16 handler if requested */
	{
		r.x.ax  = 0x2516;                        /* dosSetVect */
		r.x.dx  = FP_OFF(pint16_handler);
		sregs.ds   = residentSeg;
		int86x(0x21,&r,&r,&sregs);
		// printf("INT16 installed at %04x:%04x\n", sregs.ds, r.x.dx);
	}
	r.x.ax  = 0x2515;                        /* dosSetVect */
	r.x.dx  = FP_OFF(int15_handler);
	sregs.ds   = residentSeg;
	int86x(0x21,&r,&r,&sregs);
	// printf("INT15 installed at %04x:%04x\n", sregs.ds, r.x.dx);

	r.x.ax  = 0x252f;                        /* dosSetVect */
	r.x.dx  = FP_OFF(int2f_handler);
	sregs.ds   = residentSeg;
	int86x(0x21,&r,&r,&sregs);
	// printf("INT2F installed at %04x:%04x\n", sregs.ds, r.x.dx);

  }	/* done with install */

	if (GOTSR)
	{
		exit(0);
	}

	printf("\n mKEYB installed at segment %04x, %u bytes\n", residentSeg, residentsize);
	if(int9hChain)
		printf(" INT 9 handler installed at %04x:%04x\n", residentSeg, FP_OFF(pint9_handler));
	if(int16hChain)
		printf(" INT 16 handler installed at %04x:%04x\n", residentSeg, FP_OFF(pint16_handler));
	printf(" INT 15 handler installed at %04x:%04x\n", residentSeg, FP_OFF(int15_handler));
	printf(" INT 2F handler installed at %04x:%04x\n", residentSeg, FP_OFF(int2f_handler));
	printf(" %s keyboard layout\n", (kb->DriverFunctionRequired & 4) ? "Standard" : "Enhanced");

	printf("\n mKEYB debug mode - hit ESC key to terminate test mode\n");

  {	/* debug only */
	extern uchar far debug_scancode;        /* debug */
	uchar last_scancode = 0;

	do
	{
		if (*(uchar far*)RESPTR(&debug_scancode) != 0)
		{
			printf("shiftstate %02x scancode    %02x\n",
					*(uchar far*)MK_FP(0x40,0x17),
					*(uchar far*)RESPTR(&debug_scancode));

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
			last_scancode = r.h.ah;
			printf("key pressed %04x '%c'\n",r.x.ax,r.h.al);
		}
	}
	while (last_scancode != 1);
  } /* end debug */
	if(int9hChain) 	setvect(0x9,OldInt9);
	if(int16hChain) setvect(0x16,OldInt16);
	setvect(0x15,OldInt15);
	setvect(0x2f,OldInt2F);

	printf(" mKEYB - uninstalled\n");

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
	,Keyboard_ITstd
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
	,Keyboard_UX
	,Keyboard_TR
	;

/* 101/102 keys enhanced keyboards definition table */
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
	,&Keyboard_TR
	,&Keyboard_UK
	,&Keyboard_UX
	};

/* 83/84 keys standard keyboards definition table */
struct KeyboardDefinition *StdKeyDefTab[] =
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
	,&Keyboard_ITstd
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
	,&Keyboard_TR
	,&Keyboard_UK
	,&Keyboard_UX
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

	printf("MKEYB usage:\n"
		   "      MKEYB UK - United Kingdom keyboard\n"
		   "      MKEYB GR - German - deutsche Tastatur\n"
		   "      ....\n"
		   "      MKEYB /L - Lists all available keyboards\n"
		   "      MKEYB /U - Uninstalls previous keyboard driver\n"
		   "      MKEYB /Q - Quiet - absorb all keyboard input\n"
		   "      MKEYB /E - Specifies that an enhanced 101/102 keys keyboard is installed\n"
		   "      MKEYB /S - Specifies that a standard 83/84 keys keyboard is installed\n"
		   "      MKEYB /9 - Installs INT 9 handler (/9- to disable)\n"
		   "      MKEYB /G - Installs INT 16 handler (/G- to disable)\n"
		   "      MKEYB GR /T - Tests the GERman keyboard driver, don't go resident\n"
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
	uint int9hChain = AutodetectInt9h();
	uint int16hChain = AutodetectInt16h();
	uint enhancedKeyb = AutodetectKeyboard();
	int i, kb_idx = LENGTH(KeyDefTab);
	uchar far *pmodel;

	if (argv);
	if (argc);

	printf("mKEYB " MY_VERSION_TEXT " [" __DATE__ "] - " );

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
						  printf("\n");
						  UninstallKeyboard(1);
						  exit(0);
						  break;

				case 'Q': SilentKeyboard = 1;
						  break;

				case 'E': enhancedKeyb = 1;
						  break;

				case 'S': enhancedKeyb = 0;
						  break;

				case '9': int9hChain = (argptr[2] != '-');
					break;

				case 'G': int16hChain = (argptr[2] != '-');
					break;

				default: printf("unknown argument <%s>\n", argptr+1);
				case 'H':
				case '?':usage();
						 break;

			}
		} else {
			for (kb_idx = 0; kb_idx < LENGTH(KeyDefTab); kb_idx++)
			{
				if (stricmp(argptr,KeyDefTab[kb_idx]->LanguageShort) == 0)
				{
					break;
				}
			}

			if (kb_idx == LENGTH(KeyDefTab))
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

	if (kb_idx == LENGTH(KeyDefTab))
	{
		printf("you MUST specify a keyboard language like\n"
			   "   MKEYB GR\n"
			   "   MKEYB SP\n"
			   "use MKEYB /L to get a list of available languages\n");
		exit(1);
	}

	kb = KeyDefTab[kb_idx];
	if(!enhancedKeyb)
	{
		kb = StdKeyDefTab[kb_idx];
		if (kb == NULL)
		{
			printf("%s language not available for 83/84 keys keyboards\n"
				   "please select a different language\n");
			exit(1);
		}
		/* Patch enhanced keyboard layouts to use standard drivers */
		kb->DriverFunctionRequired = (kb->DriverFunctionRequired & 1) | 4;
	}

	printf("%s - %s\n", kb->LanguageShort, kb->Description);
	UninstallKeyboard(0);
	return InstallKeyboard(kb, GOTSR, int9hChain, int16hChain);
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
