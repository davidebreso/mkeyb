/* keydeftr.h */

/*
 * history
 * 18 apr 22: davide bresolin - creation
 */

#define NAME(x) x##_TRF

#include <dos.h>
#include "mkeyb.h"

#define LANGUAGE "turkish-f"
#define STATUS   "untested, by Davide"

#define COMBI

/********************************************************
 * TURKISH F keyboard mappings				*
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

/* Created from the Turkish F Layout at http://kbdlayout.info/kbdtuf
   Codepage: 857
*/

uchar NAME(scancodetable)[] = {

 /* ` */ PUNCT_ALTGR	(0x29, '+',  '*',       0xAA  )		// PLUS SIGN, ASTERISK, NOT SIGN
 /* 1 */ PUNCT_ALTGRSHIFT(0x02, '1',  '!',       0xFB, 0xAD)	// DIGIT ONE, EXCLAMATION MARK, SUPERSCRIPT ONE, INVERTED EXCLAMATION MARK
 /* 2 */ PUNCT_ALTGR	(0x03, '2',  '"',       0xFD  )		// DIGIT TWO, QUOTATION MARK, SUPERSCRIPT TWO
#ifdef COMBI
 /* 3 */ PUNCT_ALTGRSHIFT(0x04, '3',  COMBI1,    '#',  0xFC)	// DIGIT THREE, CIRCUMFLEX ACCENT, NUMBER SIGN, SUPERSCRIPT THREE
#else
 /* 3 */ PUNCT_ALTGRSHIFT(0x04, '3',  '^',       '#',  0xFC)	// DIGIT THREE, CIRCUMFLEX ACCENT, NUMBER SIGN, SUPERSCRIPT THREE
#endif
 /* 4 */ PUNCT_ALTGRSHIFT(0x05, '4',  '$',       0xAC, 0xCF)	// DIGIT FOUR, DOLLAR SIGN, VULGAR FRACTION ONE QUARTER, CURRENCY SIGN
 /* 5 */ PUNCT_ALTGR	(0x06, '5',  '%',       0xAB  )		// DIGIT FIVE, PERCENT SIGN, VULGAR FRACTION ONE HALF
 /* 6 */ PUNCT_ALTGR	(0x07, '6',  '&',       0xF3  )		// DIGIT SIX, AMPERSAND, VULGAR FRACTION THREE QUARTERS
 /* 7 */ PUNCT_ALTGR	(0x08, '7',  '\'',      '{'   )		// DIGIT SEVEN, APOSTROPHE, LEFT CURLY BRACKET
 /* 8 */ PUNCT_ALTGR	(0x09, '8',  '(',       '['   )		// DIGIT EIGHT, LEFT PARENTHESIS, LEFT SQUARE BRACKET
 /* 9 */ PUNCT_ALTGR	(0x0a, '9',  ')',       ']'   )		// DIGIT NINE, RIGHT PARENTHESIS, RIGHT SQUARE BRACKET
 /* 0 */ PUNCT_ALTGR	(0x0b, '0',  '=',       '}'   )		// DIGIT ZERO, EQUALS SIGN, RIGHT CURLY BRACKET
 /* - */ PUNCT_ALTGRSHIFT(0x0c, '/',  '?',       '\\', 0xA8)	// SOLIDUS, QUESTION MARK, REVERSE SOLIDUS, INVERTED QUESTION MARK
 /* = */ PUNCT_ALTGR	(0x0d, '-',  '_',       '|'   )		// HYPHEN-MINUS, LOW LINE, VERTICAL LINE

 /* Q */ ALPHA_ALTGR	(0x10, 'f',  'F',       '@'   )		// LATIN SMALL LETTER F, LATIN CAPITAL LETTER F, COMMERCIAL AT
 /* W */ ALPHA		(0x11, 'g',  'G'              )		// LATIN SMALL LETTER G, LATIN CAPITAL LETTER G
 /* E */ ALPHA		(0x12, 0xA7, 0xA6             )		// LATIN SMALL LETTER G WITH BREVE, LATIN CAPITAL LETTER G WITH BREVE
 /* R */ ALPHA_ALTGRSHIFT(0x13, 0x8D, 'I',       0xF4, 0xA9)	// LATIN SMALL LETTER DOTLESS I, LATIN CAPITAL LETTER I, PILCROW SIGN, REGISTERED SIGN
 /* T */ ALPHA		(0x14, 'o',  'O'              )		// LATIN SMALL LETTER O, LATIN CAPITAL LETTER O
 /* Y */ ALPHA_ALTGR	(0x15, 'd',  'D',       0xBE  )		// LATIN SMALL LETTER D, LATIN CAPITAL LETTER D, YEN SIGN
 /* U */ ALPHA		(0x16, 'r',  'R'              )		// LATIN SMALL LETTER R, LATIN CAPITAL LETTER R
 /* I */ ALPHA		(0x17, 'n',  'N'              )		// LATIN SMALL LETTER N, LATIN CAPITAL LETTER N
 /* O */ ALPHA_ALTGRSHIFT(0x18, 'h',  'H',      0x9B,  0x9D)	// LATIN SMALL LETTER H, LATIN CAPITAL LETTER H, LATIN SMALL LETTER O WITH STROKE, LATIN CAPITAL LETTER O WITH STROKE
 /* P */ ALPHA_ALTGR	(0x19, 'p',  'P',       0x9C  )		// LATIN SMALL LETTER P, LATIN CAPITAL LETTER P, POUND SIGN
#ifdef COMBI
 /* [ */ ALPHA_ALTGR	(0x1a, 'q',  'Q',       COMBI2)		// LATIN SMALL LETTER Q, LATIN CAPITAL LETTER Q, DIAERESIS
 /* ] */ ALPHA_ALTGR	(0x1b, 'w',  'W',       COMBI3)		// LATIN SMALL LETTER W, LATIN CAPITAL LETTER W, TILDE
#else
 /* [ */ ALPHA_ALTGR	(0x1a, 'q',  'Q',       0xF9  )		// LATIN SMALL LETTER Q, LATIN CAPITAL LETTER Q, DIAERESIS
 /* ] */ ALPHA_ALTGR	(0x1b, 'w',  'W',       '~'   )		// LATIN SMALL LETTER W, LATIN CAPITAL LETTER W, TILDE
#endif

 /* A */ ALPHA_ALTGRSHIFT(0x1e, 'u',  'U',      0x91,  0x92)	// LATIN SMALL LETTER U, LATIN CAPITAL LETTER U, LATIN SMALL LETTER AE, LATIN CAPITAL LETTER AE
 /* S */ ALPHA_ALTGRSHIFT(0x1f, 'i',  0x98,     0xE1,  0xF5)	// LATIN SMALL LETTER I, LATIN CAPITAL LETTER I WITH DOT ABOVE, LATIN SMALL LETTER SHARP S, SECTION SIGN
 /* D */ ALPHA_ALTGR	(0x20, 'e',  'E',       0xD5  )		// LATIN SMALL LETTER E, LATIN CAPITAL LETTER E, EURO SIGN
 /* F */ ALPHA_ALTGRSHIFT(0x21, 'a',  'A',      IGNORE,0xD1)	// LATIN SMALL LETTER A, LATIN CAPITAL LETTER A, <none>, FEMININE ORDINAL INDICATOR
 /* G */ ALPHA		(0x22, 0x81, 0x9A             )		// LATIN SMALL LETTER U WITH DIAERESIS, LATIN CAPITAL LETTER U WITH DIAERESIS
 /* H */ ALPHA		(0x23, 't',  'T'              )		// LATIN SMALL LETTER T, LATIN CAPITAL LETTER T
 /* J */ ALPHA		(0x24, 'k',  'K'              )		// LATIN SMALL LETTER K, LATIN CAPITAL LETTER K
 /* K */ ALPHA		(0x25, 'm',  'M'              )		// LATIN SMALL LETTER M, LATIN CAPITAL LETTER M

#ifdef COMBI
 /* ; */ ALPHA_ALTGR	(0x27, 'y',  'Y',       COMBI4)		// LATIN SMALL LETTER Y, LATIN CAPITAL LETTER Y, ACUTE ACCENT
 /*   */ PUNCT_ALTGR	(0x2b, 'x',  'X',       COMBI5)		// LATIN SMALL LETTER X, LATIN CAPITAL LETTER X, GRAVE ACCENT
#else
 /* ; */ ALPHA_ALTGR	(0x27, 'y',  'Y',       0xEF  )		// LATIN SMALL LETTER Y, LATIN CAPITAL LETTER Y, ACUTE ACCENT
 /*   */ PUNCT_ALTGR	(0x2b, 'x',  'X',       '`'   )		// LATIN SMALL LETTER X, LATIN CAPITAL LETTER X, GRAVE ACCENT
#endif
 /* ' */ ALPHA		(0x28, 0x9F, 0x9E             )		// LATIN SMALL LETTER S WITH CEDILLA, LATIN CAPITAL LETTER S WITH CEDILLA

 /* \ */ PUNCT_ALTGRSHIFT(0x56, '<',  '>',      '|',   0xDD)	// LESS-THAN SIGN, GREATER-THAN SIGN, VERTICAL LINE, BROKEN BAR

 /* Z */ ALPHA_ALTGRSHIFT(0x2c, 'j',  'J',      0xAE,  '<')	// LATIN SMALL LETTER J, LATIN CAPITAL LETTER J, LEFT-POINTING DOUBLE ANGLE QUOTATION MARK, LESS-THAN SIGN
 /* X */ ALPHA_ALTGRSHIFT(0x2d, 0x94, 0x99,     0xAF,  '>')	// LATIN SMALL LETTER O WITH DIAERESIS, LATIN CAPITAL LETTER O WITH DIAERESIS, RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK, GREATER-THAN SIGN
 /* C */ ALPHA_ALTGRSHIFT(0x2e, 'v',  'V',      0XBD,  0xB8)	// LATIN SMALL LETTER V, LATIN CAPITAL LETTER V, CENT SIGN, COPYRIGHT SIGN
 /* V */ ALPHA		(0x2f, 'c',  'C'              )		// LATIN SMALL LETTER C, LATIN CAPITAL LETTER C
 /* B */ ALPHA		(0x30, 0x87, 0x80             )		// LATIN SMALL LETTER C WITH CEDILLA, LATIN CAPITAL LETTER C WITH CEDILLA
 /* N */ ALPHA		(0x31, 'z',  'Z'              )		// LATIN SMALL LETTER Z, LATIN CAPITAL LETTER Z
 /* M */ ALPHA_ALTGRSHIFT(0x32, 's',  'S',	0xE6,  0xD0)	// LATIN SMALL LETTER S, LATIN CAPITAL LETTER S, MICRO SIGN, MASCULINE ORDINAL INDICATOR
 /* , */ ALPHA_ALTGR	(0x33, 'b',  'B',       0xE8  )		// LATIN SMALL LETTER B, LATIN CAPITAL LETTER B, MULTIPLICATION SIGN
 /* . */ PUNCT_ALTGR	(0x34, '.',  ':',       0xF6  )		// FULL STOP, COLON, DIVISION SIGN
 /* / */ PUNCT_ALTGR	(0x35, ',',  ';',       0xF0  )		// COMMA, SEMICOLON, SOFT HYPHEN

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
 /* A */ 0x21, 0x83, 0xB6,
 /* E */ 0x20, 0x88, 0xD2,
 /* I */ 0x13, 0x8C, 0xD7,
 /* i */ 0x1F, 0x8C, 0xD7,
 /* O */ 0x14, 0x93, 0xE2,
 /* U */ 0x1E, 0x96, 0xEA,
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
	 0
};

