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

#include "mrg1457.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsMrg1457)
    {
        //-- tests empty constructor
        Mrg1457 mrg_1;

        EXPECT_EQ(47ULL, mrg_1._internal_state.state.list.size());
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
            Mrg1457 mrg(1);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x5f75c6d0, mrg._internal_state.state.list[1]);
            EXPECT_EQ(0x248b8c6f, mrg._internal_state.state.list[8]);
            EXPECT_EQ(0x1561670b, mrg._internal_state.state.list[15]);
            EXPECT_EQ(0x3f78fe87, mrg._internal_state.state.list[22]);
            EXPECT_EQ(0x7fb633f4, mrg._internal_state.state.list[29]);
            EXPECT_EQ(0x45970122, mrg._internal_state.state.list[36]);
            EXPECT_EQ(0x53ff869c, mrg._internal_state.state.list[43]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x12ce8e15, 0x5ef95e9b, 0x49993ccf, 0x217ffbdc, 0x6fb12f95 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x6fb12f95, mrg._internal_state.state.list[4]);
            EXPECT_EQ(0x4d7e6a26, mrg._internal_state.state.list[11]);
            EXPECT_EQ(0x57421bcb, mrg._internal_state.state.list[18]);
            EXPECT_EQ(0x0621a03e, mrg._internal_state.state.list[25]);
            EXPECT_EQ(0x32d67134, mrg._internal_state.state.list[32]);
            EXPECT_EQ(0x5593d0b8, mrg._internal_state.state.list[39]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(-2);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x6c2d5bd1, mrg._internal_state.state.list[5]);
            EXPECT_EQ(0x470f871c, mrg._internal_state.state.list[12]);
            EXPECT_EQ(0x6422863b, mrg._internal_state.state.list[19]);
            EXPECT_EQ(0x59d7f561, mrg._internal_state.state.list[26]);
            EXPECT_EQ(0x72f3a638, mrg._internal_state.state.list[33]);
            EXPECT_EQ(0x7854c5c6, mrg._internal_state.state.list[40]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x76528f85, 0x251d4dee, 0x5c0126de, 0x3316e359, 0x35cc2715 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x251d4dee, mrg._internal_state.state.list[1]);
            EXPECT_EQ(0x1259bb88, mrg._internal_state.state.list[8]);
            EXPECT_EQ(0x29779b5d, mrg._internal_state.state.list[15]);
            EXPECT_EQ(0x7cf42138, mrg._internal_state.state.list[22]);
            EXPECT_EQ(0x66368bf0, mrg._internal_state.state.list[29]);
            EXPECT_EQ(0x1243e37f, mrg._internal_state.state.list[36]);
            EXPECT_EQ(0x57ef01cf, mrg._internal_state.state.list[43]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(9);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x21f615f2, mrg._internal_state.state.list[2]);
            EXPECT_EQ(0x65033a18, mrg._internal_state.state.list[9]);
            EXPECT_EQ(0x485b4ad4, mrg._internal_state.state.list[16]);
            EXPECT_EQ(0x2fdb4320, mrg._internal_state.state.list[23]);
            EXPECT_EQ(0x27550a43, mrg._internal_state.state.list[30]);
            EXPECT_EQ(0x6360105e, mrg._internal_state.state.list[37]);
            EXPECT_EQ(0x57972710, mrg._internal_state.state.list[44]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x4f3ab691, 0x156c69eb, 0x1487a7b8, 0x66beeaad, 0x11171e36 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x0eab7a52, mrg._internal_state.state.list[5]);
            EXPECT_EQ(0x7e2d1a1f, mrg._internal_state.state.list[12]);
            EXPECT_EQ(0x5693b4e2, mrg._internal_state.state.list[19]);
            EXPECT_EQ(0x7af8fcbf, mrg._internal_state.state.list[26]);
            EXPECT_EQ(0x6d3a30e1, mrg._internal_state.state.list[33]);
            EXPECT_EQ(0x1ec46676, mrg._internal_state.state.list[40]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(-11);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x3766392e, mrg._internal_state.state.list[3]);
            EXPECT_EQ(0x0bd89bc8, mrg._internal_state.state.list[10]);
            EXPECT_EQ(0x11018138, mrg._internal_state.state.list[17]);
            EXPECT_EQ(0x10102bb5, mrg._internal_state.state.list[24]);
            EXPECT_EQ(0x5814dc5a, mrg._internal_state.state.list[31]);
            EXPECT_EQ(0x7e610c8c, mrg._internal_state.state.list[38]);
            EXPECT_EQ(0x557c4eee, mrg._internal_state.state.list[45]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x2afce433, 0x1cfbfb61, 0x70f32235, 0x19322ef8, 0x410733fd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x690048e8, mrg._internal_state.state.list[6]);
            EXPECT_EQ(0x72ab0ac1, mrg._internal_state.state.list[13]);
            EXPECT_EQ(0x00bb0c97, mrg._internal_state.state.list[20]);
            EXPECT_EQ(0x5c6bae05, mrg._internal_state.state.list[27]);
            EXPECT_EQ(0x4e5ff5f9, mrg._internal_state.state.list[34]);
            EXPECT_EQ(0x686b5efd, mrg._internal_state.state.list[41]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(17);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x1ca8a165, mrg._internal_state.state.list[3]);
            EXPECT_EQ(0x20a8ae97, mrg._internal_state.state.list[10]);
            EXPECT_EQ(0x365beb7a, mrg._internal_state.state.list[17]);
            EXPECT_EQ(0x347a23cf, mrg._internal_state.state.list[24]);
            EXPECT_EQ(0x3055be16, mrg._internal_state.state.list[31]);
            EXPECT_EQ(0x104da183, mrg._internal_state.state.list[38]);
            EXPECT_EQ(0x2698e24b, mrg._internal_state.state.list[45]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x77360b27, 0x18343220, 0x13c8c435, 0x1fe022b1, 0x2961af03 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x0403d35a, mrg._internal_state.state.list[6]);
            EXPECT_EQ(0x413114e5, mrg._internal_state.state.list[13]);
            EXPECT_EQ(0x5af40bd4, mrg._internal_state.state.list[20]);
            EXPECT_EQ(0x6a07f73c, mrg._internal_state.state.list[27]);
            EXPECT_EQ(0x7014e66d, mrg._internal_state.state.list[34]);
            EXPECT_EQ(0x33d5d4c4, mrg._internal_state.state.list[41]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x5c7e2d88, mrg._internal_state.state.list[6]);
            EXPECT_EQ(0x4bfb634c, mrg._internal_state.state.list[13]);
            EXPECT_EQ(0x2d159a4f, mrg._internal_state.state.list[20]);
            EXPECT_EQ(0x2c8d3baa, mrg._internal_state.state.list[27]);
            EXPECT_EQ(0x7bd16646, mrg._internal_state.state.list[34]);
            EXPECT_EQ(0x3fd8cb74, mrg._internal_state.state.list[41]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5b9a0a70, 0x11db2b21, 0x762504bd, 0x48cacaca, 0x0af720ea };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x762504bd, mrg._internal_state.state.list[2]);
            EXPECT_EQ(0x13406832, mrg._internal_state.state.list[9]);
            EXPECT_EQ(0x155c6271, mrg._internal_state.state.list[16]);
            EXPECT_EQ(0x7bf4ffba, mrg._internal_state.state.list[23]);
            EXPECT_EQ(0x048c9f63, mrg._internal_state.state.list[30]);
            EXPECT_EQ(0x1efd7e94, mrg._internal_state.state.list[37]);
            EXPECT_EQ(0x532cd602, mrg._internal_state.state.list[44]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(-8870000000000000000);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x717de1a2, mrg._internal_state.state.list[1]);
            EXPECT_EQ(0x15370809, mrg._internal_state.state.list[8]);
            EXPECT_EQ(0x7f5b31cc, mrg._internal_state.state.list[15]);
            EXPECT_EQ(0x00971099, mrg._internal_state.state.list[22]);
            EXPECT_EQ(0x31117f8c, mrg._internal_state.state.list[29]);
            EXPECT_EQ(0x50c40395, mrg._internal_state.state.list[36]);
            EXPECT_EQ(0x040e8e0c, mrg._internal_state.state.list[43]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x67dc1fe1, 0x4afc59ac, 0x04fb7f26, 0x1323fd01, 0x563193cf };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x563193cf, mrg._internal_state.state.list[4]);
            EXPECT_EQ(0x49c11799, mrg._internal_state.state.list[11]);
            EXPECT_EQ(0x43731401, mrg._internal_state.state.list[18]);
            EXPECT_EQ(0x7505ac1e, mrg._internal_state.state.list[25]);
            EXPECT_EQ(0x442b4ce0, mrg._internal_state.state.list[32]);
            EXPECT_EQ(0x28edeb84, mrg._internal_state.state.list[39]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(8870000000000000000);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x0a043caf, mrg._internal_state.state.list[6]);
            EXPECT_EQ(0x1c9c87c0, mrg._internal_state.state.list[13]);
            EXPECT_EQ(0x1441a9fd, mrg._internal_state.state.list[20]);
            EXPECT_EQ(0x253d0f34, mrg._internal_state.state.list[27]);
            EXPECT_EQ(0x21c338cc, mrg._internal_state.state.list[34]);
            EXPECT_EQ(0x035dae05, mrg._internal_state.state.list[41]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x3e8969f0, 0x7335d7c4, 0x4f91d942, 0x4fa3aa7e, 0x617c254d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x4f91d942, mrg._internal_state.state.list[2]);
            EXPECT_EQ(0x02221d08, mrg._internal_state.state.list[9]);
            EXPECT_EQ(0x65f4ee72, mrg._internal_state.state.list[16]);
            EXPECT_EQ(0x1f15e441, mrg._internal_state.state.list[23]);
            EXPECT_EQ(0x25f86f28, mrg._internal_state.state.list[30]);
            EXPECT_EQ(0x1a69f26e, mrg._internal_state.state.list[37]);
            EXPECT_EQ(0x77b33a94, mrg._internal_state.state.list[44]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(0.357);

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x2ff72327, mrg._internal_state.state.list[0]);
            EXPECT_EQ(0x735a9b30, mrg._internal_state.state.list[7]);
            EXPECT_EQ(0x0fcc7e29, mrg._internal_state.state.list[14]);
            EXPECT_EQ(0x177d97f7, mrg._internal_state.state.list[21]);
            EXPECT_EQ(0x0cd45b20, mrg._internal_state.state.list[28]);
            EXPECT_EQ(0x023a8f66, mrg._internal_state.state.list[35]);
            EXPECT_EQ(0x4c4169e8, mrg._internal_state.state.list[42]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x2dbd706e, 0x190a1ed2, 0x060f71e7, 0x34b3ea09, 0x632b30b5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x34b3ea09, mrg._internal_state.state.list[3]);
            EXPECT_EQ(0x06f9e986, mrg._internal_state.state.list[10]);
            EXPECT_EQ(0x712d657e, mrg._internal_state.state.list[17]);
            EXPECT_EQ(0x3e70e5ce, mrg._internal_state.state.list[24]);
            EXPECT_EQ(0x485991ea, mrg._internal_state.state.list[31]);
            EXPECT_EQ(0x496a4ff3, mrg._internal_state.state.list[38]);
            EXPECT_EQ(0x4c45914d, mrg._internal_state.state.list[45]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }
        {
            Mrg1457 mrg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, mrg._internal_state.state.index);
            EXPECT_EQ(0x3d2fb3f1, mrg._internal_state.state.list[6]);
            EXPECT_EQ(0x34f8bf70, mrg._internal_state.state.list[13]);
            EXPECT_EQ(0x76b742cd, mrg._internal_state.state.list[20]);
            EXPECT_EQ(0x500eecfc, mrg._internal_state.state.list[27]);
            EXPECT_EQ(0x227a9b47, mrg._internal_state.state.list[34]);
            EXPECT_EQ(0x1dacc61b, mrg._internal_state.state.list[41]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x498f88cc, 0x1d464e80, 0x6df13fc5, 0x076fe67d, 0x732adef4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, mrg.next());

            EXPECT_EQ(5, mrg._internal_state.state.index);
            EXPECT_EQ(0x6df13fc5, mrg._internal_state.state.list[2]);
            EXPECT_EQ(0x2b53a2c5, mrg._internal_state.state.list[9]);
            EXPECT_EQ(0x337dadd1, mrg._internal_state.state.list[16]);
            EXPECT_EQ(0x779e3f6c, mrg._internal_state.state.list[23]);
            EXPECT_EQ(0x68ef40b7, mrg._internal_state.state.list[30]);
            EXPECT_EQ(0x5306d0b3, mrg._internal_state.state.list[37]);
            EXPECT_EQ(0x3836005f, mrg._internal_state.state.list[44]);
            EXPECT_FALSE(mrg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);
        }

        EXPECT_THROW(Mrg1457(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Mrg1457(1.0001), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Mrg1457 mrg(mrg_1);

            EXPECT_TRUE(mrg_1._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_1._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_1._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Mrg1457 mrg_0;

        {
            Mrg1457 mrg_mem(mrg_0);
            Mrg1457 mrg(std::move(mrg_mem));

            EXPECT_TRUE(mrg_0._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_0._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_0._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Mrg1457 mrg;

            mrg = mrg_1;
            EXPECT_TRUE(mrg_1._internal_state.state == mrg._internal_state.state);
            EXPECT_EQ(mrg_1._internal_state.gauss_next, mrg._internal_state.gauss_next);
            EXPECT_EQ(mrg_1._internal_state.gauss_valid, mrg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Mrg1457 mrg;

        {
            Mrg1457 mrg_mem(mrg_0);
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
        EXPECT_EQ(0x78a7967c, mrg._internal_state.state.list[6]);
        EXPECT_EQ(0x6ec87087, mrg._internal_state.state.list[13]);
        EXPECT_EQ(0x2ea5f73d, mrg._internal_state.state.list[20]);
        EXPECT_EQ(0x3945df32, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0x4a327e9d, mrg._internal_state.state.list[34]);
        EXPECT_EQ(0x5961771a, mrg._internal_state.state.list[41]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(1);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x5f75c6d0, mrg._internal_state.state.list[1]);
        EXPECT_EQ(0x248b8c6f, mrg._internal_state.state.list[8]);
        EXPECT_EQ(0x1561670b, mrg._internal_state.state.list[15]);
        EXPECT_EQ(0x3f78fe87, mrg._internal_state.state.list[22]);
        EXPECT_EQ(0x7fb633f4, mrg._internal_state.state.list[29]);
        EXPECT_EQ(0x45970122, mrg._internal_state.state.list[36]);
        EXPECT_EQ(0x53ff869c, mrg._internal_state.state.list[43]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-2);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x6c2d5bd1, mrg._internal_state.state.list[5]);
        EXPECT_EQ(0x470f871c, mrg._internal_state.state.list[12]);
        EXPECT_EQ(0x6422863b, mrg._internal_state.state.list[19]);
        EXPECT_EQ(0x59d7f561, mrg._internal_state.state.list[26]);
        EXPECT_EQ(0x72f3a638, mrg._internal_state.state.list[33]);
        EXPECT_EQ(0x7854c5c6, mrg._internal_state.state.list[40]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(9L);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x21f615f2, mrg._internal_state.state.list[2]);
        EXPECT_EQ(0x65033a18, mrg._internal_state.state.list[9]);
        EXPECT_EQ(0x485b4ad4, mrg._internal_state.state.list[16]);
        EXPECT_EQ(0x2fdb4320, mrg._internal_state.state.list[23]);
        EXPECT_EQ(0x27550a43, mrg._internal_state.state.list[30]);
        EXPECT_EQ(0x6360105e, mrg._internal_state.state.list[37]);
        EXPECT_EQ(0x57972710, mrg._internal_state.state.list[44]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-11L);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x3766392e, mrg._internal_state.state.list[3]);
        EXPECT_EQ(0x0bd89bc8, mrg._internal_state.state.list[10]);
        EXPECT_EQ(0x11018138, mrg._internal_state.state.list[17]);
        EXPECT_EQ(0x10102bb5, mrg._internal_state.state.list[24]);
        EXPECT_EQ(0x5814dc5a, mrg._internal_state.state.list[31]);
        EXPECT_EQ(0x7e610c8c, mrg._internal_state.state.list[38]);
        EXPECT_EQ(0x557c4eee, mrg._internal_state.state.list[45]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(17UL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x1ca8a165, mrg._internal_state.state.list[3]);
        EXPECT_EQ(0x20a8ae97, mrg._internal_state.state.list[10]);
        EXPECT_EQ(0x365beb7a, mrg._internal_state.state.list[17]);
        EXPECT_EQ(0x347a23cf, mrg._internal_state.state.list[24]);
        EXPECT_EQ(0x3055be16, mrg._internal_state.state.list[31]);
        EXPECT_EQ(0x104da183, mrg._internal_state.state.list[38]);
        EXPECT_EQ(0x2698e24b, mrg._internal_state.state.list[45]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x5c7e2d88, mrg._internal_state.state.list[6]);
        EXPECT_EQ(0x4bfb634c, mrg._internal_state.state.list[13]);
        EXPECT_EQ(0x2d159a4f, mrg._internal_state.state.list[20]);
        EXPECT_EQ(0x2c8d3baa, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0x7bd16646, mrg._internal_state.state.list[34]);
        EXPECT_EQ(0x3fd8cb74, mrg._internal_state.state.list[41]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x717de1a2, mrg._internal_state.state.list[1]);
        EXPECT_EQ(0x15370809, mrg._internal_state.state.list[8]);
        EXPECT_EQ(0x7f5b31cc, mrg._internal_state.state.list[15]);
        EXPECT_EQ(0x00971099, mrg._internal_state.state.list[22]);
        EXPECT_EQ(0x31117f8c, mrg._internal_state.state.list[29]);
        EXPECT_EQ(0x50c40395, mrg._internal_state.state.list[36]);
        EXPECT_EQ(0x040e8e0c, mrg._internal_state.state.list[43]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x0a043caf, mrg._internal_state.state.list[6]);
        EXPECT_EQ(0x1c9c87c0, mrg._internal_state.state.list[13]);
        EXPECT_EQ(0x1441a9fd, mrg._internal_state.state.list[20]);
        EXPECT_EQ(0x253d0f34, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0x21c338cc, mrg._internal_state.state.list[34]);
        EXPECT_EQ(0x035dae05, mrg._internal_state.state.list[41]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(0.357);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x2ff72327, mrg._internal_state.state.list[0]);
        EXPECT_EQ(0x735a9b30, mrg._internal_state.state.list[7]);
        EXPECT_EQ(0x0fcc7e29, mrg._internal_state.state.list[14]);
        EXPECT_EQ(0x177d97f7, mrg._internal_state.state.list[21]);
        EXPECT_EQ(0x0cd45b20, mrg._internal_state.state.list[28]);
        EXPECT_EQ(0x023a8f66, mrg._internal_state.state.list[35]);
        EXPECT_EQ(0x4c4169e8, mrg._internal_state.state.list[42]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x3d2fb3f1, mrg._internal_state.state.list[6]);
        EXPECT_EQ(0x34f8bf70, mrg._internal_state.state.list[13]);
        EXPECT_EQ(0x76b742cd, mrg._internal_state.state.list[20]);
        EXPECT_EQ(0x500eecfc, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0x227a9b47, mrg._internal_state.state.list[34]);
        EXPECT_EQ(0x1dacc61b, mrg._internal_state.state.list[41]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        EXPECT_THROW(mrg.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(mrg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        mrg._setstate(-1LL);
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x78a7967c, mrg._internal_state.state.list[6]);
        EXPECT_EQ(0x6ec87087, mrg._internal_state.state.list[13]);
        EXPECT_EQ(0x2ea5f73d, mrg._internal_state.state.list[20]);
        EXPECT_EQ(0x3945df32, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0x4a327e9d, mrg._internal_state.state.list[34]);
        EXPECT_EQ(0x5961771a, mrg._internal_state.state.list[41]);
        EXPECT_FALSE(mrg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, mrg._internal_state.gauss_next);

        mrg._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, mrg._internal_state.state.index);
        EXPECT_EQ(0x3d2fb3f1, mrg._internal_state.state.list[6]);
        EXPECT_EQ(0x34f8bf70, mrg._internal_state.state.list[13]);
        EXPECT_EQ(0x76b742cd, mrg._internal_state.state.list[20]);
        EXPECT_EQ(0x500eecfc, mrg._internal_state.state.list[27]);
        EXPECT_EQ(0x227a9b47, mrg._internal_state.state.list[34]);
        EXPECT_EQ(0x1dacc61b, mrg._internal_state.state.list[41]);
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
