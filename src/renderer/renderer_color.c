
color3 color3_new(f32 r, f32 g, f32 b) {
    return (color3) {
        .r = r,
        .g = g,
        .b = b,
    };
}

bool color3_compare(color3 *c1, color3 *c2) {
    return f32_compare(c1->r, c2->r) &&
           f32_compare(c1->g, c2->g) &&
           f32_compare(c1->b, c2->b);
}


color3 color3_add(color3 *c1, color3 *c2) {
    return (color3) {
        c1->r + c2->r,
        c1->g + c2->g,
        c1->b + c2->b,
    };
}


color3 color3_sub(color3 *c1, color3 *c2) {
    return (color3) {
        c1->r - c2->r,
        c1->g - c2->g,
        c1->b - c2->b,
    };
}


color3 color3_scalar_mul(color3 *c, f32 scalar) {
    return (color3) {
        c->r * scalar,
        c->g * scalar,
        c->b * scalar,
    };
}


// This is also called hadamard product
color3 color3_mul(color3 *c1, color3 *c2) {
    return (color3) {
        c1->r * c2->r,
        c1->g * c2->g,
        c1->b * c2->b,
    };
}


u32 color3_as_u32(color3 *c) {
    return ((u8) (c->b * 255)) |
           ((u8) (c->g * 255)) << 8 |
           ((u8) (c->r * 255)) << 16;
}
