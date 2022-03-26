/* keydefsf.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 */

#define NAME(x) x##_SF


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "swiss french"
#define STATUS   "first try"

/********************************************************
 * SWISS FRENCH keyboard mappings			*
 ********************************************************/

/* keyboard image (by arkady)

Standard layout characters+scancodes:
имммямммямммямммямммямммямммямммямммямммямммямммямммяммммммммм╩
╨~29Ё!02Ё@03Ё#04Ё$05Ё%06Ё^07Ё&08Ё*09Ё(0AЁ)0BЁ-0CЁ=0DЁBacksp 0E╨
гдддаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбдддддд╤
╨Tab 0FЁq10Ёw11Ёe12Ёr13Ёt14Ёy15Ёu16Ёi17Ёo18Ёp19Ё[1AЁ]1BЁ      ╨
гддддддадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадбды <дды ╨
╨ Caps 3AЁa1EЁs1FЁd20Ёf21Ёg22Ёh23Ёj24Ёk25Ёl26Ё;27Ё'28ЁEnter 1C╨
гддддддддадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадддддддд╤
╨ Shift 2A Ёz2CЁx2DЁc2EЁv2FЁb30Ёn31Ёm32Ё,33Ё.34Ё/35Ё Shift 36 ╨
гддддддддбдадддадбдадбдадддадддадддадддадбдадбдадддадбдддддддд╤
╨ Ctrl 1DЁ Alt 38Ё\56Ё    Spacebar 39    Ё\2BЁAlt E38ЁCtrl E1D╨
хммммммммомммммммомммомммммммммммммммммммомммомммммммомммммммм╪
*/

/* copied mostly from portugese,
   changed

	 2  1  +   .  .  |
	 3  2 #34  .  .  @
	 4  3  *   .  . #35
	 5  4  ┤   .  .  .
	 6  5  %   .  .  .
	 7  6  &  #30 .  ╙
	 8  7  /   .  .  щ
	 9  8  (   .  .  ╫
	10  9  )   .  .  .
	11  0  =   .  .  .
	12  '  ?   .  .  О
	13  ^  `   .  .  ~
	21C z  Z  #26 .  .
	26C ┼  │  #27 .  [
	27  Ы #33 #29 .  ]
	39C ┌  ■   .  .  .
	40C ┘  └   .  .  {
	41  У  Ь   .  .  .
	43  $  °   .  .  }
	44C y  Y  #25 .  .
	86  <  >  #28 .  \
*/

uchar NAME(scancodetable)[] = {    

 //* Y */ REPLACE	 (0x15,0x2C		    ) /* 21C z  Z  #26 . . */
 //* Z */ REPLACE	 (0x2C,0x15		    ) /* 44C y  Y  #25 . . */

 /* Z */ PUNCT_ALTGR	(0x2C, 'y', 'Y', 0x19		)
 /* Y */ PUNCT_ALTGR	(0x15, 'z', 'Z', 0x1A		)

 /* 1 */ PUNCT_ALTGR	 (0x02, '1', '+',	 '|') /*  2 1  +   .  .  | */
 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	 '@') /*  3 2 #34  .  .  @ */
 /* 3 */ PUNCT_ALTGR	 (0x04, '3', '*',	 '#') /*  4 3  *   .  . #35 */
 /* 4 */ PUNCT		 (0x05, '4',0x87	    ) /*  5 4  ┤   .  .  . */
//* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  .  . */
 /* 6 */ PUNCT_CTRL_ALTGR(0x07, '6', '&',0x1E,	0xAA) /*  7 6  &  #30 .  ╙ */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	0xDD) /*  8 7  /   .  .  щ */
 /* 8 */ PUNCT_ALTGR	 (0x09, '8', '(',	0xBD) /*  9 8  (   .  .  ╫ */
 /* 9 */ PUNCT		 (0x0A, '9', ')'	    ) /* 10 9  )   .  .  . */
 /* 0 */ PUNCT		 (0x0B, '0', '='	    ) /* 11 0  =   .  .  . */
 /* - */ PUNCT_ALTGR	 (0x0C,'\'', '?',	0xEF) /* 12 '  ?   .  .  О */
 /* = */ PUNCT_ALTGR	 (0x0D, '^', '`',	 '~') /* 13 ^  `   .  .  ~ */

 /* [ */ ALPHA_ALTGR	 (0x1A,0x8A,0x81,	 '[') /* 26C ┼  │  #27 . [ */
 /* ] */ PUNCT_ALTGR	 (0x1B,0xF9, '!',	 ']') /* 27  Ы #33 #29 . ] */
 /* ; */ ALPHA		 (0x27,0x82,0x94	    ) /* 39C ┌  ■   .  . . */
 /* ' */ ALPHA_ALTGR	 (0x28,0x85,0x84,	 '{') /* 40C ┘  └   .  . { */
 /* ~ */ PUNCT		 (0x29,0xF5,0xF8	    ) /* 41  У  Ь   .  . . */
 /* \ */ PUNCT		 (0x2B, '$',0x9C	    ) /* 43  $  °   .  . } */
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  ,  ;   .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  .  :   .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  -  _  #31 . . */
 /*   */ PUNCT_CTRL_ALTGR(0x56, '<', '>',0x1C,	'\\') /* 86  <  >   .  . \ */  
 
 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
 
	 0
};

struct KeyboardDefinition NAME(Keyboard) = {
	"SF",                                          //char LanguageShort[4];			// "GR",                    
	"SWISS FRENCH - (by tom)",  //char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_NORMAL,                        //char DriverFunctionRequired;                                  
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
