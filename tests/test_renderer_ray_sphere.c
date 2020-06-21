
void test_ray_position(void) {
    struct { f32 time; vec4 pos; } tests[] = {
        {  0.0f, vec4_make_point(2.0f, 3.0f, 4.0f) },
        {  1.0f, vec4_make_point(3.0f, 3.0f, 4.0f) },
        { -1.0f, vec4_make_point(1.0f, 3.0f, 4.0f) },
        {  2.5f, vec4_make_point(4.5f, 3.0f, 4.0f) },
    };
    ray r = ray_new(vec4_make_point (2.0f, 3.0f, 4.0f),
                    vec4_make_vector(1.0f, 0.0f, 0.0f));

    for (usize i = 0; i < _countof(tests); i++) {
        f32  time = tests[i].time;
        vec4 pos  = tests[i].pos;

        vec4 res = ray_position(&r, time);
        assert(vec4_compare(res, pos) == true);
    }
}


void test_sphere_intersection(void) {
    sphere s = sphere_new();
    struct { ray r; u32 count; f32 values[2]; } tests[] = {
        {
            ray_new(vec4_make_point (0.0f, 0.0f, -5.0f),
                    vec4_make_vector(0.0f, 0.0f,  1.0f)),
            2, { 4.0f, 6.0f },
        },
        {
            ray_new(vec4_make_point (0.0f, 1.0f, -5.0f),
                    vec4_make_vector(0.0f, 0.0f,  1.0f)),
            2, { 5.0f, 5.0f },
        },
        {
            ray_new(vec4_make_point (0.0f, 2.0f, -5.0f),
                    vec4_make_vector(0.0f, 0.0f,  1.0f)),
            0, { 0.0f },
        },
        {
            ray_new(vec4_make_point (0.0f, 0.0f, 0.0f),
                    vec4_make_vector(0.0f, 0.0f, 1.0f)),
            2, { -1.0f, 1.0f },
        },
        {
            ray_new(vec4_make_point (0.0f, 0.0f, 5.0f),
                    vec4_make_vector(0.0f, 0.0f, 1.0f)),
            2, { -6.0f, -4.0f },
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        ray *r      = &tests[i].r;
        u32  count  = tests[i].count;
        f32 *values = tests[i].values;

        intersect_list res = sphere_intersect(&s, r);

        assert(res.count == count);
        for (u32 j = 0; j < res.count; j++) {
            assert(f32_compare(res.values[j], values[j]));
        }
    }
}


void test_intersection_hit(void) {
    sphere s = sphere_new();
    struct {u32 index; f32 values[2]; } tests[] = {
        { 0, {  1.0f, 2.0f } },
        { 1, { -1.0f, 1.0f } },
        { INTERSECT_NO_HIT, { -2.0f, -1.0f } },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        f32  *values = tests[i].values;
        u32   index  = tests[i].index;
        intersect_list list = intersect_list_new(&s, _countof(values), values);

        u32 res = intersect_list_hit(&list);
        assert(res == index);
    }

    // Last special test - variable sized array values
    u32 index = 3;
    intersect_list list;
    intersect_list_init(list, &s, 5.0f, 7.0f, -3.0f, 2.0f);

    u32 res = intersect_list_hit(&list);
    assert(res == index);
}


void test_ray_translate(void) {
    ray r     = ray_new(vec4_make_point (1.0f, 2.0f, 3.0f),
                        vec4_make_vector(0.0f, 1.0f, 0.0f));
    ray r2    = ray_new(vec4_make_point (4.0f, 6.0f, 8.0f),
                        vec4_make_vector(0.0f, 1.0f, 0.0f));
    mat4 tran = mat4_translate(mat4_new_transform(), 3.0f, 4.0, 5.0f);

    ray res = ray_transform(&r, tran);
    assert(vec4_compare(res.origin,    r2.origin)    == true);
    assert(vec4_compare(res.direction, r2.direction) == true);
}


void test_ray_scale(void) {
    ray r     = ray_new(vec4_make_point (1.0f, 2.0f, 3.0f),
                        vec4_make_vector(0.0f, 1.0f, 0.0f));
    ray r2    = ray_new(vec4_make_point (2.0f, 6.0f, 12.0f),
                        vec4_make_vector(0.0f, 3.0f, 0.0f));
    mat4 tran = mat4_scale(mat4_new_transform(), 2.0f, 3.0, 4.0f);

    ray res = ray_transform(&r, tran);
    assert(vec4_compare(res.origin,    r2.origin)    == true);
    assert(vec4_compare(res.direction, r2.direction) == true);
}


void test_sphere_scaled_intersection(void) {
    ray    r    = ray_new(vec4_make_point (0.0f, 0.0f, -5.0f),
                          vec4_make_vector(0.0f, 0.0f,  1.0f));
    sphere s    = sphere_new();
    s.transform = mat4_scale(s.transform, 2.0f, 2.0f, 2.0f);

    intersect_list list = sphere_intersect(&s, &r);
    assert(list.count == 2);
    assert(list.values[0] == 3.0f);
    assert(list.values[1] == 7.0f);
}


void test_sphere_translated_intersection(void) {
    ray    r    = ray_new(vec4_make_point (0.0f, 0.0f, -5.0f),
                          vec4_make_vector(0.0f, 0.0f,  1.0f));
    sphere s    = sphere_new();
    s.transform = mat4_translate(s.transform, 5.0f, 0.0f, 0.0f);

    intersect_list list = sphere_intersect(&s, &r);
    assert(list.count == 0);
}


void test_sphere_normal_at(void) {
    sphere s       = sphere_new();
    f32    sqrt3_3 = sqrtf(3.0f) / 3.0f;
    struct { vec4 point; vec4 normal; } tests[] = {
        {
            vec4_make_point (1.0f, 0.0f, 0.0f),
            vec4_make_vector(1.0f, 0.0f, 0.0f),
        },
        {
            vec4_make_point (0.0f, 1.0f, 0.0f),
            vec4_make_vector(0.0f, 1.0f, 0.0f),
        },
        {
            vec4_make_point (0.0f, 0.0f, 1.0f),
            vec4_make_vector(0.0f, 0.0f, 1.0f),
        },
        {
            vec4_make_point (sqrt3_3, sqrt3_3, sqrt3_3),
            vec4_make_vector(sqrt3_3, sqrt3_3, sqrt3_3),
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 point  = tests[i].point;
        vec4 normal = tests[i].normal;

        vec4 res = sphere_normal_at(&s, point);
        assert(vec4_compare(res, normal) == true);

        // Should still be the same, since it should be normalized
        res = vec4_normalize(res);
        assert(vec4_compare(res, normal) == true);
    }
}


void test_sphere_transform_normal_at(void) {
    sphere s;
    vec4   point;
    vec4   normal;
    vec4   res;

    // Test 1
    s           = sphere_new();
    s.transform = mat4_translate(s.transform, 0.0f, 1.0f, 0.0f);
    point       = vec4_make_point(0.0f, 1.70711f, -0.70711f);
    normal      = vec4_make_vector(0.0f, 0.70711f, -0.70711f);
    res         = sphere_normal_at(&s, point);
    assert(vec4_compare(res, normal) == true);

    // Test 2
    s           = sphere_new();
    s.transform = mat4_new_transform();
    s.transform = mat4_rotate_z(s.transform, (f32) M_PI / 5.0f);
    s.transform = mat4_scale   (s.transform, 1.0f, 0.5f, 1.0f);
    f32 sqrt2_2 = sqrtf(2.0f) / 2.0f;
    point       = vec4_make_point(0.0f, sqrt2_2, -sqrt2_2);
    normal      = vec4_make_vector(0.0f, 0.97014f, -0.24254f);
    res         = sphere_normal_at(&s, point);
    assert(vec4_compare(res, normal) == true);
}


void test_suite_ray_sphere(void) {
    printf("Running tests for renderer_ray.c\n");

    test_ray_position();
    test_sphere_intersection();
    test_intersection_hit();
    test_ray_translate();
    test_ray_scale();
    test_sphere_scaled_intersection();
    test_sphere_translated_intersection();
    test_sphere_normal_at();
    test_sphere_transform_normal_at();

    printf("Succesfully ran all tests\n");
}
