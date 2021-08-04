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
    std::string fn = "mpi_ind_chunked.h5";
    hid_t plist = H5Pcreate(H5P_FILE_ACCESS);
// Ref: https://forum.hdfgroup.org/t/slow-writing-parallel-hdf5-performance-for-only-one-variable/3258
    MPI_Info_create(&info);
    MPI_Info_set(info, "striping_unit", "1048576");
    MPI_Info_set(info, "ind_wr_buffer_size", "40");
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
    int nchunk = 400;
    int rows_now=0;
    int rows_size=0;
    for (int i=0; i< 100000; i++) {
	for (auto& el : xx) el += mpi_rank*10;
	dims[0] = 1;
	hid_t mspace = H5Screate_simple(2, dims, NULL);
	if (rows_size <= rows_now) {
	    rows_size += nchunk;
	    dims[0] = static_cast<hsize_t> (rows_size);
	    for (int i=0;i<mpi_size; i++) H5Dset_extent(dset_id[i], dims);
	// make sure extend all of dset_id[] over entire ranks
	}
	hspace = H5Dget_space(my_dset);
	hsize_t start[2] = {rows_now,0};
	hsize_t count[2] = {1,ncols};
	H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
	plist = H5Pcreate(H5P_DATASET_XFER);
	H5Pset_dxpl_mpio(plist, H5FD_MPIO_INDEPENDENT);
	H5Dwrite(my_dset, H5T_NATIVE_DOUBLE, mspace, hspace, plist, xx.data());
	rows_now ++;
	H5Pclose(plist);
	H5Sclose(mspace);
	H5Sclose(hspace);
    }
    // resize - removing margin
    dims[0] = static_cast<hsize_t> (rows_now);
    for (int i=0;i<mpi_size; i++) H5Dset_extent(dset_id[i], dims);
    //
    for (int i=0;i<mpi_size; i++) H5Dclose(dset_id[i]);
    H5Gclose(hgrp);
    H5Fclose(hfile);
    MPI_Finalize();
    return 0;
}

/*
  mpic++ -std=c++14 append_chunk_parallel_ind.cc \
  -L/opt/hdf5/1.8.20/lib \
  -lhdf5 -I/opt/hdf5/1.8.20/include
*/
