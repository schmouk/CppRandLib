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

#include "well44497b.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsWell44497b)
    {
        //-- tests empty constructor
        Well44497b wll_1;

        EXPECT_EQ(1391ULL, wll_1._internal_state.state.list.size());
        EXPECT_EQ(0, wll_1._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                wll_1._internal_state.state.list.cbegin(),
                wll_1._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(wll_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Well44497b wll(1);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
            EXPECT_EQ(0xa13e727a, wll._internal_state.state.list[232]);
            EXPECT_EQ(0xc7fd0b60, wll._internal_state.state.list[463]);
            EXPECT_EQ(0x43bf1ac4, wll._internal_state.state.list[694]);
            EXPECT_EQ(0xb269cad1, wll._internal_state.state.list[925]);
            EXPECT_EQ(0xaac932c2, wll._internal_state.state.list[1156]);
            EXPECT_EQ(0x46f1f73f, wll._internal_state.state.list[1387]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x72be36cc, 0xab9f28e7, 0xcdce22d6, 0xe9402219, 0x24f24314 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0xfd0d1f90, wll._internal_state.state.list[116]);
            EXPECT_EQ(0xe7705a2e, wll._internal_state.state.list[347]);
            EXPECT_EQ(0x98532e3e, wll._internal_state.state.list[578]);
            EXPECT_EQ(0xa6c795d9, wll._internal_state.state.list[809]);
            EXPECT_EQ(0x4e9474f4, wll._internal_state.state.list[1040]);
            EXPECT_EQ(0xfa46daa5, wll._internal_state.state.list[1271]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(-2);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xe09472b5, wll._internal_state.state.list[233]);
            EXPECT_EQ(0x46038a1e, wll._internal_state.state.list[464]);
            EXPECT_EQ(0x79a6b61c, wll._internal_state.state.list[695]);
            EXPECT_EQ(0xe0bcd931, wll._internal_state.state.list[926]);
            EXPECT_EQ(0x995061d0, wll._internal_state.state.list[1157]);
            EXPECT_EQ(0x9e846e17, wll._internal_state.state.list[1388]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc535385d, 0x0615c209, 0xd02425c2, 0xcc7ce173, 0x77aaecf2 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x9418b065, wll._internal_state.state.list[117]);
            EXPECT_EQ(0x15db96ef, wll._internal_state.state.list[348]);
            EXPECT_EQ(0x073fa92c, wll._internal_state.state.list[579]);
            EXPECT_EQ(0x09b14666, wll._internal_state.state.list[810]);
            EXPECT_EQ(0x5015977d, wll._internal_state.state.list[1041]);
            EXPECT_EQ(0x719b899a, wll._internal_state.state.list[1272]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(9);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xca067431, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x17b17b42, wll._internal_state.state.list[240]);
            EXPECT_EQ(0x11ca595c, wll._internal_state.state.list[471]);
            EXPECT_EQ(0xff95bf5a, wll._internal_state.state.list[702]);
            EXPECT_EQ(0x3d4f0e12, wll._internal_state.state.list[933]);
            EXPECT_EQ(0x79cf4a30, wll._internal_state.state.list[1164]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x99fa275b, 0x2e989dae, 0x6938aad4, 0x2e9abb95, 0xac9a4f9f };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x997898e7, wll._internal_state.state.list[124]);
            EXPECT_EQ(0xe76e140b, wll._internal_state.state.list[355]);
            EXPECT_EQ(0xe4cbd1aa, wll._internal_state.state.list[586]);
            EXPECT_EQ(0xba8e9bc8, wll._internal_state.state.list[817]);
            EXPECT_EQ(0x9f8742fb, wll._internal_state.state.list[1048]);
            EXPECT_EQ(0xaa6dff8f, wll._internal_state.state.list[1279]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(-11);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x0d4e1cbb, wll._internal_state.state.list[224]);
            EXPECT_EQ(0xade04968, wll._internal_state.state.list[455]);
            EXPECT_EQ(0x8324acca, wll._internal_state.state.list[686]);
            EXPECT_EQ(0x3cec4914, wll._internal_state.state.list[917]);
            EXPECT_EQ(0xa9089af3, wll._internal_state.state.list[1148]);
            EXPECT_EQ(0x7aeadbc0, wll._internal_state.state.list[1379]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x0c074e37, 0xd4f8f876, 0x326a064d, 0x557c0f1e, 0xc9c4ef56 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x48fe8a2e, wll._internal_state.state.list[108]);
            EXPECT_EQ(0x0012cae1, wll._internal_state.state.list[339]);
            EXPECT_EQ(0x2de49ca9, wll._internal_state.state.list[570]);
            EXPECT_EQ(0x7fbcc420, wll._internal_state.state.list[801]);
            EXPECT_EQ(0x4d8b51a6, wll._internal_state.state.list[1032]);
            EXPECT_EQ(0xb72e74e0, wll._internal_state.state.list[1263]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(17);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x6cb7d6f5, wll._internal_state.state.list[17]);
            EXPECT_EQ(0x822f30a3, wll._internal_state.state.list[248]);
            EXPECT_EQ(0x152f94ef, wll._internal_state.state.list[479]);
            EXPECT_EQ(0x5ad10662, wll._internal_state.state.list[710]);
            EXPECT_EQ(0x21cc7d2e, wll._internal_state.state.list[941]);
            EXPECT_EQ(0xd13dbf88, wll._internal_state.state.list[1172]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x081f9f0e, 0xe4fd544f, 0x957b2916, 0x517f2924, 0x73462303 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x4b11e906, wll._internal_state.state.list[132]);
            EXPECT_EQ(0x4358d821, wll._internal_state.state.list[363]);
            EXPECT_EQ(0x76403255, wll._internal_state.state.list[594]);
            EXPECT_EQ(0x342c5668, wll._internal_state.state.list[825]);
            EXPECT_EQ(0x62093f82, wll._internal_state.state.list[1056]);
            EXPECT_EQ(0x24d6ebee, wll._internal_state.state.list[1287]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x9c889382, wll._internal_state.state.list[125]);
            EXPECT_EQ(0x253a378b, wll._internal_state.state.list[356]);
            EXPECT_EQ(0x690c72ab, wll._internal_state.state.list[587]);
            EXPECT_EQ(0x78f5d84f, wll._internal_state.state.list[818]);
            EXPECT_EQ(0x8375eb49, wll._internal_state.state.list[1049]);
            EXPECT_EQ(0x92e2ba8b, wll._internal_state.state.list[1280]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5cbd80e9, 0xe4d7c606, 0x514f30a3, 0x7379b30b, 0xf3549668 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x2680d065, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x443ca02a, wll._internal_state.state.list[240]);
            EXPECT_EQ(0xcda43b6a, wll._internal_state.state.list[471]);
            EXPECT_EQ(0x033dc469, wll._internal_state.state.list[702]);
            EXPECT_EQ(0x0a34b280, wll._internal_state.state.list[933]);
            EXPECT_EQ(0x0e1d2eaf, wll._internal_state.state.list[1164]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(-8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x1d0bb5d2, wll._internal_state.state.list[50]);
            EXPECT_EQ(0x073462d5, wll._internal_state.state.list[281]);
            EXPECT_EQ(0xa500600f, wll._internal_state.state.list[512]);
            EXPECT_EQ(0x0c57749a, wll._internal_state.state.list[743]);
            EXPECT_EQ(0xa039f6de, wll._internal_state.state.list[974]);
            EXPECT_EQ(0xb2f5bbaa, wll._internal_state.state.list[1205]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xdba327cf, 0x9b0dc424, 0xbfe33fa6, 0x3966028d, 0x23a3e470 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x89453124, wll._internal_state.state.list[165]);
            EXPECT_EQ(0xd665f8bb, wll._internal_state.state.list[396]);
            EXPECT_EQ(0xc87becf7, wll._internal_state.state.list[627]);
            EXPECT_EQ(0x2d9e90c5, wll._internal_state.state.list[858]);
            EXPECT_EQ(0x0e0eaa1f, wll._internal_state.state.list[1089]);
            EXPECT_EQ(0x02f156ff, wll._internal_state.state.list[1320]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x57dfb91b, wll._internal_state.state.list[185]);
            EXPECT_EQ(0x8bc453b4, wll._internal_state.state.list[416]);
            EXPECT_EQ(0x59c0a78e, wll._internal_state.state.list[647]);
            EXPECT_EQ(0x361926a3, wll._internal_state.state.list[878]);
            EXPECT_EQ(0xbb2b9865, wll._internal_state.state.list[1109]);
            EXPECT_EQ(0x150e567c, wll._internal_state.state.list[1340]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x150e5deb, 0x441565f1, 0xb4994dfe, 0x786b2a7d, 0xce0bff5b };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0xea371b89, wll._internal_state.state.list[69]);
            EXPECT_EQ(0xb058ef64, wll._internal_state.state.list[300]);
            EXPECT_EQ(0x4936be6a, wll._internal_state.state.list[531]);
            EXPECT_EQ(0x9055cb78, wll._internal_state.state.list[762]);
            EXPECT_EQ(0x2b3a8784, wll._internal_state.state.list[993]);
            EXPECT_EQ(0x883daf6d, wll._internal_state.state.list[1224]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(0.357);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
            EXPECT_EQ(0xa1c9c800, wll._internal_state.state.list[231]);
            EXPECT_EQ(0x9b8c5c6f, wll._internal_state.state.list[462]);
            EXPECT_EQ(0xf6d7870f, wll._internal_state.state.list[693]);
            EXPECT_EQ(0xb5682bb8, wll._internal_state.state.list[924]);
            EXPECT_EQ(0xeae78622, wll._internal_state.state.list[1155]);
            EXPECT_EQ(0xb47820d7, wll._internal_state.state.list[1386]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x70cad36d, 0x2a6be26c, 0xdffb16b7, 0xbba77a8f, 0xd2dfcd4b };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x49bcbe08, wll._internal_state.state.list[115]);
            EXPECT_EQ(0x639cdefb, wll._internal_state.state.list[346]);
            EXPECT_EQ(0x10be683a, wll._internal_state.state.list[577]);
            EXPECT_EQ(0x2e161cb6, wll._internal_state.state.list[808]);
            EXPECT_EQ(0xd8c81f6a, wll._internal_state.state.list[1039]);
            EXPECT_EQ(0xc465a549, wll._internal_state.state.list[1270]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well44497b wll(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x33f37c98, wll._internal_state.state.list[127]);
            EXPECT_EQ(0xd9760a2a, wll._internal_state.state.list[358]);
            EXPECT_EQ(0x2774c2e3, wll._internal_state.state.list[589]);
            EXPECT_EQ(0x3827beea, wll._internal_state.state.list[820]);
            EXPECT_EQ(0xb9dcad84, wll._internal_state.state.list[1051]);
            EXPECT_EQ(0x986d6ae2, wll._internal_state.state.list[1282]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x7f144435, 0xf01eafe7, 0x284139cf, 0xb2323263, 0xf82bf5c5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(1386, wll._internal_state.state.index);
            EXPECT_EQ(0x8808168a, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x01ae36f4, wll._internal_state.state.list[242]);
            EXPECT_EQ(0x53fdca97, wll._internal_state.state.list[473]);
            EXPECT_EQ(0xf497fce3, wll._internal_state.state.list[704]);
            EXPECT_EQ(0x55d0fc02, wll._internal_state.state.list[935]);
            EXPECT_EQ(0x2a58d706, wll._internal_state.state.list[1166]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }

        EXPECT_THROW(Well44497b(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Well44497b(1.0001), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Well44497b wll(wll_1);

            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Well44497b wll_0;

        {
            Well44497b wll_mem(wll_0);
            Well44497b wll(std::move(wll_mem));

            EXPECT_TRUE(wll_0._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_0._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_0._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Well44497b wll;

            wll = wll_1;
            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Well44497b wll;

        {
            Well44497b wll_mem(wll_0);
            wll = std::move(wll_mem);

            EXPECT_TRUE(wll_0._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_0._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_0._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests seed()
        wll.seed();
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                wll._internal_state.state.list.cbegin(),
                wll._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);


        //-- tests seed(value)
        wll.seed(-1);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xb94eff77, wll._internal_state.state.list[234]);
        EXPECT_EQ(0xa7fbc19c, wll._internal_state.state.list[465]);
        EXPECT_EQ(0x44ca43ee, wll._internal_state.state.list[696]);
        EXPECT_EQ(0x47de975f, wll._internal_state.state.list[927]);
        EXPECT_EQ(0x971818bf, wll._internal_state.state.list[1158]);
        EXPECT_EQ(0xdd6c2f66, wll._internal_state.state.list[1389]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0x79987e97, 0x0c131dd5, 0x0b0d501a, 0xac0acb74, 0x5b82525f };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, wll.next());
        EXPECT_EQ(1386, wll._internal_state.state.index);
        EXPECT_EQ(0x7cfc5b90, wll._internal_state.state.list[118]);
        EXPECT_EQ(0xe2d07a9b, wll._internal_state.state.list[349]);
        EXPECT_EQ(0x8244ce97, wll._internal_state.state.list[580]);
        EXPECT_EQ(0xd1e38a7d, wll._internal_state.state.list[811]);
        EXPECT_EQ(0xf1c8dbdc, wll._internal_state.state.list[1042]);
        EXPECT_EQ(0x1eddd06e, wll._internal_state.state.list[1273]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(1);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
        EXPECT_EQ(0xa13e727a, wll._internal_state.state.list[232]);
        EXPECT_EQ(0xc7fd0b60, wll._internal_state.state.list[463]);
        EXPECT_EQ(0x43bf1ac4, wll._internal_state.state.list[694]);
        EXPECT_EQ(0xb269cad1, wll._internal_state.state.list[925]);
        EXPECT_EQ(0xaac932c2, wll._internal_state.state.list[1156]);
        EXPECT_EQ(0x46f1f73f, wll._internal_state.state.list[1387]);

        wll.seed(-2);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xe09472b5, wll._internal_state.state.list[233]);
        EXPECT_EQ(0x46038a1e, wll._internal_state.state.list[464]);
        EXPECT_EQ(0x79a6b61c, wll._internal_state.state.list[695]);
        EXPECT_EQ(0xe0bcd931, wll._internal_state.state.list[926]);
        EXPECT_EQ(0x995061d0, wll._internal_state.state.list[1157]);
        EXPECT_EQ(0x9e846e17, wll._internal_state.state.list[1388]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(9L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xca067431, wll._internal_state.state.list[9]);
        EXPECT_EQ(0x17b17b42, wll._internal_state.state.list[240]);
        EXPECT_EQ(0x11ca595c, wll._internal_state.state.list[471]);
        EXPECT_EQ(0xff95bf5a, wll._internal_state.state.list[702]);
        EXPECT_EQ(0x3d4f0e12, wll._internal_state.state.list[933]);
        EXPECT_EQ(0x79cf4a30, wll._internal_state.state.list[1164]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-11L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x0d4e1cbb, wll._internal_state.state.list[224]);
        EXPECT_EQ(0xade04968, wll._internal_state.state.list[455]);
        EXPECT_EQ(0x8324acca, wll._internal_state.state.list[686]);
        EXPECT_EQ(0x3cec4914, wll._internal_state.state.list[917]);
        EXPECT_EQ(0xa9089af3, wll._internal_state.state.list[1148]);
        EXPECT_EQ(0x7aeadbc0, wll._internal_state.state.list[1379]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(17UL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x6cb7d6f5, wll._internal_state.state.list[17]);
        EXPECT_EQ(0x822f30a3, wll._internal_state.state.list[248]);
        EXPECT_EQ(0x152f94ef, wll._internal_state.state.list[479]);
        EXPECT_EQ(0x5ad10662, wll._internal_state.state.list[710]);
        EXPECT_EQ(0x21cc7d2e, wll._internal_state.state.list[941]);
        EXPECT_EQ(0xd13dbf88, wll._internal_state.state.list[1172]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x9c889382, wll._internal_state.state.list[125]);
        EXPECT_EQ(0x253a378b, wll._internal_state.state.list[356]);
        EXPECT_EQ(0x690c72ab, wll._internal_state.state.list[587]);
        EXPECT_EQ(0x78f5d84f, wll._internal_state.state.list[818]);
        EXPECT_EQ(0x8375eb49, wll._internal_state.state.list[1049]);
        EXPECT_EQ(0x92e2ba8b, wll._internal_state.state.list[1280]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x1d0bb5d2, wll._internal_state.state.list[50]);
        EXPECT_EQ(0x073462d5, wll._internal_state.state.list[281]);
        EXPECT_EQ(0xa500600f, wll._internal_state.state.list[512]);
        EXPECT_EQ(0x0c57749a, wll._internal_state.state.list[743]);
        EXPECT_EQ(0xa039f6de, wll._internal_state.state.list[974]);
        EXPECT_EQ(0xb2f5bbaa, wll._internal_state.state.list[1205]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x57dfb91b, wll._internal_state.state.list[185]);
        EXPECT_EQ(0x8bc453b4, wll._internal_state.state.list[416]);
        EXPECT_EQ(0x59c0a78e, wll._internal_state.state.list[647]);
        EXPECT_EQ(0x361926a3, wll._internal_state.state.list[878]);
        EXPECT_EQ(0xbb2b9865, wll._internal_state.state.list[1109]);
        EXPECT_EQ(0x150e567c, wll._internal_state.state.list[1340]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0.357);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
        EXPECT_EQ(0xa1c9c800, wll._internal_state.state.list[231]);
        EXPECT_EQ(0x9b8c5c6f, wll._internal_state.state.list[462]);
        EXPECT_EQ(0xf6d7870f, wll._internal_state.state.list[693]);
        EXPECT_EQ(0xb5682bb8, wll._internal_state.state.list[924]);
        EXPECT_EQ(0xeae78622, wll._internal_state.state.list[1155]);
        EXPECT_EQ(0xb47820d7, wll._internal_state.state.list[1386]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x33f37c98, wll._internal_state.state.list[127]);
        EXPECT_EQ(0xd9760a2a, wll._internal_state.state.list[358]);
        EXPECT_EQ(0x2774c2e3, wll._internal_state.state.list[589]);
        EXPECT_EQ(0x3827beea, wll._internal_state.state.list[820]);
        EXPECT_EQ(0xb9dcad84, wll._internal_state.state.list[1051]);
        EXPECT_EQ(0x986d6ae2, wll._internal_state.state.list[1282]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        EXPECT_THROW(wll.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(wll.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        wll._setstate(-1LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xb94eff77, wll._internal_state.state.list[234]);
        EXPECT_EQ(0xa7fbc19c, wll._internal_state.state.list[465]);
        EXPECT_EQ(0x44ca43ee, wll._internal_state.state.list[696]);
        EXPECT_EQ(0x47de975f, wll._internal_state.state.list[927]);
        EXPECT_EQ(0x971818bf, wll._internal_state.state.list[1158]);
        EXPECT_EQ(0xdd6c2f66, wll._internal_state.state.list[1389]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x33f37c98, wll._internal_state.state.list[127]);
        EXPECT_EQ(0xd9760a2a, wll._internal_state.state.list[358]);
        EXPECT_EQ(0x2774c2e3, wll._internal_state.state.list[589]);
        EXPECT_EQ(0x3827beea, wll._internal_state.state.list[820]);
        EXPECT_EQ(0xb9dcad84, wll._internal_state.state.list[1051]);
        EXPECT_EQ(0x986d6ae2, wll._internal_state.state.list[1282]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        wll.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 60) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)wll(ENTRIES_COUNT)]++;
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
