#ifndef __BSOD_DEBUG_H
#define __BSOD_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

void die(const char *msg);

void hook_assert(void);
void hook_except(void);

void xlog(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
