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
#include <algorithm>
#include <cstdint>

#include "gtest/gtest.h"

#include "pcg64_32.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsPcg64_32)
    {
        //-- tests empty constructor
        Pcg64_32 pcg_1;

        EXPECT_NE(0ULL, pcg_1._internal_state.state);  // notice: 1 over 2^64 risk that state is zero
        EXPECT_FALSE(pcg_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Pcg64_32 pcg(1);

            EXPECT_EQ(0x0000000000000001ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x00000000UL, 0x2bb70e8fUL, 0x9a212e89UL, 0xbf5c61d9UL, 0x01aa228eUL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0xcba276b4b881a9f0ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(-2);

            EXPECT_EQ(0xfffffffffffffffeULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffe000UL, 0xb0c954ecUL, 0x49bde8a7UL, 0x3b69c9ffUL, 0x0dd2711aUL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x8f5af925b57121f9ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(9UL);

            EXPECT_EQ(0x0000000000000009ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x00000000UL, 0xce235a69UL, 0x56548d60UL, 0xf0f17546UL, 0xda583023UL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x170bc5876b5869d8ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(-11L);

            EXPECT_EQ(0xfffffffffffffff5ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffe000UL, 0x7ffcad53UL, 0x7b575b31UL, 0x8be105a2UL, 0x992452e9UL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0xda848078ac3f8a14ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(17ULL);

            EXPECT_EQ(0x0000000000000011ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x00000000UL, 0x8bb58a26UL, 0x8843c85cUL, 0x41785147UL, 0x5c117592UL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x6275145a1e2f29c0ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(0x0123'4567'89ab'cdefULL);

            EXPECT_EQ(0x0123456789abcdefULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x8d158c12UL, 0xc65b2172UL, 0xa18de728UL, 0x83d45f91UL, 0x1094d283UL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0xc60c9ae76aeb1026ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(-8870000000000000000LL);

            EXPECT_EQ(0x84e76dfeca490000ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x39dbfb55UL, 0xce80b9ceUL, 0x508070b4UL, 0x2aa645bbUL, 0x8c737806UL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x4effa1359b4bd1f3ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(8870000000000000000);

            EXPECT_EQ(0x7b18920135b70000ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x8c49f6abUL, 0x5d5ac1b3UL, 0x9e0acbf0UL, 0x9824604eUL, 0x097f8a5dUL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x756af87f2901d1f3ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(0.357);

            EXPECT_EQ(0x5b645a1cac083000ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x645b713dUL, 0x422a71daUL, 0x8b4de3efUL, 0x4fea2236UL, 0x4534954bUL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x8a988aac268e41f3ULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg64_32 pcg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0xfffffffffffffffdULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffe000UL, 0x3e7b6cbfUL, 0x07513d41UL, 0xf49d2d7eUL, 0x6735f6ffUL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x25edcf4b5f1649fcULL, pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }

        EXPECT_THROW(Pcg64_32(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Pcg64_32(1.0001), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Pcg64_32 pcg(pcg_1);

            EXPECT_TRUE(pcg_1._internal_state.state == pcg._internal_state.state);
            EXPECT_EQ(pcg_1._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_1._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Pcg64_32 pcg_0;

        {
            Pcg64_32 pcg_mem(pcg_0);
            Pcg64_32 pcg(std::move(pcg_mem));

            EXPECT_TRUE(pcg_0._internal_state.state == pcg._internal_state.state);
            EXPECT_EQ(pcg_0._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_0._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Pcg64_32 pcg;

            pcg = pcg_1;
            EXPECT_TRUE(pcg_1._internal_state.state == pcg._internal_state.state);
            EXPECT_EQ(pcg_1._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_1._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Pcg64_32 pcg;
        {
            Pcg64_32 pcg_mem(pcg_0);
            pcg = std::move(pcg_mem);

            EXPECT_TRUE(pcg_0._internal_state.state == pcg._internal_state.state);
            EXPECT_EQ(pcg_0._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_0._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests seed()
        pcg.seed();
        EXPECT_NE(0, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);


        //-- tests seed(value)
        pcg.seed(-1);
        EXPECT_EQ(0xffffffffffffffffULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0xffffe000UL, 0x7670b7ecUL, 0x352af524UL, 0xfc83253dUL, 0xb470d427UL };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, pcg.next());
        EXPECT_EQ(0xf8c823000bcbf9f6ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(1);
        EXPECT_EQ(0x0000000000000001ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-2);
        EXPECT_EQ(0xfffffffffffffffeULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(9L);
        EXPECT_EQ(0x0000000000000009ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-11L);
        EXPECT_EQ(0xfffffffffffffff5ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(17UL);
        EXPECT_EQ(0x0000000000000011ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0123456789abcdefULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x84e76dfeca490000ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x7b18920135b70000ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(0.357);
        EXPECT_EQ(0x5b645a1cac083000ULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0xfffffffffffffffdULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        EXPECT_THROW(pcg.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(pcg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        pcg._setstate(-1LL);
        EXPECT_EQ(0xffffffffffffffffULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0xfffffffffffffffdULL, pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        pcg.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 100) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)pcg(ENTRIES_COUNT)]++;
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
