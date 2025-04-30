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

#include "baseclasses/basecwg.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseCwg)
    {
        //-- tests empty constructor
        BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_1;
        BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_1;
        BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_1;

        EXPECT_EQ(0ULL, cwg64_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg64_1._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg64_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_EQ(0ULL, cwg64_1._internal_state.state.weyl);

        EXPECT_EQ(0ULL, cwg128_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_1._internal_state.state.s.lo & 1ULL);
        EXPECT_NE(0ULL, cwg128_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_EQ(0ULL, cwg128_1._internal_state.state.weyl);

        EXPECT_EQ(0ULL, cwg128_64_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_64_1._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg128_64_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_EQ(0ULL, cwg128_64_1._internal_state.state.weyl);


        //-- tests Valued construtor (seed). */
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64(-1);
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(0.567f);
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64(0xfedc'ba98'0123'4567ULL);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(1ULL, cwg64._internal_state.state.s & 1ULL);
            EXPECT_NE(0ULL, cwg64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
            EXPECT_NE(cwg64_1._internal_state.state.s, cwg64._internal_state.state.s);  // (1 over 2^64 risk)
            EXPECT_NE(cwg64_1._internal_state.state.state, cwg64._internal_state.state.state);  // (1 over 2^64 risk)
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);

            EXPECT_EQ(0ULL, cwg128._internal_state.state.a);
            EXPECT_EQ(1ULL, cwg128._internal_state.state.s.lo & 1ULL);
            EXPECT_NE(0ULL, cwg128._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
            EXPECT_NE(cwg128_1._internal_state.state.s, cwg128._internal_state.state.s);  // (1 over 2^128 risk)
            EXPECT_NE(cwg128_1._internal_state.state.state, cwg128._internal_state.state.state);  // (1 over 2^128 risk)
            EXPECT_EQ(0ULL, cwg128._internal_state.state.weyl);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(1ULL, cwg128_64._internal_state.state.s & 1ULL);
            EXPECT_NE(0ULL, cwg128_64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
            EXPECT_NE(cwg128_64_1._internal_state.state.s, cwg128_64._internal_state.state.s);  // (1 over 2^128 risk)
            EXPECT_NE(cwg128_64_1._internal_state.state.state, cwg128_64._internal_state.state.state);  // (1 over 2^64 risk)
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
        }

        
        //-- tests Valued constructor (full state).
        CollatzWeylState<std::uint64_t, std::uint64_t>   internal_state_64_0;
        CollatzWeylState<std::uint64_t, utils::UInt128>  internal_state_128_64_0;
        CollatzWeylState<utils::UInt128, utils::UInt128> internal_state_128_0;

        BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_0(internal_state_64_0);
        BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_0(internal_state_128_64_0);
        BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_0(internal_state_128_0);

        EXPECT_EQ(internal_state_64_0, cwg64_0._internal_state.state);
        EXPECT_EQ(internal_state_128_64_0, cwg128_64_0._internal_state.state);
        EXPECT_EQ(internal_state_128_0, cwg128_0._internal_state.state);


        //-- tests copy constructor
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64(cwg64_1);
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(cwg128_1);
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64(cwg128_64_1);

            EXPECT_EQ(cwg64_1._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_1._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_1._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_1._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_1._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_1._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_64_1._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_mem(cwg64_0);
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_mem(cwg128_0);
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_mem(cwg128_64_0);

            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64(std::move(cwg64_mem));
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(std::move(cwg128_mem));
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64(std::move(cwg128_64_mem));

            EXPECT_EQ(cwg64_0._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_0._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_0._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_0._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_0._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_0._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_64_0._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64;
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128;
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64;

            cwg64 = cwg64_1;
            EXPECT_EQ(cwg64_1._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_1._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_1._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            cwg128 = cwg128_1;
            EXPECT_EQ(cwg128_1._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_1._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_1._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            cwg128_64 = cwg128_64_1;
            EXPECT_EQ(cwg128_64_1._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests move assignement
        BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64;
        BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128;
        BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64;

        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_mem(cwg64_0);
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_mem(cwg128_0);
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_mem(cwg128_64_0);

            cwg64 = std::move(cwg64_mem);
            EXPECT_EQ(cwg64_0._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_0._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_0._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            cwg128 = std::move(cwg128_mem);
            EXPECT_EQ(cwg128_0._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_0._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_0._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            cwg128_64 = std::move(cwg128_64_mem);
            EXPECT_EQ(cwg128_64_0._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests seed()
        cwg64.seed();
        cwg128.seed();
        cwg128_64.seed();

        EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(cwg64_1._internal_state.state.s, cwg64._internal_state.state.s);  // (1 over 2^64 risk)
        EXPECT_NE(cwg64_1._internal_state.state.state, cwg64._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);

        EXPECT_EQ(0ULL, cwg128._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128._internal_state.state.s.lo & 1ULL);
        EXPECT_NE(0ULL, cwg128._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_NE(cwg128_1._internal_state.state.s, cwg128._internal_state.state.s);  // (1 over 2^128 risk)
        EXPECT_NE(cwg128_1._internal_state.state.state, cwg128._internal_state.state.state);  // (1 over 2^128 risk)
        EXPECT_EQ(0ULL, cwg128._internal_state.state.weyl);

        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg128_64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(cwg128_64_1._internal_state.state.s, cwg128_64._internal_state.state.s);  // (1 over 2^128 risk)
        EXPECT_NE(cwg128_64_1._internal_state.state.state, cwg128_64._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);


        //-- tests seed(value)
        cwg64.seed(-1);
        cwg128.seed(utils::UInt128(123, 456));
        cwg128_64.seed(0.789);

        EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(cwg64_1._internal_state.state.s, cwg64._internal_state.state.s);  // (1 over 2^64 risk)
        EXPECT_NE(cwg64_1._internal_state.state.state, cwg64._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);

        EXPECT_EQ(0ULL, cwg128._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128._internal_state.state.s.lo & 1ULL);
        EXPECT_NE(0ULL, cwg128._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_NE(cwg128_1._internal_state.state.s, cwg128._internal_state.state.s);  // (1 over 2^128 risk)
        EXPECT_NE(cwg128_1._internal_state.state.state, cwg128._internal_state.state.state);  // (1 over 2^128 risk)
        EXPECT_EQ(0ULL, cwg128._internal_state.state.weyl);

        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg128_64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(cwg128_64_1._internal_state.state.s, cwg128_64._internal_state.state.s);  // (1 over 2^128 risk)
        EXPECT_NE(cwg128_64_1._internal_state.state.state, cwg128_64._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);


        //-- tests _setstate(seed_)
        // Notice: hard coded value below have been evaluated with PyRandLib
        cwg64._setstate(-1LL);
        EXPECT_EQ(0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xe4d9'7177'1b65'2c20 | 1, cwg64._internal_state.state.s);
        EXPECT_EQ(0xe99f'f867'dbf6'82c9, cwg64._internal_state.state.state);
        EXPECT_EQ(0, cwg64._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg64._internal_state.gauss_next);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);

        cwg128._setstate(utils::UInt128(1, 2));
        EXPECT_EQ(0, cwg128._internal_state.state.a);
        EXPECT_EQ(utils::UInt128(0x910a2dec89025cc1, 0x975835de1c9756ce | 1), cwg128._internal_state.state.s);
        EXPECT_EQ(utils::UInt128(0xbeeb8da1658eec67, 0xbfc846100bfc1e42), cwg128._internal_state.state.state);
        EXPECT_EQ(0, cwg128._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg128._internal_state.gauss_next);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);

    }

}
