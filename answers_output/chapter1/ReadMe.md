# Output 1
```c
projectile proj = {
    .position = vec4_make_point(0.0f, 1.0f, 0.0f),
    .velocity = vec4_normalize(vec4_make_vector(1.0f, 1.0f, 0.0f)),
};

environment env = {
    .gravity = vec4_make_vector(0.0f, -0.1f, 0.0f),
    .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
};
```

# Output 2
```c
projectile proj = {
    .position = vec4_make_point(0.0f, 1.0f, 0.0f),
    .velocity = vec4_normalize(vec4_make_vector(1.0f, 1.0f, 0.0f)),
};
proj.velocity = vec4_scalar_mul(proj.velocity, 1.5f);

environment env = {
    .gravity = vec4_make_vector(0.0f, -0.1f, 0.0f),
    .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
};
```

# Output 3
```c
projectile proj = {
    .position = vec4_make_point(0.0f, 1.0f, 0.0f),
    .velocity = vec4_normalize(vec4_make_vector(1.0f, 1.0f, 0.0f)),
};
proj.velocity = vec4_scalar_mul(proj.velocity, 21.25f);

environment env = {
    .gravity = vec4_make_vector(0.0f, -0.5f, 0.0f),
    .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
};
```
