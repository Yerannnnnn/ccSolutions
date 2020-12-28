#include <iostream>
#include <map>
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
  // hash map
  bool hasCycle(ListNode* head)
  {
    map<ListNode*, bool> pool;
    ListNode*            node = head;
    while (node != NULL) {
      if (pool[node] == true)
        return true;
      pool[node] = true;
      node       = node->next;
    }
    return false;
  }
  // double pointer
  bool hasCycle2(ListNode* head)
  {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;

      if (slow == fast)
        return true;
    }
    return false;
  }
};

void addcycle(ListNode* head, int cycle_entry)
{
  ListNode* node  = head;
  ListNode* tail  = nullptr;
  ListNode* entry = nullptr;
  int       i     = 0;
  while (node) {
    if (i == cycle_entry) {
      entry = node;
    }
    tail = node;
    node = node->next;
    i++;
  }
  tail->next = entry;
}
int main(int argc, char const* argv[])
{
  const unsigned int linkListLength = 6;
  ListNode*          head           = nullptr;
  ListNode**         cur            = &head;
  ListNode*          node_helper[linkListLength];

  // create
  for (int i = 0; i < linkListLength; ++i) {
    *cur           = new ListNode(i);
    node_helper[i] = *cur;
    cur            = &((*cur)->next);
  }

  cout << head;

  addcycle(head, 3);

  Solution sol;
  if (sol.hasCycle(head))
    cout << "has cycle" << endl;
  else
    cout << "no cycle" << endl;

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
  auto                 _rm = [](ListNode* node) { return true; };
  map<ListNode*, bool> pool;
  for (ListNode** cur = &head; *cur;) {
    ListNode* entry = *cur;
    if (_rm(entry)) {
      *cur = pool[entry->next] ? entry->next : nullptr;
      delete entry;
    } else
      cur = &(entry->next);
    pool[entry] = true;
  }

  cout << head;

  return 0;
}
