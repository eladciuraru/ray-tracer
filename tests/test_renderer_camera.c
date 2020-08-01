
void test_camera_pixel_size(void) {
    camera cam = camera_new(200, 125, M_PI_2);
    assert(f64_compare(cam.pixel_size, 0.01) == true);

    cam = camera_new(125, 200, M_PI_2);
    assert(f64_compare(cam.pixel_size, 0.01) == true);
}


void test_camera_ray_for_pixel(void) {
    camera cam  = camera_new(201, 101, M_PI_2);
    struct { ray r; u32 x, y; } tests[] = {
        {
            ray_new(vec4_make_point (0.0, 0.0,  0.0),
                    vec4_make_vector(0.0, 0.0, -1.0)),
            100, 50,
        },
        {
            ray_new(vec4_make_point (0.00000, 0.00000,  0.00000),
                    vec4_make_vector(0.66519, 0.33259, -0.66851)),
            0, 0,
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        ray r = tests[i].r;
        u32 x = tests[i].x;
        u32 y = tests[i].y;

        ray res = camera_ray_for_pixel(cam, x, y);
        assert(vec4_compare(res.origin,    r.origin)    == true);
        assert(vec4_compare(res.direction, r.direction) == true);
    }

    // Special case
    cam.transform = mat4_translate(cam.transform, 0.0, -2.0, 5.0);
    cam.transform = mat4_rotate_y(cam.transform, M_PI_4);

    f64 sqrt_2_2 = f64_sqrt(2.0) / 2.0;
    ray res      = camera_ray_for_pixel(cam, 100, 50);
    assert(vec4_compare(res.origin,    vec4_make_point (0.0,      2.0, -5.0))      == true);
    assert(vec4_compare(res.direction, vec4_make_vector(sqrt_2_2, 0.0, -sqrt_2_2)) == true);
}


void test_suite_camera(void) {
    printf("Running tests for renderer_camera.c\n");

    test_camera_pixel_size();
    test_camera_ray_for_pixel();

    printf("Succesfully ran all tests\n");
}
