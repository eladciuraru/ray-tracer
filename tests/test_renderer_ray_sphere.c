
void test_ray_position(void) {
    struct { f64 time; vec4 pos; } tests[] = {
        {  0.0, vec4_make_point(2.0, 3.0, 4.0) },
        {  1.0, vec4_make_point(3.0, 3.0, 4.0) },
        { -1.0, vec4_make_point(1.0, 3.0, 4.0) },
        {  2.5, vec4_make_point(4.5, 3.0, 4.0) },
    };
    ray r = ray_new(vec4_make_point (2.0, 3.0, 4.0),
                    vec4_make_vector(1.0, 0.0, 0.0));

    for (usize i = 0; i < _countof(tests); i++) {
        f64  time = tests[i].time;
        vec4 pos  = tests[i].pos;

        vec4 res = ray_position(r, time);
        assert(vec4_compare(res, pos) == true);
    }
}


void test_sphere_intersection(void) {
    sphere s = sphere_new();
    struct { ray r; u32 count; intersect xs[2]; } tests[] = {
        {
            ray_new(vec4_make_point (0.0, 0.0, -5.0),
                    vec4_make_vector(0.0, 0.0,  1.0)),
            2, { intersect_new(&s, 4.0), intersect_new(&s, 6.0) },
        },
        {
            ray_new(vec4_make_point (0.0, 1.0, -5.0),
                    vec4_make_vector(0.0, 0.0,  1.0)),
            2, { intersect_new(&s, 5.0), intersect_new(&s, 5.0) },
        },
        {
            ray_new(vec4_make_point (0.0, 2.0, -5.0),
                    vec4_make_vector(0.0, 0.0,  1.0)),
            0,
        },
        {
            ray_new(vec4_make_point (0.0, 0.0, 0.0),
                    vec4_make_vector(0.0, 0.0, 1.0)),
            2, { intersect_new(&s, -1.0), intersect_new(&s, 1.0) },
        },
        {
            ray_new(vec4_make_point (0.0, 0.0, 5.0),
                    vec4_make_vector(0.0, 0.0, 1.0)),
            2, { intersect_new(&s, -6.0), intersect_new(&s, -4.0) },
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        ray        r     = tests[i].r;
        u32        count = tests[i].count;
        intersect *xs    = tests[i].xs;

        intersect *res = sphere_intersect(&s, r);

        assert(intersect_list_len(res) == count);
        for (u32 j = 0; j < count; j++) {
            assert(intersect_compare(res[j], xs[j]));
        }

        res = intersect_list_destroy(res);
    }
}


void test_intersection_hit(void) {
    sphere s = sphere_new();
    struct { bool flag; intersect hit; intersect xs[2]; } tests[] = {
        {
            true,
            intersect_new(&s, 1.0),
            { intersect_new(&s, 1.0) , intersect_new(&s, 2.0) }
        },
        {
            true,
            intersect_new(&s, 1.0),
            { intersect_new(&s, -1.0), intersect_new(&s, 1.0) }
        },
        {
            false,
            intersect_new(NULL, 0.0),
            { intersect_new(&s, -2.0), intersect_new(&s, -1.0) }
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        bool       flag = tests[i].flag;
        intersect *xs   = tests[i].xs;
        intersect  hit  = tests[i].hit;

        intersect *list = NULL;

        list = intersect_list_append(list, xs[0]);
        list = intersect_list_append(list, xs[1]);

        intersect *res = intersect_list_hit(list);
        if (flag == true) {
            assert(intersect_compare(*res, hit));
        } else {
            assert(res == INTERSECT_NO_HIT);
        }

        list = intersect_list_destroy(list);
    }

    // Last special test - variable sized array values
    intersect *list = NULL;

    list = intersect_list_append(list, intersect_new(&s,  5.0));
    list = intersect_list_append(list, intersect_new(&s,  7.0));
    list = intersect_list_append(list, intersect_new(&s, -3.0));
    list = intersect_list_append(list, intersect_new(&s,  2.0));

    intersect *res = intersect_list_hit(list);
    assert(intersect_compare(*res, list[3]));

    list = intersect_list_destroy(list);
}


void test_ray_translate(void) {
    ray r     = ray_new(vec4_make_point (1.0, 2.0, 3.0),
                        vec4_make_vector(0.0, 1.0, 0.0));
    ray r2    = ray_new(vec4_make_point (4.0, 6.0, 8.0),
                        vec4_make_vector(0.0, 1.0, 0.0));
    mat4 tran = mat4_translate(mat4_new_transform(), 3.0, 4.0, 5.0);

    ray res = ray_transform(r, tran);
    assert(vec4_compare(res.origin,    r2.origin)    == true);
    assert(vec4_compare(res.direction, r2.direction) == true);
}


void test_ray_scale(void) {
    ray r     = ray_new(vec4_make_point (1.0, 2.0,  3.0),
                        vec4_make_vector(0.0, 1.0,  0.0));
    ray r2    = ray_new(vec4_make_point (2.0, 6.0, 12.0),
                        vec4_make_vector(0.0, 3.0,  0.0));
    mat4 tran = mat4_scale(mat4_new_transform(), 2.0, 3.0, 4.0);

    ray res = ray_transform(r, tran);
    assert(vec4_compare(res.origin,    r2.origin)    == true);
    assert(vec4_compare(res.direction, r2.direction) == true);
}


void test_sphere_scaled_intersection(void) {
    ray    r    = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                          vec4_make_vector(0.0, 0.0,  1.0));
    sphere s    = sphere_new();
    s.transform = mat4_scale(s.transform, 2.0, 2.0, 2.0);

    intersect *list = sphere_intersect(&s, r);
    assert(intersect_list_len(list) == 2);
    assert(intersect_compare(list[0], intersect_new(&s, 3.0)));
    assert(intersect_compare(list[1], intersect_new(&s, 7.0)));
}


void test_sphere_translated_intersection(void) {
    ray    r    = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                          vec4_make_vector(0.0, 0.0,  1.0));
    sphere s    = sphere_new();
    s.transform = mat4_translate(s.transform, 5.0, 0.0, 0.0);

    intersect *list = sphere_intersect(&s, r);
    assert(intersect_list_len(list) == 0);
}


