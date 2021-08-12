#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "hdf5.h"

static const int nchar=6;

typedef struct {
    int ijk;
    char spec[nchar];
    double xyz;
} new_dtype;
    

int main(int argc, char** argv) {    
    std::string fn = "result.h5";
    //
    // making new data type using compound/structure datatype
    hid_t hid_new = H5Tcreate(H5T_COMPOUND, sizeof(new_dtype));
    herr_t hstat = H5Tinsert(hid_new, "index", HOFFSET(new_dtype, ijk),
			     H5T_NATIVE_INT);    
    hid_t strtype = H5Tcopy(H5T_C_S1);
    hstat = H5Tset_size(strtype, nchar*sizeof(char));
    hstat = H5Tinsert(hid_new, "descr", HOFFSET(new_dtype, spec), strtype);
    hstat = H5Tinsert(hid_new, "value", HOFFSET(new_dtype, xyz), H5T_NATIVE_DOUBLE);
    //
    // making an empty table
    hid_t hfile, hspace, hprop, hset, hgrp;
    hfile = H5Fcreate(fn.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hgrp = H5Gcreate2(hfile, "/GRP1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Gclose(hgrp);
    hsize_t ncols = 1;
    hsize_t dims[1] = {0};
    hsize_t dims_max[1] = {H5S_UNLIMITED};
    hspace = H5Screate_simple(1, dims, dims_max);
    hprop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_layout(hprop, H5D_CHUNKED);
    hsize_t cdims[1] = {ncols};
    H5Pset_chunk(hprop,1,cdims);
    hset = H5Dcreate(hfile, "/GRP1/SAMPLE", hid_new, hspace,
		     H5P_DEFAULT, hprop, H5P_DEFAULT);
    H5Dclose(hset);
    H5Pclose(hprop);
    H5Sclose(hspace);
    H5Fclose(hfile);
    //
    // Repetition of re-opening/appending/closing
    for (int n = 0; n<5; n++){
      hfile = H5Fopen (fn.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
      hset = H5Dopen (hfile, "/GRP1/SAMPLE", H5P_DEFAULT);
      new_dtype tmp;
      tmp.ijk = n;
      std::string descr = "STAT" + std::to_string(n);
      strcpy(tmp.spec, descr.c_str());
      tmp.xyz = 3.1415*n;
      dims[0] ++;
      hsize_t dims_mem[1] = {ncols};
      hid_t hmem = H5Screate_simple(1,dims_mem,NULL);
      H5Dset_extent(hset, dims);
      hspace = H5Dget_space(hset);
      hsize_t start[1] = {dims[0]-1};
      hsize_t count[1] = {ncols};
      H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
      H5Dwrite(hset, hid_new, hmem, hspace, H5P_DEFAULT, &tmp);
      H5Sclose(hmem);
      H5Dclose(hset);
      H5Fclose(hfile);
    }
    return 0;
}
