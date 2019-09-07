#include <iostream>
#include <vector>
#include "mpi.h"

int main(int argc, char** argv) {

    int myrank, ncpus;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    std::vector<MPI_Request> requests(ncpus);
    std::cout << myrank << " " << ncpus << std::endl;
    MPI_Finalize();
    
    return 0;
}
