
static void set_pixel_scaled(canvas *can, vec4 point, color3 color, u32 scale) {
    for (u32 height = 0; height < scale; height++) {
        for (u32 width = 0; width < scale; width++) {
            u32 x = (u32) point.x + width;
            u32 y = (u32) point.y + height;

            canvas_set_pixel(can, x, y, color);
        }
    }
}


static void answer_chapter4(void) {
    const u32 NUM_OF_POINTS = 12;
    const u32 SCALE_SIZE    = 5;

    canvas *can    = canvas_create(500, 500);
    color3  color  = color3_new(1.0f, 0.25f, 0.75f);
    vec4    middle = vec4_make_point(can->width / 2.0f,
                                     can->height / 2.0f,
                                     0.0f);
    f32     radius = can->width * 3.0f / 8.0f;
    f32     rotate = 2.0f * (f32) M_PI / NUM_OF_POINTS;

    for (u32 i = 0; i < NUM_OF_POINTS; i++) {
        mat4 tran = mat4_new_transform();
        tran      = mat4_rotate_z(tran, rotate * i);
        tran      = mat4_scale(tran, radius, radius, 0.0f);
        tran      = mat4_translate(tran, middle.x, middle.y, middle.z);

        vec4 point = vec4_make_point(0.0f, 1.0f, 0.0f);
        point      = mat4_mul_vec4(tran, point);
        set_pixel_scaled(can, point, color, SCALE_SIZE);
    }

    write_canvas(can, "answers_output\\chapter4\\clock.bmp");
    can = canvas_delete(can);
}
