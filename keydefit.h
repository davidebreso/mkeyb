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
�������������������������������������������������������������ͻ
�~29�!02�@03�#04�$05�%06�^07�&08�*09�(0A�)0B�-0C�=0D�Backsp 0E�
�������������������������������������������������������������Ķ
�Tab 0F�q10�w11�e12�r13�t14�y15�u16�i17�o18�p19�[1A�]1B�      �
�������������������������������������������������������� <��� �
� Caps 3A�a1E�s1F�d20�f21�g22�h23�j24�k25�l26�;27�'28�Enter 1C�
�������������������������������������������������������������Ķ
� Shift 2A �z2C�x2D�c2E�v2F�b30�n31�m32�,33�.34�/35� Shift 36 �
�������������������������������������������������������������Ķ
� Ctrl 1D� Alt 38�\56�    Spacebar 39    �\2B�Alt E38�Ctrl E1D�
�������������������������������������������������������������ͼ
*/

/* copied mostly from portugese,
   changed

	  3 2 #34  .  .  .
	  4 3  �   .  .  .
	  5 4  $   .  .  .
	  8 7  /   .  .  .
	  9 8  (   .  .  .
	 10 9  )   .  .  .
	 11 0  =   .  .  .
	 12 '  ?  #31 .  .
	 13 �  ^   .  .  .
	 26 �  �  #27 .  [
	 27 +  *  #29 .  ]
	 39 �  �   .  .  @
	 40 �  �   .  . #35
	 41 \  |  #28 .  .
	 43 � #21  .  .  .
	 53 -  _   .  .  .
	E53 /  /   .  .  .
	 54 /  /   .  .
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT		(0x03, '2', '"'			) /*  3 2 #34  .  . . */
 /* 3 */ PUNCT		(0x04, '3',0x9C			) /*  4 3  �   .  . . */
//* 4 */ PUNCT		(0x05, '4', '$'			) /*  5 4  $   .  . . */
 /* 5 */ ALTGR		(0x06,           	EURO) /*  6              � */
 /* 6 */ PUNCT_CTRL	(0x07, '6', '&',0x1E	) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT		(0x08, '7', '/'			) /*  8 7  /   .  . . */
 /* 8 */ PUNCT		(0x09, '8', '('			) /*  9 8  (   .  . . */
 /* 9 */ PUNCT		(0x0A, '9', ')'			) /* 10 9  )   .  . . */
 /* 0 */ PUNCT		(0x0B, '0', '='			) /* 11 0  =   .  . . */
 /* - */ PUNCT_CTRL	(0x0C,'\'','?',0x1F		) /* 12 '  ?  #31 . . */
 /* = */ PUNCT		(0x0D,0x8D, '^'			) /* 13 �  ^   .  . . */


 /* E */       ALTGR	(0x12,               '�') /* 18              � */
 /* [ */ PUNCT_ALTGR	(0x1A,0x8A,0x82,     '[') /* 26 �  �  #27 .  [ */
 /* ] */ PUNCT_ALTGR	(0x1B, '+', '*',     ']') /* 27 +  *  #29 .  ] */
#ifdef STANDARD
 /* ; */ PUNCT			(0x27,0x95,'@'			) /* 39 �  @  .   .  .  */
 /* ' */ PUNCT			(0x28,0x85,'#'       	) /* 40 � #35 .   .  .  */
 /* ~ */ PUNCT_ALTGR	(0x29,'<', '>',     '\\') /* 41 <  >  .   .  \  */
#else
 /* ; */ PUNCT_ALTGR	(0x27,0x95,0x87,     '@') /* 39 �  �   .  .  @ */
 /* ' */ PUNCT_ALTGR	(0x28,0x85,0xF8,     '#') /* 40 �  �   .  . #35 */
 /* ~ */ PUNCT_CTRL	(0x29, '\\','|',0x1C	) /* 41 \  |  #28 .  . */
 /*   */ PUNCT_CTRL	(0x56, '<', '>',0x1C	) /* 86 <  >   .  .  . */
#endif
 /* \ */ PUNCT		(0x2B,0x97,0x15		) /* 43 � #21  .  .  . */
 /* , */ PUNCT		(0x33, ',', ';'		) /* 51 ,  ;   .  .  . */
 /* . */ PUNCT		(0x34, '.', ':'		) /* 52 .  :   .  .  . */
 /* / */ PUNCT		(0x35, '-', '_'		) /* 53 -  _   .  .  . */

	 0
};

struct KeyboardDefinition NAME(Keyboard) = {
	"IT",                                          //char LanguageShort[4];			// "GR",
#ifdef STANDARD
	"ITALY - tastiera italiana 83/84 tasti (by Davide)",	 //char *Description;				// created by, "with combis"
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
