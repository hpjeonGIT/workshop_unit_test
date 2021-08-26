#include <iostream>
#include <string>
#include <vector>
#include <mpi.h>
#include <stdexcept>

#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>

// Ref: https://gitlab.tue.nl/SCiarella/hoomd-reversiblecrosslinker/-/blob/master/hoomd/HOOMDMPI.h

struct substruct {
    std::vector<int> ijk;
    std::vector<std::string> subname;
    template <class Archive>
    void serialize(Archive &ar) {
	ar(ijk, subname);
    }
};

struct mainstruct {
    std::vector<double> xyz;
    std::vector<std::string> txt;
    std::vector<substruct> data;
    template <class Archive>
    void serialize(Archive &ar) {
	ar(xyz, txt, data);
    }
};

int main(int argc, char** argv) {
    int mpi_size, mpi_rank;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Info info = MPI_INFO_NULL;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &mpi_size);
    MPI_Comm_rank(comm, &mpi_rank);

    // preparation
    std::vector<mainstruct> abc;
    int nsize;
    if (mpi_rank%2 == 0) {
	nsize = 2;
    } else {
	nsize = 3;
    }
    abc.resize(nsize);
    for (int i=0; i<nsize; i++) {
	abc[i].xyz.push_back(mpi_rank);
	abc[i].txt.push_back("my rank is " + std::to_string(mpi_rank*i));
	substruct inner;
	inner.ijk.push_back(mpi_rank*i); inner.ijk.push_back(mpi_rank*100);
	inner.subname.push_back("inner txt is from " +
				std::to_string(mpi_rank) + " with index " +
				std::to_string(i));
	abc[i].data.push_back(inner);
    }

    // serialize
    std::stringstream ss;
    cereal::BinaryOutputArchive oarchive(ss);
    oarchive(abc);
    ss.flush();
    std::string str_local = ss.str();
    auto send_count = str_local.length(); // send_count will be unsigned long
    std::cout << "send_count = " << send_count << std::endl;
    if (send_count*mpi_size > 2147483647) 
	throw std::runtime_error("32bit integer limit will be violated");
    // gathering
    std::vector<int> ncount(mpi_size), ndispl(mpi_size), nrecv(mpi_size);
    std::string str_global;
    if (mpi_rank == 0) {
	ncount.resize(mpi_size);
	ndispl.resize(mpi_size);
	nrecv.resize(mpi_size);
    }
    MPI_Gather(&send_count, 1, MPI_INT, nrecv.data(), 1, MPI_INT, 0, comm);
    uint64_t sum_count = 0;
    if (mpi_rank ==0) {
	ncount[0] = nrecv[0];
	ndispl[0] = 0;
	sum_count += nrecv[0];
	for (int p=1; p < mpi_size; p++) {
	    ncount[p] = nrecv[p];
	    ndispl[p] = ndispl[p-1] + ncount[p-1];
	    sum_count += nrecv[p];
	}
	str_global.resize(sum_count);
    }
    MPI_Gatherv((void *)str_local.data(), send_count, MPI_BYTE,
		(void *)str_global.data(), ncount.data(), ndispl.data(),
		MPI_BYTE, 0, comm);
    // de-serialize
    if (mpi_rank == 0) {
	std::vector<mainstruct> result;
	for (int i=0;i<mpi_size; i++) {
	    std::stringstream s(std::string(str_global.substr(ndispl[i],
							      ncount[i])));
	    cereal::BinaryInputArchive iarchive(s);
	    std::vector<mainstruct> tmp;
	    iarchive >> tmp;
	    for (auto& el: tmp) result.push_back(el);
	}
	//
	for (auto&el : result) { // 2, 3, 2, 3, ...
	    for (auto& txt : el.txt) {
		std::cout << "main txt " << txt << std::endl;
	    }
	    for (auto& x: el.data) {
		for (auto& txt: x.subname) {
		    std::cout << "sub txt " << txt << std::endl;
		}
	    }
	}
    }
    MPI_Finalize();
    return 0;
}

/* 

mpic++ -std=c++14 ./gatherv_cereal.cc -I/opt/cereal-1.3.0/include/

$ mpirun -np 3 ./a.out 
main txt my rank is 0
sub txt inner txt is from 0 with index 0
main txt my rank is 0
sub txt inner txt is from 0 with index 1
main txt my rank is 0
sub txt inner txt is from 1 with index 0
main txt my rank is 1
sub txt inner txt is from 1 with index 1
main txt my rank is 2
sub txt inner txt is from 1 with index 2
main txt my rank is 0
sub txt inner txt is from 2 with index 0
main txt my rank is 2
sub txt inner txt is from 2 with index 1

*/
