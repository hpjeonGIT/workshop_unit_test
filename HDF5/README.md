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
- mpic++ -std=c++14 independent_writing.cc -L/opt/hdf5/1.8.20/lib -lhdf5 -I/opt/hdf5/1.8.20/include
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

## Independent writing with appending rows
-  mpic++ -std=c++14 append_parallel_ind.cc -L/opt/hdf5/1.8.20/lib \
  -lhdf5 -I/opt/hdf5/1.8.20/include
- When extending dset_id[], make sure that all of dset_id[] are extended over entire ranks. Extending my_dset only on a single rank will produce inappropriate reuslts.
```
h5dump mpi_ind.h5 
HDF5 "mpi_ind.h5" {
GROUP "/" {
   GROUP "GRP01" {
      DATASET "Data0" {
         DATATYPE  H5T_IEEE_F64LE
         DATASPACE  SIMPLE { ( 5, 5 ) / ( H5S_UNLIMITED, 5 ) }
         DATA {
         (0,0): 1, 2, 3, 4, 5,
         (1,0): 1, 2, 3, 4, 5,
         (2,0): 1, 2, 3, 4, 5,
         (3,0): 1, 2, 3, 4, 5,
         (4,0): 1, 2, 3, 4, 5
         }
      }
      DATASET "Data1" {
         DATATYPE  H5T_IEEE_F64LE
         DATASPACE  SIMPLE { ( 5, 5 ) / ( H5S_UNLIMITED, 5 ) }
         DATA {
         (0,0): 21, 22, 23, 24, 25,
         (1,0): 31, 32, 33, 34, 35,
         (2,0): 41, 42, 43, 44, 45,
         (3,0): 51, 52, 53, 54, 55,
         (4,0): 61, 62, 63, 64, 65
         }
      }
      DATASET "Data2" {
         DATATYPE  H5T_IEEE_F64LE
         DATASPACE  SIMPLE { ( 5, 5 ) / ( H5S_UNLIMITED, 5 ) }
         DATA {
         (0,0): 41, 42, 43, 44, 45,
         (1,0): 61, 62, 63, 64, 65,
         (2,0): 81, 82, 83, 84, 85,
         (3,0): 101, 102, 103, 104, 105,
         (4,0): 121, 122, 123, 124, 125
         }
      }
   }
}
}
```
- For the iterations of 100,000 using 3 MPI ranks, this took more than 30 sec using intel-i3
- We may use chunked row growth - may increase the row size by 400. In the end, reset the table size with exact row size
  - `mpic++ -std=c++14 append_chunk_parallel_ind.cc   -L/opt/hdf5/1.8.20/lib   -lhdf5 -I/opt/hdf5/1.8.20/include`
  - This took 5.439 sec
- Or we may aggregate results into a vector of vectors - then dump all results into double array, then write HDF5 once
  - `mpic++ -std=c++14 finalize_parallel_ind.cc    -L/opt/hdf5/1.8.20/lib   -lhdf5 -I/opt/hdf5/1.8.20/include`
  - This took 0.352 sec
- Parallel file system may take the advantage of MPI info
  - Ref: https://forum.hdfgroup.org/t/slow-writing-parallel-hdf5-performance-for-only-one-variable/3258
```
    MPI_Info info;
    MPI_Info_create(&info);
    MPI_Info_set(info, "striping_unit", "1048576");
    MPI_Info_set(info, "ind_wr_buffer_size", "1024");
    H5Pset_fapl_mpio(hprop, comm, info);
```
## Parallel collective writing + attribute
- mpic++ -std=c++14 parallel_hyperslab.cc -L/home/hpjeon/sw_local/hdf5/1.8.20/lib -I/home/hpjeon/sw_local/hdf5/1.8.20/include  -lhdf5
- mpirun -np 3 ./a.out 
- h5dump  par_hyperslab.h5 
```
HDF5 "par_hyperslab.h5" {
GROUP "/" {
   DATASET "ATTR" {
      DATATYPE  H5T_STD_I32LE
      DATASPACE  SIMPLE { ( 3 ) / ( 3 ) }
      DATA {
      (0): 0, 0, 0
      }
      ATTRIBUTE "coord" {
         DATATYPE  H5T_STD_I32LE
         DATASPACE  SIMPLE { ( 3 ) / ( 3 ) }
         DATA {
         (0): 11, 22, 33
         }
      }
   }
   DATASET "PRL" {
      DATATYPE  H5T_IEEE_F64LE
      DATASPACE  SIMPLE { ( 3, 5 ) / ( 3, 5 ) }
      DATA {
      (0,0): 1, 2, 3, 4, 5,
      (1,0): 11, 12, 13, 14, 15,
      (2,0): 21, 22, 23, 24, 25
      }
   }
}
}
```
