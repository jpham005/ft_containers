#include "red_black_tree.hpp"
#include <map>
#include <iostream>
#include <string>
#include "vector.hpp"

template <typename T>
struct use_key {
  T operator()(const T& t) { return t; }
};

template <typename first, typename last>
struct use_first {
  first operator()(const ft::pair<first, last>* pair) { return pair->first; }
  const first operator()(const ft::pair<first, last>* pair) const { return pair->first; }
};

template <typename first, typename last>
struct use_std_first {
  first operator() (const std::pair<first, last>* pair) { return pair->first; }
};

template <
  typename Key, typename Value, typename ExtractKey,
  typename Compare, typename Allocator
>
void testprint(typename rbtree<Key, Value, ExtractKey, Compare, Allocator>::node *node, std::string dir) {

  if (!node->value_) { std::cout << "end"  << std::endl; return; }
  ExtractKey extractor;
  std::cout << " value: " << extractor(node->value_) << " color: ";
  if (node->color_ == kRBTreeColorBlack)
    std::cout << "black";
  else if (node->color_ == kRBTreeColorRed)
    std::cout << "red";
  else if (!node->value_)
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
  if (!node->value_)
    return 1;
  if (node->parent_->color_ == kRBTreeColorRed && node->color_ == kRBTreeColorRed)
    return -1;

  int left_height = test_valid_tree<Key, Value, ExtractKey, Compare, Allocator >(node->left_);
  int right_height = test_valid_tree<Key, Value, ExtractKey, Compare, Allocator >(node->right_);

  if (left_height <= 0 || left_height != right_height) {
    return -1;
  }
  return left_height + (node->color_ != kRBTreeColorRed);
}

template <typename first, typename last>
void printinsert(ft::pair<first, last> result) {
  if (result.second) {
    std::cout << result.second << std::endl;
    std::cout << result.first->first << std::endl;
  }
  else {
    std::cout << result.second << std::endl;
    std::cout << (++result.first)->first << std::endl;
  }
  std::cout << "==============" << std::endl;
}

#include <map>

