/* keydefpo.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 */

#define NAME(x) x##_PO


#include <dos.h>
#include "mkeyb.h"


#define LANGUAGE "portugese"
#define STATUS   "revised by Davide"

#define COMBI

/********************************************************
 * PORTUGESE keyboard mappings				*
 ********************************************************/

/* keyboard image (by arkady)

Standard layout characters+scancodes:
ÉÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÑÍÍÍÍÍÍÍÍÍ»
º~29³!02³@03³#04³$05³%06³^07³&08³*09³(0A³)0B³-0C³=0D³Backsp 0Eº
ÇÄÄÄÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÁÄÄÂÄÄÄÄÄÄ¶
ºTab 0F³q10³w11³e12³r13³t14³y15³u16³i17³o18³p19³[1A³]1B³      º
ÇÄÄÄÄÄÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÙ <ÄÄÙ º
º Caps 3A³a1E³s1F³d20³f21³g22³h23³j24³k25³l26³;27³'28³Enter 1Cº
ÇÄÄÄÄÄÄÄÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÄÄÄÄÄÄÄ¶
º Shift 2A ³z2C³x2D³c2E³v2F³b30³n31³m32³,33³.34³/35³ Shift 36 º
ÇÄÄÄÄÄÄÄÄÂÄÁÄÄÄÁÄÂÄÁÄÂÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÂÄÁÄÂÄÁÄÄÄÁÄÂÄÄÄÄÄÄÄÄ¶
º Ctrl 1D³ Alt 38³\56³    Spacebar 39    ³\2B³Alt E38³Ctrl E1Dº
ÈÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÏÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÏÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍ¼
*/

/* copied mostly from norvegian,
   changed

	 5  4 $  .  . õ
	12  ' ?  .  . .
	13  ® ¯  .  . .
	26  + *  .  . ù
	27  ï `  .  . .
	39C ‡ €  .  . .
	40  § ¦  .  . .
	41  \ | #28 . .
	43  ~ ^ #28 . .
	83N . .  .  . !255
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	 '@') /*  3 2 #34  .  . @ */
 /* 3 */ PUNCT_ALTGR	 (0x04, '3', '#',	0x9C) /*  4 3 #35  .  . œ */
 /* 4 */ PUNCT_ALTGR	 (0x05, '4', '$',	0xF5) /*  5 4  $   .  . õ */
 /* 5 */ PUNCT		     (0x06, '5', '%'	    ) /*  6 5  %   .  . . */
 /* 6 */ PUNCT_CTRL	     (0x07, '6', '&',0x1E	) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	 '{') /*  8 7  /   .  . { */
 /* 8 */ PUNCT_CTRL_ALTGR(0x09, '8', '(',0x1B,	 '[') /*  9 8  (  #27 . [ */
 /* 9 */ PUNCT_CTRL_ALTGR(0x0A, '9', ')',0x1D,	 ']') /* 10 9  )  #29 . ] */
 /* 0 */ PUNCT_ALTGR	 (0x0B, '0', '=',	 '}') /* 11 0  =   .  . } */
 /* - */ PUNCT		 (0x0C,'\'', '?'	    ) /* 12 '  ?   .  . . */
 /* = */ PUNCT		 (0x0D,0xAE,0xAF	    ) /* 13 ®  ¯   .  . . */

#ifdef COMBI
 /* [ */ PUNCT_ALTGR (0x1A, '+', '*', COMBI4) /* 26  + *  .  . ù */
 /* ] */ PUNCT		 (0x1B,COMBI1,COMBI2    ) /* 27  ï `  .  . . */
#else
 /* [ */ PUNCT_ALTGR (0x1A, '+', '*',	0xF9) /* 26  + *  .  . ù */
 /* ] */ PUNCT		 (0x1B,0xEF, '`'	    ) /* 27  ï `  .  . . */
#endif
 /* ; */ ALPHA		 (0x27,0x87,0x80	    ) /* 39C ‡ €  .  . . */
 /* ' */ PUNCT		 (0x28,0xA7,0xA6	    ) /* 40  § ¦  .  . . */
 /* ~ */ PUNCT		 (0x29,'\\', '|'	    ) /* 41  \ | #28 . . */
#ifdef COMBI
 /* \ */ PUNCT		 (0x2B,COMBI5,COMBI3	) /* 43  ~ ^ #28 . . */
#else
 /* \ */ PUNCT		 (0x2B, '~', '^'	    ) /* 43  ~ ^ #28 . . */
#endif
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  , ;  .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  . :  .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  - _ #31 . . */
 /*   */ PUNCT		 (0x56, '<', '>'	    ) /* 86  < >  .  . . */

 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81

	 0
};

/*
   These keys are generated on a COMBI+character base.
   Some of them are correct only for codepage 850, since
   the standard 437 codepage doesn't have all accented characters
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {         /* ' a  e‚ i¡ o¢ u£ E #32' */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xA0, 0xB5,
 /* E */ 0x12, 0x82, 0x90,
 /* I */ 0x17, 0xA1, 0xD6,
 /* O */ 0x18, 0xA2, 0xE0,
 /* U */ 0x16, 0xA3, 0xE9,
 /*   */ 0x39, 0xEF, 0xEF, /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {         /* ` a… eŠ i o• u— #32` */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x85, 0xB7,
 /* E */ 0x12, 0x8A, 0xD4,
 /* I */ 0x17, 0x8D, 0xDE,
 /* O */ 0x18, 0x95, 0xE3,
 /* U */ 0x16, 0x97, 0xEB,
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {         /* ^ aƒ eˆ iŒ o“ u– #32^ */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x83, 0xB6,
 /* E */ 0x12, 0x88, 0xD2,
 /* I */ 0x17, 0x8C, 0xD7,
 /* O */ 0x18, 0x93, 0xE2,
 /* U */ 0x16, 0x96, 0xEA,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi4table)[] = {         /* " a„ e‰ i‹ o” u A O™ Uš y˜ #32" */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x84, 0x8E,
 /* E */ 0x12, 0x89, 0xD3,
 /* I */ 0x17, 0x8B, 0xD8,
 /* O */ 0x18, 0x94, 0x99,
 /* U */ 0x16, 0x81, 0x9A,
 /* Y */ 0x15, 0x98,    0, /* no Y character ?? */
 /*   */ 0x39, 0xF9, 0xF9, /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {        /* ~ n¤ N¥ #32~
	/*scancode lower upper*/
 /* A */ 0x1E, 0xC6, 0xC7,
 /* O */ 0x18, 0xE4, 0xE5,
 /* N */ 0x31, 0xA4, 0xA5,
 /*   */ 0x39,  '~',  '~', /* and additional generated character */
	0
};

uchar NAME(combi6table)[] = {
	/*scancode lower upper*/
	 0
};

#endif


struct KeyboardDefinition NAME(Keyboard) = {
	"PO",                                       //char LanguageShort[4];			// "GR",
	"PORTUGAL - portugese keyboard (by tom)",   //char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_FULL,                       //char DriverFunctionRequired;
	NAME(scancodetable),                        //char *ScancodeTable;

#ifdef COMBI
	{	NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif
	0,                                          //char DezimalDingsbums;
	0,                                          //char DefaultLayoutUS;			// TRUE for russian
	} ;
