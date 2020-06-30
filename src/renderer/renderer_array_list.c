// This is a base implementation for dynamic size array.
// This API is for internal use, this will not be exported as is,
// but by other wrapper APIs
// This is a lame attempt to mimic Golang array slices API.


typedef struct _array_list {
    u32 magic;  // This is for debugging only
    u32 limit;
    u32 length;
    u8  raw_buffer[];
} array_list;


#define _ARRAY_LIST_MAGIC            'LRRA'
#define _ARRAY_LIST_DEFAULT_LIMIT    64
#define _ARRAY_LIST_STEP_SIZE        2


static inline array_list *_array_list_get_header(void *list) {
    _ASSERT(list != NULL);

    array_list *header = &((array_list *) list)[-1];
    _ASSERT(header->magic == _ARRAY_LIST_MAGIC);

    return header;
}


static inline u32 _array_list_len(void *list) {
    return (list == NULL) ? 0 : _array_list_get_header(list)->length;
}


// It was better if item_size was saved here,
// and then use this everywhere, but to support NULL case on append,
// it need to get item_size as parameter, so for consistency it will not be saved.
// Another option is to make the wrapper API support NULL by creating the list itself,
// but I rather this case be handled on the base append code and not on per wrapper code.
static inline void *_array_list_create(u32 item_count, usize item_size) {
    array_list *list = _allocate_buffer(sizeof(*list) + item_count * item_size);

    list->magic  = _ARRAY_LIST_MAGIC;
    list->limit  = item_count;
    list->length = 0;

    return list->raw_buffer;
}


static inline void *_array_list_destroy(void *list) {
    return (list == NULL) ? NULL : _deallocate(_array_list_get_header(list));
}


static inline void *_array_list_append(void *list, void *item, usize item_size) {
    if (list == NULL) {
        list = _array_list_create(_ARRAY_LIST_DEFAULT_LIMIT, item_size);
    }

    array_list *header = _array_list_get_header(list);
    if (header->length == header->limit) {
        header->limit *= _ARRAY_LIST_STEP_SIZE;

        usize size = sizeof(*header) + header->limit * item_size;
        header     = _reallocate_buffer(header, size);
        list       = header->raw_buffer;
    }

    u8 *dest = ((u8 *) list) + header->length * item_size;
    memmove(dest, item, item_size);
    header->length += 1;

    return list;
}


static inline void _array_list_pop(void *list, void *item, usize item_size) {
    array_list *header = _array_list_get_header(list);
    _ASSERT(header->length > 0);

    header->length -= 1;
    u8 *src         = ((u8 *) list) + header->length * item_size;
    memmove(item, src, item_size);
}
