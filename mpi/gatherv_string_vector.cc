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
	std::string abc = "from_rank" + std::to_string(mpi_rank);
	std::vector<std::string> my_vector = {abc};
	if (mpi_rank == 0) {
		my_vector.push_back("hello world");
	}
	// count the length of string of each vector
	std::vector<int> len_vector;
	int all_length = 0;
	for (auto &el : my_vector) {
		len_vector.push_back(el.size());
		all_length += el.size();
	}
	// rank 0 has 2 vector
	// rank 1 has 1 vector
	// ncount = [2,1]
	std::vector<int> ndispl(mpi_size,0);
	std::vector<int> ncount(mpi_size,0);
	int local_size = my_vector.size();
	MPI_Gather(&local_size, 1, MPI_INT, ncount.data(), 1, MPI_INT, 0, comm);
	int total_length = ncount[0];
	for (int i=1; i< mpi_size; i++) {
		ndispl[i] = ndispl[i-1] + ncount[i-1];
		total_length += ncount[i];
	}
	// rank 0: 10, 11
	// rank 1: 10
	// final would be 10, 11, 10, ...
	char *buff = new char[all_length];
	char *buff_all = new char[total_length];
	MPI_Gatherv(buff, all_length, MPI_CHAR, buff_all, ncount.data(),
				ndispl.data(), MPI_CHAR, 0, comm);
	// convert all string vector into a single char array

	delete[] buff;
	delete[] buff_all;
	MPI_Finalize();
	return 0;
}

/*
 mpic++ -std=c++14 bcast_string.cc
*/
