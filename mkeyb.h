/* these things are imported from the resident part */

#ifndef RESIDENT
 #define RESIDENT far
#endif

typedef unsigned long   ulong;
typedef unsigned int    uint;
typedef unsigned short  ushort;
typedef unsigned char   uchar;

extern uchar *RESIDENT cdecl pResidentScancodetable;
extern char  *RESIDENT cdecl ResidentCombiTables[6];
extern uchar  RESIDENT cdecl DecimalDingsBums; /* grey , or . */
extern uchar  RESIDENT cdecl SilentKeyboard; /* absorb all keyboard input except CtrlAltDel */

extern uchar RESIDENT  cdecl usebiosonly_flag;

extern void (interrupt far *RESIDENT cdecl OldInt9)();
extern void (interrupt far *RESIDENT cdecl OldInt16)();
extern void (interrupt far *RESIDENT cdecl OldInt15)();
extern void (interrupt far *RESIDENT cdecl OldInt2F)();

extern void interrupt RESIDENT int9_handler();
extern void interrupt RESIDENT int16_handler();
extern void interrupt RESIDENT int15_handler();
extern void interrupt RESIDENT int2f_handler();
/* magic constants in keycode table */

#define _KCAPS       0x80               /* key uses caps lock */
#define _KCHAR       0x40               /* upper/lower defined */
#define _KCTRL       0x20               /* ctrl defined */
#define _KALTGR      0x10               /* altgrey defined */
#define _KALTGRSHIFT 0x08               /* altgrey uses shift */
#define _KREPLACE    0xF8               /* impossible combination */

#define SIZEFIELD        0x07           /* length field */

#define PUNCT(scan,lcase,ucase) \
        scan, 2 + _KCHAR+2, lcase, ucase,
#define PUNCT_CTRL(scan,lcase,ucase,ctrl) \
        scan, 2 + (_KCHAR|_KCTRL)+3, lcase, ucase, ctrl,
#define ALPHA(scan,lcase,ucase) \
        scan, 2 + (_KCHAR|_KCAPS)+2, lcase, ucase,
#define ALPHA_CTRL(scan,lcase,ucase,ctrl) \
        scan, 2 + (_KCHAR|_KCAPS|_KCTRL)+3, lcase, ucase, ctrl,


#define ALTGR(scan,code) \
        scan, 2 + _KALTGR+1, code,
#define ALTGRSHIFT(scan,code1,code2) \
        scan, 2 + (_KALTGR|_KALTGRSHIFT)+2, code1, code2,

#define PUNCT_ALTGR(scan,lcase,ucase,alt) \
        scan, 2 + (_KCHAR|_KALTGR)+3, lcase, ucase, alt,
#define ALPHA_ALTGR(scan,lcase,ucase,alt) \
        scan, 2 + (_KCHAR|_KCAPS|_KALTGR)+3, lcase, ucase, alt,

#define PUNCT_CTRL_ALTGR(scan,lcase,ucase,ctrl,alt) \
        scan, 2 + (_KCHAR|_KCTRL|_KALTGR)+4, lcase, ucase, ctrl, alt,

#define ALPHA_CTRL_ALTGR(scan,lcase,ucase,ctrl,alt) \
        scan, 2 + (_KCHAR|_KCAPS|_KCTRL|_KALTGR)+4, lcase, ucase, ctrl, alt,

#define CTRL_ALTGR(scan,ctrl,alt) \
        scan, 2 + (_KCTRL|_KALTGR)+2, ctrl, alt,

#define REPLACE(scan,code) \
        scan, 2 + _KREPLACE+1, code,
#define REPLACESCAN (2+_KREPLACE+1)


/* #define IGNORE       0x00 */
#define COMBI1          1
#define COMBI2          2
#define COMBI3          3
#define COMBI4          4
#define COMBI5          5
#define COMBI6          6

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))


#define DRIVER_FUNCTION_NORMAL     0
#define DRIVER_FUNCTION_FULL       1
#define DRIVER_FUNCTION_FASTSWITCH 2
#define DRIVER_FUNCTION_STANDARD   4
#define DRIVER_FUNCTION_STD_FULL   5

struct KeyboardDefinition {
	char LanguageShort[4];			// "GR", 
	char *Description;				// created by, "with combis",...
	char DriverFunctionRequired;
	char *ScancodeTable;
	char *CombicodeTables[6];
	char DezimalDingsbums;
	char DefaultLayoutUS;			// TRUE for russian  
	};


#define EURO 213
