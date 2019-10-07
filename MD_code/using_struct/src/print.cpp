#include <iostream>
#include <fstream>
#include "md.h"

void MD::print_snap(int const& isnap)
{
    std::ofstream f;
    char name[256];
    sprintf(name, "snapshot%4.4d.xyz", isnap);
    f.open(name);
    f << Npt << std::endl;
    f << "#######" << std::endl;
    for (std::size_t i=0; i<Npt; i++) {
	f << "C " << q.xx[i] <<" "<<q.xy[i] << " " << q.xz[i] << std::endl;
    }
    f.close();
}

void MD::find_ngbr()
{
    double r2, dxx, dxy, dxz;
    for (std::size_t i=0; i<Npt-1; i++) {
	for (std::size_t j=i+1; j< Npt; j++) {
	    dxx = q.xx[i] - q.xx[j];
	    dxx -= box * dnint(dxx/box);
	    dxy = q.xy[i] - q.xy[j];
	    dxy -= box * dnint(dxy/box);
	    dxz = q.xz[i] - q.xz[j];
	    dxz -= box * dnint(dxz/box);
	    r2 = dxx*dxx + dxy*dxy + dxz*dxz;
	    if (r2 < rcut2) {
		ngbr.doi[i].insert(j);
	    }
	}
	
    }
}
