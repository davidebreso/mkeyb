/* keydefux.h */

/*
 * history
 * 27 mar 02: Davide Bresolin - creation
 */

#define NAME(x) x##_UX


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "us-international"
#define STATUS   "by DB"

#define COMBI

/********************************************************
 * US INTERNATIONAL keyboard mappings                   *
 ********************************************************/

uchar NAME(scancodetable)[] = {

 /* 5 */       ALTGR    (0x06,              EURO) /* 05  5 % */
#ifdef COMBI
 /* 6 */ PUNCT    	(0x07,  '6' ,COMBI3     ) /* 07  6 ^ */
 /* ' */ PUNCT    	(0x28,COMBI1,COMBI4     ) /* 40  ' " */
 /* ` */ PUNCT    	(0x29,COMBI2,COMBI5     ) /* 41  ` ~ */
#endif
	 0
};

/*
   These keys are generated on a COMBI+character base.
   Some of them are correct only for codepage 850, since
   the standard 437 codepage doesn't have all accented characters
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

uchar NAME(combi4table)[] = {         /* " aÑ eâ iã oî uÅ Aé Oô Uö yò #32" */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x84, 0x8E,
 /* E */ 0x12, 0x89, 0xD3,
 /* I */ 0x17, 0x8B, 0xD8,
 /* O */ 0x18, 0x94, 0x99,
 /* U */ 0x16, 0x81, 0x9A,
 /* Y */ 0x15, 0x98,    0, /* no Y character ?? */
 /*   */ 0x39,  '"',  '"', /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {        /* ~ n§ N• #32~
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
	"UX",                                         //char LanguageShort[4];                 // "GR",
	"US INTERNATIONAL - with combis, Ctrl+Alt+F2 to switch (by DB)",    //char *Description;                              // created by, "with combis"
	DRIVER_FUNCTION_FULL,                       //char DriverFunctionRequired;
	NAME(scancodetable),                          //char *ScancodeTable;
#ifdef COMBI
	{       NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif
	0,                            		//char DezimalDingsbums;
	1,                           		//char DefaultLayoutUS;                  // TRUE for russian
	} ;
