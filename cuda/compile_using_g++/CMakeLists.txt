#
# stackoverflow.com/questions/35886052/cuda-c-linking-error-undefined-reference-to
cmake_minimum_required(VERSION 3.0)
#
project(simple CXX CUDA)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions(-std=c++14)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g -Wall")
set(CMAKE_CUDA_FLAGS "${CUDA_NVCC_FLAGS} -O1 -gencode arch=compute_61,code=sm_61")
include_directories(.)
include_directories(/home/hpjeon/NVIDIA_CUDA-10.1_Samples/common/inc)
set(regsrc main.cpp)
set(cudasrc kernel.cu kernel.h)
set(extraheaders /home/hpjeon/NVIDIA_CUDA-10.1_Samples/common/inc/helper_functions.h /home/hpjeon/NVIDIA_CUDA-10.1_Samples/common/inc/helper_cuda.h)
add_executable(a.exe ${regsrc} ${cudasrc})

