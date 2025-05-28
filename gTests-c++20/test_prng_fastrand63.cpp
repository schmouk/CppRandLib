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

#include "fastrand63.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsFastRand63)
    {
        //-- tests empty constructor
        FastRand63 frand63_1;

        EXPECT_NE(0UL, frand63_1._internal_state.state);  // Well, one chance over 2^32 that this will occur...
        EXPECT_FALSE(frand63_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63_1._internal_state.gauss_next);


        //-- tests Valued construtor (seed) AND next()
        {
            FastRand63 frand63(1);

            EXPECT_EQ(0x488516f644812e60, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x1e8b7bf8ca5f91e1, 0x54491bb4578e74d6, 0xdcbc269442bcf, 0x92d1d243d7c6c9c, 0x13db4f804bab9f4d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x13db4f804bab9f4d, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(-2);

            EXPECT_EQ(0x79901f481cfa5410, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x47bfcf11e89afb51, 0x11402266f47c9506, 0x4d7d4881a47491bf, 0x6f312c89e1b2734c, 0x6628b79b8b02ddbd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x6628b79b8b02ddbd, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(9);

            EXPECT_EQ(0x5757a97f5f383032, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x42afbf246e9188db, 0x474a9d5a9c4bdf18, 0x6b792f175541cdf9, 0x7cce1c68412dc3ce, 0x78045fdce71afb27 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x78045fdce71afb27, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(-11);

            EXPECT_EQ(0x37e2a9849cfdca61, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x1db0452e40cac756, 0x5e24308f0c6c604f, 0x6fccd2bb2024eb1c, 0x64e07c3b854fefcd, 0x414d5992a1492db2 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x414d5992a1492db2, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(17);

            EXPECT_EQ(0x40423af81771b9b1, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x64a3d459e806f6e6, 0x3f07a4a0c682d1f, 0x3b724be56392d62c, 0x18f8bb2c22dee1d, 0x1df22b26dfa53842 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x1df22b26dfa53842, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(81985529216486895);

            EXPECT_EQ(0xabd1c03d247d54e, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x3f518f7da727aa7, 0x589fb832e7310d54, 0x77dbcffa81e88b65, 0x2e702905e2ada22a, 0x7190c03af2215733 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x7190c03af2215733, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(-8870000000000000000);

            EXPECT_EQ(0x245de2dc213af9e5, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x3132dfd6516ca2aa, 0x268ce62246111b3, 0x480f36f43f7a01d0, 0x547e97549d592411, 0x4699ced776bbf4c6 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x4699ced776bbf4c6, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(8870000000000000000);

            EXPECT_EQ(0x776f00a6cd2d3084, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xe7a713e523b5055, 0x24116e3c9d1013da, 0x4c732d382a287ca3, 0x6db715fa55425180, 0x3dcc3409fbfcbf81 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x3dcc3409fbfcbf81, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(0.357);

            EXPECT_EQ(0x2ff723279b7e2161, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xdeb2cba2da18a56, 0x294eb076730e7f4f, 0x5d1e3c047b74161c, 0x1c3be0f3f7a196cd, 0x15fc89176e9980b2 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x15fc89176e9980b2, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }
        {
            FastRand63 frand63(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0x7baf8265dad0d0ee, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x55d0edc0b3f21ac7, 0x54cb06fa46a25bf4, 0x529c74f268211a85, 0xd8196a6392b2bca, 0x41ad42933ba3dd53 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, frand63.next());

            EXPECT_EQ(0x41ad42933ba3dd53, frand63._internal_state.state);
            EXPECT_FALSE(frand63._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);
        }

        EXPECT_THROW(FastRand63(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(FastRand63(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            FastRand63 frand63(frand63_1);

            EXPECT_EQ(frand63_1._internal_state.state, frand63._internal_state.state);
            EXPECT_EQ(frand63_1._internal_state.gauss_next, frand63._internal_state.gauss_next);
            EXPECT_EQ(frand63_1._internal_state.gauss_valid, frand63._internal_state.gauss_valid);
        }


        //-- tests move constructor
        FastRand63 frand63_0;

        {
            FastRand63 frand63_mem(frand63_0);
            FastRand63 frand63(std::move(frand63_mem));

            EXPECT_EQ(frand63_0._internal_state.state, frand63._internal_state.state);
            EXPECT_EQ(frand63_0._internal_state.gauss_next, frand63._internal_state.gauss_next);
            EXPECT_EQ(frand63_0._internal_state.gauss_valid, frand63._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            FastRand63 frand63;

            frand63 = frand63_1;
            EXPECT_EQ(frand63_1._internal_state.state, frand63._internal_state.state);
            EXPECT_EQ(frand63_1._internal_state.gauss_next, frand63._internal_state.gauss_next);
            EXPECT_EQ(frand63_1._internal_state.gauss_valid, frand63._internal_state.gauss_valid);
        }


        //-- tests move assignement
        FastRand63 frand63;

        {
            FastRand63 frand63_mem(frand63_0);
            frand63 = std::move(frand63_mem);

            EXPECT_EQ(frand63_0._internal_state.state, frand63._internal_state.state);
            EXPECT_EQ(frand63_0._internal_state.gauss_next, frand63._internal_state.gauss_next);
            EXPECT_EQ(frand63_0._internal_state.gauss_valid, frand63._internal_state.gauss_valid);
        }


        //-- tests seed()
        frand63.seed();
        EXPECT_NE(0ULL, frand63._internal_state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)


        //-- tests seed(value)
        frand63.seed(1);
        EXPECT_EQ(0x488516f644812e60, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(-2);
        EXPECT_EQ(0x79901f481cfa5410, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(9L);
        EXPECT_EQ(0x5757a97f5f383032, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(-11L);
        EXPECT_EQ(0x37e2a9849cfdca61, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(17UL);
        EXPECT_EQ(0x40423af81771b9b1, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0xabd1c03d247d54e, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x245de2dc213af9e5, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x776f00a6cd2d3084, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(0.357);
        EXPECT_EQ(0x2ff723279b7e2161, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0x7baf8265dad0d0ee, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        EXPECT_THROW(frand63.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(frand63.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        // Notice: hard coded value below have been evaluated with PyRandLib
        frand63._setstate(-1LL);
        EXPECT_EQ(0x726cb8bb8db29610, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);

        frand63._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0x7baf8265dad0d0ee, frand63._internal_state.state);
        EXPECT_FALSE(frand63._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, frand63._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        frand63.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 100) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)frand63(ENTRIES_COUNT)]++;
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
