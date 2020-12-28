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
  ListNode* swapPairs(ListNode* head)
  {
    if ((!head) || (!head->next))
      return head;

    ListNode* tail     = nullptr;
    ListNode* first    = head;
    ListNode* second   = nullptr;
    ListNode* nextnext = nullptr;

    while (first && first->next) {
      second       = first->next;
      nextnext     = second->next;
      second->next = first;

      if (!tail) {
        head = second;
      } else {
        tail->next = second;
      }
      first->next = nextnext;
      tail        = first;
      first       = nextnext;
    }

    return head;
  }

  // 添加空节点 避免判断头部 统一操作
  ListNode* swapPairs2(ListNode* head)
  {
    ListNode p(0);
    p.next         = head;
    ListNode* curr = &p;
    while (head != NULL && head->next != NULL) {
      ListNode* firstNode  = head;
      ListNode* secondNode = head->next;

      curr->next       = secondNode;
      firstNode->next  = secondNode->next;
      secondNode->next = firstNode;

      curr = firstNode;
      head = firstNode->next;
    }
    return p.next;
  }

  // 二级指针 消灭空节点
  ListNode* swapPairs3(ListNode* head)
  {
    ListNode** curr = &head;
    while ((*curr) != NULL && (*curr)->next != NULL) {
      ListNode* firstNode  = (*curr);
      ListNode* secondNode = (*curr)->next;

      (*curr)          = secondNode;
      firstNode->next  = secondNode->next;
      secondNode->next = firstNode;

      curr    = &(firstNode->next);
      (*curr) = firstNode->next;
    }
    return head;
  }

  // 递归
  ListNode* swapPairs4(ListNode* head)
  {
    if ((head == nullptr) || (head->next == nullptr))
      return head;
    ListNode* firstNode  = head;
    ListNode* secondNode = head->next;
    firstNode->next      = swapPairs(secondNode->next);
    secondNode->next     = firstNode;
    return secondNode;
  }
};

int main(int argc, char const* argv[])
{
  const unsigned int linkListLength = 6;
  ListNode*          head           = new ListNode(0);
  ListNode**         cur            = &head->next;

  // create
  for (int i = 1; i < linkListLength + 1; ++i) {
    *cur = new ListNode(i);
    cur  = &((*cur)->next);
  }

  cout << head;

  Solution sol;
  head = sol.swapPairs3(head);

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
