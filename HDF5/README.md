## Install HDF5/1.8.20
 - ./configure --prefix=/opt/sw_local/hdf5/1.8.20 --enable-shared --enable-static --enable-build-mode=production --enable-deprecated-symbols --enable-hl --enable-fortran --enable-parallel CC=mpicc FC=mpif90 CXX=mpicxx F77=mpif90
 - make -j4
 - make install

## Appending rows into existing table
- g++ -std=c++17 append_rows.cc -L/opt/sw_local/hdf5/1.8.20/lib -lhdf5 -I/opt/sw_local/hdf5/1.8.20/include
```
$ ~/sw_local/hdf5/1.8.20/bin/h5dump result.h5
HDF5 "result.h5" {
GROUP "/" {
   GROUP "GRP1" {
      DATASET "VDAT0" {
         DATATYPE  H5T_IEEE_F64LE
         DATASPACE  SIMPLE { ( 2, 4 ) / ( H5S_UNLIMITED, 4 ) }
         DATA {
         (0,0): 1, 2, 3, 4,
         (1,0): 11, 22, 33, 44
         }
      }
   }
}
}
```
- Using h5py
```
>>> import h5py
>>> f = h5py.File('result.h5','r')
>>> f['GRP1']['VDAT0'][:]
array([[ 1.,  2.,  3.,  4.],
       [11., 22., 33., 44.]])
```
## Add labels as a string list
- g++ -std=c++17 add_labels.cc  -L/opt/sw_local/hdf5/1.8.20/lib -lhdf5 -I/opt/sw_local/hdf5/1.8.20/include
- Using memcpy() yielded trash/garbage character. Copy string into char array 1:1
 ```
 ~/sw_local/hdf5/1.8.20/bin/h5dump result.h5
HDF5 "result.h5" {
GROUP "/" {
   GROUP "GRP1" {
      DATASET "LABELS" {
         DATATYPE  H5T_STRING {
            STRSIZE 6;
            STRPAD H5T_STR_NULLTERM;
            CSET H5T_CSET_ASCII;
            CTYPE H5T_C_S1;
         }
         DATASPACE  SIMPLE { ( 3 ) / ( 3 ) }
         DATA {
         (0): "RED   ", "BLACK ", "YeLLoW"
         }
      }
   }
}
}
```
