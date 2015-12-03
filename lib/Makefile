CXX= clang++-3.7
CXX_FLAGS=-O3 -Rpass=loop-vectorize
#CXX_FLAGS=-O0 -g3

CXX_NOVECT_FLAGS=-fno-vectorize
SRC= MatrixMul/MMSSE.cpp

all: ${SRC}
	${CXX} ${XCC_FLAGS} -I ../include/ -std=c++11 -fno-exceptions -fpic ${SRC} -shared -o libMLOpt.so
