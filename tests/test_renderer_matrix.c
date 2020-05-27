// TODO: Change the tests later
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "renderer/renderer.h"


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

    mat4 res = mat4_mul(&m1, &m2);
    assert(mat4_compare(&res, &mul) == true);
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

    vec4 res = mat4_mul_vec4(&mat, &vec);
    assert(vec4_compare(&res, &mul) == true);
}


void test_mul_matrix4_identity(void) {
    mat4 mat  = {
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 4.0f, 4.0f, 2.0f,
        8.0f, 6.0f, 4.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    mat4 iden = mat4_identity();

    mat4 res = mat4_mul(&mat, &iden);
    assert(mat4_compare(&res, &mat) == true);
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

    mat4 res = mat4_transpose(&mat);
    assert(mat4_compare(&res, &tran) == true);
}


void test_determinant_matrix2(void) {
    mat2 mat = {
         1.0f, 5.0f,
        -3.0f, 2.0f
    };
    f32 det  = 17.0f;

    f32 res = mat2_determinant(&mat);
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

    mat2 res = mat3_submatrix(&mat, 0, 2);
    assert(mat2_compare(&res, &subm) == true);
}


// void test_submatrix_matrix4(void) {
//     mat4 mat  = {
//         -6.0f, 1.0f,  1.0f, 6.0f,
//         -8.0f, 5.0f,  8.0f, 6.0f,
//         -1.0f, 0.0f,  8.0f, 2.0f,
//         -7.0f, 1.0f, -1.0f, 1.0f,
//     };
//     mat3 subm = {
//         -6.0f,  1.0f, 6.0f,
//         -8.0f,  8.0f, 6.0f,
//         -7.0f, -1.0f, 1.0f,
//     };

//     mat2 res = mat4_submatrix(&mat, 0, 2);
//     assert(mat3_compare(&res, &subm) == true);
// }


int main(void) {
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
    // test_submatrix_matrix4();

    printf("Succesfully ran all tests\n");

    return EXIT_SUCCESS;
}
