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
