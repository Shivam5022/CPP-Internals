//
// Created by Shivam Verma on 15/10/24.
//

#pragma once

#include <iostream>

template <typename T> class unique_pointer_sv {
private:
  T *mPtr{nullptr};

public:
  explicit unique_pointer_sv(T *ptr = nullptr) : mPtr(ptr) {
    std::cout << "Unique Pointer Constructed\n";
  }
  ~unique_pointer_sv() {
    if (mPtr) {
      delete mPtr;
      std::cout << "Unique Pointer Destructed\n";
    }
  }

  // deleting copy constructor and copy assignment operator
  unique_pointer_sv(const unique_pointer_sv &rhs) = delete;
  unique_pointer_sv &operator=(const unique_pointer_sv &rhs) = delete;

  // defining move constructor and move assignment operator
  // transferring the ownership
  unique_pointer_sv(unique_pointer_sv &&rhs) noexcept : mPtr(rhs.mPtr) {
    rhs.mPtr = nullptr;
  }
  unique_pointer_sv &operator=(unique_pointer_sv &&rhs) noexcept {
    if (&rhs != this) {
      delete this->mPtr;
      this->mPtr = rhs.mPtr;
      rhs.mPtr = nullptr;
      std::cout << "Unique Pointer Moved\n";
    }
    return *this;
  }

  // dereferencing operator
  T &operator*() const { return *mPtr; }

  // arrow operator returns the underlying pointer
  T *operator->() const { return mPtr; }

  void reset(T *rhs = nullptr) {
    if (mPtr) {
      delete mPtr;
    }
    mPtr = rhs;
  }

  T *get() const { return mPtr; }

  explicit operator bool() const { return mPtr != nullptr; }
};
