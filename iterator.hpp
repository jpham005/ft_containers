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
      typename ft::void_t<typename up::iterator_category>::type*,
      typename ft::void_t<typename up::difference_type>::type*,
      typename ft::void_t<typename up::value_type>::type*,
      typename ft::void_t<typename up::reference>::type*,
      typename ft::void_t<typename up::pointer>::type*
    );
  public:
    static const bool value = sizeof(test<T>(0, 0, 0, 0, 0)) == 1;
  };

  template <typename Iter, bool> struct iterator_traits_impl {};

  template <typename Iter>
  struct iterator_traits_impl<Iter, true> {
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
  };

  template <typename Iter>
  struct iterator_traits : public iterator_traits_impl<Iter, has_iterator_typedefs<Iter>::value> {};

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

  template <typename T>
  struct is_input_iterator : ft::is_convertible<T, std::input_iterator_tag> {};

  template <typename T>
  struct is_forward_iterator : ft::is_convertible<T, std::forward_iterator_tag> {};

  template <typename T>
  struct is_bidrectional_iterator : ft::is_convertible<T, std::bidirectional_iterator_tag> {};

  template <typename T>
  struct is_random_access_iterator : ft::is_convertible<T, std::random_access_iterator_tag> {};

  template <typename Iter>
  class reverse_iterator {
  public:
    typedef Iter                                              iterator_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::value_type        value_type;
    typedef typename iterator_traits<Iter>::difference_type   difference_type;
    typedef typename iterator_traits<Iter>::pointer           pointer;
    typedef typename iterator_traits<Iter>::reference         reference;

    reverse_iterator() : it_() {}
    explicit reverse_iterator(iterator_type it) : it_(it) {}
    template <typename rev_iter>
    explicit reverse_iterator(const reverse_iterator<rev_iter>& rev_it) : it_(rev_it.base()) {}

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

  template <typename Iter1, typename Iter2>
  bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() == rhs.base();
  }
  template <typename Iter1, typename Iter2>
  bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return !(lhs == rhs);
  }
  template <typename Iter1, typename Iter2>
  bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() > rhs.base();
  }
  template <typename Iter1, typename Iter2>
  bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return !(rhs < lhs);
  }
  template <typename Iter1, typename Iter2>
  bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return rhs < lhs;
  }
  template <typename Iter1, typename Iter2>
  bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
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

  template <typename Iter>
  Iter advance(Iter it, std::size_t n) { for (std::size_t i = 0; i < n; ++i) ++it; return it; }

  template <typename Iter>
  std::size_t do_distance(Iter first, Iter last, std::input_iterator_tag) {
    std::size_t gap = 0;
    while (first != last) { ++first; ++gap; }
    return gap;
  }

  template <typename Iter>
  std::size_t do_distance(Iter first, Iter last, std::random_access_iterator_tag) {
    return last - first;
  }

  template <typename Iter>
  std::size_t distance(Iter first, Iter last) {
    return do_distance(first, last, typename iterator_traits<Iter>::iterator_category());
  }
}
