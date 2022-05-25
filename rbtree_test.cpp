#include "red_black_tree.hpp"
#include <map>
#include <iostream>
#include <string>

template <typename T>
struct use_key {
  T operator()(T t) { return t; }
};

template <
  typename Key, typename Value, typename ExtractKey,
  typename Compare, typename Allocator
>
void testprint(typename rbtree<Key, Value, ExtractKey, Compare, Allocator>::node *node, std::string dir) {

  if (node->color_ == kRBTreeColorBlue) { std::cout << "end"  << std::endl; return; }

  std::cout << " value: " << node->value_ << " color: ";
  if (node->color_ == kRBTreeColorBlack)
    std::cout << "black";
  else if (node->color_ == kRBTreeColorRed)
    std::cout << "red";
  else if (node->color_ == kRBTreeColorBlue)
    std::cout << "blue";
  else
    std::cout << "wrong";
  std::cout << " dir: " << dir << std::endl;
  testprint<Key, Value, ExtractKey, Compare, Allocator>(node->left_, "left");
  testprint<Key, Value, ExtractKey, Compare, Allocator>(node->right_, "right");
}

int main() {
  rbtree<int, int, use_key<int> > tree;
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);
  tree.insert(7);
  tree.insert(1);
  tree.insert(2);
  testprint<int, int, use_key<int>, std::less<int>, std::allocator<int> >(tree.getnode(), "root");
  std::cout << tree.getnode()->left_->value_ << std::endl;
}
