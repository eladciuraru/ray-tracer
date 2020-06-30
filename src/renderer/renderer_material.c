
material material_new(color3 color, f32 ambient, f32 diffuse,
                      f32 specular, f32 shininess) {
    return (material) {
        .color     = color,
        .ambient   = f32_clamp_01(ambient),
        .diffuse   = f32_clamp_01(diffuse),
        .specular  = f32_clamp_01(specular),
        .shininess = f32_clamp(shininess, 10.0f, 200.0f),
    };
}


material material_default(void) {
    return material_new(COLOR3_WHITE, 0.1f, 0.9f, 0.9f, 200.0f);
}
