# Aligned Allocator
[![CMake (Linux, macOS, Windows)](https://github.com/hansen-audio/aligned-allocator/actions/workflows/cmake.yml/badge.svg)](https://github.com/hansen-audio/aligned-allocator/actions/workflows/cmake.yml)

## Motivation

This is an attempt to build a very lightweight allocator for STL containers like ```std::vector```, which can allocate memory aligned. With the introduction of ```std::aligned_alloc``` in ```c++17``` there is a cross platform solution. To date it seems as if if this is not supported yet on all platforms.

Therefore I took a look into Boost align library and "copied" the MSVS and macOS parts until ```std::aligned_alloc``` is available on these platforms as well.

> This is the first attempt to build a STL compatible allocator. There are unit tests avaiable. Nevertheless, be carefull when using this allocator!!!

## Using the allocator

Create a vector which holds 16-byte alligned floats for e.g. audio processing purpose.

```cpp
    using vector_r16b = std::vector<float, ha::alignment::aligned_allocator<float, 16>>;
    vector_r16b values;
    values.push_back(1.f);
    ...
```

## Links

* [https://en.cppreference.com/w/cpp/named_req/Allocator](https://en.cppreference.com/w/cpp/named_req/Allocator)
* [https://en.cppreference.com/w/cpp/memory/allocator](https://en.cppreference.com/w/cpp/memory/allocator)
* [https://github.com/boostorg/align/tree/develop/include/boost/align/detail](https://github.com/boostorg/align/tree/develop/include/boost/align/detail)

## License

Copyright 2021 Hansen Audio

Licensed under the MIT: https://mit-license.org/
