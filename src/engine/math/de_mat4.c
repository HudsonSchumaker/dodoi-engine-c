/**
* @file mat4.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_matrix.h"

mat4_t mat4_identity(void) {
    // | 1 0 0 0 |
    // | 0 1 0 0 |
    // | 0 0 1 0 |
    // | 0 0 0 1 |
    mat4_t m = {{
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    }};
    return m;
}

mat4_t mat4_make_scale(float sx, float sy, float sz) {
    // | sx  0  0  0 |
    // |  0 sy  0  0 |
    // |  0  0 sz  0 |
    // |  0  0  0  1 |
    mat4_t m = mat4_identity();
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;
    return m;
}

mat4_t mat4_make_translation(float tx, float ty, float tz) {
    // | 1  0  0  tx |
    // | 0  1  0  ty |
    // | 0  0  1  tz |
    // | 0  0  0  1  |
    mat4_t m = mat4_identity();
    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;
    return m;
}

mat4_t mat4_make_rotation_x(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
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

mat4_t mat4_make_rotation_y(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
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

mat4_t mat4_make_rotation_z(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
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

vec4_t mat4_mul_vec4(mat4_t* m, vec4_t* v) {
    vec4_t result = vec4_zero();
    result.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w;
    result.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w;
    result.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w;
    result.w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w;
    return result;
}

mat4_t mat4_mul_mat4(mat4_t* a, mat4_t* b) {
    mat4_t m;
    for (byte i = 0; i < 4; i++) {
        for (byte j = 0; j < 4; j++) {
            m.m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j] + a->m[i][3] * b->m[3][j];
        }
    }
    return m;
}

mat4_t mat4_perspective(float fov, float aspect, float znear, float zfar) {
    // | (h/w)*1/tan(fov/2)             0              0                 0 |
    // |                  0  1/tan(fov/2)              0                 0 |
    // |                  0             0     zf/(zf-zn)  (-zf*zn)/(zf-zn) |
    // |                  0             0              1                 0 |

    float ctanFov = 1.0f / tanf(fov / 2.0f);

    mat4_t m = { {{ 0.0f }} };
    m.m[0][0] = aspect / ctanFov;
    m.m[1][1] = ctanFov;
    m.m[2][2] = zfar / (zfar - znear);
    m.m[2][3] = (-zfar * znear) / (zfar - znear);
    m.m[3][2] = 1.0f; // right-handed coordinate system
    return m;
}

mat4_t mat4_orthographic(float left, float right, float bottom, float top, float z_near, float z_far) {
    // | 2/(r-l)    0        0    -(r+l)/(r-l) |
    // |    0     2/(t-b)    0    -(t+b)/(t-b) |
    // |    0       0    -2/(f-n) -(f+n)/(f-n) |
    // |    0       0        0          1      |
	float far_minus_near = z_far - z_near;
    mat4_t m = { {{ 0.0f }} };
    m.m[0][0] = 2.0f / (right - left);
    m.m[1][1] = 2.0f / (top - bottom);
    m.m[2][2] = -2.0f / far_minus_near;
    m.m[0][3] = -(right + left) / (right - left);
    m.m[1][3] = -(top + bottom) / (top - bottom);
    m.m[2][3] = -(z_far + z_near) / far_minus_near;
    m.m[3][3] = 1.0f;
    return m;
}

mat4_t mat4_look_at(vec3_t* eye, vec3_t* target, vec3_t* up) {
    // Compute the forward (z), right (x), and up (y) vectors
    vec3_t z = vec3_sub(target, eye);
    vec3_normalize(&z);
    vec3_t x = vec3_cross(up, &z);
    vec3_normalize(&x);
    vec3_t y = vec3_cross(&z, &x);

    // | x.x   x.y   x.z  -dot(x,eye) |
    // | y.x   y.y   y.z  -dot(y,eye) |
    // | z.x   z.y   z.z  -dot(z,eye) |
    // | 0.0f  0.0f  0.0f    1.0f     |
    mat4_t view_matrix = { {
        { x.x, x.y, x.z, -vec3_dot(&x, eye) },
        { y.x, y.y, y.z, -vec3_dot(&y, eye) },
        { z.x, z.y, z.z, -vec3_dot(&z, eye) },
        { 0.0f, 0.0f, 0.0f,    1.0f         }
    } };
    return view_matrix;
}

void mat4_to_array(const mat4_t* mat, float* array) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array[j * 4 + i] = mat->m[i][j]; // column-major order
        }
    }
}
