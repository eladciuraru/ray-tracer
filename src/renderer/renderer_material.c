
material material_new(color3 color, f64 ambient, f64 diffuse,
                      f64 specular, f64 shininess) {
    return (material) {
        .color     = color,
        .ambient   = f64_clamp_01(ambient),
        .diffuse   = f64_clamp_01(diffuse),
        .specular  = f64_clamp_01(specular),
        .shininess = f64_clamp(shininess, 10.0, 200.0),
    };
}


material material_default(void) {
    return material_new(COLOR3_WHITE, 0.1, 0.9, 0.9, 200.0);
}
