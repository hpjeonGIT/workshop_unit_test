#ifndef md_h
#define md_h

#include <iostream>
#include <vector>
template <typename T>
class Particle {
public:
    std::vector<T> xx, xy, xz;
    T xm;
    Particle() {
    }
Particle(std::size_t Npt): xm(1.0), xx(Npt,1), xy(Npt,0), xz(Npt,0) {
    }
    ~Particle() {
    }
};

template <typename T>
class ptclass {
public:
    T xx, xy, xz, xm;
    ptclass() {
	xx = 0.0;
	xy = 1.0;
	xz = 2.0;
	xm = 11.1;
    }
    ~ptclass() {
    }
};

template <typename T>
struct ptstr {
    T xx = 1.1;
    T xy = 2.2;
    T xz = 3.3;
    T xm = 11.1;
};

/*
template <typename T>
class Particle {
public:
    std::vector<T> xx, xy, xz;
    T xm;
    Particle() {
    }
    Particle(std::size_t Npt) {
	xm = 1.0; xx.resize(Npt,1); xy.resize(Npt,0); xz.resize(Npt,0);
    }
    ~Particle() {
    }
};
*/
#endif
