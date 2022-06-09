#pragma once

namespace ft {
  template <bool Cond, typename T = void>
  struct enable_if {};

  template <typename T>
  struct enable_if<true, T> { typedef T type; };

  template <typename>
  struct void_t {
    typedef void type;
  };

  template <typename T, typename U>
  struct is_convertible {
  private:
    struct two { char _lx; char _lxx; };
    static two test(...);
    static char test(U u);

  public:
    static const bool value = sizeof(test(T())) == 1;
  };

//  template <typename T, T v>
//  struct integral_constant {
//    typedef T                           value_type;
//    typedef ft::integral_constant<T, v> type;
//
//    static const T value = v;
//    operator value_type() const throw() { return value; }
//  };
//
//  int a = integral_constant<int, 1>();
//
//  template <>
//  struct integral_constant<bool, true> {
//    typedef ft::integral_constant<bool, true> true_type;
//
//    static const bool value = true;
//  };
//
//  template <>
//  struct integral_constant<bool, false> {
//    typedef ft::integral_constant<bool, false> false_type;
//
//    static const bool value = false;
//  };
//
//  template <typename T>
//  struct is_integral : public ft::integral_constant<T, > {
//
//  };
}
