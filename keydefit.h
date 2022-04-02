/* keydefit.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 * 27 mar 22: davide bresolin - correct name
 *  2 apr 22: davide bresolin - 83 keys layout
 */

#ifdef STANDARD
	#define NAME(x) x##_ITstd
#else
	#define NAME(x) x##_IT
#endif

#include <dos.h>
#include "mkeyb.h"

/********************************************************
 * ITALIAN keyboard mappings				*
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

/* copied mostly from portugese,
   changed

	  3 2 #34  .  .  .
	  4 3  œ   .  .  .
	  5 4  $   .  .  .
	  8 7  /   .  .  .
	  9 8  (   .  .  .
	 10 9  )   .  .  .
	 11 0  =   .  .  .
	 12 '  ?  #31 .  .
	 13   ^   .  .  .
	 26 Š  ‚  #27 .  [
	 27 +  *  #29 .  ]
	 39 •  ‡   .  .  @
	 40 …  ø   .  . #35
	 41 \  |  #28 .  .
	 43 — #21  .  .  .
	 53 -  _   .  .  .
	E53 /  /   .  .  .
	 54 /  /   .  .
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT		(0x03, '2', '"'			) /*  3 2 #34  .  . . */
 /* 3 */ PUNCT		(0x04, '3',0x9C			) /*  4 3  œ   .  . . */
//* 4 */ PUNCT		(0x05, '4', '$'			) /*  5 4  $   .  . . */
 /* 5 */ ALTGR		(0x06,           	EURO) /*  6              Õ */
 /* 6 */ PUNCT_CTRL	(0x07, '6', '&',0x1E	) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT		(0x08, '7', '/'			) /*  8 7  /   .  . . */
 /* 8 */ PUNCT		(0x09, '8', '('			) /*  9 8  (   .  . . */
 /* 9 */ PUNCT		(0x0A, '9', ')'			) /* 10 9  )   .  . . */
 /* 0 */ PUNCT		(0x0B, '0', '='			) /* 11 0  =   .  . . */
 /* - */ PUNCT_CTRL	(0x0C,'\'','?',0x1F		) /* 12 '  ?  #31 . . */
 /* = */ PUNCT		(0x0D,0x8D, '^'			) /* 13   ^   .  . . */


 /* E */       ALTGR	(0x12,               'Õ') /* 18              Õ */
 /* [ */ PUNCT_ALTGR	(0x1A,0x8A,0x82,     '[') /* 26 Š  ‚  #27 .  [ */
 /* ] */ PUNCT_ALTGR	(0x1B, '+', '*',     ']') /* 27 +  *  #29 .  ] */
#ifdef STANDARD
 /* ; */ PUNCT			(0x27,0x95,'@'			) /* 39 •  @  .   .  .  */
 /* ' */ PUNCT			(0x28,0x85,'#'       	) /* 40 … #35 .   .  .  */
 /* ~ */ PUNCT_ALTGR	(0x29,'<', '>',     '\\') /* 41 <  >  .   .  \  */
#else
 /* ; */ PUNCT_ALTGR	(0x27,0x95,0x87,     '@') /* 39 •  ‡   .  .  @ */
 /* ' */ PUNCT_ALTGR	(0x28,0x85,0xF8,     '#') /* 40 …  ø   .  . #35 */
 /* ~ */ PUNCT_CTRL	(0x29, '\\','|',0x1C	) /* 41 \  |  #28 .  . */
 /*   */ PUNCT_CTRL	(0x56, '<', '>',0x1C	) /* 86 <  >   .  .  . */
#endif
 /* \ */ PUNCT		(0x2B,0x97,0x15		) /* 43 — #21  .  .  . */
 /* , */ PUNCT		(0x33, ',', ';'		) /* 51 ,  ;   .  .  . */
 /* . */ PUNCT		(0x34, '.', ':'		) /* 52 .  :   .  .  . */
 /* / */ PUNCT		(0x35, '-', '_'		) /* 53 -  _   .  .  . */

	 0
};

struct KeyboardDefinition NAME(Keyboard) = {
	"IT",                                          //char LanguageShort[4];			// "GR",
#ifdef STANDARD
	"ITALY - tastiera italiana 83/84 tasti (by DB)",	 //char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_STANDARD,                      //char DriverFunctionRequired;
#else
	"ITALY - tastiera italiana (by tom)",          //char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_NORMAL,                        //char DriverFunctionRequired;
#endif
	NAME(scancodetable),                           //char *ScancodeTable;
#ifdef COMBI
	{	NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif			
	0,                                             //char DezimalDingsbums;                                        
	0,                                             //char DefaultLayoutUS;			// TRUE for russian             
	} ;
