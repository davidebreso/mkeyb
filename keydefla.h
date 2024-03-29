/* keydefla.h */

/*
 * history
 * 26 apr 02: tom ehlert - creation
 */

#define NAME(x) x##_LA


#include <dos.h>
#include "mkeyb.h"

// latin america needs combi's
#define COMBI

/********************************************************
 * LATIN AMERICAN keyboard mappings			*
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

/* copied mostly from italy,
   changed

	 4  3 #35  . . .
	12  '  ?  #31 . \
	13  �  �   . . .
	16C q  Q  #17 . @
	26  '  �  #27 . .
	27  +  *  #29 . ~
	39C �  �   . . .
	40  {  [   . . ^
	41  |  �   . . �
	43  }  ]  #28 . `

	[Combi]
	' a� e� i� o� u� E� #32'
	` a� e� i� o� u� #32`
	^ a� e� i� o� u� #32^
	� a� e� i� o� u� A� O� U� y� #32�
	~ n� N� #32~
	� C� c�
*/

uchar NAME(scancodetable)[] = {

 /* 2 */ PUNCT		 (0x03, '2', '"'	    ) /*  3 2 #34  .  . . */
//* 3 */ PUNCT		 (0x04, '3', '#'	    ) /*  4 3 #35  .  . . */
//* 4 */ PUNCT		 (0x05, '4', '$'	    ) /*  5 4  $   .  . . */
//* 5 */ PUNCT		 (0x06, '5', '%'	    ) /*  6 5  %   .  . . */
 /* 6 */ PUNCT_CTRL	 (0x07, '6', '&',0x1E	    ) /*  7 6  &  #30 . . */
 /* 7 */ PUNCT		 (0x08, '7', '/'	    ) /*  8 7  /   .  . . */
 /* 8 */ PUNCT		 (0x09, '8', '('	    ) /*  9 8  (   .  . . */
 /* 9 */ PUNCT		 (0x0A, '9', ')'	    ) /* 10 9  )   .  . . */
 /* 0 */ PUNCT		 (0x0B, '0', '='	    ) /* 11 0  =   .  . . */
#ifdef COMBI
 /* - */ PUNCT_ALTGR	 (0x0C,COMBI6,'?',	'\\') /* 12 '  ?  #31 . \ */
#else
 /* - */ PUNCT_ALTGR	 (0x0C,'\'', '?',	'\\') /* 12 '  ?  #31 . \ */
#endif
 /* = */ PUNCT		 (0x0D,0xA8,0xAD	    ) /* 13 �  �   .  . . */

 /* q */       ALTGR	 (0x10,			 '@') /* 16C q Q #17 . @ */
#ifdef COMBI
 /* [ */ PUNCT		 (0x1A,COMBI1,COMBI4	    ) /* 26  ' � #27 . . */
 /* ] */ PUNCT_ALTGR	 (0x1B, '+', '*',     COMBI5) /* 27  + * #29 . ~ */
#else
 /* [ */ PUNCT		 (0x1A,'\'',0xF9	    ) /* 26  ' � #27 . . */
 /* ] */ PUNCT_ALTGR	 (0x1B, '+', '*',	 '~') /* 27  + * #29 . ~ */
#endif
 /* ; */ ALPHA		 (0x27,0xA4,0xA5	    ) /* 39C � �  .  . . */
#ifdef COMBI
 /* ' */ PUNCT_ALTGR	 (0x28, '{', '[',     COMBI3) /* 40  { [  .  . ^ */
#else
 /* ' */ PUNCT_ALTGR	 (0x28, '{', '[',	 '^') /* 40  { [  .  . ^ */
#endif
 /* ~ */ PUNCT_ALTGR	 (0x29, '|',0xF8,	0xAA) /* 41  | �  .  . � */
#ifdef COMBI
 /* \ */ PUNCT_CTRL_ALTGR(0x2B, '}', ']',0x1C,COMBI2)/* 43 } ] #28 . ` */
#else
 /* \ */ PUNCT_CTRL_ALTGR(0x2B, '}', ']',0x1C,	 '`') /* 43  } ] #28 . ` */
#endif
 /* , */ PUNCT		 (0x33, ',', ';'	    ) /* 51  , ;  .  . . */
 /* . */ PUNCT		 (0x34, '.', ':'	    ) /* 52  . :  .  . . */
 /* / */ PUNCT		 (0x35, '-', '_'	    ) /* 53  - _  .  . . */
 /*   */ PUNCT		 (0x56, '<', '>'	    ) /* 86  < >  .  . . */

 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81
 /* 5 */ ALTGR           (0x06, EURO)          // Added by Tom
	 0
};

/* these keys are generated on a COMBI+character base,
   the upper case accented characters '`^+AEIOU need an enhanced
   codepage (850), as they can't be displayed in standard BIOS
   codepage (437)
*/

/* [Combi]
   ' a� e� i� o� u� E� #32'
   ` a� e� i� o� u� #32`
   ^ a� e� i� o� u� #32^
   � a� e� i� o� u� A� O� U� y� #32�
   ~ n� N� #32~
   � C� c�
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {		/* ' a� e� i� o� u� E� #32' */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xA0, '�', // �
 /* E */ 0x12, 0x82, '�',
 /* I */ 0x17, 0xA1, '�',
 /* O */ 0x18, 0xA2, '�',    
 /* U */ 0x16, 0xA3, '�',    // 00a3 '�'
 /*   */ 0x39, '\'', '\'', /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {		/* ` a� e� i� o� u� #32` */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x85, '�',
 /* E */ 0x12, 0x8A, '�',
 /* I */ 0x17, 0x8D, '�',
 /* O */ 0x18, 0x95, '�',
 /* U */ 0x16, 0x97, '�',
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {		/* ^ a� e� i� o� u� #32^ */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x83, 0xB6,
 /* E */ 0x12, 0x88, 0xD2,
 /* I */ 0x17, 0x8C, 0xD7,
 /* O */ 0x18, 0x93, 0xE2,
 /* U */ 0x16, 0x96, 0xEA,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi4table)[] = {		/* � a� e� i� o� u� A� O� U� y� #32� */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x84, '�', // � 
 /* E */ 0x12, 0x89, '�', 
 /* I */ 0x17, 0x8B, '�', 
 /* O */ 0x18, 0x94, '�',
 /* U */ 0x16, 0x81, '�',
 /* Y */ 0x15, 0x98, 0x98, 
 /*   */ 0x39,  '�',  '�', /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {		/* ~ n� N� #32~ */
	/*scancode lower upper*/
 /* N */ 0x16, 0xA4, 0xA5,
 /*   */ 0x39,  '~',  '~', /* and additional generated character */
	 0
};
uchar NAME(combi6table)[] = {		/* something missing yet ?? */
	/*scancode lower upper*/
//   ' a� e� i� o� u� E� #32'
	
 /* A */ 0x1E, 0x85, 0x85, /* � */
 /* E */ 0x12, 0x90, 0x90, 
 /* I */ 0x17, 0x8d, 0x8d, /* � */
 /* O */ 0x18, 0x95, 0x95, /* � */
 /* U */ 0x16, 0x97, 0x97,
 /*   */ 0x39,  '\'',  '\'', /* and additional generated character */
	 0
};

#endif

struct KeyboardDefinition NAME(Keyboard) = {
	"LA",                                          //char LanguageShort[4];			// "GR",                    
	"Latin American - keyboardo espanolo latino americano (by tom)",  //char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_FULL,                          //char DriverFunctionRequired;                                  
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
