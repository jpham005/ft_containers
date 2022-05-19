#include "vector.hpp"

#include <iostream>
#include <vector>

#include <ctime>

int main() {
// iterator typedefs
//  typedef ft::vector<int>::iterator iter;
// default construct && push back
    ft::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
//
//    v.clear();
//
//    for (int i = 1; i < 6; ++i) {
//      v.insert(v.begin(), i);
//    }
//
//    for (iter i = v.begin(); i != v.end(); ++i) std::cout << *i << std::endl;
//
//    for (int i = 0; i < 5; ++i) {
//      iter it = v.begin() + 2;
//      v.insert(it, 9);
//    }
//
//    for (iter i = v.begin(); i != v.end(); ++i) std::cout << *i << std::endl;
//
//    v.clear();
//
//    for (int i = 1; i < 6; ++i) {
//      iter it = v.end();
//      v.insert(it, i);
//    }
//
//    for (iter i = v.begin(); i != v.end(); ++i) std::cout << *i << std::endl;

// copy construct
//    ft::vector<int> cp(v);
//    for (iter i = cp.begin(); i != cp.end(); ++i) std::cout << *i << std::endl;}

//  typedef ft::vector<int>::reverse_iterator riter;
//  for (riter i = v.rbegin(); i != v.rend(); ++i) std::cout << *i << std::endl;


// iterator construct, earse test
//  std::vector<int> origin(v.begin(), v.end());
//  v.insert(v.begin(), origin.begin(), origin.end());
//  for (iter i = v.begin(); i != v.end(); ++i) std::cout << *i << std::endl;
//  v.erase(v.begin(), v.end() - 1);
//  for (iter i = v.begin(); i != v.end(); ++i) std::cout << *i << std::endl;

// pop back
//  v.pop_back();
//  v.pop_back();
//  v.pop_back();
//  v.pop_back();
//  v.pop_back();
//  for (iter i = v.begin(); i != v.end(); ++i) std::cout << *i << std::endl;

// resize
//  v.resize(3, 9);
//  for (iter i = v.begin(); i != v.end(); ++i) std::cout << *i << std::endl;

  ft::vector<int> cp(v);
  ft::swap(v, cp);
}
