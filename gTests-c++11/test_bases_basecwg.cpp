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
#include "gtest/gtest.h"

#include "baseclasses/basecwg.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseCwg)
    {
        //-- tests empty constructor
        BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_1;
        BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_1;
        BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_1;

        EXPECT_EQ(0ULL, cwg64_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg64_1._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg64_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_EQ(0ULL, cwg64_1._internal_state.state.weyl);
        EXPECT_FALSE(cwg64_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64_1._internal_state.gauss_next);

        EXPECT_EQ(0ULL, cwg128_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_1._internal_state.state.s.lo & 1ULL);
        EXPECT_NE(0ULL, cwg128_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_EQ(0ULL, cwg128_1._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_1._internal_state.gauss_next);

        EXPECT_EQ(0ULL, cwg128_64_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_64_1._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg128_64_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_EQ(0ULL, cwg128_64_1._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64_1._internal_state.gauss_next);


        //-- tests Valued constructor (seed). */
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(1);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x910a2dec89025cc1ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xbeeb8da1658eec67ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(-2);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xf3203e9039f4a821ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xba56949915dcf9e9ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(9);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xaeaf52febe706065ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xc02d8a5e87afea62ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(-11);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x6fc5530939fb94c3ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x96caee613260cfcaULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(17);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x808475f02ee37363ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x6434ff62b4e8edd1ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x157a3807a48faa9dULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xd573529b34a1d093ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(-8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x48bbc5b84275f3cbULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xe2fbc345a799b5aaULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
  }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0xa6eb6466bac9f251ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(0.357);

            EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
            EXPECT_EQ(0x5fee464f36fc42c3ULL, cwg64._internal_state.state.s);
            EXPECT_EQ(0x954faf5a9ad49cf8ULL, cwg64._internal_state.state.state);
            EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64> cwg64(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));

            EXPECT_EQ(0x0, cwg64._internal_state.state.a);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg64._internal_state.state.s);
            EXPECT_EQ(0xec779c3693f88501, cwg64._internal_state.state.state);
            EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
            EXPECT_FALSE(cwg64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);
        }

        EXPECT_THROW((BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>(-8.87e+18)), FloatValueRange01Exception);
        EXPECT_THROW((BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>(1.0001)), FloatValueRange01Exception);

        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(1);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x910a2dec89025cc1, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xbeeb8da1658eec67, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xf893a2eefb32555e, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x71c18690ee42c90b, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(-2);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xd0d5127a96e8d90d, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x1ef156bb76650c37, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(9);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xaeaf52febe706064, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xc02d8a5e87afea63, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x43ec2be544b589b6, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xc8e98cd697316060, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(-11);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x6fc5530939fb94c3, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x96caee613260cfcb, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x46d40b90622a734b, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x6ecc725d7bedada9, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(17);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x808475f02ee37363, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x6434ff62b4e8edd1, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x540d6c3702d41b8c, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x395142ca8efaf003, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x157a3807a48faa9d, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xd573529b34a1d093, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x2f90b72e996dccbe, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xa2d419334c4667ec, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(-8870000000000000000);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x48bbc5b84275f3ca, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xe2fbc345a799b5ab, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x86ce19a135fba0de, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x637c87187035ea06, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(8870000000000000000);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xeede014d9a5a6108, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xa6eb6466bac9f251, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x4246cbb1a64bf70c, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xaf6aa8f43ebb8659, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(0.357);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x5fee464f36fc42c3, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x954faf5a9ad49cf9, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xa985465a4a5fc644, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x77714db9e870d702, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xec779c3693f88501, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }

        EXPECT_THROW((BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128>(-8.87e+18)), FloatValueRange01Exception);
        EXPECT_THROW((BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128>(1.0001)), FloatValueRange01Exception);

        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(1);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x910a2dec89025cc1, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xbeeb8da1658eec67, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xf893a2eefb32555e, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(-2);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xba56949915dcf9e9, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xd0d5127a96e8d90d, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(9);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xaeaf52febe706065, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xc02d8a5e87afea62, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x43ec2be544b589b6, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(-11);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x6fc5530939fb94c3, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x96caee613260cfca, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x46d40b90622a734b, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(17);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x808475f02ee37363, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x6434ff62b4e8edd1, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x540d6c3702d41b8c, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x157a3807a48faa9d, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xd573529b34a1d093, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x2f90b72e996dccbe, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(-8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x48bbc5b84275f3cb, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xe2fbc345a799b5aa, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x86ce19a135fba0de, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xa6eb6466bac9f251, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x4246cbb1a64bf70c, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(0.357);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x5fee464f36fc42c3, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x954faf5a9ad49cf8, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xa985465a4a5fc644, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64> cwg128_64(utils::UInt128(0xffff'ffff'ffff'fffeULL, 0xffff'ffff'ffff'fffdULL));

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xec779c3693f88501, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }

        EXPECT_THROW((BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>(-8.87e+18)), FloatValueRange01Exception);
        EXPECT_THROW((BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>(1.0001)), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        CollatzWeylState<std::uint64_t, std::uint64_t>   internal_state_64_0;
        CollatzWeylState<std::uint64_t, utils::UInt128>  internal_state_128_64_0;
        CollatzWeylState<utils::UInt128, utils::UInt128> internal_state_128_0;

        BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_0(internal_state_64_0);
        BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_0(internal_state_128_64_0);
        BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_0(internal_state_128_0);

        EXPECT_EQ(internal_state_64_0, cwg64_0._internal_state.state);
        EXPECT_EQ(internal_state_128_64_0, cwg128_64_0._internal_state.state);
        EXPECT_EQ(internal_state_128_0, cwg128_0._internal_state.state);


        //-- tests copy constructor
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64(cwg64_1);
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(cwg128_1);
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64(cwg128_64_1);

            EXPECT_EQ(cwg64_1._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_1._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_1._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_1._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_1._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_1._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_64_1._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_mem(cwg64_0);
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_mem(cwg128_0);
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_mem(cwg128_64_0);

            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64(std::move(cwg64_mem));
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128(std::move(cwg128_mem));
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64(std::move(cwg128_64_mem));

            EXPECT_EQ(cwg64_0._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_0._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_0._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_0._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_0._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_0._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            EXPECT_EQ(cwg128_64_0._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64;
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128;
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64;

            cwg64 = cwg64_1;
            EXPECT_EQ(cwg64_1._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_1._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_1._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            cwg128 = cwg128_1;
            EXPECT_EQ(cwg128_1._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_1._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_1._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            cwg128_64 = cwg128_64_1;
            EXPECT_EQ(cwg128_64_1._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests move assignement
        BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64;
        BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128;
        BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64;

        {
            BaseCWG<std::uint64_t, std::uint64_t, std::uint64_t, 64>     cwg64_mem(cwg64_0);
            BaseCWG<utils::UInt128, utils::UInt128, utils::UInt128, 128> cwg128_mem(cwg128_0);
            BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>    cwg128_64_mem(cwg128_64_0);

            cwg64 = std::move(cwg64_mem);
            EXPECT_EQ(cwg64_0._internal_state.state, cwg64._internal_state.state);
            EXPECT_EQ(cwg64_0._internal_state.gauss_next, cwg64._internal_state.gauss_next);
            EXPECT_EQ(cwg64_0._internal_state.gauss_valid, cwg64._internal_state.gauss_valid);

            cwg128 = std::move(cwg128_mem);
            EXPECT_EQ(cwg128_0._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_0._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_0._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);

            cwg128_64 = std::move(cwg128_64_mem);
            EXPECT_EQ(cwg128_64_0._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests seed()
        cwg64.seed();
        EXPECT_EQ(0ULL, cwg64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(cwg64_1._internal_state.state.s, cwg64._internal_state.state.s);  // (1 over 2^64 risk)
        EXPECT_NE(cwg64_1._internal_state.state.state, cwg64._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg128.seed();
        EXPECT_EQ(0ULL, cwg128._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128._internal_state.state.s.lo & 1ULL);
        EXPECT_NE(0ULL, cwg128._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_NE(cwg128_1._internal_state.state.s, cwg128._internal_state.state.s);  // (1 over 2^128 risk)
        EXPECT_NE(cwg128_1._internal_state.state.state, cwg128._internal_state.state.state);  // (1 over 2^128 risk)
        EXPECT_EQ(0ULL, cwg128._internal_state.state.weyl);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128_64.seed();
        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg128_64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^64)
        EXPECT_NE(cwg128_64_1._internal_state.state.s, cwg128_64._internal_state.state.s);  // (1 over 2^128 risk)
        EXPECT_NE(cwg128_64_1._internal_state.state.state, cwg128_64._internal_state.state.state);  // (1 over 2^64 risk)
        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);


        //-- tests seed(value)
        cwg64.seed(-1);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c21, cwg64._internal_state.state.s);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(1);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x910a2dec89025cc1, cwg64._internal_state.state.s);
        EXPECT_EQ(0xbeeb8da1658eec67, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(-2);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xf3203e9039f4a821, cwg64._internal_state.state.s);
        EXPECT_EQ(0xba56949915dcf9e9, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(9L);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xaeaf52febe706065, cwg64._internal_state.state.s);
        EXPECT_EQ(0xc02d8a5e87afea62, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(-11L);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x6fc5530939fb94c3, cwg64._internal_state.state.s);
        EXPECT_EQ(0x96caee613260cfca, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(17UL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x808475f02ee37363, cwg64._internal_state.state.s);
        EXPECT_EQ(0x6434ff62b4e8edd1, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x157a3807a48faa9d, cwg64._internal_state.state.s);
        EXPECT_EQ(0xd573529b34a1d093, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x48bbc5b84275f3cb, cwg64._internal_state.state.s);
        EXPECT_EQ(0xe2fbc345a799b5aa, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xeede014d9a5a6109, cwg64._internal_state.state.s);
        EXPECT_EQ(0xa6eb6466bac9f251, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(0.357);
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x5fee464f36fc42c3, cwg64._internal_state.state.s);
        EXPECT_EQ(0x954faf5a9ad49cf8, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        cwg64.seed(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));
        EXPECT_EQ(0x0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg64._internal_state.state.s);
        EXPECT_EQ(0xec779c3693f88501, cwg64._internal_state.state.state);
        EXPECT_EQ(0x0, cwg64._internal_state.state.weyl);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg64._internal_state.gauss_next);

        EXPECT_THROW(cwg64.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(cwg64.seed(-0.001), FloatValueRange01Exception);

        cwg128.seed(-1);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xe4d971771b652c20, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x6d1db36ccba982d2, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(1);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x910a2dec89025cc1, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xbeeb8da1658eec67, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xf893a2eefb32555e, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x71c18690ee42c90b, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(-2);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xd0d5127a96e8d90d, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x1ef156bb76650c37, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(9L);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xaeaf52febe706064, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xc02d8a5e87afea63, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x43ec2be544b589b6, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xc8e98cd697316060, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(-11L);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x6fc5530939fb94c3, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0x96caee613260cfcb, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x46d40b90622a734b, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x6ecc725d7bedada9, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(17UL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x808475f02ee37363, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0x6434ff62b4e8edd1, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x540d6c3702d41b8c, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x395142ca8efaf003, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x157a3807a48faa9d, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xd573529b34a1d093, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x2f90b72e996dccbe, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xa2d419334c4667ec, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x48bbc5b84275f3ca, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xe2fbc345a799b5ab, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x86ce19a135fba0de, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x637c87187035ea06, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xeede014d9a5a6108, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xa6eb6466bac9f251, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x4246cbb1a64bf70c, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xaf6aa8f43ebb8659, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(0.357);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x5fee464f36fc42c3, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0x954faf5a9ad49cf9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xa985465a4a5fc644, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x77714db9e870d702, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xec779c3693f88501, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        EXPECT_THROW(cwg128.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(cwg128.seed(-0.001), FloatValueRange01Exception);

        cwg128_64.seed(-1);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c21, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(1);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x910a2dec89025cc1, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xbeeb8da1658eec67, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0xf893a2eefb32555e, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(-2);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xba56949915dcf9e9, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0xd0d5127a96e8d90d, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(9L);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xaeaf52febe706065, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xc02d8a5e87afea62, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x43ec2be544b589b6, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(-11L);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x6fc5530939fb94c3, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0x96caee613260cfca, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x46d40b90622a734b, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(17UL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x808475f02ee37363, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0x6434ff62b4e8edd1, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x540d6c3702d41b8c, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x157a3807a48faa9d, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xd573529b34a1d093, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x2f90b72e996dccbe, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x48bbc5b84275f3cb, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xe2fbc345a799b5aa, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x86ce19a135fba0de, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xa6eb6466bac9f251, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x4246cbb1a64bf70c, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(0.357);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x5fee464f36fc42c3, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0x954faf5a9ad49cf8, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0xa985465a4a5fc644, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(utils::UInt128(0xffff'ffff'ffff'fffeULL, 0xffff'ffff'ffff'fffdULL));
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0xec779c3693f88501, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        EXPECT_THROW(cwg128_64.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(cwg128_64.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        // Notice: hard coded value below have been evaluated with PyRandLib
        cwg64._setstate(-1);
        EXPECT_EQ(0, cwg64._internal_state.state.a);
        EXPECT_EQ(0xe4d9'7177'1b65'2c20 | 1, cwg64._internal_state.state.s);
        EXPECT_EQ(0xe99f'f867'dbf6'82c9, cwg64._internal_state.state.state);
        EXPECT_EQ(0, cwg64._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg64._internal_state.gauss_next);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);

        cwg64._setstate(utils::UInt128(1, 2));
        EXPECT_EQ(0, cwg64._internal_state.state.a);
        EXPECT_EQ(0x9758'35de'1c97'56ce | 1, cwg64._internal_state.state.s);
        EXPECT_EQ(0xbfc8'4610'0bfc'1e42, cwg64._internal_state.state.state);
        EXPECT_EQ(0, cwg64._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg64._internal_state.gauss_next);
        EXPECT_FALSE(cwg64._internal_state.gauss_valid);

        cwg128._setstate(-1LL);
        EXPECT_EQ(0, cwg128._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c20, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x6d1db36ccba982d2, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0, cwg128._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg128._internal_state.gauss_next);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);

        cwg128._setstate(utils::UInt128(1, 2));
        EXPECT_EQ(0, cwg128._internal_state.state.a);
        EXPECT_EQ(utils::UInt128(0x910a2dec89025cc1, 0x975835de1c9756ce | 1), cwg128._internal_state.state.s);
        EXPECT_EQ(utils::UInt128(0xbeeb8da1658eec67, 0xbfc846100bfc1e42), cwg128._internal_state.state.state);
        EXPECT_EQ(0, cwg128._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg128._internal_state.gauss_next);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);

        cwg128_64._setstate(-1LL);
        EXPECT_EQ(0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c21, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0, cwg128_64._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg128_64._internal_state.gauss_next);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);

        cwg128_64._setstate(utils::UInt128(1, 2));
        EXPECT_EQ(0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x975835de1c9756cf, cwg128_64._internal_state.state.s);
        EXPECT_EQ(utils::UInt128(0x910a2dec89025cc1, 0xbfc846100bfc1e42), cwg128_64._internal_state.state.state);
        EXPECT_EQ(0, cwg128_64._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg128_64._internal_state.gauss_next);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);

    }

}
