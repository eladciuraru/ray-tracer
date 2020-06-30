#pragma once

#include <stdint.h>
#include <float.h>
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

typedef char *cstring;

bool f32_compare(f32 num, f32 other);


// Vector/Point type
typedef struct _vec4 { f32 x, y, z, w; } vec4;

vec4 vec4_make_point   (f32 x, f32 y, f32 z);
vec4 vec4_make_vector  (f32 x, f32 y, f32 z);
bool vec4_is_point     (vec4 v);
bool vec4_is_vector    (vec4 v);
bool vec4_compare      (vec4 v1, vec4 v2);
vec4 vec4_add          (vec4 v1, vec4 v2);
vec4 vec4_sub          (vec4 v1, vec4 v2);
vec4 vec4_negate       (vec4 v);
vec4 vec4_scalar_mul   (vec4 v, f32 scalar);
vec4 vec4_scalar_div   (vec4 v, f32 scalar);
f32  vec4_magnitude    (vec4 v);
vec4 vec4_normalize    (vec4 v);
f32  vec4_dot_product  (vec4 v1, vec4 v2);
vec4 vec4_cross_product(vec4 v1, vec4 v2);
vec4 vec4_reflect      (vec4 v, vec4 normal);


// Color type
typedef struct _color3 { f32 r, g, b; } color3;

#define COLOR3_BLACK    color3_new(0.0f, 0.0f, 0.0f)
#define COLOR3_RED      color3_new(1.0f, 0.0f, 0.0f)
#define COLOR3_GREEN    color3_new(0.0f, 1.0f, 0.0f)
#define COLOR3_BLUE     color3_new(0.0f, 0.0f, 1.0f)
#define COLOR3_YELLOW   color3_new(1.0f, 1.0f, 0.0f)
#define COLOR3_PINK     color3_new(1.0f, 0.0f, 1.0f)
#define COLOR3_CYAN     color3_new(0.0f, 1.0f, 1.0f)
#define COLOR3_WHITE    color3_new(1.0f, 1.0f, 1.0f)

color3 color3_new       (f32 r, f32 g, f32 b);
bool   color3_compare   (color3 c1, color3 c2);
color3 color3_add       (color3 c1, color3 c2);
color3 color3_sub       (color3 c1, color3 c2);
color3 color3_scalar_mul(color3 c,  f32 scalar);
color3 color3_mul       (color3 c1, color3 c2);
u32    color3_as_u32    (color3 c);


// Canvas type
typedef struct _canvas {
    u32    width;
    u32    height;
    u32    length;
    color3 pixels[];
} canvas;

#pragma pack(push, 1)
typedef struct _bitmap_header {
    u16 magic;
    u32 file_size;
    u16 reserved[2];
    u32 pix_offset;
} bitmap_header;

typedef struct _bitmap_info {
    u32 info_size;
    u32 width;
    u32 height;
    u16 planes;
    u16 bit_count;
    u32 compression;
    u32 image_size;
    i32 x_pixels_per_meter;
    i32 y_pixels_per_meter;
    u32 color_used;
    u32 color_important;
} bitmap_info;

typedef struct _bitmap {
    bitmap_header header;
    bitmap_info   info;
    u32           pixels[];
} bitmap;
#pragma pack(pop)

#define BITMAP_MAGIC            'MB'
#define BITMAP_BPP              sizeof(u32) * 8
#define BITMAP_PIX_OFFSET       offsetof(bitmap, pixels)

canvas *canvas_create       (u32 width, u32 height);
void    canvas_set_pixel    (canvas *can, u32 x, u32 y, color3 color);
color3  canvas_get_pixel    (canvas *can, u32 x, u32 y);
canvas *canvas_destroy      (canvas *can);
bitmap *canvas_as_bitmap    (canvas *can);
bitmap *canvas_bitmap_destroy(bitmap *bmp);


// Matrix type
#define MAT4_SIZE       4
#define MAT3_SIZE       3
#define MAT2_SIZE       2

