#include <cmath>
#include "md.h"

void MD::force()
{
  double r2, dxx, dxy, dxz, coef;

  // force initialization 
  for(std::size_t i=0; i<Npt; i++) {
      q.fx[i] = 0.0;
      q.fy[i] = 0.0;
      q.fz[i] = 0.0;
  }

  // neighbor list for many-body interaction
  for (std::size_t i=0; i<Npt; i++) {
      for (auto m : nlist[i]) {
	  dxx = q.xx[i] - q.xx[m];
	  dxx -= box * dnint(dxx/box);
	  dxy = q.xy[i] - q.xy[m];
	  dxy -= box * dnint(dxy/box);
	  dxz = q.xz[i] - q.xz[m];
	  dxz -= box * dnint(dxz/box);
	  r2 = dxx*dxx + dxy*dxy + dxz*dxz;
	  coef = 1./(r2*sqrt(r2));
	  q.fx[i] += coef * dxx;
	  q.fy[i] += coef * dxy;
	  q.fz[i] += coef * dxz;
	  q.fx[m] -= coef * dxx;
	  q.fy[m] -= coef * dxy;
	  q.fz[m] -= coef * dxz;
      }
  }
}

