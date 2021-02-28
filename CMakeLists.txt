cmake_minimum_required(VERSION 3.14.0)

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

target_compile_features(aligned-allocator 
    PUBLIC 
        cxx_std_17
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