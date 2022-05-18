#pragma once
#include <iostream> // TODO
#include <stdexcept>
#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {
  template <typename T, typename Allocator = std::allocator<T> >
  class vector {
  public:
    typedef T                                         value_type;
    typedef Allocator                                 allocator_type;
    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;
    typedef pointer                                   iterator;
    typedef const_pointer                             const_iterator;
    typedef ft::reverse_iterator<iterator>            reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;
    typedef typename std::ptrdiff_t                   difference_type;
    typedef typename std::size_t                      size_type;

    explicit vector() : alloc_(allocator_type()), cap_(0), begin_(NULL), end_(NULL) {}

    explicit vector(size_type count, const_reference value)
      : alloc_(allocator_type()), cap_(count), begin_(this->alloc_.allocate(count)), end_(this->begin_ + count) {
      for (size_type i = 0; i < count; ++i) this->alloc_.construct(&(this->begin_[i]), value);
    };

    template<typename InputIterator>
    vector(InputIterator first,
           typename enable_if
             <
               ft::is_input_iterator<typename ft::iterator_traits<InputIterator>::iterator_category >::value,
               InputIterator
             >::type last,
           const allocator_type &alloc = allocator_type())
           : alloc_(alloc()), cap_(ft::get_iter_gap(first, last)),
             begin_(this->alloc_.allocate(this->cap_)), end_(this->begin_ + this->cap_) {
      for (size_type i = 0; first != last; ++i, ++first) this->alloc_.construct(&(this->begin[i]), *first);
    }

    vector(const vector &x)
      : alloc_(allocator_type()), cap_(x.cap_), begin_(this->alloc_.allocate(x.size())), end_(this->begin_ + x.size()) {
      size_type size = x.size();
      for (size_type i = 0; i < size; ++i) this->alloc_.construct(&(this->begin_[i]), x[i]);
    }

    ~vector() {
      if (this->begin_) {
        this->clear();
        this->alloc_.deallocate(this->begin_, this->cap_);
      }
    }

    vector& operator=(const vector& other) {
      this->reserve(other.cap_);
      size_type size = other.size();
      for (size_type i = 0; i < size; ++i) this->alloc_.construct(&(this->begin_[i]), other[i]);
      this->end_ = this->begin_ + size;
    }

    void assign(size_type count, const_reference value) {
      this->clear();
      this->reserve(count);
      for (size_type i = 0; i < count; ++i) this->alloc_.construct(&(this->begin_[i]), value);
      this->end_ = this->begin_ + count;
    }
    template <typename InputIt>
    void assign(
      InputIt first,
      typename enable_if<ft::is_input_iterator<typename ft::iterator_traits<InputIt>::iterator_category >::value,
      InputIt>::type last
    ) {
      this->clear();
      this->reserve(ft::get_iter_gap(first, last));
      size_type i;
      for (i = 0; first != last; ++i, ++first) this->alloc_.construct(&(this->begin_[i]), *first);
      this->end_ = this->begin_ + i;
    }

    allocator_type get_allocator() const throw() { return this->alloc_; }

    /*
    =============================================================================
    Element access
    =============================================================================
     */

    reference at(size_type pos) {
      if (!(pos < this->size()))
        throw std::out_of_range("position out of range");
      return this->begin_[pos];
    }
    const_reference at(size_type pos) const {
      if (!(pos < this->size()))
        throw std::out_of_range("position out of range");
      return this->begin_[pos];
    }

    reference operator[](size_type pos) { return this->begin_[pos]; }
    const_reference operator[](size_type pos) const { return this->begin_[pos]; }

    reference front() { return *(this->begin_); }
    const_reference front() const { return *(this->begin_); }

    reference back() { return *(this->end_ - 1); }
    const_reference back() const { return *(this->end_ - 1); }

    pointer data() throw() { return this->begin_; }
    const_pointer data() const throw() { return this->begin_; }

    /*
    =============================================================================
    Iterators
    =============================================================================
     */

    iterator begin() throw() { return this->begin_; }
    const_iterator begin() const throw() { return this->begin_; }

    iterator end() throw() { return this->end_; }
    const_iterator end() const throw() { return this->end_; }

    reverse_iterator rbegin() throw() { return reverse_iterator(this->end_); }
    const_reverse_iterator rbegin() const throw() { return const_reverse_iterator(this->end_); }

    reverse_iterator rend() throw() { return reverse_iterator(this->begin_); }
    const_reverse_iterator rend() const throw() { return const_reverse_iterator(this->end_); }

    /*
    =============================================================================
    Capacity
    =============================================================================
     */

    bool empty() const throw() { return !this->size(); }

    size_type size() const throw() { return this->end_ - this->begin_; }

    size_type max_size() const throw() { return this->alloc_.max_size(); }

    void reserve(size_type new_cap) {
      if (new_cap <= this->cap_)
        return;
      size_type size = this->size();
      pointer temp = alloc_.allocate(new_cap);
      for (size_type i = 0; i < size; ++i) alloc_.construct(&temp[i], this->begin_[i]);
      if (this->begin_) {
        this->clear();
        alloc_.deallocate(this->begin_, this->cap_);
      }
      this->cap_ = new_cap;
      this->begin_ = temp;
      this->end_ = temp + size;
    }

    size_type capacity() const throw() { return this->cap_; }

    /*
    =============================================================================
    Modifiers
    =============================================================================
     */

    void clear() throw() {
      size_type size = this->size();
      for (size_type i = 0; i < size; ++i) this->alloc_.destroy(&(this->begin_[i]));
      this->end_ = this->begin_;
    }

    iterator insert(iterator pos, const_reference value) {
      if (!this->cap_) {
        this->reserve(1);
        this->begin_[0] = value;
        this->end_ = this->begin_ + 1;
        return this->begin_;
      }

      size_type new_size = this->size() + 1;
      if (this->cap_ < new_size) {
        pointer temp = this->alloc_.allocate(this->cap_ << 1);
        size_type i = 0;
        iterator it;
        for (it = this->begin(); it != pos; ++it, ++i) this->alloc_.construct(&temp[i], *it);
        iterator ret = &temp[i];
        this->alloc_.construct(&temp[i++], value);
        for (; it != this->end(); ++it, ++i) this->alloc_.construct(&temp[i], *it);
        this->clear();
        this->alloc_.deallocate(this->begin_, this->cap_);
        this->cap_ <<= 1;
        this->begin_ = temp;
        this->end_ = this->begin_ + i;
        return ret;
      }

      value_type replaced = *pos;
      (void) replaced;
      return pos;
    }
//
//    void insert(iterator pos, size_type count, const_reference value) {}
//
//    template <typename InputIt>
//    void insert(iterator pos, InputIt first, InputIt last) {}

//    void resize(size_type n, value_type val = value_type()) {
//      if (this->size() > n) for (size_type i = this->size() - n; i > 0; --i) ~(*(this->end_));
//      else if (this->size() < n);
//      (void)val;
//    }

  private:
    allocator_type  alloc_;
    size_type       cap_;
    pointer         begin_;
    pointer         end_;
  };
}
