#include "vector.hpp"

# include <iostream>
# include <string>
# include <memory>

# define FT 0
# define STD 1

# ifndef NAMESPACE
#  define NAMESPACE FT
# endif

# if NAMESPACE == FT
#  define NS ft
# else
#  define NS std
# endif

template	<typename A, typename B>
void	compare_all(A const& a, B const& b)
{
  std::cout << (a == b) << '\n';
  std::cout << (a != b) << '\n';
  std::cout << (a < b) << '\n';
  std::cout << (a <= b) << '\n';
  std::cout << (a > b) << '\n';
  std::cout << (a >= b) << '\n';
}

template	<class It, class _It>
void	print_it(It first, _It last)
{
  unsigned int	count = 0;
  for (It it = first; it != last; ++it)
  {
    std::cout << count << ": " << *it << '\n';
    ++count;
  }
}

template	<class Container>
void	print_all(Container cont)
{
  print_it(cont.begin(), cont.end());
  std::cout << "size: " << cont.size() << "\n\n";
}

template	<class Container>
void	fill_int(Container& cont, int first, int diff)
{
  for (typename Container::iterator it = cont.begin(); it != cont.end(); ++it)
  {
    *it = first;
    first += diff;
  }
}

template	<class Container, typename Tp>
void	fill_type(Container& cont, Tp first, Tp diff)
{
  for (typename Container::iterator it = cont.begin(); it != cont.end(); ++it)
  {
    *it = first;
    first += diff;
  }
}

template	<typename T>
class	wrapper;

template	<typename T>
std::ostream	operator<<(std::ostream os, wrapper<T> wrap);

template	<typename T>
bool	operator==(wrapper<T> lhs, wrapper<T> rhs);

template	<typename T>
class	wrapper
{
  T		content_;
  bool	verbose_;

public:
  wrapper(T content = T(), bool verbose = false): content_(content), verbose_(verbose)
  { if (verbose_) std::cout << "wrapper constructed" << '\n'; };

  wrapper(wrapper const& a): content_(a.content_), verbose_(a.verbose_)
  { if (verbose_) std::cout << "wrapper copy-constructed" << '\n'; };

  ~wrapper()
  { if (verbose_) std::cout << "wrapper destructed" << '\n'; };

  operator int() const
  { return content_; }

  wrapper&	operator=(wrapper const& a)
  {
    this->content_ = a.content_; this->verbose_ = a.verbose_;
    if (verbose_) std::cout << "wrapper assigned" << '\n';
    return (*this);
  };

  friend std::ostream&	operator<<(std::ostream& os, wrapper wrap)
  {
    os << wrap.content_;
    return (os);
  };

  friend bool	operator==(wrapper lhs, wrapper rhs)
  { return (lhs.content_ == rhs.content_); };
};

class	A {};

struct Leaky {
  std::string* a;
  Leaky();
  Leaky(std::string str);
  Leaky(const Leaky& a);
  Leaky&  operator=(const Leaky& a);
  ~Leaky();
};

Leaky::Leaky() {
  a = new std::string(" Leaky");
}

Leaky::Leaky(std::string str) {
  a = new std::string(str + " Leaky");
}

Leaky::Leaky(const Leaky& a) {
  this->a = new std::string(*a.a);
}

Leaky& Leaky::operator=(const Leaky& a) {
  delete this->a;
  this->a = new std::string(*a.a);
  return *this;
}

Leaky::~Leaky() {
  delete a;
}

bool	operator==(const Leaky& lhs, const Leaky& rhs)
{
  return (*lhs.a == *rhs.a);
}
bool	operator!=(const Leaky& lhs, const Leaky& rhs)
{
  return (*lhs.a != *rhs.a);
}
bool	operator<(const Leaky& lhs, const Leaky& rhs)
{
  return (*lhs.a < *rhs.a);
}
bool	operator<=(const Leaky& lhs, const Leaky& rhs)
{
  return (*lhs.a <= *rhs.a);
}
bool	operator>(const Leaky& lhs, const Leaky& rhs)
{
  return (*lhs.a > *rhs.a);
}
bool	operator>=(const Leaky& lhs, const Leaky& rhs)
{
  return (*lhs.a >= *rhs.a);
}

namespace	test
{
  template	<typename Arg1, typename Arg2, typename Result>
  struct	binary_function
  {
    typedef Arg1	first_argument_type;
    typedef Arg2	second_argument_type;
    typedef Result	result_type;
  };

  template	<typename Tp = void>
  struct	less : public binary_function<Tp, Tp, bool>
  {
    bool	operator()(Tp const& x, Tp const& y) const
    { return (x < y); };
  };

  template	<bool B, typename T = void>
  struct	enable_if
  {};

  template	<typename T>
  struct	enable_if<true, T>
  { typedef T	type; };

  template	<typename T, typename U>
  struct	is_same
  { static const bool value = false; };

  template	<typename T>
  struct	is_same<T, T>
  { static const bool value = true; };
}

typedef NS::vector<A, std::allocator<A> >	vecA;
typedef NS::vector<int>						vecInt_o;
typedef NS::vector<wrapper<int> >			vecInt;
typedef NS::vector<std::string>				vecStr;
typedef NS::vector<float>					vecFloat_o;
typedef NS::vector<wrapper<float> >			vecFloat;
typedef NS::vector<vecA::size_type>		vecSize;

template	<typename Tp>
void	receive_vector(NS::vector<Tp>) {}
#include <vector>

int	main()
{
	vecInt	i4(4);
	vecInt	i7(7);

	fill_int(i4, 0, 4);
	fill_int(i7, 7, 3);

	vecInt::iterator	it_7b = i7.begin();
	vecInt::iterator	it_7e = i7.end();
	print_it(it_7b, it_7e);

	vecInt::const_iterator	cit_7b = i7.begin();
	vecInt::const_iterator	cit_7e = i7.end();
	print_it(cit_7b, cit_7e);

	vecInt::reverse_iterator	rit_4b = i4.rbegin();
	vecInt::reverse_iterator	rit_4e = i4.rend();
	print_it(rit_4b, rit_4e);

	vecInt::const_reverse_iterator	crit_4b = i4.rbegin();
	vecInt::const_reverse_iterator	crit_4e = i4.rend();
	print_it(crit_4b, crit_4e);

	print_it(it_7b, cit_7e); // iterator and const_iterator should be comparable
	print_it(rit_4b, crit_4e); // this also applys to reverse iterators
	print_it(cit_7b, it_7e);
	print_it(crit_4b, rit_4e);

	return (0);
}
