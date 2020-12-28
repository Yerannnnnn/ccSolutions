
#include <time.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define solution_function_name letterCombinations

class Solution
{
 public:
  vector<string> solution_function_name(string digits)
  {
    const string dict[10] = {   
      "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    if (digits.empty())
      return vector<string>();

    vector<string> res(1, "");
    for (auto& d : digits) {
      vector<string> tmp;
      for (auto c : dict[d - '2']) {
        for (auto s : res) {
          tmp.push_back(s + c);
        }
      }

      res = tmp;
    }
    return res;
  }
};

ostream& operator<<(ostream& os, const vector<string>& e)
{
  for (auto&& i : e) {
    os << i<<',';
  }
  return os;
}

int main(int argc, char const* argv[])
{
  Solution            sol;
  std::vector<string> v{};
  v.emplace_back("23");  // ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

  int cnt = 0;
  for (auto&& i : v) {
    // build
    const bool show_time = 0;
    // run
    clock_t _start   = clock();
    auto    result   = sol.solution_function_name(i);
    clock_t _stop    = clock();
    double  _time    = double(_stop - _start);
    double  _time_s  = (_time / CLOCKS_PER_SEC);
    double  _time_ms = _time_s * 1000.0;
    double  _time_ns = _time_ms * 1000.0;
    cout << "problem" << cnt++ << ": ";
    if (show_time)
      cout << _time_s << " s \n\t\t\t";
    else
      cout << "\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}

// Automaton
