/* keydefuk.h */

/*
 * history
 * 20 apr 02: tom ehlert - creation
 * 25 apr 02: bart oldeman - adjustment to british
 */

#define NAME(x) x##_UK


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "english"
#define STATUS   "by Bart"

/********************************************************
 * BRITISH keyboard mappings                            *
 ********************************************************/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT_ALTGR    (0x03, '2', '"',     '@')
 /* 3 */ PUNCT_ALTGR    (0x04, '3', 0x9c,     0xFF) /* '£' */
 /* 4 */       ALTGR    (0x05,              EURO) /* */
 /* 7 */       ALTGR    (0x08,               '{')
 /* 8 */       ALTGR    (0x09,               '[')
 /* 9 */       ALTGR    (0x0A,               ']')
 /* 0 */       ALTGR    (0x0B,               '}')

 /* - */       ALTGR    (0x0C,               '\\')
 /* ] */       ALTGR    (0x1B,               '~')
 /*   */ PUNCT          (0x28,0x27, '@') /* APOSTROPHE AT */
 
 /* ` */ PUNCT_ALTGR    (0x29, '`',0xAA,     0xB3) /* ª, ³ */
 /* \ */ PUNCT          (0x2B, '#', '~'         )
 /*   */ PUNCT_ALTGR    (0x56,'\\', '|',     '|')
         0
};

struct KeyboardDefinition NAME(Keyboard) = {
        "UK",                                          //char LanguageShort[4];                 // "GR",
        "UNITED KINGDOM - british keyboard, no combi's (by Bart)",  //char *Description;                              // created by, "with combis"
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
