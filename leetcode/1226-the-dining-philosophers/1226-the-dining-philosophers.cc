
#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class DiningPhilosophers
{
 private:
  std::mutex m_mtx[5];

 public:
  DiningPhilosophers() {}

  void wantsToEat(int philosopher, function<void()> pickLeftFork,
    function<void()> pickRightFork, function<void()> eat,
    function<void()> putLeftFork, function<void()> putRightFork)
#if 0
  {
    int  right = (philosopher + 1) % 5;
    int& left  = philosopher;
    if (philosopher % 2) {
      // right first
      m_mtx[right].lock();
      m_mtx[left].lock();
    } else {
      // left first
      m_mtx[left].lock();
      m_mtx[right].lock();
    }
    pickLeftFork();
    pickRightFork();
    eat();
    putLeftFork();
    putRightFork();
    m_mtx[left].unlock();
    m_mtx[right].unlock();
  }
#else
  {
    unique_lock<mutex> lk_left(m_mtx[philosopher], std::defer_lock);
    unique_lock<mutex> lk_right(m_mtx[(philosopher + 1) % 5], std::defer_lock);

    std::lock(lk_left, lk_right);
    pickLeftFork();
    pickRightFork();
    eat();
    putLeftFork();
    putRightFork();
    std::this_thread::yield();
  }
#endif
};
int main(int argc, char const* argv[])
{
  DiningPhilosophers       sth;
  std::vector<std::thread> v;

  // clang-format off
  auto _0 = [](){ cout << "a"   <<" "; };
  auto _1 = [](){ cout << "b"   <<" "; };
  auto _2 = [](){ cout << "3"   <<" "; };
  auto _3 = [](){ cout << "A"   <<" "; };
  auto _4 = [](){ cout << "B"   <<" "; };
  // clang-format on

  for (int n = 0; n < 10; ++n) {
    v.emplace_back([&] { sth.wantsToEat(0, _0, _1, _2, _3, _4); });
    v.emplace_back([&] { sth.wantsToEat(1, _0, _1, _2, _3, _4); });
    v.emplace_back([&] { sth.wantsToEat(2, _0, _1, _2, _3, _4); });
    v.emplace_back([&] { sth.wantsToEat(3, _0, _1, _2, _3, _4); });
    v.emplace_back([&] { sth.wantsToEat(4, _0, _1, _2, _3, _4); });
  }

  for (auto& t : v) {
    t.join();
  }
  cout << "\ntest end" << endl;

  return 0;
}

/*
180~240  ms | std::lock(lk_left, lk_right);
44~200   ms | right first
*/
