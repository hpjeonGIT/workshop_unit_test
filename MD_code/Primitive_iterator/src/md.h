#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
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


struct Particle {
    Particle() = default;
    Particle(std::size_t const& npt){
	xm.resize(npt);
	xx.resize(npt);
	xy.resize(npt);
	xz.resize(npt);
	vx.resize(npt);
	vy.resize(npt);
	vz.resize(npt);
	fx.resize(npt);
	fy.resize(npt);
	fz.resize(npt);
	std::cout << "resized as many as " << npt << std::endl;
    }
    std::size_t getSize() {
	return xm.size();
    }
    ~Particle() = default;
    std::vector<double> xm, xx, xy, xz, vx, vy, vz, fx, fy, fz;
};

class MD {
    using nlist_type = typename std::vector<std::unordered_set<std::size_t>>;
public:
//https://softwareengineering.stackexchange.com/questions/264728/allow-iteration-of-an-internal-vector-without-leaking-the-implementation
    using nlist_iterator = nlist_type::iterator;
    using nlist_const_iterator = nlist_type::const_iterator;
    MD() = default;
    MD(std::size_t npt): q(npt) {
	nlist.resize(npt);
	std::cout << "MD constructor allocated Particle. Resized nlist" << std::endl;
    }
    ~MD() {
	std::cout << "MD destructor deallocated Particle" << std::endl;
    }
    nlist_iterator nlist_begin() { return nlist.begin(); }
    nlist_iterator nlist_end()   { return nlist.end(); }
    nlist_const_iterator nlist_begin() const { return nlist.begin(); }
    nlist_const_iterator nlist_end()   const { return nlist.end(); }
    nlist_const_iterator nlist_cbegin() { return nlist.cbegin(); }
    nlist_const_iterator nlist_cend()   { return nlist.cend(); }
    
    std::size_t getSizeofq() {	return q.xm.size();    }
    std::size_t getSizeofnlist() { return nlist.size();  }
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
    void vverlet_1(double const& dt);
    void vverlet_2(double const& dt);
    // (double const dt) works same. Just passing by value. Passing by constant reference might be faster
    void force();
    void print_snap(int const& isnap);
    void find_nlist();
private:    
    Particle q;
    nlist_type nlist;
};


  
