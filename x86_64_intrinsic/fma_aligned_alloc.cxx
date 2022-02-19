#include <iostream>
#include <vector>
#include <immintrin.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>

/* g++ -march=native  -std=c++17 -O3 -fopenmp fma_aligned_alloc.cxx -o fma_a
./fma_a
Wall time at regular = 196 millisec
local sum = 2.17126e+08
Wall time at openmp simd = 201 millisec
local sum = 2.17126e+08
Wall time at SIMD 256 = 200 millisec
local sum = 2.17126e+08
*/


using chtime = std::chrono::steady_clock;
using chmilli = std::chrono::milliseconds;

double drand() {
    return static_cast<double> (rand())/ static_cast<double> (RAND_MAX);
}

void fma_256(int n, double *x, double *y, double *z) {
    double pi = 3.1415;
    int m = n / 4;
    int l = n % 4;
    __m256d coef = _mm256_setr_pd(pi,pi,pi,pi);
    for (int i = 0; i<m ;i++) {
	__m256d px = _mm256_load_pd(&x[i*4]);
	__m256d py = _mm256_load_pd(&y[i*4]);
	__m256d pz = _mm256_fmadd_pd(coef,px,py);
	_mm256_store_pd(&z[i*4],pz);
    }
    for (int i=m*4; i<n;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

void openmp_simd(int n, double *x, double *y, double *z) {
    double pi = 3.1415;
    #pragma omp parallel
    #pragma omp for simd schedule(static,100000)
    for (int i = 0; i<n ;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

void regular(int n, double *x, double *y, double *z) {
    double pi = 3.1415;
    for (int i = 0; i<n ;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

int main() {
    int n = 1024*1024*100;
    double *x = static_cast<double*>(aligned_alloc(n,n*sizeof *x));
    double *y = static_cast<double*>(aligned_alloc(n,n*sizeof *y));
    double *z = static_cast<double*>(aligned_alloc(n,n*sizeof *z));
    
    for (int i = 0; i<n ;i++){
	x[i] = drand();
	y[i] = drand();
	z[i] = 0.0;
    }
    chtime::time_point t0 = chtime::now();
    regular(n,x,y,z);
    chtime::time_point t1 = chtime::now();
    std::cout << "Wall time at regular = "
	      << std::chrono::duration_cast<chmilli>(t1-t0).count()
	      << " millisec" << std::endl;
    double l_sum = 0.0;
    for (int i = 0; i<n ;i++) l_sum += z[i];
    std::cout << "local sum = "<< l_sum << std::endl;
    //########### openmp
    t0 = chtime::now();
    openmp_simd(n,x,y,z);
    t1 = chtime::now();
    std::cout << "Wall time at openmp simd = "
	      << std::chrono::duration_cast<chmilli>(t1-t0).count()
	      << " millisec" << std::endl;
    l_sum = 0.0;
    for (int i = 0; i<n ;i++) l_sum += z[i];
    std::cout << "local sum = "<< l_sum << std::endl;
   //########### SIMD 256
    t0 = chtime::now();
    fma_256(n,x,y,z);
    t1 = chtime::now();
    std::cout << "Wall time at SIMD 256 = "
	      << std::chrono::duration_cast<chmilli>(t1-t0).count()
	      << " millisec" << std::endl;
    l_sum = 0.0;
    for (int i = 0; i<n ;i++) l_sum += z[i];
    std::cout << "local sum = "<< l_sum << std::endl;
    free(x);
    free(y);
    free(z);
    return 0;
}
