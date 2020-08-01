
void test_lighting_1(void) {
    vec4        pos = vec4_make_point(0.0, 0.0, 0.0);
    material    m   = material_default();
    vec4        v   = vec4_make_vector(0.0, 0.0, -1.0);
    vec4        n   = vec4_make_vector(0.0, 0.0, -1.0);
    light_point l   = light_point_new(vec4_make_point(0.0, 0.0, -10.0),
                                      COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(1.9, 1.9, 1.9);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_2(void) {
    const f64 sqrt2_2 = f64_sqrt(2.0) / 2.0;

    vec4        pos = vec4_make_point(0.0, 0.0, 0.0);
    material    m   = material_default();
    vec4        v   = vec4_make_vector(0.0, sqrt2_2, -sqrt2_2);
    vec4        n   = vec4_make_vector(0.0, 0.0, -1.0);
    light_point l   = light_point_new(vec4_make_point(0.0, 0.0, -10.0),
                                      COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(1.0, 1.0, 1.0);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_3(void) {
    vec4        pos = vec4_make_point(0.0, 0.0, 0.0);
    material    m   = material_default();
    vec4        v   = vec4_make_vector(0.0, 0.0, -1.0);
    vec4        n   = vec4_make_vector(0.0, 0.0, -1.0);
    light_point l   = light_point_new(vec4_make_point(0.0, 10.0, -10.0),
                                      COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(0.7364, 0.7364, 0.7364);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_4(void) {
    const f64 sqrt2_2 = f64_sqrt(2.0) / 2.0;

    vec4        pos = vec4_make_point(0.0, 0.0, 0.0);
    material    m   = material_default();
    vec4        v   = vec4_make_vector(0.0, -sqrt2_2, -sqrt2_2);
    vec4        n   = vec4_make_vector(0.0, 0.0, -1.0);
    light_point l   = light_point_new(vec4_make_point(0.0, 10.0, -10.0),
                                      COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(1.63638, 1.63638, 1.63638);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_lighting_5(void) {
    vec4        pos = vec4_make_point(0.0, 0.0, 0.0);
    material    m   = material_default();
    vec4        v   = vec4_make_vector(0.0, 0.0, -1.0);
    vec4        n   = vec4_make_vector(0.0, 0.0, -1.0);
    light_point l   = light_point_new(vec4_make_point(0.0, 0.0, 10.0),
                                      COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(0.1, 0.1, 0.1);
    color3 res      = light_point_color(l, m, pos, v, n, false);
    assert(color3_compare(res, lighting));
}


void test_shadow(void) {
    vec4        pos = vec4_make_point(0.0, 0.0, 0.0);
    material    m   = material_default();
    vec4        v   = vec4_make_vector(0.0, 0.0, -1.0);
    vec4        n   = vec4_make_vector(0.0, 0.0, -1.0);
    light_point l   = light_point_new(vec4_make_point(0.0, 0.0, -10.0),
                                      COLOR3_MAX_INTENSITY);

    color3 lighting = color3_new(0.1, 0.1, 0.1);
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
