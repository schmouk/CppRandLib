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

#include "xoroshiro512.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsXoroshiro512)
    {
        //-- tests empty constructor
        Xoroshiro512 xrsr_1;

        EXPECT_EQ(8ULL, xrsr_1._internal_state.state.list.size());
        EXPECT_EQ(0, xrsr_1._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                xrsr_1._internal_state.state.list.cbegin(),
                xrsr_1._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(xrsr_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Xoroshiro512 xrsr(1);

            EXPECT_EQ(0x910a2dec89025cc1, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xbeeb8da1658eec67, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xf893a2eefb32555e, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x71c18690ee42c90b, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x71bb54d8d101b5b9, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xc34d0bff90150280, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xe099ec6cd7363ca5, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x85e7bb0f12278575, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb3f2af6d0fc710c5, 0x853b559647364cea, 0x12b0ebbfe54e43b6, 0x7dc8a7e8eb0ac06b, 0x616dbf8258a39551 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x0e409c2efa701d9e, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xc542180fd6b1aabf, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x5839d3f2f48d7ead, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x2131879511433df6, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x5e1e555a3d1c034f, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x16e41addee199e49, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xf9430f51ac65db09, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x73ae77c62de045af, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(-2);

            EXPECT_EQ(0xf3203e9039f4a821, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xba56949915dcf9e9, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xd0d5127a96e8d90d, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x1ef156bb76650c37, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x7842841591543f1d, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xd85ab7a2b154095a, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xea909a92e113bf3c, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x1e2b53fb7bd63f05, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9c0f746bebf6fd59, 0xe3b62be9ec055080, 0xbb45b189c48072e1, 0x4318adc0dc125095, 0xf7206a3cbd6e03b6 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0xc93e8935bf6b5180, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x4dca3dbfba03020d, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x24ed50382ae8fb8e, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x1ba8a93843428608, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0xd08ffa32680cd8d9, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xef938d592ad034d7, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xa9a511edec8f4eaa, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x5dbbec6bde39181a, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(9);

            EXPECT_EQ(0xaeaf52febe706064, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xc02d8a5e87afea62, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x43ec2be544b589b6, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xc8e98cd697316060, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x4336b3782f5887a1, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x1d56f4a5808e6bfe, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xa553b8a65aacb8cc, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xfbc9d6184de7f13d, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa94eecf619a060, 0x40619b85d152fbf9, 0xe6f08fbd9ff6c565, 0xbcd7dd050d690bdf, 0x4ccbb0851109486e };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x366f7cbf342fb69e, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x1c6e4b830db6f2c0, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x79dd8f4a49cb1b68, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x9cbd50e0bd853782, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x302f694c0f77dd5f, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x82c426393bdabbc7, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x2e5feb6686e3b93e, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x2626d50bfd28d973, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(-11);

            EXPECT_EQ(0x6fc5530939fb94c3, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x96caee613260cfca, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x46d40b90622a734b, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x6ecc725d7bedada9, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x69e6fff0691d876d, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xdbc92595fffb67c7, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xd20091d031cd373d, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xd830cf06dc6b4874, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd5f38aed82434538, 0xcf94d54a1209d057, 0xd56e3120988295c3, 0x45a397be25d29a53, 0x9a902e1dcdbe74c9 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x9db4c3b8c3d3b374, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x4b44e65dc6d30629, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xac67b600d4b72cb0, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x1db4f02cd9144fac, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0xe8c948e18cb469cd, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x0f6550d07daacfbe, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x1df4013046d7fff0, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xaff266317e3c02f3, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(17);

            EXPECT_EQ(0x808475f02ee37363, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x6434ff62b4e8edd1, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x540d6c3702d41b8c, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x395142ca8efaf003, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x046b1664f61a205e, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x14db9121e4c732ea, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x0807a6b4c6fa7404, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xa74db96e1ce9c735, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa8722ce678e6e2ca, 0xb0c58defa535f501, 0x19615f2b432101c7, 0xe0417b93cf3e858, 0xebda10e4463caf16 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x7de8559b770a2340, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x99713ea9b1162f04, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x5bd8fbc567e42117, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xd85305de47507380, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x5a9a916d2c361bc0, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xe7921cfa21b2f7cb, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x3f4910c9834d4125, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x0356cc13815384ac, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0x157a3807a48faa9d, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xd573529b34a1d093, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x2f90b72e996dccbe, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xa2d419334c4667ec, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x01404ce914938008, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x14bc574c2a2b4c72, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xb8fc5b1060708c05, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x8931545f4f9ea651, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa2c2a42038d4ec3d, 0x5fc25d0738e7b0f, 0x8cdae320589ff91e, 0x5ef9741cae1d2a1c, 0xb5bfb1afdbeb04dd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x2dd1d8834a1d1abe, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xfd4348c7c59ed738, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xe8c9a4d483fa1ce6, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x90f3152a081b547f, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0xadf094a1bc23213c, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x08bb748601635214, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xfad74f72516c3bfd, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x8f2b04287d66d6e6, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(-8870000000000000000);

            EXPECT_EQ(0x48bbc5b84275f3ca, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xe2fbc345a799b5aa, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x86ce19a135fba0de, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x637c87187035ea06, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x2a03b9aff2bfd421, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x534fe17cac5d7a22, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x95d0c8e531644d42, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xe6d2502493ff622e, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x20a99f3b027772ef, 0x7dc1a84a19c7b6e7, 0x3a1d2eadf4fa7e0e, 0xd9641a86828c970e, 0xe5a0217e5122a658 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x103002960048f16e, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x84e68f88940a0f58, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xb804edab0b3cc10f, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x496ed04bea07f859, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x98c537adb2c5dedc, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xa1c9b1ba2c68211f, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0xa18854c569fcc441, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xb8def929e56339dc, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(8870000000000000000);

            EXPECT_EQ(0xeede014d9a5a6108, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xa6eb6466bac9f251, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x4246cbb1a64bf70c, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xaf6aa8f43ebb8659, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0xe1b0fb2c7e764cdb, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x56d25f68391b2f83, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x1408795faf81b73d, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xe0c07d9420f2f41e, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb053076abfcc1fa9, 0x2ad894da04d1796a, 0x5f003e931832cd96, 0x30fa0d4c68ebcc18, 0xaabfa100ba6c8b97 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0xfc38345463e2d0ba, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xe3029d9f518e44ed, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x3a44b73920412164, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xe2c300cd828611fc, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x94f2f6f00379d0e4, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x8f15ec27b68e0770, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x3ae597d619838224, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x5e43b3542d3c95c8, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(0.357);

            EXPECT_EQ(0x5fee464f36fc42c3, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x954faf5a9ad49cf8, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xa985465a4a5fc644, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x77714db9e870d702, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0xa3aac457d81d552c, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xbcf1fb888caf4f02, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x1c4d126a40f3f8a9, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xe6b536617ee8b60c, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x80e9769bafcbd01d, 0xb96885c177a72daf, 0xd41abe5142e3d5e1, 0x38284ef2881f2551, 0xb22d3c0a578ad547 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x26f4334f02af70c5, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x06727eb5957d75ac, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x198ef43ea6d5abf5, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xd243349f3e425f0e, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x4304e17111157e1d, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x53fecc67cd8bc8fc, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x63900bc3d0c165b2, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x355c62aa6d2ee6cb, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro512 xrsr(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xec779c3693f88501, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xfed9eeb4936de39d, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x260ffb0260bbbe5f, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x082cfe8866fac366, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x7a5f67e38e997e3f, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xd7c07017388fa2af, xrsr._internal_state.state.list[7]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }

        EXPECT_THROW(Xoroshiro512(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Xoroshiro512(1.0), FloatValueRange01Exception);



        //-- tests copy constructor
        {
            Xoroshiro512 xrsr(xrsr_1);

            EXPECT_TRUE(xrsr_1._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_1._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_1._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Xoroshiro512 xrsr_0;

        {
            Xoroshiro512 xrsr_mem(xrsr_0);
            Xoroshiro512 xrsr(std::move(xrsr_mem));

            EXPECT_TRUE(xrsr_0._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_0._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_0._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Xoroshiro512 xrsr;

            xrsr = xrsr_1;
            EXPECT_TRUE(xrsr_1._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_1._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_1._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Xoroshiro512 xrsr;

        {
            Xoroshiro512 xrsr_mem(xrsr_0);
            xrsr = std::move(xrsr_mem);

            EXPECT_TRUE(xrsr_0._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_0._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_0._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests seed()
        xrsr.seed();
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                xrsr._internal_state.state.list.cbegin(),
                xrsr._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);


        //-- tests seed(value)
        xrsr.seed(-1);
        EXPECT_EQ(0xe4d971771b652c20, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xe99ff867dbf682c9, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x382ff84cb27281e9, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x6d1db36ccba982d2, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xb4a0472e578069ae, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xd31dadbda438bb33, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xf14f2cf802083fa5, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x405da438a39e8064, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0x8f5520d52a7ead08, 0xc476a018caa1802d, 0xd914f51aac453226, 0xff289ff706f7af3f, 0xd501b724ae06993a };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, xrsr.next());
        EXPECT_EQ(0x45ecede8c77365aa, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x7b808c7675ca9236, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xeaa565246da85381, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x2687780aeb1733a6, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xe30e5e4ef2b700af, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x61f4419c62730f97, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x298e47f5c0f40b20, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xe11a3ca1a5477373, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(1);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x910a2dec89025cc1, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xbeeb8da1658eec67, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xf893a2eefb32555e, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x71c18690ee42c90b, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x71bb54d8d101b5b9, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xc34d0bff90150280, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xe099ec6cd7363ca5, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x85e7bb0f12278575, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-2);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xf3203e9039f4a821, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xba56949915dcf9e9, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xd0d5127a96e8d90d, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x1ef156bb76650c37, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x7842841591543f1d, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xd85ab7a2b154095a, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xea909a92e113bf3c, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x1e2b53fb7bd63f05, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(9L);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xaeaf52febe706064, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xc02d8a5e87afea62, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x43ec2be544b589b6, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xc8e98cd697316060, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x4336b3782f5887a1, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x1d56f4a5808e6bfe, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xa553b8a65aacb8cc, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xfbc9d6184de7f13d, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-11L);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x6fc5530939fb94c3, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x96caee613260cfca, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x46d40b90622a734b, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x6ecc725d7bedada9, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x69e6fff0691d876d, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xdbc92595fffb67c7, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xd20091d031cd373d, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xd830cf06dc6b4874, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(17UL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x808475f02ee37363, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x6434ff62b4e8edd1, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x540d6c3702d41b8c, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x395142ca8efaf003, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x046b1664f61a205e, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x14db9121e4c732ea, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x0807a6b4c6fa7404, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xa74db96e1ce9c735, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x157a3807a48faa9d, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xd573529b34a1d093, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x2f90b72e996dccbe, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xa2d419334c4667ec, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x01404ce914938008, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x14bc574c2a2b4c72, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xb8fc5b1060708c05, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x8931545f4f9ea651, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x48bbc5b84275f3ca, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xe2fbc345a799b5aa, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x86ce19a135fba0de, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x637c87187035ea06, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x2a03b9aff2bfd421, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x534fe17cac5d7a22, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x95d0c8e531644d42, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xe6d2502493ff622e, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xeede014d9a5a6108, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xa6eb6466bac9f251, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x4246cbb1a64bf70c, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xaf6aa8f43ebb8659, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xe1b0fb2c7e764cdb, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x56d25f68391b2f83, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x1408795faf81b73d, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xe0c07d9420f2f41e, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(0.357);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x5fee464f36fc42c3, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x954faf5a9ad49cf8, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xa985465a4a5fc644, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x77714db9e870d702, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xa3aac457d81d552c, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xbcf1fb888caf4f02, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x1c4d126a40f3f8a9, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xe6b536617ee8b60c, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xec779c3693f88501, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xfed9eeb4936de39d, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x260ffb0260bbbe5f, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x082cfe8866fac366, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x7a5f67e38e997e3f, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xd7c07017388fa2af, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        EXPECT_THROW(xrsr.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(xrsr.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        xrsr._setstate(-1LL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xe4d971771b652c20, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xe99ff867dbf682c9, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x382ff84cb27281e9, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x6d1db36ccba982d2, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xb4a0472e578069ae, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xd31dadbda438bb33, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xf14f2cf802083fa5, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x405da438a39e8064, xrsr._internal_state.state.list[7]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        xrsr.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 60) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)xrsr(ENTRIES_COUNT)]++;
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
