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
  friend class rbtree_iterator<T, const T*, const T&>;
  typedef rbtree_iterator<T, T*, T&>              iterator;
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
  typedef typename allocator_type::template rebind<node>::other       node_allocator_type;

private:
  allocator_type      allocator_;
  node_allocator_type node_allocator_;
  extract             extractor_;
  key_compare         comparator_;
  node*               nil_;
  node*               root_;
  node*               anchor_;
  size_type           size_;

public:
  node* getnode() { return root_; } // TODO
  rbtree()
    : allocator_(allocator_type()), node_allocator_(node_allocator_type()),
      nil_(init_nil()), root_(this->nil_), anchor_(init_nil()), size_(0) {}

  explicit rbtree(const key_compare& comp, const allocator_type& alloc = allocator_type())
    : allocator_(alloc), node_allocator_(node_allocator_type()), comparator_(comp),
      nil_(init_nil()), root_(this->nil_), anchor_(init_nil()), size_(0) {}

  template <typename InputIt>
  rbtree(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
    : allocator_(alloc), node_allocator_(node_allocator_type()),
      nil_(init_nil()), root_(this->nil), anchor_(init_nil()), size_(0) {
    insert(first, last);
  }

  rbtree(const rbtree& other)
    : nil_(init_nil()), root_(this->nil_), anchor_(init_nil()), size_(0) {
    allocator_ = other.allocator_;
    node_allocator_ = other.node_allocator_;
    extractor_ = other.extractor_;
    comparator_ = other.comparator_;
    for (const_iterator it = other.begin(); it != other.end(); ++it) insert(*it);
  }

  ~rbtree() {
    if (this->root_->value_) clear_all_node(this->root_);

    delete this->nil_;
    delete this->anchor_;
  }

  rbtree& operator=(const rbtree& other) {
    rbtree cp(other);
    this->swap(cp);
    return *this;
  }

  allocator_type get_allocator() const throw() { return this->allocator_; }

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

  size_type max_size() const throw() {
    return std::numeric_limits<difference_type>::max(), std::numeric_limits<size_type>::max()
      / (sizeof(node) + sizeof(value_type));
  }

  /*
  ======================================================================================================================
  modifier
  ======================================================================================================================
  */

  void clear() throw() {
    this->clear_all_node(this->root_);
    this->size_ = 0;
    this->anchor_->parent_ = NULL;
    this->anchor_->left_ = NULL;
    this->anchor_->right_ = NULL;
    this->root_ = this->nil_;
  }

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
      else {
        this->destroy_node(z);
        return ft::make_pair(iterator(x), false);
      }
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

    if (compare(z, x)) {
      while (x->parent_->value_ && compare(z, x)) {
        y = x->parent_;
        x = x->parent_;
      }
    } else if (compare(x, z)) {
      while (x->parent_->value_ && compare(x, z)) {
        y = x;
        x = x->parent_;
      }
    }

    if (!(compare(z, x) || compare(x, z))) {
      destroy_node(z);
      return iterator(x);
    }

    x = y;
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

  template <typename InputIt>
  void insert(InputIt first, InputIt last) { for (; first != last; ++first) insert(*first); }

  void erase(iterator pos) {
    node* z = pos.node_;
    node* y = z;
    node* x;
    char y_original_color = y->color_;

    iterator new_begin = ++(this->begin());
    iterator new_end = --(this->end());

    if (!z->left_->value_) {
      x = z->right_;
      this->transplant_node(z, z->right_);
      if (!x->value_) x->parent_ = z; // TODO: when x == nil
    } else if (!z->right_->value_) {
      x = z->left_;
      this->transplant_node(z, z->left_);
    } else {
      y = (++pos).node_;
      y_original_color = y->color_;
      x = y->right_;

      if (y->parent_ != z) {
        this->transplant_node(y, y->right_);
        y->right_ = z->right_;
        y->right_->parent_ = y;
      } else x->parent_ = y;

      this->transplant_node(z, y);
      y->left_ = z->left_;
      y->left_->parent_ = y;
      y->color_ = z->color_;
    }

    if (z == this->anchor_->right_) {
      this->anchor_->right_ = new_begin.node_;
      new_begin.node_->left_ = this->anchor_;
    }

    if (z == this->anchor_->left_) {
      this->anchor_->left_ = new_end.node_;
      new_end.node_->right_ = this->anchor_;
    }

    this->destroy_node(z);
    if (y_original_color == kRBTreeColorBlack) this->delete_fixup(x);
  }

  void erase(iterator first, iterator last) { for (; first != last; ++first) this->erase(first); }

  size_type erase(const key_type& key) {
    iterator target = this->find(key);

    if (!target.node_->value_) return 0;

    this->erase(target);
    return 1;
  }

  void swap(rbtree& other) {
    key_compare         temp_comparator_ = other.comparator_;
    allocator_type      temp_allocator_ = other.allocator_;
    node_allocator_type temp_node_allocator_ = other.node_allocator_;
    extract             temp_extractor_ = other.extractor_;
    node*               temp_nil_ = other.nil_;
    node*               temp_root_ = other.root_;
    node*               temp_anchor_ = other.anchor_;
    size_type           temp_size_ = other.size_;

    other.comparator_ = this->comparator_;
    other.allocator_ = this->allocator_;
    other.node_allocator_ = this->node_allocator_;
    other.extractor_ = this->extractor_;
    other.nil_ = this->nil_;
    other.root_ = this->root_;
    other.anchor_ = this->anchor_;
    other.size_ = this->size_;

    this->comparator_ = temp_comparator_;
    this->allocator_ = temp_allocator_;
    this->node_allocator_ = temp_node_allocator_;
    this->extractor_ = temp_extractor_;
    this->nil_ = temp_nil_;
    this->root_ = temp_root_;
    this->anchor_ = temp_anchor_;
    this->size_ = temp_size_;
  }

  /*
  ======================================================================================================================
  Lookup
  ======================================================================================================================
  */

  size_type count(const key_type& key) const { return (this->find(key) != this->end()); }

  iterator find(const key_type& key) {
    node* x = this->root_;
    while (x->value_) {
      if (this->comparator_(this->extractor_(x->value_), key)) x = x->right_;
      else if (this->comparator_(key, this->extractor_(x->value_))) x = x->left_;
      else return iterator(x);
    }
    return this->end();
  }

  const_iterator find(const key_type& key) const {
    node* x = this->root_;
    while (x->value_) {
      if (this->comparator_(this->extractor_(x->value_), key)) x = x->right_;
      else if (this->comparator_(key, this->extractor_(x->value_))) x = x->left_;
      else return const_iterator(x);
    }
    return this->end();
  }

  ft::pair<iterator, iterator> equal_range(const key_type& key) {
    return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
  }

  ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
    return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
  }

  iterator lower_bound(const key_type& key) { return this->find(key); }

  const_iterator lower_bound(const key_type& key) const { return this->find(key); }

  iterator upper_bound(const key_type& key) {
    iterator ret = this->find(key);
    if (ret.node_->value_) return ++ret;
    else return ret;
  }

  const_iterator upper_bound(const key_type& key) const {
    const_iterator ret = this->find(key);
    if (ret.node_->value_) return ++ret;
    else return ret;
  }

  /*
  ======================================================================================================================
  Observers
  ======================================================================================================================
  */

  key_compare key_comp() const { return this->comparator_; }

  // value_compare is implemented individually

