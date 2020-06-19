# Output 1
```c
vec4 velocity = vec4_normalize(vec4_make_vector(1.0f, 1.8f, 0.0f));
velocity      = vec4_scalar_mul(velocity, 11.25f);

projectile proj = {
    .position = vec4_make_point(0.0f, 1.0f, 0.0f),
    .velocity = velocity,
};
environment env = {
    .gravity = vec4_make_vector( 0.0f, -0.1f, 0.0f),
    .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
};

canvas *can = canvas_create(900, 550);
```

# Output 2
```c
vec4 velocity = vec4_normalize(vec4_make_vector(2.5f, 2.5f, 0.0f));
velocity      = vec4_scalar_mul(velocity, 10.0f);

projectile proj = {
    .position = vec4_make_point(0.0f, 1.0f, 0.0f),
    .velocity = velocity,
};
environment env = {
    .gravity = vec4_make_vector( 0.0f, -0.1f, 0.0f),
    .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
};

canvas *can = canvas_create(900, 550);
color3  col = { 0.75f, 0.25f, 0.25f };
```

# Output 3
```c
vec4 velocity = vec4_normalize(vec4_make_vector(9.0f, 0.5f, 0.0f));
velocity      = vec4_scalar_mul(velocity, 10.0f);

projectile proj = {
    .position = vec4_make_point(0.0f, 250.0f, 0.0f),
    .velocity = velocity,
};
environment env = {
    .gravity = vec4_make_vector( 0.0f, -0.1f, 0.0f),
    .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
};

canvas *can = canvas_create(1000, 550);
color3  col = { 0.75f, 0.25f, 0.25f };
```

# Output 4
```c
vec4 velocity = vec4_normalize(vec4_make_vector(1.0f, 5.0f, 0.0f));
velocity      = vec4_scalar_mul(velocity, 10.0f);

projectile proj = {
    .position = vec4_make_point(0.0f, 250.0f, 0.0f),
    .velocity = velocity,
};
environment env = {
    .gravity = vec4_make_vector( 0.0f, -0.1f, 0.0f),
    .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
};

canvas *can = canvas_create(250, 800);
color3  col = { 0.75f, 0.25f, 0.25f };
```
