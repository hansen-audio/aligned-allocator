// Copyright(c) 2021 Hansen Audio.

#include "ha/aligned_allocator/allocator.h"
#include "gtest/gtest.h"
#include <vector>

using namespace ha::memory;

namespace {

using vector_r16b = std::vector<float, aligned_allocator<float, 16>>;

//-----------------------------------------------------------------------------
TEST(aligned_allocator_test, test_vector)
{
    vector_r16b values;
    values.push_back(1.f);

    EXPECT_EQ(values.size(), 1);
}

//-----------------------------------------------------------------------------
TEST(aligned_allocator_test, test_assignment)
{
    vector_r16b values;
    values.push_back(1.f);

    vector_r16b values2;
    values2.push_back(2.f);

    EXPECT_NE(values, values2);

    values = values2;

    EXPECT_EQ(values, values2);
}

//-----------------------------------------------------------------------------
TEST(aligned_allocator_test, test_multiple_allocations)
{
    constexpr vector_r16b::size_type NUM_ENTRIES = 16;
    vector_r16b values;

    auto rounds = NUM_ENTRIES;
    while (rounds-- > 0)
        values.push_back(vector_r16b::value_type(rounds));

    EXPECT_EQ(values.size(), NUM_ENTRIES);
}

//-----------------------------------------------------------------------------
} // namespace