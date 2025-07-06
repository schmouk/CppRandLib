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

#include "utils/splitmix.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_utils
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteUtils, TestsUtilsSplitmix)
    {
        // checks correctness of utils::SplitMix64
        {
            utils::SplitMix64 splitmix_64;

            std::uint64_t val_prec{ splitmix_64() };
            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val{ splitmix_64() };
                EXPECT_NE(val_prec, val);
                val_prec = val;
            }
        }

        // Notice:  SplitMix implementation is done on a 64-bits  integer
        // internal state. Should we get 'random' values on less bits, it 
        // may  happen that two successive values will be the same on the 
        // checked bits.  This is to occur with a bigger probability when 
        // returned bits count is smaller,  even if the probability of it 
        // to happen remains very low. So, we don't check in the belowing
        // tests the difference of two successive values.

        // checks correctness of utils::SplitMix63
        {
            utils::SplitMix63 splitmix_63;

            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val{ splitmix_63() };
                EXPECT_LE(val, 0x7fff'ffff'ffff'ffffull);
            }
        }

        // checks correctness of utils::SplitMix32
        {
            utils::SplitMix32 splitmix_32;

            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val{ splitmix_32() };
                EXPECT_LE(val, 0xffff'ffffull);
            }
        }

        // checks correctness of utils::SplmitMix31
        {
            utils::SplitMix31 splitmix_31;

            for (int i = 0; i < 1'000'000; ++i) {
                std::uint64_t val = splitmix_31();
                EXPECT_LE(val, 0x7fff'ffffull);
            }
        }

        // notice: all belowing hard coded values have been evaluated with PyRandLib

        // tests SplitMix64(int seed) and operator()
        {
            utils::SplitMix64 s64(1);
            std::uint64_t expected[]{ 0x910a2dec89025cc1, 0xbeeb8da1658eec67, 0xf893a2eefb32555e, 0x71c18690ee42c90b, 0x71bb54d8d101b5b9 };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(-1);
            std::uint64_t expected[]{ 0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9, 0x6d1db36ccba982d2, 0xb4a0472e578069ae };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(1L);
            std::uint64_t expected[]{ 0x910a2dec89025cc1, 0xbeeb8da1658eec67, 0xf893a2eefb32555e, 0x71c18690ee42c90b, 0x71bb54d8d101b5b9 };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(-1L);
            std::uint64_t expected[]{ 0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9, 0x6d1db36ccba982d2, 0xb4a0472e578069ae };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(9UL);
            std::uint64_t expected[]{ 0xaeaf52febe706064, 0xc02d8a5e87afea62, 0x43ec2be544b589b6, 0xc8e98cd697316060, 0x4336b3782f5887a1 };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(-8'870'000'000'000'000'000LL);
            std::uint64_t expected[]{ 0x48bbc5b84275f3ca, 0xe2fbc345a799b5aa, 0x86ce19a135fba0de, 0x637c87187035ea06, 0x2a03b9aff2bfd421 };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(0x0123'4567'89ab'cdefLL);
            std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(8'870'000'000'000'000'000ULL);
            std::uint64_t expected[]{ 0xeede014d9a5a6108, 0xa6eb6466bac9f251, 0x4246cbb1a64bf70c, 0xaf6aa8f43ebb8659, 0xe1b0fb2c7e764cdb };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }
        {
            utils::SplitMix64 s64(0.357);
            std::uint64_t expected[]{ 0x5fee464f36fc42c3, 0x954faf5a9ad49cf8, 0xa985465a4a5fc644, 0x77714db9e870d702, 0xa3aac457d81d552c };
            for (auto e : expected)
                EXPECT_EQ(e, s64());
        }

        EXPECT_THROW(utils::SplitMix64(1.001), FloatValueRange01Exception);
        EXPECT_THROW(utils::SplitMix64(-0.001), FloatValueRange01Exception);


        // tests SplitMix63(int seed) and operator()
        {
            utils::SplitMix63 s63(1);
            std::uint64_t expected[]{ 0x910a2dec89025cc1 >> 1, 0xbeeb8da1658eec67 >> 1, 0xf893a2eefb32555e >> 1, 0x71c18690ee42c90b >> 1, 0x71bb54d8d101b5b9 >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(-1);
            std::uint64_t expected[]{ 0xe4d971771b652c20 >> 1, 0xe99ff867dbf682c9 >> 1, 0x382ff84cb27281e9 >> 1, 0x6d1db36ccba982d2 >> 1, 0xb4a0472e578069ae >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(1L);
            std::uint64_t expected[]{ 0x910a2dec89025cc1 >> 1, 0xbeeb8da1658eec67 >> 1, 0xf893a2eefb32555e >> 1, 0x71c18690ee42c90b >> 1, 0x71bb54d8d101b5b9 >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(-1L);
            std::uint64_t expected[]{ 0xe4d971771b652c20 >> 1, 0xe99ff867dbf682c9 >> 1, 0x382ff84cb27281e9 >> 1, 0x6d1db36ccba982d2 >> 1, 0xb4a0472e578069ae >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(9UL);
            std::uint64_t expected[]{ 0xaeaf52febe706064 >> 1, 0xc02d8a5e87afea62 >> 1, 0x43ec2be544b589b6 >> 1, 0xc8e98cd697316060 >> 1, 0x4336b3782f5887a1 >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(-8'870'000'000'000'000'000LL);
            std::uint64_t expected[]{ 0x48bbc5b84275f3ca >> 1, 0xe2fbc345a799b5aa >> 1, 0x86ce19a135fba0de >> 1, 0x637c87187035ea06 >> 1, 0x2a03b9aff2bfd421 >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(0x0123'4567'89ab'cdefLL);
            std::uint64_t expected[]{ 0x157a3807a48faa9d >> 1, 0xd573529b34a1d093 >> 1, 0x2f90b72e996dccbe >> 1, 0xa2d419334c4667ec >> 1, 0x1404ce914938008 >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(8'870'000'000'000'000'000ULL);
            std::uint64_t expected[]{ 0xeede014d9a5a6108 >> 1, 0xa6eb6466bac9f251 >> 1, 0x4246cbb1a64bf70c >> 1, 0xaf6aa8f43ebb8659 >> 1, 0xe1b0fb2c7e764cdb >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            std::uint64_t expected[]{ 0x157a3807a48faa9d >> 1, 0xd573529b34a1d093 >> 1, 0x2f90b72e996dccbe >> 1, 0xa2d419334c4667ec >> 1, 0x1404ce914938008 >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }
        {
            utils::SplitMix63 s63(0.357);
            std::uint64_t expected[]{ 0x5fee464f36fc42c3 >> 1, 0x954faf5a9ad49cf8 >> 1, 0xa985465a4a5fc644 >> 1, 0x77714db9e870d702 >> 1, 0xa3aac457d81d552c >> 1 };
            for (auto e : expected)
                EXPECT_EQ(e, s63());
        }

        EXPECT_THROW(utils::SplitMix64(1.001), FloatValueRange01Exception);
        EXPECT_THROW(utils::SplitMix63(-0.001), FloatValueRange01Exception);


        // tests SplitMix32(int seed) and operator()
        {
            utils::SplitMix32 s32(1);
            std::uint64_t expected[]{ 0x910a2dec89025cc1 >> 32, 0xbeeb8da1658eec67 >> 32, 0xf893a2eefb32555e >> 32, 0x71c18690ee42c90b >> 32, 0x71bb54d8d101b5b9 >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(-1);
            std::uint64_t expected[]{ 0xe4d971771b652c20 >> 32, 0xe99ff867dbf682c9 >> 32, 0x382ff84cb27281e9 >> 32, 0x6d1db36ccba982d2 >> 32, 0xb4a0472e578069ae >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(1L);
            std::uint64_t expected[]{ 0x910a2dec89025cc1 >> 32, 0xbeeb8da1658eec67 >> 32, 0xf893a2eefb32555e >> 32, 0x71c18690ee42c90b >> 32, 0x71bb54d8d101b5b9 >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(-1L);
            std::uint64_t expected[]{ 0xe4d971771b652c20 >> 32, 0xe99ff867dbf682c9 >> 32, 0x382ff84cb27281e9 >> 32, 0x6d1db36ccba982d2 >> 32, 0xb4a0472e578069ae >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(9UL);
            std::uint64_t expected[]{ 0xaeaf52febe706064 >> 32, 0xc02d8a5e87afea62 >> 32, 0x43ec2be544b589b6 >> 32, 0xc8e98cd697316060 >> 32, 0x4336b3782f5887a1 >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(-8'870'000'000'000'000'000LL);
            std::uint64_t expected[]{ 0x48bbc5b84275f3ca >> 32, 0xe2fbc345a799b5aa >> 32, 0x86ce19a135fba0de >> 32, 0x637c87187035ea06 >> 32, 0x2a03b9aff2bfd421 >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(0x0123'4567'89ab'cdefLL);
            std::uint64_t expected[]{ 0x157a3807a48faa9d >> 32, 0xd573529b34a1d093 >> 32, 0x2f90b72e996dccbe >> 32, 0xa2d419334c4667ec >> 32, 0x1404ce914938008 >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(8'870'000'000'000'000'000ULL);
            std::uint64_t expected[]{ 0xeede014d9a5a6108 >> 32, 0xa6eb6466bac9f251 >> 32, 0x4246cbb1a64bf70c >> 32, 0xaf6aa8f43ebb8659 >> 32, 0xe1b0fb2c7e764cdb >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            std::uint64_t expected[]{ 0x157a3807a48faa9d >> 32, 0xd573529b34a1d093 >> 32, 0x2f90b72e996dccbe >> 32, 0xa2d419334c4667ec >> 32, 0x1404ce914938008 >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }
        {
            utils::SplitMix32 s32(0.357);
            std::uint64_t expected[]{ 0x5fee464f36fc42c3 >> 32, 0x954faf5a9ad49cf8 >> 32, 0xa985465a4a5fc644 >> 32, 0x77714db9e870d702 >> 32, 0xa3aac457d81d552c >> 32 };
            for (auto e : expected)
                EXPECT_EQ(e, s32());
        }

        EXPECT_THROW(utils::SplitMix64(1.001), FloatValueRange01Exception);
        EXPECT_THROW(utils::SplitMix32(-0.001), FloatValueRange01Exception);


        // tests SplitMix31(int seed) and operator()
        {
            utils::SplitMix31 s31(1);
            std::uint64_t expected[]{ 0x910a2dec89025cc1 >> 33, 0xbeeb8da1658eec67 >> 33, 0xf893a2eefb32555e >> 33, 0x71c18690ee42c90b >> 33, 0x71bb54d8d101b5b9 >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(-1);
            std::uint64_t expected[]{ 0xe4d971771b652c20 >> 33, 0xe99ff867dbf682c9 >> 33, 0x382ff84cb27281e9 >> 33, 0x6d1db36ccba982d2 >> 33, 0xb4a0472e578069ae >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(1L);
            std::uint64_t expected[]{ 0x910a2dec89025cc1 >> 33, 0xbeeb8da1658eec67 >> 33, 0xf893a2eefb32555e >> 33, 0x71c18690ee42c90b >> 33, 0x71bb54d8d101b5b9 >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(-1L);
            std::uint64_t expected[]{ 0xe4d971771b652c20 >> 33, 0xe99ff867dbf682c9 >> 33, 0x382ff84cb27281e9 >> 33, 0x6d1db36ccba982d2 >> 33, 0xb4a0472e578069ae >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(9UL);
            std::uint64_t expected[]{ 0xaeaf52febe706064 >> 33, 0xc02d8a5e87afea62 >> 33, 0x43ec2be544b589b6 >> 33, 0xc8e98cd697316060 >> 33, 0x4336b3782f5887a1 >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(-8'870'000'000'000'000'000LL);
            std::uint64_t expected[]{ 0x48bbc5b84275f3ca >> 33, 0xe2fbc345a799b5aa >> 33, 0x86ce19a135fba0de >> 33, 0x637c87187035ea06 >> 33, 0x2a03b9aff2bfd421 >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(0x0123'4567'89ab'cdefLL);
            std::uint64_t expected[]{ 0x157a3807a48faa9d >> 33, 0xd573529b34a1d093 >> 33, 0x2f90b72e996dccbe >> 33, 0xa2d419334c4667ec >> 33, 0x1404ce914938008 >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(8'870'000'000'000'000'000ULL);
            std::uint64_t expected[]{ 0xeede014d9a5a6108 >> 33, 0xa6eb6466bac9f251 >> 33, 0x4246cbb1a64bf70c >> 33, 0xaf6aa8f43ebb8659 >> 33, 0xe1b0fb2c7e764cdb >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            std::uint64_t expected[]{ 0x157a3807a48faa9d >> 33, 0xd573529b34a1d093 >> 33, 0x2f90b72e996dccbe >> 33, 0xa2d419334c4667ec >> 33, 0x1404ce914938008 >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }
        {
            utils::SplitMix31 s31(0.357);
            std::uint64_t expected[]{ 0x5fee464f36fc42c3 >> 33, 0x954faf5a9ad49cf8 >> 33, 0xa985465a4a5fc644 >> 33, 0x77714db9e870d702 >> 33, 0xa3aac457d81d552c >> 33 };
            for (auto e : expected)
                EXPECT_EQ(e, s31());
        }

        EXPECT_THROW(utils::SplitMix64(1.001), FloatValueRange01Exception);
        EXPECT_THROW(utils::SplitMix31(-0.001), FloatValueRange01Exception);


    }
}
