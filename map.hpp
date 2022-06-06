#pragma once

#include "algorithm.hpp"
#include "red_black_tree.hpp"

namespace ft {
  template
  <
    typename Key, typename T, typename Compare = std::less<Key>,
    typename Allocator = std::allocator<ft::pair<const Key, T> >
  >
  class map {

  public:
    typedef Key                                   key_type;
    typedef T                                     mapped_type;
    typedef typename ft::pair<const Key, T>       value_type;
    typedef typename std::size_t                  size_type;
    typedef typename std::ptrdiff_t               difference_type;
    typedef Compare                               key_compare;
    typedef Allocator                             allocator_type;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;
    typedef typename Allocator::pointer           pointer;
    typedef typename Allocator::const_pointer     const_pointer;

  private:
    template <typename Pair>
    struct use_first {
      typedef typename Pair::first_type  first_type;
      typedef typename Pair::second_type second_type;

      const first_type&  operator()(const Pair* pair) { return pair->first; }
      const first_type&  operator()(const Pair* pair) const { return pair->first; }
    };

    typedef rbtree<key_type, value_type, use_first<value_type>, key_compare , allocator_type>  tree;

    tree  tree_;

  public:
    typedef typename tree::iterator               iterator;
    typedef typename tree::const_iterator         const_iterator;
    typedef typename tree::reverse_iterator       reverse_iterator;
    typedef typename tree::const_reverse_iterator const_reverse_iterator;

    class value_compare : public std::binary_function<value_type, value_type, bool> {
    private:
      typedef std::binary_function<value_type, value_type, bool>  bftype;

    protected:
      Compare comp;

    public:
      typedef typename bftype::result_type          result_type;
      typedef typename bftype::first_argument_type  first_argument_type;
      typedef typename bftype::second_argument_type second_argument_type;

      value_compare() : comp() {}
      result_type operator()(first_argument_type lhs, second_argument_type rhs) { return comp(lhs, rhs); }
    };

    map() : tree_() {}
    explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : tree_(tree(comp, alloc)) {}

    template <typename InputIt>
    map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
      : tree_(tree(first, last, comp, alloc)) {}

    map(const map& other) : tree_(other.tree_) {}

    ~map() {}

    map& operator=(const map& other) {
      tree_ = other.tree_;
      return *this;
    }

    allocator_type  get_allocator() const throw() { tree_.get_allocator(); }

    /*
    ====================================================================================================================
    element access
    ====================================================================================================================
    */

    mapped_type & at(const key_type& key) {
      iterator node = find(key);
      if (node == tree_.end()) throw std::out_of_range("out of range");
      return node->second;
    }

    mapped_type&  operator[](const key_type& key) {
      return insert(ft::make_pair(key, mapped_type())).first->second;
    }

    /*
    ====================================================================================================================
    iterator
    ====================================================================================================================
    */

    iterator begin() throw() { return tree_.begin(); }
    const_iterator begin() const throw() { return tree_.begin(); }

    iterator end() throw() { return tree_.end(); }
    const_iterator end() const throw() { return tree_.end(); }

    reverse_iterator rbegin() throw() { return tree_.rbegin(); }
    const_reverse_iterator rbegin() const throw() { return tree_.rbegin(); }

    reverse_iterator rend() throw() { return tree_.rend(); }
    const_reverse_iterator rend() const throw() { return tree_.rend(); }

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

    void swap(const map& other) { tree_.swap(other.tree_); }

    /*
    ====================================================================================================================
    Lookup
    ====================================================================================================================
    */

    size_type count(const key_type& key) const { return tree_.count(key); }

    iterator find(const key_type& key) { return tree_.find(key); }

    const_iterator find(const key_type& key) const { return tree_.find(key); }

    ft::pair<iterator, iterator> equal_range(const key_type& key) { return tree_.equal_range(key); }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const { return tree_.equal_range(key); }

    iterator lower_bound(const key_type& key) { return tree_.lower_bound(key); }

    const_iterator lower_bound(const key_type& key) const { return tree_.lower_bound(key); }

    iterator upper_bound(const key_type& key) { return tree_.upper_bound(key); }

    const_iterator upper_bound(const key_type& key) const { return tree_.upper_bound(key); }

    /*
    ====================================================================================================================
    Observers
    ====================================================================================================================
    */

    key_compare key_comp() const { return tree_.key_comp(); }

    value_compare value_comp() const { return value_compare(); }
  };

  template <typename Key, typename T, typename Compare, typename Alloc>
  void  swap(ft::map<Key, T, Compare, Alloc> lhs, ft::map<Key, T, Compare, Alloc> rhs) { lhs.swap(rhs); }

  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
    return !(lhs == rhs);
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
    return !(rhs < lhs);
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
    return rhs < lhs;
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
    return !(lhs < rhs);
  }
}
