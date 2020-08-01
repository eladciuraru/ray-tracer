
camera camera_new(u32 hsize, u32 vsize, f64 field) {
    camera cam = {
        .hsize     = hsize,
        .vsize     = vsize,
        .field     = field,
        .transform = mat4_new_transform(),
    };

    f64 half_view = f64_tan(cam.field / 2.0);
    f64 aspect    = (f64) cam.hsize / (f64) cam.vsize;
    if (aspect >= 1.0) {
        cam.half_width  = half_view;
        cam.half_height = half_view / aspect;
    } else {
        cam.half_width  = half_view * aspect;
        cam.half_height = half_view;
    }
    cam.pixel_size = (cam.half_width * 2.0) / (f64) cam.hsize;

    return cam;
}


ray camera_ray_for_pixel(camera cam, u32 x, u32 y) {
    f64 xoffset = (x + 0.5) * cam.pixel_size;
    f64 yoffset = (y + 0.5) * cam.pixel_size;

    vec4 world_point = vec4_make_point(cam.half_width - xoffset,
                                       cam.half_height - yoffset,
                                       -1.0);

    mat4 inv       = mat4_inverse(cam.transform);
    vec4 pixel     = mat4_mul_vec4(inv, world_point);
    vec4 origin    = mat4_mul_vec4(inv, vec4_make_point(0.0, 0.0, 0.0));
    vec4 direction = vec4_normalize(vec4_sub(pixel, origin));

    return ray_new(origin, direction);
}


canvas *camera_render_world(camera cam, world_map *world) {
    canvas *can = canvas_create(cam.hsize, cam.vsize);

    for (u32 y = 0; y < cam.vsize; y++) {
        for (u32 x = 0; x < cam.hsize; x++) {
            ray    r = camera_ray_for_pixel(cam, x, y);
            color3 c = world_map_color_at(world, r);

            canvas_set_pixel(can, x, y, c);
        }
    }

    return can;
}
