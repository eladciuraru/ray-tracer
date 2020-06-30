
static void answer_chapter6(void) {
    const u32 CANVAS_PIXELS  = 250;
    // Next values are in world's units
    const f32 WALL_SIZE      = 7.0f;
    const f32 HALF_WALL_SIZE = WALL_SIZE / 2.0f;
    const f32 PIXEL_SIZE     = (f32) WALL_SIZE / (f32) CANVAS_PIXELS;
    const f32 WALL_Z_POS     = 10.0f;

    canvas *can = canvas_create(CANVAS_PIXELS, CANVAS_PIXELS);

    vec4    ray_origin = vec4_make_point(0.0f, 0.0f, -5.0f);
    sphere  s          = sphere_new();
    s.material.color   = color3_new(1.0f, 0.2f, 1.0f);

    light_point light = light_point_new(vec4_make_point(10.0f, 10.0f, -10.0f),
                                        COLOR3_WHITE);

    vec4 wall_pos = vec4_make_point(0.0f, 0.0f, WALL_Z_POS);
    for (u32 row = 0; row < can->height; row++) {
        // Translate from canvas pixel to world pixel
        // and center the wall
        wall_pos.y = HALF_WALL_SIZE - row * PIXEL_SIZE;

        for (u32 col = 0; col < can->width; col++) {
            // Translate from canvas pixel to world pixel
            // and center the wall
            wall_pos.x = HALF_WALL_SIZE - col * PIXEL_SIZE;

            vec4 wall_dir = vec4_sub(wall_pos, ray_origin);
            ray  r        = ray_new(ray_origin, vec4_normalize(wall_dir));

            intersect *list = sphere_intersect(&s, &r);
            intersect *hit  = intersect_list_hit(list);
            if (hit != INTERSECT_NO_HIT) {
                vec4 point  = ray_position(&r, hit->value);
                vec4 normal = sphere_normal_at(hit->s, point);
                vec4 view   = vec4_negate(r.direction);

                color3 color = light_point_color(light, hit->s->material, point, view, normal);
                canvas_set_pixel(can, col, row, color);
            }

            list = intersect_list_destroy(list);
        }
    }

    write_canvas(can, "answers_output\\chapter6\\sphere_light_small.bmp");
    can = canvas_destroy(can);
}
