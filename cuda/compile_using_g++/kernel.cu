// kernel.cu
#include <kernel.h>
#include "helper_functions.h"
#include "helper_cuda.h"

__global__ void vec_add_kernel(float *a, float *b, float *c, int n) {
    int i = threadIdx.x + blockDim.x * blockIdx.x;
    if (i < n) c[i] = a[i] + b[i];
}

int cuda_vec_add(float *h_a, float *h_b, float *h_c, int n) {
    float *d_a, *d_b, *d_c;

    checkCudaErrors(cudaMalloc(&d_a, n*sizeof(float)));
    checkCudaErrors(cudaMalloc(&d_b, n*sizeof(float)));
    checkCudaErrors(cudaMalloc(&d_c, n*sizeof(float)));

    checkCudaErrors(cudaMemcpy(d_a, h_a, n*sizeof(float),
    				    cudaMemcpyHostToDevice));
    checkCudaErrors(cudaMemcpy(d_b, h_b, n*sizeof(float),
    				    cudaMemcpyHostToDevice));

    vec_add_kernel<< <(n-1)/256+1,256>> >(d_a, d_b, d_c, n);

    checkCudaErrors(cudaMemcpy(h_c, d_c, n*sizeof(float),
    				    cudaMemcpyDeviceToHost));

    checkCudaErrors(cudaFree(d_a));
    checkCudaErrors(cudaFree(d_b));
    checkCudaErrors(cudaFree(d_c));

    return 0;
}
