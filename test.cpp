#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "vector.hpp"

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
void test(Iter i1, typename ft::enable_if<ft::iterator_traits<Iter>::iterator_category>::type i2) {
  std::cout << "iterator" << std::endl;
  (void)i1;
  (void)i2;
}

int main() {
  ft::vector<int> v(static_cast<std::size_t>(5), 4);

  typedef ft::vector<int>::iterator iter;
  for (iter i = v.begin(); i != v.end(); i++) {
    std::cout << *i << std::endl;
  }

  typedef ft::vector<int>::reverse_iterator riter;
//  for (riter i = v.rbegin(); i != v.rend(); ++i) {
//    std::cout << *i << std::endl;
//  }
  riter i = v.rbegin();
  std::cout << *i << std::endl;

  std::cout << "===============" << std::endl;

  const ft::vector<int>& cp = const_cast<const ft::vector<int>& >(v);
  typedef ft::vector<int>::const_reverse_iterator criter;

  criter cri = cp.rbegin();
  std::cout << *cri << std::endl;

  if (cri != i)
    return 0;

}
