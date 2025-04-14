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
#include <vector>

#include "gtest/gtest.h"

#include "baseclasses/baseinternalstate.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseInternalState)
    {
        constexpr std::size_t N{ 1023 };
        //-- tests general case with non specialized 16-bits unsigned case
        {
            std::vector<std::uint16_t> internal_state(N, 0);  // creates a vector containing 23 items all set to zero
            BaseInternalState::_init_state(internal_state, 0x94ae'17f0'563c'28bdULL);

            for (auto is : internal_state) {
                EXPECT_NE(is, 0);    // well, expect no state item is null
                EXPECT_LE(is, 0xffffU);
            }

            for (int i = 0; i < internal_state.size() - 1; ++i)
                EXPECT_NE(internal_state[i], internal_state[i + 1]);  // well, expect no two successive state items are the same
        }


        //-- tests general case with non specialized 16-bits unsigned case
        {
            std::vector<std::uint64_t> internal_state(N, 0);  // creates a vector containing 23 items all set to zero
            BaseInternalState::_init_state(internal_state, 0x94ae'17f0'563c'28bdULL);

            for (auto is : internal_state) {
                EXPECT_NE(is, 0);    // well, expect no state item is null
                EXPECT_LE(is, 0xffff'ffff'ffff'ffffULL);
            }

            for (int i = 0; i < internal_state.size() - 1; ++i)
                EXPECT_NE(internal_state[i], internal_state[i + 1]);  // well, expect no two successive state items are the same
        }


        //-- tests general case with non specialized 16-bits unsigned case
        {
            std::vector<std::uint32_t> internal_state(N, 0);  // creates a vector containing 23 items all set to zero
            BaseInternalState::_init_state(internal_state, 0x94ae'17f0'563c'28bdULL);

            for (auto is : internal_state) {
                EXPECT_NE(is, 0);    // well, expect no state item is null
                EXPECT_LE(is, 0xffff'ffffUL);
            }

            for (int i = 0; i < internal_state.size() - 1; ++i)
                EXPECT_NE(internal_state[i], internal_state[i + 1]);  // well, expect no two successive state items are the same
        }


        //-- tests general case with non specialized 16-bits unsigned case
        {
            std::vector<std::uint32_t> internal_state(N, 0);  // creates a vector containing 23 items all set to zero
            BaseInternalState::_init_state<std::uint32_t, 31>(internal_state, 0x94ae'17f0'563c'28bdULL);

            for (auto is : internal_state) {
                EXPECT_NE(is, 0);    // well, expect no state item is null
                EXPECT_LE(is, 0x7fff'ffff'ffff'ffffULL);
            }

            for (int i = 0; i < internal_state.size() - 1; ++i)
                EXPECT_NE(internal_state[i], internal_state[i + 1]);  // well, expect no two successive state items are the same
        }

    }
}
