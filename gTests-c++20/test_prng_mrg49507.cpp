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

#include "mrg49507.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsMrg49507)
    {
        //-- tests empty constructor
        Mrg49507 mrg_1;

        EXPECT_EQ(1597ULL, mrg_1._internal_state.state.list.size());
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
            Mrg49507 mrg(1);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x5f75c6d0, mrg._internal_state.state.list[1]);
            EXPECT_EQ(0x18eff17e, mrg._internal_state.state.list[267]);
            EXPECT_EQ(0x55a11f7f, mrg._internal_state.state.list[533]);
            EXPECT_EQ(0x74965c80, mrg._internal_state.state.list[799]);
            EXPECT_EQ(0x6460da87, mrg._internal_state.state.list[1065]);
            EXPECT_EQ(0x4a7fad07, mrg._internal_state.state.list[1331]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x131406ec, 0x4b1d5f0c, 0x6aabce3b, 0x086e1d9f, 0x5fbf49e1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x3ade28de, mrg._internal_state.state.list[134]);
            EXPECT_EQ(0x6d1b7ca8, mrg._internal_state.state.list[400]);
            EXPECT_EQ(0x183dab06, mrg._internal_state.state.list[666]);
            EXPECT_EQ(0x1b678581, mrg._internal_state.state.list[932]);
            EXPECT_EQ(0x6a00692a, mrg._internal_state.state.list[1198]);
            EXPECT_EQ(0x34b1b445, mrg._internal_state.state.list[1464]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(-2);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x5239e9e0, mrg._internal_state.state.list[264]);
            EXPECT_EQ(0x24411a1a, mrg._internal_state.state.list[530]);
            EXPECT_EQ(0x3f0a3f55, mrg._internal_state.state.list[796]);
            EXPECT_EQ(0x1ec33a01, mrg._internal_state.state.list[1062]);
            EXPECT_EQ(0x6e2f037f, mrg._internal_state.state.list[1328]);
            EXPECT_EQ(0x50768912, mrg._internal_state.state.list[1594]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x312d7672, 0x50dab381, 0x4a5dcd94, 0x377f84b6, 0x79e8124a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x43ccd75a, mrg._internal_state.state.list[131]);
            EXPECT_EQ(0x1711fd43, mrg._internal_state.state.list[397]);
            EXPECT_EQ(0x7c31af5b, mrg._internal_state.state.list[663]);
            EXPECT_EQ(0x51cff642, mrg._internal_state.state.list[929]);
            EXPECT_EQ(0x2019cd30, mrg._internal_state.state.list[1195]);
            EXPECT_EQ(0x2b049d30, mrg._internal_state.state.list[1461]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(9);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x65033a18, mrg._internal_state.state.list[9]);
            EXPECT_EQ(0x2f334d69, mrg._internal_state.state.list[275]);
            EXPECT_EQ(0x032aeb65, mrg._internal_state.state.list[541]);
            EXPECT_EQ(0x494d8adf, mrg._internal_state.state.list[807]);
            EXPECT_EQ(0x1288cf3f, mrg._internal_state.state.list[1073]);
            EXPECT_EQ(0x2482f4a8, mrg._internal_state.state.list[1339]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x7d134324, 0x1a0d7dc6, 0x5a91150f, 0x56ad8b95, 0x5f77ada8 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x65c44a11, mrg._internal_state.state.list[142]);
            EXPECT_EQ(0x02894067, mrg._internal_state.state.list[408]);
            EXPECT_EQ(0x69d7dbc2, mrg._internal_state.state.list[674]);
            EXPECT_EQ(0x7801cf0c, mrg._internal_state.state.list[940]);
            EXPECT_EQ(0x470e74e0, mrg._internal_state.state.list[1206]);
            EXPECT_EQ(0x063258ef, mrg._internal_state.state.list[1472]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(-11);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x123f2c51, mrg._internal_state.state.list[255]);
            EXPECT_EQ(0x24e1a7ec, mrg._internal_state.state.list[521]);
            EXPECT_EQ(0x46cf5b8e, mrg._internal_state.state.list[787]);
            EXPECT_EQ(0x1acd75ad, mrg._internal_state.state.list[1053]);
            EXPECT_EQ(0x0288f40e, mrg._internal_state.state.list[1319]);
            EXPECT_EQ(0x6abfce34, mrg._internal_state.state.list[1585]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x4fc6d964, 0x139754ea, 0x158bc1d2, 0x1f036e7b, 0x102992d7 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x1372442c, mrg._internal_state.state.list[122]);
            EXPECT_EQ(0x1b3928aa, mrg._internal_state.state.list[388]);
            EXPECT_EQ(0x47a17a10, mrg._internal_state.state.list[654]);
            EXPECT_EQ(0x56b662d8, mrg._internal_state.state.list[920]);
            EXPECT_EQ(0x052095ef, mrg._internal_state.state.list[1186]);
            EXPECT_EQ(0x42b4196d, mrg._internal_state.state.list[1452]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(17);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x365beb7a, mrg._internal_state.state.list[17]);
            EXPECT_EQ(0x3e0cb6d1, mrg._internal_state.state.list[283]);
            EXPECT_EQ(0x1da28fd0, mrg._internal_state.state.list[549]);
            EXPECT_EQ(0x66755792, mrg._internal_state.state.list[815]);
            EXPECT_EQ(0x65bbeb6b, mrg._internal_state.state.list[1081]);
            EXPECT_EQ(0x18873938, mrg._internal_state.state.list[1347]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x16ff5829, 0x2107fe85, 0x52a7a857, 0x7b76dd0f, 0x747a8cac };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x31a07e41, mrg._internal_state.state.list[150]);
            EXPECT_EQ(0x7ba45afe, mrg._internal_state.state.list[416]);
            EXPECT_EQ(0x669ffee6, mrg._internal_state.state.list[682]);
            EXPECT_EQ(0x559daffb, mrg._internal_state.state.list[948]);
            EXPECT_EQ(0x340eb44a, mrg._internal_state.state.list[1214]);
            EXPECT_EQ(0x3028c2ee, mrg._internal_state.state.list[1480]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x22161e6c, mrg._internal_state.state.list[195]);
            EXPECT_EQ(0x2c540f50, mrg._internal_state.state.list[461]);
            EXPECT_EQ(0x3dd37934, mrg._internal_state.state.list[727]);
            EXPECT_EQ(0x322564a4, mrg._internal_state.state.list[993]);
            EXPECT_EQ(0x338c2677, mrg._internal_state.state.list[1259]);
            EXPECT_EQ(0x214ccbe7, mrg._internal_state.state.list[1525]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x142cabde, 0x616d6b20, 0x665602d0, 0x51eb821a, 0x129949ef };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x3c1055e0, mrg._internal_state.state.list[62]);
            EXPECT_EQ(0x2c69c157, mrg._internal_state.state.list[328]);
            EXPECT_EQ(0x48128c13, mrg._internal_state.state.list[594]);
            EXPECT_EQ(0x76d1e78c, mrg._internal_state.state.list[860]);
            EXPECT_EQ(0x6d472f68, mrg._internal_state.state.list[1126]);
            EXPECT_EQ(0x21476161, mrg._internal_state.state.list[1392]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(-8870000000000000000);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x3a2a1d02, mrg._internal_state.state.list[176]);
            EXPECT_EQ(0x290ae9c8, mrg._internal_state.state.list[442]);
            EXPECT_EQ(0x23a1f3ef, mrg._internal_state.state.list[708]);
            EXPECT_EQ(0x501cfb6f, mrg._internal_state.state.list[974]);
            EXPECT_EQ(0x23247fa1, mrg._internal_state.state.list[1240]);
            EXPECT_EQ(0x141b3fde, mrg._internal_state.state.list[1506]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x3bf48c37, 0x5b8ceda1, 0x63f57523, 0x09293975, 0x682e87b8 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x040e8e0c, mrg._internal_state.state.list[43]);
            EXPECT_EQ(0x7ef619fe, mrg._internal_state.state.list[309]);
            EXPECT_EQ(0x60e293f2, mrg._internal_state.state.list[575]);
            EXPECT_EQ(0x44741e66, mrg._internal_state.state.list[841]);
            EXPECT_EQ(0x359f977e, mrg._internal_state.state.list[1107]);
            EXPECT_EQ(0x130bfb7e, mrg._internal_state.state.list[1373]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(8870000000000000000);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x52c8b378, mrg._internal_state.state.list[90]);
            EXPECT_EQ(0x03cb6c1e, mrg._internal_state.state.list[356]);
            EXPECT_EQ(0x5bb1be93, mrg._internal_state.state.list[622]);
            EXPECT_EQ(0x22e6f2ce, mrg._internal_state.state.list[888]);
            EXPECT_EQ(0x7a3e53b6, mrg._internal_state.state.list[1154]);
            EXPECT_EQ(0x42faeace, mrg._internal_state.state.list[1420]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x66168d31, 0x6c259913, 0x544a8995, 0x08a4bf3f, 0x300943a0 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x175ea947, mrg._internal_state.state.list[223]);
            EXPECT_EQ(0x513c8052, mrg._internal_state.state.list[489]);
            EXPECT_EQ(0x74e98b5c, mrg._internal_state.state.list[755]);
            EXPECT_EQ(0x40db937d, mrg._internal_state.state.list[1021]);
            EXPECT_EQ(0x7f6cb0bc, mrg._internal_state.state.list[1287]);
            EXPECT_EQ(0x172f6cf6, mrg._internal_state.state.list[1553]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(0.357);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x2ff72327, mrg._internal_state.state.list[0]);
            EXPECT_EQ(0x0d50b0c0, mrg._internal_state.state.list[266]);
            EXPECT_EQ(0x156820b8, mrg._internal_state.state.list[532]);
            EXPECT_EQ(0x24a731ed, mrg._internal_state.state.list[798]);
            EXPECT_EQ(0x505a1c7e, mrg._internal_state.state.list[1064]);
            EXPECT_EQ(0x18dca9e2, mrg._internal_state.state.list[1330]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5517b3cb, 0x61d5b167, 0x5694860f, 0x2b2eacb9, 0x608e74f4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x058809f6, mrg._internal_state.state.list[133]);
            EXPECT_EQ(0x631faa67, mrg._internal_state.state.list[399]);
            EXPECT_EQ(0x45a657b1, mrg._internal_state.state.list[665]);
            EXPECT_EQ(0x6b0f9802, mrg._internal_state.state.list[931]);
            EXPECT_EQ(0x648ee44c, mrg._internal_state.state.list[1197]);
            EXPECT_EQ(0x5ebdfc83, mrg._internal_state.state.list[1463]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg49507 mrg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x1dacc61b, mrg._internal_state.state.list[41]);
            EXPECT_EQ(0x7d78f872, mrg._internal_state.state.list[307]);
            EXPECT_EQ(0x132a5660, mrg._internal_state.state.list[573]);
            EXPECT_EQ(0x59ea938c, mrg._internal_state.state.list[839]);
            EXPECT_EQ(0x21161c1b, mrg._internal_state.state.list[1105]);
            EXPECT_EQ(0x0a371094, mrg._internal_state.state.list[1371]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x76a13320, 0x0a7000a4, 0x4730fe6b, 0x265e1575, 0x6b025a4f };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x6ebd7e3e, mrg._internal_state.state.list[174]);
            EXPECT_EQ(0x5fa1f887, mrg._internal_state.state.list[440]);
            EXPECT_EQ(0x0be48de9, mrg._internal_state.state.list[706]);
            EXPECT_EQ(0x14e2da6f, mrg._internal_state.state.list[972]);
            EXPECT_EQ(0x7036e134, mrg._internal_state.state.list[1238]);
            EXPECT_EQ(0x1d73d915, mrg._internal_state.state.list[1504]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }

        EXPECT_THROW(Mrg49507(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Mrg49507(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Mrg49507 mrg(mrg_1);

            EXPECT_TRUE(mrg_1._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_1._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_1._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Mrg49507 mrg_0;

        {
            Mrg49507 mrg_mem(mrg_0);
            Mrg49507 mrg(std::move(mrg_mem));

            EXPECT_TRUE(mrg_0._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_0._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_0._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Mrg49507 mrg;

            mrg = mrg_1;
            EXPECT_TRUE(mrg_1._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_1._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_1._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Mrg49507 mrg;

        {
            Mrg49507 mrg_mem(mrg_0);
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
        EXPECT_EQ(0x3bafada8, mrg._internal_state.state.list[265]);
        EXPECT_EQ(0x535d997d, mrg._internal_state.state.list[531]);
        EXPECT_EQ(0x446ed2d2, mrg._internal_state.state.list[797]);
        EXPECT_EQ(0x7de01220, mrg._internal_state.state.list[1063]);
        EXPECT_EQ(0x2323f716, mrg._internal_state.state.list[1329]);
        EXPECT_EQ(0x5798d26c, mrg._internal_state.state.list[1595]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(1);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x5f75c6d0, mrg._internal_state.state.list[1]);
        EXPECT_EQ(0x18eff17e, mrg._internal_state.state.list[267]);
        EXPECT_EQ(0x55a11f7f, mrg._internal_state.state.list[533]);
        EXPECT_EQ(0x74965c80, mrg._internal_state.state.list[799]);
        EXPECT_EQ(0x6460da87, mrg._internal_state.state.list[1065]);
        EXPECT_EQ(0x4a7fad07, mrg._internal_state.state.list[1331]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-2);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x5239e9e0, mrg._internal_state.state.list[264]);
        EXPECT_EQ(0x24411a1a, mrg._internal_state.state.list[530]);
        EXPECT_EQ(0x3f0a3f55, mrg._internal_state.state.list[796]);
        EXPECT_EQ(0x1ec33a01, mrg._internal_state.state.list[1062]);
        EXPECT_EQ(0x6e2f037f, mrg._internal_state.state.list[1328]);
        EXPECT_EQ(0x50768912, mrg._internal_state.state.list[1594]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(9L);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x65033a18, mrg._internal_state.state.list[9]);
        EXPECT_EQ(0x2f334d69, mrg._internal_state.state.list[275]);
        EXPECT_EQ(0x032aeb65, mrg._internal_state.state.list[541]);
        EXPECT_EQ(0x494d8adf, mrg._internal_state.state.list[807]);
        EXPECT_EQ(0x1288cf3f, mrg._internal_state.state.list[1073]);
        EXPECT_EQ(0x2482f4a8, mrg._internal_state.state.list[1339]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-11L);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x123f2c51, mrg._internal_state.state.list[255]);
        EXPECT_EQ(0x24e1a7ec, mrg._internal_state.state.list[521]);
        EXPECT_EQ(0x46cf5b8e, mrg._internal_state.state.list[787]);
        EXPECT_EQ(0x1acd75ad, mrg._internal_state.state.list[1053]);
        EXPECT_EQ(0x0288f40e, mrg._internal_state.state.list[1319]);
        EXPECT_EQ(0x6abfce34, mrg._internal_state.state.list[1585]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(17UL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x365beb7a, mrg._internal_state.state.list[17]);
        EXPECT_EQ(0x3e0cb6d1, mrg._internal_state.state.list[283]);
        EXPECT_EQ(0x1da28fd0, mrg._internal_state.state.list[549]);
        EXPECT_EQ(0x66755792, mrg._internal_state.state.list[815]);
        EXPECT_EQ(0x65bbeb6b, mrg._internal_state.state.list[1081]);
        EXPECT_EQ(0x18873938, mrg._internal_state.state.list[1347]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x22161e6c, mrg._internal_state.state.list[195]);
        EXPECT_EQ(0x2c540f50, mrg._internal_state.state.list[461]);
        EXPECT_EQ(0x3dd37934, mrg._internal_state.state.list[727]);
        EXPECT_EQ(0x322564a4, mrg._internal_state.state.list[993]);
        EXPECT_EQ(0x338c2677, mrg._internal_state.state.list[1259]);
        EXPECT_EQ(0x214ccbe7, mrg._internal_state.state.list[1525]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x3a2a1d02, mrg._internal_state.state.list[176]);
        EXPECT_EQ(0x290ae9c8, mrg._internal_state.state.list[442]);
        EXPECT_EQ(0x23a1f3ef, mrg._internal_state.state.list[708]);
        EXPECT_EQ(0x501cfb6f, mrg._internal_state.state.list[974]);
        EXPECT_EQ(0x23247fa1, mrg._internal_state.state.list[1240]);
        EXPECT_EQ(0x141b3fde, mrg._internal_state.state.list[1506]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x52c8b378, mrg._internal_state.state.list[90]);
        EXPECT_EQ(0x03cb6c1e, mrg._internal_state.state.list[356]);
        EXPECT_EQ(0x5bb1be93, mrg._internal_state.state.list[622]);
        EXPECT_EQ(0x22e6f2ce, mrg._internal_state.state.list[888]);
        EXPECT_EQ(0x7a3e53b6, mrg._internal_state.state.list[1154]);
        EXPECT_EQ(0x42faeace, mrg._internal_state.state.list[1420]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(0.357);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x2ff72327, mrg._internal_state.state.list[0]);
        EXPECT_EQ(0x0d50b0c0, mrg._internal_state.state.list[266]);
        EXPECT_EQ(0x156820b8, mrg._internal_state.state.list[532]);
        EXPECT_EQ(0x24a731ed, mrg._internal_state.state.list[798]);
        EXPECT_EQ(0x505a1c7e, mrg._internal_state.state.list[1064]);
        EXPECT_EQ(0x18dca9e2, mrg._internal_state.state.list[1330]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x1dacc61b, mrg._internal_state.state.list[41]);
        EXPECT_EQ(0x7d78f872, mrg._internal_state.state.list[307]);
        EXPECT_EQ(0x132a5660, mrg._internal_state.state.list[573]);
        EXPECT_EQ(0x59ea938c, mrg._internal_state.state.list[839]);
        EXPECT_EQ(0x21161c1b, mrg._internal_state.state.list[1105]);
        EXPECT_EQ(0x0a371094, mrg._internal_state.state.list[1371]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        EXPECT_THROW(mrg.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(mrg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        mrg._setstate(-1LL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x3bafada8, mrg._internal_state.state.list[265]);
        EXPECT_EQ(0x535d997d, mrg._internal_state.state.list[531]);
        EXPECT_EQ(0x446ed2d2, mrg._internal_state.state.list[797]);
        EXPECT_EQ(0x7de01220, mrg._internal_state.state.list[1063]);
        EXPECT_EQ(0x2323f716, mrg._internal_state.state.list[1329]);
        EXPECT_EQ(0x5798d26c, mrg._internal_state.state.list[1595]);
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
