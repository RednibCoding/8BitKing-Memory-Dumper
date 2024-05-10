# Copyright (C) 2024 Nikita Burnashev

# Permission to use, copy, modify, and/or distribute this software
# for any purpose with or without fee is hereby granted.

# THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND!

exec_hc = 0xafc08dd4	# bootloader's exec()

ofs_os = 0x1e0 - 0x90	# TDS2 context switch headroom
ofs_id = 0x1e0 + 0x14	# setup_task_stack reserve is 0x20 bytes

heaplim = 0x83159000	# from 8BitKing RAMSIZE

.section .text.unlikely, "x", @progbits
.set noreorder
.globl __start
__start:
	lw	$v1, ofs_id($a0)	# read an id word from the stack

	li	$ra, 4 + heaplim + ofs_id	# last possible branch location
1:	addiu	$ra, 4 - 0x1000	# memory allocation BLOCKSIZE
	lw	$v0, -8($ra)	# negative offset to possible id to avoid NUL
	bne	$v0, $v1, 1b	# scan and branch backwards for the same reason
	addiu	$ra, -4	# BLOCKSIZE has NUL, must adjust twice
.set mips32r2
	jr.hb	$ra	# to the code immediately following the id word
	addiu	$a0, $ra, -(4 + ofs_id)	# start address of this larger buffer

.fill (__start + ofs_os - .) / 4, 4, exec_hc
.org   __start + ofs_os	# error when code too long
.fill (ofs_id - ofs_os) / 4, 4, exec_hc

.string	"y2l"	# id word: must be 3 characters + string terminator
# end of a buffer overflow left in stack by sscanf($a0, "%s ...
	b	relocate
	nop
