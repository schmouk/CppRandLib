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

#include "lfib1340.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsLFib1340)
    {
        //-- tests empty constructor
        LFib1340 lfib_1;

        EXPECT_EQ(1279ULL, lfib_1._internal_state.state.list.size());
        EXPECT_EQ(0, lfib_1._internal_state.state.index);
        EXPECT_TRUE(std::ranges::any_of(lfib_1._internal_state.state.list, [](auto s) { return s != 0; }));
        EXPECT_FALSE(lfib_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            LFib1340 lfib(1);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xf902155aa328d575, lfib._internal_state.state.list[72]);
            EXPECT_EQ(0x741cad5364f02a78, lfib._internal_state.state.list[285]);
            EXPECT_EQ(0xb844e2ec5f91aae4, lfib._internal_state.state.list[498]);
            EXPECT_EQ(0x3a62209c3fcf0186, lfib._internal_state.state.list[711]);
            EXPECT_EQ(0x5fa048438ae81274, lfib._internal_state.state.list[924]);
            EXPECT_EQ(0xba01f31340cbe6dd, lfib._internal_state.state.list[1137]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x952a109fe83cd2be, 0x041cbf7396197a05, 0xf0ae341bba23e17c, 0x61eecbcaf968dcfe, 0xa46a59bd8d5a5d9a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x8c7ca121fd9fb515, lfib._internal_state.state.list[143]);
            EXPECT_EQ(0xaca3375dd6d07d49, lfib._internal_state.state.list[356]);
            EXPECT_EQ(0x40689f70150ef04a, lfib._internal_state.state.list[569]);
            EXPECT_EQ(0xf5cacda28569f2cb, lfib._internal_state.state.list[782]);
            EXPECT_EQ(0xd0ab06416a03afe7, lfib._internal_state.state.list[995]);
            EXPECT_EQ(0xd0f4ae660045ef1d, lfib._internal_state.state.list[1208]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(-2);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x7892c83522f7d7ef, lfib._internal_state.state.list[69]);
            EXPECT_EQ(0xf37b8c9e51800f48, lfib._internal_state.state.list[282]);
            EXPECT_EQ(0xc314d56916b97b66, lfib._internal_state.state.list[495]);
            EXPECT_EQ(0xdbc7469e2509e204, lfib._internal_state.state.list[708]);
            EXPECT_EQ(0x6939f1bb0f77111a, lfib._internal_state.state.list[921]);
            EXPECT_EQ(0x700be0b1f884906f, lfib._internal_state.state.list[1134]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xff50adf3572e5c51, 0xdb9ee6b069154793, 0xd9cea56a1355da12, 0x5b6fbe1543c606fe, 0x57bc1a889c4d93ba };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x44796f16ad630136, lfib._internal_state.state.list[140]);
            EXPECT_EQ(0x539cf95d15921891, lfib._internal_state.state.list[353]);
            EXPECT_EQ(0xd1cefb4f1047ea18, lfib._internal_state.state.list[566]);
            EXPECT_EQ(0x7dfbbfb0e98490f8, lfib._internal_state.state.list[779]);
            EXPECT_EQ(0xd5ff66230deb85d0, lfib._internal_state.state.list[992]);
            EXPECT_EQ(0x54a885615dd575fe, lfib._internal_state.state.list[1205]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(9);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xf65638b907c07ab1, lfib._internal_state.state.list[80]);
            EXPECT_EQ(0x6732d317c6459927, lfib._internal_state.state.list[293]);
            EXPECT_EQ(0xf475ef560744c220, lfib._internal_state.state.list[506]);
            EXPECT_EQ(0x731f5f3452c5ac44, lfib._internal_state.state.list[719]);
            EXPECT_EQ(0xbb184925b72717e5, lfib._internal_state.state.list[932]);
            EXPECT_EQ(0x417475f5a90532e3, lfib._internal_state.state.list[1145]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x00022d49c4d8db5d, 0x3d455840a2ab0dfd, 0xc8de7b75093dd1b4, 0x8198133ed993b548, 0x86f5e4138393fce3 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xd9dad1cb89328aa6, lfib._internal_state.state.list[151]);
            EXPECT_EQ(0x73a6535e962822ed, lfib._internal_state.state.list[364]);
            EXPECT_EQ(0xe772bf683a8580a2, lfib._internal_state.state.list[577]);
            EXPECT_EQ(0xf07b8cfa23458981, lfib._internal_state.state.list[790]);
            EXPECT_EQ(0xb7155d275b9f9d6f, lfib._internal_state.state.list[1003]);
            EXPECT_EQ(0xdfe37c9702f971b2, lfib._internal_state.state.list[1216]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(-11);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xcb337d3f0fd24bf6, lfib._internal_state.state.list[60]);
            EXPECT_EQ(0xe339b0eb93152afe, lfib._internal_state.state.list[273]);
            EXPECT_EQ(0x4e167b4cf1f32a33, lfib._internal_state.state.list[486]);
            EXPECT_EQ(0x7c7724f7f3f2063f, lfib._internal_state.state.list[699]);
            EXPECT_EQ(0x2ac2e95cfa88e57a, lfib._internal_state.state.list[912]);
            EXPECT_EQ(0xa0e59eb935c35056, lfib._internal_state.state.list[1125]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf5277eed359f2027, 0xbda6ec10e04075f2, 0x6228c544b62023ed, 0x007e5f0a03013730, 0xfc8ed1a548f7c856 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x0361175ccba2fed5, lfib._internal_state.state.list[131]);
            EXPECT_EQ(0x760f3fae13bb7ef3, lfib._internal_state.state.list[344]);
            EXPECT_EQ(0x109dbad26d73bf93, lfib._internal_state.state.list[557]);
            EXPECT_EQ(0xf75aa750e9975115, lfib._internal_state.state.list[770]);
            EXPECT_EQ(0x280a8027c4f57bc5, lfib._internal_state.state.list[983]);
            EXPECT_EQ(0x0866c16aa49ee427, lfib._internal_state.state.list[1196]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(17);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x40b826594cfc38d1, lfib._internal_state.state.list[88]);
            EXPECT_EQ(0xc17c5801351fb216, lfib._internal_state.state.list[301]);
            EXPECT_EQ(0xf0dcc79d4c352b15, lfib._internal_state.state.list[514]);
            EXPECT_EQ(0x99b5b6c5148f06f0, lfib._internal_state.state.list[727]);
            EXPECT_EQ(0x878cc148a39eae06, lfib._internal_state.state.list[940]);
            EXPECT_EQ(0x41b846f60f00826a, lfib._internal_state.state.list[1153]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x8fb383eb342f7ba1, 0x0b81539a7909a2b2, 0xa4f71f3ea6e6d248, 0x819cec69337dcb95, 0xab1791f7cd6d309f };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xd9bafed52d1a2d99, lfib._internal_state.state.list[159]);
            EXPECT_EQ(0x31ce683f8677dd86, lfib._internal_state.state.list[372]);
            EXPECT_EQ(0xafd1400f337d6174, lfib._internal_state.state.list[585]);
            EXPECT_EQ(0xcaa58a7dfc93295c, lfib._internal_state.state.list[798]);
            EXPECT_EQ(0x54c47a2462058e6f, lfib._internal_state.state.list[1011]);
            EXPECT_EQ(0x590f62f3782d0a96, lfib._internal_state.state.list[1224]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x349ffd38cb9dd55d, lfib._internal_state.state.list[176]);
            EXPECT_EQ(0xd57d7467699349cb, lfib._internal_state.state.list[389]);
            EXPECT_EQ(0x2736fee2a4e1416a, lfib._internal_state.state.list[602]);
            EXPECT_EQ(0x1251b233b6bee6b8, lfib._internal_state.state.list[815]);
            EXPECT_EQ(0x3fb8a1cf72aa7d52, lfib._internal_state.state.list[1028]);
            EXPECT_EQ(0x5a8736fd16abc59e, lfib._internal_state.state.list[1241]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf808ad0938a84212, 0x8bcb541c42eef6b5, 0x94d93887673e368f, 0x4c922b172455da8f, 0xda7f94589c17e131 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xf7a2cc8df2b2c4f6, lfib._internal_state.state.list[34]);
            EXPECT_EQ(0x7e07ab8606a92cfc, lfib._internal_state.state.list[247]);
            EXPECT_EQ(0x997ee6416930557b, lfib._internal_state.state.list[460]);
            EXPECT_EQ(0x20d4e5146b3bff6d, lfib._internal_state.state.list[673]);
            EXPECT_EQ(0x3b2ee6608180063f, lfib._internal_state.state.list[886]);
            EXPECT_EQ(0x820166d19fd2b597, lfib._internal_state.state.list[1099]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(-8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x58936da4dd390547, lfib._internal_state.state.list[114]);
            EXPECT_EQ(0xc4b92afd301cb2b4, lfib._internal_state.state.list[327]);
            EXPECT_EQ(0xcfde8fee4028fe15, lfib._internal_state.state.list[540]);
            EXPECT_EQ(0x350ffeb259eadcc7, lfib._internal_state.state.list[753]);
            EXPECT_EQ(0x509add6ee2f82a6d, lfib._internal_state.state.list[966]);
            EXPECT_EQ(0x8b52f609e9039839, lfib._internal_state.state.list[1179]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x3d48bf12edda0053, 0xe2cd543312b1c414, 0x9fd3d82480e14c03, 0x2ca0a824409fafb0, 0x6355c2b4f083ba40 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xc9502541955ea35f, lfib._internal_state.state.list[185]);
            EXPECT_EQ(0x7f4ab2cfda515ef0, lfib._internal_state.state.list[398]);
            EXPECT_EQ(0xb77009cb6041797b, lfib._internal_state.state.list[611]);
            EXPECT_EQ(0xf9160963dfba6730, lfib._internal_state.state.list[824]);
            EXPECT_EQ(0x0f553d0dd75fc806, lfib._internal_state.state.list[1037]);
            EXPECT_EQ(0x64da6495371bedcf, lfib._internal_state.state.list[1250]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x8670f33f969fb20d, lfib._internal_state.state.list[28]);
            EXPECT_EQ(0x780261dabe792b80, lfib._internal_state.state.list[241]);
            EXPECT_EQ(0x20c9a6945b67e651, lfib._internal_state.state.list[454]);
            EXPECT_EQ(0x0c18711ceef4d0f2, lfib._internal_state.state.list[667]);
            EXPECT_EQ(0x6c73ee9b31f3a8db, lfib._internal_state.state.list[880]);
            EXPECT_EQ(0x10187b94f0384098, lfib._internal_state.state.list[1093]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x6dfa45f3f1992c46, 0x089767a4540e5125, 0x94c5bb22f59704f8, 0x9a66aebf73655445, 0xd5b4569f3f954873 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xff2df6a181cd39dc, lfib._internal_state.state.list[99]);
            EXPECT_EQ(0x9e848fa014031d88, lfib._internal_state.state.list[312]);
            EXPECT_EQ(0x8158cc9dc7bb31a0, lfib._internal_state.state.list[525]);
            EXPECT_EQ(0x73406cd8db36db36, lfib._internal_state.state.list[738]);
            EXPECT_EQ(0x7bb2b19779022d46, lfib._internal_state.state.list[951]);
            EXPECT_EQ(0x870f4b358aace012, lfib._internal_state.state.list[1164]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(-0.357);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x7fde3752e0b07d27, lfib._internal_state.state.list[71]);
            EXPECT_EQ(0xefc598238522eb63, lfib._internal_state.state.list[284]);
            EXPECT_EQ(0x91af6061e4006dcc, lfib._internal_state.state.list[497]);
            EXPECT_EQ(0x312725df9584eeb3, lfib._internal_state.state.list[710]);
            EXPECT_EQ(0xb6716d176c4b597a, lfib._internal_state.state.list[923]);
            EXPECT_EQ(0x224cf21abad4b4ae, lfib._internal_state.state.list[1136]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5632b0658fc55ee9, 0x3f3537953c7230d8, 0x9ac51b0ebba3b7f4, 0x30d65f7ca083d20a, 0x7d279a8cfe4abece };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xd7c8565de70f219b, lfib._internal_state.state.list[142]);
            EXPECT_EQ(0x97c131c2d3fe994f, lfib._internal_state.state.list[355]);
            EXPECT_EQ(0xb57bb459b26b13ad, lfib._internal_state.state.list[568]);
            EXPECT_EQ(0xcc0f4066f4b8d873, lfib._internal_state.state.list[781]);
            EXPECT_EQ(0x4587edf490dd2ae3, lfib._internal_state.state.list[994]);
            EXPECT_EQ(0xb2d169b9dff026e4, lfib._internal_state.state.list[1207]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(8.87e+18);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x8670f33f969fb20d, lfib._internal_state.state.list[28]);
            EXPECT_EQ(0x780261dabe792b80, lfib._internal_state.state.list[241]);
            EXPECT_EQ(0x20c9a6945b67e651, lfib._internal_state.state.list[454]);
            EXPECT_EQ(0x0c18711ceef4d0f2, lfib._internal_state.state.list[667]);
            EXPECT_EQ(0x6c73ee9b31f3a8db, lfib._internal_state.state.list[880]);
            EXPECT_EQ(0x10187b94f0384098, lfib._internal_state.state.list[1093]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x6dfa45f3f1992c46, 0x089767a4540e5125, 0x94c5bb22f59704f8, 0x9a66aebf73655445, 0xd5b4569f3f954873 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xff2df6a181cd39dc, lfib._internal_state.state.list[99]);
            EXPECT_EQ(0x9e848fa014031d88, lfib._internal_state.state.list[312]);
            EXPECT_EQ(0x8158cc9dc7bb31a0, lfib._internal_state.state.list[525]);
            EXPECT_EQ(0x73406cd8db36db36, lfib._internal_state.state.list[738]);
            EXPECT_EQ(0x7bb2b19779022d46, lfib._internal_state.state.list[951]);
            EXPECT_EQ(0x870f4b358aace012, lfib._internal_state.state.list[1164]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib1340 lfib(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xd461ce58038fc9f9, lfib._internal_state.state.list[158]);
            EXPECT_EQ(0x10970a243a7818bb, lfib._internal_state.state.list[371]);
            EXPECT_EQ(0x53add06887e5c0fd, lfib._internal_state.state.list[584]);
            EXPECT_EQ(0x26d20c416ef4b509, lfib._internal_state.state.list[797]);
            EXPECT_EQ(0xfeb0fca0a50ab9d2, lfib._internal_state.state.list[1010]);
            EXPECT_EQ(0xf68183fdd3bb40e8, lfib._internal_state.state.list[1223]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x1c0ec6c67fc5c35d, 0xa2893965d8b0a613, 0x7f76a10aea2d5096, 0xe78b3958185c2a18, 0x140c7a71df2beeb1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x66fb5ba3ae1546e0, lfib._internal_state.state.list[16]);
            EXPECT_EQ(0xbafc9ffd354012e4, lfib._internal_state.state.list[229]);
            EXPECT_EQ(0x2ed260411b39656d, lfib._internal_state.state.list[442]);
            EXPECT_EQ(0xc5af87d5405a9a73, lfib._internal_state.state.list[655]);
            EXPECT_EQ(0xe72fdb17c2844a96, lfib._internal_state.state.list[868]);
            EXPECT_EQ(0x39a07dfa75338327, lfib._internal_state.state.list[1081]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }


        //-- tests copy constructor
        {
            LFib1340 lfib(lfib_1);

            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move constructor
        LFib1340 lfib_0;

        {
            LFib1340 lfib_mem(lfib_0);
            LFib1340 lfib(std::move(lfib_mem));

            EXPECT_TRUE(lfib_0._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_0._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_0._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            LFib1340 lfib;

            lfib = lfib_1;
            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move assignement
        LFib1340 lfib;

        {
            LFib1340 lfib_mem(lfib_0);
            lfib = std::move(lfib_mem);

            EXPECT_TRUE(lfib_0._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_0._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_0._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests seed()
        lfib.seed();
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_TRUE(std::ranges::any_of(lfib._internal_state.state.list, [](auto s) { return s != 0; }));
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);


        //-- tests seed(value)
        lfib.seed(-1);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xc5ee6d5ad3840f45, lfib._internal_state.state.list[70]);
        EXPECT_EQ(0x6415fdcadee16cf5, lfib._internal_state.state.list[283]);
        EXPECT_EQ(0xc165e8b5e4b5cf31, lfib._internal_state.state.list[496]);
        EXPECT_EQ(0x66eb466019e23a95, lfib._internal_state.state.list[709]);
        EXPECT_EQ(0x61844a6d3de51ee8, lfib._internal_state.state.list[922]);
        EXPECT_EQ(0x386a84015d7bf286, lfib._internal_state.state.list[1135]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(1);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xf902155aa328d575, lfib._internal_state.state.list[72]);
        EXPECT_EQ(0x741cad5364f02a78, lfib._internal_state.state.list[285]);
        EXPECT_EQ(0xb844e2ec5f91aae4, lfib._internal_state.state.list[498]);
        EXPECT_EQ(0x3a62209c3fcf0186, lfib._internal_state.state.list[711]);
        EXPECT_EQ(0x5fa048438ae81274, lfib._internal_state.state.list[924]);
        EXPECT_EQ(0xba01f31340cbe6dd, lfib._internal_state.state.list[1137]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-2);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x7892c83522f7d7ef, lfib._internal_state.state.list[69]);
        EXPECT_EQ(0xf37b8c9e51800f48, lfib._internal_state.state.list[282]);
        EXPECT_EQ(0xc314d56916b97b66, lfib._internal_state.state.list[495]);
        EXPECT_EQ(0xdbc7469e2509e204, lfib._internal_state.state.list[708]);
        EXPECT_EQ(0x6939f1bb0f77111a, lfib._internal_state.state.list[921]);
        EXPECT_EQ(0x700be0b1f884906f, lfib._internal_state.state.list[1134]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(9L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xf65638b907c07ab1, lfib._internal_state.state.list[80]);
        EXPECT_EQ(0x6732d317c6459927, lfib._internal_state.state.list[293]);
        EXPECT_EQ(0xf475ef560744c220, lfib._internal_state.state.list[506]);
        EXPECT_EQ(0x731f5f3452c5ac44, lfib._internal_state.state.list[719]);
        EXPECT_EQ(0xbb184925b72717e5, lfib._internal_state.state.list[932]);
        EXPECT_EQ(0x417475f5a90532e3, lfib._internal_state.state.list[1145]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-11L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xcb337d3f0fd24bf6, lfib._internal_state.state.list[60]);
        EXPECT_EQ(0xe339b0eb93152afe, lfib._internal_state.state.list[273]);
        EXPECT_EQ(0x4e167b4cf1f32a33, lfib._internal_state.state.list[486]);
        EXPECT_EQ(0x7c7724f7f3f2063f, lfib._internal_state.state.list[699]);
        EXPECT_EQ(0x2ac2e95cfa88e57a, lfib._internal_state.state.list[912]);
        EXPECT_EQ(0xa0e59eb935c35056, lfib._internal_state.state.list[1125]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(17UL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x40b826594cfc38d1, lfib._internal_state.state.list[88]);
        EXPECT_EQ(0xc17c5801351fb216, lfib._internal_state.state.list[301]);
        EXPECT_EQ(0xf0dcc79d4c352b15, lfib._internal_state.state.list[514]);
        EXPECT_EQ(0x99b5b6c5148f06f0, lfib._internal_state.state.list[727]);
        EXPECT_EQ(0x878cc148a39eae06, lfib._internal_state.state.list[940]);
        EXPECT_EQ(0x41b846f60f00826a, lfib._internal_state.state.list[1153]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x349ffd38cb9dd55d, lfib._internal_state.state.list[176]);
        EXPECT_EQ(0xd57d7467699349cb, lfib._internal_state.state.list[389]);
        EXPECT_EQ(0x2736fee2a4e1416a, lfib._internal_state.state.list[602]);
        EXPECT_EQ(0x1251b233b6bee6b8, lfib._internal_state.state.list[815]);
        EXPECT_EQ(0x3fb8a1cf72aa7d52, lfib._internal_state.state.list[1028]);
        EXPECT_EQ(0x5a8736fd16abc59e, lfib._internal_state.state.list[1241]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x58936da4dd390547, lfib._internal_state.state.list[114]);
        EXPECT_EQ(0xc4b92afd301cb2b4, lfib._internal_state.state.list[327]);
        EXPECT_EQ(0xcfde8fee4028fe15, lfib._internal_state.state.list[540]);
        EXPECT_EQ(0x350ffeb259eadcc7, lfib._internal_state.state.list[753]);
        EXPECT_EQ(0x509add6ee2f82a6d, lfib._internal_state.state.list[966]);
        EXPECT_EQ(0x8b52f609e9039839, lfib._internal_state.state.list[1179]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x8670f33f969fb20d, lfib._internal_state.state.list[28]);
        EXPECT_EQ(0x780261dabe792b80, lfib._internal_state.state.list[241]);
        EXPECT_EQ(0x20c9a6945b67e651, lfib._internal_state.state.list[454]);
        EXPECT_EQ(0x0c18711ceef4d0f2, lfib._internal_state.state.list[667]);
        EXPECT_EQ(0x6c73ee9b31f3a8db, lfib._internal_state.state.list[880]);
        EXPECT_EQ(0x10187b94f0384098, lfib._internal_state.state.list[1093]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-0.357);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x7fde3752e0b07d27, lfib._internal_state.state.list[71]);
        EXPECT_EQ(0xefc598238522eb63, lfib._internal_state.state.list[284]);
        EXPECT_EQ(0x91af6061e4006dcc, lfib._internal_state.state.list[497]);
        EXPECT_EQ(0x312725df9584eeb3, lfib._internal_state.state.list[710]);
        EXPECT_EQ(0xb6716d176c4b597a, lfib._internal_state.state.list[923]);
        EXPECT_EQ(0x224cf21abad4b4ae, lfib._internal_state.state.list[1136]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(8.87e+18);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x8670f33f969fb20d, lfib._internal_state.state.list[28]);
        EXPECT_EQ(0x780261dabe792b80, lfib._internal_state.state.list[241]);
        EXPECT_EQ(0x20c9a6945b67e651, lfib._internal_state.state.list[454]);
        EXPECT_EQ(0x0c18711ceef4d0f2, lfib._internal_state.state.list[667]);
        EXPECT_EQ(0x6c73ee9b31f3a8db, lfib._internal_state.state.list[880]);
        EXPECT_EQ(0x10187b94f0384098, lfib._internal_state.state.list[1093]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xd461ce58038fc9f9, lfib._internal_state.state.list[158]);
        EXPECT_EQ(0x10970a243a7818bb, lfib._internal_state.state.list[371]);
        EXPECT_EQ(0x53add06887e5c0fd, lfib._internal_state.state.list[584]);
        EXPECT_EQ(0x26d20c416ef4b509, lfib._internal_state.state.list[797]);
        EXPECT_EQ(0xfeb0fca0a50ab9d2, lfib._internal_state.state.list[1010]);
        EXPECT_EQ(0xf68183fdd3bb40e8, lfib._internal_state.state.list[1223]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);


        //-- tests _setstate(seed_)
        lfib._setstate(-1LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xc5ee6d5ad3840f45, lfib._internal_state.state.list[70]);
        EXPECT_EQ(0x6415fdcadee16cf5, lfib._internal_state.state.list[283]);
        EXPECT_EQ(0xc165e8b5e4b5cf31, lfib._internal_state.state.list[496]);
        EXPECT_EQ(0x66eb466019e23a95, lfib._internal_state.state.list[709]);
        EXPECT_EQ(0x61844a6d3de51ee8, lfib._internal_state.state.list[922]);
        EXPECT_EQ(0x386a84015d7bf286, lfib._internal_state.state.list[1135]);
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
