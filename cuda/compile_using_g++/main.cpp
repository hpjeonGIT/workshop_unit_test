// ref: https://stackoverflow.com/questions/35886052/cuda-c-linking-error-undefined-reference-to
// main.cpp
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <kernel.h>

using namespace std;

int main() {
    const int n = 5;
    float h_A[n] = { 0., 1., 2., 3., 4. };
    float h_B[n] = { 5., 4., 3., 2., 1. };
    float h_C[n];

    cuda_vec_add(h_A, h_B, h_C, n);

    printf("{ 0.0, 1.0, 2.0, 3.0, 4.0 } + { 5.0, 4.0, 3.0, 2.0, 1.0 } = { %0.01f, %0.01f, %0.01f, %0.01f, %0.01f }\n",
        h_C[0], h_C[1], h_C[2], h_C[3], h_C[4]);

    cin.get();

    return 0;
}
