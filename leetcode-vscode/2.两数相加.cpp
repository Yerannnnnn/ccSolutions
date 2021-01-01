/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
 *
 * https://leetcode-cn.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (39.18%)
 * Likes:    5451
 * Dislikes: 0
 * Total Accepted:    665.8K
 * Total Submissions: 1.7M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 *
 * 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
 *
 * 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 * 示例：
 *
 * 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 * 输出：7 -> 0 -> 8
 * 原因：342 + 465 = 807
 *
 *
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
  {
    int        cur_sum = 0;
    int        cur_c   = 0;
    ListNode*  result  = nullptr;
    ListNode** cur     = &result;

    // auto _val  = [](const ListNode* node) { return node ? (node->val) : 0; };
    // auto _push = [&]() {l1 = l1 ? l1->next : l1; l2 = l2 ? l2->next : l2; };
    #define _val(node)  (node ? (node->val) : 0)
    #define _push() l1 = (l1 ? l1->next : l1); l2 = (l2 ? l2->next : l2);

    while (l1 || l2 || cur_c) {
      cur_sum = _val(l1) + _val(l2) + cur_c;

      *cur = new ListNode((cur_sum) % 10);

      cur_c = cur_sum / 10;

      cur = &((*cur)->next);

      _push();
    }
    return result;
  }
};
// @lc code=end

