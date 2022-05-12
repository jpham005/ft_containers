#pragma once

#include <memory>

class vector_base {

};

template <typename T, typename Allocator = std::allocator<T> >
class vector {
 public:
  // member types
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef allocator_type::pointer pointer;
  typedef allocator_type::const_pointer const_pointer;
  typedef std::ptrdiff_t difference_type // signed integer type, result of subtracting two ptr
  typedef std::size_t size_type; // unsigned integer type

  explicit vector(const allocator_type& alloc = allocator_type()) : val_(NULL) {} // default constructor
  explicit vector(size_type count, const T& value); // copy elements with count
  template <typename InputIterator>
  vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
  vector(const vector& x);

 private:
  value_type* ;
};
