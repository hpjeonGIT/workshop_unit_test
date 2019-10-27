#include <chrono>
#include <thread>
#include <iostream>

//Ref: https://stackoverflow.com/questions/879408/c-function-wrapper-that-behaves-just-like-the-function-itself
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
    
void mysleep(uint x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(x));    
}


int main(int argc, char **argv)
{
    float elapsed;
    TIMER_CPU(mysleep(1234), elapsed, 2);
    std::cout << elapsed/1000. << std::endl;
    return 0;
}
