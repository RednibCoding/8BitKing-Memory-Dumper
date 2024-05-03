/* Copyright (C) 2024 Nikita Burnashev

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted.

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND! */

#include <stdio.h>
#include <stdarg.h>
#include "tui.h"

void die(const char *msg) // !! MUST NOT use ANY library calls !!
{
	asm volatile("mtc0 %0, $12; nop; nop" : : "r"(0x10000000)); // Status CU0
	tui_open(BLUE);
	tui_add(2, 1, WHITE, BLUE, msg);
	do {
	} while (1);
}

void hook_assert(void)
{
	unsigned ra;
	char msg[99];

	asm volatile ("move %0, $ra" : "=r" (ra));
	sprintf(msg, "assert failed at %x", ra);
	die(msg);
}

void hook_except(void)
{
	unsigned code, epc;
	char msg[99];

	asm volatile ("srl %0, $k1, 2" : "=r" (code)); // masked Cause
	asm volatile ("mfc0 %0, $14; nop; nop" : "=r" (epc));
	sprintf(msg, "exception %u at %x", code, epc);
	die(msg);
}
