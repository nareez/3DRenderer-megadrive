#ifndef VECTOR_H
#define VECTOR_H
#include <genesis.h>

typedef struct {
    fix16 x;
    fix16 y;
} vec2_t;

typedef struct {
    fix16 x;
    fix16 y;
    fix16 z;
} vec3_t;

/****************************************
 *         Vector 2D functions          *
 * **************************************/
fix16 vec2_length(vec2_t v);
vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_mul(vec2_t a, fix16 factor);
vec2_t vec2_div(vec2_t a, fix16 factor);
fix16 vec2_dot(vec2_t a, vec2_t b);
void vec2_normalize(vec2_t *a);

/****************************************
 *         Vector 3D functions          *
 * **************************************/
fix16 vec3_length(vec3_t v);
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
vec3_t vec3_mul(vec3_t a, fix16 factor);
vec3_t vec3_div(vec3_t a, fix16 factor);
vec3_t vec3_cross(vec3_t a, vec3_t b);
fix16 vec3_dot(vec3_t a, vec3_t b);
void vec3_normalize(vec3_t *a);

/****************************************
 *          3D Rotation functions       *
 * **************************************/
vec3_t vec3_rotate_x(vec3_t v, fix16 angle);
vec3_t vec3_rotate_y(vec3_t v, fix16 angle);
vec3_t vec3_rotate_z(vec3_t v, fix16 angle);

#endif