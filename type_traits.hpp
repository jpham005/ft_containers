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

  struct true_type { const static bool value = true; };
  struct false_type { const static bool value = false; };

  template <typename T>
  struct remove_const { typedef T type; };

  template <typename T>
  struct remove_const<const T> { typedef T type; };

  template <typename T>
  struct remove_volatile { typedef T type; };

  template <typename T>
  struct remove_volatile<volatile T> { typedef T type; };

  template <typename T>
  struct remove_const_volatile {
    typedef typename ft::remove_volatile<typename ft::remove_const<T>::type>::type type;
  };

  template <typename T>
  struct is_integral_impl : ft::false_type {};

  template <>
  struct is_integral_impl<bool> : ft::true_type {};

  template <>
  struct is_integral_impl<char> : ft::true_type {};

  template <>
  struct is_integral_impl<signed char> : ft::true_type {};

  template <>
  struct is_integral_impl<unsigned char> : ft::true_type {};

  template <>
  struct is_integral_impl<char16_t> : ft::true_type {};

  template <>
  struct is_integral_impl<char32_t> : ft::true_type {};

  template <>
  struct is_integral_impl<wchar_t> : ft::true_type {};

  template <>
  struct is_integral_impl<short> : ft::true_type {};

  template <>
  struct is_integral_impl<unsigned short> : ft::true_type {};

  template <>
  struct is_integral_impl<int> : ft::true_type {};

  template <>
  struct is_integral_impl<unsigned int> : ft::true_type {};

  template <>
  struct is_integral_impl<long> : ft::true_type {};

  template <>
  struct is_integral_impl<unsigned long> : ft::true_type {};

  template <typename T>
  struct is_integral : ft::is_integral_impl<typename ft::remove_const_volatile<T>::type> {};
}
