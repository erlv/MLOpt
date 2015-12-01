all:
	clang++ main.cpp -o main.exe -std=c++11 -fno-exceptions -O0 -g3

clean:
	-rm -f main.exe
