TOOLPATH = ../../z_tools/
BIM2BIN  = $(TOOLPATH)bim2bin.exe

default:
	$(MAKE) all

all: unifont.fnt

hex2bin:
	$(CC) hex2bin.c -o hex2bin

unifont.fnt: unifont.bin
	$(BIM2BIN) -osacmp in:unifont.bin out:unifont.fnt -tek5

unifont.bin: hex2bin
	hex2bin unifont-7.0.06.hex unifont.bin

clean:
	$(RM) hex2bin

src_only:
	$(RM) hex2bin
	$(RM) unifont.bin
	$(RM) unifont.fnt
