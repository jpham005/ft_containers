#pragma once

#include <iterator>
#include "type_traits.hpp"

namespace ft {
  template <typename T>
  struct has_iterator_typedefs {
  private:
    struct two {char lx; char lxx;};
    template <typename up> static two test(...);
    template <typename up> static char test(
      typename ft::is_valid<typename up::iterator_category>::type* = 0,
      typename ft::is_valid<typename up::difference_type>::type* = 0,
      typename ft::is_valid<typename up::value_type>::type* = 0,
      typename ft::is_valid<typename up::reference>::type* = 0,
      typename ft::is_valid<typename up::pointer>::type* = 0
    );
  public:
    static const bool value = sizeof(test<T>(0, 0, 0, 0, 0)) == 1;
  };

  template <typename T>
  struct has_iterator_category {
  private:
    struct two {char lx; char lxx;};
    template <typename up> static two test(...);
    template <typename up> static char test(typename up::iterator_category* = 0);
  public:
    static const bool value = sizeof(test<T>(0)) == 1;
  };

  template <typename Iter>
  struct iterator_traits_impl<Iter, true> {
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
  };

  template <typename Iter, bool> struct iterator_traits {};

  template <typename Iter>
  struct iterator_traits<Iter, true>
    : iterator_traits_impl
    <
      Iter,
      std::is_convertible<typename Iter::iterator_category, std::input_iterator_tag>::value ||
      std::is_convertible<typename Iter::iterator_category, std::output_iterator_tag>::value
    >
  {};

  template <typename Iter>
  struct iterator_traits<Iter, true> {
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
  };

  template <typename T>
  struct iterator_traits<T*> {
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
  };

  template <typename T>
  struct iterator_traits<const T*> {
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef const T& reference;
  };

  template <typename Iter>
  class reverse_iterator {
  public:
    typedef Iter iterator_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;

    reverse_iterator() : it_() {}
    explicit reverse_iterator(iterator_type it) : it_(it) {}
    template <typename Iter>
    explicit reverse_iterator(const reverse_iterator<Iter>& rev_it) : it_(rev_it.base()) {}

    iterator_type base() const { return it_; }

    reference operator*() const { iterator_type temp = it_; return *(--temp); }

    reverse_iterator operator+(difference_type n) const { return reverse_iterator(it_ - n); }
    reverse_iterator& operator++() { --it_; return *this; }
    const reverse_iterator operator++(int) { // NOLINT(readability-const-return-type)
      reverse_iterator<Iter> temp(*this);
      ++(*this);
      return temp;
    }
    reverse_iterator& operator+=(difference_type n) { it_ -= n; return *this; }

    reverse_iterator operator-(difference_type n) const { return reverse_iterator(it_ + n); }
    reverse_iterator& operator--() { ++it_; return *this; }
    const reverse_iterator operator--(int) { // NOLINT(readability-const-return-type)
      reverse_iterator<Iter> temp(*this);
      --(*this);
      return temp;
    }
    reverse_iterator& operator-=(difference_type n) { it_ += n; return *this; }

    pointer operator->() const { return &(operator*()); }
    reference operator[](difference_type n) const { return *(*this + n); }

  protected:
    iterator_type it_;
  };

  template <typename Iter>
  bool operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
    return lhs.base() == rhs.base();
  }
  template <typename Iter>
  bool operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
    return !(lhs == rhs);
  }
  template <typename Iter>
  bool operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
    return lhs.base() > rhs.base();
  }
  template <typename Iter>
  bool operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
    return !(rhs < lhs);
  }
  template <typename Iter>
  bool operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
    return rhs < lhs;
  }
  template <typename Iter>
  bool operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
    return !(lhs < rhs);
  }

  template <typename Iter>
  reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>& rev_it
  ) { return rev_it + n; }
  template <typename Iter>
  reverse_iterator<Iter> operator-(
    typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>& rev_it
  ) { return rev_it - n; }
}
