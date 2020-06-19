# Output sphere
```c
sphere s = sphere_new();
```

# Output scale1
```c
sphere s    = sphere_new();
s.transform = mat4_scale(s.transform, 1.0f, 0.5f, 1.0f);
```

# Output scale2
```c
sphere s    = sphere_new();
s.transform = mat4_scale(s.transform, 0.5f, 1.0f, 1.0f);
```

# Output scale_and_rotate
```c
sphere s    = sphere_new();
s.transform = mat4_scale   (s.transform, 0.5f, 1.0f, 1.0f);
s.transform = mat4_rotate_z(s.transform, (f32) M_PI_4);
```

# Output scale_and_skew
```c
sphere s    = sphere_new();
s.transform = mat4_scale   (s.transform, 0.5f, 1.0f, 1.0f);
s.transform = mat4_shearing(s.transform, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
```
