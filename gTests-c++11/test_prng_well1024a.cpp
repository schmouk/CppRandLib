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

#include "well1024a.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsWell1024a)
    {
        //-- tests empty constructor
        Well1024a wll_1;

        EXPECT_EQ(32ULL, wll_1._internal_state.state.list.size());
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
            Well1024a wll(1);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x85e7bb0f, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x87b341d6, wll._internal_state.state.list[13]);
            EXPECT_EQ(0xe2631837, wll._internal_state.state.list[19]);
            EXPECT_EQ(0x0c43407d, wll._internal_state.state.list[25]);
            EXPECT_EQ(0x962b1967, wll._internal_state.state.list[31]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x97897348, 0x1ffd928e, 0x5e8f8ff9, 0x281eaa99, 0x7778e6c4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0x71bb54d8, wll._internal_state.state.list[4]);
            EXPECT_EQ(0x6775dc77, wll._internal_state.state.list[10]);
            EXPECT_EQ(0xa534a6a6, wll._internal_state.state.list[16]);
            EXPECT_EQ(0x7ef1fd0e, wll._internal_state.state.list[22]);
            EXPECT_EQ(0x7778e6c4, wll._internal_state.state.list[28]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(-2);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xd85ab7a2, wll._internal_state.state.list[5]);
            EXPECT_EQ(0xf79e3f6d, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x7b875a0b, wll._internal_state.state.list[17]);
            EXPECT_EQ(0xcfee92df, wll._internal_state.state.list[23]);
            EXPECT_EQ(0xcc6d17e0, wll._internal_state.state.list[29]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc82a6f4c, 0x11ae0862, 0xdd5f0267, 0x8bc6d4ae, 0xf373cb0e };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0xd0d5127a, wll._internal_state.state.list[2]);
            EXPECT_EQ(0x24b37710, wll._internal_state.state.list[8]);
            EXPECT_EQ(0x0eaf4f68, wll._internal_state.state.list[14]);
            EXPECT_EQ(0x4f6d1767, wll._internal_state.state.list[20]);
            EXPECT_EQ(0xb3afeac2, wll._internal_state.state.list[26]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(9);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x43ec2be5, wll._internal_state.state.list[2]);
            EXPECT_EQ(0x3812b742, wll._internal_state.state.list[8]);
            EXPECT_EQ(0xc291b7c1, wll._internal_state.state.list[14]);
            EXPECT_EQ(0xc440b4f2, wll._internal_state.state.list[20]);
            EXPECT_EQ(0xf5f1f97e, wll._internal_state.state.list[26]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xabee96c1, 0x6375b810, 0x1422f3a9, 0x2466067d, 0xac8de664 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0x1d56f4a5, wll._internal_state.state.list[5]);
            EXPECT_EQ(0x36fb302f, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x32718c66, wll._internal_state.state.list[17]);
            EXPECT_EQ(0x5fb68641, wll._internal_state.state.list[23]);
            EXPECT_EQ(0x2466067d, wll._internal_state.state.list[29]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(-11);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x6ecc725d, wll._internal_state.state.list[3]);
            EXPECT_EQ(0x29417c76, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x07bca8b4, wll._internal_state.state.list[15]);
            EXPECT_EQ(0xe279f107, wll._internal_state.state.list[21]);
            EXPECT_EQ(0xb8d75c0b, wll._internal_state.state.list[27]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc04a8ddd, 0x8e152354, 0x1bff99e7, 0xde3ee844, 0xbd3a75b1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0xc04a8ddd, wll._internal_state.state.list[0]);
            EXPECT_EQ(0xd20091d0, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x16e30748, wll._internal_state.state.list[12]);
            EXPECT_EQ(0xd2f49a24, wll._internal_state.state.list[18]);
            EXPECT_EQ(0x2020576b, wll._internal_state.state.list[24]);
            EXPECT_EQ(0x1bff99e7, wll._internal_state.state.list[30]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(17);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x395142ca, wll._internal_state.state.list[3]);
            EXPECT_EQ(0xb57d05b4, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x09893880, wll._internal_state.state.list[15]);
            EXPECT_EQ(0x1ec47e35, wll._internal_state.state.list[21]);
            EXPECT_EQ(0xd40fee79, wll._internal_state.state.list[27]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xfbfafcc9, 0xca0db5ea, 0x5c39e0fc, 0x8961bbc2, 0xd17724a6 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0xfbfafcc9, wll._internal_state.state.list[0]);
            EXPECT_EQ(0x0807a6b4, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x68cfd338, wll._internal_state.state.list[12]);
            EXPECT_EQ(0x2a466b5b, wll._internal_state.state.list[18]);
            EXPECT_EQ(0x68f4479f, wll._internal_state.state.list[24]);
            EXPECT_EQ(0x5c39e0fc, wll._internal_state.state.list[30]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xb8fc5b10, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x8eba85b2, wll._internal_state.state.list[12]);
            EXPECT_EQ(0x997f31f8, wll._internal_state.state.list[18]);
            EXPECT_EQ(0x5e4d770f, wll._internal_state.state.list[24]);
            EXPECT_EQ(0x09193ec6, wll._internal_state.state.list[30]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xaef20bef, 0x3d574a34, 0x1f36d6d6, 0x227fe92e, 0x680e6922 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0xa2d41933, wll._internal_state.state.list[3]);
            EXPECT_EQ(0x2680d065, wll._internal_state.state.list[9]);
            EXPECT_EQ(0xd7ebcca1, wll._internal_state.state.list[15]);
            EXPECT_EQ(0x797f89de, wll._internal_state.state.list[21]);
            EXPECT_EQ(0xfddc00f7, wll._internal_state.state.list[27]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(-8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xe2fbc345, wll._internal_state.state.list[1]);
            EXPECT_EQ(0xe6d25024, wll._internal_state.state.list[7]);
            EXPECT_EQ(0xfbe6cd71, wll._internal_state.state.list[13]);
            EXPECT_EQ(0xd8a2a21a, wll._internal_state.state.list[19]);
            EXPECT_EQ(0xea0b583d, wll._internal_state.state.list[25]);
            EXPECT_EQ(0xc20cfd85, wll._internal_state.state.list[31]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x866fd6cc, 0x5c78dfcf, 0x8a7a4376, 0xf0c86ba9, 0xad89c7b6 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0x2a03b9af, wll._internal_state.state.list[4]);
            EXPECT_EQ(0x4592e2e8, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x61075d5d, wll._internal_state.state.list[16]);
            EXPECT_EQ(0x012e2133, wll._internal_state.state.list[22]);
            EXPECT_EQ(0xad89c7b6, wll._internal_state.state.list[28]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x1408795f, wll._internal_state.state.list[6]);
            EXPECT_EQ(0xc6afab58, wll._internal_state.state.list[12]);
            EXPECT_EQ(0xfb8939c5, wll._internal_state.state.list[18]);
            EXPECT_EQ(0x7c374de5, wll._internal_state.state.list[24]);
            EXPECT_EQ(0x4bf0de50, wll._internal_state.state.list[30]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb2a768cf, 0xfd25ea1c, 0x3b994f9f, 0xc96e082e, 0x6ae59943 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0xaf6aa8f4, wll._internal_state.state.list[3]);
            EXPECT_EQ(0x04443a10, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x4a80a9e7, wll._internal_state.state.list[15]);
            EXPECT_EQ(0xb5e65cc4, wll._internal_state.state.list[21]);
            EXPECT_EQ(0x9d81bcaa, wll._internal_state.state.list[27]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(0.357);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
            EXPECT_EQ(0x1c4d126a, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x102227a3, wll._internal_state.state.list[12]);
            EXPECT_EQ(0x239bcb0a, wll._internal_state.state.list[18]);
            EXPECT_EQ(0x7ce1cb9d, wll._internal_state.state.list[24]);
            EXPECT_EQ(0x365bbd9a, wll._internal_state.state.list[30]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf1d1222b, 0x91802bb8, 0x4dfcba4a, 0x6df924ca, 0x7f685e83 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0x77714db9, wll._internal_state.state.list[3]);
            EXPECT_EQ(0xe8f9525b, wll._internal_state.state.list[9]);
            EXPECT_EQ(0xd619e21c, wll._internal_state.state.list[15]);
            EXPECT_EQ(0x2efb2fee, wll._internal_state.state.list[21]);
            EXPECT_EQ(0xab8f74a9, wll._internal_state.state.list[27]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well1024a wll(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x7a5f67e3, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x149cc0b2, wll._internal_state.state.list[12]);
            EXPECT_EQ(0x4f7825c4, wll._internal_state.state.list[18]);
            EXPECT_EQ(0x54551aad, wll._internal_state.state.list[24]);
            EXPECT_EQ(0xd1de816e, wll._internal_state.state.list[30]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xcb50fdfc, 0x4af0897a, 0xfe8bb82e, 0x31648d0f, 0x48f8d5a1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(27, wll._internal_state.state.index);
            EXPECT_EQ(0x6f9fb04b, wll._internal_state.state.list[3]);
            EXPECT_EQ(0x56a7458a, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x4a78cd4f, wll._internal_state.state.list[15]);
            EXPECT_EQ(0x84a75e46, wll._internal_state.state.list[21]);
            EXPECT_EQ(0x569e20d9, wll._internal_state.state.list[27]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }

        EXPECT_THROW(Well1024a(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Well1024a(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Well1024a wll(wll_1);

            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Well1024a wll_0;

        {
            Well1024a wll_mem(wll_0);
            Well1024a wll(std::move(wll_mem));

            EXPECT_TRUE(wll_0._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_0._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_0._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Well1024a wll;

            wll = wll_1;
            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Well1024a wll;

        {
            Well1024a wll_mem(wll_0);
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
        EXPECT_EQ(0xf14f2cf8, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x01c9558b, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x2310bd4a, wll._internal_state.state.list[18]);
        EXPECT_EQ(0x2f36eb37, wll._internal_state.state.list[24]);
        EXPECT_EQ(0x24bdf605, wll._internal_state.state.list[30]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0x71b08009, 0x77e96294, 0x07e23a6d, 0x6964192a, 0xcf1099e9 };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, wll.next());
        EXPECT_EQ(27, wll._internal_state.state.index);
        EXPECT_EQ(0x6d1db36c, wll._internal_state.state.list[3]);
        EXPECT_EQ(0x031e50fe, wll._internal_state.state.list[9]);
        EXPECT_EQ(0xaceea13c, wll._internal_state.state.list[15]);
        EXPECT_EQ(0xac2cc667, wll._internal_state.state.list[21]);
        EXPECT_EQ(0x4515f20d, wll._internal_state.state.list[27]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(1);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x85e7bb0f, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x87b341d6, wll._internal_state.state.list[13]);
        EXPECT_EQ(0xe2631837, wll._internal_state.state.list[19]);
        EXPECT_EQ(0x0c43407d, wll._internal_state.state.list[25]);
        EXPECT_EQ(0x962b1967, wll._internal_state.state.list[31]);

        wll.seed(-2);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xd85ab7a2, wll._internal_state.state.list[5]);
        EXPECT_EQ(0xf79e3f6d, wll._internal_state.state.list[11]);
        EXPECT_EQ(0x7b875a0b, wll._internal_state.state.list[17]);
        EXPECT_EQ(0xcfee92df, wll._internal_state.state.list[23]);
        EXPECT_EQ(0xcc6d17e0, wll._internal_state.state.list[29]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(9L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x43ec2be5, wll._internal_state.state.list[2]);
        EXPECT_EQ(0x3812b742, wll._internal_state.state.list[8]);
        EXPECT_EQ(0xc291b7c1, wll._internal_state.state.list[14]);
        EXPECT_EQ(0xc440b4f2, wll._internal_state.state.list[20]);
        EXPECT_EQ(0xf5f1f97e, wll._internal_state.state.list[26]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-11L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x6ecc725d, wll._internal_state.state.list[3]);
        EXPECT_EQ(0x29417c76, wll._internal_state.state.list[9]);
        EXPECT_EQ(0x07bca8b4, wll._internal_state.state.list[15]);
        EXPECT_EQ(0xe279f107, wll._internal_state.state.list[21]);
        EXPECT_EQ(0xb8d75c0b, wll._internal_state.state.list[27]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(17UL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x395142ca, wll._internal_state.state.list[3]);
        EXPECT_EQ(0xb57d05b4, wll._internal_state.state.list[9]);
        EXPECT_EQ(0x09893880, wll._internal_state.state.list[15]);
        EXPECT_EQ(0x1ec47e35, wll._internal_state.state.list[21]);
        EXPECT_EQ(0xd40fee79, wll._internal_state.state.list[27]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xb8fc5b10, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x8eba85b2, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x997f31f8, wll._internal_state.state.list[18]);
        EXPECT_EQ(0x5e4d770f, wll._internal_state.state.list[24]);
        EXPECT_EQ(0x09193ec6, wll._internal_state.state.list[30]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xe2fbc345, wll._internal_state.state.list[1]);
        EXPECT_EQ(0xe6d25024, wll._internal_state.state.list[7]);
        EXPECT_EQ(0xfbe6cd71, wll._internal_state.state.list[13]);
        EXPECT_EQ(0xd8a2a21a, wll._internal_state.state.list[19]);
        EXPECT_EQ(0xea0b583d, wll._internal_state.state.list[25]);
        EXPECT_EQ(0xc20cfd85, wll._internal_state.state.list[31]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x1408795f, wll._internal_state.state.list[6]);
        EXPECT_EQ(0xc6afab58, wll._internal_state.state.list[12]);
        EXPECT_EQ(0xfb8939c5, wll._internal_state.state.list[18]);
        EXPECT_EQ(0x7c374de5, wll._internal_state.state.list[24]);
        EXPECT_EQ(0x4bf0de50, wll._internal_state.state.list[30]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0.357);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
        EXPECT_EQ(0x1c4d126a, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x102227a3, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x239bcb0a, wll._internal_state.state.list[18]);
        EXPECT_EQ(0x7ce1cb9d, wll._internal_state.state.list[24]);
        EXPECT_EQ(0x365bbd9a, wll._internal_state.state.list[30]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x7a5f67e3, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x149cc0b2, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x4f7825c4, wll._internal_state.state.list[18]);
        EXPECT_EQ(0x54551aad, wll._internal_state.state.list[24]);
        EXPECT_EQ(0xd1de816e, wll._internal_state.state.list[30]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        EXPECT_THROW(wll.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(wll.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        wll._setstate(-1LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xf14f2cf8, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x01c9558b, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x2310bd4a, wll._internal_state.state.list[18]);
        EXPECT_EQ(0x2f36eb37, wll._internal_state.state.list[24]);
        EXPECT_EQ(0x24bdf605, wll._internal_state.state.list[30]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x7a5f67e3, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x149cc0b2, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x4f7825c4, wll._internal_state.state.list[18]);
        EXPECT_EQ(0x54551aad, wll._internal_state.state.list[24]);
        EXPECT_EQ(0xd1de816e, wll._internal_state.state.list[30]);
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
