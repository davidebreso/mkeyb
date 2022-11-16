/* keydefsg.h */

/*
 * history
 * 27 apr 02: tom ehlert - creation
 * 16 nov 22: davide bresolin - review
 */

#define NAME(x) x##_SG


#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "swiss german"
#define STATUS   "first try"

/********************************************************
 * SWISS GERMAN keyboard mappings			*
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

/* copied mostly from swiss french,
   changed

	26C � � #27 . [
	39C � �  .  . .
	40C � �  .  . {
*/

uchar NAME(scancodetable)[] = {   

 //* Y */ REPLACE	 (0x15,0x2C		    ) /* 21C z  Z  #26 . . */
 //* Z */ REPLACE	 (0x2C,0x15		    ) /* 44C y  Y  #25 . . */

 /* Z */ ALPHA_CTRL 	(0x2C, 'y', 'Y', 0x19		)
 /* Y */ ALPHA_CTRL 	(0x15, 'z', 'Z', 0x1A		)



 /* 1 */ PUNCT_ALTGR	 (0x02, '1', '+',	 '|') /*  2 1  +   .  .  | */
 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	 '@') /*  3 2 #34  .  .  @ */
 /* 3 */ PUNCT_ALTGR	 (0x04, '3', '*',	 '#') /*  4 3  *   .  . #35 */
 /* 4 */ PUNCT		 (0x05, '4',0x87	    ) /*  5 4  �   .  .  . */
//* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  .  . */
 /* 6 */ PUNCT_CTRL_ALTGR(0x07, '6', '&',0x1E,	0xAA) /*  7 6  &  #30 .  � */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	0xDD) /*  8 7  /   .  .  � */
 /* 8 */ PUNCT_ALTGR	 (0x09, '8', '(',	0xBD) /*  9 8  (   .  .  � */
 /* 9 */ PUNCT		 (0x0A, '9', ')'	    ) /* 10 9  )   .  .  . */
 /* 0 */ PUNCT		 (0x0B, '0', '='	    ) /* 11 0  =   .  .  . */
 /* - */ PUNCT_ALTGR	 (0x0C,'\'', '?',	0xEF) /* 12 '  ?   .  .  � */
 /* = */ PUNCT_ALTGR	 (0x0D, '^', '`',	 '~') /* 13 ^  `   .  .  ~ */

 /* [ */ ALPHA_ALTGR	 (0x1A,0x81,0x8A,	 '[') /* 26C �  �  #27 . [ */
 /* ] */ PUNCT_CTRL_ALTGR(0x1B,0xF9, '!',0x1D,	 ']') /* 27  � #33 #29 . ] */
 /* ; */ ALPHA		 (0x27,0x94,0x82	    ) /* 39C �  �   .  . . */
 /* ' */ ALPHA_ALTGR	 (0x28,0x84,0x85,	 '{') /* 40C �  �   .  . { */
 /* ~ */ PUNCT		 (0x29,0xF5,0xF8	    ) /* 41  �  �   .  . . */
 /* \ */ PUNCT		 (0x2B, '$',0x9C	    ) /* 43  $  �   .  . } */
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  ,  ;   .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  .  :   .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  -  _  #31 . . */
 /*   */ PUNCT_CTRL_ALTGR(0x56, '<', '>',0x1C,	'\\') /* 86  <  >   .  . \ */

 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
	 0
};

struct KeyboardDefinition NAME(Keyboard) = {
	"SG",                                          //char LanguageShort[4];			// "GR",                    
	"SWISS GERMAN - schweizer deutsches Keyboard, keine combi's (by tom)",  //char *Description;				// created by, "with combis"
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