uchar NAME(combi2table)[] = {         /* DIAERESIS */
	/*scancode lower upper*/
 /* A */ 0x21, 0x84, 0x8E,
 /* E */ 0x20, 0x89, 0xD3,
 /* I */ 0x13, 0x8B, 0xD8,
 /* i */ 0x1F, 0x8B, 0xD8,
 /* O */ 0x14, 0x94, 0x99,
 /* U */ 0x1E, 0x81, 0x9A,
 /*   */ 0x39, 0xF9, 0xF9, /* and additional generated character */
	 0
};

uchar NAME(combi3table)[] = {        /* TILDE */
	/*scancode lower upper*/
 /* A */ 0x21, 0xC6, 0xC7,
 /* O */ 0x14, 0xE4, 0xE5,
 /* N */ 0x17, 0xA4, 0xA5,
 /*   */ 0x39,  '~',  '~', /* and additional generated character */
	0
};

uchar NAME(combi4table)[] = {         /* ACUTE ACCENT */
	/*scancode lower upper*/
 /* A */ 0x21, 0xA0, 0xB5,
 /* E */ 0x20, 0x82, 0x90,
 /* I */ 0x13, 0xA1, 0xD6,
 /* i */ 0x1F, 0xA1, 0xD6,
 /* O */ 0x14, 0xA2, 0xE0,
 /* U */ 0x1E, 0xA3, 0xE9,
 /*   */ 0x39, 0xEF, 0xEF, /* and additional generated character */
	 0
};

uchar NAME(combi5table)[] = {         /* GRAVE ACCENT */
	/*scancode lower upper*/
 /* A */ 0x21, 0x85, 0xB7,
 /* E */ 0x20, 0x8A, 0xD4,
 /* I */ 0x13, 0xEC, 0xDE,
 /* i */ 0x1F, 0xEC, 0xDE,
 /* O */ 0x14, 0x95, 0xE3,
 /* U */ 0x1E, 0x97, 0xEB,
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
	 0
};

uchar NAME(combi6table)[] = {
	/*scancode lower upper*/
	 0
};

#endif

struct KeyboardDefinition NAME(Keyboard) = {
	"TRF",                                          //char LanguageShort[4];			// "GR",
	"TURKISH - F layout with combis (untested, by Davide)",    //char *Description;		// created by, "with combis"
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
