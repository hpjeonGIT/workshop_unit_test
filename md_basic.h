#ifndef md_h
#define md_h

#include <iostream>
template <typename T>
class Particle {
public:    
    T xx[3], xm;
    Particle() {
	xm = 1.0;
	xx[0] = 1.;
	xx[1] = 2.;
	xx[2] = 3.;
	
    }
    ~Particle() {
    }
};
#endif
