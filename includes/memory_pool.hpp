//
// Created by Shivam Verma on 12/11/24.
//

#pragma once

#include <iostream>

// memory pool without using any extra space
// each free block has pointer to the next free block
// allocation: return the block pointed by the head
// deallocation (*ptr): store head at location ptr and point new head to ptr

template<typename T>
class memory_pool {
public:
    explicit memory_pool(const int sz) {
        buf = new char[sz * sizeof(T)];
        for (int i = 0; i < sz; i++) {
            void* current = buf + i * sizeof(T);
            void* next = nullptr;
            if (i + 1 < sz) {
                next = buf + (i + 1) * sizeof(T);
            }
            *(reinterpret_cast<void**>(current)) = next;
        }
        front = buf;
    }

    ~memory_pool() {
        delete [] buf;
    }

    T* allocate() {
        if (!front) {
            std::cerr << "Memory Pool Exhausted\n";
            return nullptr;
        }
        T* freeBlock = reinterpret_cast<T*>(front);
        front = *reinterpret_cast<void**>(front);
        return freeBlock;
    }

    void deallocate(T* ptr) {
        *reinterpret_cast<void**>(ptr) = front;
        front = ptr;
    }

private:
    T* buf;
    void* front;
};

// Sample usage would be like:
// memory_pool<custom> pool(100);
// custom* obj = pool.allocate();
// new (obj) custom(constructor arguments...); // using placement new for object construction
