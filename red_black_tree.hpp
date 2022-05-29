#pragma once
#include <iostream> //TODO
#include <functional>

#include "iterator.hpp"
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

template <typename Value>
struct rbtree_node {
  Value         value_;
  rbtree_node*  right_;
  rbtree_node*  left_;
  rbtree_node*  parent_;
  char          color_;
};

template <typename T, typename Pointer, typename Reference>
class rbtree_iterator {
private:
  template <typename Key, typename Value, typename ExtractKey, typename Compare, typename Allocator>
  friend class rbtree;
  typedef rbtree_iterator<T, T*, T&>              iterator;
  typedef rbtree_iterator<T, const T*, const T&>  const_iteraotr;
  typedef rbtree_node<T>                          node_type;

  node_type* get_next_node(node_type* curr) {
    if (curr->right_->color_ != kRBTreeColorBlue) {
      curr = curr->right_;
      while (curr->parent_->color_ != kRBTreeColorBlue && curr->left_->color_ != kRBTreeColorBlue) curr = curr->left_;
      return curr;
    }

    while (curr->parent_->color_ != kRBTreeColorBlue && curr != curr->parent_->left_) curr = curr->parent_;
    return curr->parent_;
  }

  node_type* get_prev_node(node_type* curr) {
    if (curr->left_->color_ != kRBTreeColorBlue) {
      curr = curr->left_;
      while (curr->right_->color_ != kRBTreeColorBlue) curr = curr->right_;
      return curr;
    }

    while (curr->parent_->color_ != kRBTreeColorBlue && curr != curr->parent_->right_) curr = curr->parent_;
    return curr->parent_;
  }

public:
  typedef std::bidirectional_iterator_tag         iterator_category;
  typedef ptrdiff_t                               difference_tyoe;
  typedef T                                       value_type;
  typedef Reference                               reference;
  typedef Pointer                                 pointer;

  node_type* node_;

  rbtree_iterator() : node_(NULL) {};
  explicit rbtree_iterator(node_type* node) : node_(node) {}
  rbtree_iterator(const iterator& other) : node_(other.node_) {}
  rbtree_iterator& operator=(const iterator& other) { this->node_ = other.node_; return *this; }

  reference operator*() const { return this->node_->value_; }
  pointer operator->() const { return &(this->node_->value_); }

  rbtree_iterator& operator++() { this->node_ = get_next_node(this->node_); return *this; }
  rbtree_iterator operator++(int) {
    node_type* temp = this->node_;
    this->node_ = get_next_node(this->node_);
    return iterator(temp);
  }

  rbtree_iterator& operator--() { this->node_ = get_prev_node(this->node_); return *this; }
  rbtree_iterator operator--(int) {
    node_type* temp = this->node_;
    this->node_ = get_prev_node(this->node_);
    return iterator(temp);
  }

  friend bool operator==(const rbtree_iterator& it1, const rbtree_iterator& it2) {
    return it1.node_ == it2.node_;
  }

  friend bool operator!=(const rbtree_iterator& it1, const rbtree_iterator& it2) {
    return !(it1 == it2);
  }
};

template <
  typename Key, typename Value, typename ExtractKey,
  typename Compare = std::less<Key>, typename Allocator = std::allocator<Value>
>
class rbtree {
public:
  typedef Key                                                         key_type;
  typedef Value                                                       value_type;
  typedef std::size_t                                                 size_type;
  typedef std::ptrdiff_t                                              difference_type;
  typedef Compare                                                     key_compare;
  typedef Allocator                                                   allocator_type;
  typedef value_type&                                                 reference;
  typedef const value_type&                                           const_reference;
  typedef typename Allocator::pointer                                 pointer;
  typedef typename Allocator::const_pointer                           const_pointer;
  typedef rbtree_node<value_type>                                     node;
  typedef rbtree_iterator<value_type, pointer, reference>             iterator;
  typedef rbtree_iterator<value_type, const_pointer, const_reference> const_iterator;
  typedef ft::reverse_iterator<iterator>                              reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;
  typedef ExtractKey                                                  extract;

private:
  extract     extractor_;
  key_compare comparator_;
  node*       nil_;
  node*       root_;
  node*       anchor_;
  size_type   size_;

public:
  node* getnode() { return root_; }
  rbtree() : nil_(init_nil()), root_(this->nil_), anchor_(init_nil()), size_(0) {}
//  explicit rbtree(const key_compare& comp, const allocator_type& alloc = allocator_type());
//  template <typename InputIt>
//  rbtree(InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) {}
//  rbtree(const rbtree& other) {}

  void insert(const_reference value) {
    if (this->root_->color_ == kRBTreeColorBlue) {
      this->root_ = init_node(value);
      this->root_->color_ = kRBTreeColorBlack;
      this->root_->left_ = this->anchor_;
      this->root_->right_ = this->anchor_;
      this->root_->parent_ = this->anchor_;
      this->anchor_->left_ = this->root_;
      this->anchor_->right_ = this->root_;
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

    ++(this->size_);
    if (this->anchor_->left_->left_->color_ != kRBTreeColorBlue) {
      this->anchor_->left_ = this->anchor_->left_->left_;
      this->anchor_->left_->left_ = this->anchor_;
    }
    if (this->anchor_->right_->right_->color_ != kRBTreeColorBlue) {
      this->anchor_->right_ = this->anchor_->right_->right_;
      this->anchor_->right_->right_ = this->anchor_;
    }
  }
//  ft::pair<iterator, bool> insert(const_reference value) {
//
//  }
//  iterator insert(iterator hint, const_reference value) {}
//  template <typename InputIt>
//  void insert(InputIt first, InputIt last) {}

  /*
  ======================================================================================================================
   iterator
  ======================================================================================================================
   */

  iterator begin() throw() { return iterator(this->anchor_->left_); }

  const_iterator begin() const throw() { return const_iterator(this->anchor_->left_); }

  iterator end() throw() { return iterator(this->anchor_); }

  const_iterator end() const throw() { return const_iterator(this->anchor_); }

  reverse_iterator rbegin() throw() { return reverse_iterator(this->anchor_->right_); }

  const_reverse_iterator rbegin() const throw() { return reverse_iterator(this->anchor_->right_); }

  iterator rend() throw() { return reverse_iterator(this->anchor_); }

  const_iterator rend() const throw() { return const_reverse_iterator(this->anchor_); }

private:
  node* init_node(const_reference value) {
    node* ret = new node;
    ret->parent_ = nil_;
    ret->left_ = nil_;
    ret->right_ = nil_;
    ret->value_ = value;
    ret->color_ = kRBTreeColorRed;
    return ret;
  }

  node* init_nil() {
    node* ret = new node;
    ret->color_ = kRBTreeColorBlue;
    return ret;
  }

  bool compare(node* n1, node* n2) { return comparator_(extractor_(n1->value_), extractor_(n2->value_)); }

  void left_rotate(node* x) {
    node* y = x->right_;

    x->right_ = y->left_;
    if (y->left_->color_ != kRBTreeColorBlue) y->left_->parent_ = x;
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
    if (y->right_->color_ != kRBTreeColorBlue) y->right_->parent_ = x;
    y->parent_ = x->parent_;
    if (x->parent_->color_ == kRBTreeColorBlue) this->root_ = y;
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
        } else {
          if (z == z->parent_->right_) {
            z = z->parent_;
            left_rotate(z);
          }
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
        } else {
          if (z == z->parent_->left_) {
            z = z->parent_;
            right_rotate(z);
          }
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
