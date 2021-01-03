/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 *
 * https://leetcode-cn.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (49.69%)
 * Likes:    9927
 * Dislikes: 0
 * Total Accepted:    1.6M
 * Total Submissions: 3.3M
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
 *
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
 *
 *
 *
 * 示例:
 *
 * 给定 nums = [2, 7, 11, 15], target = 9
 *
 * 因为 nums[0] + nums[1] = 2 + 7 = 9
 * 所以返回 [0, 1]
 *
 *
 */

// @lc code=start
using namespace std;
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

// #define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

Solution sol;
TEST_CASE("basic tests 1", "[test 1]") {
    vector<int32_t> vec{2, 7, 11, 15};
    auto result = sol.twoSum(vec, 9);
    SECTION("size is always 2") {
        CHECK(result.size() == 2);
    }
    SECTION("test cases") {
        CHECK_THAT(result, Catch::Matchers::UnorderedEquals<int>({0, 1}));
        CHECK_THAT(result, Catch::Matchers::Contains<int>({0, 1}));
    }
}

TEST_CASE("basic tests 2", "[test 2]") {
    vector<int32_t> vec{3, 2, 4};
    auto result = sol.twoSum(vec, 6);
    SECTION("size is always 2") {
        CHECK(result.size() == 2);
    }
    SECTION("test cases") {
        CHECK_THAT(result, Catch::Matchers::UnorderedEquals<int32_t>({1, 2}));
        CHECK_THAT(result, Catch::Matchers::Contains<int32_t>({}));
    }
}
