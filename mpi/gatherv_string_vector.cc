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
    int vec_size = my_vector.size();
    MPI_Allgather(&vec_size, 1, MPI_INT, ncount.data(), 1, MPI_INT, comm);
    int total_size = ncount[0];
    for (int i=1; i< mpi_size; i++) {
	ndispl[i] = ndispl[i-1] + ncount[i-1];
	total_size += ncount[i];
    }
    // rank 0: 10, 11
    // rank 1: 10
    // str_size_glob would be [10, 11, 10, ...]
    std::vector<int> str_size(vec_size,0);
    std::vector<int> str_size_glob(total_size,0);
    for (int i=0;i<vec_size;i++) str_size[i] = my_vector[i].size();
    MPI_Allgatherv(str_size.data(), vec_size, MPI_INT, str_size_glob.data(),
		   ncount.data(), ndispl.data(), MPI_INT, comm);
    // now build the list of number of char
    std::vector<int> nchar_rank(mpi_size,0);
    int k = 0;
    int nchar_total = 0;
    for (int i=0;i<mpi_size;i++){
	for (int j=0;j<ncount[i];j++) {
	    nchar_rank[i] += str_size_glob[k];
	    k += 1;
	}
	nchar_total += nchar_rank[i];
    }
    // Recycle of ndispl
    ndispl[0] = 0;
    int nchar_glob = 0;
    for (int i=1;i<mpi_size;i++) {
	ndispl[i] = ndispl[i-1] + nchar_rank[i-1];
    }
    char *buff = new char[nchar_rank[mpi_rank]];
    char *buff_glob = new char[nchar_total];
    // dump string vector into a char array
    int cursor = 0;
    for (auto & el: my_vector) {
	for (int i=0; i<el.size(); i++) {
	    buff[cursor+i] = el[i];
	}
	cursor += el.size();
    }
    MPI_Allgatherv(buff, nchar_rank[mpi_rank], MPI_CHAR, buff_glob,
		   nchar_rank.data(), ndispl.data(), MPI_CHAR, comm);
    // convert all string vector into a single char array
    std::vector<std::string> global_vector;
    k = 0;
    for (auto& el : str_size_glob) {
	global_vector.push_back(std::string(&buff_glob[k], el));
	k += el;
    }
    for (auto &el : global_vector) std::cout << el <<  std::endl;

    delete[] buff;
    delete[] buff_glob;
    MPI_Finalize();
    return 0;
}

/*
  mpic++ -std=c++14 gather_string_vector.cc
*/
