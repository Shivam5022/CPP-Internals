//
// Created by Shivam Verma on 15/10/24.
//

#pragma once

#include <iostream>

template<typename T>
class unique_pointer {
private:
    T* mPtr {nullptr};
public:
    explicit unique_pointer(T* ptr = nullptr) : mPtr(ptr) {
        std::cout << "Unique Pointer Constructed\n";
    }
    ~unique_pointer() {
        if (mPtr) {
            delete mPtr;
            std::cout << "Unique Pointer Destructed\n";
        }
    }

    // deleting copy constructor and copy assignment operator
    unique_pointer(const unique_pointer& rhs) = delete;
    unique_pointer& operator=(const unique_pointer& rhs) = delete;

    // defining move constructor and move assignment operator
    // transferring the ownership
    unique_pointer(unique_pointer&& rhs) noexcept : mPtr(rhs.mPtr) {
        rhs.mPtr = nullptr;
    }
    unique_pointer& operator=(unique_pointer&& rhs) noexcept {
        if (&rhs != this) {
            delete this->mPtr;
            this->mPtr = rhs.mPtr;
            rhs.mPtr = nullptr;
            std::cout << "Unique Pointer Moved\n";
        }
        return *this;
    }

    // dereferencing operator
    T& operator*() const {
        return *mPtr;
    }

    // arrow operator returns the underlying pointer
    T* operator->() const {
        return mPtr;
    }

    void reset(T* rhs = nullptr) {
        if (mPtr) {
            delete mPtr;
        }
        mPtr = rhs;
    }

    T* get() const {
        return mPtr;
    }

    explicit operator bool() const {
        return mPtr != nullptr;
    }
};
