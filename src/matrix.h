#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
    fix16 m[4][4];
} mat4_t;

mat4_t mat4_identity(void);
vec4_t mat4_mul_vec4(mat4_t m, vec4_t v);
mat4_t mat4_make_scale(fix16 sx, fix16 sy, fix16 sz);
mat4_t mat4_make_translation(fix16 tx, fix16 ty, fix16 tz);
mat4_t mat4_make_rotation_x(fix16 angle);
mat4_t mat4_make_rotation_y(fix16 angle);
mat4_t mat4_make_rotation_z(fix16 angle);

#endif