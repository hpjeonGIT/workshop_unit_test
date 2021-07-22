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
    int nchar_local = 0;
    for (auto& el: my_vector) nchar_local += el.size();
    nchar_local += my_vector.size();
    char *buff = new char[nchar_local];
    int cursor = 0;
    for (auto & el: my_vector) {
	for (int i=0; i<el.size(); i++) {
	    buff[cursor+i] = el[i];
	}
	cursor += el.size();
	buff[cursor] = '\0'; // injection of the delimiter
	cursor += 1;
    }
    std::vector<int> ndispl(mpi_size,0);
    std::vector<int> ncount(mpi_size,0);
    int vec_size = my_vector.size();
    MPI_Allgather(&nchar_local, 1, MPI_INT, ncount.data(), 1, MPI_INT, comm);
    int nchar_glob = ncount[0];
    for (int i=1; i< mpi_size; i++) {
	ndispl[i] = ndispl[i-1] + ncount[i-1];
	nchar_glob += ncount[i];
    }
    char *buff_glob = new char[nchar_glob];
    MPI_Allgatherv(buff, nchar_local, MPI_CHAR, buff_glob,
		   ncount.data(), ndispl.data(), MPI_CHAR, comm);
    std::vector<std::string> global_vector;
    std::string tmp;
    for (int i=0;i<nchar_glob;i++) {
	if (buff_glob[i] == '\0') {
	    global_vector.push_back(tmp);
	    tmp.clear();
	} else {
	    tmp.push_back(buff_glob[i]);
	}	
    }
       
    for (auto &el : global_vector) std::cout << el <<  std::endl;

    delete[] buff;
    delete[] buff_glob;
    MPI_Finalize();
    return 0;
}

/*
  mpic++ -std=c++14 gather_string_vector2.cc
*/
