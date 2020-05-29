
canvas canvas_create(u32 width, u32 height) {
    canvas can = {
        .width  = width,
        .height = height,
        .length = width * height,
    };
    can.pixels = (color3 *) _allocate_buffer(can.length * sizeof(color3));

    return can;
}


void canvas_set_pixel(canvas *can, u32 x, u32 y, color3 *color) {
    u32 index = y * can->width + x;
    _ASSERT(0 <= index && index < can->length);

    can->pixels[index] = *color;
}


color3 *canvas_get_pixel(canvas *can, u32 x, u32 y) {
    u32 index = y * can->width + x;
    _ASSERT(0 <= index && index < can->length);

    return &can->pixels[index];
}


bitmap *canvas_as_bitmap(canvas *can) {
    usize   bmp_size = sizeof(bitmap) + (can->length * sizeof(u32));
    bitmap *bmp      = (bitmap *) _allocate_buffer(bmp_size);

    // Set up file header
    bmp->header = (bitmap_header) {
        .magic      = BITMAP_MAGIC,
        .file_size  = (u32) bmp_size,
        .pix_offset = BITMAP_PIX_OFFSET,
    };

    // Set up bitmap info
    bmp->info = (bitmap_info) {
        .info_size = sizeof(bitmap_info),
        .width     =  (i32) can->width,
        .height    = -(i32) can->height,  // Minus height for top down bitmap
        .planes    = 1,
        .bit_count = BITMAP_BPP,
    };

    for (usize i = 0; i < can->length; i++) {
        bmp->pixels[i] = color3_as_u32(&can->pixels[i]);
    }

    return bmp;
}
