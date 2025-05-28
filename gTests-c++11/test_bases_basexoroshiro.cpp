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

#include "baseclasses/basexoroshiro.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseXoroshiro)
    {
        //-- tests empty constructor
        {
            constexpr int N{ 5 };
            BaseXoroshiro<N> xrsr;

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_NE(0, xrsr._internal_state.state.list[0]);
            for (int i = 1; i < N; ++i) {
                EXPECT_NE(0ULL, xrsr._internal_state.state.list[i]);
                EXPECT_NE(xrsr._internal_state.state.list[i - 1], xrsr._internal_state.state.list[i]);
            }
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }


        // notice: all hard coded belowing value have been evaluated with PyRandLib

        //-- tests Valued construtor (seed).
        {
            BaseXoroshiro<5> xrsr(1);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x910a2dec89025cc1, 0xbeeb8da1658eec67, 0xf893a2eefb32555e, 0x71c18690ee42c90b, 0x71bb54d8d101b5b9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(-2);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf3203e9039f4a821, 0xba56949915dcf9e9, 0xd0d5127a96e8d90d, 0x1ef156bb76650c37, 0x7842841591543f1d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(9L);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0xaeaf52febe706064, 0xc02d8a5e87afea62, 0x43ec2be544b589b6, 0xc8e98cd697316060, 0x4336b3782f5887a1 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(-11L);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x6fc5530939fb94c3, 0x96caee613260cfca, 0x46d40b90622a734b, 0x6ecc725d7bedada9, 0x69e6fff0691d876d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(17UL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x808475f02ee37363, 0x6434ff62b4e8edd1, 0x540d6c3702d41b8c, 0x395142ca8efaf003, 0x46b1664f61a205e };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x48bbc5b84275f3ca, 0xe2fbc345a799b5aa, 0x86ce19a135fba0de, 0x637c87187035ea06, 0x2a03b9aff2bfd421 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0xeede014d9a5a6108, 0xa6eb6466bac9f251, 0x4246cbb1a64bf70c, 0xaf6aa8f43ebb8659, 0xe1b0fb2c7e764cdb };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            BaseXoroshiro<5> xrsr(0.357);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x5fee464f36fc42c3, 0x954faf5a9ad49cf8, 0xa985465a4a5fc644, 0x77714db9e870d702, 0xa3aac457d81d552c };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }

        EXPECT_THROW(BaseXoroshiro<5>(-0.357), FloatValueRange01Exception);
        EXPECT_THROW(BaseXoroshiro<5>(8.87e+18), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        {
            BaseXoroshiro<5>::state_type st_5;
            st_5.seed(133ULL);
            st_5.index = 3;
            BaseXoroshiro<5> xrsr_5(st_5);

            EXPECT_EQ(st_5.index, xrsr_5._internal_state.state.index);
            EXPECT_EQ(st_5.list, xrsr_5._internal_state.state.list);
            EXPECT_FALSE(xrsr_5._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr_5._internal_state.gauss_next);
        }


        //-- tests copy constructor
        {
            BaseXoroshiro<5> xrsr_5(129);
            BaseXoroshiro<5> xrsr(xrsr_5);

            EXPECT_EQ(xrsr_5._internal_state.state.index, xrsr._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(xrsr_5._internal_state.state.list[i], xrsr._internal_state.state.list[i]);
            EXPECT_EQ(xrsr_5._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_5._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            BaseXoroshiro<5> xrsr_5(129), mrg_tmp(129);
            BaseXoroshiro<5> xrsr(std::move(mrg_tmp));

            EXPECT_EQ(xrsr_5._internal_state.state.index, xrsr._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(xrsr_5._internal_state.state.list[i], xrsr._internal_state.state.list[i]);
            EXPECT_EQ(xrsr_5._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_5._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            BaseXoroshiro<5> xrsr_5(129);
            BaseXoroshiro<5> xrsr;

            xrsr = xrsr_5;

            EXPECT_EQ(xrsr_5._internal_state.state.index, xrsr._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(xrsr_5._internal_state.state.list[i], xrsr._internal_state.state.list[i]);
            EXPECT_EQ(xrsr_5._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_5._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move assignment
        {
            BaseXoroshiro<5> xrsr_5(129), mrg_tmp(129);
            BaseXoroshiro<5> xrsr;

            xrsr = std::move(mrg_tmp);

            EXPECT_EQ(xrsr_5._internal_state.state.index, xrsr._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(xrsr_5._internal_state.state.list[i], xrsr._internal_state.state.list[i]);
            EXPECT_EQ(xrsr_5._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_5._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }

        BaseXoroshiro<5> xrsr;

        {
            xrsr.seed(1);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x910a2dec89025cc1, 0xbeeb8da1658eec67, 0xf893a2eefb32555e, 0x71c18690ee42c90b, 0x71bb54d8d101b5b9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(-2);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf3203e9039f4a821, 0xba56949915dcf9e9, 0xd0d5127a96e8d90d, 0x1ef156bb76650c37, 0x7842841591543f1d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(9L);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0xaeaf52febe706064, 0xc02d8a5e87afea62, 0x43ec2be544b589b6, 0xc8e98cd697316060, 0x4336b3782f5887a1 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(-11L);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x6fc5530939fb94c3, 0x96caee613260cfca, 0x46d40b90622a734b, 0x6ecc725d7bedada9, 0x69e6fff0691d876d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(17UL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x808475f02ee37363, 0x6434ff62b4e8edd1, 0x540d6c3702d41b8c, 0x395142ca8efaf003, 0x46b1664f61a205e };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x48bbc5b84275f3ca, 0xe2fbc345a799b5aa, 0x86ce19a135fba0de, 0x637c87187035ea06, 0x2a03b9aff2bfd421 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0xeede014d9a5a6108, 0xa6eb6466bac9f251, 0x4246cbb1a64bf70c, 0xaf6aa8f43ebb8659, 0xe1b0fb2c7e764cdb };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            xrsr.seed(0.357);
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x5fee464f36fc42c3, 0x954faf5a9ad49cf8, 0xa985465a4a5fc644, 0x77714db9e870d702, 0xa3aac457d81d552c };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }


        //-- tests _setstate()
        {
            xrsr._setstate(0xa876'cb13'e2f0'594d);
            std::uint64_t expected[]{ 0xe7186b7b3854a9bc, 0x4689d02b25c81d1, 0x9daeb55b5a2ef996, 0xa28288978dd3cea5, 0xa9fa0fe2f8412ebe };

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
        }
        {
            xrsr.seed(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            EXPECT_EQ(0, xrsr._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], xrsr._internal_state.state.list[i]);
            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }

    }

}
