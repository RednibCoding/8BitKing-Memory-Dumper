/* Copyright (C) 2024 Nikita Burnashev

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted.

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND! */

#include <stddef.h>

void _flush_cache(void *buf, size_t sz, int flags)
{
	unsigned idx;
	// Index_Writeback_Inv_D
	for (idx = 0x80000000; idx <= 0x80004000; idx += 16) // all of D-cache
		asm volatile("cache 1, 0(%0); cache 1, 0(%0)" : : "r"(idx));
	asm volatile("sync 0; nop; nop");
	// Index_Invalidate_I
	for (idx = 0x80000000; idx <= 0x80004000; idx += 16) // all of I-cache
		asm volatile("cache 0, 0(%0); cache 0, 0(%0)" : : "r"(idx));
	asm volatile("nop; nop; nop; nop; nop"); // ehb may be nop on this core
}
