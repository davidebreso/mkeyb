/* keydefsp.h */


#define LANGUAGE "spanish"
#define STATUS   "mostly OK"

#define NAME(x) x##_SP


#include <dos.h>
#include "mkeyb.h"


#define COMBI


/********************************************************
 * SPANISH keyboard mappings                            *
 ********************************************************/

/* table layout:

key on US keyboard,
	scancode,
		flags, what is defined
			3 keys for NORMAL+CTRL, 1 for ALTGREY
*/

uchar NAME(scancodetable)[] = {

 /* 1 */       ALTGR     (0x02,                  '|')
 /* 2 */ PUNCT_ALTGR     (0x03, '2', '"',        '@')
 /* 3 */ PUNCT_ALTGR     (0x04, '3',0xFA,       0x23)
//* 4 */ PUNCT           (0x05, '4', '$'            )
//* 5 */ PUNCT_ALTGR     (0x06, '5', '%',      EURO )
 /* 6 */ PUNCT_ALTGR     (0x07, '6', '&',       0xAA) /* ™ */
 /* 7 */ PUNCT           (0x08, '7', '/'            )
 /* 8 */ PUNCT           (0x09, '8', '('            )
 /* 9 */ PUNCT           (0x0A, '9', ')'            )
 /* 0 */ PUNCT           (0x0B, '0', '='            )
 /* - */ PUNCT_CTRL      (0x0c,'\'', '?',0x1F       )

 /* = */ PUNCT           (0x0D,0xAD,0xA8            ) /* 13  ≠ ® . . . */

 /* E */ ALTGR           (0x12,                  EURO)

#ifdef COMBI
 /* [ */ PUNCT_ALTGR     (0x1A,COMBI2,COMBI3,    '[')
#else
 /* [ */ PUNCT_ALTGR     (0x1A, '`', '^',        '[')
#endif
 /* ] */ PUNCT_ALTGR     (0x1B, '+', '*',        ']')
 /* ; */ ALPHA_ALTGR     (0x27,0xA4,0xA5,        '~') /* 39C § • . . ~ */
#ifdef COMBI
 /* ' */ PUNCT_ALTGR     (0x28,COMBI1,COMBI4,    '{') /* 40  ' ˘ . . { */
#else
 /* ' */ PUNCT_ALTGR     (0x28,'\'',0xF9,        '{')
#endif
 /* ` */ PUNCT_CTRL_ALTGR(0x29,'ß','¶',0x1C,  '\\') /* 41  ß ¶ #28 . \ */
 /* \ */ PUNCT_ALTGR     (0x2B,0x87,0x80,        '}') /* á Ä */
 /* m */       ALTGR     (0x32,                 0xE6) /* greek mue */
 /* , */ PUNCT           (0x33, ',', ';'            )
 /* . */ PUNCT           (0x34, '.', ':'            )
 /* / */ PUNCT           (0x35, '-', '_'            )
 /*   */ PUNCT_ALTGR     (0x56, '<', '>',        '|')
	 0
};

/* these keys are generated on a COMBI+character base,
   don't know if that is correct.
   I also don't know what keys to generate, as the
   standard character set (DOS/BIOS) doesn't have
   norwegian/swedish/spanish characters
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {         /* ' a† eÇ i° o¢ u£ Eê #32' */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xA0, 0xB5,
 /* E */ 0x12, 0x82, 0x90,
 /* I */ 0x17, 0xA1, 0xD6,
 /* O */ 0x18, 0xA2, 0xE0,
 /* U */ 0x16, 0xA3, 0xE9,
 /*   */ 0x39, '\'', '\'', /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {         /* ` aÖ eä iç oï uó #32` */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x85, 0xB7,
 /* E */ 0x12, 0x8A, 0xD4,
 /* I */ 0x17, 0x8D, 0xDE,
 /* O */ 0x18, 0x95, 0xE3,
 /* U */ 0x16, 0x97, 0xEB,
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {         /* ^ aÉ eà iå oì uñ #32^ */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x83, 0xB6,
 /* E */ 0x12, 0x88, 0xD2,
 /* I */ 0x17, 0x8C, 0xD7,
 /* O */ 0x18, 0x93, 0xE2,
 /* U */ 0x16, 0x96, 0xEA,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi4table)[] = {         /* ˘ aÑ eâ iã oî uÅ Aé Oô Uö yò #32˘ */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x84, 0x8E,
 /* E */ 0x12, 0x89, 0xD3,
 /* I */ 0x17, 0x8B, 0xD8,
 /* O */ 0x18, 0x94, 0x99,
 /* U */ 0x16, 0x81, 0x9A,
 /* Y */ 0x15, 0x98,    0, /* no Y character ?? */
 /*   */ 0x39,  '˘',  '˘', /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {         /* ˜ CÄ cá ??? */
	/*scancode lower upper*/
 /*   */ 0x39,  ' ',  ' ', /* and additional generated character */
	 0
};

uchar NAME(combi6table)[] = {   
	/*scancode lower upper*/
	 0
};

#endif


struct KeyboardDefinition NAME(Keyboard) = {
	"SP",                                    //char LanguageShort[4];                       // "GR",                    
	"SPANISH - keyboard with combis (by aitor)",//char *Description;                                // created by, "with combis"
	DRIVER_FUNCTION_FULL,                    //char DriverFunctionRequired;                                
	NAME(scancodetable),                     //char *ScancodeTable;                                        
#ifdef COMBI
	{       NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif                  
	0,                                     //char DezimalDingsbums;                                      
	0,                                       //char DefaultLayoutUS;                        // TRUE for russian         
	} ;
