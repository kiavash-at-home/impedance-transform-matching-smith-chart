.AUTODEPEND

#		*Translator Definitions*
CC = tcc +SMITH.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = D:\TC\LIB
INCLUDEPATH = D:\TC\INCLUDE


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 main.obj \
 menu.obj \
 stuble.obj

#		*Explicit Rules*
smith.exe: smith.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/L$(LIBPATH) @&&|
c0s.obj+
main.obj+
menu.obj+
stuble.obj
smith
		# no map file
graphics.lib+
emu.lib+
maths.lib+
cs.lib
|


#		*Individual File Dependencies*
main.obj: smith.cfg main.cpp 

menu.obj: smith.cfg menu.cpp 

stuble.obj: smith.cfg stuble.cpp 

#		*Compiler Configuration File*
smith.cfg: smith.mak
  copy &&|
-v
-vi-
-w-ret
-w-nci
-w-inl
-wpin
-wamb
-wamp
-w-par
-wasm
-wcln
-w-cpt
-wdef
-w-dup
-w-pia
-wsig
-wnod
-w-ill
-w-sus
-wstv
-wucp
-wuse
-w-ext
-w-ias
-w-ibc
-w-pre
-w-nst
-I$(INCLUDEPATH)
-L$(LIBPATH)
| smith.cfg


