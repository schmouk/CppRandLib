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
#include <chrono>
#include <thread>

#include "gtest/gtest.h"

#include "baseclasses/basewell.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseWell)
    {
        //-- tests empty constructor
        {
            constexpr int N{ 5 };
            BaseWell<N> wll;

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_NE(0, wll._internal_state.state.list[0]);
            for (int i = 1; i < N; ++i) {
                EXPECT_NE(0ULL, wll._internal_state.state.list[i]);
                EXPECT_NE(wll._internal_state.state.list[i - 1], wll._internal_state.state.list[i]);
            }
        }


        // notice: all hard coded belowing value have been evaluated with PyRandLib

        //-- tests Valued construtor (seed).
        {
            BaseWell<5> wll(1);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x910a2dec, 0xbeeb8da1, 0xf893a2ee, 0x71c18690, 0x71bb54d8 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(-2);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf3203e90, 0xba569499, 0xd0d5127a, 0x1ef156bb, 0x78428415 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(9L);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0xaeaf52fe, 0xc02d8a5e, 0x43ec2be5, 0xc8e98cd6, 0x4336b378 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(-11L);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x6fc55309, 0x96caee61, 0x46d40b90, 0x6ecc725d, 0x69e6fff0 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(17UL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x808475f0, 0x6434ff62, 0x540d6c37, 0x395142ca, 0x046b1664 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807, 0xd573529b, 0x2f90b72e, 0xa2d41933, 0x1404ce9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x48bbc5b8, 0xe2fbc345, 0x86ce19a1, 0x637c8718, 0x2a03b9af };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0xeede014d, 0xa6eb6466, 0x4246cbb1, 0xaf6aa8f4, 0xe1b0fb2c };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807, 0xd573529b, 0x2f90b72e, 0xa2d41933, 0x1404ce9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            BaseWell<5> wll(0.357);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x5fee464f, 0x954faf5a, 0xa985465a, 0x77714db9, 0xa3aac457 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }

        EXPECT_THROW(BaseWell<5>(-0.357), FloatValueRange01Exception);
        EXPECT_THROW(BaseWell<5>(8.87e+18), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        {
            BaseWell<5>::state_type st_5;
            st_5.seed(133ULL);
            st_5.index = 3;
            BaseWell<5> wll_5(st_5);

            EXPECT_EQ(st_5.index, wll_5._internal_state.state.index);
            EXPECT_EQ(st_5.list, wll_5._internal_state.state.list);
        }


        //-- tests copy constructor
        {
            BaseWell<5> wll_5(129);
            BaseWell<5> wll(wll_5);

            EXPECT_EQ(wll_5._internal_state.state.index, wll._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(wll_5._internal_state.state.list[i], wll._internal_state.state.list[i]);
            EXPECT_EQ(wll_5._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_5._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            BaseWell<5> wll_5(129), mrg_tmp(129);
            BaseWell<5> wll(std::move(mrg_tmp));

            EXPECT_EQ(wll_5._internal_state.state.index, wll._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(wll_5._internal_state.state.list[i], wll._internal_state.state.list[i]);
            EXPECT_EQ(wll_5._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_5._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            BaseWell<5> wll_5(129);
            BaseWell<5> wll;

            wll = wll_5;

            EXPECT_EQ(wll_5._internal_state.state.index, wll._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(wll_5._internal_state.state.list[i], wll._internal_state.state.list[i]);
            EXPECT_EQ(wll_5._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_5._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move assignment
        {
            BaseWell<5> wll_5(129), mrg_tmp(129);
            BaseWell<5> wll;

            wll = std::move(mrg_tmp);

            EXPECT_EQ(wll_5._internal_state.state.index, wll._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(wll_5._internal_state.state.list[i], wll._internal_state.state.list[i]);
            EXPECT_EQ(wll_5._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_5._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests seed()
        {
            BaseWell<5> wll;
            BaseWell<5> wll_5;
            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // just to ensure different system times for seeding
            wll.seed();

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0, wll_5._internal_state.state.index);
            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_FALSE(wll_5._internal_state.gauss_valid);
            bool diff{ false };
            for (int i = 0; i < 5; ++i)
                if (wll._internal_state.state.list[i] != wll_5._internal_state.state.list[i]) {
                    diff = true;
                    break;
                }
            EXPECT_TRUE(diff);
        }

        BaseWell<5> wll;

        {
            wll.seed(1);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x910a2dec, 0xbeeb8da1, 0xf893a2ee, 0x71c18690, 0x71bb54d8 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(-2);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf3203e90, 0xba569499, 0xd0d5127a, 0x1ef156bb, 0x78428415 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(9L);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0xaeaf52fe, 0xc02d8a5e, 0x43ec2be5, 0xc8e98cd6, 0x4336b378 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(-11L);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x6fc55309, 0x96caee61, 0x46d40b90, 0x6ecc725d, 0x69e6fff0 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(17UL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x808475f0, 0x6434ff62, 0x540d6c37, 0x395142ca, 0x046b1664 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807, 0xd573529b, 0x2f90b72e, 0xa2d41933, 0x1404ce9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x48bbc5b8, 0xe2fbc345, 0x86ce19a1, 0x637c8718, 0x2a03b9af };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0xeede014d, 0xa6eb6466, 0x4246cbb1, 0xaf6aa8f4, 0xe1b0fb2c };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807, 0xd573529b, 0x2f90b72e, 0xa2d41933, 0x1404ce9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }
        {
            wll.seed(0.357);
            EXPECT_EQ(0, wll._internal_state.state.index);
            const std::uint64_t expected[]{ 0x5fee464f, 0x954faf5a, 0xa985465a, 0x77714db9, 0xa3aac457 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }



        //-- tests _setstate()
        {
            BaseWell<5> wll;
            wll._setstate(0xa876'cb13'e2f0'594d);
            std::uint64_t expected[]{ 0xe7186b7b, 0x4689d02, 0x9daeb55b, 0xa2828897, 0xa9fa0fe2 };

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], wll._internal_state.state.list[i]);
        }

    }

}
