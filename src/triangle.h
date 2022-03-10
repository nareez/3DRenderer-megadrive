#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <genesis.h>
#include "vector.h"
#include "display.h"
 
typedef struct {
    s16 a;
    s16 b;
    s16 c;
    u16 color;
} face_t;

typedef struct {
    vec2_t points[3];
    u16 color;
    fix16 avg_depth;
} triangle_t;

void draw_filled_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color);

#endif
