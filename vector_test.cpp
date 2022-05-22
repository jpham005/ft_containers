//#include "vector.hpp"
//#include <vector>
//
//#include <iostream>
//#include <string>
//
//int main() {
//  ft::vector<std::string> a;
////  a.size();
////  a.capacity();
////  a.resize(5, 1);
////  a.push_back(6);
////  a.pop_back();
////  a.insert(a.begin(), 1);
////  a.erase(a.end() - 1);
////  a.empty();
////  a.assign(4, 5);
//  a.push_back("asdf");
//  a.push_back("1234");
//  a.push_back("qplsl");
//  typedef ft::vector<std::string>::iterator iter;
//  iter it = a.begin();
//  it++;
//  std::cout << (*(++it)).capacity() << std::endl;
//}
// #include <stdlib.h>
// #include "test.hpp"

#include <iostream>
#include <string>
// #include <vector>
#include "vector.hpp"
#define NS ft

using std::string;

int main() {
  typedef NS::vector<string> vecStr;
  vecStr                     vec(1, "4");

  vec.push_back("abababab");
  vec.push_back("123123123123123123123");
  vec.push_back("1234123412341234123412341234123412341234124");

  std::cout << vec.begin()->c_str() << '\n';
  std::cout << (++(vec.begin()))->c_str() << '\n';

  vecStr::const_iterator         cit  = --(vec.end());
  vecStr::const_reverse_iterator crit = vec.rbegin();

  std::cout << (cit->capacity() == (crit++)->capacity()) << '\n';
  std::cout << ((*(--cit)).capacity() == (*crit).capacity()) << '\n';
  std::cout << (cit->get_allocator() == (*crit).get_allocator())
            << '\n';
  std::cout << *cit << *crit << '\n';
  return (0);
}
