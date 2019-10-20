// kernel.cu
#include <kernel.h>

__global__ void vec_add_kernel(float *a, float *b, float *c, int n) {
    int i = threadIdx.x + blockDim.x * blockIdx.x;
    if (i < n) c[i] = a[i] + b[i];
}

int cuda_vec_add(float *h_a, float *h_b, float *h_c, int n) {
    float *d_a, *d_b, *d_c;

    cudaMalloc(&d_a, n*sizeof(float));
    cudaMalloc(&d_b, n*sizeof(float));
    cudaMalloc(&d_c, n*sizeof(float));

    cudaMemcpy(d_a, h_a, n*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, n*sizeof(float), cudaMemcpyHostToDevice);

    vec_add_kernel<< <(n-1)/256+1,256>> >(d_a, d_b, d_c, n);

    cudaMemcpy(h_c, d_c, n*sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

    return 0;
}
