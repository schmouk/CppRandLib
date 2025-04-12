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

#include "utils/splitmix.h"


//===========================================================================
namespace tests_utils
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteUtils, TestsUtilsSplitmix)
    {
        // checks correctness of utils::splitmix_64
        {
            utils::SplitMix64 splitmix_64;

            std::uint64_t val_prec{ splitmix_64() };
            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val{ splitmix_64() };
                EXPECT_NE(val_prec, val);
                val_prec = val;
            }
        }

        // Notice:  SplitMix implementation is done on a 64-bits  integer
        // internal state. Should we get 'random' values on less bits, it 
        // may  happen that two successive values will be the same on the 
        // checked bits.  This is to occur with a bigger probability when 
        // returned bits count is smaller,  even if the probability of it 
        // to happen remains very low. So, we don't check in the belowing
        // tests the difference of two successive values.

        // checks correctness of utils::splitmix_63
        {
            utils::SplitMix63 splitmix_63;

            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val{ splitmix_63() };
                EXPECT_LE(val, 0x7fff'ffff'ffff'ffffull);
            }
        }

        // checks correctness of utils::splitmix_32
        {
            utils::SplitMix32 splitmix_32;

            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val{ splitmix_32() };
                EXPECT_LE(val, 0xffff'ffffull);
            }
        }

        // checks correctness of utils::set_random_seed31
        {
            utils::SplitMix31 splitmix_31;

            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val = splitmix_31();
                EXPECT_LE(val, 0x7fff'ffffull);
            }
        }

    }
}
