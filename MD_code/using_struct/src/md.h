#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include "particle.h"
#include "neighbor_list.h"
const std::size_t  Npt = 100;
const double rcut = 9.0;
const double rcut2= rcut*rcut;
const double box  = 20.0;
const double mass = 10.0;

inline double drand()
{
    double x = static_cast<double> (rand())/ static_cast<double> (RAND_MAX);
  return x;
}

template <typename T>
inline T dnint(T x)
{
    T y = (x > 0.0) ? floor(x+0.5): ceil(x-0.5);
    return y;
}


class MD {
public:
    MD() = default;
    MD(std::size_t npt): q(npt), ngbr(npt) {
	std::cout << "MD constructor allocated Particle. Resized nlist" << std::endl;
    }
    ~MD() {
	std::cout << "MD destructor deallocated Particle" << std::endl;
    }
    void data_read() {
	for (std::size_t i=0; i< Npt; i++) {
	    //std::cout << q.xx[i] << std::endl;
	    q.xx[i] = (drand() - 0.5)*box;
	    q.xy[i] = (drand() - 0.5)*box;
	    q.xz[i] = (drand() - 0.5)*box;
	    q.vx[i] = 0.0;
	    q.vy[i] = 0.0;
	    q.vz[i] = 0.0;
	    q.fx[i] = 0.0;
	    q.fy[i] = 0.0;
	    q.fz[i] = 0.0;
	    q.xm[i] = mass;
	}
    }
    void find_ngbr();
    void vverlet_1(double const& dt);
    void vverlet_2(double const& dt);
    std::size_t getSize_q() {
	return q.getSize();
    }
    std::size_t getSize_ngbr() {
	return ngbr.getSize();
    }
    
    // (double const dt) works same. Just passing by value. Passing by constant reference might be faster
    void force();
    void print_snap(int const& isnap);
private:    
    Particle q;
    Nlist ngbr;
};


  
