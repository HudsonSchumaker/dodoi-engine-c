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

mat4_t mat4_make_scale(const float sx, const float sy, const float sz) {
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

mat4_t mat4_make_translation(const float tx, const float ty, const float tz) {
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

#pragma intrinsic(cosf, sinf)
mat4_t mat4_make_rotation_x(const float rx) {
    float c = cosf(rx);
    float s = sinf(rx);
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

#pragma intrinsic(cosf, sinf)
mat4_t mat4_make_rotation_y(const float ry) {
    float c = cosf(ry);
    float s = sinf(ry);
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

#pragma intrinsic(cosf, sinf)
mat4_t mat4_make_rotation_z(const float rz) {
    float c = cosf(rz);
    float s = sinf(rz);
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

vec4_t mat4_mul_vec4(const mat4_t* m, const vec4_t* v) {
    vec4_t result;
    result.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w;
    result.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w;
    result.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w;
    result.w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w;
    return result;
}

vec4_t mat4_mul_vec4_sse(const mat4_t* m, const vec4_t* v) {
    __m128 vec = _mm_loadu_ps(&v->x);
    __m128 row0 = _mm_load_ps(&m->m[0][0]);
    __m128 row1 = _mm_load_ps(&m->m[1][0]);
    __m128 row2 = _mm_load_ps(&m->m[2][0]);
    __m128 row3 = _mm_load_ps(&m->m[3][0]);

    // Each output component = dot(row_i, v) — matches mat4_mul_vec4's row-major M*v.
    __m128 x = _mm_dp_ps(row0, vec, 0xF1);
    __m128 y = _mm_dp_ps(row1, vec, 0xF2);
    __m128 z = _mm_dp_ps(row2, vec, 0xF4);
    __m128 w = _mm_dp_ps(row3, vec, 0xF8);

    __m128 result = _mm_or_ps(_mm_or_ps(x, y), _mm_or_ps(z, w));

    vec4_t out;
    _mm_store_ps(&out.x, result);
    return out;
}

mat4_t mat4_mul_mat4(const mat4_t* a, const mat4_t* b) {
    mat4_t result;
    for (byte i = 0; i < 4; i++) {
        result.m[i][0] = a->m[i][0] * b->m[0][0] + a->m[i][1] * b->m[1][0] + a->m[i][2] * b->m[2][0] + a->m[i][3] * b->m[3][0];
        result.m[i][1] = a->m[i][0] * b->m[0][1] + a->m[i][1] * b->m[1][1] + a->m[i][2] * b->m[2][1] + a->m[i][3] * b->m[3][1];
        result.m[i][2] = a->m[i][0] * b->m[0][2] + a->m[i][1] * b->m[1][2] + a->m[i][2] * b->m[2][2] + a->m[i][3] * b->m[3][2];
        result.m[i][3] = a->m[i][0] * b->m[0][3] + a->m[i][1] * b->m[1][3] + a->m[i][2] * b->m[2][3] + a->m[i][3] * b->m[3][3];
    }
    return result;
}

mat4_t mat4_mul_mat4_sse(const mat4_t* a, const mat4_t* b) {
    mat4_t result;
    __m128 row1 = _mm_load_ps(&b->m[0][0]);
    __m128 row2 = _mm_load_ps(&b->m[1][0]);
    __m128 row3 = _mm_load_ps(&b->m[2][0]);
    __m128 row4 = _mm_load_ps(&b->m[3][0]);

    for (byte i = 0; i < 4; i++) {
        __m128 brod1 = _mm_set1_ps(a->m[i][0]);
        __m128 brod2 = _mm_set1_ps(a->m[i][1]);
        __m128 brod3 = _mm_set1_ps(a->m[i][2]);
        __m128 brod4 = _mm_set1_ps(a->m[i][3]);

        __m128 res = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(brod1, row1), _mm_mul_ps(brod2, row2)),
            _mm_add_ps(_mm_mul_ps(brod3, row3), _mm_mul_ps(brod4, row4))
        );
        _mm_store_ps(&result.m[i][0], res);
    }
    return result;
}

float mat4_determinant(const mat4_t* mat) {
    float det = 0.0f;

    // Precompute sub-determinants to avoid redundant calculations
    float sub1 = mat->m[2][2] * mat->m[3][3] - mat->m[2][3] * mat->m[3][2];
    float sub2 = mat->m[2][1] * mat->m[3][3] - mat->m[2][3] * mat->m[3][1];
    float sub3 = mat->m[2][1] * mat->m[3][2] - mat->m[2][2] * mat->m[3][1];
    float sub4 = mat->m[2][0] * mat->m[3][3] - mat->m[2][3] * mat->m[3][0];
    float sub5 = mat->m[2][0] * mat->m[3][2] - mat->m[2][2] * mat->m[3][0];
    float sub6 = mat->m[2][0] * mat->m[3][1] - mat->m[2][1] * mat->m[3][0];

    det += mat->m[0][0] * (mat->m[1][1] * sub1 - mat->m[1][2] * sub2 + mat->m[1][3] * sub3);
    det -= mat->m[0][1] * (mat->m[1][0] * sub1 - mat->m[1][2] * sub4 + mat->m[1][3] * sub5);
    det += mat->m[0][2] * (mat->m[1][0] * sub2 - mat->m[1][1] * sub4 + mat->m[1][3] * sub6);
    det -= mat->m[0][3] * (mat->m[1][0] * sub3 - mat->m[1][1] * sub5 + mat->m[1][2] * sub6);

    return det;
}

bool mat4_inverse(const mat4_t* mat, mat4_t* result) {
    float a[4][8]; // [source | identity] augmented matrix

    for (byte i = 0; i < 4; i++) {
        for (byte j = 0; j < 4; j++) {
            a[i][j] = mat->m[i][j];
            a[i][j + 4] = (i == j) ? 1.0f : 0.0f;
        }
    }

    for (byte col = 0; col < 4; col++) {
        // Partial pivoting: find the row with the largest absolute value in this column.
        int pivot_row = col;
        float max_val = fabsf(a[col][col]);
        for (byte row = col + 1; row < 4; row++) {
            float val = fabsf(a[row][col]);
            if (val > max_val) {
                max_val = val;
                pivot_row = row;
            }
        }

        if (max_val < FLT_EPSILON) {
            return false; // Matrix is not invertible
        }

        if (pivot_row != col) {
            for (byte k = 0; k < 8; k++) {
                float tmp = a[col][k];
                a[col][k] = a[pivot_row][k];
                a[pivot_row][k] = tmp;
            }
        }

        // Normalize pivot row.
        float pivot = a[col][col];
        for (byte k = 0; k < 8; k++) {
            a[col][k] /= pivot;
        }

        // Eliminate this column from all other rows.
        for (byte row = 0; row < 4; row++) {
            if (row == col) continue;
            float factor = a[row][col];
            for (byte k = 0; k < 8; k++) {
                a[row][k] -= factor * a[col][k];
            }
        }
    }

    for (byte i = 0; i < 4; i++) {
        for (byte j = 0; j < 4; j++) {
            result->m[i][j] = a[i][j + 4];
        }
    }

    return true;
}

#pragma intrinsic(tanf)
mat4_t mat4_perspective(const float fov, const float aspect, const float znear, const float zfar) {
    // OpenGL RH clip space, z in [-1, 1]
    // | 1/tan(fov/2)/aspect      0                  0                    0     |
    // |        0            1/tan(fov/2)            0                    0     |
    // |        0                 0        -(zf+zn)/(zf-zn)  -(2*zf*zn)/(zf-zn) |
    // |        0                 0               -1                      0     |

    const float ctanFov = 1.0f / tanf(fov * 0.5f);
    const float xScale = ctanFov / aspect;
    const float yScale = ctanFov;
    const float zDiff = zfar - znear;

    mat4_t m = { {{ 0.0f }} };
    m.m[0][0] = xScale;
    m.m[1][1] = yScale;
    m.m[2][2] = -(zfar + znear) / zDiff;
    m.m[2][3] = -(2.0f * zfar * znear) / zDiff;
    m.m[3][2] = -1.0f;
    return m;
}
mat4_t mat4_orthographic(const float left, const float right, const float bottom, const float top, const float z_near, const float z_far) {
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

mat4_t mat4_look_at(const vec3_t* eye, const vec3_t* target, const vec3_t* up) {
    // Compute the forward (z), right (x), and up (y) vectors
    vec3_t z = vec3_normalized(vec3_sub(target, eye));
    vec3_t x = vec3_normalized(vec3_cross(&z, up));
    vec3_t y = vec3_cross(&x, &z);

    // | x.x   x.y   x.z  -dot(x,eye) |
    // | y.x   y.y   y.z  -dot(y,eye) |
    // | z.x   z.y   z.z  -dot(z,eye) |
    // | 0.0f  0.0f  0.0f    1.0f     |
    mat4_t view_matrix = {{
        { x.x, x.y, x.z, -vec3_dot(&x, eye) },
        { y.x, y.y, y.z, -vec3_dot(&y, eye) },
        { z.x, z.y, z.z, -vec3_dot(&z, eye) },
        { 0.0f, 0.0f, 0.0f,    1.0f         }
    }};
    return view_matrix;
}

void mat4_to_array(const mat4_t* mat, float* array) {
    for (byte i = 0; i < 4; i++) {
        for (byte j = 0; j < 4; j++) {
            array[j * 4 + i] = mat->m[i][j]; // column-major order
        }
    }
}
