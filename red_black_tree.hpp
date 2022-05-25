#pragma once

#include <functional>

#include "utility.hpp"

enum RBTreeColor {
  kRBTreeColorRed,
  kRBTreeColorBlack,
  kRBTreeColorBlue
};

enum RBTreeSide {
  kRBTreeSideLeft,
  kRBTreeSideRight
};

template <typename Value> // seperate typedef => can use node without <T>
struct rbtree_node {
  Value         value_;
  rbtree_node*  right_;
  rbtree_node*  left_;
  rbtree_node*  parent_;
  char          color_;
}; // set: user val, map: pair

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
  node* getnode() { return root_; }
  rbtree() : root_(NULL), size(0), nill_(init_nill()) {}
//  explicit rbtree(const key_compare& comp, const allocator_type& alloc = allocator_type());
//  template <typename InputIt>
//  rbtree(InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) {}
//  rbtree(const rbtree& other) {}

  void insert(const_reference value) {
    if (!this->root_) {
      this->root_ = init_node(value);
      this->root_->color_ = kRBTreeColorBlack;
      return;
    }

    node* x = this->root_;
    node* y = NULL;
    node* z = init_node(value);
    while (x->color_ != kRBTreeColorBlue) {
      y = x;
      if (compare(z, x)) x = x->left_;
      else if (compare(x, z)) x = x->right_;
      else return;
    }

    z->parent_ = y;
    if (!y) this->root_ = z;
    else if (compare(z, y)) y->left_ = z;
    else y->right_ = z;

    insert_fixup(z);
  }
//  ft::pair<iterator, bool> insert(const_reference value) {
//
//  }
//  iterator insert(iterator hint, const_reference value) {}
//  template <typename InputIt>
//  void insert(InputIt first, InputIt last) {}

private:
  extract     extractor_;
  key_compare comparator_;
  node*       nill_;

  node* init_node(const_reference value) {
    node* ret = new node;
    ret->parent_ = nill_;
    ret->left_ = nill_;
    ret->right_ = nill_;
    ret->value_ = value;
    ret->color_ = kRBTreeColorRed;
    return ret;
  }

  node* init_nill() {
    node* ret = new node;
    ret->color_ = kRBTreeColorBlue;
    return ret;
  }

  bool compare(node* n1, node* n2) { return comparator_(extractor_(n1->value_), extractor_(n2->value_)); }

  void left_rotate(node* x) {
    node* y = x->right_;

    x->right_ = y->left_;
    if (y->left_) y->left_->parent_ = x;
    y->parent_ = x->parent_;
    if (x->parent_->color_ == kRBTreeColorBlue) this->root_ = y;
    else if (x == x->parent_->left_) x->parent_->left_ = y;
    else x->parent_->right_ = y;
    y->left_ = x;
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
    y->right_ = x;
    x->parent_ = y;
  }

  void insert_fixup(node* z) {
    node* y;

    while (z->parent_->color_ == kRBTreeColorRed) {
      if (z->parent_ == z->parent_->parent_->left_) {
        y = z->parent_->parent_->right_;
        if (y->color_ == kRBTreeColorRed) {
          z->parent_->color_ = kRBTreeColorBlack;
          y->color_ = kRBTreeColorBlack;
          z->parent_->parent_->color_ = kRBTreeColorRed;
          z = z->parent_->parent_;
        }
        else if (z == z->parent_->right_) {
          z = z->parent_;
          left_rotate(z);
          z->parent_->color_ = kRBTreeColorBlack;
          z->parent_->parent_->color_ = kRBTreeColorRed;
          right_rotate(z->parent_->parent_);
        }
        if (z == z->parent_->left_) {
          z->parent_->color_ = kRBTreeColorBlack;
          z->parent_->parent_->color_ = kRBTreeColorRed;
          right_rotate(z->parent_->parent_);
        }
      }
      else {
        y = z->parent_->parent_->left_;
        if (y->color_ == kRBTreeColorRed) {
          z->parent_->color_ = kRBTreeColorBlack;
          y->color_ = kRBTreeColorBlack;
          z->parent_->parent_->color_ = kRBTreeColorRed;
          z = z->parent_->parent_;
        }
        else if (z == z->parent_->left_) {
          z = z->parent_;
          right_rotate(z);
          z->parent_->color_ = kRBTreeColorBlack;
          z->parent_->parent_->color_ = kRBTreeColorRed;
          left_rotate(z->parent_->parent_);
        }
        if (z == z->parent_->right_) {
          z->parent_->color_ = kRBTreeColorBlack;
          z->parent_->parent_->color_ = kRBTreeColorRed;
          left_rotate(z->parent_->parent_);
        }
      }
    }
    this->root_->color_ = kRBTreeColorBlack;
  }
};

// iterators
// capacity: empty, size, max_size
// modifiers: clear, insert, erase, swap
// lookup: count, find, equal_range, lower_bound, upper_bound
// observers: key_comp, value_comp
