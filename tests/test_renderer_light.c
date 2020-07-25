
void test_lighting_1(void) {
    vec4        pos = vec4_make_point(0.0f, 0.0f, 0.0f);
    material    m   = material_default();
    vec4        v   = vec4_make_vector(0.0f, 0.0f, -1.0f);
    vec4        n   = vec4_make_vector(0.0f, 0.0f, -1.0f);
    light_point l   = light_point_new(vec4_make_point(0.0f, 0.0f, -10.0f),
                                      COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(1.9f, 1.9f, 1.9f);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_2(void) {
    f32      sqrt2_2 = sqrtf(2.0f) / 2.0f;
    vec4     pos     = vec4_make_point(0.0f, 0.0f, 0.0f);
    material m       = material_default();
    vec4     v       = vec4_make_vector(0.0f, sqrt2_2, -sqrt2_2);
    vec4     n       = vec4_make_vector(0.0f, 0.0f, -1.0f);
    light_point l    = light_point_new(vec4_make_point(0.0f, 0.0f, -10.0f),
                                       COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(1.0f, 1.0f, 1.0f);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_3(void) {
    vec4     pos  = vec4_make_point(0.0f, 0.0f, 0.0f);
    material m    = material_default();
    vec4     v    = vec4_make_vector(0.0f, 0.0f, -1.0f);
    vec4     n    = vec4_make_vector(0.0f, 0.0f, -1.0f);
    light_point l = light_point_new(vec4_make_point(0.0f, 10.0f, -10.0f),
                                    COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(0.7364f, 0.7364f, 0.7364f);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_4(void) {
    f32      sqrt2_2 = sqrtf(2.0f) / 2.0f;
    vec4     pos     = vec4_make_point(0.0f, 0.0f, 0.0f);
    material m       = material_default();
    vec4     v       = vec4_make_vector(0.0f, -sqrt2_2, -sqrt2_2);
    vec4     n       = vec4_make_vector(0.0f, 0.0f, -1.0f);
    light_point l    = light_point_new(vec4_make_point(0.0f, 10.0f, -10.0f),
                                       COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(1.63638f, 1.63638f, 1.63638f);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_5(void) {
    vec4     pos  = vec4_make_point(0.0f, 0.0f, 0.0f);
    material m    = material_default();
    vec4     v    = vec4_make_vector(0.0f, 0.0f, -1.0f);
    vec4     n    = vec4_make_vector(0.0f, 0.0f, -1.0f);
    light_point l = light_point_new(vec4_make_point(0.0f, 0.0f, 10.0f),
                                    COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(0.1f, 0.1f, 0.1f);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_shadow(void) {
    vec4     pos  = vec4_make_point(0.0f, 0.0f, 0.0f);
    material m    = material_default();
    vec4     v    = vec4_make_vector(0.0f, 0.0f, -1.0f);
    vec4     n    = vec4_make_vector(0.0f, 0.0f, -1.0f);
    light_point l = light_point_new(vec4_make_point(0.0f, 0.0f, -10.0f),
                                    COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(0.1f, 0.1f, 0.1f);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_suite_light(void) {
    printf("Running tests for renderer_light.c\n");

    test_lighting_1();
    test_lighting_2();
    test_lighting_3();
    test_lighting_4();
    test_lighting_5();

    printf("Succesfully ran all tests\n");
}
