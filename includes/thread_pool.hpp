//
// Created by Shivam Verma on 15/10/24.
//

#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <queue>

class thread_pool {
public:
    explicit thread_pool(const size_t numThreads) : stop(false) {
        for (int i {}; i < numThreads; i++) {
            workers.emplace_back([this]() {
                worker();
            });
        }
    }

    ~thread_pool() {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
        lock.unlock();

        cv.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    template<class F, class... Args>
    void execute(F&& func, Args&&... args) {
        auto task = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop) {
            throw std::runtime_error("ThreadPool has been stopped. Don't enqueue more tasks.");
        }
        tasks.push(task);
        lock.unlock();

        cv.notify_one();
    }

private:
    void worker() {
        while (true) {
            std::function<void()> task;
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this]() {
               return stop || !tasks.empty();
            });

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
    std::mutex queue_mutex;
    std::condition_variable cv;

    bool stop;
};
