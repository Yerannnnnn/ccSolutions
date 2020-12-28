#include "iostream"
using namespace std;
// Definition for singly-linked list.
struct ListNode {
  int       val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
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
  ListNode* reverseList(ListNode* head)
  {
    // init
    ListNode* prev = nullptr;
    ListNode* next = nullptr;

    while (head) {
      next       = head->next;
      head->next = prev;

      if (next) {
        prev = head;
        head = next;
      } else {
        break;
      }
    }

    return head;
  }
  ListNode* reverseList2(ListNode* head)
  {
    if ((head == nullptr)||(head->next == nullptr))
      return head;
    auto ret = reverseList2(head->next);

    head->next->next = head;
    head->next       = nullptr;

    return ret;
  }
};

int main(int argc, char const* argv[])
{
  const unsigned int linkListLength = 5;
  ListNode*          head           = new ListNode(0);
  ListNode**         cur            = &head->next;

  // create
  for (int i = 1; i < linkListLength + 1; ++i) {
    *cur = new ListNode(i);
    cur  = &((*cur)->next);
  }

  cout << head;

  Solution sol;
  head = sol.reverseList2(head);

  cout << head;

  /*
    // normal delete
    auto _rm = [](ListNode* node) { return (node->val % 2) == 0; };
    for (ListNode *prev = nullptr, *cursor = head; cursor != nullptr;) {
      ListNode* const next = cursor->next;
      if (_rm(cursor)) {
        if (prev)
          prev->next = next;
        else
          head = next;
        delete cursor;
      } else
        prev = cursor;
      cursor = next;
    }
  */
  // use node** delete
  // auto _rm = [](ListNode* node) { return (node->val % 2) == 0; };
  auto _rm = [](ListNode* node) { return true; };
  for (ListNode** cur = &head; *cur;) {
    ListNode* entry = *cur;
    if (_rm(entry)) {
      *cur = entry->next;
      delete entry;
    } else
      cur = &(entry->next);
  }

  cout << head;

  return 0;
}