typedef struct _mat4 {
    f32 m[MAT4_SIZE][MAT4_SIZE];
} mat4;

typedef struct _mat3 {
    f32 m[MAT3_SIZE][MAT3_SIZE];
} mat3;

typedef struct _mat2 {
    f32 m[MAT2_SIZE][MAT2_SIZE];
} mat2;

mat4 mat4_identity     (void);
bool mat4_compare      (mat4 m1, mat4 m2);
mat4 mat4_mul          (mat4 m1, mat4 m2);
vec4 mat4_mul_vec4     (mat4 m,  vec4 v);
mat4 mat4_transpose    (mat4 m);
mat3 mat4_submatrix    (mat4 m, u32 row, u32 col);
f32  mat4_minor        (mat4 m, u32 row, u32 col);
f32  mat4_cofactor     (mat4 m, u32 row, u32 col);
f32  mat4_determinant  (mat4 m);
bool mat4_is_invertible(mat4 m);
mat4 mat4_inverse      (mat4 m);
bool mat3_compare      (mat3 m1, mat3 m2);
mat2 mat3_submatrix    (mat3 m,  u32 row, u32 col);
f32  mat3_minor        (mat3 m,  u32 row, u32 col);
f32  mat3_cofactor     (mat3 m,  u32 row, u32 col);
f32  mat3_determinant  (mat3 m);
bool mat2_compare      (mat2 m1, mat2 m2);
f32  mat2_determinant  (mat2 m);


// Transformation operations
#define mat4_new_transform      mat4_identity

mat4 mat4_translate(mat4 m, f32 x, f32 y, f32 z);
mat4 mat4_scale    (mat4 m, f32 x, f32 y, f32 z);
mat4 mat4_rotate_x (mat4 m, f32 radians);
mat4 mat4_rotate_y (mat4 m, f32 radians);
mat4 mat4_rotate_z (mat4 m, f32 radians);
mat4 mat4_shearing (mat4 m, f32 xy, f32 xz, f32 yx, f32 yz, f32 zx, f32 zy);


// Ray type
typedef struct _ray {
    vec4 origin;
    vec4 direction;
} ray;

ray  ray_new      (vec4 origin, vec4 direction);
vec4 ray_position (ray *r, f32 time);
ray  ray_transform(ray *r, mat4 transform);


// Type Material
typedef struct _material {
    color3 color;
    f32    ambient;
    f32    diffuse;
    f32    specular;
    f32    shininess;
} material;

material material_new    (color3 color, f32 ambient, f32 diffuse,
                          f32 specular, f32 shininess);
material material_default(void);


// Sphere type
typedef struct _sphere {
    vec4     origin;
    mat4     transform;
    material material;
} sphere;

sphere sphere_new(void);
vec4   sphere_normal_at(sphere *s, vec4 point);

// Intersect type
// Hardlimit the amount of values, for providing API
// that do not requires dynamically allocated memory
// - This limit should be enough, but in case it doesn't
//   just increase this value
#define INTERSECT_LIST_LIMIT    10

typedef struct _intersect_list {
    sphere *s;
    u32     count;
    f32     values[INTERSECT_LIST_LIMIT];
} intersect_list;

#define INTERSECT_NO_HIT        ((u32) - 1)

#define intersect_list_init(name, sphere, ...) \
    do { \
        f32 values[] = {__VA_ARGS__}; \
        name         = intersect_list_new(sphere, _countof(values), values); \
    } while (false);

#define intersect_list_init_empty(name, sphere) \
    do { \
        name = intersect_list_new(sphere, 0, NULL); \
    } while (false);

intersect_list sphere_intersect  (sphere *s, ray *r);
intersect_list intersect_list_new(sphere *s, u32 count, f32 values[]);
u32            intersect_list_hit(intersect_list *list);


// Type light
typedef struct _light_point {
    vec4   position;
    color3 intensity;
} light_point;

light_point light_point_new  (vec4 position, color3 intensity);
color3      light_point_color(light_point light, material m, vec4 point,
                              vec4 view, vec4 normal);
