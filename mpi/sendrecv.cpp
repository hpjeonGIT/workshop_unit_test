#include <iostream>
#include <vector>
#include "mpi.h"

int main(int argc, char** argv) {

    int myrank, ncpus;
    int target, source;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    std::vector<MPI_Request> requests(ncpus);
    MPI_Status status;

    std::vector<float> xx={1.1f, 2.2f, 3.3f}, yy;
    yy.resize(3);
    if (myrank == 0) {
	for (auto i = xx.begin(); i < xx.end(); i++){
	    *i += 0.5f;
	}
    }
    target = (myrank + 1)%ncpus;
    source = (myrank -1 + ncpus)%ncpus;
    MPI_Sendrecv(xx.data(), 3, MPI_FLOAT, target, 0,
		 yy.data(), 3, MPI_FLOAT, source, 0,
		 MPI_COMM_WORLD, &status);
	
    std::cout << myrank << " " << yy[0] << std::endl;
    MPI_Finalize();
    
    return 0;
}
