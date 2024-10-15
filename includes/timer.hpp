//
// Created by Shivam Verma on 15/10/24.
//

#pragma once

#include <chrono>
#include <iostream>

// benchmarking a scope of code
class Timer {
    std::chrono::time_point<std::chrono::steady_clock> start;
public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    ~Timer() {
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<float> duration = end - start;
        const float ms = duration.count() * 1000.0f;
        std::cout << ms << " milliseconds\n";
    }
};



