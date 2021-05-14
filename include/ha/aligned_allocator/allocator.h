// Copyright(c) 2021 Hansen Audio.

#pragma once

//#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <vector>

#if defined(_WIN32)
#include <malloc.h>
#elif __APPLE__
#include <stdlib.h>
#else
#include <cstdlib>
#endif

namespace ha::alignment {

//-----------------------------------------------------------------------------
/*
 * https://en.cppreference.com/w/cpp/named_req/Allocator
 * https://en.cppreference.com/w/cpp/memory/allocator
 * https://github.com/boostorg/align/tree/develop/include/boost/align/detail
 */
//-----------------------------------------------------------------------------
template <typename T, std::size_t BYTE_ALIGNMENT>
struct aligned_allocator
{
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;

    template <class U>
    struct rebind
    {
        typedef aligned_allocator<U, BYTE_ALIGNMENT> other;
    };

    aligned_allocator() = default;
    template <class U>
    constexpr aligned_allocator(const aligned_allocator<U, BYTE_ALIGNMENT>&) noexcept
    {
    }

    [[nodiscard]] T* allocate(std::size_t n)
    {
        static_assert(BYTE_ALIGNMENT == 8 || BYTE_ALIGNMENT == 16 || BYTE_ALIGNMENT == 32 ||
                      BYTE_ALIGNMENT == 64);

        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_alloc();
#if defined(_WIN32)
        if (auto p = static_cast<T*>(_aligned_malloc(n * sizeof(T), BYTE_ALIGNMENT)))
#elif __APPLE__
        void* pT = nullptr;
        if (::posix_memalign(&pT, BYTE_ALIGNMENT, n * sizeof(T)) == 0)
#else
        if (auto p = static_cast<T*>(std::aligned_alloc(BYTE_ALIGNMENT, n * sizeof(T))))
#endif
        {
#if defined(__APPLE__)
            auto p = static_cast<T*>(pT);
#endif
#if REPORT_ALLOCATIONS
            report(p, n);
#endif
            return p;
        }

        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t n) noexcept
    {
#if REPORT_ALLOCATIONS
        report(p, n, 0);
#endif
#if defined(_WIN32)
        _aligned_free(p);
#elif __APPLE__
        ::free(p);
#else
        std::free(p);
#endif
    }

private:
    void report(T* p, std::size_t n, bool alloc = true) const
    {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n << " bytes at " << std::hex
                  << std::showbase << reinterpret_cast<void*>(p) << std::dec << '\n';
    }
};

template <class T, class U, std::size_t BYTE_ALIGNMENT>
bool operator==(const aligned_allocator<T, BYTE_ALIGNMENT>&,
                const aligned_allocator<U, BYTE_ALIGNMENT>&)
{
    return true;
}
template <class T, class U, std::size_t BYTE_ALIGNMENT>
bool operator!=(const aligned_allocator<T, BYTE_ALIGNMENT>&,
                const aligned_allocator<U, BYTE_ALIGNMENT>&)
{
    return false;
}

//-----------------------------------------------------------------------------
} // namespace ha::alignment