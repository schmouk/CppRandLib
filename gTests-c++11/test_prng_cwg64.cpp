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

#include "cwg64.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsCwg64)
    {
        //-- tests empty constructor
        Cwg64 cwg64_1;

        EXPECT_EQ(0ULL, cwg64_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg64_1._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg64_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_EQ(0ULL, cwg64_1._internal_state.state.weyl);
        EXPECT_FALSE(cwg64_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64_1._internal_state.gauss_next);

        // Notice: all belowing hard coded values have been evaluated with PyRandLib

        //-- tests Valued constructor (seed) AND next()
        {
            Cwg64 cwg64(1);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x910a2dec89025cc1ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xbeeb8da1658eec67ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd15981ccf78370af, 0x92a898cc34dc3e71, 0x77e3762f7fc15b08, 0x1f2ee85f2316e3ef, 0x73e2d6de8708ac18 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0xba0006c934c75c02ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x910a2dec89025cc1ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x73e2d6de87081618ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0xd532e59ead0bcfc5ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(-2);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xf3203e9039f4a821ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xba56949915dcf9e9ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc0b5fb43e9bd1c63, 0x5cc25f71bd66fb68, 0xbefd42742a2f363b, 0x76427be4540ece7e, 0x32852a159517f8ea };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0x0d0eada73b3f5b29ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xf3203e9039f4a821ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x32852a159517f5e4ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0xbfa138d121c748a5ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(9);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xaeaf52febe706065ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xc02d8a5e87afea62ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x709878c8a8513bbb, 0xf5cc2e77e850817f, 0x78664fa0899633a1, 0x83b6022231a659b1, 0xfce72b6042db1083 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0x22ae8361d38f742dULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xaeaf52febe706065ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xfce72b6042db322dULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0x696c9ef9b831e1f9ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(-11);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x6fc5530939fb94c3ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x96caee613260cfcaULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x565faa9774bf8f9e, 0x632f7dc304d9063a, 0xcba980a67b6f5deb, 0x29f28cae27cc0127, 0x8950951f46343b8f };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0x45f624104f34ff03ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x6fc5530939fb94c3ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x8950951f46347e79ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0x2eda9f2e21e9e7cfULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(17);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x808475f02ee37363ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x6434ff62b4e8edd1ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc6d79f8fa38acc3f, 0x7989d4383ab9bc9b, 0xaaac4fbd689bc58e, 0xe8b74ace94f106ca, 0x2fe67f0549eced99 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0x37fa0db690b9d813ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x808475f02ee37363ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x2fe67f0549ecda63ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0x82964db0ea7140efULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x157a3807a48faa9dULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xd573529b34a1d093ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xdbfaff32e796ce05, 0x4ab030b1e0e73bc7, 0x33dbb1ac8abdb275, 0x2c6c9c56c4ce3f8f, 0x81a05875df4bf239 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0x5c66d0834caad592ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x157a3807a48faa9dULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x81a05875df4bae5fULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0x6b63182636ce5511ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(-8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x48bbc5b84275f3cbULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xe2fbc345a799b5aaULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd36c8fa44eaed477, 0xbb9d8d0e11ae35f4, 0x5251907fbb8627ae, 0x18580ce37fbad87a, 0xcb6c862660e0a0ea };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0xdcaf7d5b4336e1aaULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x48bbc5b84275f3cbULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xcb6c862660e07c45ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0x6baadc994c4dc2f7ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xa6eb6466bac9f251ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd8f686852ab8624a, 0x25850835c5828c03, 0xd2dfe9d74da6f9f8, 0xb590e785355c0a1f, 0x3d52bb48b14ee91e };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0x2dd7c47e2e0879cbULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x3d52bb48b14ec4c9ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0xaa56068403c3e52dULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(0.357);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x5fee464f36fc42c3ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x954faf5a9ad49cf8ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x57e08bdb9c153110, 0x5a1a62dba3f9344f, 0x34137ef62f66b56a, 0xcd2808938477fe22, 0x9afdebcd5f09d213 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0x4886259b8ec29272ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x5fee464f36fc42c3ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x9afdebcd5f099a95ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0xdfa75f8c12ed4dcfULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            Cwg64 cwg64(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));

            EXPECT_EQ(0x0, cwg64._internal_state.state.a);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg64._internal_state.state.s);
            EXPECT_EQ(0xec779c3693f88501, cwg64._internal_state.state.state);
            EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xec288dd0f1298f2a, 0x44e33950a6e20488, 0x4d83d25b218ca498, 0x459c640e6a48e1de, 0xc98743f470b82316 };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg64.next());

            EXPECT_EQ(0xb0a399c1b7da087a, cwg64._internal_state.state.a);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg64._internal_state.state.s);
            EXPECT_EQ(0xc98743f470b893b5, cwg64._internal_state.state.state);
            EXPECT_EQ(0xd4db17fa8c282951, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }

        EXPECT_THROW(Cwg64(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Cwg64(1.0), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        CollatzWeylState<std::uint64_t, std::uint64_t>   internal_state_64_0;
        Cwg64 cwg64_0(internal_state_64_0);

        EXPECT_EQ(internal_state_64_0, cwg64_0._internal_state.state);


        //-- tests copy constructor
        {
            Cwg64 cwg64(cwg64_1);

            EXPECT_EQ(cwg64_1._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_1._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_1._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            Cwg64 cwg64_mem(cwg64_0);
            Cwg64 cwg64(std::move(cwg64_mem));

            EXPECT_EQ(cwg64_0._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_0._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_0._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Cwg64 cwg64;

            cwg64 = cwg64_1;
            EXPECT_EQ(cwg64_1._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_1._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_1._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Cwg64 cwg64;

        {
            Cwg64 cwg64_mem(cwg64_0);
            cwg64 = std::move(cwg64_mem);

            EXPECT_EQ(cwg64_0._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_0._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_0._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);
        }


        //-- tests seed()
        cwg64.seed();

        EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(cwg64_1._internal_state.state.s, cwg64._internal_state.state.s);  // (1 over 2^64 risk)
        EXPECT_NE(cwg64_1._internal_state.state.state, cwg64._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);


        //-- tests seed(value)
        cwg64.seed(-1);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c21, cwg64._internal_state.state.s);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(1);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x910a2dec89025cc1, cwg64._internal_state.state.s);
        EXPECT_EQ(0xbeeb8da1658eec67, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(-2);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xf3203e9039f4a821, cwg64._internal_state.state.s);
        EXPECT_EQ(0xba56949915dcf9e9, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(9L);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xaeaf52febe706065, cwg64._internal_state.state.s);
        EXPECT_EQ(0xc02d8a5e87afea62, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(-11L);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x6fc5530939fb94c3, cwg64._internal_state.state.s);
        EXPECT_EQ(0x96caee613260cfca, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(17UL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x808475f02ee37363, cwg64._internal_state.state.s);
        EXPECT_EQ(0x6434ff62b4e8edd1, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x157a3807a48faa9d, cwg64._internal_state.state.s);
        EXPECT_EQ(0xd573529b34a1d093, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x48bbc5b84275f3cb, cwg64._internal_state.state.s);
        EXPECT_EQ(0xe2fbc345a799b5aa, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xeede014d9a5a6109, cwg64._internal_state.state.s);
        EXPECT_EQ(0xa6eb6466bac9f251, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(0.357);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x5fee464f36fc42c3, cwg64._internal_state.state.s);
        EXPECT_EQ(0x954faf5a9ad49cf8, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg64._internal_state.state.s);
        EXPECT_EQ(0xec779c3693f88501, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        EXPECT_THROW(cwg64.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(cwg64.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        // Notice: hard coded value below have been evaluated with PyRandLib
        cwg64._setstate(-1LL);
        EXPECT_EQ(0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xe4d9'7177'1b65'2c20 | 1, cwg64._internal_state.state.s);
        EXPECT_EQ(0xe99f'f867'dbf6'82c9, cwg64._internal_state.state.state);
        EXPECT_EQ(0, cwg64._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg64._internal_state.gauss_next);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        cwg64.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint32_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);
        
        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 50) {
            for (int i=0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[cwg64(ENTRIES_COUNT)]++;
            ++n;
            if (utils::get_time_ms() - start_ms >= 1000)
                break;  // no evaluation during more than 1 second duration
        }

        const std::uint64_t nloops{ n * INTERNAL_LOOPS_COUNT };
        EXPECT_TRUE(hist.is_mean_median_difference_ok(nloops));
        EXPECT_TRUE(hist.is_stdev_ok(nloops));
        EXPECT_TRUE(hist.is_variance_ok());
        
    }

}
