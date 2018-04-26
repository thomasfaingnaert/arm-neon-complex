#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arm_neon_complex.h"

// Should be divisible by 8
#define ARRAY_SIZE 16

int main()
{
    srand(time(NULL));

    float x[2 * ARRAY_SIZE];
    float y[2 * ARRAY_SIZE];
    float acc[2 * ARRAY_SIZE];
    float res[2 * ARRAY_SIZE];

    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; ++i)
    {
        x[i] = 10.0f * (float)rand() / RAND_MAX;
        y[i] = 10.0f * (float)rand() / RAND_MAX;
        acc[i] = 10.0f * (float)rand() / RAND_MAX;
    }

    arm_neon_complex_multiply_accumulate(res, acc, x, y, ARRAY_SIZE);

    printf("acc: ");
    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; i += 2)
        printf("%f + i%f ", acc[i], acc[i+1]);
    printf("\n");

    printf("x: ");
    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; i += 2)
        printf("%f + i%f ", x[i], x[i+1]);
    printf("\n");

    printf("y: ");
    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; i += 2)
        printf("%f + i%f ", y[i], y[i+1]);
    printf("\n");

    printf("acc+x*y: ");
    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; i += 2)
        printf("%f + i%f ", res[i], res[i+1]);
    printf("\n");

    return 0;
}
