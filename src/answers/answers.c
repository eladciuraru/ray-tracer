#include <stdlib.h>
#include <stdio.h>

#include "answers/chapter1.c"


typedef void (*answer_func)(void);

answer_func answers[] = {
    NULL,
    &answer_chapter1,
};


int main(int argc, char **argv) {
    return EXIT_SUCCESS;
}
