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

#include "pcg1024_32.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsPcg1024_32)
    {
        //-- tests empty constructor
        Pcg1024_32 pcg_1;

        EXPECT_EQ(1024ULL, pcg_1._internal_state.state.extended_state.size());
        EXPECT_NE(0, pcg_1._internal_state.state.state._internal_state.state);  // notice: should not be zero while it could (1 over 2^64)
        EXPECT_TRUE(
            std::any_of(
                pcg_1._internal_state.state.extended_state.cbegin(),
                pcg_1._internal_state.state.extended_state.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(pcg_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Pcg1024_32 pcg(1);

            EXPECT_EQ(0x00000001, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xbeeb8da1, pcg._internal_state.state.extended_state[1]);
            EXPECT_EQ(0x6c5cc4ca, pcg._internal_state.state.extended_state[171]);
            EXPECT_EQ(0x299c7163, pcg._internal_state.state.extended_state[341]);
            EXPECT_EQ(0x619b42a2, pcg._internal_state.state.extended_state[511]);
            EXPECT_EQ(0x30119338, pcg._internal_state.state.extended_state[681]);
            EXPECT_EQ(0x06d5c6fe, pcg._internal_state.state.extended_state[851]);
            EXPECT_EQ(0xa4bcae83, pcg._internal_state.state.extended_state[1021]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x910a2dec, 0x1364cbc7, 0xec5f61c7, 0x82a5b817, 0x28cc1c10 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0xcba276b4b881a9f0, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xc0257e40, pcg._internal_state.state.extended_state[86]);
            EXPECT_EQ(0x5c9a9246, pcg._internal_state.state.extended_state[256]);
            EXPECT_EQ(0xaf6c066f, pcg._internal_state.state.extended_state[426]);
            EXPECT_EQ(0x9eb33113, pcg._internal_state.state.extended_state[596]);
            EXPECT_EQ(0x09736869, pcg._internal_state.state.extended_state[766]);
            EXPECT_EQ(0x32d5d9e3, pcg._internal_state.state.extended_state[936]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(-2);

            EXPECT_EQ(0xfffffffffffffffe, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xd0d5127a, pcg._internal_state.state.extended_state[2]);
            EXPECT_EQ(0x107b5555, pcg._internal_state.state.extended_state[172]);
            EXPECT_EQ(0x50553132, pcg._internal_state.state.extended_state[342]);
            EXPECT_EQ(0xaf98cf4a, pcg._internal_state.state.extended_state[512]);
            EXPECT_EQ(0x6f84b49b, pcg._internal_state.state.extended_state[682]);
            EXPECT_EQ(0x38fd4a1f, pcg._internal_state.state.extended_state[852]);
            EXPECT_EQ(0xaee1bb4c, pcg._internal_state.state.extended_state[1022]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x567368d, 0x4b1ab02, 0x4c8abf2a, 0x42c79439, 0xf19624b2 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x8f5af925b57121f9, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xebf0b493, pcg._internal_state.state.extended_state[87]);
            EXPECT_EQ(0xcc9821e9, pcg._internal_state.state.extended_state[257]);
            EXPECT_EQ(0xb95e3def, pcg._internal_state.state.extended_state[427]);
            EXPECT_EQ(0xd466cbf6, pcg._internal_state.state.extended_state[597]);
            EXPECT_EQ(0xcb39f12f, pcg._internal_state.state.extended_state[767]);
            EXPECT_EQ(0x5c4ba1ec, pcg._internal_state.state.extended_state[937]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(9);

            EXPECT_EQ(0x00000009, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xc02d8a5e, pcg._internal_state.state.extended_state[1]);
            EXPECT_EQ(0x60fc7b79, pcg._internal_state.state.extended_state[171]);
            EXPECT_EQ(0xee0f8883, pcg._internal_state.state.extended_state[341]);
            EXPECT_EQ(0x68b37d2f, pcg._internal_state.state.extended_state[511]);
            EXPECT_EQ(0x0798b004, pcg._internal_state.state.extended_state[681]);
            EXPECT_EQ(0xdf3232b3, pcg._internal_state.state.extended_state[851]);
            EXPECT_EQ(0x5a74f55c, pcg._internal_state.state.extended_state[1021]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xaeaf52fe, 0x1d8cedec, 0x87a87820, 0x8f067248, 0xdf69f1a5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x170bc5876b5869d8, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xae6ca3d1, pcg._internal_state.state.extended_state[86]);
            EXPECT_EQ(0xbff5b913, pcg._internal_state.state.extended_state[256]);
            EXPECT_EQ(0x5690ef2e, pcg._internal_state.state.extended_state[426]);
            EXPECT_EQ(0xb3cba043, pcg._internal_state.state.extended_state[596]);
            EXPECT_EQ(0x4288157d, pcg._internal_state.state.extended_state[766]);
            EXPECT_EQ(0xf1c42c46, pcg._internal_state.state.extended_state[936]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(-11);

            EXPECT_EQ(0xfffffffffffffff5, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x96caee61, pcg._internal_state.state.extended_state[1]);
            EXPECT_EQ(0x16d8d34b, pcg._internal_state.state.extended_state[171]);
            EXPECT_EQ(0x032704ba, pcg._internal_state.state.extended_state[341]);
            EXPECT_EQ(0x7ce268ac, pcg._internal_state.state.extended_state[511]);
            EXPECT_EQ(0x82b8149e, pcg._internal_state.state.extended_state[681]);
            EXPECT_EQ(0x41fea804, pcg._internal_state.state.extended_state[851]);
            EXPECT_EQ(0xf8ef347c, pcg._internal_state.state.extended_state[1021]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb439ee8f, 0xc660f366, 0x8215ee59, 0x52e4b080, 0xe79a29e };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0xda848078ac3f8a14, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x057d70dc, pcg._internal_state.state.extended_state[86]);
            EXPECT_EQ(0x72ba1e6b, pcg._internal_state.state.extended_state[256]);
            EXPECT_EQ(0x3f81eb75, pcg._internal_state.state.extended_state[426]);
            EXPECT_EQ(0xa60b8680, pcg._internal_state.state.extended_state[596]);
            EXPECT_EQ(0x36aa45ab, pcg._internal_state.state.extended_state[766]);
            EXPECT_EQ(0x6471881c, pcg._internal_state.state.extended_state[936]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(17);

            EXPECT_EQ(0x00000011, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x6434ff62, pcg._internal_state.state.extended_state[1]);
            EXPECT_EQ(0x911227ec, pcg._internal_state.state.extended_state[171]);
            EXPECT_EQ(0xd13ba9d7, pcg._internal_state.state.extended_state[341]);
            EXPECT_EQ(0x8127480b, pcg._internal_state.state.extended_state[511]);
            EXPECT_EQ(0x3b64271c, pcg._internal_state.state.extended_state[681]);
            EXPECT_EQ(0xba697831, pcg._internal_state.state.extended_state[851]);
            EXPECT_EQ(0x1525ec1e, pcg._internal_state.state.extended_state[1021]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x808475f0, 0xc990e87f, 0xc096f410, 0xe11e036a, 0x96edc8d8 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x6275145a1e2f29c0, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xd1230010, pcg._internal_state.state.extended_state[86]);
            EXPECT_EQ(0x0b88b660, pcg._internal_state.state.extended_state[256]);
            EXPECT_EQ(0xad754037, pcg._internal_state.state.extended_state[426]);
            EXPECT_EQ(0x23f0d195, pcg._internal_state.state.extended_state[596]);
            EXPECT_EQ(0x1f968eaa, pcg._internal_state.state.extended_state[766]);
            EXPECT_EQ(0x57602905, pcg._internal_state.state.extended_state[936]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0x123456789abcdef, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xa2d41933, pcg._internal_state.state.extended_state[3]);
            EXPECT_EQ(0x3ac4288a, pcg._internal_state.state.extended_state[173]);
            EXPECT_EQ(0x5fabd717, pcg._internal_state.state.extended_state[343]);
            EXPECT_EQ(0xbab3def7, pcg._internal_state.state.extended_state[513]);
            EXPECT_EQ(0xb6665fdc, pcg._internal_state.state.extended_state[683]);
            EXPECT_EQ(0x407040cf, pcg._internal_state.state.extended_state[853]);
            EXPECT_EQ(0x1a8aec91, pcg._internal_state.state.extended_state[1023]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x57207a74, 0x77abc3ae, 0xafe24cef, 0xbac4f59f, 0x5b7e3bd4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0xc60c9ae76aeb1026, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x6f42e684, pcg._internal_state.state.extended_state[88]);
            EXPECT_EQ(0xce160356, pcg._internal_state.state.extended_state[258]);
            EXPECT_EQ(0x055754b9, pcg._internal_state.state.extended_state[428]);
            EXPECT_EQ(0xc4ecf79a, pcg._internal_state.state.extended_state[598]);
            EXPECT_EQ(0xe7c3ca1e, pcg._internal_state.state.extended_state[768]);
            EXPECT_EQ(0xfe7f5216, pcg._internal_state.state.extended_state[938]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(-8870000000000000000);

            EXPECT_EQ(0x84e76dfeca490000, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x48bbc5b8, pcg._internal_state.state.extended_state[0]);
            EXPECT_EQ(0xfb57d0fb, pcg._internal_state.state.extended_state[170]);
            EXPECT_EQ(0x5306c566, pcg._internal_state.state.extended_state[340]);
            EXPECT_EQ(0x99371619, pcg._internal_state.state.extended_state[510]);
            EXPECT_EQ(0x4820d8be, pcg._internal_state.state.extended_state[680]);
            EXPECT_EQ(0x80274781, pcg._internal_state.state.extended_state[850]);
            EXPECT_EQ(0xa69891d2, pcg._internal_state.state.extended_state[1020]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x443e55db, 0xbb4d2c09, 0x26c3c3a9, 0xe3f660fa, 0xc2f33fc8 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x4effa1359b4bd1f3, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xf2a41f9c, pcg._internal_state.state.extended_state[85]);
            EXPECT_EQ(0x76b51bac, pcg._internal_state.state.extended_state[255]);
            EXPECT_EQ(0x77072958, pcg._internal_state.state.extended_state[425]);
            EXPECT_EQ(0x5d2497e0, pcg._internal_state.state.extended_state[595]);
            EXPECT_EQ(0xa9d85ea2, pcg._internal_state.state.extended_state[765]);
            EXPECT_EQ(0x871b272d, pcg._internal_state.state.extended_state[935]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(8870000000000000000);

            EXPECT_EQ(0x7b18920135b70000, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xeede014d, pcg._internal_state.state.extended_state[0]);
            EXPECT_EQ(0xaf64f516, pcg._internal_state.state.extended_state[170]);
            EXPECT_EQ(0xe53c8982, pcg._internal_state.state.extended_state[340]);
            EXPECT_EQ(0xd27c5157, pcg._internal_state.state.extended_state[510]);
            EXPECT_EQ(0x48ede633, pcg._internal_state.state.extended_state[680]);
            EXPECT_EQ(0x19078a53, pcg._internal_state.state.extended_state[850]);
            EXPECT_EQ(0x138889f7, pcg._internal_state.state.extended_state[1020]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xabb96f67, 0x470ed664, 0xb911a476, 0x3ecfed68, 0x83a8878d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x756af87f2901d1f3, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x6f068ac8, pcg._internal_state.state.extended_state[85]);
            EXPECT_EQ(0x10c08f19, pcg._internal_state.state.extended_state[255]);
            EXPECT_EQ(0xa6b174ab, pcg._internal_state.state.extended_state[425]);
            EXPECT_EQ(0x62aa592a, pcg._internal_state.state.extended_state[595]);
            EXPECT_EQ(0x1eaffb52, pcg._internal_state.state.extended_state[765]);
            EXPECT_EQ(0x813d72c8, pcg._internal_state.state.extended_state[935]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(0.357);

            EXPECT_EQ(0x5b645a1cac083000, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x5fee464f, pcg._internal_state.state.extended_state[0]);
            EXPECT_EQ(0x2084fa3f, pcg._internal_state.state.extended_state[170]);
            EXPECT_EQ(0x489eef92, pcg._internal_state.state.extended_state[340]);
            EXPECT_EQ(0xd233535b, pcg._internal_state.state.extended_state[510]);
            EXPECT_EQ(0x6f6dd894, pcg._internal_state.state.extended_state[680]);
            EXPECT_EQ(0x515faa34, pcg._internal_state.state.extended_state[850]);
            EXPECT_EQ(0xff1a726d, pcg._internal_state.state.extended_state[1020]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x313a03cd, 0x19e0b3e7, 0xebea2f9b, 0x26de931e, 0x77638b76 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x8a988aac268e41f3, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0x807d0f89, pcg._internal_state.state.extended_state[85]);
            EXPECT_EQ(0xff3597be, pcg._internal_state.state.extended_state[255]);
            EXPECT_EQ(0xf9d265c1, pcg._internal_state.state.extended_state[425]);
            EXPECT_EQ(0x7dae7949, pcg._internal_state.state.extended_state[595]);
            EXPECT_EQ(0x2c5eeeeb, pcg._internal_state.state.extended_state[765]);
            EXPECT_EQ(0x0ce454f8, pcg._internal_state.state.extended_state[935]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }
        {
            Pcg1024_32 pcg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0xfffffffffffffffd, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xec779c36, pcg._internal_state.state.extended_state[1]);
            EXPECT_EQ(0x0ae1d8ad, pcg._internal_state.state.extended_state[171]);
            EXPECT_EQ(0x9e0740e7, pcg._internal_state.state.extended_state[341]);
            EXPECT_EQ(0x5d88abb1, pcg._internal_state.state.extended_state[511]);
            EXPECT_EQ(0x32e7dd3a, pcg._internal_state.state.extended_state[681]);
            EXPECT_EQ(0x0eadef97, pcg._internal_state.state.extended_state[851]);
            EXPECT_EQ(0x86e22c5c, pcg._internal_state.state.extended_state[1021]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc18a3c14, 0xc6fd545f, 0x583af8aa, 0x99fcc31, 0x1dcdfe50 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, pcg.next());

            EXPECT_EQ(0x25edcf4b5f1649fc, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(0xca59a978, pcg._internal_state.state.extended_state[86]);
            EXPECT_EQ(0x464333e4, pcg._internal_state.state.extended_state[256]);
            EXPECT_EQ(0xcaf1f382, pcg._internal_state.state.extended_state[426]);
            EXPECT_EQ(0x5d9f047d, pcg._internal_state.state.extended_state[596]);
            EXPECT_EQ(0xa130e070, pcg._internal_state.state.extended_state[766]);
            EXPECT_EQ(0x0e0bf2d6, pcg._internal_state.state.extended_state[936]);
            EXPECT_FALSE(pcg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);
        }

        EXPECT_THROW(Pcg1024_32(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Pcg1024_32(1.0001), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Pcg1024_32 pcg(pcg_1);

            EXPECT_TRUE(pcg_1._internal_state.state.extended_state == pcg._internal_state.state.extended_state);
            EXPECT_TRUE(pcg_1._internal_state.state.state._internal_state.state == pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(pcg_1._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_1._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Pcg1024_32 pcg_0;

        {
            Pcg1024_32 pcg_mem(pcg_0);
            Pcg1024_32 pcg(std::move(pcg_mem));

            EXPECT_TRUE(pcg_0._internal_state.state.extended_state == pcg._internal_state.state.extended_state);
            EXPECT_TRUE(pcg_0._internal_state.state.state._internal_state.state == pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(pcg_0._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_0._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Pcg1024_32 pcg;

            pcg = pcg_1;
            EXPECT_TRUE(pcg_1._internal_state.state.extended_state == pcg._internal_state.state.extended_state);
            EXPECT_TRUE(pcg_1._internal_state.state.state._internal_state.state == pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(pcg_1._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_1._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Pcg1024_32 pcg;

        {
            Pcg1024_32 pcg_mem(pcg_0);
            pcg = std::move(pcg_mem);

            EXPECT_TRUE(pcg_0._internal_state.state.extended_state == pcg._internal_state.state.extended_state);
            EXPECT_TRUE(pcg_0._internal_state.state.state._internal_state.state == pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
            EXPECT_EQ(pcg_0._internal_state.gauss_next, pcg._internal_state.gauss_next);
            EXPECT_EQ(pcg_0._internal_state.gauss_valid, pcg._internal_state.gauss_valid);
        }


        //-- tests seed()
        pcg.seed();
        EXPECT_NE(0, pcg._internal_state.state.state._internal_state.state);  // notice: should not be zero, while it could (1 over 2^64)
        EXPECT_TRUE(
            std::any_of(
                pcg._internal_state.state.extended_state.cbegin(),
                pcg._internal_state.state.extended_state.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);


        //-- tests seed(value)
        pcg.seed(-1);
        EXPECT_EQ(0xffffffffffffffff, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0x6d1db36c, pcg._internal_state.state.extended_state[3]);
        EXPECT_EQ(0xd5dcb771, pcg._internal_state.state.extended_state[173]);
        EXPECT_EQ(0x634141d4, pcg._internal_state.state.extended_state[343]);
        EXPECT_EQ(0x521e36db, pcg._internal_state.state.extended_state[513]);
        EXPECT_EQ(0xe737509e, pcg._internal_state.state.extended_state[683]);
        EXPECT_EQ(0xe524096b, pcg._internal_state.state.extended_state[853]);
        EXPECT_EQ(0x7fe7d678, pcg._internal_state.state.extended_state[1023]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(1);
        EXPECT_EQ(0x00000001, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0xbeeb8da1, pcg._internal_state.state.extended_state[1]);
        EXPECT_EQ(0x6c5cc4ca, pcg._internal_state.state.extended_state[171]);
        EXPECT_EQ(0x299c7163, pcg._internal_state.state.extended_state[341]);
        EXPECT_EQ(0x619b42a2, pcg._internal_state.state.extended_state[511]);
        EXPECT_EQ(0x30119338, pcg._internal_state.state.extended_state[681]);
        EXPECT_EQ(0x06d5c6fe, pcg._internal_state.state.extended_state[851]);
        EXPECT_EQ(0xa4bcae83, pcg._internal_state.state.extended_state[1021]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-2);
        EXPECT_EQ(0xfffffffffffffffe, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0xd0d5127a, pcg._internal_state.state.extended_state[2]);
        EXPECT_EQ(0x107b5555, pcg._internal_state.state.extended_state[172]);
        EXPECT_EQ(0x50553132, pcg._internal_state.state.extended_state[342]);
        EXPECT_EQ(0xaf98cf4a, pcg._internal_state.state.extended_state[512]);
        EXPECT_EQ(0x6f84b49b, pcg._internal_state.state.extended_state[682]);
        EXPECT_EQ(0x38fd4a1f, pcg._internal_state.state.extended_state[852]);
        EXPECT_EQ(0xaee1bb4c, pcg._internal_state.state.extended_state[1022]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(9L);
        EXPECT_EQ(0x00000009, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0xc02d8a5e, pcg._internal_state.state.extended_state[1]);
        EXPECT_EQ(0x60fc7b79, pcg._internal_state.state.extended_state[171]);
        EXPECT_EQ(0xee0f8883, pcg._internal_state.state.extended_state[341]);
        EXPECT_EQ(0x68b37d2f, pcg._internal_state.state.extended_state[511]);
        EXPECT_EQ(0x0798b004, pcg._internal_state.state.extended_state[681]);
        EXPECT_EQ(0xdf3232b3, pcg._internal_state.state.extended_state[851]);
        EXPECT_EQ(0x5a74f55c, pcg._internal_state.state.extended_state[1021]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-11L);
        EXPECT_EQ(0xfffffffffffffff5, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0x96caee61, pcg._internal_state.state.extended_state[1]);
        EXPECT_EQ(0x16d8d34b, pcg._internal_state.state.extended_state[171]);
        EXPECT_EQ(0x032704ba, pcg._internal_state.state.extended_state[341]);
        EXPECT_EQ(0x7ce268ac, pcg._internal_state.state.extended_state[511]);
        EXPECT_EQ(0x82b8149e, pcg._internal_state.state.extended_state[681]);
        EXPECT_EQ(0x41fea804, pcg._internal_state.state.extended_state[851]);
        EXPECT_EQ(0xf8ef347c, pcg._internal_state.state.extended_state[1021]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(17UL);
        EXPECT_EQ(0x00000011, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0x6434ff62, pcg._internal_state.state.extended_state[1]);
        EXPECT_EQ(0x911227ec, pcg._internal_state.state.extended_state[171]);
        EXPECT_EQ(0xd13ba9d7, pcg._internal_state.state.extended_state[341]);
        EXPECT_EQ(0x8127480b, pcg._internal_state.state.extended_state[511]);
        EXPECT_EQ(0x3b64271c, pcg._internal_state.state.extended_state[681]);
        EXPECT_EQ(0xba697831, pcg._internal_state.state.extended_state[851]);
        EXPECT_EQ(0x1525ec1e, pcg._internal_state.state.extended_state[1021]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x123456789abcdef, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0xa2d41933, pcg._internal_state.state.extended_state[3]);
        EXPECT_EQ(0x3ac4288a, pcg._internal_state.state.extended_state[173]);
        EXPECT_EQ(0x5fabd717, pcg._internal_state.state.extended_state[343]);
        EXPECT_EQ(0xbab3def7, pcg._internal_state.state.extended_state[513]);
        EXPECT_EQ(0xb6665fdc, pcg._internal_state.state.extended_state[683]);
        EXPECT_EQ(0x407040cf, pcg._internal_state.state.extended_state[853]);
        EXPECT_EQ(0x1a8aec91, pcg._internal_state.state.extended_state[1023]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x84e76dfeca490000, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0x48bbc5b8, pcg._internal_state.state.extended_state[0]);
        EXPECT_EQ(0xfb57d0fb, pcg._internal_state.state.extended_state[170]);
        EXPECT_EQ(0x5306c566, pcg._internal_state.state.extended_state[340]);
        EXPECT_EQ(0x99371619, pcg._internal_state.state.extended_state[510]);
        EXPECT_EQ(0x4820d8be, pcg._internal_state.state.extended_state[680]);
        EXPECT_EQ(0x80274781, pcg._internal_state.state.extended_state[850]);
        EXPECT_EQ(0xa69891d2, pcg._internal_state.state.extended_state[1020]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x7b18920135b70000, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0xeede014d, pcg._internal_state.state.extended_state[0]);
        EXPECT_EQ(0xaf64f516, pcg._internal_state.state.extended_state[170]);
        EXPECT_EQ(0xe53c8982, pcg._internal_state.state.extended_state[340]);
        EXPECT_EQ(0xd27c5157, pcg._internal_state.state.extended_state[510]);
        EXPECT_EQ(0x48ede633, pcg._internal_state.state.extended_state[680]);
        EXPECT_EQ(0x19078a53, pcg._internal_state.state.extended_state[850]);
        EXPECT_EQ(0x138889f7, pcg._internal_state.state.extended_state[1020]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(0.357);
        EXPECT_EQ(0x5b645a1cac083000, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0x5fee464f, pcg._internal_state.state.extended_state[0]);
        EXPECT_EQ(0x2084fa3f, pcg._internal_state.state.extended_state[170]);
        EXPECT_EQ(0x489eef92, pcg._internal_state.state.extended_state[340]);
        EXPECT_EQ(0xd233535b, pcg._internal_state.state.extended_state[510]);
        EXPECT_EQ(0x6f6dd894, pcg._internal_state.state.extended_state[680]);
        EXPECT_EQ(0x515faa34, pcg._internal_state.state.extended_state[850]);
        EXPECT_EQ(0xff1a726d, pcg._internal_state.state.extended_state[1020]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0xfffffffffffffffd, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0xec779c36, pcg._internal_state.state.extended_state[1]);
        EXPECT_EQ(0x0ae1d8ad, pcg._internal_state.state.extended_state[171]);
        EXPECT_EQ(0x9e0740e7, pcg._internal_state.state.extended_state[341]);
        EXPECT_EQ(0x5d88abb1, pcg._internal_state.state.extended_state[511]);
        EXPECT_EQ(0x32e7dd3a, pcg._internal_state.state.extended_state[681]);
        EXPECT_EQ(0x0eadef97, pcg._internal_state.state.extended_state[851]);
        EXPECT_EQ(0x86e22c5c, pcg._internal_state.state.extended_state[1021]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        EXPECT_THROW(pcg.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(pcg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        pcg._setstate(-1LL);
        EXPECT_EQ(0xffffffffffffffff, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0x6d1db36c, pcg._internal_state.state.extended_state[3]);
        EXPECT_EQ(0xd5dcb771, pcg._internal_state.state.extended_state[173]);
        EXPECT_EQ(0x634141d4, pcg._internal_state.state.extended_state[343]);
        EXPECT_EQ(0x521e36db, pcg._internal_state.state.extended_state[513]);
        EXPECT_EQ(0xe737509e, pcg._internal_state.state.extended_state[683]);
        EXPECT_EQ(0xe524096b, pcg._internal_state.state.extended_state[853]);
        EXPECT_EQ(0x7fe7d678, pcg._internal_state.state.extended_state[1023]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);

        pcg._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0xfffffffffffffffd, pcg._internal_state.state.state._internal_state.state);  // notice: (sic!)
        EXPECT_EQ(0xec779c36, pcg._internal_state.state.extended_state[1]);
        EXPECT_EQ(0x0ae1d8ad, pcg._internal_state.state.extended_state[171]);
        EXPECT_EQ(0x9e0740e7, pcg._internal_state.state.extended_state[341]);
        EXPECT_EQ(0x5d88abb1, pcg._internal_state.state.extended_state[511]);
        EXPECT_EQ(0x32e7dd3a, pcg._internal_state.state.extended_state[681]);
        EXPECT_EQ(0x0eadef97, pcg._internal_state.state.extended_state[851]);
        EXPECT_EQ(0x86e22c5c, pcg._internal_state.state.extended_state[1021]);
        EXPECT_FALSE(pcg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, pcg._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        pcg.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 60) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)pcg(ENTRIES_COUNT)]++;
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
