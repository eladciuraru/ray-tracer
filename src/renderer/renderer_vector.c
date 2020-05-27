
#define _VEC4_TYPE_POINT    1.0f
#define _VEC4_TYPE_VECTOR   0.0f


inline vec4 vec4_make_point(f32 x, f32 y, f32 z) {
    return (vec4) { x, y, z, _VEC4_TYPE_POINT };
}


inline vec4 vec4_make_vector(f32 x, f32 y, f32 z) {
    return (vec4) { x, y, z, _VEC4_TYPE_VECTOR };
}


inline bool vec4_is_point(vec4 *v) {
    return v->w == _VEC4_TYPE_POINT;
}


inline bool vec4_is_vector(vec4 *v) {
    return v->w == _VEC4_TYPE_VECTOR;
}


inline bool vec4_compare(vec4 *v1, vec4 *v2) {
    return f32_compare(v1->x, v2->x) &&
           f32_compare(v1->y, v2->y) &&
           f32_compare(v1->z, v2->z) &&
           f32_compare(v1->w, v2->w);
}


inline vec4 vec4_add(vec4 *v1, vec4 *v2) {
    return (vec4) {
        v1->x + v2->x,
        v1->y + v2->y,
        v1->z + v2->z,
        v1->w + v2->w,
    };
}


inline vec4 vec4_sub(vec4 *v1, vec4 *v2) {
    return (vec4) {
        v1->x - v2->x,
        v1->y - v2->y,
        v1->z - v2->z,
        v1->w - v2->w,
    };
}


inline vec4 vec4_negate(vec4 *v) {
    return (vec4) {
        -v->x,
        -v->y,
        -v->z,
        -v->w
    };
}


inline vec4 vec4_scalar_mul(vec4 *v, f32 scalar) {
    return (vec4) {
        v->x * scalar,
        v->y * scalar,
        v->z * scalar,
        v->w * scalar,
    };
}


inline vec4 vec4_scalar_div(vec4 *v, f32 scalar) {
    return (vec4) {
        v->x / scalar,
        v->y / scalar,
        v->z / scalar,
        v->w / scalar,
    };
}


// TODO: Replace this to not relay on the CRT
#include <math.h>
inline f32 vec4_magnitude(vec4 *v) {
    return (f32) sqrt(v->x * v->x +
                      v->y * v->y +
                      v->z * v->z +
                      v->w * v->w);
}


inline vec4 vec4_normalize(vec4 *v) {
    const f32 magni = vec4_magnitude(v);

    return (vec4) {
        v->x / magni,
        v->y / magni,
        v->z / magni,
        v->w / magni,
    };
}


inline f32 vec4_dot_product(vec4 *v1, vec4 *v2) {
    return v1->x * v2->x +
           v1->y * v2->y +
           v1->z * v2->z +
           v1->w * v2->w;
}


inline vec4 vec4_cross_product(vec4 *v1, vec4 *v2) {
    // This implementation works only for when W=0, which means vector
    // for simplicity
    _ASSERT(vec4_is_vector(v1) == true);
    _ASSERT(vec4_is_vector(v2) == true);

    return (vec4) {
        v1->y * v2->z - v1->z * v2->y,
        v1->z * v2->x - v1->x * v2->z,
        v1->x * v2->y - v1->y * v2->x,
    };
}
