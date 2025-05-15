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

#include "lfib668.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsLFib668)
    {
        //-- tests empty constructor
        LFib668 lfib_1;

        EXPECT_EQ(607ULL, lfib_1._internal_state.state.list.size());
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
            LFib668 lfib(1);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x40d6824e2ef3fc17, lfib._internal_state.state.list[34]);
            EXPECT_EQ(0x0bf99fe6cbdde2d6, lfib._internal_state.state.list[135]);
            EXPECT_EQ(0x2d1d63dad4a646be, lfib._internal_state.state.list[236]);
            EXPECT_EQ(0xf021a06c3994c719, lfib._internal_state.state.list[337]);
            EXPECT_EQ(0xbc82fc84cf39a3d5, lfib._internal_state.state.list[438]);
            EXPECT_EQ(0x16f44cde26568725, lfib._internal_state.state.list[539]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x006c6675dd712147, 0xd2fdcf21b619c898, 0xd77796cc06953a70, 0x61e326fd27d79024, 0x0590efed9dc150bd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x91866d4d0cde66a9, lfib._internal_state.state.list[68]);
            EXPECT_EQ(0x100ba66a4ed81db5, lfib._internal_state.state.list[169]);
            EXPECT_EQ(0x7e8f9ffef47c203d, lfib._internal_state.state.list[270]);
            EXPECT_EQ(0x0c6ddaed661a61df, lfib._internal_state.state.list[371]);
            EXPECT_EQ(0xac384de3f4976fd5, lfib._internal_state.state.list[472]);
            EXPECT_EQ(0xdd394e82ec10c0cf, lfib._internal_state.state.list[573]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(-2);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x5575497b9a16aed3, lfib._internal_state.state.list[31]);
            EXPECT_EQ(0x85655d04487d0761, lfib._internal_state.state.list[132]);
            EXPECT_EQ(0xe09472b54f8e7fbb, lfib._internal_state.state.list[233]);
            EXPECT_EQ(0xaae39a74a86ffb0b, lfib._internal_state.state.list[334]);
            EXPECT_EQ(0xccea4a74623415b8, lfib._internal_state.state.list[435]);
            EXPECT_EQ(0xab9d474e0f54e203, lfib._internal_state.state.list[536]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9e03d904e264a32c, 0x8c4c3385d89f787d, 0xa0811c6751b00928, 0x4dfce1bea0754607, 0x96b7d34475759110 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xa40955b8aa5ccee6, lfib._internal_state.state.list[65]);
            EXPECT_EQ(0xe7fa3f41394de055, lfib._internal_state.state.list[166]);
            EXPECT_EQ(0x083fbf83eabf8585, lfib._internal_state.state.list[267]);
            EXPECT_EQ(0x6cc5bcbb983623e1, lfib._internal_state.state.list[368]);
            EXPECT_EQ(0xd8c03c4d3d53b2e1, lfib._internal_state.state.list[469]);
            EXPECT_EQ(0x5d0d77de87a4092b, lfib._internal_state.state.list[570]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(9);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x6ac4b2f18eeba85c, lfib._internal_state.state.list[42]);
            EXPECT_EQ(0x7ccc50e4b1f79123, lfib._internal_state.state.list[143]);
            EXPECT_EQ(0x66a0c0508889a61d, lfib._internal_state.state.list[244]);
            EXPECT_EQ(0xf6992984ee586f56, lfib._internal_state.state.list[345]);
            EXPECT_EQ(0x27c13f059712c432, lfib._internal_state.state.list[446]);
            EXPECT_EQ(0xb6744f0426beb60b, lfib._internal_state.state.list[547]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9c71ecd0616ba108, 0x4cc196ee2e594613, 0x9e40a7846671bbbb, 0x594544f3dafdd120, 0x0c5715bfe306f58d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xce8169d6d803d77f, lfib._internal_state.state.list[76]);
            EXPECT_EQ(0x790f4a317a6ced7d, lfib._internal_state.state.list[177]);
            EXPECT_EQ(0x7dc1a5a269ebfcfb, lfib._internal_state.state.list[278]);
            EXPECT_EQ(0x1a187e9f5257cca7, lfib._internal_state.state.list[379]);
            EXPECT_EQ(0x5e20debd1d288d07, lfib._internal_state.state.list[480]);
            EXPECT_EQ(0xa20b4927bd3acac7, lfib._internal_state.state.list[581]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(-11);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xd88e76c22399ab7c, lfib._internal_state.state.list[22]);
            EXPECT_EQ(0x8d2a339cd5c6d358, lfib._internal_state.state.list[123]);
            EXPECT_EQ(0x0d4e1cbb571c2820, lfib._internal_state.state.list[224]);
            EXPECT_EQ(0x27971a00d97fa2cb, lfib._internal_state.state.list[325]);
            EXPECT_EQ(0x3f81eb7583b006f8, lfib._internal_state.state.list[426]);
            EXPECT_EQ(0xa01c94fedf8cb216, lfib._internal_state.state.list[527]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb05ec62280fae756, 0xae995fc4934d7560, 0x8d41701a94c88f4e, 0xe7548db33899eb1e, 0x466d06a8fb768aa6 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x51d07cea2d6c2b81, lfib._internal_state.state.list[56]);
            EXPECT_EQ(0xe9c8d99a494c68ad, lfib._internal_state.state.list[157]);
            EXPECT_EQ(0x4fbc447aefa993a5, lfib._internal_state.state.list[258]);
            EXPECT_EQ(0x1853c26930da534a, lfib._internal_state.state.list[359]);
            EXPECT_EQ(0x59912b3de5cfc8cf, lfib._internal_state.state.list[460]);
            EXPECT_EQ(0x3ec029b098805d44, lfib._internal_state.state.list[561]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(17);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xcb6480055ef570a3, lfib._internal_state.state.list[50]);
            EXPECT_EQ(0x0a2b11f95c1cc30b, lfib._internal_state.state.list[151]);
            EXPECT_EQ(0x0652ba608d7c15eb, lfib._internal_state.state.list[252]);
            EXPECT_EQ(0x7bbc5165a4852c42, lfib._internal_state.state.list[353]);
            EXPECT_EQ(0x69627080f980d9d7, lfib._internal_state.state.list[454]);
            EXPECT_EQ(0xb589c88b419eaa76, lfib._internal_state.state.list[555]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xe0a0d9fdfe2dff34, 0xe5334b5ecef259f9, 0xd076f00b7159719c, 0x561235f56118f115, 0x7132094f47443152 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xc4dcc968366fc46d, lfib._internal_state.state.list[84]);
            EXPECT_EQ(0xae84f7050a807eb7, lfib._internal_state.state.list[185]);
            EXPECT_EQ(0x222b2edcfd029bda, lfib._internal_state.state.list[286]);
            EXPECT_EQ(0x2c11ed8c8d22f18f, lfib._internal_state.state.list[387]);
            EXPECT_EQ(0xc246cca1a73cf803, lfib._internal_state.state.list[488]);
            EXPECT_EQ(0x8d0ac166627b16c0, lfib._internal_state.state.list[589]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x01404ce914938008, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xe7cf4ae1ccc855ee, lfib._internal_state.state.list[105]);
            EXPECT_EQ(0xccf850c57a705cd6, lfib._internal_state.state.list[206]);
            EXPECT_EQ(0x3822f2eb098d4c15, lfib._internal_state.state.list[307]);
            EXPECT_EQ(0xb1147de017060044, lfib._internal_state.state.list[408]);
            EXPECT_EQ(0xd0171502d4408191, lfib._internal_state.state.list[509]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x66d94c71cf6c9734, 0x31e154b04f01d4a6, 0x9d1e21a3cf797025, 0x96b803c37236482b, 0x9b2e73147b19ff21 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xbfd57627fe350937, lfib._internal_state.state.list[38]);
            EXPECT_EQ(0x4e68e26636092c9a, lfib._internal_state.state.list[139]);
            EXPECT_EQ(0x443ca02ab33c4c1f, lfib._internal_state.state.list[240]);
            EXPECT_EQ(0x309546ff7bfd72fb, lfib._internal_state.state.list[341]);
            EXPECT_EQ(0xaab04d23fc88a152, lfib._internal_state.state.list[442]);
            EXPECT_EQ(0x0891f7d38d26c8fb, lfib._internal_state.state.list[543]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(-8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x0ae6185bdfe16a2b, lfib._internal_state.state.list[55]);
            EXPECT_EQ(0x906b0e9a2ebe39f4, lfib._internal_state.state.list[156]);
            EXPECT_EQ(0xa1f04b27bd2c2bc1, lfib._internal_state.state.list[257]);
            EXPECT_EQ(0xa19853dd7cfa899c, lfib._internal_state.state.list[358]);
            EXPECT_EQ(0x6ad5898368d6d393, lfib._internal_state.state.list[459]);
            EXPECT_EQ(0xc677f2594b231d78, lfib._internal_state.state.list[560]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf461fd9be99961c6, 0xb7fb9770078a0225, 0x5ed9c34b18922bf3, 0xa948724d266750ca, 0x933b688936faadfe };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x49bffd5ac3eb5994, lfib._internal_state.state.list[89]);
            EXPECT_EQ(0x36b3b4b19674dace, lfib._internal_state.state.list[190]);
            EXPECT_EQ(0x362f01f2eecd6d6d, lfib._internal_state.state.list[291]);
            EXPECT_EQ(0x380db856b58f4744, lfib._internal_state.state.list[392]);
            EXPECT_EQ(0x5557dba3d4ae920b, lfib._internal_state.state.list[493]);
            EXPECT_EQ(0xd69f20601e272a45, lfib._internal_state.state.list[594]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xff42f03c6e8cba89, lfib._internal_state.state.list[11]);
            EXPECT_EQ(0x836c808fba21e190, lfib._internal_state.state.list[112]);
            EXPECT_EQ(0xdba3cc01687a3ed9, lfib._internal_state.state.list[213]);
            EXPECT_EQ(0xb771fcfd28ab59fb, lfib._internal_state.state.list[314]);
            EXPECT_EQ(0x18996ed40fb43cc1, lfib._internal_state.state.list[415]);
            EXPECT_EQ(0xf734350d707383d9, lfib._internal_state.state.list[516]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x163536d69031f2d3, 0xd5c8b5833acdc5b1, 0x83ac03b31560a435, 0x94ee3075d2114729, 0x16dd1e0c906b498a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x77a4643cecbb7171, lfib._internal_state.state.list[45]);
            EXPECT_EQ(0xfceb2f8c77af806f, lfib._internal_state.state.list[146]);
            EXPECT_EQ(0x2b83b19038b56fd3, lfib._internal_state.state.list[247]);
            EXPECT_EQ(0xdddc2a4b0afd4f68, lfib._internal_state.state.list[348]);
            EXPECT_EQ(0xb2dbeb44766177f2, lfib._internal_state.state.list[449]);
            EXPECT_EQ(0xf476e1121e33615b, lfib._internal_state.state.list[550]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(0.357);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xd394e8454bdb01ba, lfib._internal_state.state.list[33]);
            EXPECT_EQ(0x5f2cb7df658e2b39, lfib._internal_state.state.list[134]);
            EXPECT_EQ(0x6dc81aab3925d369, lfib._internal_state.state.list[235]);
            EXPECT_EQ(0xa57b09f2d2d85743, lfib._internal_state.state.list[336]);
            EXPECT_EQ(0x5c330aad92d95d4c, lfib._internal_state.state.list[437]);
            EXPECT_EQ(0x842fc05b58add847, lfib._internal_state.state.list[538]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc9f4d246e1a58df0, 0x973c164d6b903fb9, 0x4f00504d1d381d87, 0x01651ae97159ce6e, 0x32f7ce671dc133cd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x64cec29126bed99c, lfib._internal_state.state.list[67]);
            EXPECT_EQ(0xe93c7669592d248f, lfib._internal_state.state.list[168]);
            EXPECT_EQ(0x6ae08b55bd0e171c, lfib._internal_state.state.list[269]);
            EXPECT_EQ(0xd5b2aa466d5bcb96, lfib._internal_state.state.list[370]);
            EXPECT_EQ(0xc05e9c027f7d0003, lfib._internal_state.state.list[471]);
            EXPECT_EQ(0x83b24e25c57f0d3a, lfib._internal_state.state.list[572]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib668 lfib(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xb83e988fc0cd7c45, lfib._internal_state.state.list[31]);
            EXPECT_EQ(0x165be770d0e2db3d, lfib._internal_state.state.list[132]);
            EXPECT_EQ(0x116482f314d44886, lfib._internal_state.state.list[233]);
            EXPECT_EQ(0x8136d7f63fddb8c1, lfib._internal_state.state.list[334]);
            EXPECT_EQ(0x0672cbd2265d70ff, lfib._internal_state.state.list[435]);
            EXPECT_EQ(0x07cc37398fdd730d, lfib._internal_state.state.list[536]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x7895dcc1f57f5a9e, 0x0ee619c6255c68f1, 0xcd5e5b0827f02256, 0x89e6b7efbfc25edd, 0xc4a27c350643a742 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x83591e27c5b8f825, lfib._internal_state.state.list[65]);
            EXPECT_EQ(0x95e6be6c946d8600, lfib._internal_state.state.list[166]);
            EXPECT_EQ(0x1e1aaff5488ee384, lfib._internal_state.state.list[267]);
            EXPECT_EQ(0x3404ab11c6f176d8, lfib._internal_state.state.list[368]);
            EXPECT_EQ(0xba090bad395d9c70, lfib._internal_state.state.list[469]);
            EXPECT_EQ(0xaf4a5e323cd715c5, lfib._internal_state.state.list[570]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }

        EXPECT_THROW(LFib668(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(LFib668(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            LFib668 lfib(lfib_1);

            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move constructor
        LFib668 lfib_0;

        {
            LFib668 lfib_mem(lfib_0);
            LFib668 lfib(std::move(lfib_mem));

            EXPECT_TRUE(lfib_0._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_0._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_0._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            LFib668 lfib;

            lfib = lfib_1;
            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move assignement
        LFib668 lfib;

        {
            LFib668 lfib_mem(lfib_0);
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
        EXPECT_EQ(0x69d22506dd4562e7, lfib._internal_state.state.list[32]);
        EXPECT_EQ(0x7fa431dd4dfc7bb8, lfib._internal_state.state.list[133]);
        EXPECT_EQ(0xb94eff7734f41bd0, lfib._internal_state.state.list[234]);
        EXPECT_EQ(0x84c5af9eae120642, lfib._internal_state.state.list[335]);
        EXPECT_EQ(0x22c70e16717c02f5, lfib._internal_state.state.list[436]);
        EXPECT_EQ(0x043a192f8c8ea0e4, lfib._internal_state.state.list[537]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(1);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x40d6824e2ef3fc17, lfib._internal_state.state.list[34]);
        EXPECT_EQ(0x0bf99fe6cbdde2d6, lfib._internal_state.state.list[135]);
        EXPECT_EQ(0x2d1d63dad4a646be, lfib._internal_state.state.list[236]);
        EXPECT_EQ(0xf021a06c3994c719, lfib._internal_state.state.list[337]);
        EXPECT_EQ(0xbc82fc84cf39a3d5, lfib._internal_state.state.list[438]);
        EXPECT_EQ(0x16f44cde26568725, lfib._internal_state.state.list[539]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-2);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x5575497b9a16aed3, lfib._internal_state.state.list[31]);
        EXPECT_EQ(0x85655d04487d0761, lfib._internal_state.state.list[132]);
        EXPECT_EQ(0xe09472b54f8e7fbb, lfib._internal_state.state.list[233]);
        EXPECT_EQ(0xaae39a74a86ffb0b, lfib._internal_state.state.list[334]);
        EXPECT_EQ(0xccea4a74623415b8, lfib._internal_state.state.list[435]);
        EXPECT_EQ(0xab9d474e0f54e203, lfib._internal_state.state.list[536]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(9L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x6ac4b2f18eeba85c, lfib._internal_state.state.list[42]);
        EXPECT_EQ(0x7ccc50e4b1f79123, lfib._internal_state.state.list[143]);
        EXPECT_EQ(0x66a0c0508889a61d, lfib._internal_state.state.list[244]);
        EXPECT_EQ(0xf6992984ee586f56, lfib._internal_state.state.list[345]);
        EXPECT_EQ(0x27c13f059712c432, lfib._internal_state.state.list[446]);
        EXPECT_EQ(0xb6744f0426beb60b, lfib._internal_state.state.list[547]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-11L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xd88e76c22399ab7c, lfib._internal_state.state.list[22]);
        EXPECT_EQ(0x8d2a339cd5c6d358, lfib._internal_state.state.list[123]);
        EXPECT_EQ(0x0d4e1cbb571c2820, lfib._internal_state.state.list[224]);
        EXPECT_EQ(0x27971a00d97fa2cb, lfib._internal_state.state.list[325]);
        EXPECT_EQ(0x3f81eb7583b006f8, lfib._internal_state.state.list[426]);
        EXPECT_EQ(0xa01c94fedf8cb216, lfib._internal_state.state.list[527]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(17UL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xcb6480055ef570a3, lfib._internal_state.state.list[50]);
        EXPECT_EQ(0x0a2b11f95c1cc30b, lfib._internal_state.state.list[151]);
        EXPECT_EQ(0x0652ba608d7c15eb, lfib._internal_state.state.list[252]);
        EXPECT_EQ(0x7bbc5165a4852c42, lfib._internal_state.state.list[353]);
        EXPECT_EQ(0x69627080f980d9d7, lfib._internal_state.state.list[454]);
        EXPECT_EQ(0xb589c88b419eaa76, lfib._internal_state.state.list[555]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x01404ce914938008, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0xe7cf4ae1ccc855ee, lfib._internal_state.state.list[105]);
        EXPECT_EQ(0xccf850c57a705cd6, lfib._internal_state.state.list[206]);
        EXPECT_EQ(0x3822f2eb098d4c15, lfib._internal_state.state.list[307]);
        EXPECT_EQ(0xb1147de017060044, lfib._internal_state.state.list[408]);
        EXPECT_EQ(0xd0171502d4408191, lfib._internal_state.state.list[509]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x0ae6185bdfe16a2b, lfib._internal_state.state.list[55]);
        EXPECT_EQ(0x906b0e9a2ebe39f4, lfib._internal_state.state.list[156]);
        EXPECT_EQ(0xa1f04b27bd2c2bc1, lfib._internal_state.state.list[257]);
        EXPECT_EQ(0xa19853dd7cfa899c, lfib._internal_state.state.list[358]);
        EXPECT_EQ(0x6ad5898368d6d393, lfib._internal_state.state.list[459]);
        EXPECT_EQ(0xc677f2594b231d78, lfib._internal_state.state.list[560]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xff42f03c6e8cba89, lfib._internal_state.state.list[11]);
        EXPECT_EQ(0x836c808fba21e190, lfib._internal_state.state.list[112]);
        EXPECT_EQ(0xdba3cc01687a3ed9, lfib._internal_state.state.list[213]);
        EXPECT_EQ(0xb771fcfd28ab59fb, lfib._internal_state.state.list[314]);
        EXPECT_EQ(0x18996ed40fb43cc1, lfib._internal_state.state.list[415]);
        EXPECT_EQ(0xf734350d707383d9, lfib._internal_state.state.list[516]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(0.357);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xd394e8454bdb01ba, lfib._internal_state.state.list[33]);
        EXPECT_EQ(0x5f2cb7df658e2b39, lfib._internal_state.state.list[134]);
        EXPECT_EQ(0x6dc81aab3925d369, lfib._internal_state.state.list[235]);
        EXPECT_EQ(0xa57b09f2d2d85743, lfib._internal_state.state.list[336]);
        EXPECT_EQ(0x5c330aad92d95d4c, lfib._internal_state.state.list[437]);
        EXPECT_EQ(0x842fc05b58add847, lfib._internal_state.state.list[538]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xb83e988fc0cd7c45, lfib._internal_state.state.list[31]);
        EXPECT_EQ(0x165be770d0e2db3d, lfib._internal_state.state.list[132]);
        EXPECT_EQ(0x116482f314d44886, lfib._internal_state.state.list[233]);
        EXPECT_EQ(0x8136d7f63fddb8c1, lfib._internal_state.state.list[334]);
        EXPECT_EQ(0x0672cbd2265d70ff, lfib._internal_state.state.list[435]);
        EXPECT_EQ(0x07cc37398fdd730d, lfib._internal_state.state.list[536]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        EXPECT_THROW(lfib.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(lfib.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        lfib._setstate(-1LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x69d22506dd4562e7, lfib._internal_state.state.list[32]);
        EXPECT_EQ(0x7fa431dd4dfc7bb8, lfib._internal_state.state.list[133]);
        EXPECT_EQ(0xb94eff7734f41bd0, lfib._internal_state.state.list[234]);
        EXPECT_EQ(0x84c5af9eae120642, lfib._internal_state.state.list[335]);
        EXPECT_EQ(0x22c70e16717c02f5, lfib._internal_state.state.list[436]);
        EXPECT_EQ(0x043a192f8c8ea0e4, lfib._internal_state.state.list[537]);
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
