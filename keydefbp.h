/* keydefbp.h */

/*
 * history
 * 22 may 03: Anton Zinoviev <anton@lml.bas.bg> - creation
 */

#define NAME(x) x##_BGP

#include <dos.h>
#include "mkeyb.h"


/********************************************************
 * BULGARIAN phonetic keyboard mappings			*
 ********************************************************/

uchar NAME(scancodetable)[] = {

//* 1 */ PUNCT(0x02, '1', '!')
//* 2 */ PUNCT(0x03, '2', '@')
//* 3 */ PUNCT(0x04, '3', '#')
//* 4 */ PUNCT(0x05, '4', '$')
//* 5 */ PUNCT(0x06, '5', '%')
//* 6 */ PUNCT(0x07, '6', '^')
//* 7 */ PUNCT(0x08, '7', '&')
//* 8 */ PUNCT(0x09, '8', '*')
//* 9 */ PUNCT(0x0A, '9', '(')
//* 0 */ PUNCT(0x0B, '0', ')')
//* - */ PUNCT(0x0C, '-', '_')
//* = */ PUNCT(0x0D, '=', '+')

 /* q */ ALPHA(0x10, 'ø', 'ü')
 /* w */ ALPHA(0x11, '¢', 'Ç')
 /* e */ ALPHA(0x12, '•', 'Ö')
 /* r */ ALPHA(0x13, '∞', 'ê')
 /* t */ ALPHA(0x14, '≤', 'í')
 /* y */ ALPHA(0x15, '∫', 'ö')
 /* u */ ALPHA(0x16, '≥', 'ì')
 /* i */ ALPHA(0x17, '®', 'à')
 /* o */ ALPHA(0x18, 'Æ', 'é')
 /* p */ ALPHA(0x19, 'Ø', 'è')
 /* [ */ ALPHA(0x1A, '∏', 'ò')
 /* ] */ ALPHA(0x1B, 'π', 'ô')

 /* a */ ALPHA(0x1E, '†', 'Ä')
 /* s */ ALPHA(0x1F, '±', 'ë')
 /* d */ ALPHA(0x20, '§', 'Ñ')
 /* f */ ALPHA(0x21, '¥', 'î')
 /* g */ ALPHA(0x22, '£', 'É')
 /* h */ ALPHA(0x23, 'µ', 'ï')
 /* j */ ALPHA(0x24, '©', 'â')
 /* k */ ALPHA(0x25, '™', 'ä')
 /* l */ ALPHA(0x26, '´', 'ã')
//* ; */ PUNCT(0x27, ';', ';')
//* ' */ PUNCT(0x28, '\'', '"')

 /* ~ */ ALPHA(0x29, '∑', 'ó')
 /* \ */ ALPHA(0x2B, 'æ','û')

 /* z */ ALPHA(0x2C, 'ß', 'á')
 /* x */ ALPHA(0x2D, 'º', 'ú')
 /* c */ ALPHA(0x2E, '∂', 'ñ')
 /* v */ ALPHA(0x2F, '¶', 'Ü')
 /* b */ ALPHA(0x30, '°', 'Å')
 /* n */ ALPHA(0x31, '≠', 'ç')
 /* m */ ALPHA(0x32, '¨', 'å')
//* , */ PUNCT(0x33, ',', '<')
//* . */ PUNCT(0x34, '.', '>')
//* / */ PUNCT(0x35, '/', '?')
	 0
};

struct KeyboardDefinition NAME(Keyboard) = {
	"BGP",                             //char LanguageShort[4]; // "GR",
	"BULGARIAN PHONETIC - use right Ctrl to switch (by Anton Zinoviev)",  //char *Description; // created by, "with combis"
	DRIVER_FUNCTION_FASTSWITCH,          //char DriverFunctionRequired;
	NAME(scancodetable),              //char *ScancodeTable;
#ifdef COMBI
	{	NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif			
	0,                                //char DezimalDingsbums;
	1,                                //char DefaultLayoutUS; // TRUE for non-latin languages
	} ;                               
                                      
                                      
                                      
