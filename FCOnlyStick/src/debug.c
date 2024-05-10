/* Copyright (C) 2024 Nikita Burnashev

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted.

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND! */

#include "tui.h"

void die(const char *msg) // !! MUST NOT use ANY library calls !!
{
	asm volatile("mtc0 %0, $12; nop; nop" : : "r"(0x10000000)); // Status CU0
	tui_open(BLUE);
	tui_add(2, 1, WHITE, BLUE, msg);
	do {
	} while (1);
}

void hex(char *s, unsigned v)
{
	static const char tab[] = "0123456789abcdef___";
	int i;

	for (i = 0; i < 8; i++) {
		s[7 - i] = tab[v & 15];
		v >>= 4;
	}
	s[8] = 0;
}

void hook_assert(void)
{
	unsigned ra;
	static const char err[] = "assert failed at ";
	const char *pe = err;
	char msg[99], *pm = msg;

	asm volatile ("move %0, $ra" : "=r" (ra));
	while (*pe) *pm++ = *pe++;
	hex(pm, ra);
	die(msg);
}

void hook_except(void)
{
	unsigned code, epc;
	static const char err[] = "exception \0 at ";
	const char *pe = err;
	char msg[99], *pm = msg;

	asm volatile ("srl %0, $k1, 2" : "=r" (code)); // masked Cause
	asm volatile ("mfc0 %0, $14; nop; nop" : "=r" (epc));
	while (*pe) *pm++ = *pe++;
	if (code >= 10) *pm++ = code / 10 + '0';
	*pm++ = code % 10 + '0';
	pe++;
	while (*pe) *pm++ = *pe++;
	hex(pm, epc);
	die(msg);
}
