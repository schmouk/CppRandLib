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

#include "internalstates/listseedstate.h"
#include "utils/splitmix.h"


//===========================================================================
namespace tests_internal_states
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteInternalStates, TestsListSeedState)
    {
        using LSS64 = ListSeedState<utils::SplitMix64, std::uint64_t, 15>;
        using LSS31 = ListSeedState<utils::SplitMix31, std::uint32_t, 123>;


        // tests empty constructor
        LSS64 lss_64;
        EXPECT_EQ(15ULL, lss_64.list.size());
        EXPECT_EQ(0UL, lss_64.index);

        LSS31 lss_31;
        EXPECT_EQ(123ULL, lss_31.list.size());
        EXPECT_EQ(0UL, lss_31.index);


        // tests seed
        lss_64.seed(0xa758'f61e'0c53'2b49ULL);
        EXPECT_EQ(15ULL, lss_64.list.size());
        EXPECT_EQ(0UL, lss_64.index);
        for (int i = 0; i < lss_64.list.size() - 1; ++i) {
            EXPECT_NE(lss_64.list[i], 0ULL);                // well, expected to be not zero
            EXPECT_NE(lss_64.list[i], lss_64.list[i + 1]);  // well, two succeeding items expected to be different
        }
        EXPECT_NE(lss_64.list[lss_64.list.size() - 1], 0ULL);   // well, expected to be not zero

        lss_31.seed(0xa758'f61e'0c53'2b49ULL);
        EXPECT_EQ(123ULL, lss_31.list.size());
        EXPECT_EQ(0UL, lss_31.index);
        for (int i = 0; i < lss_31.list.size() - 1; ++i) {
            EXPECT_NE(lss_31.list[i], 0ULL);                // well, expected to be not zero
            EXPECT_LE(lss_31.list[i], 0x7fff'ffffUL);
            EXPECT_NE(lss_31.list[i], lss_31.list[i + 1]);  // well, two succeeding items expected to be different
        }
        EXPECT_NE(lss_31.list[lss_31.list.size() - 1], 0ULL);   // well, expected to be not zero
        EXPECT_LE(lss_31.list[lss_31.list.size() - 1], 0x7fff'ffffUL);


        // tests copy constructor
        LSS64 lss0(lss_64);
        EXPECT_EQ(lss0.list.size(), lss_64.list.size());
        EXPECT_EQ(lss0.index, lss_64.index);
        for (int i = 0; i < lss0.list.size(); ++i)
            EXPECT_EQ(lss0.list[i], lss_64.list[i]);

        LSS31 lss1(lss_31);
        EXPECT_EQ(lss1.list.size(), lss_31.list.size());
        EXPECT_EQ(lss1.index, lss_31.index);
        for (int i = 0; i < lss1.list.size(); ++i)
            EXPECT_EQ(lss1.list[i], lss_31.list[i]);


        // tests move constructor
        LSS64 lss2(std::move(lss0));
        EXPECT_EQ(lss2.list.size(), lss_64.list.size());
        EXPECT_EQ(lss2.index, lss_64.index);
        for (int i = 0; i < lss2.list.size(); ++i)
            EXPECT_EQ(lss2.list[i], lss_64.list[i]);

        LSS31 lss3(std::move(lss1));
        EXPECT_EQ(lss3.list.size(), lss_31.list.size());
        EXPECT_EQ(lss3.index, lss_31.index);
        for (int i = 0; i < lss3.list.size(); ++i)
            EXPECT_EQ(lss3.list[i], lss_31.list[i]);


        // tests copy assignment
        lss_64.seed(0x0c53'a758'f61e'2b49ULL);
        lss0 = lss_64;
        EXPECT_EQ(lss0.list.size(), lss_64.list.size());
        EXPECT_EQ(lss0.index, lss_64.index);
        for (int i = 0; i < lss0.list.size(); ++i)
            EXPECT_EQ(lss0.list[i], lss_64.list[i]);

        lss_31.seed(0x0c53'a758'f61e'2b49ULL);
        lss1 = lss_31;
        EXPECT_EQ(lss1.list.size(), lss_31.list.size());
        EXPECT_EQ(lss1.index, lss_31.index);
        for (int i = 0; i < lss1.list.size(); ++i)
            EXPECT_EQ(lss1.list[i], lss_31.list[i]);


        // tests move assignment
        lss2 = std::move(lss0);
        EXPECT_EQ(lss2.list.size(), lss_64.list.size());
        EXPECT_EQ(lss2.index, lss_64.index);
        for (int i = 0; i < lss2.list.size(); ++i)
            EXPECT_EQ(lss2.list[i], lss_64.list[i]);

        lss3 = std::move(lss1);
        EXPECT_EQ(lss3.list.size(), lss_31.list.size());
        EXPECT_EQ(lss3.index, lss_31.index);
        for (int i = 0; i < lss3.list.size(); ++i)
            EXPECT_EQ(lss3.list[i], lss_31.list[i]);
    }

}
