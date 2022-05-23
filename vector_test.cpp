#include "vector.hpp"
#include <vector>

#include <iostream>
#include <string>

typedef ft::vector<int>::iterator iter;

void print_content(ft::vector<int> vec) {
  std::cout << "==========" << std::endl;
  for (iter it = vec.begin(); it != vec.end(); ++it) std::cout << *it << std::endl;
  std::cout << "==========" << std::endl;
}

int main() {

  ft::vector<int> a;
  std::cout << a.size() << std::endl;
  std::cout << a.capacity() << std::endl;
  a.resize(5, 1);
  print_content(a);
  a.push_back(6);
  print_content(a);
  a.pop_back();
  print_content(a);
  a.insert(a.begin(), 9);
  print_content(a);
  a.erase(a.end() - 1);
  print_content(a);
  std::cout << "is empty: " << a.empty() << std::endl;
  a.assign(4, 5);
  print_content(a);
  typedef ft::vector<int>::iterator iter;
  iter it = a.begin();
  it++;
  std::cout << (*(++it)) << std::endl;
}
