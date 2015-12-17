CXX= g++
#CXX_FLAGS=-O3 -msse4.2 -g3 #-DDETAIL_PRINT
CXX_FLAGS=-O0 -g3 -msse4.2

CXX_NOVECT_FLAGS=-fno-vectorize
SRC= MatrixMul/MMSSE.cpp

all: ${SRC}
	${CXX} ${CXX_FLAGS} -I ../include/ -std=c++11 -fno-exceptions -fpic ${SRC} -shared -o libMLOpt.so
