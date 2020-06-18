
sphere sphere_new(void) {
    return (sphere) {
        .origin    = vec4_make_point(0.0f, 0.0f, 0.0f),
        .transform = mat4_identity(),
    };
}

intersect_list *intersect_list_new(sphere *s, u32 count, f32 values[]) {
    usize          size  = sizeof(intersect_list) + count * sizeof(values[0]);
    intersect_list *list = (intersect_list *) _allocate_buffer(size);

    list->s     = s;
    list->count = count;
    for (usize i = 0; i < count; i++) {
        list->values[i] = values[i];
    }

    return list;
};


intersect_list *intersect_list_delete(intersect_list *list) {
    return _deallocate(list);
}


u32 intersect_list_hit(intersect_list *list) {
    u32 min_i = INTERSECT_NO_HIT;
    f32 min   = FLT_MAX;
    for (u32 i = 0; i < list->count; i++) {
        f32 value = list->values[i];

        if (value >= 0.0f && value < min) {
            min_i = i;
            min   = value;
        }
    }

    return min_i;
}


intersect_list *sphere_intersect(sphere *s, ray *r) {
    mat4 inv_tran  = mat4_inverse(&s->transform);
    ray  new_ray   = ray_transform(r, &inv_tran);
    vec4 direction = vec4_sub(new_ray.origin, s->origin);

    f32 a            = vec4_dot_product(new_ray.direction, new_ray.direction);
    f32 b            = 2.0f * vec4_dot_product(new_ray.direction, direction);
    f32 c            = vec4_dot_product(direction, direction) - 1.0f;
    f32 discriminant = b * b - 4 * a * c;

    intersect_list *list = NULL;
    if (discriminant >= 0.0f) {
        f32 dis_sqrt = sqrtf(discriminant);
        f32 values[] = {
            (-b - dis_sqrt) / (2 * a),
            (-b + dis_sqrt) / (2 * a),
        };
        list = intersect_list_new(s, _countof(values), values);
    } else {
        list = intersect_list_new(s, 0, NULL);
    }

    return list;
}


vec4 sphere_normal_at(sphere *s, vec4 point) {
    assert(vec4_is_point(point));

    mat4 tran_inv     = mat4_inverse(&s->transform);
    vec4 object_point = mat4_mul_vec4(&tran_inv, &point);

    mat4 tran_tran_inv = mat4_transpose(&tran_inv);
    vec4 object_normal = vec4_sub(object_point, s->origin);
    vec4 world_normal  = mat4_mul_vec4(&tran_tran_inv, &object_normal);
    world_normal.w     = 0.0f;

    return vec4_normalize(world_normal);
}
