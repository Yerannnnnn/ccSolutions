
#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class H2O
{
 private:
  std::condition_variable m_cv;
  std::mutex              m_h;
  std::mutex              m_o;
  std::atomic<int>        h_pool;
  std::atomic<int>        h_release;

 public:
  H2O() : h_pool(0), h_release(0) {}

  void hydrogen(function<void()> releaseHydrogen)
  {
    std::unique_lock<std::mutex> lk(m_h);
    h_pool++;
    m_cv.wait(lk);
    releaseHydrogen();
    h_release++;
  }

  void oxygen(function<void()> releaseOxygen)
  {
    std::lock_guard<std::mutex> lk(m_o);
    bool                        waiting = true;
    while (waiting) {
      switch (h_pool) {
        case 0: {
          std::this_thread::yield();
        } break;
        case 1: {
          h_pool -= 1;
          m_cv.notify_one();
          while (1) {
            std::this_thread::yield();
            if (h_pool) {
              h_pool -= 1;
              m_cv.notify_one();
              waiting = false;
              break;
            }
          }
        } break;
        default: {
          h_pool -= 2;
          m_cv.notify_one();
          m_cv.notify_one();
          waiting = false;
        }
      }
    }

    while (1) {
      std::this_thread::yield();
      if (h_release == 2) {
        releaseOxygen();
        h_release = 0;
        break;
      }
    }

    // end
  }
};

int main(int argc, char const* argv[])
{
  H2O                      h2o;
  std::vector<std::thread> v;

  auto _print_H = []() { cout << "H"; };
  auto _print_O = []() { cout << "O"; };

  for (int n = 0; n < 3; ++n) {
    v.emplace_back([&] { h2o.hydrogen(_print_H); });  // H
    v.emplace_back([&] { h2o.hydrogen(_print_H); });  // H
    v.emplace_back([&] { h2o.hydrogen(_print_H); });  // H
    v.emplace_back([&] { h2o.hydrogen(_print_H); });  // H
    v.emplace_back([&] { h2o.oxygen(_print_O); });    // O
    v.emplace_back([&] { h2o.oxygen(_print_O); });    // O
  }

  for (auto& t : v) {
    t.join();
  }
  cout << "\ntest end" << endl;

  return 0;
}

/*
460      ms | lock condition_var while atomic
52~270   ms | use yeild
*/
