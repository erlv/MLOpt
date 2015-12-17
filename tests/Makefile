CXX= clang++-3.7
#CXX_FLAGS=-O3 -Rpass=loop-vectorize
CXX_FLAGS=-O0 -g3
EXTRA_FLAGS=../lib/libMLOpt.so
CXX_NOVECT_FLAGS=-fno-vectorize
SRC= MMScalar_test.cpp MMSSE_test.cpp

%.noautovec.exe : %.cpp
	${CXX} ${CXX_FLAGS} ${CXX_NOVECT_FLAGS} ${EXTRA_FLAGS} -I ../include/ -std=c++11 -fno-exceptions $< -o $@
%.autovec.exe : %.cpp
	${CXX} ${CXX_FLAGS} ${EXTRA_FLAGS} -I ../include/ -std=c++11 -fno-exceptions $< -o $@

all: $(SRC:.cpp=.autovec.exe) $(SRC:.cpp=.noautovec.exe)


clean:
	-rm -f $(SRC:.cpp=.autovec.exe) $(SRC:.cpp=.noautovec.exe)
