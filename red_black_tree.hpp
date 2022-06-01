#pragma once
#include <iostream> //TODO
#include <functional>

#include "iterator.hpp"
#include "utility.hpp"

enum RBTreeColor {
  kRBTreeColorRed,
  kRBTreeColorBlack
};

template <typename Value>
struct rbtree_node {
  Value*        value_;
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
  typedef rbtree_iterator<T, const T*, const T&>  const_iteraotr; // TODO
  typedef rbtree_node<T>                          node_type;

  node_type* get_next_node(node_type* curr) {
    if (curr->right_->value_) {
      curr = curr->right_;
      while (curr->parent_->value_ && curr->left_->value_) curr = curr->left_;
      return curr;
    }

    while (curr->parent_->value_ && curr != curr->parent_->left_) curr = curr->parent_;
    return curr->parent_;
  }

  node_type* get_prev_node(node_type* curr) {
    if (curr->left_->value_) {
      curr = curr->left_;
      while (curr->right_->value_) curr = curr->right_;
      return curr;
    }

    while (curr->parent_->value_ && curr != curr->parent_->right_) curr = curr->parent_;
    return curr->parent_;
  }
  node_type* node_;

public:
  typedef std::bidirectional_iterator_tag         iterator_category;
  typedef ptrdiff_t                               difference_type;
  typedef T                                       value_type;
  typedef Reference                               reference;
  typedef Pointer                                 pointer;

  rbtree_iterator() : node_(NULL) {};
  explicit rbtree_iterator(node_type* node) : node_(node) {}
  rbtree_iterator(const iterator& other) : node_(other.node_) {}
  rbtree_iterator& operator=(const iterator& other) { this->node_ = other.node_; return *this; }

  reference operator*() const { return *(this->node_->value_); }
  pointer operator->() const { return this->node_->value_; }

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
  allocator_type  allocator_;
  extract         extractor_;
  key_compare     comparator_;
  node*           nil_;
  node*           root_;
  node*           anchor_;
  size_type       size_;

public:
  node* getnode() { return root_; } // TODO
  rbtree()
    : allocator_(allocator_type()), nil_(init_nil()), root_(this->nil_), anchor_(init_nil()), size_(0) {}
//  explicit rbtree(const key_compare& comp, const allocator_type& alloc = allocator_type());
//  template <typename InputIt>
//  rbtree(InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) {}
//  rbtree(const rbtree& other) {}


  /*
  ======================================================================================================================
   iterator
  ======================================================================================================================
   */

  iterator begin() throw() { return iterator(this->anchor_->right_); }

  const_iterator begin() const throw() { return const_iterator(this->anchor_->right_); }

  iterator end() throw() { return iterator(this->anchor_); }

  const_iterator end() const throw() { return const_iterator(this->anchor_); }

  reverse_iterator rbegin() throw() { return reverse_iterator(iterator(this->anchor_)); }

  const_reverse_iterator rbegin() const throw() { return reverse_iterator(const_iterator(this->anchor_)); }

  reverse_iterator rend() throw() { return reverse_iterator(iterator(this->anchor_->right_)); }

  const_reverse_iterator rend() const throw() { return const_reverse_iterator(const_iterator(this->right_)); }

  /*
  ======================================================================================================================
   capacity
  ======================================================================================================================
  */

  bool empty() const throw() { return this->size_ == 0; }

  size_type size() const throw() { return this->size_; }

  size_type max_size() const throw() { // TODO
    return std::numeric_limits<difference_type>::max(), this->allocator_.max_size();
  }

  /*
  ======================================================================================================================
   modifier
  ======================================================================================================================
  */

