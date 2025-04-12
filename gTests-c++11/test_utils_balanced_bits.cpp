/*
MIT License

Copyright (c) 2025 Philippe Schmouker, ph.schmouker (at) gmail.com

This file is part of library CppRandLib.

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

#include "utils/balanced_bits_generation.h"
#include "squares64.h"



//===========================================================================
namespace tests_utils
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteUtils, TestsUtilsBalancedBitsGeneration)
    {
        Squares64 init_rand;

        // chacks correctness of utils::balanced_bits_generation on 16-bits integers
        {
            std::uint16_t val;

            for (int i = 0; i < 100'000; ++i) {
                val = utils::balanced_bits_generation<std::uint16_t>(init_rand.next());
                int hex[]{ val & 0xf, (val >> 4) & 0xf, (val >> 8) & 0xf, val >> 12 };
                for (int j = 0; j < 3; ++j) {
                    for (int k = j + 1; k < 4; ++k) {
                        EXPECT_NE(hex[j], hex[k]);
                    }
                }
            }
        }

        // chacks correctness of utils::balanced_bits_generation on 32-bits integers
        {
            std::uint32_t val;

            for (int i = 0; i < 1'000'000; ++i) {
                val = utils::balanced_bits_generation<std::uint32_t>(init_rand.next());
                int hex[8]{};
                for (int j = 0; j < 8; ++j)
                    hex[j] = (val >> (4*j)) & 0xf;
                for (int j = 0; j < 7; ++j) {
                    for (int k = j + 1; k < 8; ++k) {
                        EXPECT_NE(hex[j], hex[k]);
                    }
                }
            }
        }

        // chacks correctness of utils::balanced_bits_generation on 64-bits integers
        {
            std::uint64_t val;

            for (int i = 0; i < 1'000'000; ++i) {
                val = utils::balanced_bits_generation<std::uint64_t>(init_rand.next());
                int hex[16]{};
                for (int j = 0; j < 16; ++j)
                    hex[j] = (val >> (4 * j)) & 0xf;
                for (int j = 0; j < 7; ++j) {
                    for (int k = j + 1; k < 8; ++k) {
                        EXPECT_NE(hex[j], hex[k]);
                    }
                }
                EXPECT_NE(hex[7], hex[8]);
                for (int j = 8; j < 15; ++j) {
                    for (int k = j + 1; k < 16; ++k) {
                        EXPECT_NE(hex[j], hex[k]);
                    }
                }
            }
        }

    }
}
