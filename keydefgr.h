/* keydefgr.h */



/*
 * history
 * 20 apr 02: tom ehlert - creation
 */


#ifdef COMBI
	#define NAME(x) x##_GR2
#else	
	#define NAME(x) x##_GR
#endif	


#include <dos.h>
#include "mkeyb.h"



/********************************************************
 * GERMAN keyboard mappings				*
 ********************************************************/

uchar NAME(scancodetable)[] = {

// /* Z */ REPLACE	(0x2C, 0x15		)
// /* Y */ REPLACE	(0x15, 0x2C		)

 /* Z */ PUNCT_ALTGR	(0x2C, 'y', 'Y', 0x19		)
 /* Y */ PUNCT_ALTGR	(0x15, 'z', 'Z', 0x1A		)

 /* 1 */ PUNCT		(0x02, '1', '!'		)
 /* 2 */ PUNCT		(0x03, '2', '"'		)
 /* 3 */ PUNCT		(0x04, '3',0x15		)
//* 4 */ PUNCT		(0x05, '4', '$',0xFF	)
 /* 5 */ ALTGR		(0x06,EURO		)
 /* 6 */ PUNCT		(0x07, '6', '&'		)
 /* 7 */ PUNCT_ALTGR	(0x08, '7', '/', '{'	)
 /* 8 */ PUNCT_ALTGR	(0x09, '8', '(', '['	)
 /* 9 */ PUNCT_ALTGR	(0x0A, '9', ')', ']'	)
 /* 0 */ PUNCT_ALTGR	(0x0B, '0', '=', '}'	)

 /* - */ PUNCT_ALTGR	(0x0C,0xE1, '?','\\'	) /* szet */
#ifdef COMBI
 /* = */ PUNCT		(0x0D,COMBI1,COMBI2	) /* COMBI ' and ` + aeiou */
#else
 /* = */ PUNCT		(0x0D,'\'', '`'		) /* PUNCT_CTRL '+` */
#endif
 /* Q */ ALTGR		(0x10, '@'		)
 /* [ */ ALPHA		(0x1A,0x81,0x9a		) /* ue */
 /* ] */ PUNCT_ALTGR	(0x1B, '+', '*', '~'	)
 /* ; */ ALPHA		(0x27,0x94,0x99		) /* german umlauts oe */
 /* ' */ ALPHA		(0x28,0x84,0x8E		) /* ae */
#ifdef COMBI
 /* ` */ PUNCT		(0x29,COMBI3,0xF8	) /* COMBI ^ + aeiou */
#else
 /* ` */ PUNCT		(0x29, '^',0xF8		) /* ^ */
#endif
 /* \ */ PUNCT		(0x2B, '#','\''		)
 /* M */ ALTGR		(0x32,0xE6		) /* greek mue */
 /* , */ PUNCT		(0x33, ',', ';'		)
 /* . */ PUNCT		(0x34, '.', ':'		)
 /* / */ PUNCT		(0x35, '-', '_'		)
 /*   */ PUNCT_ALTGR	(0x56, '<', '>', '|'	)       
 
 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
 
	 0
};

// character to be send, if NUMLOCK + '.' on numeric keypad
#define DECIMALDINGSBUMS ','

/* these keys are generated on a COMBI+character base,
   the upper case accented characters '`^+AEIOU need an enhanced
   codepage (850), as they can't be displayed in standard BIOS
   codepage (437)
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {		/* ' a† eÇ i° o¢ u£ Eê #32' */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xA0, 0xB5,
 /* E */ 0x12, 0x82, 0x90,
 /* I */ 0x17, 0xA1, 0xD6,
 /* O */ 0x18, 0xA2, 0xE0,
 /* U */ 0x16, 0xA3, 0xE9,
 /*   */ 0x39, '\'', '\'', /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {		/* ` aÖ eä iç oï uó #32` */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x85, 0xB7,
 /* E */ 0x12, 0x8A, 0xD4,
 /* I */ 0x17, 0x8D, 0xDE,
 /* O */ 0x18, 0x95, 0xE3,
 /* U */ 0x16, 0x97, 0xEB,
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {		/* ^ aÉ eà iå oì uñ #32^ */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x83, 0xB6,
 /* E */ 0x12, 0x88, 0xD2,
 /* I */ 0x17, 0x8C, 0xD7,
 /* O */ 0x18, 0x93, 0xE2,
 /* U */ 0x16, 0x96, 0xEA,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi4table)[] = {		/* something missing yet ?? */
	/*scancode lower upper*/
	 0
};

uchar NAME(combi5table)[] = {		/* something missing yet ?? */
	/*scancode lower upper*/
	 0
};
uchar NAME(combi6table)[] = {		/* something missing yet ?? */
	/*scancode lower upper*/
	 0
};

#endif


#ifndef COMBI
struct KeyboardDefinition NAME(Keyboard) = {
	"GR",                                          //char LanguageShort[4];			// "GR",                    
	"GERMAN - deutsche Tastatur (by tom)",  //char *Description;				// created by, "with combis"
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
#else
	struct KeyboardDefinition NAME(Keyboard) = {
		"GR2",                                      //char LanguageShort[4];			// "GR",                    
		"GERMAN2 - deutsche Tastatur mit internatinalen Umlauten (by tom)", //char *Description;				// created by, "with combis"
		DRIVER_FUNCTION_FULL,                       //char DriverFunctionRequired;                                  
		NAME(scancodetable),                        //char *ScancodeTable;                                          
#ifdef COMBI
	{	NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif			
		',',                                        //char DezimalDingsbums;                                        
		0,                                          //char DefaultLayoutUS;			// TRUE for russian             
		};
#endif

