cmake_minimum_required(VERSION 3.28)
project(CPP_Internals)
        
set(CMAKE_CXX_STANDARD 20)

add_executable( CPP_Internals main.cpp
                includes/unique_pointer.hpp
                includes/shared_pointer.hpp
                includes/vector.hpp
                includes/hashmap.hpp
                includes/thread_pool.hpp
                includes/timer.hpp
                includes/LRU_cache.hpp
                includes/memory_pool.hpp
                includes/reader_writer.hpp
        )
