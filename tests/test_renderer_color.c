
void test_add_colors(void) {
    color3 c1  = { 0.9f, 0.6f, 0.75f };
    color3 c2  = { 0.7f, 0.1f, 0.25f };
    color3 sum = { 1.6f, 0.7f, 1.0f  };

    color3 res = color3_add(&c1, &c2);
    assert(color3_compare(&res, &sum) == true);
}


void test_sub_colors(void) {
    color3 c1  = { 0.9f, 0.6f, 0.75f };
    color3 c2  = { 0.7f, 0.1f, 0.25f };
    color3 sub = { 0.2f, 0.5f, 0.5f  };

    color3 res = color3_sub(&c1, &c2);
    assert(color3_compare(&res, &sub) == true);
}


void test_scalar_mul_color(void) {
    color3 c      = { 0.2f, 0.3f, 0.4f };
    color3 mul    = { 0.4f, 0.6f, 0.8f };
    f32    scalar = 2.0f;

    color3 res = color3_scalar_mul(&c, scalar);
    assert(color3_compare(&res, &mul) == true);
}


void test_hadamard_product_color(void) {
    color3 c1  = { 1.0f, 0.2f, 0.4f  };
    color3 c2  = { 0.9f, 1.0f, 0.1f  };
    color3 mul = { 0.9f, 0.2f, 0.04f };

    color3 res = color3_mul(&c1, &c2);
    assert(color3_compare(&res, &mul) == true);
}


void test_suite_color(void) {
    printf("Running tests for renderer_color.c\n");

    test_add_colors();
    test_sub_colors();
    test_scalar_mul_color();
    test_hadamard_product_color();

    printf("Succesfully ran all tests\n");
}
