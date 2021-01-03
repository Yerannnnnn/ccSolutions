/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 *
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (36.08%)
 * Likes:    4769
 * Dislikes: 0
 * Total Accepted:    776.8K
 * Total Submissions: 2.2M
 * Testcase Example:  '"abcabcbb"'
 *
 * 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: s = "abcabcbb"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 *
 *
 * 示例 2:
 *
 *
 * 输入: s = "bbbbb"
 * 输出: 1
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
 *
 *
 * 示例 3:
 *
 *
 * 输入: s = "pwwkew"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 * 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 *
 *
 * 示例 4:
 *
 *
 * 输入: s = ""
 * 输出: 0
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0
 * s 由英文字母、数字、符号和空格组成
 *
 *
 */

// @lc code=start
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
  int lengthOfLongestSubstring(const string& s)
  {
    // ascii码 用int[128]可表示
    int length = s.size();
    if (length == 0) {
      return 0;
    }
    int idx_a        = 0;
    int idx_b        = 0;
    int max_distance = 1;// str = [a,b], dist = b-a+1

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
// @lc code=end

