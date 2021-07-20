#include<iostream>
#include <string>
#include <vector>
#include "hdf5.h"

int main(int argc, char** argv) {
	std::vector<double> xx = {1,2,3,4,5};
	int ncols = xx.size();
	int mpi_size, mpi_rank;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Info info = MPI_INFO_NULL;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(comm, &mpi_size);
	MPI_Comm_rank(comm, &mpi_rank);
	for (auto& el : xx) el += mpi_rank*10;
	std::string fn = "mpi_indepenet.h5";
	hid_t plist = H5Pcreate(H5P_FILE_ACCESS);
	H5Pset_fapl_mpio(plist, comm, info);
	hid_t hfile = H5Fcreate(fn.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, plist);
	H5Pclose(plist);

	hsize_t dims[2] = {1, ncols};
	hid_t hspace = H5Screate_simple(2, dims, NULL);
	std::vector<hid_t> dset_id(mpi_size);
	for (int i=0;i<mpi_size; i++) {
		std::string dname = "/Data" + std::to_string(i);
		dset_id[i] = H5Dcreate2(hfile, dname.c_str(), H5T_NATIVE_DOUBLE, hspace,
								H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
	}
	hid_t my_dset = dset_id[mpi_rank];
	H5Sclose(hspace);

	hsize_t start[2] = {0,0};
	hsize_t count[2] = {1,5};
	hid_t mspace = H5Screate_simple(2, dims, NULL);
	hspace = H5Dget_space(my_dset);
	H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
	plist = H5Pcreate(H5P_DATASET_XFER);
	H5Pset_dxpl_mpio(plist, H5FD_MPIO_INDEPENDENT);
	H5Dwrite(my_dset, H5T_NATIVE_DOUBLE, mspace, hspace, plist, xx.data());
	H5Pclose(plist);
	H5Sclose(mspace);
	for (int i=0;i<mpi_size; i++) H5Dclose(dset_id[i]);
	H5Fclose(hfile);
	MPI_Finalize();
	return 0;
}

/*
 mpic++ -std=c++14 independent_writing.cc -L/home/hpjeon/sw_local/hdf5/1.8.20/lib \
  -lhdf5 -I/home/hpjeon/sw_local/hdf5/1.8.20/include
*/
