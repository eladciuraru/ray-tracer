
static void answer_chapter2(void) {
    vec4 velocity = vec4_make_vector(1.0f, 5.0f, 0.0f);
    velocity      = vec4_normalize(velocity);
    velocity      = vec4_scalar_mul(velocity, 10.0f);

    projectile proj = {
        .position = vec4_make_point(0.0f, 250.0f, 0.0f),
        .velocity = velocity,
    };
    environment env = {
        .gravity = vec4_make_vector( 0.0f, -0.1f, 0.0f),
        .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
    };

    canvas *can = canvas_create(250, 800);
    color3  col = { 0.75f, 0.25f, 0.25f };
    for (usize i = 1; proj.position.y > 0.0f; i++) {
        vec4 pos = proj.position;

        u32 x = (u32) roundf(pos.x);
        u32 y = (u32) roundf(can->height - 1 - pos.y);
        canvas_set_pixel(can, x, y, col);

        proj = tick(&env, &proj);
    }

    write_canvas(can, "answers_output\\chapter2\\4.bmp");
    can = canvas_delete(can);
}
