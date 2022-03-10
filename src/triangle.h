#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <genesis.h>
#include "vector.h"
#include "display.h"
 
typedef struct {
    int a;
    int b;
    int c;
    u16 color;
} face_t;

typedef struct {
    vec2_t points[3];
    u16 color;
    fix16 avg_depth;
} triangle_t;

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u16 color);

#endif
