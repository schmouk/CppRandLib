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
            BaseLFib64< 5, 2> lfib_5_2(-1LL);
            std::uint64_t state[]{
                0xe4d9'7177'1b65'2c20, 0xe99f'f867'dbf6'82c9, 0x382f'f84c'b272'81e9,
                0x6d1d'b36c'cba9'82d2, 0xb4a0'472e'5780'69ae
            };
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(state[i], lfib_5_2._internal_state.state.list[i]);

        }
        {
            BaseLFib64< 5, 2> lfib_5_2(0.567);
            std::uint64_t state[]{
                0x52a6'7c61'd001'8a64, 0xb4c1'873c'ac52'b799, 0x3474'6662'937d'0bdf,
                0x7b9a'8e87'b032'3f99, 0x4975'3abf'fb1a'c848
            };
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(state[i], lfib_5_2._internal_state.state.list[i]);

        }
        {
            BaseLFib64< 5, 2> lfib_5_2(0xfedc'ba98'0123'4567ULL);
            std::uint64_t state[]{
                0xc2824'378f'ddaf'44f, 0x592a'1bf0'aec8'f77e, 0x3801'7b95'2339'85d7,
                0x168b'7a29'4242'63a9, 0x9f55'af71'a8a4'dbe
            };
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(state[i], lfib_5_2._internal_state.state.list[i]);

        }
        {
            BaseLFib64< 5, 2> lfib_5_2(131L);
            std::uint64_t state[]{
                0x8e48'a85c'3260'd9d0, 0xe9eb'8d3f'012c'c6c4, 0xa1cc'9ccd'c36b'ceca,
                0x768d'85f9'0bfc'75ec, 0x62b4'5dc8'9086'f26c
            };
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(state[i], lfib_5_2._internal_state.state.list[i]);

        }


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
        BaseLFib64< 5, 2> lfib_5_2;
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
            lfib_5_2.seed(-0.987);

            std::uint64_t expected[5]{
                0x943b187a0bd8a2b1, 0x408b140678c02785, 0x50a07e0f464ee700,
                0xcc646d0c4da77303, 0x694f7527a44c6c96
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(8.87e+18);

            std::uint64_t expected[5]{
                0xeede014d9a5a6108, 0xa6eb6466bac9f251, 0x4246cbb1a64bf70c,
                0xaf6aa8f43ebb8659, 0xe1b0fb2c7e764cdb
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }
        {
            lfib_5_2.seed(-8.87e+18);

            std::uint64_t expected[5]{
                0xeede014d9a5a6108, 0xa6eb6466bac9f251, 0x4246cbb1a64bf70c,
                0xaf6aa8f43ebb8659, 0xe1b0fb2c7e764cdb
            };

            EXPECT_FALSE(lfib_5_2._internal_state.gauss_valid);
            EXPECT_EQ(0, lfib_5_2._internal_state.state.index);
            for (int i = 0; i < 5; ++i)
                EXPECT_EQ(expected[i], lfib_5_2._internal_state.state.list[i]);
        }


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
        // Notice: already tested via seed() tests

    }

}
