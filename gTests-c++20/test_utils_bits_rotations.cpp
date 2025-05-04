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

#include "utils/bits_rotations.h"


//===========================================================================
namespace tests_utils
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteUtils, TestsUtilsBitsRotations)
    {
        std::uint16_t v16{ 0x1 };
        for (int n = 1; n < 16; ++n)
            EXPECT_EQ(0x1u << n, utils::rot_left(v16, n));

        std::uint32_t v32{ 0x1ul };
        for (int n = 1; n < 32; ++n)
            EXPECT_EQ(0x1ul << n, utils::rot_left(v32, n));

        std::uint64_t v64{ 0x1ull };
        for (int n = 1; n < 64; ++n)
            EXPECT_EQ(0x1ull << n, utils::rot_left(v64, n));

        v16 = 0b1000'0010'0100'0001;
        EXPECT_EQ(0b1000'0010'0100'0001, utils::rot_left(v16, 0));
        EXPECT_EQ(0b0000'0100'1000'0011, utils::rot_left(v16, 1));
        EXPECT_EQ(0b0000'1001'0000'0110, utils::rot_left(v16, 2));
        EXPECT_EQ(0b0001'0010'0000'1100, utils::rot_left(v16, 3));
        EXPECT_EQ(0b0010'0100'0001'1000, utils::rot_left(v16, 4));
        EXPECT_EQ(0b0100'1000'0011'0000, utils::rot_left(v16, 5));
        EXPECT_EQ(0b1001'0000'0110'0000, utils::rot_left(v16, 6));
        EXPECT_EQ(0b0010'0000'1100'0001, utils::rot_left(v16, 7));
        EXPECT_EQ(0b0100'0001'1000'0010, utils::rot_left(v16, 8));
        EXPECT_EQ(0b1000'0011'0000'0100, utils::rot_left(v16, 9));
        EXPECT_EQ(0b0000'0110'0000'1001, utils::rot_left(v16, 10));
        EXPECT_EQ(0b0000'1100'0001'0010, utils::rot_left(v16, 11));
        EXPECT_EQ(0b0001'1000'0010'0100, utils::rot_left(v16, 12));
        EXPECT_EQ(0b0011'0000'0100'1000, utils::rot_left(v16, 13));
        EXPECT_EQ(0b0110'0000'1001'0000, utils::rot_left(v16, 14));
        EXPECT_EQ(0b1100'0001'0010'0000, utils::rot_left(v16, 15));
        EXPECT_EQ(0b1000'0010'0100'0001, utils::rot_left(v16, 16));
        EXPECT_THROW(utils::rot_left(v16, -1), NegativeRotationException);
        EXPECT_THROW(utils::rot_left(v16, 17), TooBigRotationException);


        v32 = 0b1000'0010'0100'0001'1000'0010'0100'0001ul;
        EXPECT_EQ(0b0000'0100'1000'0011'0000'0100'1000'0011ul, utils::rot_left(v32, 1));
        EXPECT_EQ(0b0000'1001'0000'0110'0000'1001'0000'0110ul, utils::rot_left(v32, 2));
        EXPECT_EQ(0b0001'0010'0000'1100'0001'0010'0000'1100ul, utils::rot_left(v32, 3));
        EXPECT_EQ(0b0010'0100'0001'1000'0010'0100'0001'1000ul, utils::rot_left(v32, 4));
        EXPECT_EQ(0b0100'1000'0011'0000'0100'1000'0011'0000ul, utils::rot_left(v32, 5));
        EXPECT_EQ(0b1001'0000'0110'0000'1001'0000'0110'0000ul, utils::rot_left(v32, 6));
        EXPECT_EQ(0b0010'0000'1100'0001'0010'0000'1100'0001ul, utils::rot_left(v32, 7));
        EXPECT_EQ(0b0100'0001'1000'0010'0100'0001'1000'0010ul, utils::rot_left(v32, 8));
        EXPECT_EQ(0b1000'0011'0000'0100'1000'0011'0000'0100ul, utils::rot_left(v32, 9));
        EXPECT_EQ(0b0000'0110'0000'1001'0000'0110'0000'1001ul, utils::rot_left(v32, 10));
        EXPECT_EQ(0b0000'1100'0001'0010'0000'1100'0001'0010ul, utils::rot_left(v32, 11));
        EXPECT_EQ(0b0001'1000'0010'0100'0001'1000'0010'0100ul, utils::rot_left(v32, 12));
        EXPECT_EQ(0b0011'0000'0100'1000'0011'0000'0100'1000ul, utils::rot_left(v32, 13));
        EXPECT_EQ(0b0110'0000'1001'0000'0110'0000'1001'0000ul, utils::rot_left(v32, 14));
        EXPECT_EQ(0b1100'0001'0010'0000'1100'0001'0010'0000ul, utils::rot_left(v32, 15));
        EXPECT_EQ(0b1000'0010'0100'0001'1000'0010'0100'0001ul, utils::rot_left(v32, 16));
        EXPECT_EQ(0b0000'0100'1000'0011'0000'0100'1000'0011ul, utils::rot_left(v32, 17));
        EXPECT_EQ(0b0000'1001'0000'0110'0000'1001'0000'0110ul, utils::rot_left(v32, 18));
        EXPECT_EQ(0b0001'0010'0000'1100'0001'0010'0000'1100ul, utils::rot_left(v32, 19));
        EXPECT_EQ(0b0010'0100'0001'1000'0010'0100'0001'1000ul, utils::rot_left(v32, 20));
        EXPECT_EQ(0b0100'1000'0011'0000'0100'1000'0011'0000ul, utils::rot_left(v32, 21));
        EXPECT_EQ(0b1001'0000'0110'0000'1001'0000'0110'0000ul, utils::rot_left(v32, 22));
        EXPECT_EQ(0b0010'0000'1100'0001'0010'0000'1100'0001ul, utils::rot_left(v32, 23));
        EXPECT_EQ(0b0100'0001'1000'0010'0100'0001'1000'0010ul, utils::rot_left(v32, 24));
        EXPECT_EQ(0b1000'0011'0000'0100'1000'0011'0000'0100ul, utils::rot_left(v32, 25));
        EXPECT_EQ(0b0000'0110'0000'1001'0000'0110'0000'1001ul, utils::rot_left(v32, 26));
        EXPECT_EQ(0b0000'1100'0001'0010'0000'1100'0001'0010ul, utils::rot_left(v32, 27));
        EXPECT_EQ(0b0001'1000'0010'0100'0001'1000'0010'0100ul, utils::rot_left(v32, 28));
        EXPECT_EQ(0b0011'0000'0100'1000'0011'0000'0100'1000ul, utils::rot_left(v32, 29));
        EXPECT_EQ(0b0110'0000'1001'0000'0110'0000'1001'0000ul, utils::rot_left(v32, 30));
        EXPECT_EQ(0b1100'0001'0010'0000'1100'0001'0010'0000ul, utils::rot_left(v32, 31));
        EXPECT_THROW(utils::rot_left(v32, -1), NegativeRotationException);
        EXPECT_THROW(utils::rot_left(v32, 33), TooBigRotationException);

        v64 = 0b1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001ull;
        EXPECT_EQ(0b0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011ull, utils::rot_left(v64, 1));
        EXPECT_EQ(0b0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110ull, utils::rot_left(v64, 2));
        EXPECT_EQ(0b0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100ull, utils::rot_left(v64, 3));
        EXPECT_EQ(0b0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000ull, utils::rot_left(v64, 4));
        EXPECT_EQ(0b0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000ull, utils::rot_left(v64, 5));
        EXPECT_EQ(0b1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000ull, utils::rot_left(v64, 6));
        EXPECT_EQ(0b0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001ull, utils::rot_left(v64, 7));
        EXPECT_EQ(0b0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010ull, utils::rot_left(v64, 8));
        EXPECT_EQ(0b1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100ull, utils::rot_left(v64, 9));
        EXPECT_EQ(0b0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001ull, utils::rot_left(v64, 10));
        EXPECT_EQ(0b0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010ull, utils::rot_left(v64, 11));
        EXPECT_EQ(0b0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100ull, utils::rot_left(v64, 12));
        EXPECT_EQ(0b0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000ull, utils::rot_left(v64, 13));
        EXPECT_EQ(0b0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000ull, utils::rot_left(v64, 14));
        EXPECT_EQ(0b1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000ull, utils::rot_left(v64, 15));
        EXPECT_EQ(0b1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001ull, utils::rot_left(v64, 16));
        EXPECT_EQ(0b0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011ull, utils::rot_left(v64, 17));
        EXPECT_EQ(0b0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110ull, utils::rot_left(v64, 18));
        EXPECT_EQ(0b0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100ull, utils::rot_left(v64, 19));
        EXPECT_EQ(0b0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000ull, utils::rot_left(v64, 20));
        EXPECT_EQ(0b0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000ull, utils::rot_left(v64, 21));
        EXPECT_EQ(0b1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000ull, utils::rot_left(v64, 22));
        EXPECT_EQ(0b0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001ull, utils::rot_left(v64, 23));
        EXPECT_EQ(0b0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010ull, utils::rot_left(v64, 24));
        EXPECT_EQ(0b1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100ull, utils::rot_left(v64, 25));
        EXPECT_EQ(0b0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001ull, utils::rot_left(v64, 26));
        EXPECT_EQ(0b0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010ull, utils::rot_left(v64, 27));
        EXPECT_EQ(0b0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100ull, utils::rot_left(v64, 28));
        EXPECT_EQ(0b0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000ull, utils::rot_left(v64, 29));
        EXPECT_EQ(0b0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000ull, utils::rot_left(v64, 30));
        EXPECT_EQ(0b1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000ull, utils::rot_left(v64, 31));
        EXPECT_EQ(0b1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001ull, utils::rot_left(v64, 32));
        EXPECT_EQ(0b0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011ull, utils::rot_left(v64, 33));
        EXPECT_EQ(0b0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110ull, utils::rot_left(v64, 34));
        EXPECT_EQ(0b0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100ull, utils::rot_left(v64, 35));
        EXPECT_EQ(0b0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000ull, utils::rot_left(v64, 36));
        EXPECT_EQ(0b0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000ull, utils::rot_left(v64, 37));
        EXPECT_EQ(0b1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000ull, utils::rot_left(v64, 38));
        EXPECT_EQ(0b0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001ull, utils::rot_left(v64, 39));
        EXPECT_EQ(0b0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010ull, utils::rot_left(v64, 40));
        EXPECT_EQ(0b1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100ull, utils::rot_left(v64, 41));
        EXPECT_EQ(0b0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001ull, utils::rot_left(v64, 42));
        EXPECT_EQ(0b0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010ull, utils::rot_left(v64, 43));
        EXPECT_EQ(0b0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100ull, utils::rot_left(v64, 44));
        EXPECT_EQ(0b0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000ull, utils::rot_left(v64, 45));
        EXPECT_EQ(0b0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000ull, utils::rot_left(v64, 46));
        EXPECT_EQ(0b1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000ull, utils::rot_left(v64, 47));
        EXPECT_EQ(0b1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001ull, utils::rot_left(v64, 48));
        EXPECT_EQ(0b0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011ull, utils::rot_left(v64, 49));
        EXPECT_EQ(0b0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110ull, utils::rot_left(v64, 50));
        EXPECT_EQ(0b0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100ull, utils::rot_left(v64, 51));
        EXPECT_EQ(0b0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000ull, utils::rot_left(v64, 52));
        EXPECT_EQ(0b0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000ull, utils::rot_left(v64, 53));
        EXPECT_EQ(0b1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000ull, utils::rot_left(v64, 54));
        EXPECT_EQ(0b0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001ull, utils::rot_left(v64, 55));
        EXPECT_EQ(0b0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010ull, utils::rot_left(v64, 56));
        EXPECT_EQ(0b1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100ull, utils::rot_left(v64, 57));
        EXPECT_EQ(0b0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001ull, utils::rot_left(v64, 58));
        EXPECT_EQ(0b0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010ull, utils::rot_left(v64, 59));
        EXPECT_EQ(0b0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100'0001'1000'0010'0100ull, utils::rot_left(v64, 60));
        EXPECT_EQ(0b0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000'0011'0000'0100'1000ull, utils::rot_left(v64, 61));
        EXPECT_EQ(0b0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000'0110'0000'1001'0000ull, utils::rot_left(v64, 62));
        EXPECT_EQ(0b1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000'1100'0001'0010'0000ull, utils::rot_left(v64, 63));
        EXPECT_THROW(utils::rot_left(v64, -1), NegativeRotationException);
        EXPECT_THROW(utils::rot_left(v64, 65), TooBigRotationException);

    }
}
