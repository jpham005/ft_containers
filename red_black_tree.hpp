#pragma once

struct rbtree_node_base {
  typedef rbtree_node_base this_type;

  this_type*  right_;
  this_type*  left_;
  this_type*  parent_;
  char        color_;
};

template <typename Value> // seperate typedef => can use node without <T>
struct rbtree_node : public rbtree_node_base { Value value; }; // set: user val, map: pair

template <typename T, typename Pointer, typename Reference>
struct rbtree_iterator {
  typedef rbtree_iterator<T, Pointer, Reference>  this_type;
  typedef rbtree_iterator<T, T*, T&>              iterator;
};

template <typename Key, typename Value, typename Compare, typename Allocater, typename ExtractKey>
class rbtree {

};

// iterators
// capacity: empty, size, max_size
// modifiers: clear, insert, erase, swap
// lookup: count, find, equal_range, lower_bound, upper_bound
// observers: key_comp, value_comp
