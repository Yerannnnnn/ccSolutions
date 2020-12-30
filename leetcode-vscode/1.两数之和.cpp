/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    std::unordered_map<value, pos> pools;
    int idx = 0;

    for (auto &&cur : nums) {
      auto &&need = target - cur;
      auto &&itor = pools.find(need);
      if (itor != pools.end()) {
        return {itor->second, idx};
      }
      pools[cur] = idx++;
    }
    return {};
  }

  using value = int;
  using pos = int;
};

// @lc code=end
