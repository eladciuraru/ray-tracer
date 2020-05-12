

typedef struct _projectile {
    vec4 position;
    vec4 velocity;
} projectile;


typedef struct _environment {
    vec4 gravity;
    vec4 wind;
} environment;


static projectile tick(environment *env, projectile *proj) {
    vec4 pos = vec4_add(&proj->position, &proj->velocity);
    vec4 vel = vec4_add(&proj->velocity, &env->gravity);
    vel = vec4_add(&vel, &env->wind);

    return (projectile) { pos, vel };
}


static void answer_chapter1(void) {
    projectile proj = {
        .position = vec4_make_point(0.0f, 1.0f, 0.0f),
        .velocity = vec4_make_vector(1.0f, 1.0f, 0.0f),
    };
    proj.velocity = vec4_normalize(&proj.velocity);

    environment env = {
        .gravity = vec4_make_vector(0.0f, -0.1f, 0.0f),
        .wind    = vec4_make_vector(-0.01f, 0.0f, 0.0f),
    };

    for (usize i = 1; proj.position.y > 0.0f; i++) {
        vec4 pos = proj.position;
        printf("%2zu) Projectile(%.3f, %.3f, %.3f)\n", i, pos.x, pos.y, pos.z);

        proj = tick(&env, &proj);
    }
}
