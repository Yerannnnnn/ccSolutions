#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
class Solution
{
 public:
  string convert0(string s, int numRows)
  {
    if (numRows < 2)
      return s;

    // prepare
    vector<vector<char>> v;
    for (int i = 0; i < numRows; ++i) {
      v.emplace_back(vector<char>{});
    }

    // covert

    std::string::iterator cur = s.begin();
    std::string::iterator end = s.end();

    bool z_down = true;
    int  idx    = 0;
    while (cur != end) {
      v[idx].emplace_back(*cur);
      ++cur;
      if (z_down) {
        if (idx == numRows - 1) {
          z_down = false;
          --idx;
        } else {
          ++idx;
        }
      } else {
        if (idx == 0) {
          z_down = true;
          ++idx;
        } else {
          --idx;
        }
      }
    }

    // result
    string result("");
    for (auto&& i : v) {
      for (auto&& j : i) {
        result += j;
      }
    }

    return result;
  }
  string convert(string s, int numRows)
  {
    if (numRows < 2)
      return s;

    // prepare
    vector<string> v(min(numRows,int(s.size())));

    // covert

    std::string::iterator cur = s.begin();
    std::string::iterator end = s.end();

    bool z_down = true;
    int  idx    = 0;
    while (cur != end) {
      v[idx] += *cur;
      ++cur;
      if (z_down) {
        if (idx == numRows - 1) {
          z_down = false;
          --idx;
        } else {
          ++idx;
        }
      } else {
        if (idx == 0) {
          z_down = true;
          ++idx;
        } else {
          --idx;
        }
      }
    }

    // result
    string result("");
    for (auto&& i : v) {
      result += i;
    }

    return result;
  }
};

int main(int argc, char const* argv[])
{
  Solution                            sol;
  std::vector<pair<std::string, int>> v;
  v.emplace_back(make_pair(string("AB"), 2));                // AB
  v.emplace_back(make_pair(string("LEETCODEISHIRING"), 3));  // LCIRETOESIIGEDHN
  /*
   L   C   I   R
   E T O E S I I G
   E   D   H   N
  */
  v.emplace_back(make_pair(string("LEETCODEISHIRING"), 4));  // LDREOEIIECIHNTSG
  /*
   L     D     R
   E   O E   I I
   E C   I H   N
   T     S     G
  */

  int cnt = 0;
  for (auto&& i : v) {
    // build

    // run
    auto result = sol.convert(i.first, i.second);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}
