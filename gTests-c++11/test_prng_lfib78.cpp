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

#include "lfib78.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsLFib78)
    {
        //-- tests empty constructor
        LFib78 lfib_1;

        EXPECT_EQ(17ULL, lfib_1._internal_state.state.list.size());
        EXPECT_EQ(0, lfib_1._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                lfib_1._internal_state.state.list.cbegin(),
                lfib_1._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(lfib_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")
        
        //-- tests Valued construtor (seed) AND next()
        {
            LFib78 lfib(1);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1658eec67, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x71bb54d8d101b5b9, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x85e7bb0f12278575, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x6775dc7701564f61, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x87b341d690d7a28a, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xa534a6a6b7fd0b63, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x580fd76d4acba81, 0x469ecf77f6668ef1, 0x682f109d6a7ead06, 0x9c8454a893bc1346, 0x16effb7f88fec11c };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x469ecf77f6668ef1, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x16effb7f88fec11c, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x85e7bb0f12278575, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x6775dc7701564f61, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x87b341d690d7a28a, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xa534a6a6b7fd0b63, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(-2);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xba56949915dcf9e9, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x7842841591543f1d, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x1e2b53fb7bd63f05, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x2b724bbbfb591868, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x8457d34b5125f667, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xd3e46307eece8848, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x813f4cc93a728ae7, 0x3eae67e46702f050, 0xdf8461e2dc0444ad, 0x71e08d767b2d3652, 0x4c26e71d8022c765 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x3eae67e46702f050, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x4c26e71d8022c765, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x1e2b53fb7bd63f05, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x2b724bbbfb591868, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x8457d34b5125f667, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xd3e46307eece8848, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(9);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xc02d8a5e87afea62, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x4336b3782f5887a1, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xfbc9d6184de7f13d, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x96f90d64c71a19a0, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x3d8599a83b71b57c, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x90b695a9257c7045, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xab09873e4e47d6c1, 0xfdb32406c3219fde, 0x67de3a67b5ff147, 0xabadde7c33fdd4d9, 0xd3ed492154d4f7e6 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xfdb32406c3219fde, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0xd3ed492154d4f7e6, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xfbc9d6184de7f13d, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x96f90d64c71a19a0, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x3d8599a83b71b57c, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x90b695a9257c7045, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(-11);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x96caee613260cfca, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x69e6fff0691d876d, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xd830cf06dc6b4874, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x17b1379019c20f06, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xe5561582cef81501, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xe3dd00be9840cd9c, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x86a85a515c37a2b4, 0x7c2103e40158e4cb, 0x1e6e49cc887c472b, 0x76891b11cb2637ae, 0x4dc400af015e5509 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x7c2103e40158e4cb, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x4dc400af015e5509, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xd830cf06dc6b4874, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x17b1379019c20f06, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xe5561582cef81501, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xe3dd00be9840cd9c, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(17);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x6434ff62b4e8edd1, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x46b1664f61a205e, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xa74db96e1ce9c735, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x41515d2e8802f2a0, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x826229cb0ea73196, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xfcd07de551231a0f, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xe95449289ec70ce8, 0xe697292dc3901f67, 0x212447e7cc3bb9c1, 0x42da7b4b8e6fe9ed, 0x13b944a473d3a6d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xe697292dc3901f67, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x13b944a473d3a6d, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xa74db96e1ce9c735, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x41515d2e8802f2a0, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x826229cb0ea73196, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xfcd07de551231a0f, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xd573529b34a1d093, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x1404ce914938008, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x8931545f4f9ea651, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xcdb8c9cd9a62da0f, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x97f6c69811cfb13b, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x2ab8c4e395cb5958, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa434bdba328721e4, 0x6d6a1933467181ce, 0x679f428b01be068d, 0x7abfe5d4e9902be1, 0x2bf911ccaa5ed960 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x6d6a1933467181ce, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x2bf911ccaa5ed960, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x8931545f4f9ea651, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xcdb8c9cd9a62da0f, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x97f6c69811cfb13b, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x2ab8c4e395cb5958, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(-8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xe2fbc345a799b5aa, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x2a03b9aff2bfd421, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe6d2502493ff622e, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x4592e2e878ff1b75, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xfbe6cd715ff52a4a, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x61075d5da12791c9, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x2d3a810392119a9, 0xdee290b7078edff4, 0x3f8f2a7848c20206, 0x6232eab237233efa, 0x8b0b170d93e765ea };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xdee290b7078edff4, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x8b0b170d93e765ea, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe6d2502493ff622e, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x4592e2e878ff1b75, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xfbe6cd715ff52a4a, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x61075d5da12791c9, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xa6eb6466bac9f251, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0xe1b0fb2c7e764cdb, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe0c07d9420f2f41e, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xa92d263b8e9fbd45, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xcbe9dce4849cf8e6, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb58daca64a135c56, 0xe02473e79653d56e, 0xb71ccd7a6d0d469c, 0xf9eb52dbd0651bcb, 0xad9ad811031345c1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xe02473e79653d56e, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0xad9ad811031345c1, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe0c07d9420f2f41e, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xa92d263b8e9fbd45, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xcbe9dce4849cf8e6, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(-0.357);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x954faf5a9ad49cf8, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0xa3aac457d81d552c, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe6b536617ee8b60c, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xdf3d30dc1390db9, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xee8fd4bfccca5ee3, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x63be72f7c7521c27, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x70106df293b39627, 0x83df841a679efbdb, 0xc91e42acab88388b, 0x4d8b2fd6229515b2, 0x769374f9f6f7153 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x83df841a679efbdb, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x769374f9f6f7153, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe6b536617ee8b60c, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xdf3d30dc1390db9, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xee8fd4bfccca5ee3, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x63be72f7c7521c27, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(8.87e+18);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xa6eb6466bac9f251, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0xe1b0fb2c7e764cdb, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe0c07d9420f2f41e, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xa92d263b8e9fbd45, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xcbe9dce4849cf8e6, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb58daca64a135c56, 0xe02473e79653d56e, 0xb71ccd7a6d0d469c, 0xf9eb52dbd0651bcb, 0xad9ad811031345c1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xe02473e79653d56e, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0xad9ad811031345c1, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe0c07d9420f2f41e, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0xa92d263b8e9fbd45, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xcbe9dce4849cf8e6, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib78 lfib(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xec779c3693f88501, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x260ffb0260bbbe5f, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xd7c07017388fa2af, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x71da8c61bc0cfda9, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x69f17ee1a874dbdd, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x66fb5ba3ae1546e0, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xbfbc57e9f9791ca, 0x56691b183c6d60de, 0xe063bd54f814d689, 0xba187d9ad5e3bd02, 0x8d0b56a60ed1053f };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x56691b183c6d60de, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x8d0b56a60ed1053f, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xd7c07017388fa2af, lfib._internal_state.state.list[7]);
            EXPECT_EQ(0x71da8c61bc0cfda9, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x69f17ee1a874dbdd, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x66fb5ba3ae1546e0, lfib._internal_state.state.list[16]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }


        //-- tests copy constructor
        {
            LFib78 lfib(lfib_1);

            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move constructor
        LFib78 lfib_0;

        {
            LFib78 lfib_mem(lfib_0);
            LFib78 lfib(std::move(lfib_mem));

            EXPECT_TRUE(lfib_0._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_0._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_0._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            LFib78 lfib;

            lfib = lfib_1;
            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move assignement
        LFib78 lfib;

        {
            LFib78 lfib_mem(lfib_0);
            lfib = std::move(lfib_mem);

            EXPECT_TRUE(lfib_0._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_0._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_0._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests seed()
        lfib.seed();
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                lfib._internal_state.state.list.cbegin(),
                lfib._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);


        //-- tests seed(value)
        lfib.seed(-1);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xe99ff867dbf682c9, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0xb4a0472e578069ae, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0x405da438a39e8064, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x3b234961e71cf15, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0xdd90e10f6f7c1c8a, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x6887829e84a5e267, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(1);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1658eec67, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x71bb54d8d101b5b9, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0x85e7bb0f12278575, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x6775dc7701564f61, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x87b341d690d7a28a, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0xa534a6a6b7fd0b63, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-2);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xba56949915dcf9e9, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x7842841591543f1d, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0x1e2b53fb7bd63f05, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x2b724bbbfb591868, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x8457d34b5125f667, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0xd3e46307eece8848, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(9L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xc02d8a5e87afea62, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x4336b3782f5887a1, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xfbc9d6184de7f13d, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x96f90d64c71a19a0, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x3d8599a83b71b57c, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x90b695a9257c7045, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-11L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x96caee613260cfca, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x69e6fff0691d876d, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xd830cf06dc6b4874, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x17b1379019c20f06, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0xe5561582cef81501, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0xe3dd00be9840cd9c, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(17UL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x6434ff62b4e8edd1, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x46b1664f61a205e, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xa74db96e1ce9c735, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x41515d2e8802f2a0, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x826229cb0ea73196, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0xfcd07de551231a0f, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xd573529b34a1d093, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x1404ce914938008, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0x8931545f4f9ea651, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0xcdb8c9cd9a62da0f, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x97f6c69811cfb13b, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x2ab8c4e395cb5958, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xe2fbc345a799b5aa, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x2a03b9aff2bfd421, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xe6d2502493ff622e, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x4592e2e878ff1b75, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0xfbe6cd715ff52a4a, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x61075d5da12791c9, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xa6eb6466bac9f251, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0xe1b0fb2c7e764cdb, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xe0c07d9420f2f41e, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0xa92d263b8e9fbd45, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0xcbe9dce4849cf8e6, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-0.357);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x954faf5a9ad49cf8, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0xa3aac457d81d552c, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xe6b536617ee8b60c, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0xdf3d30dc1390db9, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0xee8fd4bfccca5ee3, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x63be72f7c7521c27, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(8.87e+18);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xa6eb6466bac9f251, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0xe1b0fb2c7e764cdb, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xe0c07d9420f2f41e, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0xa92d263b8e9fbd45, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0xcbe9dce4849cf8e6, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xec779c3693f88501, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0x260ffb0260bbbe5f, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xd7c07017388fa2af, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x71da8c61bc0cfda9, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0x69f17ee1a874dbdd, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x66fb5ba3ae1546e0, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);


        //-- tests _setstate(seed_)
        lfib._setstate(-1LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xe99ff867dbf682c9, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0xb4a0472e578069ae, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0x405da438a39e8064, lfib._internal_state.state.list[7]);
        EXPECT_EQ(0x3b234961e71cf15, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0xdd90e10f6f7c1c8a, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x6887829e84a5e267, lfib._internal_state.state.list[16]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        lfib.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 100) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)lfib(ENTRIES_COUNT)]++;
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
