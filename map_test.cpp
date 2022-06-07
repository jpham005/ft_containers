#include "map.hpp"
#include <map>
#include "vector.hpp"
#include <vector>
#include <string>

//int main() {
//  ft::vector<ft::pair<int, std::string> >vec;
//  vec.push_back(ft::make_pair(1, "asdf"));
//  vec.push_back(ft::make_pair(2, "asdf"));
//  vec.push_back(ft::make_pair(3, "asdf"));
//  ft::map<int, std::string> asdf(vec.begin(), vec.end());
//  ft::map<int, std::string> cp(asdf);
//  ft::map<int, std::string> m;
//
//  m.insert(ft::make_pair(1, "ASDF"));
//  m.insert(ft::make_pair(2, "ASDF"));
//  m.insert(ft::make_pair(3, "ASDF"));
//  m.insert(ft::make_pair(4, "ASDF"));
//  m.insert(ft::make_pair(5, "ASDF"));
//  typedef ft::map<int, std::string>::iterator iter;
//
//  for (iter it = m.begin(); it != m.end(); it++) std::cout << it->first << ", " << it->second << std::endl;
//
//  std::map<int, int> a;
//  a.insert(std::make_pair(1, 1));
//  a.insert(std::make_pair(2, 1));
//  a.insert(std::make_pair(3, 1));
//
//  std::map<int, int> b;
//  b.insert(std::make_pair(1, 1));
//  b.insert(std::make_pair(2, 1));
//  b.insert(std::make_pair(3, 2));
//
//  std::cout << (a < b) << std::endl;
//
//  std::cout << m.at(000);
//}

//#include <list>
//int	main()
//{
//  std::list<ft::pair<int, std::string> >	lst;
//  lst.push_back(ft::pair<int, std::string>(4, "aaaaaaaaaaaaaaaa"));
//  lst.push_back(ft::pair<int, std::string>(3, "bbbbbbbbb"));
//  lst.push_back(ft::pair<int, std::string>(5, "ccccccccccccccccccccccccc"));
//  lst.push_back(ft::pair<int, std::string>(1, "d"));
//  lst.push_back(ft::pair<int, std::string>(2, "eeee"));
//
//  ft::map<int, std::string>	mp(lst.begin(), lst.end());
//
//  std::cout << mp.empty() << mp.size() << '\n';
//
//  ft::map<int, std::string>::size_type	size = mp.max_size();
//  (void)size;
//
//  std::cout << (mp[0] = "") << '\n';
//  int	i;
//  for (i = 0; i < 7; ++i)
//    std::cout << mp[i] << '\n';
//
//  std::cout << mp.empty() << mp.size() << '\n';
//
//  i = 0;
//  while (!mp.empty())
//    mp.erase(i++);
//
//  std::cout << mp.empty() << mp.size() << '\n';
//
//  return (0);
//}

#include <list>
template <
  typename Key, typename Value, typename ExtractKey,
  typename Compare, typename Allocator
>
void testprint(typename rbtree<Key, Value, ExtractKey, Compare, Allocator>::node *node, std::string dir) {

  if (!node->value_) { std::cout << "end"  << std::endl; return; }
  ExtractKey extractor;
  std::cout << " value: " << extractor(node->value_) << " color: ";
  if (node->color_ == kRBTreeColorBlack)
    std::cout << "black";
  else if (node->color_ == kRBTreeColorRed)
    std::cout << "red";
  else if (!node->value_)
    std::cout << "blue";
  else
    std::cout << "wrong";
  std::cout << " dir: " << dir << std::endl;
  testprint<Key, Value, ExtractKey, Compare, Allocator>(node->left_, "left");
  testprint<Key, Value, ExtractKey, Compare, Allocator>(node->right_, "right");
}
#define TESTED_NAMESPACE ft
template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
  o << "key: " << iterator->first << " | value: " << iterator->second;
  if (nl)
    o << std::endl;
  return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
  std::cout << "size: " << mp.size() << std::endl;
//	std::cout << "max_size: " << mp.max_size() << std::endl;
  if (print_content)
  {
    typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
    std::cout << std::endl << "Content is:" << std::endl;
    for (; it != ite; ++it)
      std::cout << "- " << printPair(it, false) << std::endl;
  }
  std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
  typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

  std::cout << "printReverse:" << std::endl;
  while (it != ite) {
    it--;
    std::cout << "-> " << printPair(it, false) << std::endl;
  }
  std::cout << "_______________________________________________" << std::endl;
}

#define T1 char
#define T2 int
#define _pair TESTED_NAMESPACE::pair
typedef _pair<const T1, T2> T3;

template <class MAP>
void	cmp(const MAP &lhs, const MAP &rhs)
{
  static int i = 0;

  std::cout << "############### [" << i++ << "] ###############"  << std::endl;
  std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
  std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
  std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		main(void)
{
  TESTED_NAMESPACE::map<T1, T2> mp1;
  TESTED_NAMESPACE::map<T1, T2> mp2;

  mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
  mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

  cmp(mp1, mp1); // 0
  cmp(mp1, mp2); // 1

  mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

  cmp(mp1, mp2); // 2
  cmp(mp2, mp1); // 3

  (++(++mp1.begin()))->second = 42;

  cmp(mp1, mp2); // 4
  cmp(mp2, mp1); // 5

  for (ft::map<T1, T2>::iterator it = mp1.begin(); it != mp1.end(); ++it)
    std::cout << it->first << ", " << it->second << std::endl;
  for (ft::map<T1, T2>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    std::cout << it->first << ", " << it->second << std::endl;

  swap(mp1, mp2);

  for (ft::map<T1, T2>::iterator it = mp1.begin(); it != mp1.end(); ++it)
    std::cout << it->first << ", " << it->second << std::endl;
  for (ft::map<T1, T2>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    std::cout << it->first << ", " << it->second << std::endl;
  cmp(mp1, mp2); // 6
  cmp(mp2, mp1); // 7

  return (0);
}
