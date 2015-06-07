LIBPATH  = ../../lib/
SYSPATH  = ../../sys/

MAKE     = make -r
NASK     = wine ../../../z_tools/nask.exe
CC1      = wine ../../../z_tools/cc1.exe -I../../../z_tools/haribote/ -I../../ -Os -Wall -quiet
GAS2NASK = wine ../../../z_tools/gas2nask.exe -a
OBJ2BIM  = wine ../../../z_tools/obj2bim.exe
MAKEFONT = wine ../../../z_tools/makefont.exe
BIN2OBJ  = wine ../../../z_tools/bin2obj.exe
BIM2HRB  = wine ../../../z_tools/bim2hrb.exe
RULEFILE = ../Makefile.rule
EDIMG    = wine ../../../z_tools/edimg.exe
IMGTOL   = wine ../../../z_tools/imgtol.com
GOLIB    = wine ../../../z_tools/golib00.exe 
COPY     = cp
DEL      = rm

# 默认动作

default :
	$(MAKE) $(APP).hrb

# 文件生成规则

$(APP).bim : $(APP).obj $(LIBPATH)apilib.lib Makefile ../Makefile.app
	$(OBJ2BIM) @$(RULEFILE) out:$(APP).bim map:$(APP).map stack:$(STACK) \
		$(APP).obj $(LIBPATH)apilib.lib

$(APP).hrb : $(APP).bim Makefile ../Makefile.app
	$(BIM2HRB) $(APP).bim $(APP).hrb $(MALLOC)

pripara.img : ../../sys/ipl10.bin ../../sys/pripara.sys $(APP).hrb \
		Makefile ../Makefile.app
	$(EDIMG)   imgin:../../../z_tools/fdimg0at.tek \
		wbinimg src:../../sys/ipl10.bin len:512 from:0 to:0 \
		copy from:../sys/pripara.sys to:@: \
		copy from:$(APP).hrb to:@: \
		imgout:pripara.img

# 一般规则

%.gas : %.c ../../apilib.h Makefile ../Makefile.app
	$(CC1) -o $*.gas $*.c

%.nas : %.gas Makefile ../Makefile.app
	$(GAS2NASK) $*.gas $*.nas

%.obj : %.nas Makefile ../Makefile.app
	$(NASK) $*.nas $*.obj $*.lst

# 各个命令

run :
	$(MAKE) pripara.img
	$(COPY) pripara.img ..\..\..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../../../z_tools/qemu

full :
	$(MAKE) -C $(LIBPATH)
	$(MAKE) $(APP).hrb

run_full :
	$(MAKE) -C $(LIBPATH)
	$(MAKE) -C ../../sys
	$(MAKE) run

clean :
	-$(DEL) *.lst
	-$(DEL) *.obj
	-$(DEL) *.map
	-$(DEL) *.bim
	-$(DEL) $(APP).hrb
	-$(DEL) pripara.img

src_only :
	$(MAKE) clean
	-$(DEL) $(APP).hrb
