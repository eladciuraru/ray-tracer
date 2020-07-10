
world_map *world_map_create(void) {
    return _allocate_buffer(sizeof(world_map));
}


world_map *world_map_create_default(void) {
    world_map *world = _allocate_buffer(sizeof(*world));

    world->light = light_point_new(vec4_make_point(-10.0f, 10.0f, -10.0f),
                                  COLOR3_MAX_INTENSITY);

    sphere s1            = sphere_new();
    s1.material.color    = color3_new(0.8f, 1.0f, 0.6f);
    s1.material.diffuse  = 0.7f;
    s1.material.specular = 0.2f;

    sphere s2    = sphere_new();
    s2.transform = mat4_scale(s2.transform, 0.5f, 0.5f, 0.5f);

    world->s_list = sphere_list_append(NULL, s1);
    world->s_list = sphere_list_append(world->s_list, s2);

    return world;
}


world_map *world_map_destroy(world_map *world) {
    sphere_list_destroy(world->s_list);

    return _deallocate(world);
}


intersect *world_map_intersect(world_map *world, ray r) {
    intersect *xs_list = NULL;

    for (u32 i = 0; i < sphere_list_len(world->s_list); i++) {
        intersect *temp = sphere_intersect(&world->s_list[i], &r);

        xs_list = intersect_list_extend(xs_list, temp);

        intersect_list_destroy(temp);
    }
    intersect_list_sort(xs_list);

    return xs_list;
}


// TODO: add support for multiple light point
//       the result should be all the sub color added together
color3 world_map_shade_hit(world_map *world, intersect_ex i_ex) {
    return light_point_color(world->light, i_ex.s->material, i_ex.point,
                             i_ex.view, i_ex.normal);
}


color3 world_map_color_at(world_map *world, ray r) {
    intersect *xs_list = world_map_intersect(world, r);
    intersect *hit     = intersect_list_hit(xs_list);
    color3     color   = COLOR3_BLACK;

    if (hit != INTERSECT_NO_HIT) {
        intersect_ex i_ex = intersect_ex_compute(*hit, r);
        color             = world_map_shade_hit(world, i_ex);
    }

    intersect_list_destroy(xs_list);
    return color;
}
