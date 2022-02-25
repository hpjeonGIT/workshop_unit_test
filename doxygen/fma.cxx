#include <iostream>
#include <vector>
#include <immintrin.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>

/**
 * Alias for STL vector with double
 *
 */

using Vec = std::vector<double>;

/**
 * @brief fmadd using avx2
 * @details for vector double data, daxpy is done through _mm256_fmadd_pd()
 * @param[in] n size of vectors
 * @param[in] x First input
 * @param[in] y Second input
 * @param[out] z Results
 */
void fma_256(int n, Vec const &x, Vec const &y, Vec &z) {
    double pi = 3.1415;
    int m = n / 4;
    int l = n % 4;
    __m256d coef = _mm256_setr_pd(pi,pi,pi,pi);
    for (int i = 0; i<m ;i++) {
	__m256d px = _mm256_loadu_pd(&x[i*4]);
	__m256d py = _mm256_loadu_pd(&y[i*4]);
	__m256d pz = _mm256_fmadd_pd(coef,px,py);
	_mm256_storeu_pd(&z[i*4],pz); // no-alignment required
    }
    for (int i=m*4; i<n;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

/**
 * @brief fmadd using simd instruction using OpenMP
 * @details for vector double data, daxpy is done through OpenMP
 * @param[in] n size of vectors
 * @param[in] x First input
 * @param[in] y Second input
 * @param[out] z Results
 */
void openmp_simd(int n, Vec const &x, Vec const& y, Vec &z) {
    double pi = 3.1415;
    #pragma omp parallel
    #pragma omp for simd schedule(static,100000)
    for (int i = 0; i<n ;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

/**
 * @brief fmadd using avx2
 * @details let the compiler do all optimization
 * @param[in] n size of vectors
 * @param[in] x First input
 * @param[in] y Second input
 * @param[out] z Results
 */
void regular(int n, Vec const &x, Vec const &y, Vec &z) {
    double pi = 3.1415;
    for (int i = 0; i<n ;i++) {
	z[i] = pi*x[i] + y[i];
    }
}

