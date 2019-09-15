#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

class table_soa {
public:
    std::vector<uint> ind;
    std::vector<double> x;
    std::vector<float> y;
    std::vector<bool> tag;
    table_soa() {
    }
    table_soa(std::size_t const& nsize) {
	ind.resize(nsize);
	x.resize(nsize);
	y.resize(nsize);
	tag.resize(nsize);
    }
    ~table_soa() {
    }
      
public:
    
};

class table_aos {
public:
    uint ind;
    double x;
    float y;
    bool tag;
    table_aos() {
    }
    ~table_aos() {
    }
    void init(std::size_t const& i) {
	ind = i;
	x =  static_cast<double> (rand()) / static_cast<double> (RAND_MAX);
	y =  static_cast<float > (rand()) / static_cast<float > (RAND_MAX);
    }
    uint search(double const& x) {
	if (x > x || y > static_cast<float> (x)) {
	    tag = true;
	    return ind;
	}
	else {
	    tag = false;
	    return 0;
	}
    }
      
};

int main(int argc, char** argv)
{
    std::size_t nsize=100000;
    table_soa ob1(nsize);
    // preset
    srand (time(nullptr));
    std::clock_t t0 = clock();
    for (uint i=0;i<nsize;i++) {
	ob1.ind[i]= i;
	ob1.x[i] = static_cast<double> (rand()) /
	           static_cast<double> (RAND_MAX);
	ob1.y[i] = static_cast<float> (rand()) /
	           static_cast<float> (RAND_MAX);
    }

    std::clock_t t1 = clock();
    std::cout << "wall time for SoA setup = "
	      << static_cast<float> (t1-t0) / CLOCKS_PER_SEC
	      << std:: endl; // 0.0012sec
    // search in soa using for loop
    long int nsum = 0;
    std::vector<int> ans1;
    t0 = clock();
    for (std::size_t i=0;i < nsize; i++) {
	if (ob1.x[i] > 0.5 || ob1.y[i] > 0.5) {
	    nsum += i;
	    ans1.push_back(i); 
	    ob1.tag[i] = true;
	}
	else{
	    ob1.tag[i] = false;
	}
    }
    t1 = clock();
    std::cout << "wall time for SoA search = "
	      << static_cast<float> (t1-t0)/CLOCKS_PER_SEC
	      << std:: endl;
    std::cout << "nsum = " << nsum << std::endl;

    // case of AoS
    srand (time(nullptr));
    std::vector<table_aos> ob2;
    ob2.resize(nsize);
    t0 = clock();
    for(std::size_t i; i< nsize; i++) {
	ob2[i].init(i);
    }
    t1 = clock();
    std::cout << "wall time for AoS setup = "
	      << static_cast<float> (t1-t0)/CLOCKS_PER_SEC
	      << std:: endl;

    // AoS search
    std::vector<int> ans2;
    int k;
    nsum = 0;
    t0 = clock();
    for(std::size_t i; i< nsize; i++) {
	k = ob2[i].search(0.5);
	ans2.push_back(k);
	nsum += k;
    }
    t1 = clock();
    std::cout << "wall time for AoS search = "
	      << static_cast<float> (t1-t0)/CLOCKS_PER_SEC
	      << " nsum = " << nsum << std:: endl; //0.000638sec
    // another AoS
    nsum = 0;
    t0 = clock();
    for(auto& i : ob2) {
	k = i.search(0.5);
	ans2.push_back(k);
	nsum += k;
    }
    t1 = clock();
    std::cout << "wall time for AoS search = "
	      << static_cast<float> (t1-t0)/CLOCKS_PER_SEC
	      << " nsum = " << nsum << std:: endl; 
   return 0;
}
