
// TODO: Remove these
#include <assert.h>
#include <stdlib.h>

#ifndef _RELEASE
    #define _ASSERT(condition) assert(condition)
#else
    #define _ASSERT(condition)
#endif


// This function exists to be able to easily swap calling malloc for memory allocation
static void *_allocate_buffer_no_zero(usize size) {
    void *addr = malloc(size);

    // In later implementation of allcoate, we don't want to ever fail,
    // in case of failure we will just compile with bigger pre allocated memory
    _ASSERT(addr != NULL);

    return addr;
}


static void *_allocate_buffer(usize size) {
    void *addr = calloc(size, sizeof(u8));

    // In later implementation of allcoate, we don't want to ever fail,
    // in case of failure we will just compile with bigger pre allocated memory
    _ASSERT(addr != NULL);

    return addr;
}


static void *_reallocate_buffer(void *buffer, usize size) {
    void *addr = realloc(buffer, size);

    // In later implementation of allcoate, we don't want to ever fail,
    // in case of failure we will just compile with bigger pre allocated memory
    _ASSERT(addr != NULL);

    // TODO: Think what to do about the difference between
    //       zeroed/non zeroed allocation

    return addr;
}


static void *_deallocate(void *addr) {
    free(addr);

    return NULL;
}
