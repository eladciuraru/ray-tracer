
static void answer_chapter7(void) {
    sphere floor            = sphere_new();
    floor.transform         = mat4_scale(floor.transform, 10.0f, 0.01f, 10.0f);
    floor.material.color    = color3_new(1.0f, 0.9f, 0.9f);
    floor.material.specular = 0;

    sphere left_wall    = sphere_new();
    left_wall.transform = mat4_scale(left_wall.transform, 10.0f, 0.01f, 10.0f);
    left_wall.transform = mat4_rotate_x(left_wall.transform, (f32) M_PI_2);
    left_wall.transform = mat4_rotate_y(left_wall.transform, (f32) -M_PI_4);
    left_wall.transform = mat4_translate(left_wall.transform, 0.0f, 0.0f, 5.0f);
    left_wall.material  = floor.material;

    sphere right_wall    = sphere_new();
    right_wall.transform = mat4_scale(right_wall.transform, 10.0f, 0.01f, 10.0f);
    right_wall.transform = mat4_rotate_x(right_wall.transform, (f32) M_PI_2);
    right_wall.transform = mat4_rotate_y(right_wall.transform, (f32) M_PI_4);
    right_wall.transform = mat4_translate(right_wall.transform, 0.0f, 0.0f, 5.0f);
    right_wall.material  = floor.material;

    sphere middle_s            = sphere_new();
    middle_s.transform         = mat4_translate(middle_s.transform, -0.5f, 1.0f, 0.5f);
    middle_s.material.color    = color3_new(0.1f, 1.0f, 0.5f);
    middle_s.material.diffuse  = 0.7f;
    middle_s.material.specular = 0.3f;

    sphere right_s            = sphere_new();
    right_s.transform         = mat4_scale(right_s.transform, 0.5f, 0.5f, 0.5f);
    right_s.transform         = mat4_translate(right_s.transform, 1.5f, 0.5f, -0.5f);
    right_s.material.color    = color3_new(0.5f, 1.0f, 0.1f);
    right_s.material.diffuse  = 0.7f;
    right_s.material.specular = 0.3f;

    sphere left_s            = sphere_new();
    left_s.transform         = mat4_scale(left_s.transform, 0.33f, 0.33f, 0.33f);
    left_s.transform         = mat4_translate(left_s.transform, -1.5f, 0.33f, -0.75f);
    left_s.material.color    = color3_new(1.0f, 0.8f, 0.1f);
    left_s.material.diffuse  = 0.7f;
    left_s.material.specular = 0.3f;

    world_map *world = world_map_create();
    world->light     = light_point_new(vec4_make_point(-10.0f, 10.0f, -10.0f),
                                       COLOR3_WHITE);
    world->s_list    = sphere_list_append(world->s_list, floor);
    world->s_list    = sphere_list_append(world->s_list, left_wall);
    world->s_list    = sphere_list_append(world->s_list, right_wall);
    world->s_list    = sphere_list_append(world->s_list, middle_s);
    world->s_list    = sphere_list_append(world->s_list, right_s);
    world->s_list    = sphere_list_append(world->s_list, left_s);

    camera cam = camera_new(500, 250, (f32) M_PI / 3.0f);
    cam.transform = mat4_view(vec4_make_point(0.0f, 1.5f, -5.0f),
                              vec4_make_point(0.0f, 1.0f,  0.0f),
                              vec4_make_vector(0.0f, 1.0f, 0.0f));

    canvas *can = camera_render_world(cam, world);

    write_canvas(can, "answers_output/chapter7/scene.bmp");

    can   = canvas_destroy(can);
    world = world_map_destroy(world);
}
