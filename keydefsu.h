/* keydefsu.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 */

#define NAME(x) x##_SU


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "finnish"
#define STATUS   "first try"

/********************************************************
 * FINNISH keyboard mappings				*
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

/* copied mostly from swedish,
   changed

	 5 4 Ï . . $
	13 ï ` . . .
	27 ù ^ . . ~
	41 õ « . . .
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	 '@') /*  3 2 #34  .  . @ */
 /* 3 */ PUNCT_ALTGR	 (0x04, '3', '#',	0x9C) /*  4 3 #35  .  . œ */
 /* 4 */ PUNCT_ALTGR	 (0x05, '4',0xCF,	 '$') /*  5 4  Ï   .  . $ */
 /* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  . . */
 /* 6 */ PUNCT_CTRL	 (0x07, '6', '&',0x1E	    ) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	 '{') /*  8 7  /   .  . { */
 /* 8 */ PUNCT_CTRL_ALTGR(0x09, '8', '(',0x1B,	 '[') /*  9 8  (  #27 . [ */
 /* 9 */ PUNCT_CTRL_ALTGR(0x0A, '9', ')',0x1D,	 ']') /* 10 9  )  #29 . ] */
 /* 0 */ PUNCT_ALTGR	 (0x0B, '0', '=',	 '}') /* 11 0  =   .  . } */
 /* - */ PUNCT_ALTGR	 (0x0C, '+', '?',	'\\') /* 12 +  ?   .  . \ */
 /* = */ PUNCT		 (0x0D,0xEF, '`'	    ) /* 13 ï  `   .  . . */

 /* [ */ ALPHA		 (0x1A,0x86,0x8F	    ) /* 26C †   .  . . */
 /* ] */ PUNCT_ALTGR	 (0x1B,0xF9, '^',	 '~') /* 27  ù ^  .  . ~ */
 /* ; */ ALPHA		 (0x27,0x94,0x99	    ) /* 39C ” ™  .  . . */
 /* ' */ ALPHA		 (0x28,0x84,0x8E	    ) /* 40C „   .  . . */
 /* ~ */ PUNCT		 (0x29,0xF5,0xAB	    ) /* 41  õ «  .  . . */
 /* \ */ PUNCT		 (0x2B,'\'', '*'	    ) /* 43  ' *  .  . . */
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  , ;  .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  . :  .  . . */
 /* / */ PUNCT_CTRL	 (0x35, '-', '_',0x1F	    ) /* 53  - _ #31 . . */
 /*   */ PUNCT_CTRL_ALTGR(0x56, '<', '>',0x1C,	 '|') /* 86  < > #28 . | */
	 0
};

#define DECIMALDINGSBUMS ','

struct KeyboardDefinition NAME(Keyboard) = {
	"SU",                                          //char LanguageShort[4];			// "GR",                    
	"SUOMI - finnish Keyboard, keine combi's (by tom)",  //char *Description;				// created by, "with combis"
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
