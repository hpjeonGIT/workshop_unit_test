
CUDA_INC= -I. -I/home/hpjeon/NVIDIA_CUDA-10.1_Samples/common/inc
CUDA_LIB=-L/usr/local/cuda/lib64 -lcuda -lcudart

a.exe: kernel.o main.o
	g++ -o a.exe main.o kernel.o ${CUDA_LIB} ${CUDA_INC}

kernel.o: kernel.cu
	nvcc ${CUDA_INC} -arch=sm_61 -o $@ -c $<

main.o: main.cpp
	g++  ${CUDA_INC}  -o $@ -c $<

clean:
	rm -rf main.o kernel.o a.exe
