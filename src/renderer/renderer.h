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

typedef char *cstring;  // For null terminated strings
typedef char *string;   // For non null terminated strings


// Math functions
#define _F64_EPSILON    0.0001f
#define _F64_MAX        DBL_MAX


static inline bool f64_compare(f64 num, f64 other) {
    return (num > other) ?
           ((num - other) < _F64_EPSILON) :
           ((other - num) < _F64_EPSILON);
}

static inline f64 f64_clamp(f64 value, f64 min, f64 max) {
    return max(min(max, value), min);
}

static inline f64 f64_clamp_01(f64 value) {
    return f64_clamp(value, 0.0, 1.0);
}

static inline f64 f64_pow     (f64 value, f64 exp) { return pow(value, exp); }
static inline f64 f64_sqrt    (f64 value)          { return sqrt(value); }
static inline f64 f64_round   (f64 value)          { return round(value); }
static inline f64 f64_sin     (f64 value)          { return sin(value); }
static inline f64 f64_cos     (f64 value)          { return cos(value); }
static inline f64 f64_tan     (f64 value)          { return tan(value); }


// Vector/Point type
typedef struct _vec4 { f64 x, y, z, w; } vec4;

vec4 vec4_make_point   (f64 x, f64 y, f64 z);
vec4 vec4_make_vector  (f64 x, f64 y, f64 z);
bool vec4_is_point     (vec4 v);
bool vec4_is_vector    (vec4 v);
bool vec4_compare      (vec4 v1, vec4 v2);
vec4 vec4_add          (vec4 v1, vec4 v2);
vec4 vec4_sub          (vec4 v1, vec4 v2);
vec4 vec4_negate       (vec4 v);
vec4 vec4_scalar_mul   (vec4 v, f64 scalar);
vec4 vec4_scalar_div   (vec4 v, f64 scalar);
f64  vec4_magnitude    (vec4 v);
vec4 vec4_normalize    (vec4 v);
f64  vec4_dot_product  (vec4 v1, vec4 v2);
vec4 vec4_cross_product(vec4 v1, vec4 v2);
vec4 vec4_reflect      (vec4 v, vec4 normal);


// Color type
typedef struct _color3 { f64 r, g, b; } color3;

#define COLOR3_BLACK            color3_new(0.0f, 0.0f, 0.0f)
#define COLOR3_RED              color3_new(1.0f, 0.0f, 0.0f)
#define COLOR3_GREEN            color3_new(0.0f, 1.0f, 0.0f)
#define COLOR3_BLUE             color3_new(0.0f, 0.0f, 1.0f)
#define COLOR3_YELLOW           color3_new(1.0f, 1.0f, 0.0f)
#define COLOR3_PINK             color3_new(1.0f, 0.0f, 1.0f)
#define COLOR3_CYAN             color3_new(0.0f, 1.0f, 1.0f)
#define COLOR3_WHITE            color3_new(1.0f, 1.0f, 1.0f)
#define COLOR3_MAX_INTENSITY    COLOR3_WHITE

color3 color3_new       (f64 r, f64 g, f64 b);
bool   color3_compare   (color3 c1, color3 c2);
color3 color3_add       (color3 c1, color3 c2);
color3 color3_sub       (color3 c1, color3 c2);
color3 color3_scalar_mul(color3 c,  f64 scalar);
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

canvas *canvas_create        (u32 width, u32 height);
void    canvas_set_pixel     (canvas *can, u32 x, u32 y, color3 color);
color3  canvas_get_pixel     (canvas *can, u32 x, u32 y);
canvas *canvas_destroy       (canvas *can);
bitmap *canvas_as_bitmap     (canvas *can);
bitmap *canvas_bitmap_destroy(bitmap *bmp);


// Matrix type
#define MAT4_SIZE       4
#define MAT3_SIZE       3
#define MAT2_SIZE       2

typedef struct _mat4 {
    f64 m[MAT4_SIZE][MAT4_SIZE];
} mat4;

typedef struct _mat3 {
    f64 m[MAT3_SIZE][MAT3_SIZE];
} mat3;

typedef struct _mat2 {
    f64 m[MAT2_SIZE][MAT2_SIZE];
} mat2;

