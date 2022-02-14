#ifndef DISPLAY_H
#define DISPLAY_H
#include "display.h"
#include "vector.h"

void initialize_window(void);
void draw_grid(int grid_size);
void draw_pixel(int x, int y, int color);
void draw_rect(int dx, int dy, int width, int height, int color);
void draw_line(int x0, int y0, int x1, int y1, int color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color, vec3_t cube_r);
void draw_fix16(fix16 v);
void draw_fix16_reset(void);

#endif