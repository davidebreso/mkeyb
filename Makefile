all: mkeyb.exe

INST_SIG=19309			# mKEYB fingerprint "mK"
VERSION=52				# version number
VERSION_STR=\"0.52\"		# version number text
ZIPFILE=mkeyb052.zip

WCC=wcc
WASM=wasm
TLIB=wlib
WLINK=wlink
#PACK=pklite.exe
PACK=upx --8086
ZIP=zip

WCCLINK=$(WLINK)
WCCCOMP=$(WCC) -s -os

INSTALLDIR=~/Dosbox/c_drive

depends=
resdep = mKEYBA.o mkeybrc.o mkeybr.o mkeybrf.o mkeybrs.o mkeybrsc.o
keydefs = &
	keydefdk.o &
	keydefGR.o &
	keystdGR.o &
	keydefG2.o &
	keystdG2.o &
	keydefIT.o &
	keystdIT.o &
	keydefLA.o &
	keydefNL.o &
	keydefno.o &
	keydefpl.o &
	keydefPO.o &
	keydefru.o &
	keydefSF.o &
	keydefSG.o &
	keydefSP.o &
	keydefSU.o &
	keydefSV.o &
	keydefuk.o &
	keydefBR.o &
	keydefBX.o &
	keydefFR.o &
	keydefHE.o &
	keydefBE.o &
	keydefBG.o &
	keydefBP.o &
	keydefSL.o &
	keydefUX.o &
	keydefTR.o &
	keydefTF.o &

#
# MAIN EXECUTABLE
#
mkeyb.exe: mkeyb.o  $(resdep) $(depends) $(keydefs)
	$(WCCLINK) system dos file {mKEYB.o $(resdep) $(depends) keydef.lib} option map=mkeyb name mkeyb
	$(PACK) mkeyb.exe

mkeyb.o: mkeyb.c mkeyb.h
	$(WCCCOMP) -DMY_INSTALL_SIGNATURE=$(INST_SIG) -DMY_VERSION_SIGNATURE=$(VERSION) -DMY_VERSION_TEXT=$(VERSION_STR) mKEYB.c

# GERMAN

keydefgr.o:  keydefgr.h  mkeyb.h
	$(WCCCOMP) keydefgr.h
	$(TLIB) keydef.lib -+keydefgr.o

# GERMAN+STANDARD

keystdgr.o:  keydefgr.h  mkeyb.h
	$(WCCCOMP) -fo=keystdgr -DSTANDARD keydefgr.h
	$(TLIB) keydef.lib -+keystdgr.o

# GERMAN+COMBI ( '`^ + AEIOU )

keydefg2.o: keydefgr.h  mkeyb.h
	$(WCCCOMP) -fo=keydefg2 -DCOMBI keydefgr.h
	$(TLIB) keydef.lib -+keydefg2.o

# GERMAN+COMBI+STANDARD

keystdg2.o: keydefgr.h  mkeyb.h
	$(WCCCOMP) -fo=keystdg2 -DSTANDARD -DCOMBI keydefgr.h
	$(TLIB) keydef.lib -+keystdg2.o

keydefsp.o: keydefsp.h  mkeyb.h
	$(WCCCOMP) keydefsp.h
	$(TLIB) keydef.lib -+keydefsp.o

keydefru.o: keydefru.h  mkeyb.h
	$(WCCCOMP) keydefru.h
	$(TLIB) keydef.lib -+keydefru.o

keydefdk.o: keydefdk.h  mkeyb.h
	$(WCCCOMP) keydefdk.h
	$(TLIB) keydef.lib -+keydefdk.o

keydefit.o: keydefit.h  mkeyb.h
	$(WCCCOMP) keydefit.h
	$(TLIB) keydef.lib -+keydefit.o

keystdit.o: keydefit.h  mkeyb.h
	$(WCCCOMP) -fo=keystdit -DSTANDARD keydefit.h
	$(TLIB) keydef.lib -+keystdit.o

keydefla.o: keydefla.h  mkeyb.h
	$(WCCCOMP) keydefla.h
	$(TLIB) keydef.lib -+keydefla.o

keydefnl.o: keydefnl.h  mkeyb.h
	$(WCCCOMP) keydefnl.h
	$(TLIB) keydef.lib -+keydefnl.o

keydefno.o: keydefno.h  mkeyb.h
	$(WCCCOMP) keydefno.h
	$(TLIB) keydef.lib -+keydefno.o

keydefpl.o: keydefpl.h  mkeyb.h
	$(WCCCOMP) keydefpl.h
	$(TLIB) keydef.lib -+keydefpl.o

keydefpo.o: keydefpo.h  mkeyb.h
	$(WCCCOMP) keydefpo.h
	$(TLIB) keydef.lib -+keydefpo.o

keydefsf.o: keydefsf.h  mkeyb.h
	$(WCCCOMP) keydefsf.h
	$(TLIB) keydef.lib -+keydefsf.o

keydefsg.o: keydefsg.h  mkeyb.h
	$(WCCCOMP) keydefsg.h
	$(TLIB) keydef.lib -+keydefsg.o

keydefsu.o: keydefsu.h  mkeyb.h
	$(WCCCOMP) keydefsu.h
	$(TLIB) keydef.lib -+keydefsu.o

keydefsv.o: keydefsv.h  mkeyb.h
	$(WCCCOMP) keydefsv.h
	$(TLIB) keydef.lib -+keydefsv.o

