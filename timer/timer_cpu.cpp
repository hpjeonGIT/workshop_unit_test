// g++ -std=c++11 timer_cpu.cpp
#include <chrono>
#include <thread>
#include <iostream>

void mysleep(uint x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(x));    
}


void TIMER_CPU(std::function< void(uint) > f, uint x, double& etime){
    auto start = std::chrono::steady_clock::now();
    f(x);
    auto end   = std::chrono::steady_clock::now();
    etime = static_cast<double> (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.);
}

int main(int argc, char **argv)
{
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(1234));
    auto end   = std::chrono::steady_clock::now();
    auto etime= end - start;
    std::cout << 
	std::chrono::duration_cast<std::chrono::milliseconds>(etime).count()
	<< std::endl;
    double elapsed;
    TIMER_CPU(mysleep, 1234, elapsed);
    std::cout << elapsed << std::endl;
    return 0;
}
