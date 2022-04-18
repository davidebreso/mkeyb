/* keydeftr.h */

/*
 * history
 * 17 apr 22: davide bresolin - creation
 */

#define NAME(x) x##_TR

#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "turkish-q"
#define STATUS   "untested, by Davide"

#define COMBI

/********************************************************
 * TURKISH Q keyboard mappings				*
 ********************************************************/

/* keyboard image (by arkady)

Standard layout characters+scancodes:
имммямммямммямммямммямммямммямммямммямммямммямммямммяммммммммм╩
╨~29Ё!02Ё@03Ё#04Ё$05Ё%06Ё^07Ё&08Ё*09Ё(0AЁ)0BЁ-0CЁ=0DЁBacksp 0E╨
гдддаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбаддбдддддд╤
╨Tab 0FЁq10Ёw11Ёe12Ёr13Ёt14Ёy15Ёu16Ёi17Ёo18Ёp19Ё[1AЁ]1BЁ      ╨
гддддддадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадбды <дды ╨
╨ Caps 3AЁa1EЁs1FЁd20Ёf21Ёg22Ёh23Ёj24Ёk25Ёl26Ё;27Ё'28ЁEnter 1C╨
гддддддддадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадбдадддддддд╤
╨ Shift 2A Ёz2CЁx2DЁc2EЁv2FЁb30Ёn31Ёm32Ё,33Ё.34Ё/35Ё Shift 36 ╨
гддддддддбдадддадбдадбдадддадддадддадддадбдадбдадддадбдддддддд╤
╨ Ctrl 1DЁ Alt 38Ё\56Ё    Spacebar 39    Ё\2BЁAlt E38ЁCtrl E1D╨
хммммммммомммммммомммомммммммммммммммммммомммомммммммомммммммм╪
*/

/* Created from the Turkish Q Layout at http://kbdlayout.info/kbdtuq
   Codepage: 857
   
Changes from US layout. An extra '@' at the end is a COMBI key

Code	US	Norm	Shift	AltGr	AltGr+Shift
----------------------------------------------------------------
02	1	1	!	>		// DIGIT ONE, EXCLAMATION MARK, GREATER-THAN SIGN
03	2	2	'	0x9C		// DIGIT TWO, APOSTROPHE, POUND SIGN
04	3	3	^@	#		// DIGIT THREE, CIRCUMFLEX ACCENT, NUMBER SIGN
05	4	4	+	$		// DIGIT FOUR, PLUS SIGN, DOLLAR SIGN
06	5	5	%	0xAB		// DIGIT FIVE, PERCENT SIGN, VULGAR FRACTION ONE HALF
07	6	6	&			// DIGIT SIX, AMPERSAND
08	7	7	/	{		// DIGIT SEVEN, SOLIDUS, LEFT CURLY BRACKET
09	8	8	(	[		// DIGIT EIGHT, LEFT PARENTHESIS, LEFT SQUARE BRACKET
0a	9	9	)	]		// DIGIT NINE, RIGHT PARENTHESIS, RIGHT SQUARE BRACKET
0b	0	0	=	}		// DIGIT ZERO, EQUALS SIGN, RIGHT CURLY BRACKET
0c	-	*	?	\		// ASTERISK, QUESTION MARK, REVERSE SOLIDUS
0d	=	-	_	|		// HYPHEN-MINUS, LOW LINE, VERTICAL LINE
10	Q	q	Q	@		// LATIN SMALL LETTER Q, LATIN CAPITAL LETTER Q, COMMERCIAL AT
12	E	e	E	0xD5		// LATIN SMALL LETTER E, LATIN CAPITAL LETTER E, EURO SIGN
17	I	0x8D	I			// LATIN SMALL LETTER DOTLESS I, LATIN CAPITAL LETTER I
1a	[	0xA7	0xA8	0xF9@		// LATIN SMALL LETTER G WITH BREVE, LATIN CAPITAL LETTER G WITH BREVE, DIAERESIS
1b	]	0x81	0x9A	~@		// LATIN SMALL LETTER U WITH DIAERESIS, LATIN CAPITAL LETTER U WITH DIAERESIS, TILDE
1f	S	s	S	0xE1		// LATIN SMALL LETTER S, LATIN CAPITAL LETTER S, LATIN SMALL LETTER SHARP S
27	;	0x9F	0x9E	0xEF@		// LATIN SMALL LETTER S WITH CEDILLA, LATIN CAPITAL LETTER S WITH CEDILLA, ACUTE ACCENT
28	'	i	0x98			// LATIN SMALL LETTER I, LATIN CAPITAL LETTER I WITH DOT ABOVE
29	`	"	0x82	<		// QUOTATION MARK, LATIN SMALL LETTER E WITH ACUTE, LESS-THAN SIGN
2b	        ,	;	`@		// COMMA, SEMICOLON, GRAVE ACCENT
33	,	0x94	0x99			// LATIN SMALL LETTER O WITH DIAERESIS, LATIN CAPITAL LETTER O WITH DIAERESIS
34	.	0x87	0x80			// LATIN SMALL LETTER C WITH CEDILLA, LATIN CAPITAL LETTER C WITH CEDILLA
35	/	.	:			// FULL STOP, COLON
56	\	<	>	|		// LESS-THAN SIGN, GREATER-THAN SIGN, VERTICAL LINE

*/

