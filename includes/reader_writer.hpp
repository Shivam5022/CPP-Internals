//
// Created by Shivam Verma on 12/11/24.
//

#pragma once
#include <mutex>

class RWLock {
private:
    int numReaders;
    int numWriters;
    std::mutex lk;
    std::condition_variable cv;

public:
    RWLock() : numReaders(0), numWriters(0) {}

    void read_lock() {
        std::unique_lock<std::mutex> lock(lk);
        cv.wait(lock, [this] {return numWriters == 0;});
        ++numReaders;
    }

    void read_unlock() {
        std::unique_lock<std::mutex> lock(lk);
        if ((--numReaders) == 0) {
            cv.notify_all();
        }
    }

    void write_lock() {
        std::unique_lock<std::mutex> lock(lk);
        cv.wait(lock, [this] {return numReaders == 0 && numWriters == 0;});
        ++numWriters;
    }

    void write_unlock() {
        std::unique_lock<std::mutex> lock(lk);
        --numWriters;
        cv.notify_all();
    }

};
