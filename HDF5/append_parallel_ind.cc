#include<iostream>
#include <string>
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
    for (auto& el : xx) el += mpi_rank*10;
    std::string fn = "mpi_ind.h5";
    hid_t plist = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(plist, comm, info);
    hid_t hfile = H5Fcreate(fn.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, plist);
    H5Pclose(plist);
    hid_t hgrp = H5Gcreate2(hfile, "/GRP01", H5P_DEFAULT, H5P_DEFAULT,
			    H5P_DEFAULT);
    //
    hsize_t dims[2] = {0, ncols};
    hsize_t dims_max[2] = {H5S_UNLIMITED, ncols};
    hid_t hspace = H5Screate_simple(2, dims, dims_max);
    plist = H5Pcreate(H5P_DATASET_CREATE);
    hsize_t cdims[2] = {1, ncols};
    H5Pset_chunk(plist, 2, cdims);    
    std::vector<hid_t> dset_id(mpi_size);
    for (int i=0;i<mpi_size; i++) {
	std::string dname = "/GRP01/Data" + std::to_string(i);
	dset_id[i] = H5Dcreate2(hfile, dname.c_str(), H5T_NATIVE_DOUBLE, hspace,
				H5P_DEFAULT,plist,H5P_DEFAULT);
    }
    hid_t my_dset = dset_id[mpi_rank];
    H5Pclose(plist);
    H5Sclose(hspace);

    for (int i=0; i< 5; i++) {
	for (auto& el : xx) el += mpi_rank*10;
	dims[0] = 1;
	hid_t mspace = H5Screate_simple(2, dims, NULL);
	dims[0] = i + 1;
	for (int i=0;i<mpi_size; i++) H5Dset_extent(dset_id[i], dims);
	// make sure extend all of dset_id[] over entire ranks
	hspace = H5Dget_space(my_dset);
	hsize_t start[2] = {dims[0]-1,0};
	hsize_t count[2] = {1,ncols};
	H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
	plist = H5Pcreate(H5P_DATASET_XFER);
	H5Pset_dxpl_mpio(plist, H5FD_MPIO_INDEPENDENT);
	H5Dwrite(my_dset, H5T_NATIVE_DOUBLE, mspace, hspace, plist, xx.data());
	H5Pclose(plist);
	H5Sclose(mspace);
	H5Sclose(hspace);
    }
    for (int i=0;i<mpi_size; i++) H5Dclose(dset_id[i]);
    H5Gclose(hgrp);
    H5Fclose(hfile);
    MPI_Finalize();
    return 0;
}

/*
  mpic++ -std=c++14 append_parallel_ind.cc -L/opt/hdf5/1.8.20/lib \
  -lhdf5 -I/opt/hdf5/1.8.20/include
*/
