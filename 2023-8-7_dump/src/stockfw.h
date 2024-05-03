#ifndef __STOCKFW_H
#define __STOCKFW_H

#include <stdint.h>

typedef uintptr_t HANDLE;

extern unsigned fw_fread(void *ptr, unsigned size, unsigned count, void *stream);

extern int fs_stat(const char *path, void *sbuf);
extern int fs_fstat(int fd, void *sbuf);
extern int fs_sync(const char *path);
extern int fs_mkdir(const char *path, int mode);

extern int fs_opendir(const char *path);
extern int fs_closedir(int fd);
extern int fs_readdir(int fd, void *buffer);

/* TDS2 */
extern unsigned os_get_tick_count(void);

extern long dly_tsk(unsigned long);

/* libretro frontend */
extern void run_task(void);

extern void joy_init(void);
extern void joy_spi_out_pair(unsigned char cmd, unsigned char data);
extern void joy_spi_out_multi(unsigned char cmd, unsigned len, unsigned char *data);

extern void retro_video_refresh_cb(const void *data, unsigned width, unsigned height, unsigned pitch);
extern unsigned retro_audio_sample_batch_cb(const short *data, unsigned frames);
extern void retro_input_poll_cb(void);
extern short retro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id);
extern int retro_set_environment_cb(unsigned cmd, void *data);

/* .rodata */
extern char s__s_Resources_Foldername_ini[];

/* .data */
extern unsigned RAMSIZE;

extern unsigned g_joy_state[2];

struct retro_game_info;

extern unsigned (* gfn_retro_get_region)(void);
extern int (* gfn_retro_load_game)(const struct retro_game_info *game);
extern void (* gfn_retro_deinit)(void);
extern void (* gfn_retro_run)(void);
extern void (* gfn_frameskip)(int flag);

#endif
