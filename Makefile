CXX_FLAGS=-O3
#CXX_FLAGS=-O0 -g3

CXX_NOVECT_FLAGS=-fno-vectorize

all:
	clang++ main.cpp -o main.exe -std=c++11 -fno-exceptions ${CXX_FLAGS} ${CXX_NOVECT_FLAGS}

test:
	./main.exe

clean:
	-rm -f main.exe
