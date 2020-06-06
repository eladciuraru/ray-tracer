
static void write_canvas(canvas *can, cstring filename) {
    FILE *file = fopen(filename, "wb");
    assert(file != NULL);

    bitmap *bmp     = canvas_as_bitmap(can);
    usize   written = fwrite(bmp, sizeof(u8), bmp->header.file_size, file);
    assert(written == bmp->header.file_size);

    bmp = canvas_bitmap_delete(bmp);
    fclose(file);
}


static void print_vec4(vec4 *vec) {
    printf("{ %.3f, %.3f, %.3f, %.3f }",
           vec->x, vec->y, vec->z, vec->w);
}


static void print_mat4(mat4 *mat) {
    printf("{\n");
    for (usize row = 0; row < MAT4_SIZE; row++) {
        printf("\t");

        for (usize col = 0; col < MAT4_SIZE; col++) {
            printf("%.3f, ", mat->m[row][col]);
        }

        printf("\n");
    }
    printf("}");
}
