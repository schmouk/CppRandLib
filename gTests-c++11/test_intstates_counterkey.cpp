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
#include "gtest/gtest.h"

#include "internalstates/counterkeystate.h"


//===========================================================================
namespace tests_internal_states
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteInternalStates, TestsCounterKeyState)
    {
        // tests default constructor
        CounterKeyState ck0;
        EXPECT_EQ(ck0.counter, 0);
        EXPECT_EQ(ck0.key, 1);


        // tests copy constructor
        CounterKeyState ck;
        ck.counter = 1;
        ck.key = 0x4ae1'7f05'63c2'8bd9ULL;

        CounterKeyState ck1(ck);
        EXPECT_EQ(ck1.counter, ck.counter);
        EXPECT_EQ(ck1.key, ck.key);


        // tests move constructor
        ck.counter++;
        ck.key += 2;

        CounterKeyState ck2{ std::move(ck) };
        EXPECT_EQ(ck2.counter, ck.counter);
        EXPECT_EQ(ck2.key, ck.key);


        // tests assignment copy constructor
        ck.counter++;
        ck.key += 2;
        ck1 = ck;
        EXPECT_EQ(ck1.counter, ck.counter);
        EXPECT_EQ(ck1.key, ck.key);


        // tests assignment move constructor
        ck.counter++;
        ck.key += 2;
        ck2 = std::move(ck);
        EXPECT_EQ(ck2.counter, ck.counter);
        EXPECT_EQ(ck2.key, ck.key);


        // tests seed()
        CounterKeyState c3;
        c3.seed();
        EXPECT_EQ(c3.counter, 0);
        EXPECT_EQ(c3.key & 0x1, 1);
        EXPECT_NE(c3.key, 1ULL);

        // tests seed(integer)
        c3.seed(0xae17'f056'3c28'bd94ULL);
        EXPECT_EQ(c3.counter, 0);
        EXPECT_EQ(c3.key & 0x1, 1);
        EXPECT_NE(c3.key, 1ULL);
    }
}
