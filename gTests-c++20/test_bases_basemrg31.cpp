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

#include "baseclasses/basemrg31.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseMrg31)
    {
        //-- tests empty constructor
        {
            constexpr int N{ 5 };
            BaseMRG31<N> mrg;

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_NE(0, mrg._internal_state.state.list[0]);
            for (int i = 1; i < N; ++i) {
                EXPECT_NE(0ULL, mrg._internal_state.state.list[i]);
                EXPECT_NE(mrg._internal_state.state.list[i - 1], mrg._internal_state.state.list[i]);
            }
        }


        // notice: all hard coded belowing value have been evaluated with PyRandLib

        //-- tests Valued construtor (seed).
        {
            BaseMRG31<5> mrg(1);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x910a2dec89025cc1 >> 33, 0xbeeb8da1658eec67 >> 33, 0xf893a2eefb32555e >> 33, 0x71c18690ee42c90b >> 33, 0x71bb54d8d101b5b9 >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(-2);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf3203e9039f4a821 >> 33, 0xba56949915dcf9e9 >> 33, 0xd0d5127a96e8d90d >> 33, 0x1ef156bb76650c37 >> 33, 0x7842841591543f1d >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(9L);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xaeaf52febe706064 >> 33, 0xc02d8a5e87afea62 >> 33, 0x43ec2be544b589b6 >> 33, 0xc8e98cd697316060 >> 33, 0x4336b3782f5887a1 >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(-11L);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x6fc5530939fb94c3 >> 33, 0x96caee613260cfca >> 33, 0x46d40b90622a734b >> 33, 0x6ecc725d7bedada9 >> 33, 0x69e6fff0691d876d >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(17UL);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x808475f02ee37363 >> 33, 0x6434ff62b4e8edd1 >> 33, 0x540d6c3702d41b8c >> 33, 0x395142ca8efaf003 >> 33, 0x46b1664f61a205e >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d >> 33, 0xd573529b34a1d093 >> 33, 0x2f90b72e996dccbe >> 33, 0xa2d419334c4667ec >> 33, 0x1404ce914938008 >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0x48bbc5b84275f3ca >> 33, 0xe2fbc345a799b5aa >> 33, 0x86ce19a135fba0de >> 33, 0x637c87187035ea06 >> 33, 0x2a03b9aff2bfd421 >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xeede014d9a5a6108 >> 33, 0xa6eb6466bac9f251 >> 33, 0x4246cbb1a64bf70c >> 33, 0xaf6aa8f43ebb8659 >> 33, 0xe1b0fb2c7e764cdb >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
            EXPECT_EQ(0, mrg._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf75f04cbb5a1a1dd >> 33, 0xec779c3693f88501 >> 33, 0xfed9eeb4936de39d >> 33, 0x6f9fb04b092bd30a >> 33, 0x260ffb0260bbbe5f >> 33 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }

        EXPECT_THROW(BaseMRG31<5>(-0.357), FloatValueRange01Exception);
        EXPECT_THROW(BaseMRG31<5>(8.87e+18), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        {
            BaseMRG31<5>::state_type st_5;
            st_5.seed(133ULL);
            st_5.index = 3;
            BaseMRG31<5> mrg_5(st_5);

            EXPECT_EQ(st_5.index, mrg_5._internal_state.state.index);
            EXPECT_EQ(st_5.list, mrg_5._internal_state.state.list);
            EXPECT_FALSE(mrg_5._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg_5._internal_state.gauss_next);
        }


        //-- tests copy constructor
        {
            BaseMRG31<5> mrg_5(129);
            BaseMRG31<5> mrg(mrg_5);

            EXPECT_EQ(mrg_5._internal_state.state.index, mrg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(mrg_5._internal_state.state.list[i], mrg._internal_state.state.list[i]);
            EXPECT_EQ(mrg_5._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_5._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            BaseMRG31<5> mrg_5(129), mrg_tmp(129);
            BaseMRG31<5> mrg(std::move(mrg_tmp));

            EXPECT_EQ(mrg_5._internal_state.state.index, mrg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(mrg_5._internal_state.state.list[i], mrg._internal_state.state.list[i]);
            EXPECT_EQ(mrg_5._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_5._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            BaseMRG31<5> mrg_5(129);
            BaseMRG31<5> mrg;

            mrg = mrg_5;

            EXPECT_EQ(mrg_5._internal_state.state.index, mrg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(mrg_5._internal_state.state.list[i], mrg._internal_state.state.list[i]);
            EXPECT_EQ(mrg_5._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_5._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move assignment
        {
            BaseMRG31<5> mrg_5(129), mrg_tmp(129);
            BaseMRG31<5> mrg;

            mrg = std::move(mrg_tmp);

            EXPECT_EQ(mrg_5._internal_state.state.index, mrg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(mrg_5._internal_state.state.list[i], mrg._internal_state.state.list[i]);
            EXPECT_EQ(mrg_5._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_5._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests seed()
        {
            BaseMRG31<5> mrg;
            BaseMRG31<5> mrg_5;
            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // just to ensure different system times for seeding
            mrg.seed();

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0, mrg_5._internal_state.state.index);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_FALSE(mrg_5._internal_state.gauss_valid);
            bool diff{ false };
            for (int i = 0; i < 5; ++i)
                if (mrg._internal_state.state.list[i] != mrg_5._internal_state.state.list[i]) {
                    diff = true;
                    break;
                }
            EXPECT_TRUE(diff);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
            EXPECT_DOUBLE_EQ(0.0, mrg_5._internal_state.gauss_next);
        }

        {
            BaseMRG31<5> mrg;
            EXPECT_THROW(mrg.seed(-0.001), FloatValueRange01Exception);
            EXPECT_THROW(mrg.seed(1.0001), FloatValueRange01Exception);
        }


        //-- tests _setstate()
        {
            BaseMRG31<5> mrg;
            mrg._setstate(0xa876'cb13'e2f0'594d);
            const std::uint64_t expected[]{ 0xe7186b7b3854a9bc >> 33, 0x4689d02b25c81d1 >> 33, 0x9daeb55b5a2ef996 >> 33, 0xa28288978dd3cea5 >> 33, 0xa9fa0fe2f8412ebe >> 33 };

            EXPECT_EQ(0, mrg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            BaseMRG31<5> mrg;
            mrg._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
            const std::uint64_t expected[]{ 0xf75f04cbb5a1a1dd >> 33, 0xec779c3693f88501 >> 33, 0xfed9eeb4936de39d >> 33, 0x6f9fb04b092bd30a >> 33, 0x260ffb0260bbbe5f >> 33 };

            EXPECT_EQ(0, mrg._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], mrg._internal_state.state.list[i]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }

    }

}
