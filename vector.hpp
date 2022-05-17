#pragma once
#include <iostream>
#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {
  template < typename T, typename Allocator>
  class vector_base {
  public:
    typedef T                                         value_type;
    typedef Allocator                                 allocator_type;
    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;
    typedef std::ptrdiff_t                            difference_type;
    typedef std::size_t                               size_type;

  protected:
    pointer                           begin_;
    pointer                           end_;
    ft::pair<pointer, allocator_type> end_cap_;
    vector_base() : alloc_(allocator_type()) {
      this->begin_ = NULL;
      this->end_ = NULL;
    }
    vector_base(size_type count) : alloc_(allocator_type()) {
      this->begin_ = this->alloc_.allocate(count);
      this->end_ = this->begin_;
    }

  private:
    allocator_type alloc_;
  };

  template <typename T, typename Allocator = std::allocator<T> >
  class vector : public vector_base<T, Allocator> {
  public:
    typedef vector_base<T, Allocator> base;
    typedef T value_type;
    typedef typename base::allocator_type         allocator_type;
    typedef typename base::reference              reference;
    typedef typename base::const_reference        const_reference;
    typedef typename base::pointer                pointer;
    typedef typename base::const_pointer          const_pointer;
    typedef pointer                               iterator;
    typedef const_pointer                         const_iterator;
    typedef ft::reverse_iterator<iterator>        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;
    typedef typename base::difference_type        difference_type;
    typedef typename base::size_type              size_type;

    explicit vector() : base() {}

    explicit vector(size_type count, const T &value) : base(count) {
      size_type i = 0;
      while (i < count) this->begin_[i++] = value;
      this->end_ += i;
    };

    iterator begin() { return this->begin_; }
    const_iterator begin() const { return this->begin_; }
    iterator end() { return this->end_; }

    const_iterator end() const { return this->end; }
    reverse_iterator rbegin() { return ft::reverse_iterator<iterator>(this->end_); }
    const_reverse_iterator rbegin() const { return ft::reverse_iterator<const_iterator>(this->end_); }
    reverse_iterator rend() { return ft::reverse_iterator<iterator>(this->begin_); }

    value_type test() { return *(this->end_ - 1); }

    template<typename InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());

    vector(const vector &x);

  private:
  };
}

