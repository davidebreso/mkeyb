/* keydefnl.h */

/*
 * history
 * 20 apr 02: tom ehlert - creation
 */

#define NAME(x) x##_NL


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "dutch"
#define STATUS   "by Bart"

// I don't think german DOS keyboard driver needs combies
// #define COMBI

/********************************************************
 * DUTCH keyboard mappings				*
 ********************************************************/

uchar NAME(scancodetable)[] =	{

 /* 1 */       ALTGR	 (0x02,			0xFB) /* ˚ */
 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	0xFD) /* ˝ */
 /* 3 */       ALTGR	 (0x04,			0xFC) /* ¸ */
 /* 4 */       ALTGR	 (0x05,			0xAC) /* ¨ */
 /* 5 */       ALTGR	 (0x06,			0xAB) /* ´ */
 /* 6 */ PUNCT_ALTGR	 (0x07, '6', '&',	0xF3) /* Û */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	0x9C) /* ú */
 /* 8 */ PUNCT_ALTGR	 (0x09, '8', '(',	 '{')
 /* 9 */ PUNCT_ALTGR	 (0x0A, '9', ')',	 '}')
 /* 0 */ PUNCT		 (0x0B, '0', '\''	    )

 /* - */ PUNCT_ALTGR	 (0x0C, '/', '?',	'\\')
#ifdef COMBI
 /* = */ PUNCT		 (0x0D,COMBI1,COMBI2	    ) /* COMBI ' and ` + aeiou*/
#else
 /* = */ PUNCT_ALTGR	 (0x0D,0xF8, '~',	0xF7) /* ¯ ˜ */
#endif
 /* r */       ALTGR	 (0x13,		 	0x14)
 /* [ */ PUNCT		 (0x1A,0xF9, '^'	    ) /* ˘ */
 /* ] */ PUNCT		 (0x1B, '*',0xB3	    ) /* ≥ */

 /* s */       ALTGR	 (0x1F,			0xE1) /* · */

 /* ; */ PUNCT		 (0x27, '+',0xF1	    ) /* Ò */
 /* ' */ PUNCT		 (0x28,'\'', '`'	    )
#ifdef COMBI
 /* ` */ PUNCT		 (0x29,COMBI3,0xF8	    ) /* COMBI ^ + aeiou */
#else
 /* ` */ PUNCT_ALTGR	 (0x29, '@',0x15,	0xAA) /* ™ */
#endif
 /* \ */ PUNCT		 (0x2B, '<', '>'	    )
 /* z */       ALTGR	 (0x2C,			0xAE) /* Æ */
 /* c */       ALTGR	 (0x2E,			0x9B) /* õ */

 /* m */       ALTGR	 (0x32,			0xE6) /* greek mue */
 /* , */ PUNCT_CTRL	 (0x33, ',', ';',0xFF	    )
 /* . */ PUNCT_CTRL_ALTGR(0x34, '.', ':',0x1F,	0xFA) /* ˙ */
 /* / */ PUNCT_CTRL	 (0x35, '-', '=',0x1F	    )
 /*   */ PUNCT_ALTGR	 (0x56, ']', '[',	 '|')
	 0
};

/* these keys are generated on a COMBI+character base,
   don't know if that is correct.
   I also don't know what keys to generate, as the
   standard character set (DOS/BIOS) doesn't have
   norwegian/swedish/spanish characters
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {		/* ' a† eÇ i° o¢ u£ Eê #32' */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xA0,    0,
 /* E */ 0x12, 0x82, 0x90,
 /* I */ 0x17, 0xA1,    0,
 /* O */ 0x18, 0xA2,    0,
 /* U */ 0x16, 0xA3,    0,
 /*   */ 0x39, '\'', '\'', /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {		/* ` aÖ eä iç oï uó #32` */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x85,    0,
 /* E */ 0x12, 0x8A,    0,
 /* I */ 0x17, 0x8D,    0,
 /* O */ 0x18, 0x95,    0,
 /* U */ 0x16, 0x97,    0,
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {		/* ^ aÉ eà iå oì uñ #32^ */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x83,    0,
 /* E */ 0x12, 0x88,    0,
 /* I */ 0x17, 0x8C,    0,
 /* O */ 0x18, 0x93,    0,
 /* U */ 0x16, 0x96,    0,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi4table)[] = {		/* something missing yet ?? */
	/*scancode lower upper*/
 /*   */ 0x39,  ' ',  ' ', /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {		/* something missing yet ?? */
	/*scancode lower upper*/
 /*   */ 0x39,  ' ',  ' ', /* and additional generated character */
	 0
};

#endif

struct KeyboardDefinition NAME(Keyboard) = {
	"NL",                                          //char LanguageShort[4];			// "GR",                    
	"NETHERLANDS - dutch keyboard (by Bart)",  //char *Description;				// created by, "with combis"
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
