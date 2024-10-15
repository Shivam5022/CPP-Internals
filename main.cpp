#include <iostream>
#include <string>
#include "includes/unique_pointer.hpp"
#include "includes/shared_pointer.hpp"
#include "includes/thread_pool.hpp"
#include "includes/timer.hpp"

struct A {
    int mId;
    std::string mName;
    A(int id, const std::string& name) : mId(id), mName(name) {}
};

void testUniquePtr() {
    unique_pointer<A> ptr(new A(1, "Shivam"));
    std::cout << ptr->mId << '\n';
    std::cout << ptr->mName << '\n';

    unique_pointer<A> ptr2 = std::move(ptr);
    std::cout << ptr2->mName << '\n';

    if (!ptr) {
        std::cout << "First pointer is now null\n";
    }
}

void testSharedPtr() {
    shared_pointer<A> ptr(new A(1, "Shivam"));
    shared_pointer<A> ptr2 = ptr;
    {
        shared_pointer<A> ptr3 = ptr2;
        std::cout << ptr3->mName << '\n';
    }
    shared_pointer<A> ptr4 = ptr;
}

void testThreadPool(const int numThreads) {
    constexpr int iterations = 10;
    thread_pool tp(numThreads);

    auto testFunction = [](const int a, const int b, const int c = 0) {
        std::cout << "The sum is : " << a + b + c << '\n';
        return a + b + c;
    };
    const int height = 11, weight = 12;

    Timer timer;
    for (int i = 0; i < iterations; i++) {
        tp.execute(testFunction, height, weight);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    // testUniquePtr();
    // testSharedPtr();
    testThreadPool(5);
    return 0;

}
