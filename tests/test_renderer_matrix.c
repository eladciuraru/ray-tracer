
void test_create_matrix4(void) {
    struct { u32 row, col; f32 value; } tests[] = {
        { 0, 0,  1.0f },
        { 0, 3,  4.0f },
        { 1, 0,  5.5f },
        { 1, 2,  7.5f },
        { 2, 2, 11.0f },
        { 3, 0, 13.5f },
        { 3, 2, 15.5f },
    };
    mat4 matrix = {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.5f,  6.5f,  7.5f,  8.5f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.5f, 14.5f, 15.5f, 16.5f,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f32 val = tests[i].value;

        assert(f32_compare(matrix.m[row][col], val) == true);
    };
}


void test_create_matrix3(void) {
    struct { u32 row, col; f32 value; } tests[] = {
        { 0, 0, -3.0f },
        { 1, 1, -2.0f },
        { 2, 2,  1.0f },
    };
    mat3 matrix = {
        -3.0f,  5.0f,  0.0f,
         1.0f, -2.0f, -7.0f,
         0.0f,  1.0f,  1.0f,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f32 val = tests[i].value;

        assert(f32_compare(matrix.m[row][col], val) == true);
    };
}


void test_create_matrix2(void) {
    struct { u32 row, col; f32 value; } tests[] = {
        { 0, 0, -3.0f },
        { 0, 1,  5.0f },
        { 1, 0,  1.0f },
        { 1, 1, -2.0f },
    };
    mat2 matrix = {
        -3.0f,  5.0f,
         1.0f, -2.0f,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f32 val = tests[i].value;

        assert(f32_compare(matrix.m[row][col], val) == true);
    };
}


void test_mul_matrix4(void) {
    mat4 m1  = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 8.0f, 7.0f, 6.0f,
        5.0f, 4.0f, 3.0f, 2.0f,
    };
    mat4 m2  = {
        -2.0f, 1.0f, 2.0f,  3.0f,
         3.0f, 2.0f, 1.0f, -1.0f,
         4.0f, 3.0f, 6.0f,  5.0f,
         1.0f, 2.0f, 7.0f,  8.0f,
    };
    mat4 mul = {
        20.0f, 22.0f,  50.0f,  48.0f,
        44.0f, 54.0f, 114.0f, 108.0f,
        40.0f, 58.0f, 110.0f, 102.0f,
        16.0f, 26.0f,  46.0f,  42.0f,
    };

    mat4 res = mat4_mul(m1, m2);
    assert(mat4_compare(res, mul) == true);
}


