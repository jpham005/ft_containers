#include "red_black_tree.hpp"
#include <map>
#include <iostream>
#include <string>

template <typename T>
struct use_key {
  T operator()(T t) { return t; }
};

int main() {
  rbtree<int, int, use_key<int> > tree;
  tree.insert(3);
  tree.insert(4);
  std::cout << tree.getnode()->right_->value;
//  tree.insert(5);
}
