
#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
#if 0
class FooBar
{
 private:
  int                n;
  std::promise<void>* m_bar;
  std::promise<void>* m_foo;

 public:
  FooBar(int n)
  {
    this->n = n;
    m_bar = new std::promise<void>[n];
    m_foo = new std::promise<void>[n+1];
    m_foo[0].set_value();
  }

  void foo(function<void()> printFoo)
  {
    for (int i = 0; i < n; i++) {
      // printFoo() outputs "foo". Do not change or remove this line.
      m_foo[i].get_future().wait();
      printFoo();
      m_bar[i].set_value();
    }
  }

  void bar(function<void()> printBar)
  {
    for (int i = 0; i < n; i++) {
      m_bar[i].get_future().wait();
      // printBar() outputs "bar". Do not change or remove this line.
      printBar();
      m_foo[i+1].set_value();
    }
  }
};
#endif
#if 0
class FooBar
{
 private:
  int                n;
  std::atomic<int>   m_bar;
  std::atomic<int>   m_foo;

 public:
  FooBar(int n)
  {
    this->n = n;
    m_bar=1;
    m_foo=0;
  }

  void foo(function<void()> printFoo)
  {
    for (int i = 1; i <= n; i++) {
#if 0
      while(m_bar!=i)std::this_thread::sleep_for(1ms);
#else
      while(m_bar!=i)std::this_thread::yield();
#endif
      printFoo();
      ++m_foo;
    }
  }

  void bar(function<void()> printBar)
  {
    for (int i = 1; i <= n; i++) {
#if 0
      while(m_foo!=i)std::this_thread::sleep_for(1ms);
#else
      while(m_foo!=i)std::this_thread::yield();
#endif
      printBar();
      ++m_bar;
    }
  }
};
#endif
#if 0
class FooBar
{
 private:
  int                n;
  mutex              m_mtx;
  condition_variable m_foo;
  condition_variable m_bar;
  bool               m_fooround;

 public:
  FooBar(int n) : n(n), m_fooround(true) {}

  void foo(function<void()> printFoo)
  {
    std::unique_lock<std::mutex> lk(m_mtx, std::defer_lock);
    for (int i = 0; i < n; i++) {
      lk.lock();
      if (!m_fooround) {
        m_foo.wait(lk);
      }
      printFoo();
      m_fooround = false;
      m_bar.notify_all();
      lk.unlock();
    }
  }

  void bar(function<void()> printBar)
  {
    std::unique_lock<std::mutex> lk(m_mtx, std::defer_lock);
    for (int i = 0; i < n; i++) {
      lk.lock();
      if (m_fooround) {
        m_bar.wait(lk);
      }
      printBar();
      m_fooround = true;
      m_foo.notify_all();
      lk.unlock();
    }
  }
};
#endif
#if 1
class FooBar
{
 private:
  int               n;
  std::atomic<bool> m_fooround;

 public:
  FooBar(int n) : m_fooround(true) { this->n = n; }

  void foo(function<void()> printFoo)
  {
    for (int i = 1; i <= n; i++) {
      while (!m_fooround.load(std::memory_order_acquire))
        std::this_thread::yield();
      printFoo();
      m_fooround.store(false, std::memory_order_release);
    }
  }

  void bar(function<void()> printBar)
  {
    for (int i = 1; i <= n; i++) {
      while (m_fooround.load(std::memory_order_acquire))
        std::this_thread::yield();
      printBar();
      m_fooround.store(true, std::memory_order_release);
    }
  }
};
#endif
int main(int argc, char const* argv[])
{
  FooBar      foobar(6);
  std::thread thr_foo([&] { foobar.foo([] { cout << "foo"; }); });
  std::thread thr_bar([&] { foobar.bar([] { cout << "bar\n"; }); });

  thr_foo.join();
  thr_bar.join();
  cout << endl;

  return 0;
}

/*
312 ms | promise[n]
376 ms | atomic + sleep 1ms
220 ms | atomic int yield
368 ms | lock condition_var bool while
368 ms | lock condition_var bool if
212 ms | atomic bool yield
*/
