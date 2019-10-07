#include <cmath>
#include <algorithm>
#include "md.h"

int main(int argc, char** argv)
{
  unsigned i = 0;
  double dt = 0.1;
  MD sim(Npt);

  sim.data_read();
  sim.find_ngbr();
  
  do{
      sim.vverlet_1(dt);
      sim.force();
      sim.vverlet_2(dt);
      i++;
      if (i%100 == 0) sim.print_snap(i);
  } while (i < 1000);
  return 0;
}

