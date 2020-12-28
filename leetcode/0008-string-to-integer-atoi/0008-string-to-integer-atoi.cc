#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

class Automaton
{
  string state = "start";

  // clang-format off
  unordered_map<string, vector<string>> table = {
    {"start"     , {"start" , "signed" , "in_number" , "end"}},
    {"signed"    , {"end"   , "end"    , "in_number" , "end"}},
    {"in_number" , {"end"   , "end"    , "in_number" , "end"}},
    {"end"       , {"end"   , "end"    , "end"       , "end"}}
  };
  // clang-format on

  int get_col(char c)
  {
    if (isspace(c))
      return 0;
    else if ((c == '+') || (c == '-'))
      return 1;
    else if (isdigit(c))
      return 2;
    else
      return 3;
  }

 public:
  int       sign = 1;
  long long ans  = 0;

  void get(char c)
  {
    state = table[state][get_col(c)];
    if (state == "in_number") {
      ans = ans * 10 + c - '0';
      ans = sign == 1 ? min(ans, (long long) INT_MAX)
                      : min(ans, -(long long) INT_MIN);
    } else if (state == "signed") {
      sign = c == '+' ? 1 : -1;
    }
  }
};

class Solution
{
 public:
  int myAtoi0(string str)
  {
    // trim first
    // str.trim();
    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    if (str.empty()) {
      return 0;
    }

    auto&     _first = str[0];
    int       signal = 1;
    long long result = 0;
    auto      cur    = str.begin();
    auto      end    = str.end();

    if (!((isdigit(_first) || (_first == '+') || (_first == '-')))) {
      return 0;
    }

    if (_first == '+') {
      signal = 1;
      ++cur;
    } else if (_first == '-') {
      signal = -1;
      ++cur;
    }

    while (cur != end) {
      auto&& _entry = *cur;
      if (isdigit(_entry)) {
        auto&& pop = int(_entry - '0');
        result     = 10 * result + pop;
        ++cur;
        if (signal == 1) {
          if (result > INT_MAX)
            return INT_MAX;
        } else {
          if (-result < INT_MIN)
            return INT_MIN;
        }
      } else {
        return signal * result;
      }
    }
    return signal * result;
  }
  int myAtoi(string str)
  {
    Automaton automaton;
    for (char c : str)
      automaton.get(c);
    return automaton.sign * automaton.ans;
  }
};

int main(int argc, char const* argv[])
{
  Solution            sol;
  std::vector<string> v;
  v.emplace_back("-2147483648");      // -2147483648  (INT_MIN -2^31)
  v.emplace_back("-91283472332");     // -2147483648  (INT_MIN -2^31)
  v.emplace_back("42");               // 42
  v.emplace_back("  -42");            // -42
  v.emplace_back("4193 with words");  // 4193
  v.emplace_back("words and 987");    // 0

  int cnt = 0;
  for (auto&& i : v) {
    // build

    // run
    auto result = sol.myAtoi(i);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}

//Automaton
