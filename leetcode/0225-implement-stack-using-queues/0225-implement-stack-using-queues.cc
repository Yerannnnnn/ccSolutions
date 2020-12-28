#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

class MyStack
{
 private:
  queue<int> ping;
  queue<int> pang;
  bool       take_top;
  int        tmp_top;
  bool       ping_pang;

 private:
  int pop_atob(queue<int>& a, queue<int>& b)
  {
    // we should flush a to b
    while (a.size() > 1) {
      b.push(a.front());
      a.pop();
    }
    // now we should return a.front()
    tmp_top = a.front();
    a.pop();
    return tmp_top;
  }

 public:
  /** Initialize your data structure here. */
  MyStack() : take_top(false), tmp_top(-1), ping_pang(true) {}

  /** Push element x onto stack. */
  void push(int x)
  {
    queue<int>& main_queue = ping_pang ? ping : pang;
    if (take_top) {
      take_top = false;
      main_queue.push(tmp_top);
    }
    main_queue.push(x);
  }

  /** Removes the element on top of the stack and returns that element. */
  int pop()
  {
    if (empty()) {
      return 0;
    }

    if (take_top) {
      take_top = false;
      return tmp_top;
    } else {
      queue<int>& main_queue   = ping_pang ? ping : pang;
      queue<int>& helper_queue = ping_pang ? pang : ping;
      ping_pang                = !ping_pang;
      return pop_atob(main_queue, helper_queue);
    }
  }

  /** Get the top element. */
  int top()
  {
    if (empty()) {
      return 0;
    }

    if (take_top) {
      return tmp_top;
    } else {
      queue<int>& main_queue   = ping_pang ? ping : pang;
      queue<int>& helper_queue = ping_pang ? pang : ping;
      ping_pang                = !ping_pang;
      take_top                 = true;
      return pop_atob(main_queue, helper_queue);
    }
  }

  /** Returns whether the stack is empty. */
  bool empty() { return ping.empty() && pang.empty() && (!take_top); }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main(int argc, char const* argv[])
{
  MyStack* obj = new MyStack();
  obj->push(1);
  obj->push(2);
  int  param_0 = obj->pop();
  int  param_1 = obj->pop();
  int  param_2 = obj->top();
  bool param_3 = obj->empty();
  obj->push(3);
  bool param_4 = obj->empty();
  int  param_5 = obj->top();

  return 0;
}
