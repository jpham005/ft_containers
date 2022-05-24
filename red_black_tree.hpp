#pragma once

#include <functional>

#include "utility.hpp"

enum RBTreeColor {
  kRBTreeColorRed,
  kRBTreeColorBlack
};

enum RBTreeSide {
  kRBTreeSideLeft,
  kRBTreeSideRight
};

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

template <
  typename Key, typename Value, typename ExtractKey,
  typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>
>
class rbtree {
public:
  typedef Key                               key_type;
  typedef Value                             value_type;
  typedef std::size_t                       size_type;
  typedef std::ptrdiff_t                    difference_type;
  typedef Compare                           key_compare;
  typedef Allocator                         allocator_type;
  typedef value_type&                       reference;
  typedef const value_type&                 const_reference;
  typedef typename Allocator::pointer       pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef rbtree_node<value_type>           node;
  typedef pointer                           iterator; // TODO
  typedef ExtractKey                        extract;

protected:
  node*     root_;
  size_type size;

public:
  rbtree() : root_(NULL), size(0) {}
//  explicit rbtree(const key_compare& comp, const allocator_type& alloc = allocator_type());
//  template <typename InputIt>
//  rbtree(InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) {}
//  rbtree(const rbtree& other) {}

  void insert(const_reference value) {
    if (!this->root_) {
      this->root_ = init_node(value);
      return;
    }

    node* x = this->root_;
    node* y = NULL;
    node* z = init_node(value);
    while (x) {
      y = x;
      if (compare(z, x)) x = x->left_;
      else if (compare(x, z)) x = x->right_;
      else return;
    }

    z->parent_ = y;
    if (!y) this->root_ = z;
    else if (compare(z, y))
  }
//  ft::pair<iterator, bool> insert(const_reference value) {
//
//  }
//  iterator insert(iterator hint, const_reference value) {}
//  template <typename InputIt>
//  void insert(InputIt first, InputIt last) {}

private:
  node* init_node(const_reference value) {
    node* ret = new node;
    ret->parent_ = NULL;
    ret->left_ = NULL;
    ret->right_ = NULL;
    ret->value = value;
  }

  bool compare(node* n1, node* n2) { return key_compare(extract(n1->value), extract(n2->value)); }

  void left_rotate(node* x) {
    node* y = x->right_;

    x->right_ = y->left_;
    if (y->left_) y->left_->parent_ = x;
    y->parent_ = x->parent_;
    if (!x->parent_) this->root_ = y;
    else if (x == x->parent_->left_) x->parent_->left_ = y;
    else x->parent_->right_ = y;
    y->left = x;
    x->parent_ = y;
  }

  void right_rotate(node* x) {
    node* y = x->left_;

    x->left_ = y->right_;
    if (y->right_) y->right_->parent_ = x;
    y->parent_ = x->parent_;
    if (!x->parent_) this->root_ = y;
    else if (x == x->parent_->left_) x->parent_->left_ = y;
    else x->parent_->right_ = y;
    y->right = x;
    x->parent_ = y;
  }
};

// iterators
// capacity: empty, size, max_size
// modifiers: clear, insert, erase, swap
// lookup: count, find, equal_range, lower_bound, upper_bound
// observers: key_comp, value_comp
