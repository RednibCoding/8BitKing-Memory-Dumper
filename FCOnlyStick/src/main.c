/* Copyright (C) 2024 Nikita Burnashev

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted.

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND! */

#include "debug.h"

static void spi_read_h1512(unsigned char *buf, unsigned adr, unsigned len)
{
	const unsigned char *rom = (void *)0xafc00000;

	rom += adr;
	while (len--) *buf++ = *rom++;
}

static void check_version(const char *pv, const char *pe)
{
	char msg[99], *pm = msg;

	while (*pe) *pm++ = *pe++; // can't call strcpy at this point
	spi_read_h1512(pm, 0x20030, 11); // maincode chunk time yyyy-mm-dd\0
	while (*pv && *pm++ == *pv++) ; // likewise for strcmp
	if (*pv) die(msg);
}

static int (* const fs_sync)(const char *path)
	= (void *) 0x80102160;
static int (* const fs_open)(const char *path, int oflag, int perms)
	= (void *) 0x80102288;
static int (* const fs_write)(int fd, const void *buf, unsigned nbyte)
	= (void *) 0x801027a4;
static int (* const fs_close)(int fd)
	= (void *) 0x80102a04;

static void main_task(void)
{
	static unsigned char buf[2048 * 1024];
	static const char *dump = "/mnt/sda1/dump.bin";
	int fd;

	check_version(TARGET, TARGET " required! This is ");

	*(unsigned *)0xa00030d4 = 2 << 26 | (unsigned)&hook_assert >> 2 & ((1 << 26) - 1);
	*(unsigned *)0xa001b560 = 2 << 26 | (unsigned)&hook_except >> 2 & ((1 << 26) - 1);

	// OS essentials killed by exec()
	asm volatile("mtc0 %0, $12; nop; nop" : : "r"(0x10400000)); // Status CU0 BEV
	asm volatile("mtc0 %0, $15, 1; nop; nop" : : "r"(0x80002180)); // EBase
	asm volatile("mtc0 %0, $12; nop; nop" : : "r"(0x10008801)); // CU0 IM7,3 IE

	if (*(unsigned *)fs_open  != 0x27bdffd8) die("fs_open check failed");
	if (*(unsigned *)fs_write != 0x27bdffd0) die("fs_write check failed");
	if (*(unsigned *)fs_close != 0x27bdffe8) die("fs_close check failed");
	if (*(unsigned *)fs_sync  != 0x27bdffe0) die("fs_sync check failed");

	spi_read_h1512(buf, 0, sizeof buf);

	fd = fs_open(dump, 0x301, 0777); // O_CREAT | O_TRUNC | O_WRONLY
	fs_write(fd, buf, sizeof buf);
	fs_close(fd);
	fs_sync(dump);

	die("Grab the dump.bin");
}

extern unsigned _ftext;

void relocate(unsigned *src) // !! must be position independent !!
{
	extern unsigned _edata, _end;
	unsigned idx, *dst = &_ftext;

	while (dst < &_edata) { // .text .rodata .data
		unsigned a = *src++, b = *src++, c = *src++, d = *src++;
		*dst++ = a; *dst++ = b; *dst++ = c; *dst++ = d;
	}
	while (dst < &_end) { // .bss
		*dst++ = 0; *dst++ = 0; *dst++ = 0; *dst++ = 0;
	}
	// Index_Writeback_Inv_D
	for (idx = 0x80000000; idx <= 0x80004000; idx += 16) // all of D-cache
		asm volatile("cache 1, 0(%0); cache 1, 0(%0)" : : "r"(idx));
	asm volatile("sync 0; nop; nop");
	// Index_Invalidate_I
	for (idx = 0x80000000; idx <= 0x80004000; idx += 16) // all of I-cache
		asm volatile("cache 0, 0(%0); cache 0, 0(%0)" : : "r"(idx));
	asm volatile("nop; nop; nop; nop; nop"); // ehb may be nop on this core
	asm volatile("jr %0; nop" : : "r"(&main_task));
}