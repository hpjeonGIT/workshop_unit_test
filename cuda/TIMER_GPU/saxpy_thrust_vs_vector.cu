#include <iostream>
#include <iterator>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cuda_runtime_api.h>
// Ref: http://www.training.prace-ri.eu/uploads/tx_pracetmo/CUDAGC.pdf
class Timer_CUDA {
private:
    cudaEvent_t start, stop;
public:
    Timer_CUDA() {
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
    }
    float elapsed() {
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	float milliseconds = 0.0f;
	cudaEventElapsedTime(&milliseconds, start, stop);
	return milliseconds;
    }
    ~Timer_CUDA() = default;
};
#define TIMER_GPU(f, etime, n) {Timer_CUDA t;for (uint i=0;i<n;i++) f; etime = t.elapsed(); }

// 
class Timer {
private:    
    std::chrono::time_point<std::chrono::steady_clock> start, end;
public:    
    Timer() {
	start = std::chrono::steady_clock::now();
    }
    float elapsed() {
	end = std::chrono::steady_clock::now();
	return static_cast<float>  (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    }
    ~ Timer() = default;
};
    
#define TIMER_CPU(fn, etime, n) { Timer t; for (uint i=0;i<n; i++) fn; etime= t.elapsed() ;}
    

void saxpy1(float A, thrust::device_vector<float>& X,
	   thrust::device_vector<float>& Y) {
    thrust::device_vector<float> temp(X.size());
    thrust::fill(temp.begin(), temp.end(), A);
    thrust::transform(X.begin(), X.end(), temp.begin(), temp.begin(),
		      thrust::multiplies<float>());
    thrust::transform(temp.begin(), temp.end(), Y.begin(), Y.begin(),
		      thrust::plus<float>());
}

struct saxpy_functor
{
    const float a;
    saxpy_functor(float _a) : a(_a) {}
    __host__ __device__ float operator() (const float& x, const float& y) const {
	return a*x + y;
    }
};

void saxpy2(float A, thrust::device_vector<float>& X,
	    thrust::device_vector<float>& Y) {
    thrust::transform(X.begin(), X.end(), Y.begin(), Y.begin(),
		      saxpy_functor(A));
}

void saxpy_cpu(float A, std::vector<float>& X, std::vector<float>& Y) {
    for (uint i=0; i<X.size(); i++) {
	Y[i] = A*X[i] + Y[i];
    }
    
}
int main(void)
{
    const int N=1000000;
    thrust::host_vector<float> tmp(N);
    thrust::generate(tmp.begin(), tmp.end(), rand);
    thrust::device_vector<float> X=tmp, Y=tmp;
    float etime1, etime2;

    // Warming up GPU card
    TIMER_GPU(saxpy1(10.f, X, Y), etime1, 100);
    // Actual tests
    TIMER_GPU(saxpy1(10.f, X, Y), etime1, 100);
    std::cout << etime1 << std::endl;
    TIMER_GPU(saxpy2(10.f, X, Y), etime2, 100);
    std::cout << etime2 << std::endl;

    //CPU
    std::vector<float> Xc(N);
    std::generate(Xc.begin(), Xc.end(), rand);
    std::vector<float> Yc = Xc;
    TIMER_CPU(saxpy_cpu(10.f, Xc, Yc), etime1, 100);
    std::cout << etime1 <<std::endl;
    
    return 0;
}
    
