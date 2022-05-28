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

template <
  typename Key, typename Value, typename ExtractKey,
  typename Compare, typename Allocator
>
int test_valid_tree(typename rbtree<Key, Value, ExtractKey, Compare, Allocator>::node *node) {
  if (node->color_ == kRBTreeColorBlue)
    return 1;
  if (node->parent_->color_ == kRBTreeColorRed && node->color_ == kRBTreeColorRed)
    return -1;

  int left_height = test_valid_tree<int, int, use_key<int>, std::less<int>, std::allocator<int> >(node->left_);
  int right_height = test_valid_tree<int, int, use_key<int>, std::less<int>, std::allocator<int> >(node->right_);

  if (left_height <= 0 || left_height != right_height) {
    return -1;
  }
  return left_height + !(node->color_ == kRBTreeColorRed);
}

#include <map>

int main() {
  rbtree<int, int, use_key<int> > tree;
  tree.insert(1);
  tree.insert(7);
  tree.insert(8);
  tree.insert(2);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);
  tree.insert(3);
  std::cout << "result " << test_valid_tree<int, int, use_key<int>, std::less<int>, std::allocator<int> >(tree.getnode()) << std::endl;
  typedef rbtree<int, int, use_key<int> >::iterator iter;
  std::cout << "====================" << std::endl;
  for (iter it = tree.begin(); it != tree.end(); it++) std::cout << *it << std::endl;
}
