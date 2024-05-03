/* libc */
strcat	= 0x800655b4;
strncmp	= 0x80065650;
strncpy	= 0x80065728;
strchr	= 0x800657f8;
strrchr	= 0x80065888;
strstr	= 0x800658a8;
strcasecmp	= 0x800658fc;
strncasecmp	= 0x8006597c;
memchr	= 0x800659dc;
tolower	= 0x80065b58;
toupper	= 0x80065b78;
isalnum	= 0x80065b98;
isalpha	= 0x80065bb0;
isascii	= 0x80065bc8;
iscntrl	= 0x80065bd0;
isdigit	= 0x80065be8;
isgraph	= 0x80065c00;
islower	= 0x80065c18;
isprint	= 0x80065c30;
ispunct	= 0x80065c48;
isspace	= 0x80065c60;
isupper	= 0x80065c78;
isxdigit	= 0x80065c90;
toascii	= 0x80065ca8;
_tolower	= 0x80065cb0;
_toupper	= 0x80065cb8;
isnan	= 0x80065cf8;
isinf	= 0x80065d44;
strtol	= 0x80065d94;
strtoul	= 0x80065f84;

sbrk	= 0x800c0974;	/* TODO: exposing and using sbrk might be dangerous? */
malloc	= 0x800c0c34;
free	= 0x800c1844;
realloc	= 0x800c1908;
calloc	= 0x800c1bc0;
vsnprintf	= 0x800c3654;
sprintf	= 0x800c3708;
vprintf	= 0x800c37b0;
printf	= 0x800c37f0;
snprintf	= 0x800c3818;
vsprintf	= 0x800c3838;
memcpy	= 0x800c38f8;
memset	= 0x800c3b28;
memcmp	= 0x800c3c08;
memmove	= 0x800c3c6c;
strcpy	= 0x800c3d38;
strcmp	= 0x800c3d78;
strlen	= 0x800c3dbc;
atoi	= 0x800c3de4;

time	= 0x800e5e28;
localtime	= 0x800e6070;
vsscanf	= 0x800e7444;
sscanf	= 0x800e7484;

/* these are actually fs_ variants but ABI is the same */
open	= 0x80115ab0;
read	= 0x80115ea8;
write	= 0x80115fcc;
lseek	= 0x801160ec;
close	= 0x8011622c;

fs_fstat = 0x80115dd8;
fs_stat  = 0x80115dfc;
fs_mkdir = 0x80115c0c;

fs_opendir  = 0x80115b80;
fs_closedir = 0x80116248;
fs_readdir  = 0x80116190;

fs_sync = 0x80115988;

strdup	= 0x8011cbf0; /* only needed for vfs it seems */
fclose	= 0x8011cd5c;
fflush	= 0x8011cecc; /* an actual fflush this time! not __fflush */
fgets	= 0x8011d0d0;
fopen	= 0x8011d3e8;
fw_fread	= 0x8011d5a4; /* I call this flawed one ali_fread */
fseeko	= 0x8011d710;
ftell	= 0x8011de28; /* ali_ftell returning longlong */
ftello	= 0x8011de44;
fwrite	= 0x8011e1b8; /* ali_fwrite for the return value, too */

/* TDS2 */
osal_tds2_cache_flush	= 0x80005dcc;

ali_chip_delay_ms	= 0x80068df4;

os_disable_interrupt	= 0x8014f8a0;
os_enable_interrupt	= 0x8014f8c8;

dly_tsk	= 0x80179634;

task_end	= 0x80179d1c;

os_get_tick_count = 0x8017a07c;

/* drivers */
dev_get_by_id	= 0x800c0688;

osddrv_scale	= 0x800c5f10;

/* libretro frontend */
run_task	= 0x801d0780;

joy_spi_out_pair	= 0x801dfe88;
joy_spi_out_multi	= 0x801dfd50;

retro_video_refresh_cb	= 0x801e08e0; /* run_retro_video_refresh */
retro_audio_sample_batch_cb	= 0x801e0968; /* run_retro_audio_batch */
retro_input_poll_cb	= 0x801e0b1c; /* run_retro_input_poll */
retro_input_state_cb	= 0x801e0c0c; /* run_retro_input_state_get */
retro_environment_cb	= 0x801e0c50; /* run_retro_environment_get */

/* .rodata */
_ctype_	= 0x803a39ec;

s__s_Resources_Foldername_ini	= 0x803b00ac;

/* .data */
RAMSIZE	= 0x803dbb94;

g_errno	= 0x803dc1c0;

g_joy_state	= 0x803de21c;

gfn_retro_get_region	= 0x803de260;
gfn_retro_load_game	= 0x803de290;
gfn_retro_deinit	= 0x803de298;
gfn_frameskip	= 0x803de2a4;
gfn_retro_run	= 0x803de2a8;