private:
  node* init_node(const_reference value) {
//    node* ret = new node;
    node* ret = this->node_allocator_.allocate(1);
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
    ret->parent_ = NULL;
    ret->left_ = NULL;
    ret->right_ = NULL;
    ret->value_ = NULL;
    ret->color_ = kRBTreeColorBlack;
    return ret;
  }

  void destroy_node(node* target) {
    this->allocator_.deallocate(target->value_, 1);
    this->node_allocator_.deallocate(target, 1);
  }

  bool compare(node* n1, node* n2) {
    return this->comparator_(this->extractor_(n1->value_), this->extractor_(n2->value_));
  }

  void clear_all_node(node* curr) {
    if (!curr->value_) return;

    clear_all_node(curr->left_);
    clear_all_node(curr->right_);
    destroy_node(curr);
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

  void transplant_node(node* dest, node* src) {
    if (this->root_ == dest) this->root_ = src;
    else if (dest == dest->parent_->left_) dest->parent_->left_ = src;
    else dest->parent_->right_ = src;
    src->parent_ = dest->parent_;
  }

  void delete_fixup(node* x) {
    node* w;

    while ((x != this->root_) && (x->color_ == kRBTreeColorBlack)) {
      if (x == x->parent_->left_) {
        w = x->parent_->right_;
        if (w->color_ == kRBTreeColorRed) {
          w->color_ = kRBTreeColorBlack;
          x->parent_->color_ = kRBTreeColorRed;
          this->left_rotate(x->parent_);
          w = x->parent_->right_;
        }

        if ((w->left_->color_ == kRBTreeColorBlack) && (w->right_->color_ == kRBTreeColorBlack)) {
          w->color_ = kRBTreeColorRed;
          x = x->parent_;
        } else {
          if (w->right_->color_ == kRBTreeColorBlack) {
            w->left_->color_ = kRBTreeColorBlack;
            w->color_ = kRBTreeColorRed;
            this->right_rotate(w);
            w = x->parent_->right_;
          }

          w->color_ = x->parent_->color_;
          x->parent_->color_ = kRBTreeColorBlack;
          this->left_rotate(x->parent_);
          x = this->root_;
        }
      } else {
        w = x->parent_->left_;
        if (w->color_ == kRBTreeColorRed) {
          w->color_ = kRBTreeColorBlack;
          x->parent_->color_ = kRBTreeColorRed;
          this->right_rotate(x->parent_);
          w = x->parent_->left_;
        }

        if ((w->left_->color_ == kRBTreeColorBlack) && (w->right_->color_ == kRBTreeColorBlack)) {
          w->color_ = kRBTreeColorRed;
          x = x->parent_;
        } else {
          if (w->left_->color_ == kRBTreeColorBlack) {
            w->right_->color_ = kRBTreeColorBlack;
            w->color_ = kRBTreeColorRed;
            this->left_rotate(w);
            w = x->parent_->left_;
          }

          w->color_ = x->parent_->color_;
          x->parent_->color_ = kRBTreeColorBlack;
          this->right_rotate(x->parent_);
          x = this->root_;
        }
      }
    }

    x->color_ = kRBTreeColorBlack;
  }
};
