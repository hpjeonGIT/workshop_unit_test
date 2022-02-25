.SUFFIXES: .o .cxx
CXX = g++
FLAGS = -O3 -g -march=native
LIB =
FOMP = -fopenmp
INCLUDE =
OBJ = main.o fma.o
TARGET = simd.exe
${TARGET}: ${OBJ}
	${CXX} ${FLAGS} ${FOMP} -o ${TARGET} ${OBJ} ${LIB}
.cxx.o:
	${CXX} ${FLAGS} ${FOMP} -c $<
clean:
	rm ${OBJ} ${TARGET}
docs:
	@doxygen ./Doxyfile
