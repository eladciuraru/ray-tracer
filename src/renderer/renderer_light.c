
light_point light_point_new(vec4 position, color3 intensity) {
    return (light_point) {
        .position  = position,
        .intensity = intensity,
    };
}


color3 light_point_color(light_point light, material m, vec4 point,
                         vec4 view, vec4 normal, bool in_shadow) {
    _ASSERT(vec4_is_point(point));
    _ASSERT(vec4_is_vector(view));
    _ASSERT(vec4_is_vector(normal));

    // Default values
    color3 ambient  = COLOR3_BLACK;
    color3 diffuse  = COLOR3_BLACK;
    color3 specular = COLOR3_BLACK;

    // Shared data
    color3 effective_color  = color3_mul(m.color, light.intensity);
    vec4   light_vector     = vec4_normalize(vec4_sub(light.position, point));
    f64    light_dot_normal = vec4_dot_product(light_vector, normal);

    // Calculate ambient
    ambient = color3_scalar_mul(effective_color, m.ambient);

    if (!in_shadow && light_dot_normal >= 0.0) {
        // Calculate diffuse
        diffuse = color3_scalar_mul(effective_color, m.diffuse * light_dot_normal);

        // Calculate specular
        vec4 ref_vector   = vec4_reflect(vec4_negate(light_vector), normal);
        f64  ref_dot_view = vec4_dot_product(ref_vector, view);
        if (ref_dot_view > 0.0) {
            f64 factor = f64_pow(ref_dot_view, m.shininess);
            specular   = color3_scalar_mul(light.intensity, m.specular * factor);
        }
    }

    return color3_add(ambient, color3_add(diffuse, specular));
}
