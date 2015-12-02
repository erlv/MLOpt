#include <iostream>
#include <string>
#include <cstdint>
#include "MMScalar.hpp"

using namespace std;

class MMInt8SSE: public MMScalar<int8_t> {
private:
  string _name;
public:
  MMInt8SSE (int M, int N, int K, string postfix)
    :MMScalar<int8_t>(M,N,K,postfix) {
      _name = "MMInt8SSE<" + postfix + ">";
  }
  void mmSSE(TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K);
};
