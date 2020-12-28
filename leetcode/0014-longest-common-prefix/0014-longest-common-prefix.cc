
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

#define solution_function_name longestCommonPrefix

class Solution
{
 public:
  string solution_function_name(vector<string>& strs)
  {
    string r = strs.size() ? strs[0] : "";
    for (auto s : strs) {
      while (s.substr(0, r.size()) != r) {
        r = r.substr(0, r.size() - 1);
        if (r == "")
          return r;
      }
    }
    return r;
  }
};

int main(int argc, char const* argv[])
{
  Solution                         sol;
  std::vector<std::vector<string>> v{};
  v.emplace_back(vector<string>{"flower", "flow", "flight"});  // fl
  v.emplace_back(vector<string>{"dog", "racecar", "car"});     //

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
