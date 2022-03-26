/* keydefpl.h */

/*
 * history
 * 13 may 02: tom ehlert - creation
 */

#define NAME(x) x##_PL


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "polish"
#define STATUS   "should be OK"

/********************************************************
 * POLISH keyboard mappings				*

   FROM XKEYB key definition

	---- This file is to be viewed with CP852 active ----
	
	Polish keyboard layout for codepage 852 (DOS Latin II) on standard
	US keyboards (which are the most common in Poland).
	This layout tries to mimic Win9x "PL" layout from KEYBRD4.SYS
	(so called "programmer's" keyboard), not that idiotic one from
	KEYBRD2.SYS ("typist's")

   I (tom) tried to map the AltGr+Shift things.	
 ********************************************************/

uchar NAME(scancodetable)[] =	{

 /* e */ ALTGRSHIFT(0x12, 0xA9, 0xA8) /* 18C e E  #5 . © */
 /* o */ ALTGRSHIFT(0x18, 0xA2, 0xE0) /* 24C o O #15 . ¢ */
 /* a */ ALTGRSHIFT(0x1E, 0xA5, 0xA4) /* 30C a A  #1 . • */
 /* s */ ALTGRSHIFT(0x1F, 0x98, 0x97) /* 31C s S #19 . ò */
 /* l */ ALTGRSHIFT(0x26, 0x88, 0x9D) /* 38C l L #12 . à */
 /* z */ ALTGRSHIFT(0x2C, 0xBE, 0xBD) /* 44C z Z #26 . æ */
 /* x */ ALTGRSHIFT(0x2D, 0xAB, 0x8D) /* 45C x X #24 . ´ */
 /* c */ ALTGRSHIFT(0x2E, 0x86, 0x8F) /* 46C c C  #3 . Ü */
 /* n */ ALTGRSHIFT(0x31, 0xE4, 0xE3) /* 49C n N #14 . ‰ */    
 
 /* U */ ALTGR           (0x16, EURO)          // Added by Tom
 /* 5 */ ALTGR           (0x06, EURO)          // Added by Tom


//[COMBI]
//~ a• cÜ e© là n‰ o¢ sò x´ zæ A§ Cè E® Lù N„ O‡ Só Xç ZΩ #32~
	 0
};
struct KeyboardDefinition NAME(Keyboard) = {
	"PL",                                          //char LanguageShort[4];			// "GR",                    
	"POLISH - polska klawiatura (by tom, verified by michael)",  //char *Description;				// created by, "with combis"
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
