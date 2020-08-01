
static void answer_chapter3(void) {
    // Question 1
    mat4 iden_inv = mat4_inverse(mat4_identity());

    printf("Q1: What happens when you invert the identity matrix?\n");
    printf("A1: iden == inverse(iden):\n");
    print_mat4(iden_inv);

    printf("\n\n");

    // Question 2
    mat4 mat = {
        8.0,  2.0, 2.0, 2.0,
        3.0, -1.0, 7.0, 0.0,
        7.0,  0.0, 5.0, 4.0,
        6.0, -2.0, 0.0, 5.0,
    };
    mat4 res = mat4_mul(mat, mat4_inverse(mat));

    printf("Q2: What do you get when you multiply a matrix by its inverse?\n");
    printf("A2: mat * inverse(mat) == iden\n");
    print_mat4(res);

    printf("\n\n");

    // Question 3
    mat4 tran_inv = mat4_inverse(mat4_transpose(mat));
    mat4 inv_tran = mat4_transpose(mat4_inverse(mat));

    printf("Q3: Is there any difference between the inverse of the "
           "transpose of a matrix, and the transpose of the inverse?\n");
    printf("A3: inverse(transpose(mat)) == transpose(inverse(matrix))\n");
    print_mat4(tran_inv);
    printf("\n");
    print_mat4(inv_tran);

    printf("\n\n");

    // Question 4
    mat4 iden = mat4_identity();
    iden.m[1][1] = 23.0;
    vec4 res_vec = mat4_mul_vec4(iden, (vec4) { 1.0, 2.0, 3.0, 4.0 });

    printf("Q4: Try changing any single element of the identity matrix "
           "to a different number and multiply it by a tuple, what happens?\n");
    printf("A4: iden[1][1] = 23 -> Y * 23 = ");
    print_vec4(res_vec);
    printf("\n");
}
