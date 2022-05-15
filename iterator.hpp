#pragma once

#include <iterator>

namespace ft {
  template <typename Iterator>
  class iterator_traits {
  public:
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
  };

  template <typename T>
  class iterator_traits<T*> {
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
  };

  template <typename T>
  class iterator_traits<const T*> {
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef const T& reference;
  };

  template <typename Iterator>
  class reverse_iterator {
  public:
    typedef Iterator iterator_type;
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef typename iterator_traits<Iterator>::reference reference;

    reverse_iterator() : it_() {}
    explicit reverse_iterator(iterator_type it) : it_(it) {}
    template <typename Iter>
    explicit reverse_iterator(const reverse_iterator<Iter>& rev_it) : it_(rev_it.base()) {}

    iterator_type base() const { return it_; }

    reference operator*() const { iterator_type temp = it_; return *(--temp); }

    reverse_iterator operator+(difference_type n) const { return reverse_iterator(it_ - n); }
    reverse_iterator& operator++() { --it_; return *this; }
    const reverse_iterator operator++(int) { // NOLINT(readability-const-return-type)
      reverse_iterator<Iterator> temp(*this);
      ++(*this);
      return temp;
    }
    reverse_iterator& operator+=(difference_type n) { it_ -= n; return *this; }

    reverse_iterator operator-(difference_type n) const { return reverse_iterator(it_ + n); }
    reverse_iterator& operator--() { ++it_; return *this; }
    const reverse_iterator operator--(int) { // NOLINT(readability-const-return-type)
      reverse_iterator<Iterator> temp(*this);
      --(*this);
      return temp;
    }
    reverse_iterator& operator-=(difference_type n) { it_ += n; return *this; }

    pointer operator->() const { return &(operator*()); }
    reference operator[](difference_type n) const { return *(*this + n); }

  protected:
    iterator_type it_;
  };

  template <typename Iterator>
  bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return lhs.base() == rhs.base();
  }
  template <typename Iterator>
  bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return !(lhs == rhs);
  }
  template <typename Iterator>
  bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return lhs.base() > rhs.base();
  }
  template <typename Iterator>
  bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return !(rhs < lhs);
  }
  template <typename Iterator>
  bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return rhs < lhs;
  }
  template <typename Iterator>
  bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return !(lhs < rhs);
  }

  template <typename Iterator>
  reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it
  ) { return rev_it + n; }
  template <typename Iterator>
  reverse_iterator<Iterator> operator-(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it
  ) { return rev_it - n; }
}
