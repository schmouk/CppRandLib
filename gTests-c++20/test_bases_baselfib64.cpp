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

#include "baseclasses/baselfib64.h"
#include "exceptions.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseLFib64)
    {
        //-- tests empty constructor
        {
            BaseLFib64< 5, 2> lfib_5_2;
            BaseLFib64<55, 24> lfib_55_24;

            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            EXPECT_NE(0ULL, lfib_5_2._internal_state.state.list[0]);
            for (int i = 1; i < 5; ++i) {
                EXPECT_NE(0ULL, lfib_5_2._internal_state.state.list[i]);
                EXPECT_NE(lfib_5_2._internal_state.state.list[i - 1], lfib_5_2._internal_state.state.list[i]);
            }

            EXPECT_EQ(0, lfib_55_24._internal_state.state.index);
            EXPECT_NE(0ULL, lfib_55_24._internal_state.state.list[0]);
            for (int i = 1; i < 55; ++i) {
                EXPECT_NE(0ULL, lfib_55_24._internal_state.state.list[i]);
                EXPECT_NE(lfib_55_24._internal_state.state.list[i - 1], lfib_55_24._internal_state.state.list[i]);
            }
        }


        //-- tests Valued construtor (seed).
        // notice: hard coded values below have been evaluated with PyRandLib.
        {
            BaseLFib64< 5, 2> lfib_5_2(1);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0x910a2dec89025cc1, 0xbeeb8da1658eec67, 0xf893a2eefb32555e, 0x71c18690ee42c90b, 0x71bb54d8d101b5b9 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(-2);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf3203e9039f4a821, 0xba56949915dcf9e9, 0xd0d5127a96e8d90d, 0x1ef156bb76650c37, 0x7842841591543f1d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(9L);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0xaeaf52febe706064, 0xc02d8a5e87afea62, 0x43ec2be544b589b6, 0xc8e98cd697316060, 0x4336b3782f5887a1 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(-11L);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0x6fc5530939fb94c3, 0x96caee613260cfca, 0x46d40b90622a734b, 0x6ecc725d7bedada9, 0x69e6fff0691d876d };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(17UL);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0x808475f02ee37363, 0x6434ff62b4e8edd1, 0x540d6c3702d41b8c, 0x395142ca8efaf003, 0x46b1664f61a205e };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0x157a3807a48faa9d, 0xd573529b34a1d093, 0x2f90b72e996dccbe, 0xa2d419334c4667ec, 0x1404ce914938008 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0x48bbc5b84275f3ca, 0xe2fbc345a799b5aa, 0x86ce19a135fba0de, 0x637c87187035ea06, 0x2a03b9aff2bfd421 };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0xeede014d9a5a6108, 0xa6eb6466bac9f251, 0x4246cbb1a64bf70c, 0xaf6aa8f43ebb8659, 0xe1b0fb2c7e764cdb };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(0.357);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0x5fee464f36fc42c3, 0x954faf5a9ad49cf8, 0xa985465a4a5fc644, 0x77714db9e870d702, 0xa3aac457d81d552c };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            BaseLFib64< 5, 2> lfib_5_2(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            const std::uint64_t expected[]{ 0xf75f04cbb5a1a1dd, 0xec779c3693f88501, 0xfed9eeb4936de39d, 0x6f9fb04b092bd30a, 0x260ffb0260bbbe5f };
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }

        EXPECT_THROW((BaseLFib64<5, 2>(-8.87e+18)), FloatValueRange01Exception);
        EXPECT_THROW((BaseLFib64<55, 24>(1.0001)), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        BaseLFib64<55, 24>::state_type st_55_24;
        st_55_24.seed(131ULL);
        st_55_24.index = 53;
        BaseLFib64<55, 24> lfib_55_24(st_55_24);

        EXPECT_EQ(st_55_24.index, lfib_55_24._internal_state.state.index);
        EXPECT_EQ(st_55_24.list, lfib_55_24._internal_state.state.list);


        //-- tests copy constructor
        BaseLFib64<55, 24> lfib_tmp(lfib_55_24);

        EXPECT_EQ(lfib_55_24.state().index, lfib_tmp.state().index);
        EXPECT_EQ(lfib_55_24.state().list, lfib_tmp.state().list);
        EXPECT_EQ(lfib_55_24._internal_state.gauss_next, lfib_tmp._internal_state.gauss_next);
        EXPECT_EQ(lfib_55_24._internal_state.gauss_valid, lfib_tmp._internal_state.gauss_valid);


        //-- tests move constructor
        BaseLFib64<55, 24> lfib(std::move(lfib_tmp));

        EXPECT_EQ(lfib_tmp.state().index, lfib.state().index);
        EXPECT_EQ(lfib_tmp.state().list, lfib.state().list);
        EXPECT_EQ(lfib_tmp._internal_state.gauss_next, lfib._internal_state.gauss_next);
        EXPECT_EQ(lfib_tmp._internal_state.gauss_valid, lfib._internal_state.gauss_valid);


        //-- tests copy assignment
        lfib_55_24._internal_state.state.index = 1;
        lfib_tmp = lfib_55_24;

        EXPECT_EQ(lfib_55_24.state().index, lfib_tmp.state().index);
        EXPECT_EQ(lfib_55_24.state().list, lfib_tmp.state().list);
        EXPECT_EQ(lfib_55_24._internal_state.gauss_next, lfib_tmp._internal_state.gauss_next);
        EXPECT_EQ(lfib_55_24._internal_state.gauss_valid, lfib_tmp._internal_state.gauss_valid);


        //-- tests move assignement
        lfib_55_24.seed(28031);
        lfib_55_24._internal_state.state.index = 5;
        lfib_tmp = lfib_55_24;

        lfib = std::move(lfib_tmp);
        EXPECT_EQ(lfib_55_24.state().index, lfib.state().index);
        EXPECT_EQ(lfib_55_24.state().list, lfib.state().list);
        EXPECT_EQ(lfib_55_24._internal_state.gauss_next, lfib._internal_state.gauss_next);
        EXPECT_EQ(lfib_55_24._internal_state.gauss_valid, lfib._internal_state.gauss_valid);


        //-- tests next()
        BaseLFib64<5, 2> lfib_5_2;
        {
            // notice: hard coded values below have been evaluated with PyRandLib.
            std::uint64_t expected[19]{
                0xbe5b'd096'649f'ca35, 0x3479'c117'dc8f'bd37, 0x249a'155c'54f0'9330, 0xcbcf'e2e0'f1a2'f0dc,
                0xe703'cd0e'5e15'93e7, 0x8a2b'b377'5642'bb11, 0x1b7d'8e26'3aa5'511e, 0xaec5'c8d3'ab33'4e41,
                0xe74d'7107'2c48'41fa, 0x95c9'95e2'0948'e228, 0x7179'247e'828a'fd0b, 0xb147'2408'43ee'3346,
                0x203e'ed52'2dbe'4b4c, 0x9894'950f'7036'7540, 0xb608'8334'3707'2d74, 0x0a0d'b98d'f2c1'724b,
                0x674f'a73c'7af5'60ba, 0x2a4c'a6e0'207f'bd97, 0xffe4'3c4b'eb2b'd5fa
            };

            lfib_5_2.seed(28031);
            lfib_5_2._internal_state.state.index = 0;

            int i;
            for (i = 0; i < 19; ++i) {
                EXPECT_EQ(i % 5, lfib_5_2.state().index);
                EXPECT_EQ(expected[i], lfib_5_2.next());
            }
            EXPECT_EQ(i % 5, lfib_5_2.state().index);
        }

        //-- tests seed()
        lfib_5_2.seed();
        EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
        EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
        EXPECT_NE(0ULL, lfib_5_2._internal_state.state.list[0]);
        for (int i = 1; i < 5; ++i) {
            EXPECT_NE(0ULL, lfib_5_2._internal_state.state.list[i]);
            EXPECT_NE(lfib_5_2._internal_state.state.list[i - 1], lfib_5_2._internal_state.state.list[i]);
        }

        lfib_55_24.seed();
        EXPECT_FALSE(lfib_55_24._internal_state.gauss_valid);
        EXPECT_EQ(0, lfib_55_24._internal_state.state.index);
        EXPECT_NE(0ULL, lfib_55_24._internal_state.state.list[0]);
        for (int i = 1; i < 55; ++i) {
            EXPECT_NE(0ULL, lfib_55_24._internal_state.state.list[i]);
            EXPECT_NE(lfib_55_24._internal_state.state.list[i - 1], lfib_55_24._internal_state.state.list[i]);
        }


        //-- tests seed(value)
        {
            lfib_5_2.seed(-1);

            std::uint64_t expected[5]{
                0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9,
                0x6d1db36ccba982d2, 0xb4a0472e578069ae
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(28031L);

            std::uint64_t expected[5]{
                0x2705'aecd'4f8c'9690, 0x72100965d36abc80, 0x663e'44c5'f050'c8fb,
                0x9756'21c9'1513'33a5, 0xc269b7b2092500b7
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(28032UL);

            std::uint64_t expected[5]{
                0xbf0a5635a9341d88, 0x9d72bf564a7f9995, 0x61a8c168da5def3a,
                0x1033569f139833aa, 0xa6d7a3f6d50224c0
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(-1LL);

            std::uint64_t expected[5]{
                0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9,
                0x6d1db36ccba982d2, 0xb4a0472e578069ae
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(0xffff'ffff'ffff'ffffULL);

            std::uint64_t expected[5]{
                0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9,
                0x6d1db36ccba982d2, 0xb4a0472e578069ae
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(0.187);

            std::uint64_t expected[5]{
                0x2b18160c0a9f05b4, 0xc8197d13a4d6d45f, 0xaca007e67e920ed1,
                0xf0e779fe3279121f, 0xcd551efd3099f223
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            std::uint64_t expected[5]{
                0xf75f04cbb5a1a1dd, 0xec779c3693f88501, 0xfed9eeb4936de39d,
                0x6f9fb04b092bd30a, 0x260ffb0260bbbe5f
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }

        EXPECT_THROW(lfib_5_2.seed(8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(lfib_5_2.seed(-0.987), FloatValueRange01Exception);


        //-- tests _init_index()
        {
            BaseLFib64< 5, 2> lfib_5_2;
            BaseLFib64<55, 24> lfib_55_24;

            for (int i = 0; i < 2 * 5 + 1; ++i) {
                lfib_5_2._initIndex(i);
                EXPECT_EQ(i % 5, lfib_5_2._internal_state.state.index);
            }

            for (int i = 0; i < 2 * 5 + 1; ++i) {
                lfib_55_24._initIndex(i);
                EXPECT_EQ(i % 55, lfib_55_24._internal_state.state.index);
            }

        }


        //-- tests _setstate(seed_)
        {
            lfib_5_2._setstate(0xffff'ffff'ffff'ffffULL);
            std::uint64_t expected[5]{
                0xe4d971771b652c20, 0xe99ff867dbf682c9, 0x382ff84cb27281e9,
                0x6d1db36ccba982d2, 0xb4a0472e578069ae
            };
            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
            std::uint64_t expected[5]{
                0xf75f04cbb5a1a1dd, 0xec779c3693f88501, 0xfed9eeb4936de39d,
                0x6f9fb04b092bd30a, 0x260ffb0260bbbe5f
            };
            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }

    }

}
