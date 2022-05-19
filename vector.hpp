#pragma once

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

    vector() : alloc_(allocator_type()), cap_(0), begin_(NULL), end_(NULL) {}

    explicit vector(const allocator_type& alloc) : alloc_(alloc()), cap_(0), begin_(NULL), end_(NULL) {}

    explicit vector(
      size_type count,
      const_reference value = value_type(),
      const allocator_type alloc = allocator_type()
    ) : alloc_(alloc), cap_(count), begin_(this->alloc_.allocate(count)), end_(this->begin_ + count) {
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
           : alloc_(alloc), cap_(ft::distance(first, last)),
             begin_(this->alloc_.allocate(this->cap_)), end_(this->begin_ + this->cap_) {
      for (size_type i = 0; first != last; ++i, ++first) this->alloc_.construct(&(this->begin_[i]), *first);
    }

    vector(const vector &other)
      : alloc_(allocator_type()), cap_(other.cap_),
        begin_(this->alloc_.allocate(other.cap_)), end_(this->begin_ + other.size()) {
      size_type size = other.size();
      for (size_type i = 0; i < size; ++i) this->alloc_.construct(&(this->begin_[i]), other[i]);
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
      return *this;
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
      this->reserve(ft::distance(first, last));
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
      size_type index = ft::distance(this->begin(), pos);
      if ((pos == this->end()) | this->make_insert_space(index, 1))
        this->alloc_.construct(&(this->begin_[index]), value);
      else this->begin_[index] = value;
      return this->begin_ + index;
    }

    void insert(iterator pos, size_type count, const_reference value) {
      size_type index = ft::distance(this->begin(), pos);
      if ((pos == this->end()) | this->make_insert_space(index, count))
        for (size_type i = 0; i < count; ++i) this->alloc_.construct(&(this->begin_[i + index]), value);
      else for (size_type i = 0; i < count; ++i) this->begin_[i + index] = value;
    }

    template <typename InputIt>
    void insert(iterator pos, InputIt first, typename ft::enable_if
      <
        is_input_iterator<typename ft::iterator_traits<InputIt>::iterator_category>::value,
        InputIt
      >::type last) {
      size_type index = ft::distance(this->begin(), pos);
      size_type distance = ft::distance(first, last);
      if ((pos == this->end()) | this->make_insert_space(index, distance))
        for (size_type i = 0; first != last; ++i, ++first) this->alloc_.construct(&(this->begin_[index + i]), *first);
      else for (size_type i = 0; first != last; ++i, ++first) this->begin_[index + i] = *first;
    }

    iterator erase(iterator pos) { return erase(pos, pos + 1); }
    iterator erase(iterator first, iterator last) {
      size_type remain = 0;
      for (iterator it = first; last != this->end(); ++it, ++last) {
        *it = *last;
        this->alloc_.destroy(last);
        ++remain;
      }
      this->end_ = first + remain;
      return first;
    }

    void push_back(const_reference value) {
      size_type size = this->size();
      this->make_insert_space(size, 1);
      this->alloc_.construct(&(this->begin_[size]), value);
    }

    void pop_back() { this->alloc_.destroy(this->end_-- - 1); }

    void resize(size_type count, value_type value = value_type()) {
      size_type size = this->size();
      if (size > count) {
        this->erase(this->begin_ + count, this->end());
        return;
      }

      this->make_insert_space(size, count - size);
      for (size_type i = size; i < count; ++i) this->begin_[i] = value;
    }

    void swap(vector& other) {
      allocator_type temp_alloc_ = this->alloc_;
      size_type      temp_cap_ = this->cap_;
      pointer        temp_begin_ = this->begin_;
      pointer        temp_end_ = this->end_;

      this->alloc_ = other.alloc_;
      this->cap_ = other.cap_;
      this->begin_ = other.begin_;
      this->end_ = other.end_;

      other.alloc_ = temp_alloc_;
      other.cap_ = temp_cap_;
      other.begin_ = temp_begin_;
      other.end_ = temp_end_;
    }

  private:
    allocator_type  alloc_;
    size_type       cap_;
    pointer         begin_;
    pointer         end_;

    int make_insert_space(size_type index, size_type n) {
      if (!this->cap_) {
        this->reserve(n);
        this->end_ += n;
        return true;
      }

      size_type size = this->size();
      if (this->cap_ < n + size) {
        size_type new_cap = this->cap_;
        while (new_cap < n + size) new_cap <<= 1;
        pointer temp = this->alloc_.allocate(new_cap);
        for (size_type i = 0; i < index; ++i) this->alloc_.construct(&(temp[i]), this->begin_[i]);
        for (size_type i = index; i < size; ++i) this->alloc_.construct(&(temp[i + n]), this->begin_[i]);
        this->clear();
        this->alloc_.deallocate(this->begin_, this->cap_);
        this->cap_ = new_cap;
        this->begin_ = temp;
        this->end_ = temp + size + n;
        return true;
      }

      for (size_type i = 0; i < size - index; ++i) { this->begin_[size + n - 1 - i] = this->begin_[size - 1 - i]; }
      this->end_ += n;
      return false;
    }
  };

  template <typename T, typename Alloc>
  bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(
      ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())
      || ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())
    );
  }

  template <typename T, typename Alloc>
  bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(lhs == rhs);
  }

  template <typename T, typename Alloc>
  bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  template <typename T, typename Alloc>
  bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(rhs < lhs); }

  template <typename T, typename Alloc>
  bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return rhs < lhs; }

  template <typename T, typename Alloc>
  bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs < rhs); }

  template <typename T, typename Alloc>
  void swap(vector<T, Alloc>&lhs, vector<T, Alloc>&rhs) { lhs.swap(rhs); }
}
