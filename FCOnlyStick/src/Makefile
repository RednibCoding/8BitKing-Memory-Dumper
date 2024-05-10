TARGET=2023-7-20
ADDR=0x82f00000
OUT=../Resources/Foldername

# drive.google.com/u/0/uc?id=1MpsE__0Ra_BW3GGMfxvULeX5XeLQDSZR
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
$(OUT).out: init.o main.o tui.o debug.o
	$(MIPS)-ld $(LDFLAGS) -Ttext=$(ADDR) -Map $(OUT).map -o $@ \
		--start-group $(LIBS) $^ --end-group
$(OUT).ini: $(OUT).out
	$(MIPS)-objcopy -O binary -R .MIPS.abiflags -R .note.gnu.build-id $(OUT).out $@
# NUL; HT; LF, VT, FF, CR and space characters are forbidden in the stack
	@! od -N 0x150 -A x -t x1 $@ | grep -E ' 0[09a-d]| 20'
