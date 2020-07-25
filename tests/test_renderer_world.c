
void test_world_intersect(void) {
    world_map *world = world_map_create_default();
    ray        r     = ray_new(vec4_make_point (0.0f, 0.0f, -5.0f),
                               vec4_make_vector(0.0f, 0.0f, 1.0f));

    intersect *xs_list = world_map_intersect(world, r);
    assert(intersect_list_len(xs_list)         == 4);
    assert(f32_compare(xs_list[0].value, 4.0f) == true);
    assert(f32_compare(xs_list[1].value, 4.5f) == true);
    assert(f32_compare(xs_list[2].value, 5.5f) == true);
    assert(f32_compare(xs_list[3].value, 6.0f) == true);

    world = world_map_destroy(world);
}


void test_world_shade_hit_outside(void) {
    world_map   *world = world_map_create_default();
    ray          r     = ray_new(vec4_make_point (0.0f, 0.0f, -5.0f),
                                 vec4_make_vector(0.0f, 0.0f,  1.0f));
    intersect    i     = intersect_new(&world->s_list[0], 4.0f);
    intersect_ex i_ex  = intersect_ex_compute(i, r);

    color3 res = world_map_shade_hit(world, i_ex);
    assert(color3_compare(res, color3_new(0.38066f, 0.47583f, 0.2855f)));

    world = world_map_destroy(world);
}


void test_world_shade_hit_inside(void) {
    world_map    *world = world_map_create_default();
    world->light        = light_point_new(vec4_make_point(0.0f, 0.25f, 0.0f),
                                          COLOR3_MAX_INTENSITY);
    ray           r     = ray_new(vec4_make_point (0.0f, 0.0f, 0.0f),
                                  vec4_make_vector(0.0f, 0.0f, 1.0f));

    intersect     i     = intersect_new(&world->s_list[1], 0.5f);
    intersect_ex  i_ex  = intersect_ex_compute(i, r);

    color3 res = world_map_shade_hit(world, i_ex);
    assert(color3_compare(res, color3_new(0.90498f, 0.90498f, 0.90498f)));

    world = world_map_destroy(world);
}


void test_world_shade_hit_shadow(void) {
    world_map    *world = world_map_create();
    world->light        = light_point_new(vec4_make_point(0.0f, 0.0f, -10.0f),
                                          COLOR3_MAX_INTENSITY);

    sphere s2    = sphere_new();
    s2.transform = mat4_translate(mat4_new_transform(), 0.0f, 0.0f, 10.0f);

    world->s_list = sphere_list_append(world->s_list, sphere_new());
    world->s_list = sphere_list_append(world->s_list, s2);

    ray          r    = ray_new(vec4_make_point (0.0f, 0.0f, 5.0f),
                                vec4_make_vector(0.0f, 0.0f, 1.0f));
    intersect    i    = intersect_new(&world->s_list[1], 4.0f);
    intersect_ex i_ex = intersect_ex_compute(i, r);

    color3 res = world_map_shade_hit(world, i_ex);
    assert(color3_compare(res, color3_new(0.1f, 0.1f, 0.1f)));

    world = world_map_destroy(world);
}


void test_world_color_at(void) {
    world_map *world = world_map_create_default();
    struct { ray r; color3 c; } tests[] = {
        {
            .r = ray_new(vec4_make_point (0.0f, 0.0f, -5.0f),
                         vec4_make_vector(0.0f, 1.0f,  0.0f)),
            .c = COLOR3_BLACK,
        },
        {
            .r = ray_new(vec4_make_point (0.0f, 0.0f, -5.0f),
                         vec4_make_vector(0.0f, 0.0f,  1.0f)),
            .c = color3_new(0.38066f, 0.47583f, 0.2855f),
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        ray    r = tests[i].r;
        color3 c = tests[i].c;

        color3 res = world_map_color_at(world, r);
        assert(color3_compare(res, c) == true);
    }

    // Last case is special
    world->s_list[0].material.ambient = 1.0f;
    world->s_list[1].material.ambient = 1.0f;
    ray    r = ray_new(vec4_make_point (0.0f, 0.0f,  0.75f),
                       vec4_make_vector(0.0f, 0.0f, -1.0f));
    color3 c = world->s_list[1].material.color;

    color3 res = world_map_color_at(world, r);
    assert(color3_compare(res, c) == true);

    world = world_map_destroy(world);
}


void test_world_is_shadowed(void) {
    world_map *world = world_map_create_default();
    struct { vec4 point; bool in_shadow; } tests[] = {
        { vec4_make_point(  0.0f,  10.0f,   0.0f), false },
        { vec4_make_point( 10.0f, -10.0f,  10.0f), true },
        { vec4_make_point(-20.0f,  20.0f, -20.0f), false },
        { vec4_make_point( -2.0f,   2.0f,  -2.0f), false },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 p = tests[i].point;
        bool f = tests[i].in_shadow;

        bool res = world_map_is_shadowed(world, p);
        assert(res == f);
    }

    world_map_destroy(world);
}


void test_suite_world(void) {
    printf("Running tests for renderer_world.c\n");

    test_world_intersect();
    test_world_shade_hit_outside();
    test_world_shade_hit_inside();
    test_world_shade_hit_shadow();
    test_world_color_at();
    test_world_is_shadowed();

    printf("Succesfully ran all tests\n");
}
