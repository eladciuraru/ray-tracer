// TODO: Change the tests later
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "renderer/renderer.c"


void test_canvas_init(void) {
    canvas can   = canvas_create(10, 20);
    color3 black = { 0.0f };

    for (usize i = 0; i < can.length; i++) {
        color3 *c = &can.pixels[i];

        assert(color3_compare(c, &black) == true);
    }
}


void test_canvas_operations(void) {
    canvas can = canvas_create(10, 20);
    color3 red = { 1.0f, 0.0f, 0.0f };
    canvas_set_pixel(&can, 2, 3, &red);

    color3 *res = canvas_get_pixel(&can, 2, 3);
    assert(color3_compare(res, &red) == true);
}


int main(void) {
    printf("Running tests for renderer_color.c\n");

    test_canvas_init();
    test_canvas_operations();

    printf("Succesfully ran all tests\n");

    return EXIT_SUCCESS;
}
