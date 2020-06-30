
intersect intersect_new(sphere *s, f32 value) {
    return (intersect) {
        .s     = s,
        .value = value,
    };
}


bool intersect_compare(intersect i1, intersect i2) {
    return i1.s == i2.s && f32_compare(i1.value, i2.value);
}


u32 intersect_list_len(intersect *list) {
    return _array_list_len(list);
}


intersect *intersect_list_create(u32 limit) {
    return _array_list_create(limit, sizeof(intersect));
}


void *intersect_list_destroy(intersect *list) {
    return _array_list_destroy(list);
}


intersect *intersect_list_append(intersect *list, intersect i) {
    return _array_list_append(list, &i, sizeof(i));
}


intersect intersect_list_pop(intersect *list) {
    intersect i;

    _array_list_pop(list, &i, sizeof(i));

    return i;
}


// This is implemented on this level and not on the base,
// because currently it seems like only this list uses this funcitonallity,
// so no need to complicate this code to support more generic approach.
void intersect_list_sort(intersect *list) {
    _ASSERT(false);
}


intersect *intersect_list_hit(intersect *list) {
    f32        min   = FLT_MAX;
    intersect *inter = INTERSECT_NO_HIT;
    for (u32 i = 0; i < intersect_list_len(list); i++) {
        f32 value = list[i].value;

        if (value >= 0.0f && value < min) {
            inter = &list[i];
            min   = value;
        }
    }

    return inter;
}
