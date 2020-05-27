
static void write_canvas(canvas *can, cstring filename) {
    FILE *file = fopen(filename, "wb");
    assert(file != NULL);

    bitmap *bmp     = canvas_as_bitmap(can);
    usize   written = fwrite(bmp, sizeof(u8), bmp->header.file_size, file);
    assert(written == bmp->header.file_size);

    fclose(file);
}
