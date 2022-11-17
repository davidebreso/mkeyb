/*
    mKEYBR.C - minimum keyboard handler for international keyboards

    ******* RESIDENT PART **********

    requires only ~500-600 byte of precious memory to do what it does.

    for details, please see readme.txt


    Copyright (C) 2002 by te@tomehlert.de
*/

#include <dos.h>

#define RESIDENT 
#include "mkeyb.h"



#ifdef FASTSWITCH
	#define NO_DECIDINGSBUMS
	#define NO_REPLACESCAN
	#define NO_ALTGREY

	#define NAME(x) x##_fastswitch
#elif defined(STANDARD)
	#define NO_FASTSWITCH
	#define NO_ALTGREY

	#define NAME(x) x##_standard
#elif defined(STD_FULL)
	#define NO_FASTSWITCH
	#define NO_ALTGREY
	#define COMBI
	#define STANDARD

	#define NAME(x) x##_stdfull
#elif defined(COMBI)
	#define NO_FASTSWITCH

	#define NAME(x) x##_full
#else
	#define NO_FASTSWITCH

	#define NAME(x) x##_normal
#endif


/** 'normal' data **********************************/

extern uchar cdecl usebiosonly_flag;
extern uchar cdecl lastisctrl_flag;
extern uchar cdecl debug_scancode;

extern uint  RESIDENT cdecl currentCombi             ;
extern char *RESIDENT cdecl ResidentCombiTables[6]   ;
extern uchar RESIDENT cdecl DecimalDingsBums         ;    /* grey , or . */

/* MUST BE LAST DATA MEMBER */
extern uchar * cdecl pResidentScancodetable;


/** normal data end, ONE last member - the scan code translation table
//
// scan code translation table
// this also marks the end of our resident data
//
//
// the format for each entry is
//
// [0] scancode to search
// [1] different shift states handled (SHIFT,CTRL,ALTGREY,...)
//     also implies table entry size
// [2..n]  keycode to send into BIOS buffer
//
*/


/** data end **********************************/


/* use BIOS INT16/05 to enter keystroke into key buffer */

#ifdef __TURBOC__
	#define GENERATE_KEYSTROKE(scancode,keycode)        \
		_CL = keycode,                                  \
		_CH = scancode,                                 \
		_AH = 5;                                        \
		__int__(0x16);
#else
	#define GENERATE_KEYSTROKE(scancode,keycode)        \
		_asm mov cl,byte ptr keycode;                   \
		_asm mov ch,byte ptr scancode;                  \
		_asm mov ah,5;                                  \
		_asm int 0x16;
#endif

/* tech note: as michael Tyc found out, this interrupt
		_asm mov AX,0x9102;
		_asm int 0x15;
   isn't executed on all BIOS for INT16/05
   this might be added here. As the details aren't that clear,
   and the interrupt seems not to be in use (nowadays),
   it's left out here, but may be added later.
*/