mat4 mat4_identity     (void);
bool mat4_compare      (mat4 m1, mat4 m2);
mat4 mat4_mul          (mat4 m1, mat4 m2);
vec4 mat4_mul_vec4     (mat4 m,  vec4 v);
mat4 mat4_transpose    (mat4 m);
mat3 mat4_submatrix    (mat4 m, u32 row, u32 col);
f64  mat4_minor        (mat4 m, u32 row, u32 col);
f64  mat4_cofactor     (mat4 m, u32 row, u32 col);
f64  mat4_determinant  (mat4 m);
bool mat4_is_invertible(mat4 m);
mat4 mat4_inverse      (mat4 m);
bool mat3_compare      (mat3 m1, mat3 m2);
mat2 mat3_submatrix    (mat3 m,  u32 row, u32 col);
f64  mat3_minor        (mat3 m,  u32 row, u32 col);
f64  mat3_cofactor     (mat3 m,  u32 row, u32 col);
f64  mat3_determinant  (mat3 m);
bool mat2_compare      (mat2 m1, mat2 m2);
f64  mat2_determinant  (mat2 m);


// Transformation operations
#define mat4_new_transform      mat4_identity

mat4 mat4_translate(mat4 m, f64 x, f64 y, f64 z);
mat4 mat4_scale    (mat4 m, f64 x, f64 y, f64 z);
mat4 mat4_rotate_x (mat4 m, f64 radians);
mat4 mat4_rotate_y (mat4 m, f64 radians);
mat4 mat4_rotate_z (mat4 m, f64 radians);
mat4 mat4_shearing (mat4 m, f64 xy, f64 xz, f64 yx, f64 yz, f64 zx, f64 zy);
mat4 mat4_view     (vec4 from, vec4 to, vec4 up);


// Ray type
typedef struct _ray {
    vec4 origin;
    vec4 direction;
} ray;

ray  ray_new      (vec4 origin, vec4 direction);
vec4 ray_position (ray r, f64 time);
ray  ray_transform(ray r, mat4 transform);


// Type Material
typedef struct _material {
    color3 color;
    f64    ambient;
    f64    diffuse;
    f64    specular;
    f64    shininess;
} material;

material material_new    (color3 color, f64 ambient, f64 diffuse,
                          f64 specular, f64 shininess);
material material_default(void);


// Sphere type
typedef struct _sphere {
    vec4     origin;
    mat4     transform;
    material material;
} sphere;

// This is required because of type dependency
typedef struct _intersect intersect;

sphere     sphere_new         (void);
vec4       sphere_normal_at   (sphere *s, vec4 point);
intersect *sphere_intersect   (sphere *s, ray r);
sphere    *sphere_list_create (u32 limit);
void      *sphere_list_destroy(sphere *list);
u32        sphere_list_len    (sphere *list);
sphere    *sphere_list_append (sphere *list, sphere s);
sphere     sphere_list_pop    (sphere *list);
sphere    *sphere_list_extend (sphere *list, sphere *other);


// Intersect type
typedef struct _intersect {
    sphere *s;
    f64     value;
} intersect;

// ex for extended/extra
typedef struct _intersect_ex {
    sphere *s;
    f64     value;
    bool    inside;
    vec4    point;
    vec4    view;
    vec4    normal;
    vec4    over_point;
} intersect_ex;

#define INTERSECT_NO_HIT    NULL

intersect     intersect_new         (sphere *s, f64 value);
bool          intersect_compare     (intersect i1, intersect i2);
intersect_ex  intersect_ex_compute  (intersect i, ray r);
bool          intersect_ex_compare  (intersect_ex i1, intersect_ex i2);
intersect    *intersect_list_create (u32 limit);
void         *intersect_list_destroy(intersect *list);
u32           intersect_list_len    (intersect *list);
intersect    *intersect_list_append (intersect *list, intersect i);
intersect     intersect_list_pop    (intersect *list);
intersect    *intersect_list_extend (intersect *list, intersect *other);
void          intersect_list_sort   (intersect *list);
intersect    *intersect_list_hit    (intersect *list);


// Light type
typedef struct _light_point {
    vec4   position;
    color3 intensity;
} light_point;

light_point light_point_new  (vec4 position, color3 intensity);
color3      light_point_color(light_point light, material m, vec4 point,
                              vec4 view, vec4 normal, bool in_shadow);


// World type
typedef struct _world_map {
    light_point  light;
    sphere      *s_list;
} world_map;

world_map *world_map_create        (void);
world_map *world_map_create_default(void);
world_map *world_map_destroy       (world_map *world);
intersect *world_map_intersect     (world_map *world, ray r);
bool       world_map_is_shadowed   (world_map *world, vec4 point);
color3     world_map_shade_hit     (world_map *world, intersect_ex i_ex);
color3     world_map_color_at      (world_map *world, ray r);


// Camera type
typedef struct _camera {
    u32  hsize;
    u32  vsize;
    f64  field;
    mat4 transform;

    // calculated fields
    f64 half_width;
    f64 half_height;
    f64 pixel_size;
} camera;

camera  camera_new          (u32 hsize, u32 vsize, f64 field);
ray     camera_ray_for_pixel(camera cam, u32 x, u32 y);
canvas *camera_render_world (camera cam, world_map *world);
