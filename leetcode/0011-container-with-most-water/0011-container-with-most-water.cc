#include <iostream>
#include <time.h>

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

class Solution
{
 public:
  int maxArea(vector<int>& height)
  {
    auto l   = height.begin();
    auto r   = height.end() - 1;
    int  ans = 0;
    while (l < r) {
      auto& vl   = *l;
      auto& vr   = *r;
      int   area = min(vl, vr) * (r - l);
      ans        = max(ans, area);
      if (vl < vr) {
        ++l;
      } else if (vl > vr) {
        --r;
      } else {
        ++l;
        --r;
      }
    }
    return ans;
  }
};

int main(int argc, char const* argv[])
{
  Solution                 sol;
  std::vector<vector<int>> v;
  v.emplace_back(vector<int>{1, 8, 6, 2, 5, 4, 8, 3, 7});  // 8,7 7*7=49

  int cnt = 0;
  for (auto&& i : v) {
    // build
    const bool show_time = 0;
    // run
    clock_t _start   = clock();
    auto    result   = sol.maxArea(i);
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
