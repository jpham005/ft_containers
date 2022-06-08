#pragma once

#include "algorithm.hpp"
#include "red_black_tree.hpp"

namespace ft {
  template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
  class set {
  public:
    typedef Key                               key_type;
    typedef Key                               value_type;
    typedef std::size_t                       size_type;
    typedef std::ptrdiff_t                    difference_type;
    typedef Compare                           key_compare;
    typedef Compare                           value_compare;
    typedef Allocator                         allocator_type;
    typedef value_type&                       reference;
    typedef const value_type&                 const_reference;
    typedef typename Allocator::pointer       pointer;
    typedef typename Allocator::const_pointer const_pointer;

  private:
    template <typename T>
    struct use_key {
      const T&  operator()(const T* key) const { return *key; }
    };

    typedef rbtree<Key, Key, use_key<Key>, Compare, Allocator>  tree;

    tree  tree_;

  public:
    typedef typename tree::const_iterator          const_iterator;
    typedef const_iterator                         iterator;
    typedef typename tree::const_reverse_iterator  const_reverse_iterator;
    typedef const_reverse_iterator                 reverse_iterator;

    set() : tree_() {}
    explicit set(const Compare& comp, const Allocator& alloc = Allocator()) : tree_(comp, alloc) {}

    template <typename InputIt>
    set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
    : tree_(tree(first, last, comp, alloc)) {}

    set(const set& other) : tree_(other.tree_) {}

    ~set() {}

    set& operator=(const set& other) {
      tree_ = other.tree_;
      return *this;
    }

    allocator_type  get_allocator() const throw() { tree_.get_allocator(); }

    /*
    ====================================================================================================================
    iterator
    ====================================================================================================================
    */

    iterator begin() const throw() { return tree_.begin(); }

    iterator end() const throw() { return tree_.end(); }

    reverse_iterator rbegin() const throw() { return tree_.rbegin(); }

    reverse_iterator rend() const throw() { return tree_.rend(); }

    /*
    ====================================================================================================================
    capacity
    ====================================================================================================================
    */

    bool empty() const throw() { return tree_.empty(); }

    size_type size() const throw() { return tree_.size(); }

    size_type max_size() const throw() { return tree_.max_size(); }

    /*
    ====================================================================================================================
    modifiers
    ====================================================================================================================
    */

    void clear() throw() { tree_.clear(); }

    ft::pair<iterator, bool> insert(const_reference value) { return tree_.insert(value); }

    iterator insert(iterator hint, const_reference value) { return tree_.insert(hint, value); }

    template <typename InputIt>
    void insert(InputIt first, InputIt last) { tree_.insert(first, last); }

    void erase(iterator pos) { tree_.erase(pos); }

    void erase(iterator first, iterator last) { tree_.erase(first, last); }

    size_type erase(const key_type& key) { return tree_.erase(key); }

    void swap(set& other) { tree_.swap(other.tree_); }

    /*
    ====================================================================================================================
    Lookup
    ====================================================================================================================
    */

    size_type count(const key_type& key) const { return tree_.count(key); }

    iterator find(const key_type& key) const { return tree_.find(key); }

    ft::pair<iterator, iterator> equal_range(const key_type& key) const { return tree_.equal_range(key); }

    iterator lower_bound(const key_type& key) const { return tree_.lower_bound(key); }

    iterator upper_bound(const key_type& key) const { return tree_.upper_bound(key); }

    /*
    ====================================================================================================================
    Observers
    ====================================================================================================================
    */

    key_compare key_comp() const { return tree_.key_comp(); }

    value_compare value_comp() const { return tree_.key_comp(); }
  };

  template <typename Key, typename Compare, typename Alloc>
  void  swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs) { lhs.swap(rhs); }

  template <typename Key, typename Compare, typename Alloc>
  bool operator<(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  template <typename Key, typename Compare, typename Alloc>
  bool operator==(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
  }

  template <typename Key, typename Compare, typename Alloc>
  bool operator!=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
    return !(lhs == rhs);
  }

  template <typename Key, typename Compare, typename Alloc>
  bool operator<=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
    return !(rhs < lhs);
  }

  template <typename Key, typename Compare, typename Alloc>
  bool operator>(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
    return rhs < lhs;
  }

  template <typename Key, typename Compare, typename Alloc>
  bool operator>=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
    return !(lhs < rhs);
  }
}
