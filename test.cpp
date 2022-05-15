#include "iterator.hpp"
#include "utility.hpp"

#include <iostream>
#include <typeinfo>
#include <set>
#include <vector>

int main() {
  typedef std::vector<int>::iterator VIter;
  std::vector<int> vec;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);

  VIter begin = vec.begin();
  VIter end = vec.end();

  typedef ft::reverse_iterator<VIter> VRIter;
  VRIter rbegin(end);
  VRIter rend(begin);

  std::cout << *(rbegin + 1);

  while (rend != rbegin) {
    std::cout << *rbegin << std::endl;
    rbegin++;
  }
}