  ft::pair<iterator, bool> insert(const_reference value) {
    if (!this->size_) {
      insert_root(value);
      return ft::make_pair(iterator(this->root_), true);
    }

    node* x = this->root_;
    node* y = NULL;
    node* z = init_node(value);
    while (x->value_) {
      y = x;
      if (compare(z, x)) x = x->left_;
      else if (compare(x, z)) x = x->right_;
      else return ft::make_pair(iterator(x), false);
    }

    z->parent_ = y;
    if (compare(z, y)) y->left_ = z;
    else y->right_ = z;

    insert_fixup(z);

    ++(this->size_);
    update_anchor();

    return ft::make_pair(iterator(z), true);
  }

  iterator insert(iterator hint, const_reference value) {
    if (!this->size_) {
      insert_root(value);
      return iterator(this->root_);
    }

    node* x = hint.node_;
    if (x == this->anchor_)
      x = x->right_;
    node* y = NULL;
    node* z = init_node(value);

    if (compare(z, x)) while (x->parent_->value_ && compare(z, x)) x = x->parent_;
    else if (compare(x, z)) while (x->parent_->value_ && compare(x->parent_, z)) x = x->parent_;

    if (!(compare(z, x) || compare(x, z))) return iterator(x);

    while (x->value_) {
      y = x;
      if (compare(z, x)) x = x->left_;
      else if (compare(x, z)) x = x->right_;
      else return iterator(x);
    }

    z->parent_ = y;
    if (compare(z, y)) y->left_ = z;
    else y->right_ = z;

    insert_fixup(z);

    ++(this->size_);
    update_anchor();

    return iterator(z);
  }

//  template <typename InputIt>
//  void insert(InputIt first, InputIt last) {}

private:
  node* init_node(const_reference value) {
    node* ret = new node;
    ret->parent_ = nil_;
    ret->left_ = nil_;
    ret->right_ = nil_;
    ret->value_ = this->allocator_.allocate(1);
    *(ret->value_) = value;
    ret->color_ = kRBTreeColorRed;
    return ret;
  }

  node* init_nil() {
    node* ret = new node;
    ret->value_ = NULL;
    ret->color_ = kRBTreeColorBlack;
    return ret;
  }

  bool compare(node* n1, node* n2) {
    return this->comparator_(this->extractor_(n1->value_), this->extractor_(n2->value_));
  }

  void left_rotate(node* x) {
    node* y = x->right_;

    x->right_ = y->left_;
    y->left_->parent_ = x;
    y->parent_ = x->parent_;
    if (!x->parent_->value_) this->root_ = y;
    else if (x == x->parent_->left_) x->parent_->left_ = y;
    else x->parent_->right_ = y;
    y->left_ = x;
    x->parent_ = y;
  }

  void right_rotate(node* x) {
    node* y = x->left_;

    x->left_ = y->right_;
    y->right_->parent_ = x;
    y->parent_ = x->parent_;
    if (!x->parent_->value_) this->root_ = y;
    else if (x == x->parent_->left_) x->parent_->left_ = y;
    else x->parent_->right_ = y;
    y->right_ = x;
    x->parent_ = y;
  }

  void insert_root(const_reference value) {
    this->root_ = init_node(value);
    this->root_->color_ = kRBTreeColorBlack;
    this->root_->left_ = this->anchor_;
    this->root_->right_ = this->anchor_;
    this->root_->parent_ = this->anchor_;
    this->anchor_->left_ = this->root_;
    this->anchor_->right_ = this->root_;
    ++(this->size_);
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

  void update_anchor() {
    if (this->anchor_->right_->left_->value_) {
      this->anchor_->right_ = this->anchor_->right_->left_;
      this->anchor_->right_->left_ = this->anchor_;
    }
    if (this->anchor_->left_->right_->value_) {
      this->anchor_->left_ = this->anchor_->left_->right_;
      this->anchor_->left_->right_ = this->anchor_;
      this->anchor_->parent_ = this->anchor_->left_;
    }
  }
};

// iterators
// capacity: empty, size, max_size
// modifiers: clear, insert, erase, swap
// lookup: count, find, equal_range, lower_bound, upper_bound
// observers: key_comp, value_comp
