#pragma once

#include <stdint.h>
#include <stdbool.h>


// Basic data types
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef intptr_t  isize;
typedef uintptr_t usize;

typedef float  f32;
typedef double f64;


// Vector/Point type
typedef struct _vec4 { f32 x, y, z, w; } vec4;

inline vec4 vec4_make_point   (f32 x, f32 y, f32 z);
inline vec4 vec4_make_vector  (f32 x, f32 y, f32 z);
inline bool vec4_is_point     (vec4 *v);
inline bool vec4_is_vector    (vec4 *v);
inline bool vec4_compare      (vec4 *v1, vec4 *v2);
inline vec4 vec4_add          (vec4 *v1, vec4 *v2);
inline vec4 vec4_sub          (vec4 *v1, vec4 *v2);
inline vec4 vec4_negate       (vec4 *v);
inline vec4 vec4_scalar_mul   (vec4 *v, f32 scalar);
inline vec4 vec4_scalar_div   (vec4 *v, f32 scalar);
inline f32  vec4_magnitude    (vec4 *v);
inline vec4 vec4_normalize    (vec4 *v);
inline f32  vec4_dot_product  (vec4 *v1, vec4 *v2);
inline vec4 vec4_cross_product(vec4 *v1, vec4 *v2);


// Color type
typedef struct _color3 { f32 r, g, b; } color3;

inline bool   color3_compare   (color3 *c1, color3 *c2);
inline color3 color3_add       (color3 *c1, color3 *c2);
inline color3 color3_sub       (color3 *c1, color3 *c2);
inline color3 color3_scalar_mul(color3 *c,  f32 scalar);
inline color3 color3_mul       (color3 *c1, color3 *c2);


// Canvas type
typedef struct _canvas {
    u32     width;
    u32     height;
    u32     length;
    color3 *pixels;
} canvas;

canvas         canvas_create   (u32 width, u32 height);
inline void    canvas_set_pixel(canvas *can, u32 x, u32 y, color3 *color);
inline color3 *canvas_get_pixel(canvas *can, u32 x, u32 y);