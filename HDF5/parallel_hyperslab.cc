#include <iostream>
#include <vector>
#include "hdf5.h"

int main(int argc, char** argv) {
    std::vector<double> xx = {1,2,3,4,5};
    hsize_t ncols = xx.size();
    int mpi_size, mpi_rank;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Info info = MPI_INFO_NULL;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &mpi_size);
    MPI_Comm_rank(comm, &mpi_rank);
    for (auto &x: xx) x+= mpi_rank*10;
    //
    // Parallel writing
    std::string fn = "par_hyperslab.h5";
    hid_t hprop = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(hprop, comm, info);
    hid_t hfile = H5Fcreate(fn.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, hprop);
    H5Pclose(hprop);
    hsize_t all_rows = mpi_size;
    hsize_t dims[2] = {all_rows, ncols};
    hid_t hspace = H5Screate_simple(2, dims, NULL);
    hid_t hset = H5Dcreate2(hfile, "/PRL", H5T_NATIVE_DOUBLE, hspace,
			    H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Sclose(hspace);
    hsize_t istart = mpi_rank;
    hsize_t start[2] = {istart,0};
    hsize_t count[2] = {1, ncols};
    hsize_t dims_m[2] = {1, ncols};
    hid_t hmem = H5Screate_simple(2, dims_m, NULL);
    hspace = H5Dget_space(hset);
    H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
    hprop = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(hprop, H5FD_MPIO_COLLECTIVE);
    H5Dwrite(hset, H5T_NATIVE_DOUBLE, hmem, hspace, hprop, xx.data());
    H5Pclose(hprop);
    H5Sclose(hmem);
    H5Dclose(hset);
    // hspace is not closed as it is not created but gotten

    // attribute
    dims[0] = 3;
    hspace = H5Screate_simple(1, dims, NULL);
    hset = H5Dcreate2(hfile, "/ATTR", H5T_NATIVE_INT, hspace,
		      H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    hid_t hatt = H5Acreate(hset, "coord", H5T_NATIVE_INT, hspace,
			   H5P_DEFAULT, H5P_DEFAULT);
    std::vector<int> ijk = {11, 22, 33};
    H5Awrite(hatt, H5T_NATIVE_INT, ijk.data());
    H5Aclose(hatt);
    H5Sclose(hspace);
    H5Dclose(hset);
    //
    H5Fclose(hfile);
    MPI_Finalize();
    return 0;
}

/* 

mpic++ -std=c++14 parallel_hyperslab.cc -L/opt/hdf5/1.8.20/lib -I/opt/sw_local/hdf5/1.8.20/include  -lhdf5

*/
