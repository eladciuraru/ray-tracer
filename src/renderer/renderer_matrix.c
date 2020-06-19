
mat4 mat4_identity(void) {
    return (mat4) {
        .m[0][0] = 1,
        .m[1][1] = 1,
        .m[2][2] = 1,
        .m[3][3] = 1,
    };
}


bool mat4_compare(mat4 m1, mat4 m2) {
    for (u32 row = 0; row < MAT4_SIZE; row++) {
        for (u32 col = 0; col < MAT4_SIZE; col++) {
            bool equal = f32_compare(m1.m[row][col],
                                     m2.m[row][col]);

            if (equal == false) {
                return false;
            }
        }
    }

    return true;
}


mat4 mat4_mul(mat4 m1, mat4 m2) {
    mat4 mul = { 0.0f };

    for (u32 row = 0; row < MAT4_SIZE; row++) {
        for (u32 col = 0; col < MAT4_SIZE; col++) {
            for (u32 i = 0; i < MAT4_SIZE; i++) {
                mul.m[row][col] += m1.m[row][i] * m2.m[i][col];
            }
        }
    }

    return mul;
}


vec4 mat4_mul_vec4(mat4 m, vec4 v) {
    return (vec4) {
        m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w,
        m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w,
        m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w,
        m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w,
    };
}


mat4 mat4_transpose(mat4 m) {
    mat4 res;

    for (u32 row = 0; row < MAT4_SIZE; row++) {
        for (u32 col = 0; col < MAT4_SIZE; col++) {
            res.m[row][col] = m.m[col][row];
        }
    }

    return res;
}


mat3 mat4_submatrix(mat4 m, u32 row, u32 col) {
    _ASSERT(row < MAT4_SIZE && col < MAT4_SIZE);

    mat3 res     = { 0.0f };
    u32  sub_row = 0;
    for (u32 row_ = 0; row_ < MAT4_SIZE; row_++) {
        if (row_ == row) continue;

        for (u32 col_ = 0, sub_col = 0; col_ < MAT4_SIZE; col_++) {
            if (col_ == col) continue;

            res.m[sub_row][sub_col++] = m.m[row_][col_];
        }
        sub_row++;
    }

    return res;
}


f32 mat4_minor(mat4 m, u32 row, u32 col) {
    _ASSERT(row < MAT4_SIZE && col < MAT4_SIZE);

    mat3 subm  = mat4_submatrix(m, row, col);
    f32  minor = mat3_determinant(subm);

    return minor;
}


f32 mat4_cofactor(mat4 m, u32 row, u32 col) {
    _ASSERT(row < MAT4_SIZE && col < MAT4_SIZE);

    f32 minor = mat4_minor(m, row, col);

    return ((row + col) % 2 == 0) ? minor : -minor;
}


f32 mat4_determinant(mat4 m) {
    f32 det = 0.0f;

    for (u32 col = 0; col < MAT4_SIZE; col++) {
        det += m.m[0][col] * mat4_cofactor(m, 0, col);
    }

    return det;
}


bool mat4_is_invertible(mat4 m) {
    return !f32_compare(mat4_determinant(m), 0.0f);
}


mat4 mat4_inverse(mat4 m) {
    mat4 res = { 0.0f };
    f32  det = mat4_determinant(m);

    for (u32 row = 0; row < MAT4_SIZE; row++) {
        for (u32 col = 0; col < MAT4_SIZE; col++) {
            res.m[col][row] = mat4_cofactor(m, row, col) / det;
        }
    }

    return res;
}


mat4 mat4_translate(mat4 m, f32 x, f32 y, f32 z) {
    mat4 translate = mat4_identity();
    translate.m[0][3] = x;
    translate.m[1][3] = y;
    translate.m[2][3] = z;

    return mat4_mul(translate, m);
}


mat4 mat4_scale(mat4 m, f32 x, f32 y, f32 z) {
    mat4 scale = mat4_identity();
    scale.m[0][0] = x;
    scale.m[1][1] = y;
    scale.m[2][2] = z;

    return mat4_mul(scale, m);
}


