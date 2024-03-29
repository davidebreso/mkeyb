/* keydefno.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 */         

#define NAME(x) x##_NO


#include <dos.h>
#include "mkeyb.h"
 

#define LANGUAGE "norvegian"
#define STATUS   "first try"

/********************************************************
 * NORVEGIAN keyboard mappings				*
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

/* copied mostly from daenish,
   changed

	13  \ ` #28 . �
	39C � �  .  . .
	40C � �  .  . .
	41  | �  .  . .
	86  < >  .  . .
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT_ALTGR	 (0x03, '2', '"',	 '@') /*  3 2 #34  .  . @ */
 /* 3 */ PUNCT_ALTGR	 (0x04, '3', '#',	0x9C) /*  4 3 #35  .  . � */
 /* 4 */ PUNCT_ALTGR	 (0x05, '4',0xCF,	 '$') /*  5 4  �   .  . $ */
 /* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  . . */
 /* 6 */ PUNCT_CTRL	 (0x07, '6', '&',0x1E	    ) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT_ALTGR	 (0x08, '7', '/',	 '{') /*  8 7  /   .  . { */
 /* 8 */ PUNCT_CTRL_ALTGR(0x09, '8', '(',0x1B,	 '[') /*  9 8  (  #27 . [ */
 /* 9 */ PUNCT_CTRL_ALTGR(0x0A, '9', ')',0x1D,	 ']') /* 10 9  )  #29 . ] */
 /* 0 */ PUNCT_ALTGR	 (0x0B, '0', '=',	 '}') /* 11 0  =   .  . } */
 /* - */ PUNCT		 (0x0C, '+', '?'	    ) /* 12 +  ?   .  . . */
 /* = */ PUNCT_CTRL_ALTGR(0x0D,'\\', '`',0x1C,	0xEF) /* 13 \  `  #28 . � */

 /* [ */ ALPHA		 (0x1A,0x86,0x8F	    ) /* 26C � �  .  . . */
 /* ] */ PUNCT_ALTGR	 (0x1B,0xF9, '^',	 '~') /* 27  � ^  .  . ~ */
 /* ; */ ALPHA		 (0x27,0x9B,0x9D	    ) /* 39C � �  .  . . */
 /* ' */ ALPHA		 (0x28,0x91,0x92	    ) /* 40C � �  .  . . */
 /* ~ */ PUNCT		 (0x29, '|',0xF5	    ) /* 41  | �  .  . . */
 /* \ */ PUNCT		 (0x2B,'\'', '*'	    ) /* 43  ' *  .  . . */
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  , ;  .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  . :  .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  - _  .  . . */
 /*   */ PUNCT		 (0x56, '<', '>'	    ) /* 86  < >  .  . . */ 
 
 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
 
	 0
};


struct KeyboardDefinition NAME(Keyboard) = {
	"NO",                                          //char LanguageShort[4];			// "GR",                    
	"NORVEGIAN - norske keyboard (by tom)",  //char *Description;				// created by, "with combis"
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
