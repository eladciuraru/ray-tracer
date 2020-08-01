
void test_create_matrix4(void) {
    struct { u32 row, col; f64 value; } tests[] = {
        { 0, 0,  1.0 },
        { 0, 3,  4.0 },
        { 1, 0,  5.5 },
        { 1, 2,  7.5 },
        { 2, 2, 11.0 },
        { 3, 0, 13.5 },
        { 3, 2, 15.5 },
    };
    mat4 matrix = {
         1.0,  2.0,  3.0,  4.0,
         5.5,  6.5,  7.5,  8.5,
         9.0, 10.0, 11.0, 12.0,
        13.5, 14.5, 15.5, 16.5,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f64 val = tests[i].value;

        assert(f64_compare(matrix.m[row][col], val) == true);
    };
}


void test_create_matrix3(void) {
    struct { u32 row, col; f64 value; } tests[] = {
        { 0, 0, -3.0 },
        { 1, 1, -2.0 },
        { 2, 2,  1.0 },
    };
    mat3 matrix = {
        -3.0,  5.0,  0.0,
         1.0, -2.0, -7.0,
         0.0,  1.0,  1.0,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f64 val = tests[i].value;

        assert(f64_compare(matrix.m[row][col], val) == true);
    };
}


void test_create_matrix2(void) {
    struct { u32 row, col; f64 value; } tests[] = {
        { 0, 0, -3.0 },
        { 0, 1,  5.0 },
        { 1, 0,  1.0 },
        { 1, 1, -2.0 },
    };
    mat2 matrix = {
        -3.0,  5.0,
         1.0, -2.0,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f64 val = tests[i].value;

        assert(f64_compare(matrix.m[row][col], val) == true);
    };
}


void test_mul_matrix4(void) {
    mat4 m1  = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0,
    };
    mat4 m2  = {
        -2.0, 1.0, 2.0,  3.0,
         3.0, 2.0, 1.0, -1.0,
         4.0, 3.0, 6.0,  5.0,
         1.0, 2.0, 7.0,  8.0,
    };
    mat4 mul = {
        20.0, 22.0,  50.0,  48.0,
        44.0, 54.0, 114.0, 108.0,
        40.0, 58.0, 110.0, 102.0,
        16.0, 26.0,  46.0,  42.0,
    };

    mat4 res = mat4_mul(m1, m2);
    assert(mat4_compare(res, mul) == true);
}


void test_mul_matrix4_vec4(void) {
    mat4 mat = {
        1.0, 2.0, 3.0, 4.0,
        2.0, 4.0, 4.0, 2.0,
        8.0, 6.0, 4.0, 1.0,
        0.0, 0.0, 0.0, 1.0,
    };
    vec4 vec = {  1.0,  2.0,  3.0, 1.0 };
    vec4 mul = { 18.0, 24.0, 33.0, 1.0 };

    vec4 res = mat4_mul_vec4(mat, vec);
    assert(vec4_compare(res, mul) == true);
}


void test_mul_matrix4_identity(void) {
    mat4 mat  = {
        1.0, 2.0, 3.0, 4.0,
        2.0, 4.0, 4.0, 2.0,
        8.0, 6.0, 4.0, 1.0,
        0.0, 0.0, 0.0, 1.0,
    };
    mat4 iden = mat4_identity();

    mat4 res = mat4_mul(mat, iden);
    assert(mat4_compare(res, mat) == true);
}


void test_transpose_matrix4(void) {
    mat4 mat  = {
        0.0, 9.0, 3.0, 0.0,
        9.0, 8.0, 0.0, 8.0,
        1.0, 8.0, 5.0, 3.0,
        0.0, 0.0, 5.0, 8.0,
    };
    mat4 tran = {
        0.0, 9.0, 1.0, 0.0,
        9.0, 8.0, 8.0, 0.0,
        3.0, 0.0, 5.0, 5.0,
        0.0, 8.0, 3.0, 8.0,
    };

    mat4 res = mat4_transpose(mat);
    assert(mat4_compare(res, tran) == true);
}


void test_determinant_matrix2(void) {
    mat2 mat = {
         1.0, 5.0,
        -3.0, 2.0,
    };
    f64 det  = 17.0;

    f64 res = mat2_determinant(mat);
    assert(f64_compare(res, det) == true);
}


void test_submatrix_matrix3(void) {
    mat3 mat  = {
         1.0, 5.0,  0.0,
        -3.0, 2.0,  7.0,
         0.0, 6.0, -3.0,
    };
    mat2 subm = {
        -3.0, 2.0,
         0.0, 6.0,
    };

    mat2 res = mat3_submatrix(mat, 0, 2);
    assert(mat2_compare(res, subm) == true);
}


void test_submatrix_matrix4(void) {
    mat4 mat  = {
        -6.0, 1.0,  1.0, 6.0,
        -8.0, 5.0,  8.0, 6.0,
        -1.0, 0.0,  8.0, 2.0,
        -7.0, 1.0, -1.0, 1.0,
    };
    mat3 subm = {
        -6.0,  1.0, 6.0,
        -8.0,  8.0, 6.0,
        -7.0, -1.0, 1.0,
    };

    mat3 res = mat4_submatrix(mat, 2, 1);
    assert(mat3_compare(res, subm) == true);
}


void test_minor_matrix3(void) {
    mat3 mat  = {
        3.0,  5.0,  0.0,
        2.0, -1.0, -7.0,
        6.0, -1.0,  5.0,
    };
    f64 minor = 25.0;

    f64 res = mat3_minor(mat, 1, 0);
    assert(f64_compare(res, minor) == true);
}


