
#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

static auto x = []() {
  //打断iostream输入输出到缓存，可以节约很多时间，使之与scanf相差无几。
  std::ios::sync_with_stdio(false);
  //解除cin与cout的绑定，避免每个<<都要flush
  std::cin.tie(0);
  return 0;
}();

class Foo
{
 protected:
  std::promise<void> m_step2;
  std::promise<void> m_step3;

 public:
  Foo()
  {
    // m_round=0;
    // m_step = 0;
    // m_step2=false;
    // m_step3=false;
  }

  // protected:
  //  mutex              m_mtx;
  //  condition_variable m_cv;

  // protected:
  //  atomic<int> m_round;

  // protected:
  //  bool m_step2;
  //  bool m_step3;

  void first(function<void()> printFirst)
  {
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    // m_round++;
    // m_step2=true;
    // m_cv.notify_all();
    m_step2.set_value();
  }

  void second(function<void()> printSecond)
  {
    m_step2.get_future().wait();
    // std::unique_lock<std::mutex> lk(m_mtx);
    // std::lock_guard<std::mutex> lk(m_mtx);
    // m_cv.wait(lk, [this] { return m_step2; });
    // while (m_round != 1) {
    //   std::this_thread::sleep_for(1ms);
    // }

    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    // m_step3=true;
    // m_cv.notify_all();
    m_step3.set_value();
  }

  void third(function<void()> printThird)
  {
    m_step3.get_future().wait();
    // std::unique_lock<std::mutex> lk(m_mtx);
    // std::lock_guard<std::mutex> lk(m_mtx);
    // m_cv.wait(lk, [this] { return m_step3; });
    // while (m_round != 2) {
    //   std::this_thread::sleep_for(2ms);
    //   // std::this_thread::yield();
    // }
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
  }
};

int main(int argc, char const* argv[])
{
  int input[6][3] = {
    {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

  auto call = [](Foo& foo, int in) {
    switch (in) {
      case 1: foo.first([] { cout << "First"; }); break;
      case 2: foo.second([] { cout << "Second"; }); break;
      case 3: foo.third([] { cout << "Third"; }); break;
    }
  };

  for (int i = 0; i < 6; ++i) {
    Foo         foo;
    std::thread first([&] { call(foo, input[i][0]); });
    std::thread second([&] { call(foo, input[i][1]); });
    std::thread third([&] { call(foo, input[i][2]); });

    first.join();
    second.join();
    third.join();
    cout << endl;
  }

  return 0;
}

/*
1632   ms  | while(1)
132    ms  | sleep 1ms
320    ms  | yield
180    ms  | lock condition_var
72~180 ms  | promise
*/
