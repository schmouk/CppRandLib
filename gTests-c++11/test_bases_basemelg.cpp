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

#include "baseclasses/basemelg.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseMelg)
    {
        //-- tests empty constructor
        {
            constexpr int N{ 5 };
            BaseMELG<N> melg;

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_NE(0, melg._internal_state.state.list[0]);
            for (int i = 1; i < N; ++i) {
                EXPECT_NE(0ULL, melg._internal_state.state.list[i]);
                EXPECT_NE(melg._internal_state.state.list[i - 1], melg._internal_state.state.list[i]);
            }
        }


        // notice: all hard coded belowing value have been evaluated with PyRandLib

        //-- tests Valued construtor (seed).
        {
            BaseMELG<5> melg(1);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x910a2dec89025cc1, 0xbeeb8da1658eec67, 0xf893a2eefb32555e, 0x71c18690ee42c90b, 0x71bb54d8d101b5b9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(-2);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf3203e9039f4a821, 0xba56949915dcf9e9, 0xd0d5127a96e8d90d, 0x1ef156bb76650c37, 0x7842841591543f1d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(9L);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xaeaf52febe706064, 0xc02d8a5e87afea62, 0x43ec2be544b589b6, 0xc8e98cd697316060, 0x4336b3782f5887a1 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(-11L);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x6fc5530939fb94c3, 0x96caee613260cfca, 0x46d40b90622a734b, 0x6ecc725d7bedada9, 0x69e6fff0691d876d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(17UL);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x808475f02ee37363, 0x6434ff62b4e8edd1, 0x540d6c3702d41b8c, 0x395142ca8efaf003, 0x46b1664f61a205e };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x48bbc5b84275f3ca, 0xe2fbc345a799b5aa, 0x86ce19a135fba0de, 0x637c87187035ea06, 0x2a03b9aff2bfd421 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xeede014d9a5a6108, 0xa6eb6466bac9f251, 0x4246cbb1a64bf70c, 0xaf6aa8f43ebb8659, 0xe1b0fb2c7e764cdb };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            BaseMELG<5> melg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
            EXPECT_EQ(0, melg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf75f04cbb5a1a1dd, 0xec779c3693f88501, 0xfed9eeb4936de39d, 0x6f9fb04b092bd30a, 0x260ffb0260bbbe5f };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }

        EXPECT_THROW(BaseMELG<5>(-0.357), FloatValueRange01Exception);
        EXPECT_THROW(BaseMELG<5>(8.87e+18), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        {
            BaseMELG<5>::state_type st_5;
            st_5.seed(133ULL);
            st_5.index = 3;
            BaseMELG<5> melg_5(st_5);

            EXPECT_EQ(st_5.index, melg_5._internal_state.state.index);
            EXPECT_EQ(st_5.list, melg_5._internal_state.state.list);
        }


        //-- tests copy constructor
        {
            BaseMELG<5> melg_5(129);
            BaseMELG<5> melg(melg_5);

            EXPECT_EQ(melg_5._internal_state.state.index, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(melg_5._internal_state.state.list[i], melg._internal_state.state.list[i]);
            EXPECT_EQ(melg_5._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_5._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            BaseMELG<5> melg_5(129), melg_tmp(129);
            BaseMELG<5> melg(std::move(melg_tmp));

            EXPECT_EQ(melg_5._internal_state.state.index, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(melg_5._internal_state.state.list[i], melg._internal_state.state.list[i]);
                EXPECT_EQ(melg_5._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_5._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            BaseMELG<5> melg_5(129);
            BaseMELG<5> melg;

            melg = melg_5;

            EXPECT_EQ(melg_5._internal_state.state.index, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(melg_5._internal_state.state.list[i], melg._internal_state.state.list[i]);
            EXPECT_EQ(melg_5._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_5._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move assignment
        {
            BaseMELG<5> melg_5(129), melg_tmp(129);
            BaseMELG<5> melg;
            
            melg = std::move(melg_tmp);

            EXPECT_EQ(melg_5._internal_state.state.index, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(melg_5._internal_state.state.list[i], melg._internal_state.state.list[i]);
            EXPECT_EQ(melg_5._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_5._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests seed()
        {
            BaseMELG<5> melg;
            BaseMELG<5> melg_5;
            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // just to ensure different system times for seeding
            melg.seed();

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0, melg_5._internal_state.state.index);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_FALSE(melg_5._internal_state.gauss_valid);
            bool diff{ false };
            for (int i = 0; i < 5; ++i)
                if (melg._internal_state.state.list[i] != melg_5._internal_state.state.list[i]) {
                    diff = true;
                    break;
                }
            EXPECT_TRUE(diff);
        }


        //-- tests seed(value)
        BaseMELG<5> melg;
        {
            melg.seed(28031L);

            std::uint64_t expected[5]{
                0x2705'aecd'4f8c'9690, 0x72100965d36abc80, 0x663e'44c5'f050'c8fb,
                0x9756'21c9'1513'33a5, 0xc269b7b2092500b7
            };

            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_EQ(0, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            melg.seed(28032UL);

            std::uint64_t expected[5]{
                0xbf0a5635a9341d88, 0x9d72bf564a7f9995, 0x61a8c168da5def3a,
                0x1033569f139833aa, 0xa6d7a3f6d50224c0
            };

            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_EQ(0, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            melg.seed(-1LL);

            std::uint64_t expected[5]{
                0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9,
                0x6d1db36ccba982d2, 0xb4a0472e578069ae
            };

            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_EQ(0, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            melg.seed(0xffff'ffff'ffff'ffffULL);

            std::uint64_t expected[5]{
                0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9,
                0x6d1db36ccba982d2, 0xb4a0472e578069ae
            };

            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_EQ(0, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            melg.seed(0.187);

            std::uint64_t expected[5]{
                0x2b18160c0a9f05b4, 0xc8197d13a4d6d45f, 0xaca007e67e920ed1,
                0xf0e779fe3279121f, 0xcd551efd3099f223
            };

            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_EQ(0, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }
        {
            melg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            std::uint64_t expected[5]{
                0xf75f04cbb5a1a1dd, 0xec779c3693f88501, 0xfed9eeb4936de39d,
                0x6f9fb04b092bd30a, 0x260ffb0260bbbe5f
            };

            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_EQ(0, melg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }

        EXPECT_THROW(melg.seed(-0.001), FloatValueRange01Exception);
        EXPECT_THROW(melg.seed(1.0), FloatValueRange01Exception);


        //-- tests _setstate()
        {
            BaseMELG<5> melg;
            melg._setstate(0xa876'cb13'e2f0'594d);
            std::uint64_t expected[]{ 0xe7186b7b3854a9bc, 0x4689d02b25c81d1, 0x9daeb55b5a2ef996, 0xa28288978dd3cea5, 0xa9fa0fe2f8412ebe };

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], melg._internal_state.state.list[i]);
        }

    }

}