mat4 mat4_rotate_x(mat4 m, f32 radians) {
    mat4 rotate_x = mat4_identity();
    f32  sinrad   = sinf(radians);
    f32  cosrad   = cosf(radians);

    rotate_x.m[1][1] =  cosrad;
    rotate_x.m[1][2] = -sinrad;
    rotate_x.m[2][1] =  sinrad;
    rotate_x.m[2][2] =  cosrad;

    return mat4_mul(rotate_x, m);
}


mat4 mat4_rotate_y(mat4 m, f32 radians) {
    mat4 rotate_y = mat4_identity();
    f32  sinrad   = sinf(radians);
    f32  cosrad   = cosf(radians);

    rotate_y.m[0][0] =  cosrad;
    rotate_y.m[0][2] =  sinrad;
    rotate_y.m[2][0] = -sinrad;
    rotate_y.m[2][2] =  cosrad;

    return mat4_mul(rotate_y, m);
}


mat4 mat4_rotate_z(mat4 m, f32 radians) {
    mat4 rotate_z = mat4_identity();
    f32  sinrad   = sinf(radians);
    f32  cosrad   = cosf(radians);

    rotate_z.m[0][0] =  cosrad;
    rotate_z.m[0][1] = -sinrad;
    rotate_z.m[1][0] =  sinrad;
    rotate_z.m[1][1] =  cosrad;

    return mat4_mul(rotate_z, m);
}


mat4 mat4_shearing(mat4 m, f32 xy, f32 xz, f32 yx, f32 yz, f32 zx, f32 zy) {
    mat4 shearing = mat4_identity();

    shearing.m[0][1] = xy;
    shearing.m[0][2] = xz;
    shearing.m[1][0] = yx;
    shearing.m[1][2] = yz;
    shearing.m[2][0] = zx;
    shearing.m[2][1] = zy;

    return mat4_mul(shearing, m);
}


bool mat3_compare(mat3 m1, mat3 m2) {
    for (u32 row = 0; row < MAT3_SIZE; row++) {
        for (u32 col = 0; col < MAT3_SIZE; col++) {
            bool equal = f32_compare(m1.m[row][col],
                                     m2.m[row][col]);

            if (equal == false) {
                return false;
            }
        }
    }

    return true;
}


mat2 mat3_submatrix(mat3 m, u32 row, u32 col) {
    _ASSERT(row < MAT3_SIZE && col < MAT3_SIZE);

    mat2 res     = { 0.0f };
    u32  sub_row = 0;
    for (u32 row_ = 0; row_ < MAT3_SIZE; row_++) {
        if (row_ == row) continue;

        for (u32 col_ = 0, sub_col = 0; col_ < MAT3_SIZE; col_++) {
            if (col_ == col) continue;

            res.m[sub_row][sub_col++] = m.m[row_][col_];
        }
        sub_row++;
    }

    return res;
}


f32 mat3_minor(mat3 m, u32 row, u32 col) {
    _ASSERT(row < MAT3_SIZE && col < MAT3_SIZE);

    mat2 subm  = mat3_submatrix(m, row, col);
    f32  minor = mat2_determinant(subm);

    return minor;
}


f32 mat3_cofactor(mat3 m, u32 row, u32 col) {
    _ASSERT(row < MAT3_SIZE && col < MAT3_SIZE);

    f32 minor = mat3_minor(m, row, col);

    return ((row + col) % 2 == 0) ? minor : -minor;
}


f32 mat3_determinant(mat3 m) {
    f32 det = 0.0f;

    for (u32 col = 0; col < MAT3_SIZE; col++) {
        det += m.m[0][col] * mat3_cofactor(m, 0, col);
    }

    return det;
}


bool mat2_compare(mat2 m1, mat2 m2) {
    for (u32 row = 0; row < MAT2_SIZE; row++) {
        for (u32 col = 0; col < MAT2_SIZE; col++) {
            bool equal = f32_compare(m1.m[row][col],
                                     m2.m[row][col]);

            if (equal == false) {
                return false;
            }
        }
    }

    return true;
}


f32 mat2_determinant(mat2 m) {
    return m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
}
