X86_CXX= g++
ARM_CXX= arm-linux-gnueabihf-g++
#CXX_FLAGS=-O3 -msse4.2 -g3 #-DDETAIL_PRINT
X86_CXX_FLAGS=-O0 -g3 -msse4.2
ARM_CXX_FLAGS=-O3 -g -mfpu=neon

CXX_NOVECT_FLAGS=-fno-vectorize
X86_SRC=MatrixMul/MMSSE.cpp 
ARM_SRC=MatrixMul/MMNeon.cpp

ifeq ($(DEBUG), 1)
DEBUG_FLAGS=  -DMINITEST -DDETAIL_PRINT
endif
CXX_FLAGS = ${DEBUG_FLAGS}



all: ${X86_SRC} ${ARM_SRC}
	${X86_CXX} ${X86_CXX_FLAGS} ${CXX_FLAGS} -I ../include/ -std=c++11 -fno-exceptions -fpic  \
		${X86_SRC} -shared -o libMLOptX86_64.so
	${ARM_CXX} ${ARM_CXX_FLAGS} ${CXX_FLAGS} -c -I ../include/ -std=c++11 -fno-exceptions \
		${ARM_SRC} -o $(ARM_SRC:.cpp=.o)
	arm-linux-gnueabihf-ar cr libMLOptARM.a $(ARM_SRC:.cpp=.o)

clean:
	-rm -f libMLOptX86_64.so
	-rm -f libMLOptARM.a
