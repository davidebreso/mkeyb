/* keydefla.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 */

#define NAME(x) x##_LA


#include <dos.h>
#include "mkeyb.h"

// latin america needs combi's
#define COMBI

/********************************************************
 * LATIN AMERICAN keyboard mappings			*
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

/* copied mostly from italy,
   changed

	 4  3 #35  . . .
	12  '  ?  #31 . \
	13  ¨  ­   . . .
	16C q  Q  #17 . @
	26  '  ù  #27 . .
	27  +  *  #29 . ~
	39C ¤  ¥   . . .
	40  {  [   . . ^
	41  |  ø   . . ª
	43  }  ]  #28 . `

	[Combi]
	' a  e‚ i¡ o¢ u£ E #32'
	` a… eŠ i o• u— #32`
	^ aƒ eˆ iŒ o“ u– #32^
	ù a„ e‰ i‹ o” u A O™ Uš y˜ #32ù
	~ n¤ N¥ #32~
	÷ C€ c‡
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT		 (0x03, '2', '"'	    ) /*  3 2 #34  .  . . */
//* 3 */ PUNCT		 (0x04, '3', '#'	    ) /*  4 3 #35  .  . . */
//* 4 */ PUNCT		 (0x05, '4', '$'	    ) /*  5 4  $   .  . . */
//* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  . . */
 /* 6 */ PUNCT_CTRL	 (0x07, '6', '&',0x1E	    ) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT		 (0x08, '7', '/'	    ) /*  8 7  /   .  . . */
 /* 8 */ PUNCT		 (0x09, '8', '('	    ) /*  9 8  (   .  . . */
 /* 9 */ PUNCT		 (0x0A, '9', ')'	    ) /* 10 9  )   .  . . */
 /* 0 */ PUNCT		 (0x0B, '0', '='	    ) /* 11 0  =   .  . . */
#ifdef COMBI
 /* - */ PUNCT_ALTGR	 (0x0C,COMBI6,'?',	'\\') /* 12 '  ?  #31 . \ */
#else
 /* - */ PUNCT_ALTGR	 (0x0C,'\'', '?',	'\\') /* 12 '  ?  #31 . \ */
#endif
 /* = */ PUNCT		 (0x0D,0xA8,0xAD	    ) /* 13 ¨  ­   .  . . */

 /* q */       ALTGR	 (0x10,			 '@') /* 16C q Q #17 . @ */
#ifdef COMBI
 /* [ */ PUNCT		 (0x1A,COMBI1,COMBI4	    ) /* 26  ' ù #27 . . */
 /* ] */ PUNCT_ALTGR	 (0x1B, '+', '*',     COMBI5) /* 27  + * #29 . ~ */
#else
 /* [ */ PUNCT		 (0x1A,'\'',0xF9	    ) /* 26  ' ù #27 . . */
 /* ] */ PUNCT_ALTGR	 (0x1B, '+', '*',	 '~') /* 27  + * #29 . ~ */
#endif
 /* ; */ ALPHA		 (0x27,0xA4,0xA5	    ) /* 39C ¤ ¥  .  . . */
#ifdef COMBI
 /* ' */ PUNCT_ALTGR	 (0x28, '{', '[',     COMBI3) /* 40  { [  .  . ^ */
#else
 /* ' */ PUNCT_ALTGR	 (0x28, '{', '[',	 '^') /* 40  { [  .  . ^ */
#endif
 /* ~ */ PUNCT_ALTGR	 (0x29, '|',0xF8,	0xAA) /* 41  | ø  .  . ª */
#ifdef COMBI
 /* \ */ PUNCT_CTRL_ALTGR(0x2B, '}', ']',0x1C,COMBI2)/* 43 } ] #28 . ` */
#else
 /* \ */ PUNCT_CTRL_ALTGR(0x2B, '}', ']',0x1C,	 '`') /* 43  } ] #28 . ` */
#endif
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  , ;  .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  . :  .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  - _  .  . . */
 /*   */ PUNCT		 (0x56, '<', '>'	    ) /* 86  < >  .  . . */

 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
 /* 5 */ ALTGR           (0x06, EURO)          // Added by Tom
	 0
};

/* these keys are generated on a COMBI+character base,
   the upper case accented characters '`^+AEIOU need an enhanced
   codepage (850), as they can't be displayed in standard BIOS
   codepage (437)
*/

/* [Combi]
   ' a  e‚ i¡ o¢ u£ E #32'
   ` a… eŠ i o• u— #32`
   ^ aƒ eˆ iŒ o“ u– #32^
   ù a„ e‰ i‹ o” u A O™ Uš y˜ #32ù
   ~ n¤ N¥ #32~
   ÷ C€ c‡
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {		/* ' a  e‚ i¡ o¢ u£ E #32' */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xA0, 'Á', // á
 /* E */ 0x12, 0x82, 'É',
 /* I */ 0x17, 0xA1, 'Í',
 /* O */ 0x18, 0xA2, 'Ó',    
 /* U */ 0x16, 0xA3, 'Ú',    // 00a3 'ú'
 /*   */ 0x39, '\'', '\'', /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {		/* ` a… eŠ i o• u— #32` */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x85, 'À',
 /* E */ 0x12, 0x8A, 'È',
 /* I */ 0x17, 0x8D, 'Ì',
 /* O */ 0x18, 0x95, 'Ò',
 /* U */ 0x16, 0x97, 'Ù',
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {		/* ^ aƒ eˆ iŒ o“ u– #32^ */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x83, 0xB6,
 /* E */ 0x12, 0x88, 0xD2,
 /* I */ 0x17, 0x8C, 0xD7,
 /* O */ 0x18, 0x93, 0xE2,
 /* U */ 0x16, 0x96, 0xEA,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi4table)[] = {		/* ´ a„ e‰ i‹ o” u A O™ Uš y˜ #32ù */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x84, 'Ä', // ä 
 /* E */ 0x12, 0x89, 'Ë', 
 /* I */ 0x17, 0x8B, 'Ï', 
 /* O */ 0x18, 0x94, 'Ö',
 /* U */ 0x16, 0x81, 'Ü',
 /* Y */ 0x15, 0x98, 0x98, 
 /*   */ 0x39,  '´',  '´', /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {		/* ~ n¤ N¥ #32~ */
	/*scancode lower upper*/
 /* N */ 0x16, 0xA4, 0xA5,
 /*   */ 0x39,  '~',  '~', /* and additional generated character */
	 0
};
uchar NAME(combi6table)[] = {		/* something missing yet ?? */
	/*scancode lower upper*/
//   ' a  e‚ i¡ o¢ u£ E #32'
	
 /* A */ 0x1E, 0x85, 0x85, /* à */
 /* E */ 0x12, 0x90, 0x90, 
 /* I */ 0x17, 0x8d, 0x8d, /* ì */
 /* O */ 0x18, 0x95, 0x95, /* à */
 /* U */ 0x16, 0x97, 0x97,
 /*   */ 0x39,  '\'',  '\'', /* and additional generated character */
	 0
};

#endif

struct KeyboardDefinition NAME(Keyboard) = {
	"LA",                                          //char LanguageShort[4];			// "GR",                    
	"Latin American - keyboardo espanolo latino americano (by tom)",  //char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_FULL,                          //char DriverFunctionRequired;                                  
	NAME(scancodetable),                           //char *ScancodeTable;                                          
#ifdef COMBI
	{	NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif			
	0,                                           //char DezimalDingsbums;                                        
	0,                                             //char DefaultLayoutUS;			// TRUE for russian             
	} ;
