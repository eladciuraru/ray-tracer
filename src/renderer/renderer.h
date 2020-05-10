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


// Vector/Point types
typedef struct _vec4 { f32 x, y, z, w; } vec4;

inline vec4 vec4_make_point   (f32 x, f32 y, f32 z);
inline vec4 vec4_make_vector  (f32 x, f32 y, f32 z);
inline bool vec4_is_point     (vec4 *vec);
inline bool vec4_is_vector    (vec4 *vec);
inline bool vec4_compare      (vec4 *vec, vec4 *other);
inline vec4 vec4_add          (vec4 *vec, vec4 *other);
inline vec4 vec4_sub          (vec4 *vec, vec4 *other);
inline vec4 vec4_negate       (vec4 *vec);
inline vec4 vec4_scalar_mul   (vec4 *vec, f32 scalar);
inline vec4 vec4_scalar_div   (vec4 *vec, f32 scalar);
inline f32  vec4_magnitude    (vec4 *vec);
inline vec4 vec4_normalize    (vec4 *vec);
inline f32  vec4_dot_product  (vec4 *vec, vec4 *other);
inline vec4 vec4_cross_product(vec4 *vec, vec4 *other);
