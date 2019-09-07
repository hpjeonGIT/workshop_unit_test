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
    if (ncpus != 4) {
	std::cout << "ncpus is no 4. Exits here \n";
	MPI_Finalize();
	return 1;
    }
    if (myrank == 0){
	float x=1.23f;
	MPI_Request request0;
	MPI_Status status0;
	MPI_Isend (&x,1,MPI_FLOAT, 3, 0, MPI_COMM_WORLD, &request0);
	MPI_Wait(&request0, &status0);
	std::cout << "rank 0 x= " << x << std::endl;
    }
    if (myrank == 1){
	float y=3.14f;
	MPI_Request request1;
	MPI_Status status1;
	MPI_Isend (&y,1,MPI_FLOAT, 3, 1, MPI_COMM_WORLD, &request1);
	MPI_Wait(&request1, &status1);
 	std::cout << "rank 1 y= " << y << std::endl;
   }

    if (myrank == 3) {
	MPI_Request request30;
	MPI_Request request31;
	float z[2];
	MPI_Irecv(&z[0],1, MPI_FLOAT, 0, 0,MPI_COMM_WORLD, &request30);
	MPI_Irecv(&z[1],1, MPI_FLOAT, 1, 1,MPI_COMM_WORLD, &request31);
	std::vector<MPI_Request> request3 = {request30, request31};
	MPI_Waitall(2, &request3[0], MPI_STATUSES_IGNORE);
  	std::cout << "rank 3 z= " << z[0] << " " << z[1]  << std::endl;
  }
    MPI_Finalize();
    
    return 0;
}
