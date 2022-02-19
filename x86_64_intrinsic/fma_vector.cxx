#include <iostream>
#include <vector>
#include <immintrin.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>

/*  g++ -march=native  -std=c++17 -O3 -fopenmp fma_vector.cxx
 ref: https://www.officedaytime.com/simd512e/simdimg/si.php?f=movapd
Wall time at regular = 207 millisec
local sum = 2.17126e+08
Wall time at openmp simd = 917 millisec
local sum = 2.17126e+08
Wall time at SIMD 256 = 919 millisec
local sum = 2.17126e+08
*/

using chtime = std::chrono::steady_clock;
using chmilli = std::chrono::milliseconds;
using Vec = std::vector<double>;

double drand() {
    return static_cast<double> (rand())/ static_cast<double> (RAND_MAX);
}

void fma_256(int n, Vec x, Vec y, Vec &z) {
    double pi = 3.1415;
    int m = n / 4;
    int l = n % 4;
    __m256d coef = _mm256_setr_pd(pi,pi,pi,pi);
    for (int i = 0; i<m ;i++) {
	__m256d px = _mm256_loadu_pd(&x[i*4]);
	__m256d py = _mm256_loadu_pd(&y[i*4]);
	//__m256d px = _mm256_setr_pd(x[i*4],x[i*4+1],x[i*4+2],x[i*4+3]);
	//__m256d py = _mm256_setr_pd(y[i*4],y[i*4+1],y[i*4+2],y[i*4+3]);
	__m256d pz = _mm256_fmadd_pd(coef,px,py);
	_mm256_storeu_pd(&z[i*4],pz); // no-alignment required
    }
    for (int i=m*4; i<n;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

void openmp_simd(int n, Vec x, Vec y, Vec &z) {
    double pi = 3.1415;
    #pragma omp parallel
    #pragma omp for simd schedule(static,100000)
    for (int i = 0; i<n ;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

void regular(int n, Vec const &x, Vec const &y, Vec &z) {
    double pi = 3.1415;
    for (int i = 0; i<n ;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

int main() {
    int n = 1024*1024*100;
    Vec x(n), y(n), z(n);
    
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
    return 0;
}
