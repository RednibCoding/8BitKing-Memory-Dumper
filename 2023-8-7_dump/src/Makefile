TARGET=2023-8-7
ADDR=0x83130000
OUT=../Resources/Foldername

# drive.google.com/u/0/uc?id=1MpsE__0Ra_BW3GGMfxvULeX5XeLQDSZR
# https://mega.nz/file/i3B0zJhR#VeCfSG4vff8WnZn9_4gnzn2bFdKgA-1foZJw1A7ucHs
MIPS=/opt/mips32-mti-elf/2019.09-03-2/bin/mips-mti-elf

CFLAGS := -EL -Os -G0 -mips32 -msoft-float -mno-abicalls -fno-pic -ffreestanding
LDFLAGS := -EL -nostdlib -z max-page-size=32 --build-id

CFLAGS += -DTARGET=\"$(TARGET)\"

all: $(OUT).ini
.PHONY: all clean
clean:
	rm -f *.o *.a
#	rm -f $(OUT).out $(OUT).map $(OUT).ini

%.o: %.s
	$(MIPS)-gcc $(CFLAGS) -c $< -o $@
%.o: %.c
	$(MIPS)-gcc $(CFLAGS) -c $< -o $@
$(OUT).out: $(TARGET).ld init.o main.o patch_$(TARGET).o lib.o tui.o debug.o
	$(MIPS)-ld $(LDFLAGS) -Ttext=$(ADDR) -Map $(OUT).map -o $@ \
		--start-group $(LIBS) $^ --end-group
$(OUT).ini: $(OUT).out
	$(MIPS)-objcopy -O binary -R .MIPS.abiflags -R .note.gnu.build-id $(OUT).out $@
# NUL; HT; LF, VT, FF, CR and space characters are forbidden in the stack
	@! od -N 0x150 -A x -t x1 $@ | grep -E ' 0[09a-d]| 20'
