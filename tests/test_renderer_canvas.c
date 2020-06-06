
void test_canvas_init(void) {
    canvas *can   = canvas_create(10, 20);
    color3  black = { 0.0f };

    for (usize i = 0; i < can->length; i++) {
        color3 *c = &can->pixels[i];

        assert(color3_compare(c, &black) == true);
    }
}


void test_canvas_operations(void) {
    canvas *can = canvas_create(10, 20);
    color3  red = { 1.0f, 0.0f, 0.0f };
    canvas_set_pixel(can, 2, 3, &red);

    color3 *res = canvas_get_pixel(can, 2, 3);
    assert(color3_compare(res, &red) == true);
}


void test_bitmap(void) {
    canvas *can  = canvas_create(10, 20);
    color3  blue = { 0.0f, 0.0f, 1.0f };

    for (usize i = 0; i < can->length; i++) {
        can->pixels[i] = blue;
    }

    bitmap *bmp   = canvas_as_bitmap(can);
    u32     pixel = 0x000000FF;

    bool pixel_flag = true;
    for (usize i = 0; i < can->length; i++) {
        pixel_flag &= bmp->pixels[i] == pixel;
    }
    assert(pixel_flag == true);
}


void test_suite_canvas(void) {
    printf("Running tests for renderer_canvas.c\n");

    test_canvas_init();
    test_canvas_operations();
    test_bitmap();

    printf("Succesfully ran all tests\n");
}
