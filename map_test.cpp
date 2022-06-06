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

typedef ft::map<char, float> _map;
typedef ft::map<char, float>::const_iterator const_it;

void	ft_comp(const _map &mp, const const_it &it1, const const_it &it2)
{
  bool res[2];
int i = 0;
  std::cout << "\t-- [" << ++i << "] --" << std::endl;
  res[0] = mp.key_comp()(it1->first, it2->first);
  res[1] = mp.value_comp()(*it1, *it2);
  std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
  std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

int		main(void) {
  ft::map<char, float> mp;

  mp['a'] = 2.3;
  mp['b'] = 1.4;
  mp['c'] = 0.3;
  mp['d'] = 4.2;

  for (const_it it1 = mp.begin(); it1 != mp.end(); ++it1)
    for (const_it it2 = mp.begin(); it2 != mp.end(); ++it2)
      ft_comp(mp, it1, it2);

  return (0);
}
