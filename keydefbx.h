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

����������������������������������������������������������������Ŀ
�"   �!   �@   �#   �$   �%   ��   �&   �*   �(   �)   �_   �+   �
�' � �1 � �2 � �3 � �4 � �5 � �6 � �7 � �8 � �9 � �0 � �- � �= � �
�������������������������������������������������������������������
      �Q   �W   �E   �R   �T   �Y   �U   �I   �O   �P   �`   �{   �
      �q � �w   �e � �r � �t   �y � �u   �i � �o � �p � ��   �[ � �
      ��������������������������������������������������������������
       �A   �S   �D   �F   �G   �H   �J   �K   �L   ��   �^   �}   �
       �a   �s � �d  �f � �g   �h   �j   �k   �l � ��   �~   �] � �
      ��������������������������������������������������������������
      �|   �Z   �X   �C   �V   �B   �N   �M   �<   �>   �:   �?   �
      �\ � �z � �x � �c � �v � �b   �n   �m � �, � �. � �; � �/ � �
      �������������������������������������������������������������

Also: <Ctrl> + "aeodt" = �����

********************************************************/

/* table layout:

key on US keyboard,
        scancode,
                flags, what is defined
                        3 keys for NORMAL+CTRL, 1 for ALTGREY
*/

uchar NAME(scancodetable)[] = {

 /* 1 */       ALTGR     (0x02,                  '�')
 /* 2 */       ALTGR     (0x03,                  '�')
 /* 3 */       ALTGR     (0x04,                  '�')
 /* 4 */       ALTGR     (0x05,                  '�')
 /* 5 */       ALTGR     (0x06,                  '�')
 /* 6 */ PUNCT_ALTGR     (0x07,'6', COMBI5,      '�')
 /* 7 */       ALTGR     (0x08,                  '�')
 /* 8 */       ALTGR     (0x09,                  '�')
 /* 9 */       ALTGR     (0x0A,                  '�')
 /* 0 */       ALTGR     (0x0B,                  '�')
 /* - */       ALTGR     (0x0c,                  '�')
 /* = */  CTRL_ALTGR     (0x0D,     COMBI6,      '�')
 /* Q */       ALTGR     (0x10,                  '�')
 /* E */       ALTGR     (0x12,                  EURO)
 /* R */       ALTGR     (0x13,                   '�')
 /* Y */       ALTGR     (0x15,                   '�')
 /* I */       ALTGR     (0x17,                   '�')
 /* O */       ALTGR     (0x18,                   '�')
 /* P */       ALTGR     (0x19,                   '�')
 /* ] */ PUNCT_ALTGR     (0x1B,'[','{',           '�')
 /* S */       ALTGR     (0x1F,                   '�')
 /* D */       ALTGR     (0x20,                   '')
 /* F */       ALTGR     (0x21,                   '�')
 /* L */       ALTGR     (0x26,                   '�')
 /*   */ ALPHA           (0x27,'�','�'               )
//*???*/                 (0x28,                      )
 /* ' */ PUNCT_ALTGR     (0x29,0x27,0x22,         '�')
 /* ] */ PUNCT_ALTGR     (0x2b,']','}',           '�')
 /* Z */       ALTGR     (0x2c,                   '�')
 /* X */       ALTGR     (0x2d,                   '�')
 /* C */       ALTGR     (0x2e,                   '�')
 /* V */       ALTGR     (0x2f,                   '�')
 /* M */       ALTGR     (0x32,                   '�')
 /* , */       ALTGR     (0x33,                   '�')
 /* . */       ALTGR     (0x34,                   '�')
 /* ' */ PUNCT_ALTGR     (0x35,';',':',           '�')
 /* ? */ PUNCT_ALTGR     (0x56,'\\','|',          '�')
 /* ? */ PUNCT_ALTGR     (0x73,'/','?',           '�')
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

uchar NAME(combi1table)[] = {         /* ~ a� n� o� #32~ A� N� O� */
        /*scancode lower upper*/
 /* A */ 0x1E, '�','�',
 /* O */ 0x18, '�','�',
 /* N */ 0x31, '�','�',
 /*   */ 0x39, '~', '~', /* and additional generated character */
         0
};

uchar NAME(combi2table)[] = {         /* ^ a� e� i� o� u� #32^ A� E� I� O� U� */
        /*scancode lower upper*/
 /* A */ 0x1E,'�','�',
 /* E */ 0x12,'�','�',
 /* I */ 0x17,'�','�',
 /* O */ 0x18,'�','�',
 /* U */ 0x16,'�','�',
 /*   */ 0x39,  '^',  '^', /* and additional generated character */
         0
};

uchar NAME(combi3table)[] = {         /* � a� e� i� o� u� y� #32� A� E� I� O� U� Y� */
        /*scancode lower upper*/
 /* A */ 0x1E, '�','�',
 /* E */ 0x12, '�','�',
 /* I */ 0x17, '�','�',
 /* O */ 0x18, '�','�',
 /* U */ 0x16, '�','�',
 /* Y */ 0x15, '�','�',
 /*   */ 0x39,  '�',  '�', /* and additional generated character */
         0
};

uchar NAME(combi4table)[] = {         /* ` a� e� i� o� u� #32` A� E� I� O� U� */
        /*scancode lower upper*/
 /* A */ 0x1E,'�','�',
 /* E */ 0x12,'�','�',
 /* I */ 0x17,'�','�',
 /* O */ 0x18,'�','�',
 /* U */ 0x16,'�','�',
 /*   */ 0x39,  '`',  '`', /* and additional generated character */
         0
};

uchar NAME(combi5table)[] = {         /* � a� e� i� o� u� y� #32� A� E� I� O� U� */
        /*scancode lower upper*/
 /* A */ 0x1E,'�','�',
 /* E */ 0x12,'�','�',
 /* I */ 0x17,'�','�',
 /* O */ 0x18,'�','�',
 /* U */ 0x16,'�','�',
 /* Y */ 0x15,'�', 0,           /* Y character not available in CP850 */

 /*   */ 0x39,  '�',  '�', /* and additional generated character */
         0
};

uchar NAME(combi6table)[] = {           /* <Ctrl> + <=> combinations, " ����� �����  */
	/*scancode lower upper*/
 /* A */ 0x1E,'�','�',
 /* E */ 0x12,'�','�',
 /* O */ 0x18,'�','�',
 /* D */ 0x20,'�','�',
 /* T */ 0x14,'�','�', 
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
