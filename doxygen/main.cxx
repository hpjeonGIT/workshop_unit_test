#include <iostream>
#include <vector>
#include <immintrin.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>

using chtime = std::chrono::steady_clock;
using chmilli = std::chrono::milliseconds;
using Vec = std::vector<double>;

double drand() {
    return static_cast<double> (rand())/ static_cast<double> (RAND_MAX);
}

void fma_256(int n, Vec const &x, Vec const &y, Vec &z);
void openmp_simd(int n, Vec const &x, Vec const& y, Vec &z);
void regular(int n, Vec const &x, Vec const &y, Vec &z);

/**
 * For x/y vectors, daxpy operation is done and vector z is made
 * We compare the performance by avx2, openmp optimization, and compiler-only
 * optimization for double-vector data
 */
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
