#include "stack.hpp"
#include <stack>
#include <string>
#include <iostream>

int main() {
  ft::stack<std::string> st;

  std::cout << st.empty() << std::endl;
  st.push("asdf");
  std::cout << st.empty() << std::endl;
  std::cout << st.top() << std::endl;
  st.push("zxcv");
  std::cout << st.top() << std::endl;
  st.pop();
  std::cout << st.top() << std::endl;
  std::cout << st.size() << std::endl;

  const ft::stack<std::string> cp(st);
  ft::stack<std::string> as = cp;

  as.push("1234");

  std::cout << st.top() << "\n" << cp.top() << "\n" << as.top() << std::endl;
}
