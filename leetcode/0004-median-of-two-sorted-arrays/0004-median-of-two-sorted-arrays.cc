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
  double findMedianSortedArrays0(vector<int>& nums1, vector<int>& nums2)
  {
    int  size1 = nums1.size();
    int  size2 = nums2.size();
    int  mid   = (size1 + size2) / 2;
    bool odd   = (0 == (size1 + size2) % 2) ? false : true;  // 1 3 5

    if (size1 == 0) {
      return (0 == size2 % 2) ? ((nums2[size2 / 2 - 1] + nums2[size2 / 2]) / 2.0)
                              : (nums2[size2 / 2]);
    }

    if (size2 == 0) {
      return (0 == size1 % 2) ? ((nums1[size1 / 2 - 1] + nums1[size1 / 2]) / 2.0)
                              : (nums1[size1 / 2]);
    }

    std::vector<int>::iterator a = nums1.begin();
    std::vector<int>::iterator b = nums2.begin();

    std::vector<int>::iterator* pa = &a;
    std::vector<int>::iterator* pb = &b;

    bool swaped = false;
    for (int i = (odd ? 0 : 1); i < mid; ++i) {
      if ((**pa) <= (**pb)) {
        (*pa)++;
        if (!swaped) {
          if ((*pa) == nums1.end()) {
            pa     = pb;
            swaped = true;
          }
        }
      } else {
        (*pb)++;
        if (!swaped) {
          if ((*pb) == nums2.end()) {
            pb     = pa;
            swaped = true;
          }
        }
      }
    }

    bool select_a = (**pa <= **pb) ? true : false;

    if (odd) {
      return min(**pa, **pb);
    } else {
      if (select_a) {
        int left  = **pa;
        int right = 0;
        if ((++(*pa)) == nums1.end()) {
          right = **pb;
        } else {
          right = min(**pa, **pb);
        }
        return (left + right) / 2.0;
      } else {
        int left  = **pb;
        int right = 0;
        if ((++(*pb)) == nums2.end()) {
          right = **pa;
        } else {
          right = min(**pa, **pb);
        }
        return (left + right) / 2.0;
      }
    }
  }

  /**
   * 找第k大数
   */
  int getTopK(vector<int>& nums1, vector<int>& nums2, int k)
  {
    int begin1 = -1;
    int begin2 = -1;
    // 合并后数组前k个在两个数组所选择的数的最后一个元素的下标
    int end1 = nums1.size() - 1;
    int end2 = nums2.size() - 1;

    // 处理两个数组有一个是空数组的情况
    if (end1 < 0)
      return nums2[k - 1];
    if (end2 < 0)
      return nums1[k - 1];

    while (k > 0) {
      // 处理数组越界的情况
      if (begin1 + (k + 1) / 2 > end1) {
        begin2 += k - (end1 - begin1);
        k = (end1 - begin1);
        continue;
      }
      if (begin2 + (k + 1) / 2 > end2) {
        begin1 += k - (end2 - begin2);
        k = (end2 - begin2);
        continue;
      }

      // 更小的那段一定是属于合并后那前k个数
      if (nums1[begin1 + (k + 1) / 2] < nums2[begin2 + (k + 1) / 2])
        begin1 += (k + 1) / 2;
      else
        begin2 += (k + 1) / 2;

      k = k - (k + 1) / 2;
    }

    // 处理某个数组一个都不取的情况
    if (begin1 < 0)
      return nums2[begin2];
    if (begin2 < 0)
      return nums1[begin1];

    // begin1与begin2是各自的最后一个元素但是最终合并后数组中最大元素是两者更大的那个
    return max(nums1[begin1], nums2[begin2]);
  }

  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
  {
    int    k      = (nums1.size() + nums2.size() + 1) / 2;
    double median = (double) getTopK(nums1, nums2, k);
    if ((nums1.size() + nums2.size()) % 2 == 0) {
      median = (median + getTopK(nums1, nums2, k + 1)) / 2.0;
    }
    return median;
  }
};

int main(int argc, char const* argv[])

{
  std::vector<pair<vector<int>, vector<int>>> v;
  v.emplace_back(make_pair(vector<int>{}, vector<int>{2, 3}));
  v.emplace_back(make_pair(vector<int>{1, 3}, vector<int>{2, 4}));  // 2.5
  v.emplace_back(make_pair(vector<int>{1, 3}, vector<int>{2}));
  v.emplace_back(make_pair(vector<int>{1, 2}, vector<int>{3, 4}));

  Solution sol;

  int cnt = 0;
  for (auto&& i : v) {
    // build

    // run
    auto result = sol.findMedianSortedArrays(i.first, i.second);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}
