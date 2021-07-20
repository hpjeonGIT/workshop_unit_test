#include<iostream>
#include <string>
#include <vector>
#include <mpi.h>

int main(int argc, char** argv) {
	int mpi_size, mpi_rank;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Info info = MPI_INFO_NULL;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(comm, &mpi_size);
	MPI_Comm_rank(comm, &mpi_rank);
	std::string my_script;
	if (mpi_rank == 0) {
		my_script = "hello world";
	}
	size_t length = my_script.size();
	if (mpi_rank == 0) {
		MPI_Bcast(&length, 1, MPI_INT, 0, comm);
		MPI_Bcast((void*)my_script.c_str(), length, MPI_CHAR, 0, comm);
	} else {
		MPI_Bcast(&length, 1, MPI_INT, 0, comm);
		char *buff = new char[length];
		MPI_Bcast(buff, length, MPI_CHAR, 0, comm);
		my_script = std::string(buff);
		delete[] buff;
	}
	std::cout << "my_rank = " << mpi_rank << " " << my_script << std::endl;
	MPI_Finalize();
	return 0;
}

/*
 mpic++ -std=c++14 bcast_string.cc
*/
