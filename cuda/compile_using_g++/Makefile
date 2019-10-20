
CUDA_INC= -I.
CUDA_LIB=-L/usr/local/cuda/lib64 -lcuda -lcudart

a.exe: kernel.o main.o
	g++ -o a.exe main.o kernel.o ${CUDA_LIB} -I.

kernel.o: kernel.cu
	nvcc -I. -arch=sm_61 -o $@ -c $<

main.o: main.cpp
	g++ -I. -o $@ -c $<

clean:
	rm -rf main.o kernel.o a.exe
