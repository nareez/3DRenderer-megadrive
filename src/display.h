#ifndef DISPLAY_H
#define DISPLAY_H
#include "display.h"
#include "vector.h"

enum cull_method {
    CULL_NONE,
    CULL_BACKFACE
} cull_method;

enum render_method {
    RENDER_WIRE,
    // RENDER_WIRE_VERTEX,
    RENDER_FILL_TRIANGLE,
    RENDER_FILL_TRIANGLE_WIRE
} render_method;

void initialize_window(void);
void draw_grid(s16 grid_size);
void draw_pixel(s16 x, s16 y, u8 color);
void draw_rect(s16 dx, s16 dy, s16 width, s16 height, u8 color);
void draw_line(s16 x0, s16 y0, s16 x1, s16 y1, u16 color);
void draw_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color);
void draw_fix16(fix16 v);
void draw_fix16_reset(void);

#endif