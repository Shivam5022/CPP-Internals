//
// Created by Shivam Verma on 15/10/24.
//

#pragma once

#include <thread>
#include <vector>

class ThreadPool {
public:
  explicit ThreadPool(const size_t numThreads) {
    for (int i{}; i < numThreads; i++) {
      workers.emplace_back([this]() { worker(); });
    }
  }

  ~ThreadPool() {
    std::unique_lock<std::mutex> lock(queueMutex);
    stop = true;
    lock.unlock();

    cv.notify_all();
    for (std::thread &worker : workers) {
      worker.join();
    }
  }

  template <class F, class... Args> void execute(F &&func, Args &&...args) {
    auto task = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
    std::unique_lock<std::mutex> lock(queueMutex);
    if (stop) {
      throw std::runtime_error(
          "ThreadPool has been stopped. Don't enqueue more tasks.");
    }
    tasks.push(task);
    lock.unlock();

    cv.notify_one();
  }

private:
  void worker() {
    while (true) {
      std::function<void()> task;
      std::unique_lock<std::mutex> lock(queueMutex);
      cv.wait(lock, [this]() { return stop || !tasks.empty(); });

      if (stop && tasks.empty()) {
        return;
      }
      task = std::move(tasks.front());
      tasks.pop();
      lock.unlock();

      task();
    }
  }

  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::mutex queueMutex;
  std::condition_variable cv;

  bool stop{};
};
