#include <iostream>

#include "vector_test.hpp"
#include <vector>
int main() {
  std::vector<int> a;
  if (vector_test())
    std::cout << "success" << std::endl;
}
