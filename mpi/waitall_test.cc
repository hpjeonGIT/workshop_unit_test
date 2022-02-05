#include <iostream>
#include <vector>
#include "mpi.h"

// Async version of a2a_test.cc
int main(int argc, char** argv) {

    int myrank, ncpus;
    int target, source;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    std::vector<int> s_val;
    if (myrank == 0) {
	s_val = {1,1, 3,3,3};
    } else {
        s_val = {0};
        for (int i=0; i< myrank; i++) s_val.push_back(myrank-1);
    }
    /*
      rank 0: 1,1, 3,3,3 -> send 1,1 to rank 1. send 3,3,3 to rank 3
      rank 1: 0,0 -> send 0,0 to rank 0
      rank 2: 0, 1,1 -> send 0 to rank 0, send 1,1 to rank 1
      rank 3: 0, 2,2,2 -> send 0 to rank 0, send 2,2,2 to rank 2
    */
    std::vector<int> send_size(ncpus,0), rec_size(ncpus,0);
    for (int i=0; i< s_val.size(); i++) {
        auto idx = s_val[i];
        send_size[idx] ++;
    }
    std::vector<int> send_displ = {0};
    MPI_Alltoall(send_size.data(), 1, MPI_INT, rec_size.data(), 1,
                 MPI_INT, MPI_COMM_WORLD);
    /*
      rank0 will receive 0,0 from rank 1. 0 from rank 2. 0 from rank 3
       rank1 will receive 1,1 from rank 0. 1,1 from rank 2
       rank2 will receive 2,2,2 from rank 3
       rank3 will receive 3,3,3 from rank 0
    */
    for (int i=0; i< send_size.size(); i++) {
        send_displ.push_back(send_displ.back() + send_size[i]);  
    }
    send_displ.pop_back(); // removes the last element as it is not necessary
    std::vector<int> rec_displ = {0}; // initial setup
    int local_sum = 0;
    for (int i=0; i< rec_size.size(); i++) {
        rec_displ.push_back(rec_displ.back() + rec_size[i]);
        local_sum += rec_size[i];
    }
    rec_displ.pop_back(); // removes the last element as it is not necessary
    //
    int nonzero_send=0, nonzero_rec=0;
    for (auto x: send_size) if (x > 0) nonzero_send ++;
    for (auto x: rec_size ) if (x > 0) nonzero_rec ++;
    std::vector<int> r_val(local_sum);
    std::vector<MPI_Status> stat(nonzero_send + nonzero_rec);
    std::vector<MPI_Request> req(nonzero_send + nonzero_rec);
    int nreq = 0;
    for (int i = 0; i< ncpus; i++) {
        if (send_size[i] > 0) {
            MPI_Isend(&s_val[send_displ[i]], send_size[i], MPI_INT, i, 0,
                      MPI_COMM_WORLD, &req[nreq]);
            nreq++;
        }
        if (rec_size[i] > 0) {
            MPI_Irecv(&r_val[rec_displ[i]], rec_size[i], MPI_INT, i, 0,
                      MPI_COMM_WORLD, &req[nreq]);
            nreq++;
        }
    }
    MPI_Waitall(nonzero_send+nonzero_rec, req.data(), stat.data());
    if (myrank == 1) for(int i=0; i< r_val.size(); i++) std::cout << r_val[i] << std::endl;
    MPI_Finalize();
    return 0;
}
