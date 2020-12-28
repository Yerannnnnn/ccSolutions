#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
class Solution
{
 public:
  bool isValid(string s)
  {
    stack<char> _stack;
    _stack.push('*');
    for (auto&& i : s) {
      switch (i) {
        case '(':
        case '[':
        case '{': {
          _stack.push(i);
        } break;
        case ')':
          if (_stack.top() == '(') {
            _stack.pop();
            continue;
          } else {
            return false;
          }
        case ']':
          if (_stack.top() == '[') {
            _stack.pop();
            continue;
          } else {
            return false;
          }
        case '}':
          if (_stack.top() == '{') {
            _stack.pop();
            continue;
          } else {
            return false;
          }
        default: continue;
      }
    }
    return _stack.top() == '*';
  }
  bool isValid2(string s)
  {
    stack<char>     _stack;
    map<char, char> _map = {
      std::pair<char, char>{')', '('}, {']', '['}, {'}', '{'}};
    for (auto&& i : s) {
      if (_map.find(i) == _map.end()) {
        if (i != ' ') {
          _stack.push(i);
        }
      } else {
        if (_stack.empty() || (_stack.top() != _map[i])) {
          return false;
        } else {
          _stack.pop();
        }
      }
    }
    return _stack.empty();
  }

  // replace
  bool isValid3(string s)
  {
    // clear ' '
    // clear [] {} ()
    for (auto pos = s.find(" "); pos != std::string::npos; pos = s.find(" ")) {
      s.replace(pos, 1, "");
    }

    size_t length;
    do {
      length = s.length();
      for (auto pos = s.find("()"); pos != std::string::npos;
           pos      = s.find("()")) {
        s.replace(pos, 2, "");
      }
      for (auto pos = s.find("[]"); pos != std::string::npos;
           pos      = s.find("[]")) {
        s.replace(pos, 2, "");
      }
      for (auto pos = s.find("{}"); pos != std::string::npos;
           pos      = s.find("{}")) {
        s.replace(pos, 2, "");
      }
    } while (length != s.length());

    return s.length() == 0;
  }
};

int main(int argc, char const* argv[])
{
  std::vector<std::string> v;
  v.emplace_back("()()[]{} {([])}");
  v.emplace_back("()()[]{} {([)]}");
  v.emplace_back("()()[]{} {([])}{");
  v.emplace_back("()()[]{} {([])");
  Solution sol;

  for (auto&& i : v) {
    if (sol.isValid3(i))
      cout << "isValid " << endl;
    else
      cout << "is not Valid " << endl;
  }

  return 0;
}
