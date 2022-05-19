#include "vector"
#include <vector>
int main() {
  ft::vector<int> a;
  a.size();
  a.capacity();
  a.resize(5, 1);
  a.push_back(6);
  a.pop_back();
  a.insert(a.begin(), 1);
  a.erase(a.end() - 1);
  a.empty();
  a.assign(4, 5);
}
