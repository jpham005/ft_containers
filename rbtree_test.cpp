#include "red_black_tree.hpp"
#include <map>
#include <iostream>
#include <string>

template <typename T>
struct use_key {
  T operator()(T t) { return t; }
};

template <typename first, typename last>
struct use_first {
  first operator()(ft::pair<first, last> pair) { return pair.first; }
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

  int left_height = test_valid_tree<Key, Value, ExtractKey, Compare, Allocator >(node->left_);
  int right_height = test_valid_tree<Key, Value, ExtractKey, Compare, Allocator >(node->right_);

  if (left_height <= 0 || left_height != right_height) {
    return -1;
  }
  return left_height + !(node->color_ == kRBTreeColorRed);
}

#include <map>

int main() {
  rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> > tree;
  ft::pair<int, std::string> test = ft::make_pair(1, "ASDF");
  tree.insert(test);
  tree.insert(ft::make_pair(7, "ASDF"));
  tree.insert(ft::make_pair(8, "ASDF"));
  tree.insert(ft::make_pair(2, "ASDF"));
  tree.insert(ft::make_pair(4, "ASDF"));
  tree.insert(ft::make_pair(5, "ASDF"));
  tree.insert(ft::make_pair(6, "ASDF"));
  tree.insert(ft::make_pair(3, "ASDF"));
  std::cout << "result " << test_valid_tree<int, ft::pair<int, std::string>, use_first<int, std::string>, std::less<int>, std::allocator<int> >(tree.getnode()) << std::endl;
  typedef rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> >::iterator iter;
  std::cout << "====================" << std::endl;
  for (iter it = tree.begin(); it != tree.end(); it++) {
    std::cout << it->first << ", " << it->second << std::endl;
  }

  typedef rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> >::reverse_iterator riter;
//  for (riter rit = tree.rbegin(); rit != tree.rend(); rit++)
//    std::cout << rit->first << ", " << rit->second << std::endl;
    ft::iterator_traits<iter>::iterator_category
//  std::map<int, std::string> a;
//  a.insert(std::make_pair(1, "Asdf"));
//  a.insert(std::make_pair(2, "Asdzf"));
//  typedef std::map<int, std::string>::iterator oit;

//  oit oit_ = a.end();
//  (--oit_)->first;
//  std::cout << (--oit_)->first << std::endl;
}