void test_cofactor_matrix3(void) {
    struct { u32 row, col; f64 cofactor; } tests[] = {
        { 0, 0, -12.0 },
        { 1, 0, -25.0 },
    };
    mat3 mat = {
        3.0,  5.0,  0.0,
        2.0, -1.0, -7.0,
        6.0, -1.0,  5.0,
    };

    for (usize i = 0; i < _countof(tests); i++) {
        u32 row = tests[i].row;
        u32 col = tests[i].col;
        f64 cof = tests[i].cofactor;

        f64 res = mat3_cofactor(mat, row, col);
        assert(f64_compare(res, cof) == true);
    }
}


void test_determinant_matrix3(void) {
    mat3 mat = {
         1.0, 2.0,  6.0,
        -5.0, 8.0, -4.0,
         2.0, 6.0,  4.0,
    };
    f64 det  = -196.0;

    f64 res = mat3_determinant(mat);
    assert(f64_compare(res, det) == true);
}


void test_determinant_matrix4(void) {
    mat4 mat = {
        -2.0, -8.0,  3.0,  5.0,
        -3.0,  1.0,  7.0,  3.0,
         1.0,  2.0, -9.0,  6.0,
        -6.0,  7.0,  7.0, -9.0,
    };
    f64 det  = -4071.0;

    f64 res = mat4_determinant(mat);
    assert(f64_compare(res, det) == true);
}


void test_is_invertible_matrix4(void) {
    struct { mat4 mat; bool flag; } tests[] = {
        {
            {
                6.0,  4.0, 4.0,  4.0,
                5.0,  5.0, 7.0,  6.0,
                4.0, -9.0, 3.0, -7.0,
                9.0,  1.0, 7.0, -6.0,
            },
            true
        },
        {
            {
                -4.0,  2.0, -2.0, -3.0,
                 9.0,  6.0,  2.0,  6.0,
                 0.0, -5.0,  1.0, -5.0,
                 0.0,  0.0,  0.0,  0.0,
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
                -5.0,  2.0,  6.0, -8.0,
                 1.0, -5.0,  1.0,  8.0,
                 7.0,  7.0, -6.0, -7.0,
                 1.0, -3.0,  7.0,  4.0,
            },
            {
                 0.21805,  0.45113,  0.24060, -0.04511,
                -0.80827, -1.45677, -0.44361,  0.52068,
                -0.07895, -0.22368, -0.05263,  0.19737,
                -0.52256, -0.81391, -0.30075,  0.30639,
            }
        },
        {
            {
                 8.0, -5.0,  9.0,  2.0,
                 7.0,  5.0,  6.0,  1.0,
                -6.0,  0.0,  9.0,  6.0,
                -3.0,  0.0, -9.0, -4.0,
            },
            {
                -0.15385, -0.15385, -0.28205, -0.53846,
                -0.07692,  0.12308,  0.02564,  0.03077,
                 0.35897,  0.35897,  0.43590,  0.92308,
                -0.69231, -0.69231, -0.76923, -1.92308,
            }
        },
        {
            {
                 9.0,  3.0,  0.0,  9.0,
                -5.0, -2.0, -6.0, -3.0,
                -4.0,  9.0,  6.0,  4.0,
                -7.0,  6.0,  6.0,  2.0,
            },
            {
                -0.04074, -0.07778,  0.14444, -0.22222,
                -0.07778,  0.03333,  0.36667, -0.33333,
                -0.02901, -0.14630, -0.10926,  0.12963,
                 0.17778,  0.06667, -0.26667,  0.33333,
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
         3.0, -9.0,  7.0,  3.0,
         3.0, -8.0,  2.0, -9.0,
        -4.0,  4.0,  4.0,  1.0,
        -6.0,  5.0, -1.0,  1.0,
    };
    mat4 m2 = {
        8.0,  2.0, 2.0, 2.0,
        3.0, -1.0, 7.0, 0.0,
        7.0,  0.0, 5.0, 4.0,
        6.0, -2.0, 0.0, 5.0,
    };
    mat4 m3  = mat4_mul(m1, m2);

    mat4 res = mat4_mul(m3, mat4_inverse(m2));
    assert(mat4_compare(res, m1) == true);
}


void test_view_matrix4(void) {
    struct { vec4 from, to, up; mat4 view; } tests[] = {
        {
            vec4_make_point (0.0, 0.0,  0.0),
            vec4_make_point (0.0, 0.0, -1.0),
            vec4_make_vector(0.0, 1.0,  0.0),
            mat4_new_transform(),
        },
        {
            vec4_make_point (0.0, 0.0, 0.0),
            vec4_make_point (0.0, 0.0, 1.0),
            vec4_make_vector(0.0, 1.0, 0.0),
            mat4_scale(mat4_new_transform(),
                       -1.0, 1.0, -1.0),
        },
        {
            vec4_make_point (0.0, 0.0, 8.0),
            vec4_make_point (0.0, 0.0, 0.0),
            vec4_make_vector(0.0, 1.0, 0.0),
            mat4_translate(mat4_new_transform(),
                           0.0, 0.0, -8.0),
        },
        {
            vec4_make_point (1.0,  3.0, 2.0),
            vec4_make_point (4.0, -2.0, 8.0),
            vec4_make_vector(1.0,  1.0, 0.0),
            {
                -0.50709, 0.50709,  0.67612, -2.36643,
                 0.76772, 0.60609,  0.12122, -2.82843,
                -0.35857, 0.59761, -0.71714,  0.00000,
                 0.00000, 0.00000,  0.00000,  1.00000,
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
