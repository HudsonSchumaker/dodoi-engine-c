// simd_math.h - Full SIMD Math Library (SSE4.1)
// Provides vec3, vec4, mat4, quaternion operations
// Requires: -msse4.1

#ifndef SIMD_MATH_H
#define SIMD_MATH_H

#include <smmintrin.h> // SSE4.1
#include <xmmintrin.h>
#include <emmintrin.h>

// =============================
// VEC4 (float x, y, z, w)
// =============================
typedef struct { __m128 m; } vec4;

static inline vec4 vec4_set(float x, float y, float z, float w) {
    vec4 r; r.m = _mm_set_ps(w, z, y, x); return r;
}

static inline vec4 vec4_add(vec4 a, vec4 b) {
    vec4 r; r.m = _mm_add_ps(a.m, b.m); return r;
}

static inline vec4 vec4_sub(vec4 a, vec4 b) {
    vec4 r; r.m = _mm_sub_ps(a.m, b.m); return r;
}

typedef struct { float m[16]; } mat4;

// =============================
// VEC4 Dot Product
// =============================
static inline float vec4_dot(vec4 a, vec4 b) {
    return _mm_cvtss_f32(_mm_dp_ps(a.m, b.m, 0xF1));
}

// =============================
// MAT4 (4x4 matrix) operations
// =============================
typedef struct { float m[16]; } matx4;

static inline matx4 matx4_identity() {
    matx4 M = {{
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    }};
    return M;
}   

static inline void mat4_mul_sse41(const float* A, const float* B, float* C) {
    __m128 A0 = _mm_loadu_ps(&A[0]);
    __m128 A1 = _mm_loadu_ps(&A[4]);
    __m128 A2 = _mm_loadu_ps(&A[8]);
    __m128 A3 = _mm_loadu_ps(&A[12]);

    for (int col = 0; col < 4; col++) {
        __m128 Bcol = _mm_set_ps(B[12 + col], B[8 + col], B[4 + col], B[col]);

        C[col] = _mm_cvtss_f32(_mm_dp_ps(A0, Bcol, 0xF1));
        C[4 + col] = _mm_cvtss_f32(_mm_dp_ps(A1, Bcol, 0xF1));
        C[8 + col] = _mm_cvtss_f32(_mm_dp_ps(A2, Bcol, 0xF1));
        C[12 + col] = _mm_cvtss_f32(_mm_dp_ps(A3, Bcol, 0xF1));
    }
}

static inline matx4 mat4_mul(matx4 A, matx4 B) {
    matx4 C;
    mat4_mul_sse41(A.m, B.m, C.m);
    return C;
}


#endif // SIMD_MATH_H
