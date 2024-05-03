/* Copyright (C) 2024 Nikita Burnashev

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted.

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND! */

#include "debug.h"

void debug_hooks(void)
{
	*(unsigned *)0xa00030d4 = 2 << 26 | (unsigned)&hook_assert >> 2 & ((1 << 26) - 1);
	*(unsigned *)0xa001b560 = 2 << 26 | (unsigned)&hook_except >> 2 & ((1 << 26) - 1);
}

inline static void patch_jal(unsigned addr, void *pf)
{
	*(unsigned *)addr = 3 << 26 | (unsigned)pf >> 2 & ((1 << 26) - 1);
}

inline static void patch_lui_addui(unsigned lui, unsigned addui, void *pf)
{
	unsigned af = (unsigned)pf;
	*(unsigned short *)lui = (af >> 16) + (af & 0x8000 ? 1 : 0);
	*(unsigned short *)addui = af & 0xffff;
}

void patch_music_rate(void)
{
	// run_snd_task_mix, for correct music rate (actually lui_ori)
	patch_lui_addui(0xa01d650c, 0xa01d6510, (void *)990000);
}
