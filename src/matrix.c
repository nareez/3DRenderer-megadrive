#include "matrix.h"

// creates a new "empty" matrix
mat4_t mat4_identity(void) {
    mat4_t m = {{
        { FIX16(1), FIX16(0), FIX16(0), FIX16(0) },
        { FIX16(0), FIX16(1), FIX16(0), FIX16(0) },
        { FIX16(0), FIX16(0), FIX16(1), FIX16(0) },
        { FIX16(0), FIX16(0), FIX16(0), FIX16(1) }
    }};
    return m;
}

vec4_t mat4_mul_vec4(mat4_t m, vec4_t v){
    vec4_t result;
    result.x = fix16Mul(m.m[0][0], v.x) + fix16Mul(m.m[0][1], v.y) + fix16Mul(m.m[0][2], v.z) + fix16Mul(m.m[0][3], v.w);
    result.y = fix16Mul(m.m[1][0], v.x) + fix16Mul(m.m[1][1], v.y) + fix16Mul(m.m[1][2], v.z) + fix16Mul(m.m[1][3], v.w);
    result.z = fix16Mul(m.m[2][0], v.x) + fix16Mul(m.m[2][1], v.y) + fix16Mul(m.m[2][2], v.z) + fix16Mul(m.m[2][3], v.w);
    result.w = fix16Mul(m.m[3][0], v.x) + fix16Mul(m.m[3][1], v.y) + fix16Mul(m.m[3][2], v.z) + fix16Mul(m.m[3][3], v.w);
    return result;
}

// creates a scale matrix
mat4_t mat4_make_scale(fix16 sx, fix16 sy, fix16 sz){
    mat4_t m = mat4_identity();
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;
    return m;
}

// creates a translation matrix
mat4_t mat4_make_translation(fix16 tx, fix16 ty, fix16 tz){
    mat4_t m = mat4_identity();
    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;
    return m;
}

mat4_t mat4_make_rotation_x(fix16 angle) {
    fix16 c = cosFix16(angle);
    fix16 s = sinFix16(angle);
    // | 1  0  0  0 |
    // | 0  c -s  0 |
    // | 0  s  c  0 |
    // | 0  0  0  1 |
    mat4_t m = mat4_identity();
    m.m[1][1] = c;
    m.m[1][2] = -s;
    m.m[2][1] = s;
    m.m[2][2] = c;
    return m;
}

mat4_t mat4_make_rotation_y(fix16 angle) {
    fix16 c = cosFix16(angle);
    fix16 s = sinFix16(angle);
    // |  c  0  s  0 |
    // |  0  1  0  0 |
    // | -s  0  c  0 |
    // |  0  0  0  1 |
    mat4_t m = mat4_identity();
    m.m[0][0] = c;
    m.m[0][2] = s;
    m.m[2][0] = -s;
    m.m[2][2] = c;
    return m;
}

mat4_t mat4_make_rotation_z(fix16 angle) {
    fix16 c = cosFix16(angle);
    fix16 s = sinFix16(angle);
    // | c -s  0  0 |
    // | s  c  0  0 |
    // | 0  0  1  0 |
    // | 0  0  0  1 |
    mat4_t m = mat4_identity();
    m.m[0][0] = c;
    m.m[0][1] = -s;
    m.m[1][0] = s;
    m.m[1][1] = c;
    return m;
}