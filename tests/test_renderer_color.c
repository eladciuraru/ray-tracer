
void test_add_colors(void) {
    color3 c1  = { 0.9, 0.6, 0.75 };
    color3 c2  = { 0.7, 0.1, 0.25 };
    color3 sum = { 1.6, 0.7, 1.0  };

    color3 res = color3_add(c1, c2);
    assert(color3_compare(res, sum) == true);
}


void test_sub_colors(void) {
    color3 c1  = { 0.9, 0.6, 0.75 };
    color3 c2  = { 0.7, 0.1, 0.25 };
    color3 sub = { 0.2, 0.5, 0.5  };

    color3 res = color3_sub(c1, c2);
    assert(color3_compare(res, sub) == true);
}


void test_scalar_mul_color(void) {
    color3 c      = { 0.2, 0.3, 0.4 };
    color3 mul    = { 0.4, 0.6, 0.8 };
    f64    scalar = 2.0;

    color3 res = color3_scalar_mul(c, scalar);
    assert(color3_compare(res, mul) == true);
}


void test_hadamard_product_color(void) {
    color3 c1  = { 1.0, 0.2, 0.4  };
    color3 c2  = { 0.9, 1.0, 0.1  };
    color3 mul = { 0.9, 0.2, 0.04 };

    color3 res = color3_mul(c1, c2);
    assert(color3_compare(res, mul) == true);
}


void test_suite_color(void) {
    printf("Running tests for renderer_color.c\n");

    test_add_colors();
    test_sub_colors();
    test_scalar_mul_color();
    test_hadamard_product_color();

    printf("Succesfully ran all tests\n");
}
