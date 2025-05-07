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

#include "fastrand32.h"
#include "g_utils/histogram.h"
#include "utils/time.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsFastRand32)
    {
        //-- tests empty constructor
        FastRand32 frand32_1;

        EXPECT_NE(0UL, frand32_1._internal_state.state);  // Well, one chance over 2^32 that this will occur...
        EXPECT_FALSE(frand32_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32_1._internal_state.gauss_next);


        //-- tests Valued construtor (seed) AND next()
        {
            FastRand32 frand32(1);

            EXPECT_EQ(0x910a2dec, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0xd767c1fd, 0x84ed309a, 0xae01bd53, 0x2b54d278, 0xd414a219 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xd414a219, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(-2);

            EXPECT_EQ(0xf3203e90, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x928f6951, 0xe8172de, 0xa35c41c7, 0xc1fec75c, 0x108150ad };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0x108150ad, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(9);

            EXPECT_EQ(0xaeaf52fe, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x1c9a5b67, 0x19a66c7c, 0x6a432b4d, 0xac4995aa, 0x49307b23 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0x49307b23, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(-11);

            EXPECT_EQ(0x6fc55309, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0xd943f336, 0x61f9803f, 0xa08de574, 0xabbba1e5, 0xae5e4562 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xae5e4562, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(17);

            EXPECT_EQ(0x808475f0, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x19ffa131, 0x6e14913e, 0xc31674a7, 0xd18ee4bc, 0xf5c6b68d };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xf5c6b68d, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(81985529216486895);

            EXPECT_EQ(0x157a3807, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x9fbe389c, 0xcccf40ed, 0xc93006ca, 0x9297b1c3, 0xc9434028 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xc9434028, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(-8870000000000000000);

            EXPECT_EQ(0x48bbc5b8, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x8d1fac59, 0x4a768846, 0x2e1cae0f, 0xfdd2504, 0x13fbd835 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0x13fbd835, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(8870000000000000000);

            EXPECT_EQ(0xeede014d, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x8f24f3aa, 0x74a0c123, 0x4fac7008, 0xfece1e69, 0xa102af16 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xa102af16, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(-0.357);

            EXPECT_EQ(0x5fee464f, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x31af5044, 0xbaba75, 0xcb7440b2, 0x1412d88b, 0xe0a17650 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xe0a17650, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }
        {
            FastRand32 frand32(8.87e+18);

            EXPECT_EQ(0xeede014d, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0x8f24f3aa, 0x74a0c123, 0x4fac7008, 0xfece1e69, 0xa102af16 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xa102af16, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }

        /** /
        //-- tests Valued constructor (full state).
        CollatzWeylState<std::uint64_t, std::uint64_t>   internal_state_64_0;
        FastRand32 frand32_0(internal_state_64_0);

        EXPECT_EQ(internal_state_64_0, frand32_0._internal_state.state);


        //-- tests copy constructor
        {
            FastRand32 frand32(frand32_1);

            EXPECT_EQ(frand32_1._internal_state.state, frand32._internal_state.state);
            EXPECT_EQ(frand32_1._internal_state.gauss_next, frand32._internal_state.gauss_next);
            EXPECT_EQ(frand32_1._internal_state.gauss_valid, frand32._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            FastRand32 frand32_mem(frand32_0);
            FastRand32 frand32(std::move(frand32_mem));

            EXPECT_EQ(frand32_0._internal_state.state, frand32._internal_state.state);
            EXPECT_EQ(frand32_0._internal_state.gauss_next, frand32._internal_state.gauss_next);
            EXPECT_EQ(frand32_0._internal_state.gauss_valid, frand32._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            FastRand32 frand32;

            frand32 = frand32_1;
            EXPECT_EQ(frand32_1._internal_state.state, frand32._internal_state.state);
            EXPECT_EQ(frand32_1._internal_state.gauss_next, frand32._internal_state.gauss_next);
            EXPECT_EQ(frand32_1._internal_state.gauss_valid, frand32._internal_state.gauss_valid);
        }


        //-- tests move assignement
        FastRand32 frand32;

        {
            FastRand32 frand32_mem(frand32_0);
            frand32 = std::move(frand32_mem);

            EXPECT_EQ(frand32_0._internal_state.state, frand32._internal_state.state);
            EXPECT_EQ(frand32_0._internal_state.gauss_next, frand32._internal_state.gauss_next);
            EXPECT_EQ(frand32_0._internal_state.gauss_valid, frand32._internal_state.gauss_valid);
        }


        //-- tests seed()
        frand32.seed();

        EXPECT_EQ(0ULL, frand32._internal_state.state.a);
        EXPECT_EQ(1ULL, frand32._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, frand32._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(frand32_1._internal_state.state.s, frand32._internal_state.state.s);  // (1 over 2^64 risk)
        EXPECT_NE(frand32_1._internal_state.state.state, frand32._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, frand32._internal_state.state.weyl);


        //-- tests seed(value)
        frand32.seed(-1);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c21, frand32._internal_state.state.s);
        EXPECT_EQ(0xe99ff867dbf682c9, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(1);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0x910a2dec89025cc1, frand32._internal_state.state.s);
        EXPECT_EQ(0xbeeb8da1658eec67, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(-2);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0xf3203e9039f4a821, frand32._internal_state.state.s);
        EXPECT_EQ(0xba56949915dcf9e9, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(9L);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0xaeaf52febe706065, frand32._internal_state.state.s);
        EXPECT_EQ(0xc02d8a5e87afea62, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(-11L);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0x6fc5530939fb94c3, frand32._internal_state.state.s);
        EXPECT_EQ(0x96caee613260cfca, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(17UL);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0x808475f02ee37363, frand32._internal_state.state.s);
        EXPECT_EQ(0x6434ff62b4e8edd1, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0x157a3807a48faa9d, frand32._internal_state.state.s);
        EXPECT_EQ(0xd573529b34a1d093, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0x48bbc5b84275f3cb, frand32._internal_state.state.s);
        EXPECT_EQ(0xe2fbc345a799b5aa, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0xeede014d9a5a6109, frand32._internal_state.state.s);
        EXPECT_EQ(0xa6eb6466bac9f251, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(-0.357);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0x5fee464f36fc42c3, frand32._internal_state.state.s);
        EXPECT_EQ(0x954faf5a9ad49cf8, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

        frand32.seed(8.87e+18);
        EXPECT_EQ(0x0, frand32._internal_state.state.a);
        EXPECT_EQ(0xeede014d9a5a6109, frand32._internal_state.state.s);
        EXPECT_EQ(0xa6eb6466bac9f251, frand32._internal_state.state.state);
        EXPECT_EQ(0x0, frand32._internal_state.state.weyl);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);


        //-- tests _setstate(seed_)
        // Notice: hard coded value below have been evaluated with PyRandLib
        {
            FastRand32 frand32(-1);

            EXPECT_EQ(0xe4d97177, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);

            const std::uint32_t expected[]{ 0xbe59e74c, 0xe60913dd, 0xbf2420fa, 0x6951a33, 0xf1ed91d8 };
            for (std::uint32_t e : expected)
                EXPECT_EQ(e, frand32.next());

            EXPECT_EQ(0xf1ed91d8, frand32._internal_state.state);
            EXPECT_FALSE(frand32._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand32._internal_state.gauss_next);
        }

        frand32._setstate(-1LL);
        EXPECT_EQ(0, frand32._internal_state.state.a);
        EXPECT_EQ(0xe4d9'7177'1b65'2c20 | 1, frand32._internal_state.state.s);
        EXPECT_EQ(0xe99f'f867'dbf6'82c9, frand32._internal_state.state.state);
        EXPECT_EQ(0, frand32._internal_state.state.weyl);
        EXPECT_EQ(0.0, frand32._internal_state.gauss_next);
        EXPECT_FALSE(frand32._internal_state.gauss_valid);

        /**/


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        FastRand32 frand32;  // TO BE REMOVED

        frand32.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint32_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 50) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[frand32(ENTRIES_COUNT)]++;
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
