#include <genesis.h>
#include "vector.h"

// vector 2D functions
fix16 vec2_length(vec2_t v){
    return fix16Sqrt(fix16Mul(v.x,v.x) + fix16Mul(v.y,v.y));
}

vec2_t vec2_add(vec2_t a, vec2_t b){
    vec2_t result = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
    return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b){
    vec2_t result = {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
    return result;
}

vec2_t vec2_mul(vec2_t a, fix16 factor){
    vec2_t result = {
        .x = fix16Mul(a.x, factor),
        .y = fix16Mul(a.y, factor)
    };
    return result;
}

vec2_t vec2_div(vec2_t a, fix16 factor){
    vec2_t result = {
        .x = fix16Div(a.x, factor),
        .y = fix16Div(a.y, factor)
    };
    return result;
}

fix16 vec2_dot(vec2_t a, vec2_t b){
    return fix16Mul(a.x, b.x) + fix16Mul(a.y, b.y);
}

void vec2_normalize(vec2_t *v){
    fix16 length = fix16Sqrt(fix16Mul(v->x, v->x) + fix16Mul(v->y, v->y));
    v->x = fix16Div(v->x, length);
    v->y = fix16Div(v->y, length);
}

// vector 3D functions
fix16 vec3_length(vec3_t v){
    return fix16Sqrt(fix16Mul(v.x, v.x) + fix16Mul(v.y, v.y) + fix16Mul(v.z, v.z));
}

vec3_t vec3_add(vec3_t a, vec3_t b){
    vec3_t result = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
    return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b){
    vec3_t result = {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
    return result;
}

vec3_t vec3_mul(vec3_t a, fix16 factor){
    vec3_t result = {
        .x = fix16Mul(a.x, factor),
        .y = fix16Mul(a.y, factor),
        .z = fix16Mul(a.z, factor)
    };
    return result;
}

vec3_t vec3_div(vec3_t a, fix16 factor){
    vec3_t result = {
        .x = fix16Div(a.x, factor),
        .y = fix16Div(a.y, factor),
        .z = fix16Div(a.z, factor)
    };
    return result;
}

vec3_t vec3_cross(vec3_t a, vec3_t b){
    vec3_t result = {
        .x = fix16Mul(a.y, b.z) - fix16Mul(a.z, b.y),
        .y = fix16Mul(a.z, b.x) - fix16Mul(a.x, b.z),
        .z = fix16Mul(a.x, b.y) - fix16Mul(a.y, b.x)
    };
    return result;
}

fix16 vec3_dot(vec3_t a, vec3_t b){
    return fix16Mul(a.x, b.x) + fix16Mul(a.y, b.y) + fix16Mul(a.z, b.z);
}

void vec3_normalize(vec3_t *v){
    fix16 length = fix16Sqrt(fix16Mul(v->x, v->x) + fix16Mul(v->y, v->y) + fix16Mul(v->z, v->z));
    v->x = fix16Div(v->x, length);
    v->y = fix16Div(v->y, length);
    v->z = fix16Div(v->z, length);
}

// vector 3D rotation functions
vec3_t vec3_rotate_x(vec3_t v, fix16 angle){
    vec3_t rotated_vector = {
        .x = v.x,
        .y = fix16Mul(v.y, cosFix16(angle)) - fix16Mul(v.z, sinFix16(angle)),
        .z = fix16Mul(v.y, sinFix16(angle)) + fix16Mul(v.z, cosFix16(angle))
    };
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, fix16 angle){
    vec3_t rotated_vector = {
        .x = fix16Mul(v.x, cosFix16(angle)) - fix16Mul(v.z, sinFix16(angle)),
        .y = v.y,
        .z = fix16Mul(v.x, sinFix16(angle)) + fix16Mul(v.z, cosFix16(angle))
    };
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, fix16 angle){
    vec3_t rotated_vector = {
        .x = fix16Mul(v.x, cosFix16(angle)) - fix16Mul(v.y, sinFix16(angle)),
        .y = fix16Mul(v.x, sinFix16(angle)) + fix16Mul(v.y, cosFix16(angle)),
        .z = v.z
    };
    return rotated_vector;
}

vec4_t vec4_from_vec3(vec3_t v){
    vec4_t result = {v.x, v.y, v.z, FIX16(1)};
    return result;
}

vec3_t vec3_from_vec4(vec4_t v){
    vec3_t result = {v.x, v.y, v.z};
    return result;
}