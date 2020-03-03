#include <iostream>
#include <string>
#include <fstream>
int main (int argc, char ** argv) {
  std::string cin, config_str;
  
  std::ifstream ifile ("amgx_config.txt");
  if (ifile) {
    std::cout << "amgx file found\n";
    while (ifile >> cin) { config_str.append(cin); }
  } else { 
    std::cout << "amgx file NOT found\n";
    config_str = "config_version=2, solver=AMG,max_iters=2,"
            "norm=L2, convergence=RELATIVE_INI_CORE, monitor_residual=1,"
            "tolerance=1e-4, preconditioner(amg_solver)=NOSOLVER,"
            "amg_solver:algorithm=CLASSICAL, amg_solver:max_iters=2,"
            "amg_solver:presweeps=1, amg_solver:postsweeps=1, amg_solver:cycle=V,"
            "print_solve_stats=1, print_grid_stats=1, obtain_timings=1,"
            "exception_handling=1";
  }
  std::cout << config_str << std::endl;
  ifile.close();

  return 0;
}
