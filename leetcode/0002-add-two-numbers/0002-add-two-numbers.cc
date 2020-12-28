#include "iostream"
#include <vector>
using namespace std;
// Definition for singly-linked list.
struct ListNode {
  int       val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(vector<int>& v) : val(v[0]), next(nullptr)
  {
    ListNode* cur = this;
    for (int i = 1; i < v.size(); ++i) {
      cur->next = new ListNode(v[i]);
      cur       = cur->next;
    }
  }
  void push_back(int x)
  {
    ListNode* cur = this;
    while (cur->next) {
      cur = cur->next;
    }
    cur->next = new ListNode(x);
  }
};

// use cout output linklist
inline std::ostream& operator<<(std::ostream& os, const ListNode* node)
{
  while (node) {
    os << node->val << "->";
    node = node->next;
  }
  os << "nullptr" << std::endl;

  return os;
}

class Solution
{
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
  {
    int        cur_sum = 0;
    int        cur_c   = 0;
    ListNode*  result  = nullptr;
    ListNode** cur     = &result;

    auto _val  = [](ListNode* node) { return node ? (node->val) : 0; };
    auto _push = [&]() {l1 = l1 ? l1->next : l1; l2 = l2 ? l2->next : l2; };

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

// clear
auto _delete_linklist = [](ListNode*& head) {
  auto _rm = [](ListNode* node) { return true; };
  for (ListNode** cur = &head; *cur;) {
    ListNode* entry = *cur;
    if (_rm(entry)) {
      *cur = entry->next;
      delete entry;
    } else
      cur = &(entry->next);
  }
};

int main(int argc, char const* argv[])
{
  std::vector<std::pair<std::vector<int>, std::vector<int>>> v;

  //(2 -> 4 -> 3) + (5 -> 6 -> 4)
  // 342 + 465 = 807
  v.emplace_back(make_pair(vector<int>{2, 4, 3}, vector<int>{5, 6, 4}));
  v.emplace_back(make_pair(vector<int>{2, 4, 3}, vector<int>{5, 6, 4, 1, 1}));
  v.emplace_back(make_pair(vector<int>{2, 4, 3}, vector<int>{0}));

  Solution sol;
  int      cnt = 0;
  for (auto&& i : v) {
    ListNode* l1 = new ListNode(i.first);
    ListNode* l2 = new ListNode(i.second);

    auto result = sol.addTwoNumbers(l1, l2);
    cout << "problem" << cnt++ << ":\n\t";
    cout << result;
    cout << endl;

    _delete_linklist(l1);
    _delete_linklist(l2);
  }

  return 0;
}
