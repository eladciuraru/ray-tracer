
intersect intersect_new(sphere *s, f32 value) {
    return (intersect) {
        .s     = s,
        .value = value,
    };
}


intersect_ex intersect_ex_compute(intersect i, ray r) {
    intersect_ex i_ex;

    i_ex.s      = i.s;
    i_ex.value  = i.value;
    i_ex.point  = ray_position(&r, i.value);
    i_ex.view   = vec4_negate(r.direction);
    i_ex.normal = sphere_normal_at(i.s, i_ex.point);

    if (vec4_dot_product(i_ex.normal, i_ex.view) < 0.0f) {
        i_ex.inside = true;
        i_ex.normal = vec4_negate(i_ex.normal);
    }

    i_ex.over_point = vec4_add(i_ex.point,
                               vec4_scalar_mul(i_ex.normal, 0.001f));//_F32_EPSILON));

    return i_ex;
}


bool intersect_ex_compare(intersect_ex i1, intersect_ex i2) {
    return i1.s      == i2.s                  &&
           i1.inside == i2.inside             &&
           f32_compare (i1.value,  i2.value)  &&
           vec4_compare(i1.point,  i2.point)  &&
           vec4_compare(i1.view,   i2.view)   &&
           vec4_compare(i1.normal, i2.normal) &&
           vec4_compare(i1.over_point, i2.over_point);
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


intersect *intersect_list_extend(intersect *list, intersect *other) {
    return _array_list_extend(list, other, sizeof(*list));
}


static i32 _intersect_list_compare(const void *p1, const void *p2) {
    intersect *i1 = (intersect *)p1;
    intersect *i2 = (intersect *)p2;

    return (i1->value > i2->value) - (i1->value < i2->value);
}


// This is implemented on this level and not on the base,
// because currently it seems like only this list uses this funcitonallity,
// so no need to complicate this code to support more generic approach.
void intersect_list_sort(intersect *list) {
    // TODO: Change this after removing the crt dependency
    // Maybe using timsort sort implmentation from here: https://github.com/swenson/sort
    qsort(list, intersect_list_len(list),
          sizeof(*list), _intersect_list_compare);
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
