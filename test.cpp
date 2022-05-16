#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#include <iostream>
#include <typeinfo>
#include <set>
#include <vector>
#include <type_traits>
#include <string>

template <typename T>
void test(int a, const T& b) {
  std::cout << "t: " << a << b << std::endl;
}

template <typename Iter>
void test(Iter i1, std::enable_if< ft::is_input_iterator_tag< std::iterator_traits<Iter>::iterator_category >::value , Iter>::type i2 )
  std::cout << "iterator" << std::endl;
}

int main() {
  test(1, 1);
}
