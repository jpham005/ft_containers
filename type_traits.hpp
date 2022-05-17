#pragma once

namespace ft {
  template <bool Cond, typename T = void>
  struct enable_if {};

  template <typename T>
  struct enable_if<true, T> { typedef T type; };

  template <typename T>
  struct is_integral {
    typedef bool value_type;
    value_type type;
  };

  template <typename T>
  struct is_valid {
    typedef void type;
  };
}
