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
void draw_grid(int grid_size);
void draw_pixel(int x, int y, u8 color);
void draw_rect(int dx, int dy, int width, int height, u8 color);
void draw_line(int x0, int y0, int x1, int y1, u16 color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u16 color);
void draw_fix16(fix16 v);
void draw_fix16_reset(void);

#endif