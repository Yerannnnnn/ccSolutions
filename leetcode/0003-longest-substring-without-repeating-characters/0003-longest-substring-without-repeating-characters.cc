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
  // normal
  int lengthOfLongestSubstring0(string s)
  {
    int length = s.size();
    if (length == 0)
      return 0;
    int idx_a        = 0;
    int idx_b        = 1;
    int distance     = 1;
    int max_distance = 1;

    while (idx_a <= length - 1 - max_distance) {
      unordered_set<char> _set;
      _set.emplace(s[idx_a]);

      idx_b = idx_a + 1;
      while (idx_b <= length - 1) {
        distance = idx_b - idx_a + 1;

        _set.emplace(s[idx_b]);
        if (_set.size() != distance) {
          break;
        } else if (distance > max_distance) {
          max_distance = distance;
        }

        ++idx_b;
      }

      while (s[idx_a] != s[idx_b]) {
        ++idx_a;
      }
      ++idx_a;
    }
    return max_distance;
  }
  // 使用map， 不需要循环查找a的移动目标
  int lengthOfLongestSubstring1(string s)
  {
    int length = s.size();
    if (length == 0)
      return 0;
    int idx_a        = 0;
    int idx_b        = 1;
    int idx_a_move   = 0;
    int distance     = 1;
    int max_distance = 1;

    while (idx_a <= length - 1 - max_distance) {
      unordered_map<char, int> _map;
      _map.emplace(s[idx_a], idx_a);

      idx_b      = idx_a + 1;
      idx_a_move = 0;
      while (idx_b <= length - 1) {
        char& val_b = s[idx_b];
        char& val_a = s[idx_a];

        if (_map.end() != _map.find(val_b)) {
          idx_a_move = _map[val_b] + 1;
          break;
        } else {
          _map.emplace(val_b, idx_b);
          distance = idx_b - idx_a + 1;
          if (distance > max_distance) {
            max_distance = distance;
          }
        }

        ++idx_b;
      }
      idx_a = idx_a_move ? idx_a_move : idx_a + 1;
    }
    return max_distance;
  }
  // 使用map.erase 单层循环， 不用多次重复构造map
  int lengthOfLongestSubstring2(string s)
  {
    int length = s.size();
    if (length == 0) {
      return 0;
    }
    int idx_a        = 0;
    int idx_b        = 0;
    int distance     = 1;
    int max_distance = 1;

    unordered_map<char, int> _map;

    while ((idx_a < length - max_distance) && (idx_b < length)) {
      if (_map.end() == _map.find(s[idx_b]))
      // if (!_map.contains(s[idx_b])) //need cxx20
      {
        _map.emplace(s[idx_b], idx_b);
        distance     = idx_b - idx_a + 1;
        max_distance = max(max_distance, distance);
        idx_b++;
      } else {
        int idxab = _map[s[idx_b]];
        while (idx_a <= idxab) {
          _map.erase(s[idx_a]);
          idx_a++;
        }
      }
    }
    return max_distance;
  }
  // 不需要erase 看key-value的value是否大于idx_a即可
  int lengthOfLongestSubstring3(string s)
  {
    int length = s.size();
    if (length == 0) {
      return 0;
    }
    int idx_a        = 0;
    int idx_b        = 0;
    int max_distance = 1;

    unordered_map<char, int> _map;
    while ((idx_a < length - max_distance) && (idx_b < length)) {
      if ((_map.end() == _map.find(s[idx_b])) || _map[s[idx_b]] < idx_a) {
        _map[s[idx_b]] = idx_b;
        max_distance   = max(max_distance, idx_b - idx_a + 1);
        idx_b++;
      } else {
        idx_a = _map[s[idx_b]] + 1;
      }
    }
    return max_distance;
  }
  // 桶优化map 使用数字替代map
  int lengthOfLongestSubstring(string s)
  {
    int length = s.size();
    if (length == 0) {
      return 0;
    }
    int idx_a        = 0;
    int idx_b        = 0;
    int max_distance = 1;

    std::vector<int> _map(128, -1);
    while ((idx_a < length - max_distance) && (idx_b < length)) {
      if (_map[s[idx_b]] < idx_a) {
        _map[s[idx_b]] = idx_b;
        max_distance   = max(max_distance, idx_b - idx_a + 1);
        idx_b++;
      } else {
        idx_a = _map[s[idx_b]] + 1;
      }
    }
    return max_distance;
  }
};

int main(int argc, char const* argv[])
{
  std::vector<std::string> v;
  v.emplace_back("abcabcbb");  // 3
  v.emplace_back("au");        // 2
  v.emplace_back("bbbbb");     // 1
  v.emplace_back("pwwkew");    // 3
  Solution sol;

  int cnt = 0;
  for (auto&& i : v) {
    // build

    // run
    auto result = sol.lengthOfLongestSubstring(i);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}

// 0             | 2000 ms
// 1             | 2000 ms
// 2             | 2000 ms
// 3 map noerase | 88   ms
// 4 桶 vector   | 8    ms
