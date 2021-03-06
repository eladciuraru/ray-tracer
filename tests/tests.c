// Temporary unit test file
// TODO: Create minimal unit test API
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// Why?
#define _USE_MATH_DEFINES
#include <math.h>

#include "renderer/renderer.h"

#include "./test_renderer_vector.c"
#include "./test_renderer_color.c"
#include "./test_renderer_canvas.c"
#include "./test_renderer_matrix.c"
#include "./test_renderer_transform.c"
#include "./test_renderer_ray_sphere.c"
#include "./test_renderer_light.c"
#include "./test_renderer_world.c"
#include "./test_renderer_camera.c"


int main(void) {
    test_suite_vector();
    test_suite_color();
    test_suite_canvas();
    test_suite_matrix();
    test_suite_transform();
    test_suite_ray_sphere();
    test_suite_light();
    test_suite_world();
    test_suite_camera();

    return EXIT_SUCCESS;
}
