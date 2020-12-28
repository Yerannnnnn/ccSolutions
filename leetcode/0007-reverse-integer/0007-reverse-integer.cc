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
class Solution
{
 public:
  int reverse0(int x)
  {
    int res = 0;  // res表示结果

    while (x != 0) {
      // clang-format off
      if (res > INT_MAX / 10) return 0;
      if (res < INT_MIN / 10) return 0;  //判断是否将要发生越界
      // clang-format on
      res = res * 10 + x % 10;
      x   = x / 10;
    }
    return res;
  }

  // 暴力字符串
  int reverse(int x)
  {
    string tmp = to_string(x);
    if (x >= 0)
      std::reverse(tmp.begin(), tmp.end());
    else
      std::reverse(tmp.begin() + 1, tmp.end());
    long long ans = stol(tmp);
    if (ans > INT_MAX || ans < INT_MIN)
      return 0;
    return ans;
  }
};

int main(int argc, char const* argv[])
{
  Solution         sol;
  std::vector<int> v;
  v.emplace_back(123);   // 321
  v.emplace_back(-123);  // -321
  v.emplace_back(120);   // 21

  int cnt = 0;
  for (auto&& i : v) {
    // build

    // run
    auto result = sol.reverse(i);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}
