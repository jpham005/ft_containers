//#include "red_black_tree.hpp"
#include <map>
#include <iostream>
#include <string>

int main() {
//  rbtree<int, std::string, int, > tree;
  std::map<int, std::string> m;
  m.insert(std::make_pair(3, "ASDF"));
  m.insert(std::make_pair(2, "ASDF"));
  m.insert(std::make_pair(2, "ASDF"));
  m.insert(std::make_pair(4, "ASDF"));
  m.insert(std::make_pair(2, "ASDF"));
  m.insert(std::make_pair(2, "ASDF"));
  m.insert(std::make_pair(2, "ASDF"));
  typedef std::map<int, std::string>::iterator iter;
  for (iter it = m.begin(); it != m.end(); it++)
    std::cout << (*it).first << std::endl;
  std::cout << m.size() << std::endl;
}