int main() {
  rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> > tree;
  std::cout << tree.empty() << std::endl;
  ft::pair<int, std::string> test = ft::make_pair(1, "1111");
  std::cout << "==========" << std::endl;
  std::cout << "insert 1" << std::endl;
  printinsert(tree.insert(test)); // insert(1)
  printinsert(tree.insert(ft::make_pair(7, "777777")));
  printinsert(tree.insert(ft::make_pair(8, "88")));
  printinsert(tree.insert(ft::make_pair(2, "2222")));
  printinsert(tree.insert(ft::make_pair(4, "4444")));
  printinsert(tree.insert(ft::make_pair(5, "5555")));
  printinsert(tree.insert(ft::make_pair(6, "6666")));
  printinsert(tree.insert(ft::make_pair(3, "3333")));
  printinsert(tree.insert(ft::make_pair(1, "1111")));
  std::cout << "insert 2 " << (--++tree.insert(tree.end(), ft::make_pair(0, "0000")))->first << std::endl; // insert(2)
  std::cout << "is valid " << test_valid_tree<int, ft::pair<int, std::string>, use_first<int, std::string>, std::less<int>, std::allocator<int> >(tree.getnode()) << std::endl;
//  testprint<int, ft::pair<int, std::string>, use_first<int, std::string>, std::less<int>, std::allocator<int> >(tree.getnode(), "root");
  typedef rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> >::iterator iter;
  std::cout << "====================" << std::endl;
  std::cout << "iterator" << std::endl;
  for (iter it = tree.begin(); it != tree.end(); it++) {
    std::cout << it->first << ", " << it->second << std::endl;
  }
  std::cout << "====================" << std::endl;
  std::cout << "reverse_iterator" << std::endl;
  typedef rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> >::reverse_iterator riter;
  for (riter rit = tree.rbegin(); rit != tree.rend(); rit++)
    std::cout << rit->first << ", " << rit->second << std::endl;
  std::cout << "====================" << std::endl;
  std::cout << "capacity" << std::endl;
  rbtree<char, ft::pair<char, char>, use_key<char> > max;
  std::cout << tree.empty() << ", " << tree.size() << ", " << max.max_size() << std::endl;
  std::cout << "====================" << std::endl;
  std::cout << "end iterator --" << std::endl;

  std::cout << (--tree.end())->first << std::endl;
  std::cout << (--tree.rend())->first << std::endl;

  std::cout << "====================" << std::endl;
  std::cout << "insert 3" << std::endl;

  std::map<int, std::string> map;
  map.insert(std::make_pair(1, "1111"));
  map.insert(std::make_pair(2, "2222"));
  map.insert(std::make_pair(3, "3"));
  map.insert(std::make_pair(4, "4"));
  map.insert(std::make_pair(5, "5"));
  map.insert(std::make_pair(6, "6"));
  map.insert(std::make_pair(7, "7"));
  rbtree<int, std::pair<int, std::string>, use_std_first<int, std::string> > insert3;
  typedef rbtree<int, std::pair<int, std::string>, use_std_first<int, std::string> >::iterator iter3;
  insert3.insert(map.begin(), map.end());
  for (iter3 it = insert3.begin(); it != insert3.end(); ++it)
    std::cout << it->first << ", " << it->second << std::endl;

  std::cout << "====================" << std::endl;
  std::cout << "copy constructor" << std::endl;
  rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> > cp(tree);
  for (iter it = cp.begin(); it != cp.end(); it++)
    std::cout << it->first << ", " << it->second << std::endl;

  std::cout << "====================" << std::endl;
  std::cout << "const / non const comapre" << std::endl;
  const rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> > ccp(cp);
  typedef const rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> >::const_iterator citer;
//  cit->first = 2;;
  if (ccp.begin() != cp.end()) std::cout << "compared" << std::endl;

  std::cout << "====================" << std::endl;
  std::cout << "swap, assign" << std::endl;
  rbtree<int, ft::pair<int, std::string>, use_first<int, std::string> > assign;
  assign = tree;
  for (iter it = assign.begin(); it != assign.end(); it++)
    std::cout << it->first << ", " << it->second << std::endl;
  std::cout << "====================" << std::endl;
  std::cout << "clear" << std::endl;
  iter pastend = tree.end();
  tree.clear();
  tree.insert(ft::make_pair(1, "asdf"));
  for (iter it = tree.begin(); it != pastend; it++)
    std::cout << it->first << ", " << it->second << std::endl;
  std::cout << "====================" << std::endl;
  std::cout << "observers" << std::endl;
  rbtree<int, std::string, use_first<int, std::string> >::key_compare comp = tree.key_comp();
  std::cout << comp(tree.insert(ft::make_pair(3, "3333")).first->first, tree.insert(ft::make_pair(2, "2222")).first->first) << std::endl;
  std::cout << comp(tree.insert(ft::make_pair(2, "2222")).first->first, tree.insert(ft::make_pair(3, "3333")).first->first);
  std::cout << "====================" << std::endl;
  std::cout << "find" << std::endl;
  iter found = tree.find(3);
  std::cout << found->first << ", " << found->second << std::endl;
  citer cfound = ccp.find(3);
  std::cout << cfound->first << ", " << found->second << std::endl;
  std::cout << "====================" << std::endl;
  std::cout << "count" << std::endl;
  std::cout << tree.count(3) << std::endl;
  std::cout << tree.count(999) << std::endl;
  std::cout << "====================" << std::endl;
  std::cout << "bound" << std::endl;
  std::cout << ccp.lower_bound(3)->second << ", " << ccp.upper_bound(3)->second << std::endl;
  for (iter it = cp.equal_range(3).first; it != cp.equal_range(3).second; it++)
    std::cout << it->first << ", " << it->second << std::endl;

  std::cout << "====================" << std::endl;
  std::cout << "erase" << std::endl;
  cp.erase(cp.begin());
    testprint<int, ft::pair<int, std::string>, use_first<int, std::string>, std::less<int>, std::allocator<int> >(cp.getnode(), "root");
  iter begin = cp.begin();
  ++begin;
  ++begin;
  for (iter it = cp.begin(); it != cp.end(); it++)
    std::cout << it->first << ", " << it->second << std::endl;
//  oit oit_ = a.end();
//  (--oit_)->first;
//  std::cout << (--oit_)->first << std::endl;
//  testprint<int, ft::pair<int, std::string>, use_first<int, std::string>, std::less<int>, std::allocator<int> >(tree.getnode(), "root");


}
