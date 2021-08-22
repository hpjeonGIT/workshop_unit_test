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


void hdf5_create2d_table(hid_t hfile, std::string& dname, hid_t data_type,
			 hsize_t ncols) {
    hsize_t dims[2] = {0, ncols};
    hsize_t dims_max[2] = {H5S_UNLIMITED, ncols};
    hid_t hspace = H5Screate_simple(2, dims, dims_max);
    hid_t hprop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_layout(hprop, H5D_CHUNKED);
    hsize_t cdims[2] = {1, ncols};
    H5Pset_chunk(hprop,2,cdims);
    hid_t hset = H5Dcreate(hfile, dname.c_str(), data_type, hspace,
		     H5P_DEFAULT, hprop, H5P_DEFAULT);
    H5Sclose(hspace);
    H5Pclose(hprop);
    H5Dclose(hset);    
}

void hdf5_append2d_table(hid_t hfile, std::string& dname, hid_t data_type,
			 hsize_t ncols, hsize_t nrows, void *tmp) {
    hid_t hset = H5Dopen (hfile, dname.c_str(), H5P_DEFAULT);
    hsize_t crows = H5Dget_storage_size(hset)/H5Tget_size(data_type);
    std::cout << "current rows = " << crows << std::endl;
    hsize_t dims[2] = {crows, ncols};
    dims[0] += nrows;
    hsize_t dims_mem[2] = {nrows,ncols};
    hid_t hmem = H5Screate_simple(2,dims_mem,NULL);
    H5Dset_extent(hset, dims);
    hid_t hspace = H5Dget_space(hset);
    hsize_t start[2] = {crows, 0};
    hsize_t count[2] = {nrows, ncols};
    H5Sselect_hyperslab(hspace, H5S_SELECT_SET, start, NULL, count, NULL);
    H5Dwrite(hset, data_type, hmem, hspace, H5P_DEFAULT, tmp);
    H5Sclose(hmem);
    H5Dclose(hset);
}

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
    hstat = H5Tinsert(hid_new, "value", HOFFSET(new_dtype, xyz),
		      H5T_NATIVE_DOUBLE);
    //
    // making an empty table
    hid_t hfile, hspace, hprop, hset, hgrp;
    hfile = H5Fcreate(fn.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hgrp = H5Gcreate2(hfile, "/GRP1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Gclose(hgrp);
    std::string dname = "/GRP1/SAMPLE";
    hdf5_create2d_table(hfile, dname, hid_new, 1);
    H5Fclose(hfile);
    //
    for (int n = 0; n<5; n++){
	hfile = H5Fopen (fn.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);	
	new_dtype tmp;
	tmp.ijk = n;
	std::string descr = "STAT" + std::to_string(n);
	strcpy(tmp.spec, descr.c_str());
	tmp.xyz = 3.1415*n;
	hdf5_append2d_table(hfile, dname, hid_new, 1, 1, &tmp);
	H5Fclose(hfile);
    }
    hfile = H5Fopen (fn.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
    new_dtype tmp[3];
    tmp[0].ijk = 123; tmp[1].ijk = 456; tmp[2].ijk = 789;
    std::string somestring = "abc";
    strcpy(tmp[0].spec, somestring.c_str()); somestring += "0";
    strcpy(tmp[1].spec, somestring.c_str()); somestring += "1";
    strcpy(tmp[2].spec, somestring.c_str());
    tmp[0].xyz = 0.123; tmp[1].xyz = 0.456; tmp[2].xyz = 0.789;
    hdf5_append2d_table(hfile, dname, hid_new, 1, 3, tmp);
    H5Fclose(hfile);
    return 0;
}
