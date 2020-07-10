
void test_camera_pixel_size(void) {
    camera cam = camera_new(200, 125, (f32) M_PI_2);
    assert(f32_compare(cam.pixel_size, 0.01f) == true);

    cam = camera_new(125, 200, (f32) M_PI_2);
    assert(f32_compare(cam.pixel_size, 0.01f) == true);
}


void test_camera_ray_for_pixel(void) {
    camera cam  = camera_new(201, 101, (f32) M_PI_2);
    struct { ray r; u32 x, y; } tests[] = {
        {
            ray_new(vec4_make_point (0.0f, 0.0f,  0.0f),
                    vec4_make_vector(0.0f, 0.0f, -1.0f)),
            100, 50,
        },
        {
            ray_new(vec4_make_point (0.00000f, 0.00000f,  0.00000f),
                    vec4_make_vector(0.66519f, 0.33259f, -0.66851f)),
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
    cam.transform = mat4_translate(cam.transform, 0.0f, -2.0f, 5.0f);
    cam.transform = mat4_rotate_y(cam.transform, (f32) M_PI_4);

    f32 sqrt_2_2 = sqrtf(2.0f) / 2.0f;
    ray res      = camera_ray_for_pixel(cam, 100, 50);
    assert(vec4_compare(res.origin,    vec4_make_point (0.0f,     2.0f, -5.0f))     == true);
    assert(vec4_compare(res.direction, vec4_make_vector(sqrt_2_2, 0.0f, -sqrt_2_2)) == true);
}


void test_suite_camera(void) {
    printf("Running tests for renderer_camera.c\n");

    test_camera_pixel_size();
    test_camera_ray_for_pixel();

    printf("Succesfully ran all tests\n");
}
