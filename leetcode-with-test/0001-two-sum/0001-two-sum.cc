#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// #define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

using namespace std;
class Solution
{
   public:
    vector<int> twoSum1(vector<int>& nums, int target)
    {
        // solution1 for loop
        // solution2 std::map<int, int> map;
        // solution3 check front pool
        std::vector<int> front_pool;

        for (int x = 0; x < nums.size(); ++x) {
            for (int y = 0; y < front_pool.size(); ++y) {
                if (target == nums[x] + front_pool[y]) {
                    return {x, y};
                }
            }
            front_pool.push_back(nums[x]);
        }
        return {-1, -1};
    }
    vector<int> twoSum(vector<int>& nums, int target)
    {
        // solution1 for loop
        // solution2 std::map<int, int> map;
        // solution3 check front pool
        // solution4 unordered_map->front-pool
        unordered_map<int, int> front_pool;

        for (int x = 0; x < nums.size(); ++x) {
            if (front_pool.end() != front_pool.find(target - nums[x])) {
                return {front_pool[target - nums[x]], x};
            }
            front_pool[nums[x]] = x;
        }
        return {-1, -1};
    }
};
// solution3 | 292 ms | 7.5 MB
// solution4 | 8 ms   | 8.4 MB

Solution sol;
TEST_CASE("basic tests 1", "[test 1]") {
    INFO("Test case start");
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
    INFO("Test case start");
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
