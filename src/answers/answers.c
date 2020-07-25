#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "renderer/renderer.h"

#include "answers/answers_utils.c"
#include "answers/answers_chapter1.c"
#include "answers/answers_chapter2.c"
#include "answers/answers_chapter3.c"
#include "answers/answers_chapter4.c"
#include "answers/answers_chapter5.c"
#include "answers/answers_chapter6.c"
#include "answers/answers_chapter7.c"
#include "answers/answers_chapter8.c"


typedef void (*answer_func)(void);

answer_func answers[] = {
    NULL,
    &answer_chapter1,
    &answer_chapter2,
    &answer_chapter3,
    &answer_chapter4,
    &answer_chapter5,
    &answer_chapter6,
    &answer_chapter7,
    &answer_chapter8,
};


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s chapter\n", argv[0]);
        return EXIT_FAILURE;
    }

    i32 chapter = atoi(argv[1]);
    if (chapter < 1 || chapter >= _countof(answers)) {
        printf("%d is invalid chapter number\n", chapter);
        return EXIT_FAILURE;
    }

    answers[chapter]();

    return EXIT_SUCCESS;
}
