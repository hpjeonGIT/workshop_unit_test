#include <iostream>
#include <vector>
#include "mpi.h"


class parray {
    
public:
    int myrank,ncpus;
    parray() {
	MPI_Init(nullptr, nullptr);
	MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    }
    ~parray(){
	MPI_Finalize();
    }
    
};

int main(int argc, char** argv) {

    parray mympi;
    //mympi.initialize();
    if (mympi.ncpus != 4) {
	std::cout << "ncpus is not 4. Exits here \n";
	return 1;
    }
    std::cout << mympi.myrank << " out of " << mympi.ncpus << std::endl;
    
    if (mympi.myrank == 0){
	float x=1.23f;
	MPI_Request request0;
	MPI_Status status0;
	MPI_Isend (&x,1,MPI_FLOAT, 3, 0, MPI_COMM_WORLD, &request0);
	MPI_Wait(&request0, MPI_STATUSES_IGNORE);
	std::cout << "rank 0 x= " << x << std::endl;
    }
    
    if (mympi.myrank == 1){
	float y=3.14f;
	MPI_Request request1;
	MPI_Status status1;
	MPI_Isend (&y,1,MPI_FLOAT, 3, 1, MPI_COMM_WORLD, &request1);
	MPI_Wait(&request1, MPI_STATUSES_IGNORE);
 	std::cout << "rank 1 y= " << y << std::endl;
   }
    
    if (mympi.myrank == 3) {
	MPI_Request request30;
	MPI_Request request31;
	float z[2];
	MPI_Irecv(&z[0],1, MPI_FLOAT, 0, 0,MPI_COMM_WORLD, &request30);
	MPI_Irecv(&z[1],1, MPI_FLOAT, 1, 1,MPI_COMM_WORLD, &request31);
	std::vector<MPI_Request> request3 = {request30, request31};
	MPI_Waitall(request3.size(), request3.data(), MPI_STATUSES_IGNORE);
	//MPI_Wait(&request30, MPI_STATUSES_IGNORE);
  	std::cout << "rank 3 z= " << z[0] << " " << z[1]  << std::endl;
  }

    
    return 0;
}
