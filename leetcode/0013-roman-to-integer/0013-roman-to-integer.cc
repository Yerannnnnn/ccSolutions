
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

#define solution_function_name romanToInt

class Solution
{
 public:
  int solution_function_name(string s)
  {
    unordered_map<string, int> m = {{"I", 1}, {"IV", 3}, {"IX", 8}, {"V", 5},
      {"X", 10}, {"XL", 30}, {"XC", 80}, {"L", 50}, {"C", 100}, {"CD", 300},
      {"CM", 800}, {"D", 500}, {"M", 1000}};
    int                        r = m[s.substr(0, 1)];
    for (int i = 1; i < s.size(); ++i) {
      string two = s.substr(i - 1, 2);
      string one = s.substr(i, 1);
      r += m[two] ? m[two] : m[one];
    }
    return r;
  }
};

int main(int argc, char const* argv[])
{
  Solution            sol;
  std::vector<string> v{};
  v.emplace_back("III");      // 3
  v.emplace_back("IV");       // 4
  v.emplace_back("IX");       // 9
  v.emplace_back("LVIII");    // 58
  v.emplace_back("MCMXCIV");  // 1994

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
