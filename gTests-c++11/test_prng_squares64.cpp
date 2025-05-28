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

#include "squares64.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsSquares64)
    {
        //-- tests empty constructor
        Squares64 sqr_1;

        EXPECT_NE(0ULL, sqr_1._internal_state.state.key);  // notice: 1 over 2^64 risk that state is zero
        EXPECT_EQ(0ULL, sqr_1._internal_state.state.counter);
        EXPECT_FALSE(sqr_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Squares64 sqr(1);

            EXPECT_EQ(0x9bd658ae46c9d5e3, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xe98228c678a39846, 0x278241683a3d3709, 0xabd2b4ad3710b88d, 0x605b47f37f0987be, 0x6c6a1b461a98879a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0x9bd658ae46c9d5e3, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(-2);

            EXPECT_EQ(0xfbe269a13c127d8f, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x6f43ae813f77d13f, 0x9d0fa8e841fdd1c5, 0x14d7a26a41e60797, 0xade5ed22d22c19ad, 0x69de152af4bbb184 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0xfbe269a13c127d8f, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(9);

            EXPECT_EQ(0xbf4a3268dabe3f75, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc26f7178d0c7bc08, 0x4678cdbd833c78c7, 0x74df7e8b4aef61ea, 0x5e0727d32a9b1f8b, 0x55d1c678bd07658a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0xbf4a3268dabe3f75, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(-11);

            EXPECT_EQ(0x79465e8f732a18f5, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xcac26ba44abd410f, 0xbe6f7dfa2f252dc4, 0x0a082fc0dc7a4141, 0x009f57ded6cc456e, 0x9d614de227fb0446 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0x79465e8f732a18f5, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(17);

            EXPECT_EQ(0x86531bae9b4edf83, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x6e79e93c1dc2d0bb, 0xaf479d40c8092b6e, 0x9760ae83885159a6, 0x78978bff4b215b97, 0xee20c44640a520b3 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0x86531bae9b4edf83, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0x2c381b75cd1e96f3, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc65a668817cbf776, 0xea057f03dff8ccb4, 0x107ab4e28817d6f2, 0xfc483b9151876a4e, 0x8ce1c591aaaa8d56 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0x2c381b75cd1e96f3, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(-8870000000000000000);

            EXPECT_EQ(0x5d7f246839ae54f3, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x489ec9ff0bd9e138, 0x645b8bbdfc441cfb, 0x782c313a1f705381, 0x69773f36c7986494, 0x9580edfa1c4fb326 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0x5d7f246839ae54f3, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(8870000000000000000);

            EXPECT_EQ(0xea49fd182c19435d, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x6abbdde1fd79824e, 0xae76287031b7f176, 0xde0f27f1a01d61a8, 0x932703aff57d298b, 0xf6a112a583f4a2ac };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0xea49fd182c19435d, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(0.357);

            EXPECT_EQ(0x69ef8b1a6eda9b27, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf2b6259de7380a32, 0x5f5b62c6612937da, 0x6438f7df064a6375, 0xbbb674d3d702c2fc, 0x47f9ac1f4b93cf5c };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0x69ef8b1a6eda9b27, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            Squares64 sqr(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0xfde6215797c8adf3, sqr._internal_state.state.key);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf196008549e5c033, 0xb813fc6620b97ffb, 0x83739f8403d9902d, 0x19f5e60401e40225, 0xc4abc1714352f2a4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, sqr.next());

            EXPECT_EQ(0xfde6215797c8adf3, sqr._internal_state.state.key);
            EXPECT_EQ(5, sqr._internal_state.state.counter);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }

        EXPECT_THROW(Squares64(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Squares64(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Squares64 sqr(sqr_1);

            EXPECT_EQ(sqr_1._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_1._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_1._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_1._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Squares64 sqr_0;

        {
            Squares64 sqr_mem(sqr_0);
            Squares64 sqr(std::move(sqr_mem));

            EXPECT_EQ(sqr_0._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_0._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_0._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_0._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Squares64 sqr;

            sqr = sqr_1;
            EXPECT_EQ(sqr_1._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_1._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_1._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_1._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Squares64 sqr;
        {
            Squares64 sqr_mem(sqr_0);
            sqr = std::move(sqr_mem);

            EXPECT_EQ(sqr_0._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_0._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_0._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_0._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests seed()
        sqr.seed();
        EXPECT_NE(0, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);


        //-- tests seed(value)
        sqr.seed(-1);
        EXPECT_EQ(0xed3689af81d93a2d, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0x8f5daf139c962b21, 0xfaee88572e24554a, 0xed77e3490cf390cf, 0x2688add8ddf04e39, 0x848eb8048e411825 };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, sqr.next());
        EXPECT_EQ(0xed3689af81d93a2d, sqr._internal_state.state.key);
        EXPECT_EQ(5, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(1);
        EXPECT_EQ(0x9bd658ae46c9d5e3, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(-2);
        EXPECT_EQ(0xfbe269a13c127d8f, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(9L);
        EXPECT_EQ(0xbf4a3268dabe3f75, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(-11L);
        EXPECT_EQ(0x79465e8f732a18f5, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(17UL);
        EXPECT_EQ(0x86531bae9b4edf83, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x2c381b75cd1e96f3, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x5d7f246839ae54f3, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0xea49fd182c19435d, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(0.357);
        EXPECT_EQ(0x69ef8b1a6eda9b27, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0xfde6215797c8adf3, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        EXPECT_THROW(sqr.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(sqr.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        sqr._setstate(-1LL);
        EXPECT_EQ(0xed3689af81d93a2d, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);

        sqr._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0xfde6215797c8adf3, sqr._internal_state.state.key);
        EXPECT_EQ(0, sqr._internal_state.state.counter);
        EXPECT_FALSE(sqr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        sqr.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 100) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)sqr(ENTRIES_COUNT)]++;
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
