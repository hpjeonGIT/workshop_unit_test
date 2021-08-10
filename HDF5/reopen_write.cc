// Ref: https://stackoverflow.com/questions/15379399/writing-appending-arrays-of-float-to-the-only-dataset-in-hdf5-file-in-c
#include <iostream>
#include <vector>
#include <unistd.h>
#include "hdf5.h"

int main(int argc, char** argv) {
    std::string fn = "result.h5";
    std::vector<double> xx =  {1,2,3,4};
    hid_t hfile, hspace, plist, hset, hgrp;
    herr_t hstatus;
    hfile = H5Fcreate(fn.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hgrp = H5Gcreate2(hfile, "/GRP1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    size_t ncols = 4;
    size_t nrows = 1;
    hsize_t dims[2] = {0, ncols};
    hsize_t dims_mem[2] = {1, ncols};
    hsize_t dims_max[2] = {H5S_UNLIMITED, ncols};
    hspace = H5Screate_simple(2, dims, dims_max);
    plist = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_layout(plist, H5D_CHUNKED);
    hsize_t cdims[2] = {2, ncols};
    H5Pset_chunk(plist,2,cdims);
    hset = H5Dcreate(hfile, "/GRP1/VDAT0", H5T_NATIVE_DOUBLE, hspace,
		     H5P_DEFAULT, plist, H5P_DEFAULT);
    H5Pclose(plist);
    H5Sclose(hspace);
    //appending the first row
    for (int n=0;n<3;n++) {	    
      dims[0] ++;
      hid_t mspace = H5Screate_simple(2,dims_mem,NULL);
      H5Dset_extent(hset, dims);
      hspace = H5Dget_space(hset);
      hsize_t start[2] = {dims[0]-1,0};
      hsize_t count[2] = {nrows, ncols};
      H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
      H5Dwrite(hset, H5T_NATIVE_DOUBLE, mspace, hspace, H5P_DEFAULT, xx.data());
      H5Sclose(mspace);
      for (auto &el: xx) el++;
    }
    //
    H5Dclose(hset);
    H5Gclose(hgrp);
    H5Fclose(hfile);
    // re-opening
    hfile = H5Fopen (fn.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
    hset = H5Dopen (hfile, "/GRP1/VDAT0", H5P_DEFAULT);
    dims[0] ++;
    hid_t mspace = H5Screate_simple(2,dims_mem,NULL);
    H5Dset_extent(hset, dims);
    hspace = H5Dget_space(hset);
    hsize_t start[2] = {dims[0]-1,0};
    hsize_t count[2] = {nrows, ncols};
    H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
    H5Dwrite(hset, H5T_NATIVE_DOUBLE, mspace, hspace, H5P_DEFAULT, xx.data());
    std::cout << "writing now" << std::endl;
    sleep(10);
    // during sleeping, check result.h5 from python or h5dump
    H5Sclose(mspace);
    H5Dclose(hset);
    H5Fclose(hfile);
	
    return 0;
	
}

/*
  g++ -std=c++14 reopen_write.cc -L/opt/hdf5/1.8.20/lib -lhdf5 -I/opt/hdf5/1.8.20/include

*/
