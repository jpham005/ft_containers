#pragma once

namespace ft {
  template <typename T1, typename T2>
  struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    first_type first_;
    second_type second_;

    pair();
    template<typename U, typename V>
    pair(const pair<U, V>& pr);
    pair(const first_type& a, const second_type& b);

    pair& operator=(const pair& pr);
  };

  template <typename T1, typename T2>
  bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
  template <typename T1, typename T2>
  bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
  template <typename T1, typename T2>
  bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
  template <typename T1, typename T2>
  bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
  template <typename T1, typename T2>
  bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
  template <typename T1, typename T2>
  bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);

  template <typename T1, typename T2>
  pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

  /*
  ======================================================================================================================
    pair
  ======================================================================================================================
  */

  template <typename T1, typename T2>
  pair<T1, T2>::pair() : first_(T1()), second_(T2()) {}
  template <typename T1, typename T2>
  template <typename U, typename V>
  pair<T1, T2>::pair(const pair<U, V>& pr) : first_(U(pr.first_)), second_(V(pr.second_)) {}
  template <typename T1, typename T2>
  pair<T1, T2>::pair(const first_type& a, const second_type& b) : first_(a), second_(b) {}

  template <typename T1, typename T2>
  pair<T1, T2>& pair<T1, T2>::operator=(const pair& pr) {
    this->first_ = pr.first_;
    this->second_ = pr.second_;
    return *this;
  }

  template <typename T1, typename T2>
  bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (lhs.first_ == rhs.first_) && (lhs.second_ == rhs.second_);
  }
  template <typename T1, typename T2>
  bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T1, typename T2>
  bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first_ < rhs.first_ || (!(rhs.first_ < lhs.first_) && lhs.second_ < rhs.second_);
  }
  template <typename T1, typename T2>
  bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(rhs < lhs);
  }
  template <typename T1, typename T2>
  bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return rhs < lhs;
  }
  template <typename T1, typename T2>
  bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs < rhs);
  }
}

