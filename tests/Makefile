X86_CXX= clang++-3.7
#X86_CXX= g++ -ftree-vectorizer-verbose=1
ARM_CXX= arm-linux-gnueabihf-g++ #-ftree-vectorizer-verbose=1
CXX_AUTOVEC_FLAGS=-O3 -Rpass=loop-vectorize
CXX_DEBUG_FLAGS=-O0 -g3
X86_EXTRA_FLAGS=../lib/libMLOptX86_64.so
ARM_LINKER_FLAGS= -L ../lib/ -lMLOptARM
CXX_NOVECT_FLAGS= #-fno-vectorize
COMMON_SRC = MMScalar_test.cpp
X86_SRC= ${COMMON_SRC} MMSSE_test.cpp
ARM_SRC = ${COMMON_SRC} MMNeon_test.cpp
ifeq ($(DEBUG), 1)
DEBUG_FLAGS=  -DMINITEST -DDETAIL_PRINT
endif
CXX_FLAGS = ${DEBUG_FLAGS}


%.noautovec.x86.exe : %.cpp
	${X86_CXX} ${CXX_FLAGS} ${CXX_NOVECT_FLAGS} ${X86_EXTRA_FLAGS} -I ../include/ -std=c++11 -fno-exceptions $< -o $@ 2>&1 
%.autovec.x86.exe : %.cpp
	${X86_CXX} ${CXX_FLAGS} ${CXX_AUTOVEC_FLAGS} ${X86_EXTRA_FLAGS} -I ../include/ -std=c++11 -fno-exceptions $< -o $@ 2>&1 

%.autovec.arm.exe : %.cpp
		${ARM_CXX} ${CXX_FLAGS} ${CXX_AUTOVEC_FLAGS}  -I ../include/ -std=c++11 -fno-exceptions -static  $< -o $@ ${ARM_LINKER_FLAGS} 2>&1  

all: $(X86_SRC:.cpp=.autovec.x86.exe) $(X86_SRC:.cpp=.noautovec.x86.exe) \
	$(ARM_SRC:.cpp=.autovec.arm.exe)

test:
	$(foreach exeb, $(X86_SRC:.cpp=.autovec.x86.exe), ./$(exeb))
	$(foreach exeb, $(X86_SRC:.cpp=.noautovec.x86.exe), ./$(exeb))
	$(foreach exeb, $(ARM_SRC:.cpp=.autovec.arm.exe), qemu-arm ./$(exeb))

clean:
	-rm -f $(X86_SRC:.cpp=.autovec.x86.exe) $(X86_SRC:.cpp=.noautovec.x86.exe)
	-rm -f $(ARM_SRC:.cpp=.autovec.arm.exe)
	-rm -f make.log
