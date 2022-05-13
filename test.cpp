#include "iterator.hpp"
#include "utility.hpp"

#include <iostream>
#include <typeinfo>

int main() {
  typedef ft::iterator_traits<int*> traits;
  if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
    std::cout << "int* is a random-access iterator" << std::endl;
}
