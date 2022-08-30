all: mkeyb.exe

INST_SIG=19309			# mKEYB fingerprint "mK"
VERSION=51				# version number
VERSION_STR="0.51"		# version number text
ZIPFILE=mkeyb051.zip

TCC=bcc.exe
TASM=tasm.exe
TLIB=tlib.exe
#PACK=pklite.exe
PACK=upx --8086
ZIP=zip

TCCLINK=$(TCC) -lm -O -Z -g1
TCCCOMP=$(TCC) -c  -O -Z -g1 -a-

INSTALLDIR=C:\DRIVERS

depends=prf.obj
resdep = mKEYBA.obj mkeybrc.obj mkeybr.obj mkeybrf.obj \
	mkeybrs.obj mkeybrsc.obj
keydefs = \
	keydefdk.obj \
	keydefGR.obj \
	keystdGR.obj \
	keydefG2.obj \
	keystdG2.obj \
	keydefIT.obj \
	keystdIT.obj \
	keydefLA.obj \
	keydefNL.obj \
	keydefno.obj \
	keydefpl.obj \
	keydefPO.obj \
	keydefru.obj \
	keydefSF.obj \
	keydefSG.obj \
	keydefSP.obj \
	keydefSU.obj \
	keydefSV.obj \
	keydefuk.obj \
	keydefBR.obj \
	keydefBX.obj \
	keydefFR.obj \
	keydefHE.obj \
	keydefBE.obj \
	keydefBG.obj \
	keydefBP.obj \
	keydefSL.obj \
	keydefUX.obj \
	keydefTR.obj \
	keydefTF.obj \

#
# MAIN EXECUTABLE
#
mkeyb.exe: mkeyb.obj  $(resdep) $(depends) $(keydefs)
	$(TCCLINK) mKEYB.obj $(resdep) $(depends) keydef.lib

mkeyb.obj: mkeyb.c mkeyb.h
	$(TCCCOMP) -DMY_INSTALL_SIGNATURE=$(INST_SIG) -DMY_VERSION_SIGNATURE=$(VERSION) -DMY_VERSION_TEXT=$(VERSION_STR) mKEYB.c

# GERMAN

keydefgr.obj:  keydefgr.h  mkeyb.h
	$(TCCCOMP) keydefgr.h
	$(TLIB) keydef.lib -+ keydefgr.obj

# GERMAN+STANDARD

keystdgr.obj:  keydefgr.h  mkeyb.h
	$(TCCCOMP) -okeystdgr -DSTANDARD keydefgr.h
	$(TLIB) keydef.lib -+ keystdgr.obj

# GERMAN+COMBI ( '`^ + AEIOU )

keydefg2.obj: keydefgr.h  mkeyb.h
	$(TCCCOMP) -okeydefg2 -DCOMBI keydefgr.h
	$(TLIB) keydef.lib -+ keydefg2.obj

# GERMAN+COMBI+STANDARD

keystdg2.obj: keydefgr.h  mkeyb.h
	$(TCCCOMP) -okeystdg2 -DSTANDARD -DCOMBI keydefgr.h
	$(TLIB) keydef.lib -+ keystdg2.obj

keydefsp.obj: keydefsp.h  mkeyb.h
	$(TCCCOMP) keydefsp.h
	$(TLIB) keydef.lib -+ keydefsp.obj

keydefru.obj: keydefru.h  mkeyb.h
	$(TCCCOMP) keydefru.h
	$(TLIB) keydef.lib -+ keydefru.obj

keydefdk.obj: keydefdk.h  mkeyb.h
	$(TCCCOMP) keydefdk.h
	$(TLIB) keydef.lib -+ keydefdk.obj

keydefit.obj: keydefit.h  mkeyb.h
	$(TCCCOMP) keydefit.h
	$(TLIB) keydef.lib -+ keydefit.obj

keystdit.obj: keydefit.h  mkeyb.h
	$(TCCCOMP) -okeystdit -DSTANDARD keydefit.h
	$(TLIB) keydef.lib -+ keystdit.obj

keydefla.obj: keydefla.h  mkeyb.h
	$(TCCCOMP) keydefla.h
	$(TLIB) keydef.lib -+ keydefla.obj

keydefnl.obj: keydefnl.h  mkeyb.h
	$(TCCCOMP) keydefnl.h
	$(TLIB) keydef.lib -+ keydefnl.obj

keydefno.obj: keydefno.h  mkeyb.h
	$(TCCCOMP) keydefno.h
	$(TLIB) keydef.lib -+ keydefno.obj

keydefpl.obj: keydefpl.h  mkeyb.h
	$(TCCCOMP) keydefpl.h
	$(TLIB) keydef.lib -+ keydefpl.obj

keydefpo.obj: keydefpo.h  mkeyb.h
	$(TCCCOMP) keydefpo.h
	$(TLIB) keydef.lib -+ keydefpo.obj

keydefsf.obj: keydefsf.h  mkeyb.h
	$(TCCCOMP) keydefsf.h
	$(TLIB) keydef.lib -+ keydefsf.obj

keydefsg.obj: keydefsg.h  mkeyb.h
	$(TCCCOMP) keydefsg.h
	$(TLIB) keydef.lib -+ keydefsg.obj

keydefsu.obj: keydefsu.h  mkeyb.h
	$(TCCCOMP) keydefsu.h
	$(TLIB) keydef.lib -+ keydefsu.obj

keydefsv.obj: keydefsv.h  mkeyb.h
	$(TCCCOMP) keydefsv.h
	$(TLIB) keydef.lib -+ keydefsv.obj

