
ray ray_new(vec4 origin, vec4 direction) {
    _ASSERT(vec4_is_point(&origin) &&
            vec4_is_vector(&direction));

    return (ray) {
        .origin    = origin,
        .direction = direction,
    };
}


vec4 ray_position(ray *r, f32 time) {
    vec4 pos = vec4_scalar_mul(&r->direction, time);

    return vec4_add(&r->origin, &pos);
}


ray ray_transform(ray *r, mat4 *transform) {
    return ray_new(mat4_mul_vec4(transform, &r->origin),
                   mat4_mul_vec4(transform, &r->direction));
}