keydefuk.o: keydefuk.h  mkeyb.h
	$(WCCCOMP) keydefuk.h
	$(TLIB) keydef.lib -+keydefuk.o

keydefbr.o: keydefbr.h  mkeyb.h
	$(WCCCOMP) keydefbr.h
	$(TLIB) keydef.lib -+keydefbr.o

keydefbx.o: keydefbx.h  mkeyb.h
	$(WCCCOMP) keydefbx.h
	$(TLIB) keydef.lib -+keydefbx.o

keydeffr.o: keydeffr.h  mkeyb.h
	$(WCCCOMP) keydeffr.h
	$(TLIB) keydef.lib -+keydeffr.o

keydefhe.o: keydefhe.h  mkeyb.h
	$(WCCCOMP) keydefhe.h
	$(TLIB) keydef.lib -+keydefhe.o

keydefbe.o: keydefbe.h  mkeyb.h
	$(WCCCOMP) keydefbe.h
	$(TLIB) keydef.lib -+keydefbe.o

keydefbg.o: keydefbg.h  mkeyb.h
	$(WCCCOMP) keydefbg.h
	$(TLIB) keydef.lib -+keydefbg.o

keydefbp.o: keydefbp.h  mkeyb.h
	$(WCCCOMP) keydefbp.h
	$(TLIB) keydef.lib -+keydefbp.o

keydefsl.o: keydefsl.h  mkeyb.h
	$(WCCCOMP) keydefsl.h
	$(TLIB) keydef.lib -+keydefsl.o

keydefux.o: keydefux.h  mkeyb.h
	$(WCCCOMP) keydefux.h
	$(TLIB) keydef.lib -+keydefux.o

keydeftr.o: keydeftr.h  mkeyb.h
	$(WCCCOMP) keydeftr.h
	$(TLIB) keydef.lib -+keydeftr.o

keydeftf.o: keydeftf.h  mkeyb.h
	$(WCCCOMP) keydeftf.h
	$(TLIB) keydef.lib -+keydeftf.o

#mkeybGRc.exe: mkeyb.c keydefGR.h $(combidepends)
#	$(WCCLINK) -emkeybGRc -DLANG_GR -DCOMBI mKEYB.c $(combidepends)
#	$(XUPX) mkeybGRc.exe

# ############## generic ##########################
#
# for all languages same:
#

#
#assembly stub
#
mkeybA.o: mkeybA.ASM
	$(WASM) -dMY_INSTALL_SIGNATURE=$(INST_SIG) -dMY_VERSION_SIGNATURE=$(VERSION) mKEYBA.asm

#
# resident part
#

mkeybr.o: mkeybr.c
	$(WCCCOMP) -ms -nd=I mKEYBr.c

mkeybr.asm: mkeybr.c
	$(WCCCOMP) -ms -S     mKEYBr.c

#
# resident part with combi
#
mkeybrC.o: mkeybr.c
	$(WCCCOMP) -ms -nd=I -DCOMBI -fo=mkeybrC mKEYBr.c

mkeybrC.asm: mkeybr.c
	$(WCCCOMP) -ms -S  -nd=I   -DCOMBI -fo=mkeybrC mKEYBr.c

#
# FASTSWITCH resident part without ALTGREY, REPLACESCAN, DECIMALDINGSBUMS
# The right Ctrl toggles between native QWERTY and national keyboard
#
mkeybrf.o: mkeybr.c
	$(WCCCOMP) -ms  -nd=I      -DFASTSWITCH -fo=mkeybrF mKEYBr.c

mkeybrf.asm: mkeybr.c
	$(WCCCOMP) -ms -S  -nd=I   -DFASTSWITCH -fo=mkeybrF mKEYBr.c

#
# resident part for 83 keys "standard" keyboards
#
mkeybrS.o: mkeybr.c
	$(WCCCOMP) -ms   -nd=I     -DSTANDARD -fo=mkeybrS mKEYBr.c

mkeybrS.asm: mkeybr.c
	$(WCCCOMP) -ms -S  -nd=I   -DSTANDARD -fo=mkeybrS mKEYBr.c

#
# resident part for 83 keys "standard" keyboards with COMBI
#
mkeybrSC.o: mkeybr.c
	$(WCCCOMP) -ms   -nd=I     -DSTD_FULL -fo=mkeybrSC mKEYBr.c

mkeybrSC.asm: mkeybr.c
	$(WCCCOMP) -ms -S  -nd=I   -DSTD_FULL -fo=mkeybrSC mKEYBr.c

prf.o: prf.c
	$(WCCCOMP) -DFORSYS prf.c

sscani.o: sscani.c
	$(WCCCOMP) sscani.c

#useful when debugging/analysing code
mkeyb.asm: mkeyb.c mkeyb.h
	$(WCCCOMP) -S mKEYB.c

# Create zip file for release
release
	$(ZIP) $(ZIPFILE) *.exe *.txt *.md

# copy driver to INSTALLDIR
install
	cp mkeyb.exe $(INSTALLDIR)

# cleanup
clean
	rm -f *.o
	rm -f *.lib
	rm -f *.bak
	rm -f *.map
	rm -f mkeyb.asm
	rm -f mkeybr.asm
	rm -f mkeybrc.asm
	rm -f mkeybrf.asm
	rm -f mkeybrs.asm
	rm -f mkeybrsc.asm
	

# ############## end generic ##########################

