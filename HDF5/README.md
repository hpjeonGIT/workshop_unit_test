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

## Independent writing
- A group must be written using collective calls
- Data sets might be written by different, avoiding collective calls
- However, all data sets must be defined over the entire ranks
- mpic++ -std=c++14 independent_writing.cc -L/home/hpjeon/sw_local/hdf5/1.8.20/lib -lhdf5 -I/home/hpjeon/sw_local/hdf5/1.8.20/include
```
h5dump mpi_indepenet.h5
HDF5 "mpi_indepenet.h5" {
GROUP "/" {
   DATASET "Data0" {
      DATATYPE  H5T_IEEE_F64LE
      DATASPACE  SIMPLE { ( 1, 5 ) / ( 1, 5 ) }
      DATA {
      (0,0): 1, 2, 3, 4, 5
      }
   }
   DATASET "Data1" {
      DATATYPE  H5T_IEEE_F64LE
      DATASPACE  SIMPLE { ( 1, 5 ) / ( 1, 5 ) }
      DATA {
      (0,0): 11, 12, 13, 14, 15
      }
   }
   DATASET "Data2" {
      DATATYPE  H5T_IEEE_F64LE
      DATASPACE  SIMPLE { ( 1, 5 ) / ( 1, 5 ) }
      DATA {
      (0,0): 21, 22, 23, 24, 25
      }
   }
}
}
```
- Data0 is written by rank0 and Data1 is by rank1. Data2 is by rank2. No need to call MPI_Gather()
