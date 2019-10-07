#include "md.h"

/* First step of velocity verlet */
void MD::vverlet_1(double const& dt)
{
    for (std::size_t i=0; i<Npt; i++) {
	q.xx[i] += dt*q.vx[i] +0.5*dt*dt*q.fx[i]/q.xm[i];
	q.xy[i] += dt*q.vy[i] +0.5*dt*dt*q.fy[i]/q.xm[i];
	q.xz[i] += dt*q.vz[i] +0.5*dt*dt*q.fz[i]/q.xm[i];
	q.xx[i] -= box * dnint(q.xx[i]/box);
	q.xy[i] -= box * dnint(q.xy[i]/box);
	q.xz[i] -= box * dnint(q.xz[i]/box);
	q.vx[i] += 0.5*dt*q.fx[i]/q.xm[i];
	q.vy[i] += 0.5*dt*q.fy[i]/q.xm[i];
	q.vz[i] += 0.5*dt*q.fz[i]/q.xm[i];
    }
}

/* Second step of velocity verlet */
void MD::vverlet_2(double const& dt)
{
    for (std::size_t i=0; i<Npt; i++) {
	q.vx[i] += 0.5*dt*q.fx[i]/q.xm[i];
    }
}

