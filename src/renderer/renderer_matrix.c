
inline mat4 mat4_identity(void) {
    return (mat4) {
        .m[0][0] = 1,
        .m[1][1] = 1,
        .m[2][2] = 1,
        .m[3][3] = 1,
    };
}


bool mat4_compare(mat4 *m1, mat4 *m2) {
    for (usize row = 0; row < MAT4_SIZE; row++) {
        for (usize col = 0; col < MAT4_SIZE; col++) {
            bool equal = f32_compare(m1->m[row][col],
                                     m2->m[row][col]);

            if (equal == false) {
                return false;
            }
        }
    }

    return true;
}


mat4 mat4_mul(mat4 *m1, mat4 *m2) {
    mat4 mul = { 0.0f };

    for (usize row = 0; row < MAT4_SIZE; row++) {
        for (usize col = 0; col < MAT4_SIZE; col++) {
            for (usize i = 0; i < MAT4_SIZE; i++) {
                mul.m[row][col] += m1->m[row][i] * m2->m[i][col];
            }
        }
    }

    return mul;
}


vec4 mat4_mul_vec4(mat4 *m, vec4 *v) {
    return (vec4) {
        m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w,
        m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w,
        m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w,
        m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w,
    };
}


mat4 mat4_transpose(mat4 *m) {
    mat4 res;

    for (usize row = 0; row < MAT4_SIZE; row++) {
        for (usize col = 0; col < MAT4_SIZE; col++) {
            res.m[row][col] = m->m[col][row];
        }
    }

    return res;
}


bool mat3_compare(mat3 *m1, mat3 *m2) {
    for (usize row = 0; row < MAT3_SIZE; row++) {
        for (usize col = 0; col < MAT3_SIZE; col++) {
            bool equal = f32_compare(m1->m[row][col],
                                     m2->m[row][col]);

            if (equal == false) {
                return false;
            }
        }
    }

    return true;
}


mat2 mat3_submatrix(mat3 *m, usize row, usize col) {
    _ASSERT(row < MAT3_SIZE && col < MAT3_SIZE);

    mat2  res = { 0.0f };
    usize r   = 0;
    usize c   = 0;

    for (usize row_ = 0; row_ < MAT3_SIZE; row_++) {
        if (row_ == row) continue;

        c = 0;
        for (usize col_ = 0; col_ < MAT3_SIZE; col_++) {
            if (col_ == col) continue;

            res.m[r][c++] = m->m[row_][col_];
        }
        r++;
    }

    return res;
}


bool mat2_compare(mat2 *m1, mat2 *m2) {
    for (usize row = 0; row < MAT2_SIZE; row++) {
        for (usize col = 0; col < MAT2_SIZE; col++) {
            bool equal = f32_compare(m1->m[row][col],
                                     m2->m[row][col]);

            if (equal == false) {
                return false;
            }
        }
    }

    return true;
}


f32 mat2_determinant(mat2 *m) {
    return m->m[0][0] * m->m[1][1] - m->m[0][1] * m->m[1][0];
}
