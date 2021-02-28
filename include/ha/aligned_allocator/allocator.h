// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <iostream>
#include <limits>
#include <new>
#include <stdlib.h>
#include <vector>

namespace ha {
namespace alignment {

//-----------------------------------------------------------------------------
/* https://en.cppreference.com/w/cpp/named_req/Allocator
 * https://en.cppreference.com/w/cpp/memory/allocator
 *
 */
//-----------------------------------------------------------------------------
template <typename T, int BYTE_ALIGNMENT>
struct aligned_allocator
{
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    // rebind allocator to type U
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
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_alloc();

        if (auto p = static_cast<T*>(std::aligned_alloc(BYTE_ALIGNMENT, n * sizeof(T))))
        {
            report(p, n);
            return p;
        }

        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t n) noexcept
    {
        report(p, n, 0);
        std::free(p);
    }

private:
    void report(T* p, std::size_t n, bool alloc = true) const
    {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n << " bytes at " << std::hex
                  << std::showbase << reinterpret_cast<void*>(p) << std::dec << '\n';
    }
};

template <class T, class U, int BYTE_ALIGNMENT>
bool operator==(const aligned_allocator<T, BYTE_ALIGNMENT>&,
                const aligned_allocator<U, BYTE_ALIGNMENT>&)
{
    return true;
}
template <class T, class U, int BYTE_ALIGNMENT>
bool operator!=(const aligned_allocator<T, BYTE_ALIGNMENT>&,
                const aligned_allocator<U, BYTE_ALIGNMENT>&)
{
    return false;
}

//-----------------------------------------------------------------------------
} // namespace alignment
} // namespace ha
