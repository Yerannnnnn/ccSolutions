#include <iostream>
#include <algorithm>
#include <cmath>
#include <functional>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 public:
  // min(a+b+c-target)
  int threeSumClosest(vector<int>& nums, int target)
  {
    int length = nums.size();
    if (length == 3)
      return nums[0] + nums[1] + nums[2];

    // sort it
    std::sort(nums.begin(), nums.end());

    int min = nums[0] + nums[1] + nums[2];
    if (min >= target)
      return min;

    int max = nums[length - 1] + nums[length - 2] + nums[length - 3];
    if (max <= target)
      return max;

    // init
    int result  = min;
    int min_abs = abs(min - target);

    // find min(a+b+c-target)
    for (int idx_a = 0; idx_a <= length - 1; ++idx_a) {
      int var_a = nums[idx_a];

      // if (min_abs == 0)
      //   return result;
      if (3 * var_a - target >= min_abs)
        return result;

      if (idx_a && nums[idx_a - 1] == var_a)
        continue;

      // init b c
      int idx_b = idx_a + 1;
      int idx_c = length - 1;

      while (idx_b < idx_c) {
        int _sum = var_a + nums[idx_b] + nums[idx_c];
        int _abs = abs(_sum - target);
        if (_abs < min_abs) {
          result  = _sum;
          min_abs = _abs;
          if (min_abs == 0)
            return result;
        } else if (var_a + 2 * nums[idx_b] - target >= min_abs) {
          break;
        }

        if (nums[idx_b] == nums[idx_c])
          break;

        if (_sum < target) {
          do {
            ++idx_b;
          } while ((idx_b < idx_c) && (nums[idx_b] == nums[idx_b - 1]));
        } else if (_sum > target) {
          do {
            --idx_c;
          } while ((idx_b < idx_c) && (nums[idx_c] == nums[idx_c + 1]));
        }
      }
    }

    return result;
  }
};

int main(int argc, char const* argv[])
{
  vector<std::pair<std::vector<int>, int>> v;

  v.emplace_back(vector<int>{-1, 2, 1, -4}, 1);                  // 2
  v.emplace_back(vector<int>{0, 1, 2}, 3);                       // 3
  v.emplace_back(vector<int>{1, 2, 4, 8, 16, 32, 64, 128}, 82);  // 82
  v.emplace_back(vector<int>{-1, 0, 1, 1, 55}, 3);               // 2

  Solution sol;
  int      cnt = 0;
  for (auto&& i : v) {
    auto result = sol.threeSumClosest(i.first, i.second);
    cout << "problem" << cnt++ << ": ";
    cout << result;
    cout << endl;
  }

  return 0;
}

// solution3 | 292 ms | 7.5 MB
// solution4 | 8 ms   | 8.4 MB
