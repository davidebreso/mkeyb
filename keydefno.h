/* keydefno.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 */         

#define NAME(x) x##_NO


#include <dos.h>
#include "mkeyb.h"
 

#define LANGUAGE "norvegian"
#define STATUS   "first try"

/********************************************************
 * NORVEGIAN keyboard mappings				*
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

/* copied mostly from daenish,
   changed

	13  \ ` #28 . О
	39C ⌡ ²  .  . .
	40C ▒ ▓  .  . .
	41  | У  .  . .
	86  < >  .  . .
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	 '@') /*  3 2 #34  .  . @ */
 /* 3 */ PUNCT_ALTGR	 (0x04, '3', '#',	0x9C) /*  4 3 #35  .  . ° */
 /* 4 */ PUNCT_ALTGR	 (0x05, '4',0xCF,	 '$') /*  5 4  о   .  . $ */
 /* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  . . */
 /* 6 */ PUNCT_CTRL	 (0x07, '6', '&',0x1E	    ) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	 '{') /*  8 7  /   .  . { */
 /* 8 */ PUNCT_CTRL_ALTGR(0x09, '8', '(',0x1B,	 '[') /*  9 8  (  #27 . [ */
 /* 9 */ PUNCT_CTRL_ALTGR(0x0A, '9', ')',0x1D,	 ']') /* 10 9  )  #29 . ] */
 /* 0 */ PUNCT_ALTGR	 (0x0B, '0', '=',	 '}') /* 11 0  =   .  . } */
 /* - */ PUNCT		 (0x0C, '+', '?'	    ) /* 12 +  ?   .  . . */
 /* = */ PUNCT_CTRL_ALTGR(0x0D,'\\', '`',0x1C,	0xEF) /* 13 \  `  #28 . О */

 /* [ */ ALPHA		 (0x1A,0x86,0x8F	    ) /* 26C ├ ▐  .  . . */
 /* ] */ PUNCT_ALTGR	 (0x1B,0xF9, '^',	 '~') /* 27  Ы ^  .  . ~ */
 /* ; */ ALPHA		 (0x27,0x9B,0x9D	    ) /* 39C ⌡ ²  .  . . */
 /* ' */ ALPHA		 (0x28,0x91,0x92	    ) /* 40C ▒ ▓  .  . . */
 /* ~ */ PUNCT		 (0x29, '|',0xF5	    ) /* 41  | У  .  . . */
 /* \ */ PUNCT		 (0x2B,'\'', '*'	    ) /* 43  ' *  .  . . */
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  , ;  .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  . :  .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  - _  .  . . */
 /*   */ PUNCT		 (0x56, '<', '>'	    ) /* 86  < >  .  . . */ 
 
 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
 
	 0
};


struct KeyboardDefinition NAME(Keyboard) = {
	"NO",                                          //char LanguageShort[4];			// "GR",                    
	"NORVEGIAN - norske keyboard (by tom)",  //char *Description;				// created by, "with combis"
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
