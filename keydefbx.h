/* keydefbx.h */


#define NAME(x) x##_BX


#include <dos.h>
#include "mkeyb.h"


#define COMBI

/***comments from original author (Henrique Peron - hperon@brturbo.com)***

ABNT Brazilian XKeyb keyboard layout, "extended" edition.
This layout can be used with codepages 850 or 858.
Henrique Peron - hperon@brturbo.com

This enhanced mapping for the ABNT keyboard (ABNT is a brazilian government
organization which defines standards for brazilian-made products meant for
the brazilian market, much like ISO for the rest of the world) comprehends
all the characters of the original ABNT keyboard. It also comprehends all
other characters met in CP850, though those linedraw and block characters
were left behind.

ÚÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄÂÄÄÄÄ¿
³"   ³!   ³@   ³#   ³$   ³%   ³ù   ³&   ³*   ³(   ³)   ³_   ³+   ³
³' ­ ³1 û ³2 ı ³3 ü ³4 œ ³5 ½ ³6 ª ³7 ¬ ³8 « ³9 ó ³0 î ³- ñ ³= õ ³
ÀÄÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁ¿
      ³Q   ³W   ³E   ³R   ³T   ³Y   ³U   ³I   ³O   ³P   ³`   ³{   ³
      ³q ô ³w   ³e Õ ³r © ³t   ³y ¾ ³u   ³i Õ ³o Ï ³p ò ³ï   ³[ ¦ ³
      ÀÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁÂÄÄÄÁ¿
       ³A   ³S   ³D   ³F   ³G   ³H   ³J   ³K   ³L   ³€   ³^   ³}   ³
       ³a   ³s á ³d  ³f Ÿ ³g   ³h   ³j   ³k   ³l ú ³‡   ³~   ³] § ³
      ÚÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÁÄÄÄÂÙ
      ³|   ³Z   ³X   ³C   ³V   ³B   ³N   ³M   ³<   ³>   ³:   ³?   ³
      ³\ İ ³z ö ³x  ³c ¸ ³v ÷ ³b   ³n   ³m æ ³, ® ³. ¯ ³; ¨ ³/ ø ³
      ÀÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÙ

Also: <Ctrl> + "aeodt" = †‘›Ğç

********************************************************/

/* table layout:

key on US keyboard,
        scancode,
                flags, what is defined
                        3 keys for NORMAL+CTRL, 1 for ALTGREY
*/

