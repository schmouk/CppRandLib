/*
MIT License

Copyright (c) 2025 Philippe Schmouker, ph.schmouker (at) gmail.com

This file is part of library CppRandLib Google Tests.

Permission is hereby granted,  free of charge,  to any person obtaining a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction,  including without limitation the  rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies of the Software,  and  to  permit  persons  to  whom  the  Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND,  EXPRESS  OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


//===========================================================================
#include <array>
#include <cstdint>
#include <list>
#include <map>
#include <vector>

#include "gtest/gtest.h"

#include "utils/type_traits.h"


//===========================================================================
namespace tests_utils
{
    //-----------------------------------------------------------------------
    // Dummy class for tests
    struct PleasedToMeetYou
    {
        std::int8_t val{ std::int8_t(255) };

        inline void hope_you_guess_my_name()
        {}

    };


    using Map = std::map<int, PleasedToMeetYou>;
    using Array = std::array<PleasedToMeetYou, 25>;
    using Array_d = std::array<double, 5>;
    using Array_u32 = std::array<std::uint32_t, 15>;


    //-----------------------------------------------------------------------
    TEST(TestSuiteUtils, TestsUtilsTypeTraits)
    {
        EXPECT_FALSE(utils::is_indexable_v<PleasedToMeetYou>);
        EXPECT_FALSE(utils::is_indexable_v<std::int8_t>);
        EXPECT_FALSE(utils::is_indexable_v<std::uint64_t>);
        EXPECT_FALSE(utils::is_indexable_v<double>);
        EXPECT_FALSE(utils::is_indexable_v<float>);
        EXPECT_FALSE(utils::is_indexable_v<long double>);


        EXPECT_FALSE(utils::is_indexable<Map>::value);
        EXPECT_FALSE(utils::is_indexable_v<std::list<PleasedToMeetYou>>);
        EXPECT_FALSE(utils::is_indexable_v<std::list<int>>);
        EXPECT_FALSE(utils::is_indexable_v<std::list<double>>);

        EXPECT_TRUE(utils::is_indexable_v<std::vector<double>>);
        EXPECT_TRUE(utils::is_indexable_v<Array_d>);
        EXPECT_TRUE(utils::is_indexable_v<std::vector<std::uint32_t>>);
        EXPECT_TRUE(utils::is_indexable_v<Array_u32>);
        EXPECT_TRUE(utils::is_indexable_v<std::vector<PleasedToMeetYou>>);
        EXPECT_TRUE(utils::is_indexable_v<Array>);

    }
}
