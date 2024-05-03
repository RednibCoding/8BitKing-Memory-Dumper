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