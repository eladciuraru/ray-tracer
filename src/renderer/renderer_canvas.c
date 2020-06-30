
canvas *canvas_create(u32 width, u32 height) {
    u32     len = width * height;
    canvas *can = (canvas *) _allocate_buffer(sizeof(canvas) +
                                              len * sizeof(color3));
    can->width  = width;
    can->height = height;
    can->length = len;

    return can;
}


void canvas_set_pixel(canvas *can, u32 x, u32 y, color3 color) {
    u32 index = y * can->width + x;
    _ASSERT(0 <= index && index < can->length);

    can->pixels[index] = color;
}


color3 canvas_get_pixel(canvas *can, u32 x, u32 y) {
    u32 index = y * can->width + x;
    _ASSERT(0 <= index && index < can->length);

    return can->pixels[index];
}


canvas *canvas_destroy(canvas *can) {
    return _deallocate(can);
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
        bmp->pixels[i] = color3_as_u32(can->pixels[i]);
    }

    return bmp;
}


bitmap *canvas_bitmap_destroy(bitmap *bmp) {
    return _deallocate(bmp);
}
