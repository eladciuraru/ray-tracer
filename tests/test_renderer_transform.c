
void test_translate_transform(void) {
    mat4 tran = mat4_new_transform();
    tran      = mat4_translate(&tran, 5.0f, -3.0f, 2.0f);
    vec4 dest = vec4_make_point(2.0f, 1.0f, 7.0f);

    vec4 src = vec4_make_point(-3.0f, 4.0f, 5.0f);
    vec4 res = mat4_mul_vec4(&tran, &src);
    assert(vec4_compare(&res, &dest) == true);
}


void test_inverse_translate_transform(void) {
    mat4 tran = mat4_new_transform();
    tran      = mat4_translate(&tran, 5.0f, -3.0f, 2.0f);
    tran      = mat4_inverse(&tran);
    vec4 dest = vec4_make_point(-8.0f, 7.0f, 3.0f);

    vec4 src = vec4_make_point(-3.0f, 4.0f, 5.0f);
    vec4 res = mat4_mul_vec4(&tran, &src);
    assert(vec4_compare(&res, &dest) == true);
}


void test_vector_translate_transform(void) {
    mat4 tran = mat4_new_transform();
    tran      = mat4_translate(&tran, 5.0f, -3.0f, 2.0f);
    vec4 vec  = vec4_make_vector(-3.0f, 4.0f, 5.0f);

    vec4 res = mat4_mul_vec4(&tran, &vec);
    assert(vec4_compare(&res, &vec) == true);
}


void test_scale_transform(void) {
    mat4 tran = mat4_new_transform();
    tran      = mat4_scale(&tran, 2.0f, 3.0f, 4.0f);
    vec4 dest = vec4_make_point(-8.0f, 18.0f, 32.0f);

    vec4 src = vec4_make_point(-4.0f, 6.0f, 8.0f);
    vec4 res = mat4_mul_vec4(&tran, &src);
    assert(vec4_compare(&res, &dest) == true);
}


void test_inverse_scale_transform(void) {
    mat4 tran = mat4_new_transform();
    tran      = mat4_scale(&tran, 2.0f, 3.0f, 4.0f);
    tran      = mat4_inverse(&tran);
    vec4 dest = vec4_make_point(-2.0f, 2.0f, 2.0f);

    vec4 src = vec4_make_point(-4.0f, 6.0f, 8.0f);
    vec4 res = mat4_mul_vec4(&tran, &src);
    assert(vec4_compare(&res, &dest) == true);
}


void test_vector_scale_transform(void) {
    mat4 tran = mat4_new_transform();
    tran      = mat4_scale(&tran, 2.0f, 3.0f, 4.0f);
    vec4 vec  = vec4_make_vector(-8.0f, 18.0f, 32.0f);

    vec4 v   = vec4_make_vector(-4.0f, 6.0f, 8.0f);
    vec4 res = mat4_mul_vec4(&tran, &v);
    assert(vec4_compare(&res, &vec) == true);
}


void test_rotation_x_transform(void) {
    f32  sqrt_2_2  = sqrtf(2) / 2;
    vec4 dest_half = vec4_make_point(0.0f, sqrt_2_2, sqrt_2_2);
    mat4 tran_half = mat4_new_transform();
    tran_half      = mat4_rotate_x(&tran_half, (f32) M_PI_4);

    vec4 dest_full = vec4_make_point(0.0f, 0.0f, 1.0f);
    mat4 tran_full = mat4_new_transform();
    tran_full      = mat4_rotate_x(&tran_full, (f32) M_PI_2);

    vec4 src = vec4_make_point(0.0f, 1.0f, 0.0f);
    vec4 res = mat4_mul_vec4(&tran_half, &src);
    assert(vec4_compare(&res, &dest_half) == true);

    res = mat4_mul_vec4(&tran_full, &src);
    assert(vec4_compare(&res, &dest_full) == true);
}


void test_inverse_rotation_x_transform(void) {
    f32  sqrt_2_2  = sqrtf(2) / 2;
    vec4 dest_half = vec4_make_point(0.0f, sqrt_2_2, -sqrt_2_2);
    mat4 tran_half = mat4_new_transform();
    tran_half      = mat4_rotate_x(&tran_half, (f32) M_PI_4);
    tran_half      = mat4_inverse(&tran_half);

    vec4 src = vec4_make_point(0.0f, 1.0f, 0.0f);
    vec4 res = mat4_mul_vec4(&tran_half, &src);
    assert(vec4_compare(&res, &dest_half) == true);
}


