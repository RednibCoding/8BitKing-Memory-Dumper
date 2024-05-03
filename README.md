## Rom dumping for the 8BitKing Game stick

## Dumping the rom

1. Put the `Resource` dir onto the SD card.
2. Put the SD card back into the 8BitKing stick and boot it
3. Wait until a blue screen appears with the message: Grap the dump.bin

Linux:

4. `$ tail -c +131201 dump.bin | unlzma > maincode` to extract and uncompress the raw dump of the rom.

Windows:

4. You could use Git Bash for `tail -c +131201 dump.bin > temp.bin` and 7zip for the uncompression: `7z e temp.bin -omaincode`. Or you could use wsl but you have to install `xz-utils` for the uncompression: `sudo apt install xz-utils`. Then you can follow step 1-4 for linux.

>Note: An error that the output file `maincode` is corrupted is to be expected because `maincode` is a `bisrv.asd` (bios) but w/o 512 bytes LCFG header. It's loaded to address `0x80000200` and executed from this address (_start is actually lower so it follows a string of `nops`)

## How to compile src
There's a link to the toolchain in the Makefile. Just unpacked it to /opt on your linux system then just run `make` whithin the src directory, it creates Resources/Foldername.ini with the exploit and all the code.

The toolchain has been reported to work in WSL2, too, so you don't really have to go fully Linux.

## Files
Everything for the dumpers code is in `main.c`, it's quite simple really. Other source files are supplementary.

The RTOS on this device does not support apps or libraries in any way and was designed as one huge statically linked image.

So `Foldername.ini` is quite the same, just relocated out of reach.

New `Foldername.ini` is, obviously, the executable body. It's relocated to the top of the memory in relocate function in `main.c` then main_task is run.

## The 8BitKing game stick
8BitKing is powered by HiChip Semi (HCSEMI) A210C https://en.hichiptech.com/product_1/19.html ([Datasheet](readme/HCSEMI_A210CBriefDatasheet200618.pdf))

| Feature         | Details                                     |
|-----------------|---------------------------------------------|
| CPU             | 800MHz                                      |
| DRAM            | ext. max. 256MB @800Mbps                    |
| Flash           | SPI Flash                                   |
| Video Decoder   | Multi-format @FHD 60FPS                     |
| Display         | HDMI_TX+VGA/CVBS                            |
| Video Input     | DVP/CCIR601/656                             |
| Audio           | Mono ADAC+I2S in+out/SPDIF out              |
| USB             | USB2.0x2                                    |
| SDIO            | SDIO2.0                                     |
| I2C/UART        | 3xPWM, 3xI2C+2xUart, 1xSARADC, IRRX         |
| Wi-Fi           | A210 Support                                |
| SW System       | RTOS                                        |
| Package         | eLQFP128                                    |
| Typical Products| Mobile screen sharing device, Same-screen mods, Game |


The main CPU is MIPS32-compatible (Release 1 only) running at 810 MHz, but it's bottlenecked heavily by the DDR2 due to lack of sensible caching (16K for instructions and 16K data, no L2 at all).
This CPU lacks an MMU, and is also bug-ridden, freezing on invalid memory accesses.