#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

class MyQueue
{
 private:
  stack<int> input;
  stack<int> output;

 private:
  void moveAtoB(stack<int>& a, stack<int>& b)
  {
    while (!a.empty()) {
      b.push(a.top());
      a.pop();
    }
  }
  void move_to_input() { moveAtoB(output, input); }
  void move_to_output() { moveAtoB(input, output); }

 public:
  /** Initialize your data structure here. */
  MyQueue() {}

  /** Push element x to the back of queue. */
  void push(int x)
  {
    move_to_input();
    input.push(x);
  }

  /** Removes the element from in front of queue and returns that element. */
  int pop()
  {
    if (empty())
      return 0;
    move_to_output();
    auto ret = output.top();
    output.pop();
    return ret;
  }

  /** Get the front element. */
  int peek()
  {
    if (empty())
      return 0;
    move_to_output();
    return output.top();
  }

  /** Returns whether the queue is empty. */
  bool empty() { return output.empty() && input.empty(); }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main(int argc, char const* argv[])
{
  MyQueue* obj = new MyQueue();
  obj->push(1);
  obj->push(2);
  int  param_0 = obj->pop();
  int  param_1 = obj->pop();
  int  param_2 = obj->peek();
  bool param_3 = obj->empty();
  obj->push(3);
  bool param_4 = obj->empty();
  int  param_5 = obj->peek();

  return 0;
}
