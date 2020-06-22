
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


static void *_deallocate(void *addr) {
    free(addr);

    return NULL;
}


bool f32_compare(f32 num, f32 other) {
    const f32 epsilon = 0.00001f;

    return (num > other) ?
           ((num - other) < epsilon) :
           ((other - num) < epsilon);
}


static inline f32 clamp(f32 value, f32 min, f32 max) {
    return max(min(max, value), min);
}


static inline f32 clamp_01(f32 value) {
    return clamp(value, 0.0f, 1.0f);
}