int cdecl NAME(cint15_handler)(uchar scancode)
{
	uchar  RESIDENT *tbl;
	ushort BIOSstate;
	uchar  keyflags;

	BIOSstate     = *(short far*)MK_FP(0x40,0x17);

	debug_scancode = scancode;              /* very nice for debugging   */
											/* hit ESC - and we are gone */

	if (SilentKeyboard)
	{
		return 0;							/* absorb all keyboard input :
												tell the BIOS to ignore scancode */
	}

#ifdef NO_FASTSWITCH
	if (BIOSstate & 0x08 && BIOSstate & 0x04)   /* Ctrl+Alt+F1/F2 */
	{
		if (scancode == 0x3b || scancode == 0x3c)
		{
			usebiosonly_flag = 0x3b - scancode; /* 0x00 or 0xff */
			return 0;
		}
	}
#else
	if (! lastisctrl_flag &&                   /* the last key was Ctrl */
	*(char far*)MK_FP(0x40, 0x96) & 0x04 && /* was the Right Ctrl */
	scancode == (0x1d + 0x80))              /* and now Ctrl key is released */
	{
		usebiosonly_flag = ~usebiosonly_flag;  /* toggles between 0x00 and 0xff */
	}
	if (scancode > 0 && scancode < 0x80) /* Any key pressed */
		lastisctrl_flag = 0xff;
	if (scancode == 0x1d) /* Ctrl */
		lastisctrl_flag = 0;
#endif

	if (usebiosonly_flag == 0)
		return scancode;

							/*
							** E0 scancode handling
							**      don't handle ANYTHING, if E0 was pressed
							*/
	if (*(char far*)MK_FP(0x40, 0x96) & 0x02) /* last code was E0 hidden code */
	{
		return scancode;
	}

#ifndef NO_DECIDINGSBUMS
									/* explicit handling of numeric '.' */

	if (        scancode == 0x53 &&
				DecimalDingsBums &&
				BIOSstate & 0x20)   /* NUMLOCK pressed */
	{
							/* the grey . is particular ugly */
		GENERATE_KEYSTROKE(scancode,DecimalDingsBums);
		return 0;
	}
#endif /* NO_DECIDINGSBUMS */

									/* CAPS handling:
									   logical shift state = CapsPressed ^ ShiftPressed */
	if (BIOSstate & 3)
		BIOSstate ^= 0x40;

#ifdef COMBI
									/* all that swedish, spanish stuff ;-)
									   these keys are generated
									   by 2 character combinations
									*/
	if (currentCombi != 0)
	{
									/* key release - handled by BIOS*/
		if (scancode & 0x80)
			return scancode;

		if (scancode == 0x2a  ||    /* left  shift - handled by BIOS*/
			scancode == 0x36)       /* right shift - handled by BIOS*/
		{
			return scancode;
		}

		tbl = (uchar*)ResidentCombiTables[currentCombi - COMBI1];
		currentCombi = 0;

		for ( ; tbl[0] != 0; tbl += 3)
		{
			if (tbl[0] == scancode)
			{                                /* these character all use CAPS */
				GENERATE_KEYSTROKE(0, BIOSstate & 0x40 ? tbl[2] : tbl[1]);

				return 0;
			}
		}
		/* not found ? then the last entry before holds the character to generate */

		GENERATE_KEYSTROKE(0, BIOSstate & 0x40 ? tbl[-3+2] : tbl[-3+1]);

		/* and fall through to generate the key */
	}
#endif

							/*
								'conventional' keyboard mappings
								search our table and locate the scancode
							*/

	for (   tbl = pResidentScancodetable;
				tbl[0] != scancode;
				tbl += (tbl[1] & SIZEFIELD) )
	{
							/* end of table --> not found -->
								let the BIOS do it's work
							*/
		if (tbl[0] == 0)
			return scancode;
	}

						/* now tbl points to entry in scancodetable */

	keyflags = tbl[1];
	tbl += 2;                      /* points to normal key  */

#ifndef NO_REPLACESCAN

									/* simple scancode exchange */
	if (keyflags == REPLACESCAN)
		return tbl[0];

#endif /* NO_REPLACESCAN */
									/* we found the table entry for the scancode
									   match the shiftstate in the table against
									   the current shift state
									*/

									/* now advance tbl in a way, that it
									   finally points to the key to be generated
									*/


#ifndef NO_ALTGREY

	if (keyflags & _KALTGR &&                   /* has ALTGREY definition */
		*(char far*)MK_FP(0x40,0x96) & 0x08)    /* and right ALT pressed */
	{
		if (keyflags & _KCHAR)                  /* skip over other characters */
			tbl+=2;

		if (keyflags & _KCTRL)
			tbl += 1;

		if (BIOSstate & 0x40)					/* is Shift pressed ? */
		{
			if (keyflags & _KALTGRSHIFT)        /* uses ALTGREY with shifts if defined */
			{
				tbl += 1;
			} else {
				return scancode;				/* let the BIOS do its work if not */
			}
		}

		goto simulateKeyPress;
	}
#endif  /* NO_ALTGREY */

	if (BIOSstate & 0x08)           /* any ALT pressed */
	{
#ifdef STANDARD
		if (keyflags & _KALTGR &&	/* has ALTGREY definition */
			BIOSstate & 0x04)    	/* and CTRL is also pressed */
		{
			if (keyflags & _KCHAR) 		/* skip over other characters */
				tbl+=2;

			if (BIOSstate & 0x40)					/* is Shift pressed ? */
			{
				if (keyflags & _KALTGRSHIFT)        /* uses ALTGREY with shifts if defined */
				{
					tbl += 1;
				} else {
					return scancode;				/* let the BIOS do its work if not */
				}
			}

			goto simulateKeyPress;
		}
#endif  /* STANDARD */
		return scancode;            /* leave the work to BIOS */
	}

	if(BIOSstate & 0x04)           /* either CTRL pressed */
	{
		if((keyflags & _KCTRL) == 0)    /* but no Ctrl definition given */
				return scancode;
		if(keyflags & _KCHAR)
			tbl += 2;

		goto simulateCtrlKeyPress;		/* Skip check for COMBIs to avoid clash with ^A..^F */
	}

	if ((keyflags & _KCHAR)  == 0)  /* it should have _KCHAR defined */
	{
		return scancode;        	/* if not,  give it to BIOS         */
	}

	if(keyflags & _KCAPS)
	{
		if(BIOSstate & 0x40)    /* CAPS pressed */
			tbl++;
	}
	else
	{
		if(BIOSstate & 0x03)    /* either SHIFT pressed */
			tbl++;
	}

simulateKeyPress:

#ifdef COMBI
	if (tbl[0] >= COMBI1 && tbl[0] <= COMBI6)
	{
		currentCombi         = tbl[0];
		return 0;
	}
#endif

simulateCtrlKeyPress:

	if (tbl[0] == IGNORE)
		return scancode;	/* let BIOS do its work */

							/* strange, but necessary */
	if (tbl[0] == 0xf0 ||   /* this is a BIOS 'feature' */
		tbl[0] == 0xe0)     /* this too               */
	{
		scancode = 0;
	}

	GENERATE_KEYSTROKE(scancode,tbl[0]);

	return 0;
}

void NAME(END_cint15_handler)(void){}	// MARKER for end of resident part