uchar NAME(scancodetable)[] = {

 /* ` */ PUNCT_ALTGR	(0x29, '"',  0x82,      '<'   )
 /* 1 */ PUNCT_ALTGR	(0x02, '1',  '!',       '>'   )
 /* 2 */ PUNCT_ALTGR	(0x03, '2',  '\'',      0x9C  )
#ifdef COMBI
 /* 3 */ PUNCT_ALTGR	(0x04, '3',  COMBI1,    '#'   )
#else
 /* 3 */ PUNCT_ALTGR	(0x04, '3',  '^',       '#'   )
#endif
 /* 4 */ PUNCT_ALTGR	(0x05, '4',  '+',       '$'   )
 /* 5 */ PUNCT_ALTGR	(0x06, '5',  '%',       0xAB  )
 /* 6 */ PUNCT		(0x07, '6',  '&'              )
 /* 7 */ PUNCT_ALTGR	(0x08, '7',  '/',       '{'   )
 /* 8 */ PUNCT_ALTGR	(0x09, '8',  '(',       '['   )
 /* 9 */ PUNCT_ALTGR	(0x0a, '9',  ')',       ']'   )
 /* 0 */ PUNCT_ALTGR	(0x0b, '0',  '=',       '}'   )
 /* - */ PUNCT_ALTGR	(0x0c, '*',  '?',       '\\'  )
 /* = */ PUNCT_ALTGR	(0x0d, '-',  '_',       '|'   )

 /* Q */ ALPHA_ALTGR	(0x10, 'q',  'Q',       '@'   )
 /* E */ ALPHA_ALTGR	(0x12, 'e',  'E',       0xD5  )
 /* I */ ALPHA		(0x17, 0x8D, 'I'              )
#ifdef COMBI
 /* [ */ ALPHA_ALTGR	(0x1a, 0xA7, 0xA6,      COMBI2)
 /* ] */ ALPHA_ALTGR	(0x1b, 0x81, 0x9A,      COMBI3)
#else
 /* [ */ ALPHA_ALTGR	(0x1a, 0xA7, 0xA6,      0xF9  )
 /* ] */ ALPHA_ALTGR	(0x1b, 0x81, 0x9A,      '~'   )
#endif

 /* S */ ALPHA_ALTGR	(0x1f, 's',  'S',       0xE1  )
#ifdef COMBI
 /* ; */ ALPHA_ALTGR	(0x27, 0x9F, 0x9E,      COMBI4)
 /*   */ PUNCT_ALTGR	(0x2b, ',',  ';',       COMBI5)
#else
 /* ; */ ALPHA_ALTGR	(0x27, 0x9F, 0x9E,      0xEF  )
 /*   */ PUNCT_ALTGR	(0x2b, ',',  ';',       '`'   )
#endif
 /* ' */ ALPHA		(0x28, 'i',  0x98             )

 /* , */ ALPHA		(0x33, 0x94, 0x99             )
 /* . */ ALPHA		(0x34, 0x87, 0x80             )
 /* / */ PUNCT		(0x35, '.',  ':'              )
 /* \ */ PUNCT_ALTGR	(0x56, '<',  '>',      '|'    )

	 0
};

/*
   These keys are generated on a COMBI+character base.
   Some of them are correct only for codepage 857, since
   the standard 437 codepage doesn't have all accented characters
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {         /* CIRCUMFLEX ACCENT */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x83, 0xB6,
 /* E */ 0x12, 0x88, 0xD2,
 /* I */ 0x17, 0x8C, 0xD7,
 /* i */ 0x28, 0x8C, 0xD7,
 /* O */ 0x18, 0x93, 0xE2,
 /* U */ 0x16, 0x96, 0xEA,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {         /* DIAERESIS */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x84, 0x8E,
 /* E */ 0x12, 0x89, 0xD3,
 /* I */ 0x17, 0x8B, 0xD8,
 /* i */ 0x28, 0x8B, 0xD8,
 /* O */ 0x18, 0x94, 0x99,
 /* U */ 0x16, 0x81, 0x9A,
 /*   */ 0x39, 0xF9, 0xF9, /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {        /* TILDE */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xC6, 0xC7,
 /* O */ 0x18, 0xE4, 0xE5,
 /* N */ 0x31, 0xA4, 0xA5,
 /*   */ 0x39,  '~',  '~', /* and additional generated character */
	0
};

uchar NAME(combi4table)[] = {         /* ACUTE ACCENT */
	/*scancode lower upper*/
 /* A */ 0x1E, 0xA0, 0xB5,
 /* E */ 0x12, 0x82, 0x90,
 /* I */ 0x17, 0xA1, 0xD6,
 /* i */ 0x28, 0xA1, 0xD6,
 /* O */ 0x18, 0xA2, 0xE0,
 /* U */ 0x16, 0xA3, 0xE9,
 /*   */ 0x39, 0xEF, 0xEF, /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {         /* GRAVE ACCENT */
	/*scancode lower upper*/
 /* A */ 0x1E, 0x85, 0xB7,
 /* E */ 0x12, 0x8A, 0xD4,
 /* I */ 0x17, 0xEC, 0xDE,
 /* i */ 0x28, 0xEC, 0xDE,
 /* O */ 0x18, 0x95, 0xE3,
 /* U */ 0x16, 0x97, 0xEB,
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi6table)[] = {
	/*scancode lower upper*/
	 0
};

#endif

struct KeyboardDefinition NAME(Keyboard) = {
	"TR",                                          //char LanguageShort[4];			// "GR",
	"TURKISH - Q layout with combis (untested, by Davide)",    //char *Description;		// created by, "with combis"
	DRIVER_FUNCTION_FULL,                          //char DriverFunctionRequired;
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
