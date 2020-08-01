
static void answer_chapter8(void) {
    sphere floor            = sphere_new();
    floor.transform         = mat4_scale(floor.transform, 10.0, 0.01, 10.0);
    floor.material.color    = color3_new(1.0, 0.9, 0.9);
    floor.material.specular = 0;

    sphere left_wall    = sphere_new();
    left_wall.transform = mat4_scale(left_wall.transform, 10.0, 0.01, 10.0);
    left_wall.transform = mat4_rotate_x(left_wall.transform, M_PI_2);
    left_wall.transform = mat4_rotate_y(left_wall.transform, -M_PI_4);
    left_wall.transform = mat4_translate(left_wall.transform, 0.0, 0.0, 5.0);
    left_wall.material  = floor.material;

    sphere right_wall    = sphere_new();
    right_wall.transform = mat4_scale(right_wall.transform, 10.0, 0.01, 10.0);
    right_wall.transform = mat4_rotate_x(right_wall.transform, M_PI_2);
    right_wall.transform = mat4_rotate_y(right_wall.transform, M_PI_4);
    right_wall.transform = mat4_translate(right_wall.transform, 0.0, 0.0, 5.0);
    right_wall.material  = floor.material;

    sphere middle_s            = sphere_new();
    middle_s.transform         = mat4_translate(middle_s.transform, -0.5, 1.0, 0.5);
    middle_s.material.color    = color3_new(0.1, 1.0, 0.5);
    middle_s.material.diffuse  = 0.7;
    middle_s.material.specular = 0.3;

    sphere right_s            = sphere_new();
    right_s.transform         = mat4_scale(right_s.transform, 0.5, 0.5, 0.5);
    right_s.transform         = mat4_translate(right_s.transform, 1.5, 0.5, -0.5);
    right_s.material.color    = color3_new(0.5, 1.0, 0.1);
    right_s.material.diffuse  = 0.7;
    right_s.material.specular = 0.3;

    sphere left_s            = sphere_new();
    left_s.transform         = mat4_scale(left_s.transform, 0.33, 0.33, 0.33);
    left_s.transform         = mat4_translate(left_s.transform, -1.5, 0.33, -0.75);
    left_s.material.color    = color3_new(1.0, 0.8, 0.1);
    left_s.material.diffuse  = 0.7;
    left_s.material.specular = 0.3;

    world_map *world = world_map_create();
    world->light     = light_point_new(vec4_make_point(-10.0, 10.0, -10.0),
                                       COLOR3_WHITE);
    world->s_list    = sphere_list_append(world->s_list, floor);
    world->s_list    = sphere_list_append(world->s_list, left_wall);
    world->s_list    = sphere_list_append(world->s_list, right_wall);
    world->s_list    = sphere_list_append(world->s_list, middle_s);
    world->s_list    = sphere_list_append(world->s_list, right_s);
    world->s_list    = sphere_list_append(world->s_list, left_s);

    camera cam = camera_new(250, 150, M_PI / 3.0);
    cam.transform = mat4_view(vec4_make_point (0.0, 1.5, -5.0),
                              vec4_make_point (0.0, 1.0,  0.0),
                              vec4_make_vector(0.0, 1.0,  0.0));

    canvas *can = camera_render_world(cam, world);

    write_canvas(can, "answers_output/chapter8/shadow_small.bmp");

    can   = canvas_destroy(can);
    world = world_map_destroy(world);
}
