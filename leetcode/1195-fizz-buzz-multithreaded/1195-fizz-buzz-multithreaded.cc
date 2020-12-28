
#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

#if 0
class FizzBuzz
{
 private:
  int n;

 private:
  std::atomic<int> i;

 public:
  FizzBuzz(int n) : n(n), i(1) {}

  // printFizz() outputs "fizz". %3
  void fizz(function<void()> printFizz)
  {
    while (i <= n) {
      if (((i % 5) != 0) && ((i % 3) == 0)) {
        printFizz();
        ++i;
      } else {
        std::this_thread::yield();
      }
    }
  }

  // printBuzz() outputs "buzz".
  void buzz(function<void()> printBuzz)
  {
    while (i <= n) {
      if (((i % 5) == 0) && ((i % 3) != 0)) {
        printBuzz();
        ++i;
      } else {
        std::this_thread::yield();
      }
    }
  }

  // printFizzBuzz() outputs "fizzbuzz".
  void fizzbuzz(function<void()> printFizzBuzz)
  {
    while (i <= n) {
      if (((i % 5) == 0) && ((i % 3) == 0)) {
        printFizzBuzz();
        ++i;
      } else {
        std::this_thread::yield();
      }
    }
  }

  // printNumber(x) outputs "x", where x is an integer.
  void number(function<void(int)> printNumber)
  {
    while (i <= n) {
      if (((i % 5) != 0) && ((i % 3) != 0)) {
        printNumber(i);
        ++i;
      } else {
        std::this_thread::yield();
      }
    }
  }
};
#endif

#if 1
class FizzBuzz
{
 private:
  int n;

 private:
  int                     i;
  std::condition_variable m_cv;
  std::mutex              m_mtx;

 public:
  FizzBuzz(int n) : n(n), i(1) {}

  // printFizz() outputs "fizz". %3
  void fizz(function<void()> printFizz)
  {
    unique_lock<mutex> lk(m_mtx);
    while (i <= n) {
      m_cv.wait(lk, [&] { return i > n || (((i % 5) != 0) && ((i % 3) == 0)); });
      if (i <= n) {
        printFizz();
        ++i;
      }
      m_cv.notify_all();
    }
  }
  // printBuzz() outputs "buzz".
  void buzz(function<void()> printBuzz)
  {
    unique_lock<mutex> lk(m_mtx);
    while (i <= n) {
      m_cv.wait(lk, [&] { return i > n || (((i % 5) == 0) && ((i % 3) != 0)); });
      if (i <= n) {
        printBuzz();
        ++i;
      }
      m_cv.notify_all();
    }
  }

  // printFizzBuzz() outputs "fizzbuzz".
  void fizzbuzz(function<void()> printFizzBuzz)
  {
    unique_lock<mutex> lk(m_mtx);
    while (i <= n) {
      m_cv.wait(lk, [&] { return i > n || (((i % 5) == 0) && ((i % 3) == 0)); });
      if (i <= n) {
        printFizzBuzz();
        ++i;
      }
      m_cv.notify_all();
    }
  }

  // printNumber(x) outputs "x", where x is an integer.
  void number(function<void(int)> printNumber)
  {
    unique_lock<mutex> lk(m_mtx);
    while (i <= n) {
      m_cv.wait(lk, [&] { return i > n || (((i % 5) != 0) && ((i % 3) != 0)); });
      if (i <= n) {
        printNumber(i++);
      }
      m_cv.notify_all();
    }
  }
};
#endif
int main(int argc, char const* argv[])
{
  FizzBuzz                 fb(15);
  std::vector<std::thread> v;

  // clang-format off
  auto _print_fz   = []()        { cout << "fz"   <<" "; };
  auto _print_bz   = []()        { cout << "bz"   <<" "; };
  auto _print_fzbz = []()        { cout << "fzbz" <<" "; };
  auto _print_num  = [](int a)   { cout << a      <<" "; };
  // clang-format on

  for (int n = 0; n < 1; ++n) {
    v.emplace_back([&] { fb.fizz(_print_fz); });        // H
    v.emplace_back([&] { fb.buzz(_print_bz); });        // H
    v.emplace_back([&] { fb.fizzbuzz(_print_fzbz); });  // H
    v.emplace_back([&] { fb.number(_print_num); });     // H
  }

  for (auto& t : v) {
    t.join();
  }
  cout << "\ntest end" << endl;

  return 0;
}

/*
32   ms | lock condition_var wait(,if)
36   ms | atomic
*/