void test_mul_matrix4_vec4(void) {
    mat4 mat = {
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 4.0f, 4.0f, 2.0f,
        8.0f, 6.0f, 4.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    vec4 vec = {  1.0f,  2.0f,  3.0f, 1.0f };
    vec4 mul = { 18.0f, 24.0f, 33.0f, 1.0f };

    vec4 res = mat4_mul_vec4(mat, vec);
    assert(vec4_compare(res, mul) == true);
}


void test_mul_matrix4_identity(void) {
    mat4 mat  = {
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 4.0f, 4.0f, 2.0f,
        8.0f, 6.0f, 4.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    mat4 iden = mat4_identity();

    mat4 res = mat4_mul(mat, iden);
    assert(mat4_compare(res, mat) == true);
}


void test_transpose_matrix4(void) {
    mat4 mat  = {
        0.0f, 9.0f, 3.0f, 0.0f,
        9.0f, 8.0f, 0.0f, 8.0f,
        1.0f, 8.0f, 5.0f, 3.0f,
        0.0f, 0.0f, 5.0f, 8.0f,
    };
    mat4 tran = {
        0.0f, 9.0f, 1.0f, 0.0f,
        9.0f, 8.0f, 8.0f, 0.0f,
        3.0f, 0.0f, 5.0f, 5.0f,
        0.0f, 8.0f, 3.0f, 8.0f,
    };

    mat4 res = mat4_transpose(mat);
    assert(mat4_compare(res, tran) == true);
}


void test_determinant_matrix2(void) {
    mat2 mat = {
         1.0f, 5.0f,
        -3.0f, 2.0f,
    };
    f32 det  = 17.0f;

    f32 res = mat2_determinant(mat);
    assert(f32_compare(res, det) == true);
}


void test_submatrix_matrix3(void) {
    mat3 mat  = {
         1.0f, 5.0f,  0.0f,
        -3.0f, 2.0f,  7.0f,
         0.0f, 6.0f, -3.0f,
    };
    mat2 subm = {
        -3.0f, 2.0f,
         0.0f, 6.0f,
    };

    mat2 res = mat3_submatrix(mat, 0, 2);
    assert(mat2_compare(res, subm) == true);
}


void test_submatrix_matrix4(void) {
    mat4 mat  = {
        -6.0f, 1.0f,  1.0f, 6.0f,
        -8.0f, 5.0f,  8.0f, 6.0f,
        -1.0f, 0.0f,  8.0f, 2.0f,
        -7.0f, 1.0f, -1.0f, 1.0f,
    };
    mat3 subm = {
        -6.0f,  1.0f, 6.0f,
        -8.0f,  8.0f, 6.0f,
        -7.0f, -1.0f, 1.0f,
    };

    mat3 res = mat4_submatrix(mat, 2, 1);
    assert(mat3_compare(res, subm) == true);
}


void test_minor_matrix3(void) {
    mat3 mat  = {
        3.0f,  5.0f,  0.0f,
        2.0f, -1.0f, -7.0f,
        6.0f, -1.0f,  5.0f,
    };
    f32 minor = 25;

    f32 res = mat3_minor(mat, 1, 0);
    assert(f32_compare(res, minor) == true);
}


void test_cofactor_matrix3(void) {
    struct { u32 row, col; f32 cofactor; } tests[] = {
        { 0, 0, -12 },
        { 1, 0, -25 },
    };
    mat3 mat = {
        3.0f,  5.0f,  0.0f,
        2.0f, -1.0f, -7.0f,
        6.0f, -1.0f,  5.0f,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f32 cof = tests[i].cofactor;

        f32 res = mat3_cofactor(mat, row, col);
        assert(f32_compare(res, cof) == true);
    }
}


void test_determinant_matrix3(void) {
    mat3 mat = {
         1.0f, 2.0f,  6.0f,
        -5.0f, 8.0f, -4.0f,
         2.0f, 6.0f,  4.0f,
    };
    f32 det  = -196.0f;

    f32 res = mat3_determinant(mat);
    assert(f32_compare(res, det) == true);
}


void test_determinant_matrix4(void) {
    mat4 mat = {
        -2.0f, -8.0f,  3.0f,  5.0f,
        -3.0f,  1.0f,  7.0f,  3.0f,
         1.0f,  2.0f, -9.0f,  6.0f,
        -6.0f,  7.0f,  7.0f, -9.0f,
    };
    f32 det  = -4071;

    f32 res = mat4_determinant(mat);
    assert(f32_compare(res, det) == true);
}


void test_is_invertible_matrix4(void) {
    struct { mat4 mat; bool flag; } tests[] = {
        {
            {
                6.0f,  4.0f, 4.0f,  4.0f,
                5.0f,  5.0f, 7.0f,  6.0f,
                4.0f, -9.0f, 3.0f, -7.0f,
                9.0f,  1.0f, 7.0f, -6.0f,
            },
            true
        },
        {
            {
                -4.0f,  2.0f, -2.0f, -3.0f,
                 9.0f,  6.0f,  2.0f,  6.0f,
                 0.0f, -5.0f,  1.0f, -5.0f,
                 0.0f,  0.0f,  0.0f,  0.0f,
            },
            false
        }
    };

    for (usize i = 0; i < _countof(tests); i++) {
        mat4 mat  = tests[i].mat;
        bool flag = tests[i].flag;

        bool res = mat4_is_invertible(mat);
        assert(res == flag);
    }
}


void test_inverse_matrix4(void) {
    struct { mat4 mat, inv; } tests[] = {
        {
            {
                -5.0f,  2.0f,  6.0f, -8.0f,
                 1.0f, -5.0f,  1.0f,  8.0f,
                 7.0f,  7.0f, -6.0f, -7.0f,
                 1.0f, -3.0f,  7.0f,  4.0f,
            },
            {
                 0.21805f,  0.45113f,  0.24060f, -0.04511f,
                -0.80827f, -1.45677f, -0.44361f,  0.52068f,
                -0.07895f, -0.22368f, -0.05263f,  0.19737f,
                -0.52256f, -0.81391f, -0.30075f,  0.30639f,
            }
        },
        {
            {
                 8.0f, -5.0f,  9.0f,  2.0f,
                 7.0f,  5.0f,  6.0f,  1.0f,
                -6.0f,  0.0f,  9.0f,  6.0f,
                -3.0f,  0.0f, -9.0f, -4.0f,
            },
            {
                -0.15385f, -0.15385f, -0.28205f, -0.53846f,
                -0.07692f,  0.12308f,  0.02564f,  0.03077f,
                 0.35897f,  0.35897f,  0.43590f,  0.92308f,
                -0.69231f, -0.69231f, -0.76923f, -1.92308f,
            }
        },
        {
            {
                 9.0f,  3.0f,  0.0f,  9.0f,
                -5.0f, -2.0f, -6.0f, -3.0f,
                -4.0f,  9.0f,  6.0f,  4.0f,
                -7.0f,  6.0f,  6.0f,  2.0f,
            },
            {
                -0.04074f, -0.07778f,  0.14444f, -0.22222f,
                -0.07778f,  0.03333f,  0.36667f, -0.33333f,
                -0.02901f, -0.14630f, -0.10926f,  0.12963f,
                 0.17778f,  0.06667f, -0.26667f,  0.33333f,
            }
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        mat4 mat = tests[i].mat;
        mat4 inv = tests[i].inv;

        mat4 res = mat4_inverse(mat);
        assert(mat4_compare(res, inv) == true);
    }
}


void test_inverse_matrix4_2(void) {
    mat4 m1 = {
         3.0f, -9.0f,  7.0f,  3.0f,
         3.0f, -8.0f,  2.0f, -9.0f,
        -4.0f,  4.0f,  4.0f,  1.0f,
        -6.0f,  5.0f, -1.0f,  1.0f,
    };
    mat4 m2 = {
        8.0f,  2.0f, 2.0f, 2.0f,
        3.0f, -1.0f, 7.0f, 0.0f,
        7.0f,  0.0f, 5.0f, 4.0f,
        6.0f, -2.0f, 0.0f, 5.0f,
    };
    mat4 m3  = mat4_mul(m1, m2);

    mat4 res = mat4_mul(m3, mat4_inverse(m2));
    assert(mat4_compare(res, m1) == true);
}


void test_view_matrix4(void) {
    struct { vec4 from, to, up; mat4 view; } tests[] = {
        {
            vec4_make_point (0.0f, 0.0f,  0.0f),
            vec4_make_point (0.0f, 0.0f, -1.0f),
            vec4_make_vector(0.0f, 1.0f,  0.0f),
            mat4_new_transform(),
        },
        {
            vec4_make_point (0.0f, 0.0f, 0.0f),
            vec4_make_point (0.0f, 0.0f, 1.0f),
            vec4_make_vector(0.0f, 1.0f, 0.0f),
            mat4_scale(mat4_new_transform(),
                       -1.0f, 1.0f, -1.0f),
        },
        {
            vec4_make_point (0.0f, 0.0f, 8.0f),
            vec4_make_point (0.0f, 0.0f, 0.0f),
            vec4_make_vector(0.0f, 1.0f, 0.0f),
            mat4_translate(mat4_new_transform(),
                           0.0f, 0.0f, -8.0f),
        },
        {
            vec4_make_point (1.0f,  3.0f, 2.0f),
            vec4_make_point (4.0f, -2.0f, 8.0f),
            vec4_make_vector(1.0f,  1.0f, 0.0f),
            {
                -0.50709f, 0.50709f,  0.67612f, -2.36643f,
                 0.76772f, 0.60609f,  0.12122f, -2.82843f,
                -0.35857f, 0.59761f, -0.71714f,  0.00000f,
                 0.00000f, 0.00000f,  0.00000f,  1.00000f,
            },
        },
    };

    for (usize i = 0; i < _countof(tests); i++) {
        vec4 from = tests[i].from;
        vec4 to   = tests[i].to;
        vec4 up   = tests[i].up;
        mat4 view = tests[i].view;

        mat4 res = mat4_view(from, to, up);
        assert(mat4_compare(res, view) == true);
    }
}


void test_suite_matrix(void) {
    printf("Running tests for renderer_matrix.c\n");

    test_create_matrix4();
    test_create_matrix3();
    test_create_matrix2();
    test_mul_matrix4();
    test_mul_matrix4_vec4();
    test_mul_matrix4_identity();
    test_transpose_matrix4();
    test_determinant_matrix2();
    test_submatrix_matrix3();
    test_submatrix_matrix4();
    test_minor_matrix3();
    test_cofactor_matrix3();
    test_determinant_matrix3();
    test_determinant_matrix4();
    test_is_invertible_matrix4();
    test_inverse_matrix4();
    test_inverse_matrix4_2();
    test_view_matrix4();

    printf("Succesfully ran all tests\n");
}
