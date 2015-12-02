CXX= clang++-3.7
CXX_FLAGS=-O3
#CXX_FLAGS=-O0 -g3

CXX_NOVECT_FLAGS=-fno-vectorize
SRC= MMScalar_test.cpp

%.exe : %.cpp
	${CXX} ${CXX_FLAGS} ${CXX_NOVECT_FLAGS} -I ../include/ -std=c++11 -fno-exceptions $< -o $@
all: $(SRC:.cpp=.exe)


clean:
	-rm -f $(SRC:.cpp=.exe)
