//
// Created by Shivam Verma on 15/10/24.
//

#pragma once

template<typename T>
class shared_pointer {
private:
    T* mPtr;
    int* mRefCount;

public:
    // constructor
    explicit shared_pointer(T* ptr = nullptr) : mPtr(ptr), mRefCount(new int(1)) {
        std::cout << "Shared Pointer Constructed. Reference count = " << *mRefCount << "\n";
    }

    // copy constructor
    shared_pointer(const shared_pointer& rhs) : mPtr(rhs.mPtr), mRefCount(rhs.mRefCount) {
        ++(*mRefCount);
        std::cout << "Shared Pointer Copied. New Reference count = " << *mRefCount << "\n";
    }

    // move constructor
    shared_pointer(shared_pointer&& rhs) noexcept: mPtr(rhs.mPtr), mRefCount(rhs.mRefCount) {
        rhs.mPtr = nullptr;
        rhs.mRefCount = nullptr;
        std::cout << "Shared Pointer Moved (move constructor).\n";
    }

    // copy assignment operator
    shared_pointer& operator=(const shared_pointer& rhs) {
        if (this != &rhs) {
            // removing previous ownership
            if (mRefCount && --(*mRefCount) == 0) {
                delete mPtr;
                delete mRefCount;
            }
            mPtr = rhs.mPtr;
            mRefCount = rhs.mRefCount;
            ++(*mRefCount);
        }

        std::cout << "Shared Pointer Assigned. Reference count = " << *mRefCount << "\n";
        return *this;
    }

    // move assignment operator
    shared_pointer& operator=(shared_pointer&& rhs) noexcept {
        if (this != &rhs) {
            if (mRefCount && --(*mRefCount) == 0) {
                delete mPtr;
                delete mRefCount;
            }
            mPtr = rhs.mPtr;
            mRefCount = rhs.mRefCount;
            rhs.mPtr = nullptr;
            rhs.mRefCount = nullptr;
        }
        std::cout << "Shared Pointer Moved (Move Assignment).\n";
        return *this;
    }

    ~shared_pointer() {
        if (mRefCount && --(*mRefCount) == 0) {
            delete mPtr;
            delete mRefCount;
            std::cout << "Shared Pointer Deleted the managed object.\n";
        } else if (mRefCount) {
            std::cout << "Reference Count Decreased to: " << *mRefCount << '\n';
        }
    }

    // dereferencing operator
    T& operator*() const {
        return *mPtr;
    }

    // arrow operator returns the underlying pointer
    T* operator->() const {
        return mPtr;
    }

    T* get() const {
        return mPtr;
    }

    explicit operator bool() const {
        return mPtr != nullptr;
    }

    [[nodiscard]] int refCount() const {
        return mRefCount ? *mRefCount : 0;
    }
};
