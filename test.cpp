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

char test(char a);
int test2(int a);

int main() {
  std::vector<int> origin;
  origin.push_back(1);
  origin.push_back(2);
  origin.push_back(3);
  origin.push_back(4);
  ft::vector<int> v(4, 4);
  v.assign(origin.begin(), origin.end());
  typedef ft::vector<int>::iterator iter;
  iter i = v.begin();
  v.insert(i, 10);
  for (iter a = v.begin(); a != v.end(); ++a)
    std::cout << *a << std::endl;

  ft::vector<int> cp = v;

  for (iter b = cp.begin(); b != cp.end(); ++b)
    std::cout << *b << std::endl;

//  for (std::size_t i = 0; i < 5; ++i) v[i] = i;
//
//  std::cout << v[2] << std::endl;
//  std::cout << v.at(2) << std::endl;
//  std::cout << v.front() << std::endl;
//  std::cout << v.back() << std::endl;
//  std::cout << *(v.data()) << std::endl;
//
//  std::vector<int> vec;
//  for (int i = 0; i < 10; ++i) {
//    vec.push_back(i + 10);
//  }
//
//  ft::vector<int> cp = v;
//
//  v.assign(vec.begin(), vec.end());
//  typedef ft::vector<int>::iterator iter;
//
//  for (iter i = v.begin(); i != v.end(); ++i)
//    std::cout << *i << std::endl;
//
//  for (iter i = cp.begin(); i != cp.end(); ++i)
//    std::cout << *i << std::endl;
//
//  //  v.assign(1, 1); //TODO
//  v.assign(static_cast<std::size_t>(1), 1);
//  for (iter i = v.begin(); i != v.end(); ++i)
//    std::cout << *i << std::endl;


}
