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

#include "internalstates/extendedstate.h"
#include "pcg64_32.h"
#include "pcg128_64.h"


//===========================================================================
namespace tests_internal_states
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteInternalStates, TestsExtendedState)
    {
        // tests empty constructor
        ExtendedState<Pcg64_32, std::uint32_t, 16> es16;
        EXPECT_NE(es16.state.state(), 0ULL);  // well, expected to be not zero
        EXPECT_EQ(es16.extended_state.size(), 16ULL);
        for (auto esi : es16.extended_state)
            EXPECT_EQ(esi, 0UL);

        ExtendedState<Pcg128_64, std::uint32_t, 1024> es1024;
        EXPECT_NE(es1024.state.state(), 0ULL);  // well, expected to be not zero
        EXPECT_EQ(es1024.extended_state.size(), 1024ULL);
        for (auto esi : es1024.extended_state)
            EXPECT_EQ(esi, 0UL);


        // tests seed()
        es16.seed(0x94ae'17f0'563c'28bdULL);
        EXPECT_EQ(es16.state.state(), 0x94ae'17f0'563c'28bdULL);
        EXPECT_EQ(es16.extended_state.size(), 16ULL);
        for (auto esi : es16.extended_state)
            EXPECT_NE(esi, 0UL);  // well, expected to be not zero


        // tests copy constructor
        ExtendedState<Pcg64_32, std::uint32_t, 16> es0(es16);
        EXPECT_EQ(es0.state.state(), es16.state.state());
        EXPECT_EQ(es0.extended_state.size(), 16ULL);
        for (int i = 0; i < 16; ++i)
            EXPECT_EQ(es0.extended_state[i], es16.extended_state[i]);


        // tests move constructor
        ExtendedState<Pcg64_32, std::uint32_t, 16> es1{ std::move(es0) };
        EXPECT_EQ(es1.state.state(), es16.state.state());
        EXPECT_EQ(es1.extended_state.size(), 16ULL);
        for (int i = 0; i < 16; ++i)
            EXPECT_EQ(es1.extended_state[i], es16.extended_state[i]);


        // tests copy assignment
        es0 = es1;
        EXPECT_EQ(es0.state.state(), es1.state.state());
        EXPECT_EQ(es0.extended_state.size(), 16ULL);
        for (int i = 0; i < 16; ++i)
            EXPECT_EQ(es0.extended_state[i], es1.extended_state[i]);


        // tests move assignment
        es16 = std::move(es0);
        EXPECT_EQ(es16.state.state(), es1.state.state());
        EXPECT_EQ(es16.extended_state.size(), 16ULL);
        for (int i = 0; i < 16; ++i)
            EXPECT_EQ(es16.extended_state[i], es1.extended_state[i]);
    }

}