keydefuk.obj: keydefuk.h  mkeyb.h
	$(TCCCOMP) keydefuk.h
	$(TLIB) keydef.lib -+ keydefuk.obj

keydefbr.obj: keydefbr.h  mkeyb.h
	$(TCCCOMP) keydefbr.h
	$(TLIB) keydef.lib -+ keydefbr.obj

keydefbx.obj: keydefbx.h  mkeyb.h
	$(TCCCOMP) keydefbx.h
	$(TLIB) keydef.lib -+ keydefbx.obj

keydeffr.obj: keydeffr.h  mkeyb.h
	$(TCCCOMP) keydeffr.h
	$(TLIB) keydef.lib -+ keydeffr.obj

keydefhe.obj: keydefhe.h  mkeyb.h
	$(TCCCOMP) keydefhe.h
	$(TLIB) keydef.lib -+ keydefhe.obj

keydefbe.obj: keydefbe.h  mkeyb.h
	$(TCCCOMP) keydefbe.h
	$(TLIB) keydef.lib -+ keydefbe.obj

keydefbg.obj: keydefbg.h  mkeyb.h
	$(TCCCOMP) keydefbg.h
	$(TLIB) keydef.lib -+ keydefbg.obj

keydefbp.obj: keydefbp.h  mkeyb.h
	$(TCCCOMP) keydefbp.h
	$(TLIB) keydef.lib -+ keydefbp.obj

keydefsl.obj: keydefsl.h  mkeyb.h
	$(TCCCOMP) keydefsl.h
	$(TLIB) keydef.lib -+ keydefsl.obj

keydefux.obj: keydefux.h  mkeyb.h
	$(TCCCOMP) keydefux.h
	$(TLIB) keydef.lib -+ keydefux.obj

keydeftr.obj: keydeftr.h  mkeyb.h
	$(TCCCOMP) keydeftr.h
	$(TLIB) keydef.lib -+ keydeftr.obj

keydeftf.obj: keydeftf.h  mkeyb.h
	$(TCCCOMP) keydeftf.h
	$(TLIB) keydef.lib -+ keydeftf.obj

#mkeybGRc.exe: mkeyb.c keydefGR.h $(combidepends)
#	$(TCCLINK) -emkeybGRc -DLANG_GR -DCOMBI mKEYB.c $(combidepends)
#	$(XUPX) mkeybGRc.exe

# ############## generic ##########################
#
# for all languages same:
#

#
#assembly stub
#
mkeybA.obj: mkeybA.ASM
	$(TASM) /mx /dMY_INSTALL_SIGNATURE=$(INST_SIG) /dMY_VERSION_SIGNATURE=$(VERSION) mKEYBA.asm

#
# resident part
#

mkeybr.obj: mkeybr.c
	$(TCCCOMP) -mt    -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    mKEYBr.c

mkeybr.asm: mkeybr.c
	$(TCCCOMP) -mt -S -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    mKEYBr.c

#
# resident part with combi
#
mkeybrC.obj: mkeybr.c
	$(TCCCOMP) -mt    -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DCOMBI -omkeybrC mKEYBr.c

mkeybrC.asm: mkeybr.c
	$(TCCCOMP) -mt -S -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DCOMBI -omkeybrC mKEYBr.c

#
# FASTSWITCH resident part without ALTGREY, REPLACESCAN, DECIMALDINGSBUMS
# The right Ctrl toggles between native QWERTY and national keyboard
#
mkeybrf.obj: mkeybr.c
	$(TCCCOMP) -mt    -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DFASTSWITCH -omkeybrF mKEYBr.c

mkeybrf.asm: mkeybr.c
	$(TCCCOMP) -mt -S -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DFASTSWITCH -omkeybrF mKEYBr.c

#
# resident part for 83 keys "standard" keyboards
#
mkeybrS.obj: mkeybr.c
	$(TCCCOMP) -mt    -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DSTANDARD -omkeybrS mKEYBr.c

mkeybrS.asm: mkeybr.c
	$(TCCCOMP) -mt -S -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DSTANDARD -omkeybrS mKEYBr.c

#
# resident part for 83 keys "standard" keyboards with COMBI
#
mkeybrSC.obj: mkeybr.c
	$(TCCCOMP) -mt    -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DSTD_FULL -omkeybrSC mKEYBr.c

mkeybrSC.asm: mkeybr.c
	$(TCCCOMP) -mt -S -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    -DSTD_FULL -omkeybrSC mKEYBr.c

prf.obj: prf.c
	$(TCCCOMP) -DFORSYS prf.c

sscani.obj: sscani.c
	$(TCCCOMP) sscani.c

#useful when debugging/analysing code
mkeyb.asm: mkeyb.c mkeyb.h
	$(TCCCOMP) -S mKEYB.c

# Pack executable and create zip file for release
release:
	-$(PACK) mkeyb.exe
	$(ZIP) $(ZIPFILE) *.exe *.txt *.md

# copy driver to INSTALLDIR
install:
	xcopy mkeyb.exe $(INSTALLDIR)

# cleanup
clean:
	del /eq *.obj
	del /eq *.lib
	del /eq *.bak
	del /eq *.map
	del /eq mkeyb.asm
	del /eq mkeybr.asm
	del /eq mkeybrc.asm
	del /eq mkeybrf.asm
	del /eq mkeybrs.asm
	del /eq mkeybrsc.asm

# ############## end generic ##########################

