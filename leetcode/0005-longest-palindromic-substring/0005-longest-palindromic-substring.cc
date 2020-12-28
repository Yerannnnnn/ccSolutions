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
  string longestPalindrome(string s)
  {
    if (s.length() < 1) {
      return "";
    }
    int start = 0, end = 0;

    // 计算以left和right为中心的回文串长度
    auto _expandAroundCenter = [](string s, int l, int r) -> int {
      while (l >= 0 && r < s.length() && s[l] == s[r]) {
        l--;
        r++;
      }
      return r - l - 1;
    };

    for (int i = 0; i < s.length(); i++) {
      int len1 = _expandAroundCenter(s, i, i);      //一个元素为中心
      int len2 = _expandAroundCenter(s, i, i + 1);  //两个元素为中心
      int len  = max(len1, len2);
      if (len > end - start) {
        start = i - (len - 1) / 2;
        end   = i + len / 2;
      }
    }
    return s.substr(start, end - start + 1);
  }
};

int main(int argc, char const* argv[])
{
  std::vector<std::string> v;
  v.emplace_back("babad");  // bab / aba
  v.emplace_back("cbbd");   // bb
  Solution sol;

  int cnt = 0;
  for (auto&& i : v) {
    // build

    // run
    auto result = sol.longestPalindrome(i);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}