void test_sphere_normal_at(void) {
    const f64 sqrt3_3 = f64_sqrt(3.0) / 3.0;

    sphere s = sphere_new();
    struct { vec4 point; vec4 normal; } tests[] = {
        {
            vec4_make_point (1.0, 0.0, 0.0),
            vec4_make_vector(1.0, 0.0, 0.0),
        },
        {
            vec4_make_point (0.0, 1.0, 0.0),
            vec4_make_vector(0.0, 1.0, 0.0),
        },
        {
            vec4_make_point (0.0, 0.0, 1.0),
            vec4_make_vector(0.0, 0.0, 1.0),
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
    s.transform = mat4_translate(s.transform, 0.0, 1.0, 0.0);
    point       = vec4_make_point(0.0, 1.70711, -0.70711);
    normal      = vec4_make_vector(0.0, 0.70711, -0.70711);
    res         = sphere_normal_at(&s, point);
    assert(vec4_compare(res, normal) == true);

    // Test 2
    s           = sphere_new();
    s.transform = mat4_new_transform();
    s.transform = mat4_rotate_z(s.transform, M_PI / 5.0);
    s.transform = mat4_scale   (s.transform, 1.0, 0.5, 1.0);

    f64 sqrt2_2 = f64_sqrt(2.0) / 2.0;
    point       = vec4_make_point(0.0f, sqrt2_2, -sqrt2_2);
    normal      = vec4_make_vector(0.0f, 0.97014f, -0.24254f);
    res         = sphere_normal_at(&s, point);
    assert(vec4_compare(res, normal) == true);
}


void test_intersection_ex_compute_outside(void) {
    ray       r = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                          vec4_make_vector(0.0, 0.0,  1.0));
    sphere    s = sphere_new();
    intersect i = intersect_new(&s, 4.0);

    intersect_ex res = intersect_ex_compute(i, r);
    assert(res.s      == i.s);
    assert(res.value  == i.value);
    assert(res.inside == false);
    assert(vec4_compare(res.point,  vec4_make_point (0.0, 0.0, -1.0)) == true);
    assert(vec4_compare(res.view,   vec4_make_vector(0.0, 0.0, -1.0)) == true);
    assert(vec4_compare(res.normal, vec4_make_vector(0.0, 0.0, -1.0)) == true);
}


void test_intersection_ex_compute_inside(void) {
    ray       r = ray_new(vec4_make_point (0.0, 0.0, 0.0),
                          vec4_make_vector(0.0, 0.0, 1.0));
    sphere    s = sphere_new();
    intersect i = intersect_new(&s, 1.0);

    intersect_ex res = intersect_ex_compute(i, r);
    assert(res.s      == i.s);
    assert(res.value  == i.value);
    assert(res.inside == true);
    assert(vec4_compare(res.point,  vec4_make_point (0.0, 0.0,  1.0)) == true);
    assert(vec4_compare(res.view,   vec4_make_vector(0.0, 0.0, -1.0)) == true);
    assert(vec4_compare(res.normal, vec4_make_vector(0.0, 0.0, -1.0)) == true);
}


void test_intersection_ex_compute_over_point(void) {
    ray       r = ray_new(vec4_make_point (0.0, 0.0, -5.0),
                          vec4_make_vector(0.0, 0.0,  1.0));
    sphere    s = sphere_new();
    s.transform = mat4_translate(mat4_new_transform(), 0.0, 0.0, 1.0);
    intersect i = intersect_new(&s, 5.0);

    intersect_ex res = intersect_ex_compute(i, r);
    assert(res.over_point.z < -_F64_EPSILON / 2.0);
    assert(res.point.z > res.over_point.z);
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
    test_intersection_ex_compute_outside();
    test_intersection_ex_compute_inside();

    printf("Succesfully ran all tests\n");
}
