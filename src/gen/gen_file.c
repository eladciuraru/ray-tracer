
static u32 get_file_size(cstring file_path) {
    struct _stat stat  = { 0 };

    _stat(file_path, &stat);

    return (u32) stat.st_size;
}


static bool load_file_into(cstring file_path, cstring buff, u32 len) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        return false;
    }

    u32 read_count = (u32) fread(buff, sizeof(buff[0]), len, file);

    fclose(file);

    return read_count == len;
}
