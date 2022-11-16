/* keydefsg.h */

/*
 * history
 * 27 apr 02: tom ehlert - creation
 * 16 nov 22: davide bresolin - review
 */

#define NAME(x) x##_SG


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "swiss german"
#define STATUS   "first try"

/********************************************************
 * SWISS GERMAN keyboard mappings			*
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

/* copied mostly from swiss french,
   changed

	26C  Š #27 . [
	39C ” ‚  .  . .
	40C „ …  .  . {
*/

uchar NAME(scancodetable)[] = {   

 //* Y */ REPLACE	 (0x15,0x2C		    ) /* 21C z  Z  #26 . . */
 //* Z */ REPLACE	 (0x2C,0x15		    ) /* 44C y  Y  #25 . . */

 /* Z */ ALPHA_CTRL 	(0x2C, 'y', 'Y', 0x19		)
 /* Y */ ALPHA_CTRL 	(0x15, 'z', 'Z', 0x1A		)



 /* 1 */ PUNCT_ALTGR	 (0x02, '1', '+',	 '|') /*  2 1  +   .  .  | */
 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	 '@') /*  3 2 #34  .  .  @ */
 /* 3 */ PUNCT_ALTGR	 (0x04, '3', '*',	 '#') /*  4 3  *   .  . #35 */
 /* 4 */ PUNCT		 (0x05, '4',0x87	    ) /*  5 4  ‡   .  .  . */
//* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  .  . */
 /* 6 */ PUNCT_CTRL_ALTGR(0x07, '6', '&',0x1E,	0xAA) /*  7 6  &  #30 .  ª */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	0xDD) /*  8 7  /   .  .  İ */
 /* 8 */ PUNCT_ALTGR	 (0x09, '8', '(',	0xBD) /*  9 8  (   .  .  ½ */
 /* 9 */ PUNCT		 (0x0A, '9', ')'	    ) /* 10 9  )   .  .  . */
 /* 0 */ PUNCT		 (0x0B, '0', '='	    ) /* 11 0  =   .  .  . */
 /* - */ PUNCT_ALTGR	 (0x0C,'\'', '?',	0xEF) /* 12 '  ?   .  .  ï */
 /* = */ PUNCT_ALTGR	 (0x0D, '^', '`',	 '~') /* 13 ^  `   .  .  ~ */

 /* [ */ ALPHA_ALTGR	 (0x1A,0x81,0x8A,	 '[') /* 26C   Š  #27 . [ */
 /* ] */ PUNCT_CTRL_ALTGR(0x1B,0xF9, '!',0x1D,	 ']') /* 27  ù #33 #29 . ] */
 /* ; */ ALPHA		 (0x27,0x94,0x82	    ) /* 39C ”  ‚   .  . . */
 /* ' */ ALPHA_ALTGR	 (0x28,0x84,0x85,	 '{') /* 40C „  …   .  . { */
 /* ~ */ PUNCT		 (0x29,0xF5,0xF8	    ) /* 41  õ  ø   .  . . */
 /* \ */ PUNCT		 (0x2B, '$',0x9C	    ) /* 43  $  œ   .  . } */
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  ,  ;   .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  .  :   .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  -  _  #31 . . */
 /*   */ PUNCT_CTRL_ALTGR(0x56, '<', '>',0x1C,	'\\') /* 86  <  >   .  . \ */

 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
	 0
};

struct KeyboardDefinition NAME(Keyboard) = {
	"SG",                                          //char LanguageShort[4];			// "GR",                    
	"SWISS GERMAN - schweizer deutsches Keyboard, keine combi's (by tom)",  //char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_NORMAL,                        //char DriverFunctionRequired;                                  
	NAME(scancodetable),                           //char *ScancodeTable;                                          
#ifdef COMBI
	{	NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif			
	',',                                           //char DezimalDingsbums;                                        
	0,                                             //char DefaultLayoutUS;			// TRUE for russian             
	} ;
