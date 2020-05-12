#include <stdlib.h>
#include <stdio.h>

// TODO: Remove this
#include "renderer/renderer.c"

#include "answers/chapter1.c"


typedef void (*answer_func)(void);

answer_func answers[] = {
    NULL,
    &answer_chapter1,
};


int main(int argc, char **argv) {
    answer_chapter1();

    return EXIT_SUCCESS;
}
