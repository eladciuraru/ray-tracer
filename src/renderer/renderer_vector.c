
#define _VEC4_TYPE_POINT    1.0
#define _VEC4_TYPE_VECTOR   0.0


vec4 vec4_make_point(f64 x, f64 y, f64 z) {
    return (vec4) { x, y, z, _VEC4_TYPE_POINT };
}


vec4 vec4_make_vector(f64 x, f64 y, f64 z) {
    return (vec4) { x, y, z, _VEC4_TYPE_VECTOR };
}


bool vec4_is_point(vec4 v) {
    return f64_compare(v.w, _VEC4_TYPE_POINT);
}


bool vec4_is_vector(vec4 v) {
    return f64_compare(v.w, _VEC4_TYPE_VECTOR);
}


bool vec4_compare(vec4 v1, vec4 v2) {
    return f64_compare(v1.x, v2.x) &&
           f64_compare(v1.y, v2.y) &&
           f64_compare(v1.z, v2.z) &&
           f64_compare(v1.w, v2.w);
}


vec4 vec4_add(vec4 v1, vec4 v2) {
    return (vec4) {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z,
        v1.w + v2.w,
    };
}


vec4 vec4_sub(vec4 v1, vec4 v2) {
    return (vec4) {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z,
        v1.w - v2.w,
    };
}


vec4 vec4_negate(vec4 v) {
    return (vec4) {
        -v.x,
        -v.y,
        -v.z,
        -v.w
    };
}


vec4 vec4_scalar_mul(vec4 v, f64 scalar) {
    return (vec4) {
        v.x * scalar,
        v.y * scalar,
        v.z * scalar,
        v.w * scalar,
    };
}


vec4 vec4_scalar_div(vec4 v, f64 scalar) {
    return (vec4) {
        v.x / scalar,
        v.y / scalar,
        v.z / scalar,
        v.w / scalar,
    };
}


f64 vec4_magnitude(vec4 v) {
    return f64_sqrt(v.x * v.x +
                    v.y * v.y +
                    v.z * v.z +
                    v.w * v.w);
}


vec4 vec4_normalize(vec4 v) {
    const f64 magni = vec4_magnitude(v);

    return (vec4) {
        v.x / magni,
        v.y / magni,
        v.z / magni,
        v.w / magni,
    };
}


f64 vec4_dot_product(vec4 v1, vec4 v2) {
    return v1.x * v2.x +
           v1.y * v2.y +
           v1.z * v2.z +
           v1.w * v2.w;
}


vec4 vec4_cross_product(vec4 v1, vec4 v2) {
    // This implementation works only for when W=0, which means vector
    // for simplicity
    _ASSERT(vec4_is_vector(v1));
    _ASSERT(vec4_is_vector(v2));

    return (vec4) {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
    };
}


vec4 vec4_reflect(vec4 v, vec4 normal) {
    _ASSERT(vec4_is_vector(v));
    _ASSERT(vec4_is_vector(normal));

    vec4 mul = vec4_scalar_mul(vec4_scalar_mul(normal, 2.0f),
                               vec4_dot_product(v, normal));

    return vec4_sub(v, mul);
}
