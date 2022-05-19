#pragma once

#include "vector.hpp"

namespace ft {
  template <typename T, typename Container = ft::vector<T> >
  class stack {
  public:
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    explicit stack(const Container& cont = Container()) : c(cont) {}
    stack(const stack& other) : c(other.c) {}
    ~stack() {}
    stack& operator=(const stack& other) { c = other.c; }

    // element acceess
    reference top() { return c.back(); }
    const_reference top() const { return c.back(); }

    // capacity
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }

    // modifiers
    void push(const value_type& value) { c.push_back(value); }
    void pop() { c.pop_back(); }

    template <typename _T, typename _Container>
    friend bool operator==(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

    template <typename _T, typename _Container>
    friend bool operator<(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

  protected:
    Container c;
  };

  template <typename T, typename Container>
  bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c == rhs.c; }

  template <typename T, typename Container>
  bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs == rhs); }

  template <typename T, typename Container>
  bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c < rhs.c; }

  template <typename T, typename Container>
  bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(rhs < lhs); }

  template <typename T, typename Container>
  bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return rhs < lhs; }

  template <typename T, typename Container>
  bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs < rhs); }
}