uchar NAME(scancodetable)[] = {

 /* 1 */       ALTGR     (0x02,                  'û')
 /* 2 */       ALTGR     (0x03,                  'ı')
 /* 3 */       ALTGR     (0x04,                  'ü')
 /* 4 */       ALTGR     (0x05,                  'œ')
 /* 5 */       ALTGR     (0x06,                  '½')
 /* 6 */ PUNCT_ALTGR     (0x07,'6', COMBI5,      'ª')
 /* 7 */       ALTGR     (0x08,                  '¬')
 /* 8 */       ALTGR     (0x09,                  '«')
 /* 9 */       ALTGR     (0x0A,                  'ó')
 /* 0 */       ALTGR     (0x0B,                  'î')
 /* - */       ALTGR     (0x0c,                  'ñ')
 /* = */  CTRL_ALTGR     (0x0D,     COMBI6,      'õ')
 /* Q */       ALTGR     (0x10,                  'ô')
 /* E */       ALTGR     (0x12,                  EURO)
 /* R */       ALTGR     (0x13,                   '©')
 /* Y */       ALTGR     (0x15,                   '¾')
 /* I */       ALTGR     (0x17,                   'Õ')
 /* O */       ALTGR     (0x18,                   'Ï')
 /* P */       ALTGR     (0x19,                   'ò')
 /* ] */ PUNCT_ALTGR     (0x1B,'[','{',           '¦')
 /* S */       ALTGR     (0x1F,                   'á')
 /* D */       ALTGR     (0x20,                   '')
 /* F */       ALTGR     (0x21,                   'Ÿ')
 /* L */       ALTGR     (0x26,                   'ú')
 /*   */ ALPHA           (0x27,'‡','€'               )
//*???*/                 (0x28,                      )
 /* ' */ PUNCT_ALTGR     (0x29,0x27,0x22,         '­')
 /* ] */ PUNCT_ALTGR     (0x2b,']','}',           '§')
 /* Z */       ALTGR     (0x2c,                   'ö')
 /* X */       ALTGR     (0x2d,                   '')
 /* C */       ALTGR     (0x2e,                   '¸')
 /* V */       ALTGR     (0x2f,                   '÷')
 /* M */       ALTGR     (0x32,                   'æ')
 /* , */       ALTGR     (0x33,                   '®')
 /* . */       ALTGR     (0x34,                   '¯')
 /* ' */ PUNCT_ALTGR     (0x35,';',':',           '¨')
 /* ? */ PUNCT_ALTGR     (0x56,'\\','|',          'İ')
 /* ? */ PUNCT_ALTGR     (0x73,'/','?',           'ø')
 /* ? */ PUNCT           (0x7e,'.','.'               )



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

uchar NAME(combi1table)[] = {         /* ~ aÆ n¤ oä #32~ AÇ N¥ Oå */
        /*scancode lower upper*/
 /* A */ 0x1E, 'Æ','Ç',
 /* O */ 0x18, 'ä','å',
 /* N */ 0x31, '¤','¥',
 /*   */ 0x39, '~', '~', /* and additional generated character */
         0
};

uchar NAME(combi2table)[] = {         /* ^ aƒ eˆ iŒ o“ u– #32^ A¶ EÒ I× Oâ Uê */
        /*scancode lower upper*/
 /* A */ 0x1E,'ƒ','¶',
 /* E */ 0x12,'ˆ','Ò',
 /* I */ 0x17,'Œ','×',
 /* O */ 0x18,'“','â',
 /* U */ 0x16,'–','ê',
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
         0
};

uchar NAME(combi3table)[] = {         /* ï a  e‚ i¡ o¢ u£ yì #32ï Aµ E IÖ Oà Ué Yí */
        /*scancode lower upper*/
 /* A */ 0x1E, ' ','µ',
 /* E */ 0x12, '‚','',
 /* I */ 0x17, '¡','Ö',
 /* O */ 0x18, '¢','à',
 /* U */ 0x16, '£','é',
 /* Y */ 0x15, 'ì','í',
 /*   */ 0x39,  'ï',  'ï', /* and additional generated character */
         0
};

uchar NAME(combi4table)[] = {         /* ` a… eŠ i o• u— #32` A· EÔ IŞ Oã Uë */
        /*scancode lower upper*/
 /* A */ 0x1E,'…','·',
 /* E */ 0x12,'Š','Ô',
 /* I */ 0x17,'','Ş',
 /* O */ 0x18,'•','ã',
 /* U */ 0x16,'—','ë',
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
         0
};

uchar NAME(combi5table)[] = {         /* ù a„ e‰ i‹ o” u y˜ #32ù A EÓ IØ O™ Uš */
        /*scancode lower upper*/
 /* A */ 0x1E,'„','',
 /* E */ 0x12,'‰','Ó',
 /* I */ 0x17,'‹','Ø',
 /* O */ 0x18,'”','™',
 /* U */ 0x16,'','š',
 /* Y */ 0x15,'˜', 0,           /* Y character not available in CP850 */

 /*   */ 0x39,  'ù',  'ù', /* and additional generated character */
         0
};

uchar NAME(combi6table)[] = {           /* <Ctrl> + <=> combinations, " †‘›Ğç ’Ñè  */
	/*scancode lower upper*/
 /* A */ 0x1E,'†','',
 /* E */ 0x12,'‘','’',
 /* O */ 0x18,'›','',
 /* D */ 0x20,'Ğ','Ñ',
 /* T */ 0x14,'ç','è', 
 /*   */ 0x39,  '?',  '?', /* and additional generated character */
	
	 0
};

#endif


struct KeyboardDefinition NAME(Keyboard) = {
	"BX",                                    //char LanguageShort[4];			// "GR",                    
	"BRAZIL EXTENDED - portuguese keyboard with combis (Henrique Peron)",//char *Description;				// created by, "with combis"
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
