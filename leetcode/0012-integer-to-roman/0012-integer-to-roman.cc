
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

#define solution_function_name intToRoman

class Solution
{
 public:
  string solution_function_name(int num)
  {
    const vector<string> table_thousands = {"", "M", "MM", "MMM"};
    const vector<string> table_hundreds  = {
      "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const vector<string> table_tens = {
      "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const vector<string> table_ones = {
      "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    vector<int> gsbq = {0, 0, 0, 0};

    auto ptr = gsbq.begin();

    while (num) {
      *ptr++ = num % 10;
      num    = num / 10;
    }

    return table_thousands[gsbq[3]] + table_hundreds[gsbq[2]]
           + table_tens[gsbq[1]] + table_ones[gsbq[0]];
  }
};

int main(int argc, char const* argv[])
{
  Solution         sol;
  std::vector<int> v{};
  v.emplace_back(3);     // "III"
  v.emplace_back(4);     // "IV"
  v.emplace_back(9);     // "IX"
  v.emplace_back(58);    // "LVIII"
  v.emplace_back(1994);  // "MCMXCIV"

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
