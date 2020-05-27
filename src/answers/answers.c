#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "renderer/renderer.h"

#include "answers/answers_utils.c"
#include "answers/answers_chapter1.c"
#include "answers/answers_chapter2.c"


typedef void (*answer_func)(void);

answer_func answers[] = {
    NULL,
    &answer_chapter1,
    &answer_chapter2,
};


int main(int argc, char **argv) {
    answer_chapter2();

    return EXIT_SUCCESS;
}
