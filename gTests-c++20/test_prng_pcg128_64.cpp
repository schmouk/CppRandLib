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

#include "g_utils/histogram.h"
#include "pcg128_64.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsPcg128_64)
    {
        //-- tests empty constructor
        Pcg128_64 pcg_1;

        EXPECT_NE(0ULL, pcg_1._internal_state.state);  // notice: 1 over 2^128 risk that state is zero
        EXPECT_FALSE(pcg_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Pcg128_64 pcg(1);

            EXPECT_EQ(utils::UInt128(0x0000000000000001, 0xfffffffffffffffe), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0x67edbc92ac518991ULL, 0xfb5bd5e201b571a8ULL, 0xe8628ad72b23b4c0ULL, 0xc2722d77d9a50970ULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0xc40120e741540b65, 0x5973d6ce5b782899), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(-2);

            EXPECT_EQ(utils::UInt128(0xfffffffffffffffe, 0x0000000000000001), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0x1963c455dfac3e9dULL, 0x2921be25fcc5113aULL, 0xd9c4377d1bc7d6f5ULL, 0x1e95a9af631c3bbfULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0xac01c10183cfadee, 0x9eac6e4920629ef8), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(9UL);

            EXPECT_EQ(utils::UInt128(0x0000000000000009, 0xfffffffffffffff6), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0xe3d6ca5fa7a426a9ULL, 0x7642b641bf257334ULL, 0xc32a5547abc74ba7ULL, 0xec6a8ab3cb7a8198ULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0xc677d2dec48f4614, 0xa0dced86f906ecf1), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(-11L);

            EXPECT_EQ(utils::UInt128(0xfffffffffffffff5, 0x000000000000000a), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0xaa86099efb2a1641ULL, 0x839a3cda9513aad3ULL, 0x35d3a7e4cfdbde47ULL, 0xeddae6ff06f70ce3ULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0xa93c38cb102d0be9, 0x6e5634b96f220215), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(17ULL);

            EXPECT_EQ(utils::UInt128(0x0000000000000011, 0xffffffffffffffee), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0x3fdfc8283f39c4e2ULL, 0x624e1496142469fbULL, 0x6c96f27c2b23bb76ULL, 0x505454d17bb9c7c4ULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0xc8ee84d647ca80c3, 0xe846043f9695b149), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(0x0123'4567'89ab'cdefULL);

            EXPECT_EQ(utils::UInt128(0x0123456789abcdef, 0xfedcba9876543210), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0x13c49fecdee35f71ULL, 0x4ee9574cc31f57d2ULL, 0x718b9867b2c7ef05ULL, 0xa9b3898995846d5cULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0x08ab2233cb87c6d6, 0x2bf161231d0fc8d3), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(-8870000000000000000LL);

            EXPECT_EQ(utils::UInt128(0x84e76dfeca490000, 0x7b18920135b6ffff), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0xeb5e877843114419ULL, 0xf9977cfa5bb83c83ULL, 0x2c9b122af29c4817ULL, 0x439551d6d0a1e7cfULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0x9d8dff09fb8fcb16, 0x6a7aaf75b569500e), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(8870000000000000000);

            EXPECT_EQ(utils::UInt128(0x7b18920135b70000, 0x84e76dfeca48ffff), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0x7d18788598e98884ULL, 0xd37d4c6ae1627ad1ULL, 0x1a332b2e50c187e4ULL, 0x551970cd6b82ad95ULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0xd2c3b91db9fb5593, 0x7692b878da23500e), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(0.357);

            EXPECT_EQ(utils::UInt128(0x5b645a1cac083000, 0x0000000000000000), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x20c0016d916872b0ULL, 0x7b9897ebf33ccfe3ULL, 0x55b49f0fe1223331ULL, 0xa441c2f7b505f885ULL, 0xf62f46d0314e73c7ULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0x08067877df932cb9, 0x8799912034147783), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg128_64 pcg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x0000000000000006ULL, 0x3a155d7c5ef8f6a4ULL, 0xd201f88a2ca35bd8ULL, 0x52b144175afe0a9dULL, 0xc1ce58340ac335b6ULL };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(utils::UInt128(0x680482828082d4e7, 0x4260f9a56f2a0124), pcg._internal_state.state);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }

        EXPECT_THROW(Pcg128_64(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Pcg128_64(1.0001), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Pcg128_64 pcg(pcg_1);

            EXPECT_TRUE(pcg_1._internal_state.state == pcg._internal_state.state);
            EXPECT_EQ(pcg_1._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_1._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Pcg128_64 pcg_0;

        {
            Pcg128_64 pcg_mem(pcg_0);
            Pcg128_64 pcg(std::move(pcg_mem));

            EXPECT_TRUE(pcg_0._internal_state.state == pcg._internal_state.state);
            EXPECT_EQ(pcg_0._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_0._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Pcg128_64 pcg;

            pcg = pcg_1;
            EXPECT_TRUE(pcg_1._internal_state.state == pcg._internal_state.state);
            EXPECT_EQ(pcg_1._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_1._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Pcg128_64 pcg;
        {
            Pcg128_64 pcg_mem(pcg_0);
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
        EXPECT_EQ(utils::UInt128(0xffffffffffffffff, 0x0000000000000000), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0xffffffffffffffffULL, 0x38064b7db2dd784dULL, 0xce6b76120714062aULL, 0x98b240ab6e76ef59ULL, 0x69f945133d93081bULL };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, pcg.next());
        EXPECT_EQ(utils::UInt128(0xac50974074371544, 0x8799912034147783), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(1);
        EXPECT_EQ(utils::UInt128(0x0000000000000001, 0xfffffffffffffffe), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-2);
        EXPECT_EQ(utils::UInt128(0xfffffffffffffffe, 0x0000000000000001), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(9L);
        EXPECT_EQ(utils::UInt128(0x0000000000000009, 0xfffffffffffffff6), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-11L);
        EXPECT_EQ(utils::UInt128(0xfffffffffffffff5, 0x000000000000000a), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(17UL);
        EXPECT_EQ(utils::UInt128(0x0000000000000011, 0xffffffffffffffee), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(utils::UInt128(0x0123456789abcdef, 0xfedcba9876543210), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(utils::UInt128(0x84e76dfeca490000, 0x7b18920135b6ffff), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(utils::UInt128(0x7b18920135b70000, 0x84e76dfeca48ffff), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(0.357);
        EXPECT_EQ(utils::UInt128(0x5b645a1cac083000, 0x0000000000000000), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        EXPECT_THROW(pcg.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(pcg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        pcg._setstate(-1LL);
        EXPECT_EQ(utils::UInt128(0xffff'ffff'ffff'ffff, 0x0000'0000'0000'0000), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd), pcg._internal_state.state);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        pcg.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        const std::uint64_t start_ms{ utils::get_time_ms() };
        do {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)pcg(ENTRIES_COUNT)]++;
        } while (++n < 100 && utils::get_time_ms() - start_ms < 1000);  //  not more than 1 second of tests

        const std::uint64_t nloops{ n * INTERNAL_LOOPS_COUNT };
        EXPECT_TRUE(hist.is_mean_median_difference_ok(nloops));
        EXPECT_TRUE(hist.is_stdev_ok(nloops));
        EXPECT_TRUE(hist.is_variance_ok());

    }

}
