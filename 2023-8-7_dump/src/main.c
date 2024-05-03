/* Copyright (C) 2024 Nikita Burnashev

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted.

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND! */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stockfw.h"
#include "tui.h"
#include "debug.h"
#include "patch.h"

#define SZ (2048 * 1024)

static void spi_read_h1512(unsigned char *buf, unsigned adr, unsigned len)
{
	const unsigned char *rom = (void *)0xafc00000;

	rom += adr;
	while (len--) *buf++ = *rom++;
}

extern unsigned _ftext;

static void main_task(void)
{
	static const char ver[] = TARGET, err[] = TARGET " required! This is ";
	const char *pv = ver, *pe = err;
	char msg[99], *pm = msg;
	static const char *dump = "/mnt/sda1/dump.bin";
	FILE *pf;
	void *pbuf;

	debug_hooks();

	// OS essentials killed by exec()
	asm volatile("mtc0 %0, $12; nop; nop" : : "r"(0x10400000)); // Status CU0 BEV
	asm volatile("mtc0 %0, $15, 1; nop; nop" : : "r"(0x80002180)); // EBase
	asm volatile("mtc0 %0, $12; nop; nop" : : "r"(0x10008801)); // CU0 IM7,3 IE

	while (*pe) *pm++ = *pe++; // can't call strcpy at this point
	spi_read_h1512(pm, 0x20030, 11); // maincode chunk time yyyy-mm-dd\0
	while (*pv && *pm++ == *pv++) ; // likewise for strcmp
	if (*pv) die(msg);

	RAMSIZE = (unsigned)&_ftext;

	s__s_Resources_Foldername_ini[25] = 'f';
	s__s_Resources_Foldername_ini[26] = 'c';

	pbuf = malloc(SZ);
	memcpy(pbuf, (void *) 0xafc00000, SZ);

	pf = fopen(dump, "wb");
	fwrite(pbuf, 1, SZ, pf);
	fclose(pf);
	fs_sync(dump);

	free(pbuf);

	sprintf(msg, "Grab the dump.bin");
	die(msg);
}

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