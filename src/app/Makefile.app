TOOLPATH = ../../../z_tools/
INCPATH  = ../../../z_tools/haribote/
APILIBPATH   = ../../lib/
HARIBOTEPATH = ../../sys/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -I../../ -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
BIM2BIN  = $(TOOLPATH)bim2bin.exe
RULEFILE = ../Makefile.rule
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
GOLIB    = $(TOOLPATH)golib00.exe 
COPY     = copy
DEL      = del

# デフォルト動作

default :
	$(MAKE) $(APP).hrb

# ファイル生成規則

$(APP).bim : $(APP).obj $(APILIBPATH)apilib.lib Makefile ../Makefile.app
	$(OBJ2BIM) @$(RULEFILE) out:$(APP).bim map:$(APP).map stack:$(STACK) \
		$(APP).obj $(APILIBPATH)apilib.lib

# 一般規則

%.gas : %.c ../../apilib.h Makefile ../Makefile.app
	$(CC1) -o $*.gas $*.c

%.nas : %.gas Makefile ../Makefile.app
	$(GAS2NASK) $*.gas $*.nas

%.obj : %.nas Makefile ../Makefile.app
	$(NASK) $*.nas $*.obj $*.lst

%.org : %.bim Makefile ../Makefile.app
	$(BIM2HRB) $*.bim $*.org $(MALLOC)

%.hrb : %.org Makefile ../Makefile.app
	$(BIM2BIN) -osacmp in:$*.org out:$*.hrb

# コマンド

clean :
	-$(DEL) *.lst
	-$(DEL) *.obj
	-$(DEL) *.map
	-$(DEL) *.bim
	-$(DEL) *.org

src_only :
	$(MAKE) clean
	-$(DEL) $(APP).hrb