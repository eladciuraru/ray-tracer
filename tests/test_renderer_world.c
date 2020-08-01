
void test_world_intersect(void) {
    world_map *world = world_map_create_default();
    ray        r     = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                               vec4_make_vector(0.0, 0.0,  1.0));

    intersect *xs_list = world_map_intersect(world, r);
    assert(intersect_list_len(xs_list)        == 4);
    assert(f64_compare(xs_list[0].value, 4.0) == true);
    assert(f64_compare(xs_list[1].value, 4.5) == true);
    assert(f64_compare(xs_list[2].value, 5.5) == true);
    assert(f64_compare(xs_list[3].value, 6.0) == true);

    world = world_map_destroy(world);
}


void test_world_shade_hit_outside(void) {
    world_map   *world = world_map_create_default();
    ray          r     = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                                 vec4_make_vector(0.0, 0.0,  1.0));
    intersect    i     = intersect_new(&world->s_list[0], 4.0);
    intersect_ex i_ex  = intersect_ex_compute(i, r);

    color3 res = world_map_shade_hit(world, i_ex);
    assert(color3_compare(res, color3_new(0.38066, 0.47583, 0.2855)));

    world = world_map_destroy(world);
}


void test_world_shade_hit_inside(void) {
    world_map    *world = world_map_create_default();
    world->light        = light_point_new(vec4_make_point(0.0, 0.25, 0.0),
                                          COLOR3_MAX_INTENSITY);
    ray           r     = ray_new(vec4_make_point (0.0, 0.0, 0.0),
                                  vec4_make_vector(0.0, 0.0, 1.0));

    intersect     i     = intersect_new(&world->s_list[1], 0.5);
    intersect_ex  i_ex  = intersect_ex_compute(i, r);

    color3 res = world_map_shade_hit(world, i_ex);
    assert(color3_compare(res, color3_new(0.90498, 0.90498, 0.90498)));

    world = world_map_destroy(world);
}


void test_world_shade_hit_shadow(void) {
    world_map    *world = world_map_create();
    world->light        = light_point_new(vec4_make_point(0.0, 0.0, -10.0),
                                          COLOR3_MAX_INTENSITY);

    sphere s2    = sphere_new();
    s2.transform = mat4_translate(mat4_new_transform(), 0.0, 0.0, 10.0);

    world->s_list = sphere_list_append(world->s_list, sphere_new());
    world->s_list = sphere_list_append(world->s_list, s2);

    ray          r    = ray_new(vec4_make_point (0.0, 0.0, 5.0),
                                vec4_make_vector(0.0, 0.0, 1.0));
    intersect    i    = intersect_new(&world->s_list[1], 4.0);
    intersect_ex i_ex = intersect_ex_compute(i, r);

    color3 res = world_map_shade_hit(world, i_ex);
    assert(color3_compare(res, color3_new(0.1, 0.1, 0.1)));

    world = world_map_destroy(world);
}


void test_world_color_at(void) {
    world_map *world = world_map_create_default();
    struct { ray r; color3 c; } tests[] = {
        {
            .r = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                         vec4_make_vector(0.0, 1.0,  0.0)),
            .c = COLOR3_BLACK,
        },
        {
            .r = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                         vec4_make_vector(0.0, 0.0,  1.0)),
            .c = color3_new(0.38066, 0.47583, 0.2855),
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        ray    r = tests[i].r;
        color3 c = tests[i].c;

        color3 res = world_map_color_at(world, r);
        assert(color3_compare(res, c) == true);
    }

    // Last case is special
    world->s_list[0].material.ambient = 1.0;
    world->s_list[1].material.ambient = 1.0;
    ray    r = ray_new(vec4_make_point (0.0, 0.0,  0.75),
                       vec4_make_vector(0.0, 0.0, -1.0));
    color3 c = world->s_list[1].material.color;

    color3 res = world_map_color_at(world, r);
    assert(color3_compare(res, c) == true);

    world = world_map_destroy(world);
}


void test_world_is_shadowed(void) {
    world_map *world = world_map_create_default();
    struct { vec4 point; bool in_shadow; } tests[] = {
        { vec4_make_point(  0.0,  10.0,   0.0), false },
        { vec4_make_point( 10.0, -10.0,  10.0), true },
        { vec4_make_point(-20.0,  20.0, -20.0), false },
        { vec4_make_point( -2.0,   2.0,  -2.0), false },
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
