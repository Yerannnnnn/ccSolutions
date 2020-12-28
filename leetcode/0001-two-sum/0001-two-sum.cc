#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

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

int main(int argc, char const* argv[])
{
    std::vector<std::pair<std::vector<int>, int>> v;

    v.emplace_back(make_pair(vector<int>{2, 7, 11, 15}, 9));
    v.emplace_back(make_pair(vector<int>{2, 7, 11, 15}, 9));

    Solution sol;
    int      cnt = 0;
    for (auto&& i : v) {
        auto result = sol.twoSum(i.first, i.second);
        cout << "problem" << cnt++ << ": [";
        for (auto&& r : result) {
            cout << r << " ,";
        }
        cout << "]" << endl;
    }

    return 0;
}

// solution3 | 292 ms | 7.5 MB
// solution4 | 8 ms   | 8.4 MB
