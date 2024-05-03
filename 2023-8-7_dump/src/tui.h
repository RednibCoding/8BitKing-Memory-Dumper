#ifndef __TUI_H
#define __TUI_H

#ifdef __cplusplus
extern "C" {
#endif

void gma_reg_set(unsigned adr);

#define BLACK	0
#define BLUE	0x1f
#define	GREEN	0x7e0
#define CYAN	0x7ff
#define RED	0xf800
#define YELLOW	0xffe0
#define WHITE	0xffff

void tui_open(unsigned bg);
void tui_add(int grid_x, int grid_y, unsigned fg, unsigned bg, const char *msg);

#ifdef __cplusplus
}
#endif

#endif
