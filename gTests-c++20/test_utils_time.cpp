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
#include <cstdint>

#include "gtest/gtest.h"

#include "utils/time.h"


//===========================================================================
namespace tests_utils
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteUtils, TestsUtilsTime)
    {
        std::uint64_t now_ms{ utils::get_time_ms() };
        std::uint64_t now_us{ utils::get_time_us() };
        std::uint64_t now_ns{ utils::get_time_ns() };

        EXPECT_NE(0ull, now_ms);
        EXPECT_NE(0ull, now_us);
        EXPECT_NE(0ull, now_ns);

        EXPECT_LE(now_ms, now_us / 1000 + 1);       // Should be equal most of the time, let's be careful nevertheless
        EXPECT_LE(now_us, now_ns / 1000 + 1);       // Should be equal most of the time, let's be careful nevertheless
        EXPECT_LE(now_ms, now_ns / 1'000'000 + 1);  // Should be equal most of the time, let's be careful nevertheless
    }
}
