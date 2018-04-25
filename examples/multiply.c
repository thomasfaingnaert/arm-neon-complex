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
    float z[2 * ARRAY_SIZE];

    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; ++i)
    {
        x[i] = 10.0f * (float)rand() / RAND_MAX;
        y[i] = 10.0f * (float)rand() / RAND_MAX;
    }

    arm_neon_complex_multiply(z, x, y, ARRAY_SIZE);

    printf("x: ");
    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; i += 2)
        printf("%f + i%f ", x[i], x[i+1]);
    printf("\n");

    printf("y: ");
    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; i += 2)
        printf("%f + i%f ", y[i], y[i+1]);
    printf("\n");

    printf("x*y: ");
    for (unsigned int i = 0; i < 2 * ARRAY_SIZE; i += 2)
        printf("%f + i%f ", z[i], z[i+1]);
    printf("\n");

    return 0;
}
