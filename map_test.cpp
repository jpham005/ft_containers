#include "map.hpp"
#include <map>
#include "vector.hpp"
#include <vector>
#include <string>

int main() {
  ft::vector<ft::pair<int, std::string> >vec;
  vec.push_back(ft::make_pair(1, "asdf"));
  vec.push_back(ft::make_pair(2, "asdf"));
  vec.push_back(ft::make_pair(3, "asdf"));
  ft::map<int, std::string> asdf(vec.begin(), vec.end());
  ft::map<int, std::string> cp(asdf);
  ft::map<int, std::string> m;

  m.insert(ft::make_pair(1, "ASDF"));
  m.insert(ft::make_pair(2, "ASDF"));
  m.insert(ft::make_pair(3, "ASDF"));
  m.insert(ft::make_pair(4, "ASDF"));
  m.insert(ft::make_pair(5, "ASDF"));
  typedef ft::map<int, std::string>::iterator iter;

  for (iter it = m.begin(); it != m.end(); it++) std::cout << it->first << ", " << it->second << std::endl;

  std::map<int, int> a;
  a.insert(std::make_pair(1, 1));
  a.insert(std::make_pair(2, 1));
  a.insert(std::make_pair(3, 1));

  std::map<int, int> b;
  b.insert(std::make_pair(1, 1));
  b.insert(std::make_pair(2, 1));
  b.insert(std::make_pair(3, 2));

  std::cout << (a < b) << std::endl;

  std::cout << m.at(000);
}
