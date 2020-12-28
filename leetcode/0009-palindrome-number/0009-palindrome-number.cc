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
  bool isPalindrome0(int x)
  {
    // clang-format off
    if(x<0) return false;
    else if(x<10) return true;
    else if(x%10==0) return false;
    // clang-format on

    std::vector<int> v;
    int              tmp = x;
    while (tmp) {
      v.emplace_back(tmp % 10);
      tmp /= 10;
    }

    auto tail = v.end() - 1;
    auto head = v.begin();
    while (tail >= head) {
      if (*tail == *head) {
        ;
      } else {
        return false;
      }
      ++head;
      --tail;
    }

    return true;
  }
  bool isPalindrome(int x)
  {
    // clang-format offr
    if(x<0) return false;
    else if(x<10) return true;
    else if(x%10==0) return false;
    // clang-format on

    //构造x的前半段与后半段, 前半段为x, 后半段为val
    //若x位数为偶, 则若前后半段相等 true
    //若x位数为奇, 则前后半段若较长数/10 = 较短数, true
    //例 x = 12321, 则分为 123和12, 较长数的末位为对称轴
    int val = 0;
    for (; val * 10 <= x; x /= 10)
      val = val * 10 + x % 10;
    return (val == x || (val / 10 == x));
  }
};

int main(int argc, char const* argv[])
{
  Solution         sol;
  std::vector<int> v;
  v.emplace_back(0);     // true
  v.emplace_back(10);    // false
  v.emplace_back(11);    // true
  v.emplace_back(121);   // true
  v.emplace_back(-121);  // false
  v.emplace_back(10);    // false

  int cnt = 0;
  for (auto&& i : v) {
    // build

    // run
    auto result = sol.isPalindrome(i);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}

// Automaton
