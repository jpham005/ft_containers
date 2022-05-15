#include "iterator.hpp"
#include "utility.hpp"

#include <iostream>
#include <typeinfo>

class test {
  public:
    test() {}
    int* geta() { return a; }

  private:
    int* a;
};

int main() {
  test test;
  std::cout << test.geta();
}
