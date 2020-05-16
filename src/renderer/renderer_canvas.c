
canvas canvas_create(u32 width, u32 height) {
    canvas can = {
        .width  = width,
        .height = height,
        .length = width * height,
    };
    can.pixels = _allocate_zeroed(can.length * sizeof(color3));

    return can;
}


inline void canvas_set_pixel(canvas *can, u32 x, u32 y, color3 *color) {
    u32 index = y * can->width + x;
    _ASSERT(0 <= index && index < can->length);

    can->pixels[index] = *color;
}


inline color3 *canvas_get_pixel(canvas *can, u32 x, u32 y) {
    u32 index = y * can->width + x;
    _ASSERT(0 <= index && index < can->length);

    return &can->pixels[index];
}
