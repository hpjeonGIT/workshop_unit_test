// Ref: https://stackoverflow.com/questions/15379399/writing-appending-arrays-of-float-to-the-only-dataset-in-hdf5-file-in-c
#include <iostream>
#include <vector>
#include "hdf5.h"

int main(int argc, char** argv) {
	const int lenchar = 6;
	std::string fn = "result.h5";
	std::vector<std::string> xx =  {"RED", "BLACK", "YeLLoW"};
	size_t ncols = xx.size();
	size_t nsize = ncols*lenchar;
	char *buff = new char[nsize];
	uint cursor = 0;
	for (auto& s : xx) {
		if (s.size() > lenchar) throw std::runtime_error("Violation of size");
		for (uint k=0; k < s.size(); k++) buff[cursor+k] = s[k];
		for (uint k=s.size(); k < lenchar; k++) buff[cursor+k] = ' ';
		cursor += lenchar;
	}
	hid_t hfile, hspace, plist, hset, hgrp;
	herr_t hstatus;
	hfile = H5Fcreate(fn.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	hgrp = H5Gcreate2(hfile, "/GRP1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	hsize_t dims[1] = {ncols};
	hspace = H5Screate_simple(1, dims, NULL);
	plist = H5Pcreate(H5P_DATASET_CREATE);
	H5Pset_layout(plist, H5D_CHUNKED);
	hsize_t cdims[1] = {ncols};
	H5Pset_chunk(plist,1,cdims);
	hid_t strtype = H5Tcopy(H5T_C_S1);
	hstatus = H5Tset_size(strtype, lenchar*sizeof(char));
	hset = H5Dcreate(hfile, "/GRP1/LABELS", strtype, hspace,
					H5P_DEFAULT, plist, H5P_DEFAULT);
	hid_t mspace = H5Screate_simple(1,dims,NULL);
	H5Dwrite(hset, strtype, mspace, hspace, H5P_DEFAULT, buff);
	H5Sclose(hspace);
	H5Sclose(mspace);
	H5Dclose(hset);
	H5Pclose(plist);
	H5Gclose(hgrp);
	H5Fclose(hfile);
	delete[] buff;
	return 0;
}
