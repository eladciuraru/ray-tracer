
void test_points_and_vectors(void) {
    vec4 p = vec4_make_point (4.3f, -4.2f, 3.1f);
    vec4 v = vec4_make_vector(4.3f, -4.2f, 3.1f);

    assert(vec4_is_point (p) == true);
    assert(vec4_is_vector(p) == false);

    assert(vec4_is_vector(v) == true);
    assert(vec4_is_point (v) == false);
}


void test_add_vectors(void) {
    vec4 p   = {  3.0f, -2.0f, 5.0f, 1.0f };
    vec4 v   = { -2.0f,  3.0f, 1.0f, 0.0f };
    vec4 sum = {  1.0f,  1.0f, 6.0f, 1.0f };

    vec4 res = vec4_add(p, v);
    assert(vec4_compare (res, sum) == true);
    assert(vec4_is_point(res)      == true);
}


void test_sub_vectors(void) {
    struct { vec4 v1, v2, sub; } tests[] = {
        // Test 1 - point sub point = vector
        {
            vec4_make_point ( 3.0f,  2.0f,  1.0f),
            vec4_make_point ( 5.0f,  6.0f,  7.0f),
            vec4_make_vector(-2.0f, -4.0f, -6.0f),
        },
        // Test 2 - point sub vector = point
        {
            vec4_make_point ( 3.0f,  2.0f,  1.0f),
            vec4_make_vector( 5.0f,  6.0f,  7.0f),
            vec4_make_point (-2.0f, -4.0f, -6.0f),
        },
        // Test 3 - vector sub vector = vector
        {
            vec4_make_vector( 3.0f,  2.0f,  1.0f),
            vec4_make_vector( 5.0f,  6.0f,  7.0f),
            vec4_make_vector(-2.0f, -4.0f, -6.0f),
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 v1  = tests[i].v1;
        vec4 v2  = tests[i].v2;
        vec4 sub = tests[i].sub;

        vec4 res = vec4_sub(v1, v2);
        assert(vec4_compare(res, sub) == true);
    }
}


void test_negate_vector(void) {
    vec4 v   = {  1.0f, -2.0f,  3.0f, -4.0f };
    vec4 neg = { -1.0f,  2.0f, -3.0f,  4.0f };

    vec4 res = vec4_negate(v);
    assert(vec4_compare(res, neg) == true);
}


void test_scalar_mul_vector(void) {
    struct { vec4 v1, mul; f32 scalar; } tests[] = {
        {
            { 1.0f, -2.0f,  3.0f,  -4.0f },
            { 3.5f, -7.0f, 10.5f, -14.0f },
            3.5f,
        },
        {
            { 1.0f, -2.0f, 3.0f, -4.0f },
            { 0.5f, -1.0f, 1.5f, -2.0f },
            0.5f,
        }
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 v1     = tests[i].v1;
        vec4 mul    = tests[i].mul;
        f32  scalar = tests[i].scalar;

        vec4 res = vec4_scalar_mul(v1, scalar);
        assert(vec4_compare(res, mul) == true);
    }
}


void test_scalar_div_vector(void) {
    vec4 v      = { 1.0f, -2.0f, 3.0f, -4.0f };
    vec4 div    = { 0.5f, -1.0f, 1.5f, -2.0f };
    f32  scalar = 2.0f;

    vec4 res = vec4_scalar_div(v, scalar);
    assert(vec4_compare(res, div) == true);
}


void test_magnitude_vector(void) {
    struct { vec4 v1; f32 magni; } tests[] = {
        { vec4_make_vector( 1.0f,  0.0f,  0.0f), 1.0f },
        { vec4_make_vector( 0.0f,  1.0f,  0.0f), 1.0f },
        { vec4_make_vector( 0.0f,  0.0f,  1.0f), 1.0f },
        { vec4_make_vector( 1.0f,  2.0f,  3.0f), (f32) sqrt(14.0) },
        { vec4_make_vector(-1.0f, -2.0f, -3.0f), (f32) sqrt(14.0) },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 v1    = tests[i].v1;
        f32  magni = tests[i].magni;

        f32 res = vec4_magnitude(v1);
        assert(f32_compare(res, magni) == true);
    }
}


void test_normalize_vector(void) {
    struct { vec4 v1, norm; } tests[] = {
        {
            vec4_make_vector(4.0f, 0.0f, 0.0f),
            vec4_make_vector(1.0f, 0.0f, 0.0f),
        },
        {
            vec4_make_vector(1.0f, 2.0f, 3.0f),
            // vec4 { 1/sqrt(14), 2/sqrt(14), 3/sqrt(14) }
            vec4_make_vector(0.26726f, 0.53452f, 0.80178f),
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 v1   = tests[i].v1;
        vec4 norm = tests[i].norm;

        vec4 res   = vec4_normalize(v1);
        f32  magni = vec4_magnitude(res);
        assert(vec4_compare(res,   norm) == true);
        assert(f32_compare (magni, 1)    == true);
    }
}


void test_dot_product_vector(void) {
    vec4 v1  = vec4_make_vector(1.0f, 2.0f, 3.0f);
    vec4 v2  = vec4_make_vector(2.0f, 3.0f, 4.0f);
    f32  dot = 20;

    f32 res = vec4_dot_product(v1, v2);
    assert(f32_compare(res, dot) == true);
}


void test_cross_product_vector(void) {
    struct { vec4 v1, v2, cross; } tests[] = {
        {
            vec4_make_vector( 1.0f, 2.0f,  3.0f),
            vec4_make_vector( 2.0f, 3.0f,  4.0f),
            vec4_make_vector(-1.0f, 2.0f, -1.0f),
        },
        {
            vec4_make_vector(2.0f,  3.0f, 4.0f),
            vec4_make_vector(1.0f,  2.0f, 3.0f),
            vec4_make_vector(1.0f, -2.0f, 1.0f),
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 v1    = tests[i].v1;
        vec4 v2    = tests[i].v2;
        vec4 cross = tests[i].cross;

        vec4 res   = vec4_cross_product(v1, v2);
        assert(vec4_compare(res, cross) == true);
    }
}


void test_reflect_vector(void) {
    f32 sqrt2_2 = sqrtf(2.0f) / 2.0f;
    struct { vec4 v, normal, ref; } tests[] = {
        {
            vec4_make_vector(1.0f, -1.0f, 0.0f),
            vec4_make_vector(0.0f,  1.0f, 0.0f),
            vec4_make_vector(1.0f,  1.0f, 0.0f),
        },
        {
            vec4_make_vector(0.0f, -1.0f, 0.0f),
            vec4_make_vector(sqrt2_2, sqrt2_2, 0.0f),
            vec4_make_vector(1.0f,  0.0f, 0.0f),
        }
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 v   = tests[i].v;
        vec4 n   = tests[i].normal;
        vec4 ref = tests[i].ref;

        vec4 res = vec4_reflect(v, n);
        assert(vec4_compare(res, ref) == true);
    }
}


void test_suite_vector(void) {
    printf("Running tests for renderer_vector.c\n");

    test_points_and_vectors();
    test_add_vectors();
    test_sub_vectors();
    test_negate_vector();
    test_scalar_mul_vector();
    test_scalar_div_vector();
    test_magnitude_vector();
    test_normalize_vector();
    test_dot_product_vector();
    test_cross_product_vector();
    test_reflect_vector();

    printf("Succesfully ran all tests\n");
}
