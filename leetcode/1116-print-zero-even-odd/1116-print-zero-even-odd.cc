
#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

#if 0
class ZeroEvenOdd
{
 private:
  int                     n;
  std::condition_variable m_cv;
  std::mutex              m_mtx;
  int                     m_round;

 public:
  ZeroEvenOdd(int n) : m_round(0) { this->n = n; }

  void zero(function<void(int)> printNumber)
  {
    std::unique_lock<std::mutex> lk(m_mtx, std::defer_lock);
    for (int i = 1; i <= n; ++i) {
      lk.lock();
      m_cv.wait(lk, [=]() { return (m_round == 0 || m_round == 2); });
      printNumber(0);
      ++m_round;
      lk.unlock();
      m_cv.notify_all();
    }
  }

  void odd(function<void(int)> printNumber)
  {
    std::unique_lock<std::mutex> lk(m_mtx, std::defer_lock);
    for (int i = 1; i <= n; i += 2) {
      lk.lock();
      m_cv.wait(lk, [=]() { return (m_round == 1); });
      printNumber(i);
      m_round = 2;
      lk.unlock();
      m_cv.notify_all();
    }
  }

  void even(function<void(int)> printNumber)
  {
    std::unique_lock<std::mutex> lk(m_mtx, std::defer_lock);
    for (int i = 2; i <= n; i += 2) {
      lk.lock();
      m_cv.wait(lk, [=]() { return (m_round == 3); });
      printNumber(i);
      m_round = 0;
      lk.unlock();
      m_cv.notify_all();
    }
  }
};
#endif
#if 1
class ZeroEvenOdd
{
 private:
  int              n;
  std::atomic<int> m_round;

 public:
  ZeroEvenOdd(int n) : m_round(0) { this->n = n; }

  void zero(function<void(int)> printNumber)
  {
    for (int i = 1; i <= n; ++i) {
      while (!(m_round == 0 || m_round == 2))
        std::this_thread::yield();
      printNumber(0);
      ++m_round;
    }
  }

  void odd(function<void(int)> printNumber)
  {
    for (int i = 1; i <= n; i += 2) {
      while (!(m_round == 1))
        std::this_thread::yield();
      printNumber(i);
      m_round = 2;
    }
  }

  void even(function<void(int)> printNumber)
  {
    for (int i = 2; i <= n; i += 2) {
      while (!(m_round == 3))
        std::this_thread::yield();
      printNumber(i);
      m_round = 0;
    }
  }
};
#endif
int main(int argc, char const* argv[])
{
  ZeroEvenOdd              zeo(6);
  std::vector<std::thread> v;

  for (int n = 0; n < 10; ++n) {
  }

  auto _print_num = [](int in) { cout << in; };

  v.emplace_back([&] { zeo.zero(_print_num); });
  v.emplace_back([&] { zeo.even(_print_num); });
  v.emplace_back([&] { zeo.odd(_print_num); });

  for (auto& t : v) {
    t.join();
  }
  cout << "\ntest end" << endl;

  return 0;
}

/*
36  ms | atomic bool yield
76 ms  | lock condition_var bool if
*/
