
static void answer_chapter2(void) {
    vec4 velocity = vec4_make_vector(1.0, 5.0, 0.0);
    velocity      = vec4_normalize(velocity);
    velocity      = vec4_scalar_mul(velocity, 10.0);

    projectile proj = {
        .position = vec4_make_point(0.0, 250.0, 0.0),
        .velocity = velocity,
    };
    environment env = {
        .gravity = vec4_make_vector( 0.0, -0.1, 0.0),
        .wind    = vec4_make_vector(-0.01, 0.0, 0.0),
    };

    canvas *can = canvas_create(250, 800);
    color3  col = { 0.75, 0.25, 0.25 };
    for (usize i = 1; proj.position.y > 0.0; i++) {
        vec4 pos = proj.position;

        u32 x = (u32) round(pos.x);
        u32 y = (u32) round(can->height - 1 - pos.y);
        canvas_set_pixel(can, x, y, col);

        proj = tick(&env, &proj);
    }

    write_canvas(can, "answers_output\\chapter2\\4.bmp");
    can = canvas_destroy(can);
}
