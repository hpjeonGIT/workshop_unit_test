#include <vector>

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
	size_ = npt;
	std::cout << "resized as many as " << npt << std::endl;
    }
    std::size_t getSize() {
	return size_;
    }
    ~Particle() = default;
    std::vector<double> xm, xx, xy, xz, vx, vy, vz, fx, fy, fz;
    std::size_t size_;
};
