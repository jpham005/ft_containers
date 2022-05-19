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
}