void test_rotation_y_transform(void) {
    f32  sqrt_2_2  = sqrtf(2) / 2;
    vec4 dest_half = vec4_make_point(sqrt_2_2, 0.0f, sqrt_2_2);
    mat4 tran_half = mat4_new_transform();
    tran_half      = mat4_rotate_y(&tran_half, (f32) M_PI_4);

    vec4 dest_full = vec4_make_point(1.0f, 0.0f, 0.0f);
    mat4 tran_full = mat4_new_transform();
    tran_full      = mat4_rotate_y(&tran_full, (f32) M_PI_2);

    vec4 src = vec4_make_point(0.0f, 0.0f, 1.0f);
    vec4 res = mat4_mul_vec4(&tran_half, &src);
    assert(vec4_compare(&res, &dest_half) == true);

    res = mat4_mul_vec4(&tran_full, &src);
    assert(vec4_compare(&res, &dest_full) == true);
}


void test_rotation_z_transform(void) {
    f32  sqrt_2_2  = sqrtf(2) / 2;
    vec4 dest_half = vec4_make_point(-sqrt_2_2, sqrt_2_2, 0.0f);
    mat4 tran_half = mat4_new_transform();
    tran_half      = mat4_rotate_z(&tran_half, (f32) M_PI_4);

    vec4 dest_full = vec4_make_point(-1.0f, 0.0f, 0.0f);
    mat4 tran_full = mat4_new_transform();
    tran_full      = mat4_rotate_z(&tran_full, (f32) M_PI_2);

    vec4 src = vec4_make_point(0.0f, 1.0f, 0.0f);
    vec4 res = mat4_mul_vec4(&tran_half, &src);
    assert(vec4_compare(&res, &dest_half) == true);

    res = mat4_mul_vec4(&tran_full, &src);
    assert(vec4_compare(&res, &dest_full) == true);
}


void test_shearing_transform(void) {
    struct { f32 params[6]; vec4 dest; } tests[] = {
        { { [0] = 1.0f }, vec4_make_point(5.0f, 3.0f, 4.0f) },
        { { [1] = 1.0f }, vec4_make_point(6.0f, 3.0f, 4.0f) },
        { { [2] = 1.0f }, vec4_make_point(2.0f, 5.0f, 4.0f) },
        { { [3] = 1.0f }, vec4_make_point(2.0f, 7.0f, 4.0f) },
        { { [4] = 1.0f }, vec4_make_point(2.0f, 3.0f, 6.0f) },
        { { [5] = 1.0f }, vec4_make_point(2.0f, 3.0f, 7.0f) },
    };
    vec4 src = vec4_make_point(2.0f, 3.0f, 4.0f);

    for (usize i = 0; i < _countof(tests); i++) {
        f32  *params = tests[i].params;
        vec4 *dest   = &tests[i].dest;

        mat4 tran = mat4_new_transform();
        tran      = mat4_shearing(&tran, params[0], params[1], params[2],
                                  params[3], params[4], params[5]);

        vec4 res = mat4_mul_vec4(&tran, &src);
        assert(vec4_compare(&res, dest) == true);
    }
}


void test_chaining_transforms(void) {
    mat4 tran = mat4_new_transform();
    tran      = mat4_rotate_x (&tran,  (f32) M_PI_2);
    tran      = mat4_scale    (&tran,  5.0f, 5.0f, 5.0f);
    tran      = mat4_translate(&tran, 10.0f, 5.0f, 7.0f);
    vec4 dest = vec4_make_point(15.0f, 0.0f, 7.0f);

    vec4 src = vec4_make_point(1.0f, 0.0f, 1.0f);
    vec4 res = mat4_mul_vec4(&tran, &src);
    assert(vec4_compare(&res, &dest) == true);
}


void test_suite_transform(void) {
    printf("Running tests for renderer_transform.c\n");

    test_translate_transform();
    test_inverse_translate_transform();
    test_vector_translate_transform();
    test_scale_transform();
    test_inverse_scale_transform();
    test_vector_scale_transform();
    test_rotation_x_transform();
    test_inverse_rotation_x_transform();
    test_rotation_y_transform();
    test_rotation_z_transform();
    test_shearing_transform();
    test_chaining_transforms();

    printf("Succesfully ran all tests\n");
}
