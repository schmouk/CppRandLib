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

#include "mrg287.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsMrg287)
    {
        //-- tests empty constructor
        Mrg287 mrg_1;

        EXPECT_EQ(256ULL, mrg_1._internal_state.state.list.size());
        EXPECT_EQ(0, mrg_1._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                mrg_1._internal_state.state.list.cbegin(),
                mrg_1._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(mrg_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Mrg287 mrg(1);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1, mrg._internal_state.state.list[1]);
            EXPECT_EQ(0xa7ff0d38, mrg._internal_state.state.list[43]);
            EXPECT_EQ(0xf0dad827, mrg._internal_state.state.list[85]);
            EXPECT_EQ(0x6524e51f, mrg._internal_state.state.list[127]);
            EXPECT_EQ(0x100ba66a, mrg._internal_state.state.list[169]);
            EXPECT_EQ(0xb4bdc811, mrg._internal_state.state.list[211]);
            EXPECT_EQ(0x7804cbe7, mrg._internal_state.state.list[253]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xdf8fa498, 0x1056b873, 0x24aadca6, 0xcf2941d0, 0xe213ae1c };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x7ef1fd0e, mrg._internal_state.state.list[22]);
            EXPECT_EQ(0xb86c9a98, mrg._internal_state.state.list[64]);
            EXPECT_EQ(0xa3e9bfbb, mrg._internal_state.state.list[106]);
            EXPECT_EQ(0xd4d2fac5, mrg._internal_state.state.list[148]);
            EXPECT_EQ(0x4e3adbe8, mrg._internal_state.state.list[190]);
            EXPECT_EQ(0xa13e727a, mrg._internal_state.state.list[232]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(-2);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0xf0a98b8d, mrg._internal_state.state.list[40]);
            EXPECT_EQ(0xb2624a7c, mrg._internal_state.state.list[82]);
            EXPECT_EQ(0x62be4a8f, mrg._internal_state.state.list[124]);
            EXPECT_EQ(0xe7fa3f41, mrg._internal_state.state.list[166]);
            EXPECT_EQ(0x9a81c04b, mrg._internal_state.state.list[208]);
            EXPECT_EQ(0x4e0895df, mrg._internal_state.state.list[250]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xe0147fc3, 0xf9cf8af4, 0x3cabdda2, 0xe76c65b3, 0xe1a5a4c5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0xc8450c77, mrg._internal_state.state.list[19]);
            EXPECT_EQ(0x8617bf39, mrg._internal_state.state.list[61]);
            EXPECT_EQ(0xf14ea420, mrg._internal_state.state.list[103]);
            EXPECT_EQ(0x2f197308, mrg._internal_state.state.list[145]);
            EXPECT_EQ(0xdb5adb1f, mrg._internal_state.state.list[187]);
            EXPECT_EQ(0xb020669a, mrg._internal_state.state.list[229]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(9);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0xca067431, mrg._internal_state.state.list[9]);
            EXPECT_EQ(0x6a5307e4, mrg._internal_state.state.list[51]);
            EXPECT_EQ(0xeb76302a, mrg._internal_state.state.list[93]);
            EXPECT_EQ(0xe6c2bbc8, mrg._internal_state.state.list[135]);
            EXPECT_EQ(0x790f4a31, mrg._internal_state.state.list[177]);
            EXPECT_EQ(0xd9aa4356, mrg._internal_state.state.list[219]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5e4419ed, 0x279d78cd, 0xaa4808b8, 0xc4836fdc, 0xe258db8f };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x4eaa1487, mrg._internal_state.state.list[30]);
            EXPECT_EQ(0xe74fbdd8, mrg._internal_state.state.list[72]);
            EXPECT_EQ(0x8c6b308a, mrg._internal_state.state.list[114]);
            EXPECT_EQ(0x7290a0ea, mrg._internal_state.state.list[156]);
            EXPECT_EQ(0xd8966853, mrg._internal_state.state.list[198]);
            EXPECT_EQ(0x17b17b42, mrg._internal_state.state.list[240]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(-11);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0xb029b8b5, mrg._internal_state.state.list[31]);
            EXPECT_EQ(0x13db1fa5, mrg._internal_state.state.list[73]);
            EXPECT_EQ(0x9ed3fd7c, mrg._internal_state.state.list[115]);
            EXPECT_EQ(0xe9c8d99a, mrg._internal_state.state.list[157]);
            EXPECT_EQ(0xf513d73c, mrg._internal_state.state.list[199]);
            EXPECT_EQ(0xe4e896d5, mrg._internal_state.state.list[241]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x7b3d6249, 0x01d43fdb, 0x45163d13, 0x13f29697, 0x1ec1204e };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x17b13790, mrg._internal_state.state.list[10]);
            EXPECT_EQ(0xabda70c1, mrg._internal_state.state.list[52]);
            EXPECT_EQ(0xb85a2e37, mrg._internal_state.state.list[94]);
            EXPECT_EQ(0xd3dd73d4, mrg._internal_state.state.list[136]);
            EXPECT_EQ(0x6c4682d9, mrg._internal_state.state.list[178]);
            EXPECT_EQ(0x8a7ec191, mrg._internal_state.state.list[220]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(17);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x6cb7d6f5, mrg._internal_state.state.list[17]);
            EXPECT_EQ(0x7f6c2d4c, mrg._internal_state.state.list[59]);
            EXPECT_EQ(0xeeba4b51, mrg._internal_state.state.list[101]);
            EXPECT_EQ(0x9356b196, mrg._internal_state.state.list[143]);
            EXPECT_EQ(0xae84f705, mrg._internal_state.state.list[185]);
            EXPECT_EQ(0xb6e3fa5d, mrg._internal_state.state.list[227]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5300c58c, 0xb6c8bacf, 0xd07811a8, 0x1d004b2c, 0xbf8b090a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x209b4307, mrg._internal_state.state.list[38]);
            EXPECT_EQ(0x09c773af, mrg._internal_state.state.list[80]);
            EXPECT_EQ(0x3526b6a1, mrg._internal_state.state.list[122]);
            EXPECT_EQ(0x97c6d626, mrg._internal_state.state.list[164]);
            EXPECT_EQ(0x9bb4fb91, mrg._internal_state.state.list[206]);
            EXPECT_EQ(0x822f30a3, mrg._internal_state.state.list[248]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x591a7755, mrg._internal_state.state.list[27]);
            EXPECT_EQ(0xed265d05, mrg._internal_state.state.list[69]);
            EXPECT_EQ(0x50850db1, mrg._internal_state.state.list[111]);
            EXPECT_EQ(0x55e4c9e5, mrg._internal_state.state.list[153]);
            EXPECT_EQ(0x442c3cd8, mrg._internal_state.state.list[195]);
            EXPECT_EQ(0xef61a955, mrg._internal_state.state.list[237]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x189f70e0, 0x128dcd48, 0x370e755c, 0xc77233f8, 0xdbe891b3 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0xb8fc5b10, mrg._internal_state.state.list[6]);
            EXPECT_EQ(0x42e5f9bb, mrg._internal_state.state.list[48]);
            EXPECT_EQ(0x591d691f, mrg._internal_state.state.list[90]);
            EXPECT_EQ(0x2f98b506, mrg._internal_state.state.list[132]);
            EXPECT_EQ(0x1280ba85, mrg._internal_state.state.list[174]);
            EXPECT_EQ(0x42ff9df5, mrg._internal_state.state.list[216]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(-8870000000000000000);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x012e2133, mrg._internal_state.state.list[22]);
            EXPECT_EQ(0x6de00a02, mrg._internal_state.state.list[64]);
            EXPECT_EQ(0xc968b7ee, mrg._internal_state.state.list[106]);
            EXPECT_EQ(0x1c661102, mrg._internal_state.state.list[148]);
            EXPECT_EQ(0x36b3b4b1, mrg._internal_state.state.list[190]);
            EXPECT_EQ(0x99c2bd69, mrg._internal_state.state.list[232]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb629b673, 0x45c15cc3, 0x854f2c85, 0xb2725c38, 0x33b84354 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x45c15cc3, mrg._internal_state.state.list[1]);
            EXPECT_EQ(0x081d1c19, mrg._internal_state.state.list[43]);
            EXPECT_EQ(0xf2a41f9c, mrg._internal_state.state.list[85]);
            EXPECT_EQ(0x318ae2f3, mrg._internal_state.state.list[127]);
            EXPECT_EQ(0x5094e187, mrg._internal_state.state.list[169]);
            EXPECT_EQ(0xe608a7e6, mrg._internal_state.state.list[211]);
            EXPECT_EQ(0xe4406d10, mrg._internal_state.state.list[253]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(8870000000000000000);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x288353fb, mrg._internal_state.state.list[20]);
            EXPECT_EQ(0xc56561d5, mrg._internal_state.state.list[62]);
            EXPECT_EQ(0x58e9b28d, mrg._internal_state.state.list[104]);
            EXPECT_EQ(0xfceb2f8c, mrg._internal_state.state.list[146]);
            EXPECT_EQ(0x6bfd76c0, mrg._internal_state.state.list[188]);
            EXPECT_EQ(0x687a6e56, mrg._internal_state.state.list[230]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xbb4c79ee, 0x6478a0ea, 0xc76cd71a, 0x4ee25df9, 0x907cf26d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x06bb5c0b, mrg._internal_state.state.list[41]);
            EXPECT_EQ(0x4b8799c9, mrg._internal_state.state.list[83]);
            EXPECT_EQ(0xd55e5d82, mrg._internal_state.state.list[125]);
            EXPECT_EQ(0xec705d13, mrg._internal_state.state.list[167]);
            EXPECT_EQ(0x6aa469da, mrg._internal_state.state.list[209]);
            EXPECT_EQ(0xb2678ae8, mrg._internal_state.state.list[251]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(0.357);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x5fee464f, mrg._internal_state.state.list[0]);
            EXPECT_EQ(0x9882d3d0, mrg._internal_state.state.list[42]);
            EXPECT_EQ(0x0a02114b, mrg._internal_state.state.list[84]);
            EXPECT_EQ(0x1d616c45, mrg._internal_state.state.list[126]);
            EXPECT_EQ(0xe93c7669, mrg._internal_state.state.list[168]);
            EXPECT_EQ(0x5bcac23d, mrg._internal_state.state.list[210]);
            EXPECT_EQ(0xe2635469, mrg._internal_state.state.list[252]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x10db7df2, 0xb81442a6, 0xb3b2a67f, 0xbe5fc073, 0xcacd06b3 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x2efb2fee, mrg._internal_state.state.list[21]);
            EXPECT_EQ(0x6c209880, mrg._internal_state.state.list[63]);
            EXPECT_EQ(0x37e7efa2, mrg._internal_state.state.list[105]);
            EXPECT_EQ(0xc94cbbb2, mrg._internal_state.state.list[147]);
            EXPECT_EQ(0x64f96c7b, mrg._internal_state.state.list[189]);
            EXPECT_EQ(0xa1c9c800, mrg._internal_state.state.list[231]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg287 mrg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0xa01dd9f8, mrg._internal_state.state.list[27]);
            EXPECT_EQ(0xbadf8c45, mrg._internal_state.state.list[69]);
            EXPECT_EQ(0xd7db021b, mrg._internal_state.state.list[111]);
            EXPECT_EQ(0xd0ad13da, mrg._internal_state.state.list[153]);
            EXPECT_EQ(0x72bd3013, mrg._internal_state.state.list[195]);
            EXPECT_EQ(0x78f88cbf, mrg._internal_state.state.list[237]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x2cef1cef, 0x02e970e1, 0xf82c673f, 0x406644ef, 0x064b53bd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x7a5f67e3, mrg._internal_state.state.list[6]);
            EXPECT_EQ(0xc63db3b0, mrg._internal_state.state.list[48]);
            EXPECT_EQ(0x32e58fa3, mrg._internal_state.state.list[90]);
            EXPECT_EQ(0x165be770, mrg._internal_state.state.list[132]);
            EXPECT_EQ(0xdd7afc7c, mrg._internal_state.state.list[174]);
            EXPECT_EQ(0xca60c697, mrg._internal_state.state.list[216]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }

        EXPECT_THROW(Mrg287(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Mrg287(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Mrg287 mrg(mrg_1);

            EXPECT_TRUE(mrg_1._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_1._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_1._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Mrg287 mrg_0;

        {
            Mrg287 mrg_mem(mrg_0);
            Mrg287 mrg(std::move(mrg_mem));

            EXPECT_TRUE(mrg_0._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_0._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_0._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Mrg287 mrg;

            mrg = mrg_1;
            EXPECT_TRUE(mrg_1._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_1._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_1._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Mrg287 mrg;

        {
            Mrg287 mrg_mem(mrg_0);
            mrg = std::move(mrg_mem);

            EXPECT_TRUE(mrg_0._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_0._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_0._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests seed()
        mrg.seed();
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                mrg._internal_state.state.list.cbegin(),
                mrg._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);


        //-- tests seed(value)
        mrg.seed(-1);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0xb2c2ee35, mrg._internal_state.state.list[41]);
        EXPECT_EQ(0xdfd120e3, mrg._internal_state.state.list[83]);
        EXPECT_EQ(0xa81a87a0, mrg._internal_state.state.list[125]);
        EXPECT_EQ(0xc732dd53, mrg._internal_state.state.list[167]);
        EXPECT_EQ(0x14258d3d, mrg._internal_state.state.list[209]);
        EXPECT_EQ(0x5eb6852e, mrg._internal_state.state.list[251]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(1);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1, mrg._internal_state.state.list[1]);
        EXPECT_EQ(0xa7ff0d38, mrg._internal_state.state.list[43]);
        EXPECT_EQ(0xf0dad827, mrg._internal_state.state.list[85]);
        EXPECT_EQ(0x6524e51f, mrg._internal_state.state.list[127]);
        EXPECT_EQ(0x100ba66a, mrg._internal_state.state.list[169]);
        EXPECT_EQ(0xb4bdc811, mrg._internal_state.state.list[211]);
        EXPECT_EQ(0x7804cbe7, mrg._internal_state.state.list[253]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-2);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0xf0a98b8d, mrg._internal_state.state.list[40]);
        EXPECT_EQ(0xb2624a7c, mrg._internal_state.state.list[82]);
        EXPECT_EQ(0x62be4a8f, mrg._internal_state.state.list[124]);
        EXPECT_EQ(0xe7fa3f41, mrg._internal_state.state.list[166]);
        EXPECT_EQ(0x9a81c04b, mrg._internal_state.state.list[208]);
        EXPECT_EQ(0x4e0895df, mrg._internal_state.state.list[250]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(9L);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0xca067431, mrg._internal_state.state.list[9]);
        EXPECT_EQ(0x6a5307e4, mrg._internal_state.state.list[51]);
        EXPECT_EQ(0xeb76302a, mrg._internal_state.state.list[93]);
        EXPECT_EQ(0xe6c2bbc8, mrg._internal_state.state.list[135]);
        EXPECT_EQ(0x790f4a31, mrg._internal_state.state.list[177]);
        EXPECT_EQ(0xd9aa4356, mrg._internal_state.state.list[219]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-11L);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0xb029b8b5, mrg._internal_state.state.list[31]);
        EXPECT_EQ(0x13db1fa5, mrg._internal_state.state.list[73]);
        EXPECT_EQ(0x9ed3fd7c, mrg._internal_state.state.list[115]);
        EXPECT_EQ(0xe9c8d99a, mrg._internal_state.state.list[157]);
        EXPECT_EQ(0xf513d73c, mrg._internal_state.state.list[199]);
        EXPECT_EQ(0xe4e896d5, mrg._internal_state.state.list[241]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(17UL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x6cb7d6f5, mrg._internal_state.state.list[17]);
        EXPECT_EQ(0x7f6c2d4c, mrg._internal_state.state.list[59]);
        EXPECT_EQ(0xeeba4b51, mrg._internal_state.state.list[101]);
        EXPECT_EQ(0x9356b196, mrg._internal_state.state.list[143]);
        EXPECT_EQ(0xae84f705, mrg._internal_state.state.list[185]);
        EXPECT_EQ(0xb6e3fa5d, mrg._internal_state.state.list[227]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x591a7755, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0xed265d05, mrg._internal_state.state.list[69]);
        EXPECT_EQ(0x50850db1, mrg._internal_state.state.list[111]);
        EXPECT_EQ(0x55e4c9e5, mrg._internal_state.state.list[153]);
        EXPECT_EQ(0x442c3cd8, mrg._internal_state.state.list[195]);
        EXPECT_EQ(0xef61a955, mrg._internal_state.state.list[237]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x012e2133, mrg._internal_state.state.list[22]);
        EXPECT_EQ(0x6de00a02, mrg._internal_state.state.list[64]);
        EXPECT_EQ(0xc968b7ee, mrg._internal_state.state.list[106]);
        EXPECT_EQ(0x1c661102, mrg._internal_state.state.list[148]);
        EXPECT_EQ(0x36b3b4b1, mrg._internal_state.state.list[190]);
        EXPECT_EQ(0x99c2bd69, mrg._internal_state.state.list[232]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x288353fb, mrg._internal_state.state.list[20]);
        EXPECT_EQ(0xc56561d5, mrg._internal_state.state.list[62]);
        EXPECT_EQ(0x58e9b28d, mrg._internal_state.state.list[104]);
        EXPECT_EQ(0xfceb2f8c, mrg._internal_state.state.list[146]);
        EXPECT_EQ(0x6bfd76c0, mrg._internal_state.state.list[188]);
        EXPECT_EQ(0x687a6e56, mrg._internal_state.state.list[230]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(0.357);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x5fee464f, mrg._internal_state.state.list[0]);
        EXPECT_EQ(0x9882d3d0, mrg._internal_state.state.list[42]);
        EXPECT_EQ(0x0a02114b, mrg._internal_state.state.list[84]);
        EXPECT_EQ(0x1d616c45, mrg._internal_state.state.list[126]);
        EXPECT_EQ(0xe93c7669, mrg._internal_state.state.list[168]);
        EXPECT_EQ(0x5bcac23d, mrg._internal_state.state.list[210]);
        EXPECT_EQ(0xe2635469, mrg._internal_state.state.list[252]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0xa01dd9f8, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0xbadf8c45, mrg._internal_state.state.list[69]);
        EXPECT_EQ(0xd7db021b, mrg._internal_state.state.list[111]);
        EXPECT_EQ(0xd0ad13da, mrg._internal_state.state.list[153]);
        EXPECT_EQ(0x72bd3013, mrg._internal_state.state.list[195]);
        EXPECT_EQ(0x78f88cbf, mrg._internal_state.state.list[237]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        EXPECT_THROW(mrg.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(mrg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        mrg._setstate(-1LL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0xb2c2ee35, mrg._internal_state.state.list[41]);
        EXPECT_EQ(0xdfd120e3, mrg._internal_state.state.list[83]);
        EXPECT_EQ(0xa81a87a0, mrg._internal_state.state.list[125]);
        EXPECT_EQ(0xc732dd53, mrg._internal_state.state.list[167]);
        EXPECT_EQ(0x14258d3d, mrg._internal_state.state.list[209]);
        EXPECT_EQ(0x5eb6852e, mrg._internal_state.state.list[251]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        mrg.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 60) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)mrg(ENTRIES_COUNT)]++;
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
