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
#include <xutility>

#include "gtest/gtest.h"

#include "internalstates/collatzweylstate.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_internal_states
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteInternalStates, TestsCollatzWeylState)
    {
        using Cws64 = CollatzWeylState<std::uint64_t, std::uint64_t>;
        using Cws64_128 = CollatzWeylState<std::uint64_t, utils::UInt128>;
        using Cws128 = CollatzWeylState<utils::UInt128, utils::UInt128>;


        // tests default constructor
        Cws64 s00;
        EXPECT_EQ(s00.a, 0);
        EXPECT_EQ(s00.s, 1);
        EXPECT_EQ(s00.state, 0);
        EXPECT_EQ(s00.weyl, 0);

        Cws64_128 s01;
        EXPECT_EQ(s01.a, 0);
        EXPECT_EQ(s01.s, 1);
        EXPECT_EQ(s01.state, 0);
        EXPECT_EQ(s01.weyl, 0);

        Cws128 s02;
        EXPECT_EQ(s02.a, 0);
        EXPECT_EQ(s02.s, 1);
        EXPECT_EQ(s02.state, 0);
        EXPECT_EQ(s02.weyl, 0);


        // tests copy constructor
        Cws64 s1;
        s1.a = 1;
        s1.s = 3;
        s1.state = 5;
        s1.weyl = 7;

        Cws64_128 s2;
        s2.a = 1;
        s2.s = 3;
        s2.state = 5;
        s2.weyl = 7;

        Cws128 s3;
        s3.a = 1;
        s3.s = 3;
        s3.state = 5;
        s3.weyl = 7;

        Cws64 s11(s1);
        EXPECT_EQ(s11.a,     s1.a);
        EXPECT_EQ(s11.s,     s1.s);
        EXPECT_EQ(s11.state, s1.state);
        EXPECT_EQ(s11.weyl,  s1.weyl);

        Cws64_128 s22(s2);
        EXPECT_EQ(s22.a,     s2.a);
        EXPECT_EQ(s22.s,     s2.s);
        EXPECT_EQ(s22.state, s2.state);
        EXPECT_EQ(s22.weyl,  s2.weyl);

        Cws128 s33(s3);
        EXPECT_EQ(s33.a,     s3.a);
        EXPECT_EQ(s33.s,     s3.s);
        EXPECT_EQ(s33.state, s3.state);
        EXPECT_EQ(s33.weyl,  s3.weyl);


        // tests move constructor
        Cws64 s111(std::move(s11));
        EXPECT_EQ(s111.a, s1.a);  // Notice: yes, s1 here for testing since s11 is now a moved object
        EXPECT_EQ(s111.s, s1.s);
        EXPECT_EQ(s111.state, s1.state);
        EXPECT_EQ(s111.weyl, s1.weyl);

        Cws64_128 s222(std::move(s22));
        EXPECT_EQ(s222.a, s2.a);  // Notice: yes, s2 here for testing since s22 is now a moved object
        EXPECT_EQ(s222.s, s2.s);
        EXPECT_EQ(s222.state, s2.state);
        EXPECT_EQ(s222.weyl, s2.weyl);

        Cws128 s333(std::move(s33));
        EXPECT_EQ(s333.a, s3.a);  // Notice: yes, s3 here for testing since s33 is now a moved object
        EXPECT_EQ(s333.s, s3.s);
        EXPECT_EQ(s333.state, s3.state);
        EXPECT_EQ(s333.weyl, s3.weyl);


        // tests copy assignment
        s1.a = 11;
        s1.s = 33;
        s1.state = 55;
        s1.weyl = 77;

        s2.a = 111;
        s2.s = 333;
        s2.state = 555;
        s2.weyl = 777;

        s3.a = 1111;
        s3.s = 3333;
        s3.state = 5555;
        s3.weyl = 7777;

        s11 = s1;
        EXPECT_EQ(s11.a, s1.a);
        EXPECT_EQ(s11.s, s1.s);
        EXPECT_EQ(s11.state, s1.state);
        EXPECT_EQ(s11.weyl, s1.weyl);

        s22 = s2;
        EXPECT_EQ(s22.a, s2.a);
        EXPECT_EQ(s22.s, s2.s);
        EXPECT_EQ(s22.state, s2.state);
        EXPECT_EQ(s22.weyl, s2.weyl);

        s33 = s3;
        EXPECT_EQ(s33.a, s3.a);
        EXPECT_EQ(s33.s, s3.s);
        EXPECT_EQ(s33.state, s3.state);
        EXPECT_EQ(s33.weyl, s3.weyl);


        // tests move assignment
        s111 = std::move(s11);
        EXPECT_EQ(s111.a, s1.a);  // Notice: yes, s1 here for testing since s11 is now a moved object
        EXPECT_EQ(s111.s, s1.s);
        EXPECT_EQ(s111.state, s1.state);
        EXPECT_EQ(s111.weyl, s1.weyl);

        s222 = std::move(s22);
        EXPECT_EQ(s222.a, s2.a);  // Notice: yes, s2 here for testing since s22 is now a moved object
        EXPECT_EQ(s222.s, s2.s);
        EXPECT_EQ(s222.state, s2.state);
        EXPECT_EQ(s222.weyl, s2.weyl);

        s333 = std::move(s33);
        EXPECT_EQ(s333.a, s3.a);  // Notice: yes, s3 here for testing since s33 is now a moved object
        EXPECT_EQ(s333.s, s3.s);
        EXPECT_EQ(s333.state, s3.state);
        EXPECT_EQ(s333.weyl, s3.weyl);


        // tests seed (64-bits)
        s1.seed(0x94ae'17f0'563c'28bdULL);
        EXPECT_EQ(0ULL, s1.a);
        EXPECT_EQ(0ULL, s1.weyl);
        EXPECT_EQ(1, s1.s & 1);
        EXPECT_NE(0ULL, s1.state);

        s2.seed(0x4ae1'7f05'63c2'8bd9ULL);
        EXPECT_EQ(0ULL, s2.a);
        EXPECT_EQ(0ULL, s2.weyl);
        EXPECT_EQ(1, s2.s & 1);
        EXPECT_FALSE(s2.state == 0ULL);

        s3.seed(0xae17'f056'3c28'bd94ULL);
        EXPECT_TRUE(s3.a == 0);
        EXPECT_TRUE(s3.weyl == 0);
        EXPECT_EQ(1, s3.s.lo & 1);
        EXPECT_FALSE(s3.state == 0ULL);

        CollatzWeylState<std::uint16_t, std::uint16_t> cws16;
        cws16.seed(0xae17'f056'3c28'bd94ULL);
        EXPECT_EQ(0, cws16.a);
        EXPECT_EQ(0, cws16.weyl);
        EXPECT_EQ(1, cws16.s & 1);
        EXPECT_NE(0, cws16.state);


        // tests seed (128-bits)
        utils::UInt128 seed128(0x4ae1'7f05'63c2'8bd9ULL, 0xae17'f056'3c28'bd94ULL);

        s1.seed(seed128);
        EXPECT_EQ(0ULL, s1.a);
        EXPECT_EQ(0ULL, s1.weyl);
        EXPECT_EQ(1, s1.s & 1);
        EXPECT_NE(0ULL, s1.state);

        s2.seed(seed128);
        EXPECT_EQ(0ULL, s2.a);
        EXPECT_EQ(0ULL, s2.weyl);
        EXPECT_EQ(1, s2.s & 1);
        EXPECT_FALSE(s2.state == 0ULL);

        s3.seed(seed128);
        EXPECT_TRUE(s3.a == 0);
        EXPECT_TRUE(s3.weyl == 0);
        EXPECT_EQ(1, s3.s.lo & 1);
        EXPECT_FALSE(s3.state == 0ULL);

        CollatzWeylState<std::uint16_t, std::uint16_t> cws162;
        cws162.seed(seed128);
        EXPECT_EQ(0, cws162.a);
        EXPECT_EQ(0, cws162.weyl);
        EXPECT_EQ(1, cws162.s & 1);
        EXPECT_NE(0, cws162.state);

    }
}
