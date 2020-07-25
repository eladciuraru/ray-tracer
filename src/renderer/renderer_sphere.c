
sphere sphere_new(void) {
    return (sphere) {
        .origin    = vec4_make_point(0.0f, 0.0f, 0.0f),
        .transform = mat4_identity(),
        .material  = material_default(),
    };
}


intersect *sphere_intersect(sphere *s, ray *r) {
    ray  new_ray   = ray_transform(r, mat4_inverse(s->transform));
    vec4 direction = vec4_sub(new_ray.origin, s->origin);

    f32 a            = vec4_dot_product(new_ray.direction, new_ray.direction);
    f32 b            = 2.0f * vec4_dot_product(new_ray.direction, direction);
    f32 c            = vec4_dot_product(direction, direction) - 1.0f;
    f32 discriminant = b * b - 4 * a * c;

    intersect *list = NULL;
    if (discriminant >= 0.0f) {
        f32 dis_sqrt = sqrtf(discriminant);
        f32 values[] = {
            (-b - dis_sqrt) / (2.0f * a),
            (-b + dis_sqrt) / (2.0f * a),
        };

        list = intersect_list_append(list, (intersect) {.s = s, .value = values[0]});
        list = intersect_list_append(list, (intersect) {.s = s, .value = values[1]});
    }

    return list;
}


vec4 sphere_normal_at(sphere *s, vec4 point) {
    assert(vec4_is_point(point));

    mat4 tran_inv     = mat4_inverse(s->transform);
    vec4 object_point = mat4_mul_vec4(tran_inv, point);
    vec4 world_normal = mat4_mul_vec4(mat4_transpose(tran_inv),
                                      vec4_sub(object_point, s->origin));
    world_normal.w    = 0.0f;

    return vec4_normalize(world_normal);
}


u32 sphere_list_len(sphere *list) {
    return _array_list_len(list);
}


sphere *sphere_list_create(u32 limit) {
    return _array_list_create(limit, sizeof(sphere));
}


void *sphere_list_destroy(sphere *list) {
    return _array_list_destroy(list);
}


sphere *sphere_list_append(sphere *list, sphere s) {
    return _array_list_append(list, &s, sizeof(s));
}


sphere sphere_list_pop(sphere *list) {
    sphere s;

    _array_list_pop(list, &s, sizeof(s));

    return s;
}


sphere *sphere_list_extend(sphere *list, sphere *other) {
    return _array_list_extend(list, other, sizeof(*list));
}
