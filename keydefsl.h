/* keydefsl.h 
this keyboard is modeled after the layout given by
	http://www.microsoft.com/globaldev/keyboards/kbdslove.htm
*/
/* country=386, code page=852, language=386, keyboard=sl */

/*
 * history
 * 29 sep 03: tom ehlert - creation
 * 28 nov 18: fritz corrected this layout for CP852
 * 16 nov 22: davide bresolin - review
 *
 */

#define NAME(x) x##_SL


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "slovenian"
#define STATUS   "by tom and fritz"

/********************************************************
 * SLOVENIAN keyboard mappings                          *
 ********************************************************/

uchar NAME(scancodetable)[] = {

 //* Y */ REPLACE	 (0x15,0x2C		    ) /* 21C z  Z  #26 . . */
 //* Z */ REPLACE	 (0x2C,0x15		    ) /* 44C y  Y  #25 . . */

 /* Z */ ALPHA_CTRL 	(0x2C, 'y', 'Y', 0x19		)
 /* Y */ ALPHA_CTRL 	(0x15, 'z', 'Z', 0x1A		)



 /* 1 */       ALTGR    (0x02,               '~')
 /* 2 */ PUNCT_ALTGR    (0x03, '2', '"',     0)  // wrong altgrey
 /* 3 */       ALTGR    (0x04,               '^')
 /* 4 */       ALTGR    (0x05,               0)
 /* 5 */       ALTGR    (0x06,               0)
 /* 6 */ PUNCT_ALTGR    (0x07, '6', '&',     0)
 /* 7 */ PUNCT_ALTGR    (0x08, '7', '/',     '`')
 /* 8 */ PUNCT_ALTGR    (0x09, '8', '(',     0)
 /* 9 */ PUNCT_ALTGR    (0x0a, '9', ')',     0)
 /* 0 */ PUNCT_ALTGR    (0x0b, '0', '=',     0)
 /* - */ PUNCT_ALTGR    (0x0c, 39,'?',     0)
 /* = */ PUNCT_ALTGR    (0x0d, '+', '*',     0)


 /* q */       ALTGR    (0x10,               '\\')
 /* w */       ALTGR    (0x11,               '|')

 /* [ */ ALPHA_ALTGR    (0x1a, 'Á','Ê',      'ˆ') 
 /* ] */ ALPHA_ALTGR    (0x1b, '–','—',      'û') 
 
 /* f */       ALTGR    (0x21,               '[')
 /* g */       ALTGR    (0x22,               ']')

 /* k */       ALTGR    (0x25,              'à')
 /* l */       ALTGR    (0x26,              'ù')
 /* ; */ ALPHA_ALTGR    (0x27, 'ü','¨',     0)
 /* ' */ ALPHA_ALTGR    (0x28, 'Ü','è',     '·')
 /*   */ ALPHA_ALTGR    (0x2b, 'ß','¶',     '')


 /* v */       ALTGR    (0x2f,               '@')
 /* b */       ALTGR    (0x30,               '{')
 /* n */       ALTGR    (0x31,               '}')
 /* m */       ALTGR    (0x32,               'ı')

 /* , */ PUNCT_ALTGR    (0x33,',',';',       '<')
 /* . */ PUNCT_ALTGR    (0x34,'.',':',       '>')
 /* , */ PUNCT          (0x35,'-','_'           )

 /*   */ PUNCT      	(0x56, '<', '>'     	)   
 
 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
 
         0
};

struct KeyboardDefinition NAME(Keyboard) = {
        "SL",                                          //char LanguageShort[4];                 // "GR",
        "SLOVENIAN keyboard, no combi's (by tom and fritz)",     //char *Description;                              // created by, "with combis"
        DRIVER_FUNCTION_NORMAL,                        //char DriverFunctionRequired;
        NAME(scancodetable),                           //char *ScancodeTable;
#ifdef COMBI
        {       NAME(combi1table),NAME(combi2table),NAME(combi3table),
                NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
        { 0 },
#endif                  
        ',',                                           //char DezimalDingsbums;
        0,                                             //char DefaultLayoutUS;                  // TRUE for russian
        } ;
