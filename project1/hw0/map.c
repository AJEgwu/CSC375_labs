#include <stdio.h>
#include <stdlib.h>

/* A statically allocated variable */
int foo;

extern int recur(int i);

/* A statically allocated, pre-initialized variable */
volatile int stuff = 7;

int main(int argc, char *argv[]) {
    /* A stack allocated variable */
    volatile int i = 0;

    /* Dynamically allocate some stuff */
    volatile char *buf1 = malloc(100);
    /* ... and some more stuff */
    volatile char *buf2 = malloc(100);

    printf("Address of main: %p\n", main);
    printf("Address of stack variable i: %p\n", &i);
    printf("Address of static foo: %p\n", &foo);
    printf("Address of static stuff: %p\n", &stuff);
    printf("Heap buf1: %p\n", buf1);
    printf("Heap buf2: %p\n", buf2);

    recur(3);
    return 0;
}
