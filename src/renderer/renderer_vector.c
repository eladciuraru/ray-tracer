
static inline bool _f32_compare(f32 num, f32 other) {
    const f32 epsilon = 0.00001f;

    return (num > other) ?
           ((num - other) < epsilon) :
           ((other - num) < epsilon);
}

#define _VEC4_TYPE_POINT    1.0f
#define _VEC4_TYPE_VECTOR   0.0f


inline vec4 vec4_make_point(f32 x, f32 y, f32 z) {
    return (vec4) { x, y, z, _VEC4_TYPE_POINT };
}


inline vec4 vec4_make_vector(f32 x, f32 y, f32 z) {
    return (vec4) { x, y, z, _VEC4_TYPE_VECTOR };
}


inline bool vec4_is_point(vec4 *vec) {
    return vec->w == _VEC4_TYPE_POINT;
}


inline bool vec4_is_vector(vec4 *vec) {
    return vec->w == _VEC4_TYPE_VECTOR;
}


inline bool vec4_compare(vec4 *vec, vec4 *other) {
    return _f32_compare(vec->x, other->x) &&
           _f32_compare(vec->y, other->y) &&
           _f32_compare(vec->z, other->z) &&
           _f32_compare(vec->w, other->w);
}


inline vec4 vec4_add(vec4 *vec, vec4 *other) {
    return (vec4) {
        vec->x + other->x,
        vec->y + other->y,
        vec->z + other->z,
        vec->w + other->w,
    };
}


inline vec4 vec4_sub(vec4 *vec, vec4 *other) {
    return (vec4) {
        vec->x - other->x,
        vec->y - other->y,
        vec->z - other->z,
        vec->w - other->w,
    };
}


inline vec4 vec4_negate(vec4 *vec) {
    return (vec4) {
        -vec->x,
        -vec->y,
        -vec->z,
        -vec->w
    };
}


inline vec4 vec4_scalar_mul(vec4 *vec, f32 scalar) {
    return (vec4) {
        vec->x * scalar,
        vec->y * scalar,
        vec->z * scalar,
        vec->w * scalar,
    };
}


inline vec4 vec4_scalar_div(vec4 *vec, f32 scalar) {
    return (vec4) {
        vec->x / scalar,
        vec->y / scalar,
        vec->z / scalar,
        vec->w / scalar,
    };
}


// TODO: Replace this to not relay on the CRT
#include <math.h>
inline f32 vec4_magnitude(vec4 *vec) {
    return (f32) sqrt(vec->x * vec->x +
                      vec->y * vec->y +
                      vec->z * vec->z +
                      vec->w * vec->w);
}


inline vec4 vec4_normalize(vec4 *vec) {
    const f32 magni = vec4_magnitude(vec);

    return (vec4) {
        vec->x / magni,
        vec->y / magni,
        vec->z / magni,
        vec->w / magni,
    };
}


inline f32 vec4_dot_product(vec4 *vec, vec4 *other) {
    return vec->x * other->x +
           vec->y * other->y +
           vec->z * other->z +
           vec->w * other->w;
}


inline vec4 vec4_cross_product(vec4 *vec, vec4 *other) {
    // This implementation works only for when W=0, which means vector
    // for simplicity
    return (vec4) {
        vec->y * other->z - vec->z * other->y,
        vec->z * other->x - vec->x * other->z,
        vec->x * other->y - vec->y * other->x,
    };
}
