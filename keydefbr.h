/* keydefbr.h */


#define NAME(x) x##_BR


#include <dos.h>
#include "mkeyb.h"


#define COMBI

/***comments from original author (Henrique Peron - hperon@brturbo.com)***

ABNT Brazilian XKeyb keyboard layout.
Henrique Peron
hperon@brturbo.com

********************************************************/

/* table layout:

key on US keyboard,
        scancode,
                flags, what is defined
                        3 keys for NORMAL+CTRL, 1 for ALTGREY
*/

uchar NAME(scancodetable)[] = {

 /* 1 */       ALTGR     (0x02,                  '˚')
 /* 2 */       ALTGR     (0x03,                  '˝')
 /* 3 */       ALTGR     (0x04,                  '¸')
 /* 4 */       ALTGR     (0x05,                  'ú')
 /* 5 */       ALTGR     (0x06,                  'Ω')
 /* 6 */ PUNCT_ALTGR     (0x07,'6', COMBI5,      '™')
 /* = */  CTRL_ALTGR     (0x0D,     COMBI6,      'ı')
 /* ] */ PUNCT_ALTGR     (0x1B,'[','{',           '¶')
 /*   */ ALPHA           (0x27,'á','Ä'               )
//*???*/                 (0x28,                      )
 /* ' */ PUNCT           (0x29,0x27,0x22             )
 /* ] */ PUNCT_ALTGR     (0x2b,']','}',           'ß')
 /* ' */ PUNCT           (0x35,';',':'               )
 /* ? */ PUNCT           (0x56,'\\','|'              )
 /* ? */ PUNCT_ALTGR     (0x73,'/','?',           '¯')
 /* ? */ PUNCT           (0x7e,'.','.'               )

 /* E */ ALTGR           (0x12, EURO)          // Added by Snoopy81


#ifdef COMBI
 /* [ */ PUNCT           (0x1A,COMBI3,COMBI4        )
 /* ' */ PUNCT           (0x28,COMBI1,COMBI2        )
#endif
         0
};

/* these keys are generated on a COMBI+character base,
   don't know if that is correct.
   I also don't know what keys to generate, as the
   standard character set (DOS/BIOS) doesn't have
   norwegian/swedish/spanish characters
*/

#ifdef COMBI

uchar NAME(combi1table)[] = {         /* ~ a∆ n§ o‰ #32~ A« N• OÂ */
        /*scancode lower upper*/
 /* A */ 0x1E, '∆','«',
 /* O */ 0x18, '‰','Â',
 /* N */ 0x31, '§','•',
 /*   */ 0x39, '~', '~', /* and additional generated character */
         0
};

uchar NAME(combi2table)[] = {         /* ^ aÉ eà iå oì uñ #32^ A∂ E“ I◊ O‚ UÍ */
        /*scancode lower upper*/
 /* A */ 0x1E,'É','∂',
 /* E */ 0x12,'à','“',
 /* I */ 0x17,'å','◊',
 /* O */ 0x18,'ì','‚',
 /* U */ 0x16,'ñ','Í',
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
         0
};

uchar NAME(combi3table)[] = {         /* Ô a† eÇ i° o¢ u£ yÏ #32Ô Aµ Eê I÷ O‡ UÈ YÌ */
        /*scancode lower upper*/
 /* A */ 0x1E, '†','µ',
 /* E */ 0x12, 'Ç','ê',
 /* I */ 0x17, '°','÷',
 /* O */ 0x18, '¢','‡',
 /* U */ 0x16, '£','È',
 /* Y */ 0x15, 'Ï','Ì',
 /*   */ 0x39,  'Ô',  'Ô', /* and additional generated character */
         0
};

uchar NAME(combi4table)[] = {         /* ` aÖ eä iç oï uó #32` A∑ E‘ Iﬁ O„ UÎ */
        /*scancode lower upper*/
 /* A */ 0x1E,'Ö','∑',
 /* E */ 0x12,'ä','‘',
 /* I */ 0x17,'ç','ﬁ',
 /* O */ 0x18,'ï','„',
 /* U */ 0x16,'ó','Î',
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
         0
};

uchar NAME(combi5table)[] = {         /* ˘ aÑ eâ iã oî uÅ yò #32˘ Aé E” Iÿ Oô Uö */
        /*scancode lower upper*/
 /* A */ 0x1E,'Ñ','é',
 /* E */ 0x12,'â','”',
 /* I */ 0x17,'ã','ÿ',
 /* O */ 0x18,'î','ô',
 /* U */ 0x16,'Å','ö',
 /* Y */ 0x15,'ò', 0,           /* Y character not available in CP850 */

 /*   */ 0x39,  '˘',  '˘', /* and additional generated character */
         0
};

uchar NAME(combi6table)[] = {		/* <Ctrl> + <=> combinations, " ÂÊ¯˛ ≈∆ÿ–ﬁ  */
	/*scancode lower upper*/
 /* A */ 0x1E,'Â','≈',
 /* E */ 0x12,'Ê','∆',
 /* O */ 0x18,'¯','ÿ',
 /* D */ 0x20,'','–',
 /* T */ 0x14,'˛','ﬁ', 
 /*   */ 0x39,  '?',  '?', /* and additional generated character */
	
	 0
};

#endif


struct KeyboardDefinition NAME(Keyboard) = {
	"BR",                                    //char LanguageShort[4];			// "GR",                    
	"BRAZIL - portuguese keyboard with combis (Henrique Peron)",//char *Description;				// created by, "with combis"
	DRIVER_FUNCTION_FULL,                    //char DriverFunctionRequired;                                
	NAME(scancodetable),                     //char *ScancodeTable;                                        
#ifdef COMBI
	{	NAME(combi1table),NAME(combi2table),NAME(combi3table),
		NAME(combi4table),NAME(combi5table),NAME(combi6table) },
#else
	{ 0 },
#endif			
	',',                                     //char DezimalDingsbums;                                      
	0,                                       //char DefaultLayoutUS;			// TRUE for russian         
	} ;
