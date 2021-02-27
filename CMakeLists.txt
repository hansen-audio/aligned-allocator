cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

project(ha-aligned-allocator)

add_subdirectory(external)

add_library(aligned-allocator STATIC
    include/ha/aligned_allocator/allocator.h
    source/allocator.cpp
)

target_include_directories(aligned-allocator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

enable_testing()

add_executable(aligned-allocator_test
    test/allocator_test.cpp
)

target_link_libraries(aligned-allocator_test
    PRIVATE
        aligned-allocator
        gtest
        gtest_main
)