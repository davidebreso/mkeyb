all: mkeyb.exe

TCCLINK=$(TCC) -lm -O -Z -g1
TCCCOMP=$(TCC) -c  -O -Z -g1 -a-

#
# each language gets 2 binaries:
# the miniminimum 'mkeybXX.exe'
# and additional  'mkeybXXc.exe' with additional COMBI characters
#

depends=prf.obj
resdep = mKEYBA.obj mkeybrc.obj mkeybr.obj mkeybrf.obj
keydefs = \
	keydefdk.obj \
	keydefGR.obj \
	keydefG2.obj \
	keydefIT.obj \
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

#
# GERMAN
#
mkeyb.exe: mkeyb.obj  $(resdep) $(depends) $(keydefs)
	$(TCCLINK) mKEYB.obj $(resdep) $(depends) keydef.lib
	# $(XAPACK) mkeyb.exe mkeyb.exe
	# copy mkeyb.exe keyb.exe
	# del  mkeyb.exe

mkeyb.obj: mkeyb.c mkeyb.h
	$(TCCCOMP) mKEYB.c

keydefgr.obj:  keydefgr.h  mkeyb.h
	$(TCCCOMP) keydefgr.h
	$(TLIB) keydef.lib -+ keydefgr.obj

# GERMAN+COMBI ( '`^ + AEIOU )

keydefg2.obj: keydefgr.h  mkeyb.h
	$(TCCCOMP) -okeydefg2 -DCOMBI keydefgr.h
	$(TLIB) keydef.lib -+ keydefg2.obj

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
	$(XNASM) /mx mKEYBA.asm

#
# resident part
#

mkeybr.obj: mkeybr.c
	$(TCCCOMP) -mt    -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    mKEYBr.c

mkeybr.asm: mkeybr.c
	$(TCCCOMP) -mt -S -zAINIT -zCI_TEXT -zDIB -zRID -zTID -zPI_GR -zBIB -zGI_GR -zSI_GR    mKEYBr.c

#
# resident part with combiES
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


prf.obj: prf.c
	$(TCCCOMP) -DFORSYS prf.c

sscani.obj: sscani.c
	$(TCCCOMP) sscani.c


#useful when debugging/analysing code
mkeyb.asm: mkeyb.c mkeyb.h
	$(TCCCOMP) -S mKEYB.c

# cleanup
clean:
	del *.obj
	del *.lib
	del *.bak
	del *.exe
	del mkeyb.asm
	del mkeybr.asm
	del mkeybrc.asm
	del mkeybrf.asm

# ############## end generic ##########################
