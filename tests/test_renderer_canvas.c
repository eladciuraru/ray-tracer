
void test_canvas_init(void) {
    canvas *can = canvas_create(10, 20);

    for (usize i = 0; i < can->length; i++) {
        assert(color3_compare(can->pixels[i], COLOR3_BLACK) == true);
    }

    can = canvas_destroy(can);
}


void test_canvas_operations(void) {
    canvas *can = canvas_create(10, 20);
    canvas_set_pixel(can, 2, 3, COLOR3_RED);

    color3 res = canvas_get_pixel(can, 2, 3);
    assert(color3_compare(res, COLOR3_RED) == true);

    can = canvas_destroy(can);
}


void test_bitmap(void) {
    canvas *can = canvas_create(10, 20);
    for (usize i = 0; i < can->length; i++) {
        can->pixels[i] = COLOR3_BLUE;
    }

    bitmap *bmp   = canvas_as_bitmap(can);
    u32     pixel = 0x000000FF;

    bool pixel_flag = true;
    for (usize i = 0; i < can->length; i++) {
        pixel_flag &= bmp->pixels[i] == pixel;
    }
    assert(pixel_flag == true);

    can = canvas_destroy(can);
    bmp = canvas_bitmap_destroy(bmp);
}


void test_suite_canvas(void) {
    printf("Running tests for renderer_canvas.c\n");

    test_canvas_init();
    test_canvas_operations();
    test_bitmap();

    printf("Succesfully ran all tests\n");
}
