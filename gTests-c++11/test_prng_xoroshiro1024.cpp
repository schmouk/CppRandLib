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

#include "xoroshiro1024.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsXoroshiro1024)
    {
        //-- tests empty constructor
        Xoroshiro1024 xrsr_1;

        EXPECT_EQ(16ULL, xrsr_1._internal_state.state.list.size());
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
            Xoroshiro1024 xrsr(1);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1658eec67, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x71bb54d8d101b5b9, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x85e7bb0f12278575, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0x6775dc7701564f61, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0x87b341d690d7a28a, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb3f2af6d0fc710c5, 0xf9d20113ec80c6d5, 0x8253bcf0deab787c, 0xf6f50e5ea678c37c, 0x458df629d8b843a8 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0x9dc6590fa52bc2c6, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x3e1842e97c8c3834, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x491718de357e3da8, xrsr._internal_state.state.list[8]);
            EXPECT_EQ(0x9afcd44d14cf8bfe, xrsr._internal_state.state.list[11]);
            EXPECT_EQ(0x6f9b6dae6f4c57a8, xrsr._internal_state.state.list[14]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(-2);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0xba56949915dcf9e9, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x7842841591543f1d, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x1e2b53fb7bd63f05, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0x2b724bbbfb591868, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0x8457d34b5125f667, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9c0f746bebf6fd59, 0xba1fc6437713a4da, 0x361f79e7e192d835, 0xd89be545e78c0e0c, 0xf923cc95e2d269fc };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0x22a12a4c8558017a, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x09f9f051bd60c265, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x24b37710c55c43d9, xrsr._internal_state.state.list[8]);
            EXPECT_EQ(0xf79e3f6d8cc3172a, xrsr._internal_state.state.list[11]);
            EXPECT_EQ(0x0eaf4f68451b6ba0, xrsr._internal_state.state.list[14]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(9);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0xaeaf52febe706064, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xc8e98cd697316060, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0xa553b8a65aacb8cc, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xca06743146f19573, xrsr._internal_state.state.list[9]);
            EXPECT_EQ(0xfc5a343f8fd7765d, xrsr._internal_state.state.list[12]);
            EXPECT_EQ(0xe2c451a59ccc7479, xrsr._internal_state.state.list[15]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x00a94eecf619a060, 0x41dba689f49a8071, 0x86e0dc49d6f87426, 0x4ec6102947eba7e8, 0x24808bcc847dd591 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0x09f9208d681fdbe2, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xf439f123de07ab94, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xfbc9d6184de7f13d, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0x96f90d64c71a19a0, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0x3d8599a83b71b57c, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(-11);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0x96caee613260cfca, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x69e6fff0691d876d, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xd830cf06dc6b4874, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0x17b1379019c20f06, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0xe5561582cef81501, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd5f38aed82434538, 0xa30430a0bb221939, 0xf80d376463c35b34, 0xcd7ea13d186714c8, 0x2dcdaeff989efecd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0xed4e45536f2b85b2, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x789ce829c3fb1ce9, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x87422545f121192f, xrsr._internal_state.state.list[8]);
            EXPECT_EQ(0x918022dae450d1f3, xrsr._internal_state.state.list[11]);
            EXPECT_EQ(0xd79a3e3c2651d3e0, xrsr._internal_state.state.list[14]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(17);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0x540d6c3702d41b8c, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x14db9121e4c732ea, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x067c24523a89bd3a, xrsr._internal_state.state.list[8]);
            EXPECT_EQ(0x147927e3f3e07aaa, xrsr._internal_state.state.list[11]);
            EXPECT_EQ(0xcd16dbb0c9679e35, xrsr._internal_state.state.list[14]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa8722ce678e6e2ca, 0x2e02d5bfa46bd0e2, 0xa45ecd910e184407, 0x6977dfa14bd84363, 0x4c417a9b81f992d4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0xb50907bca8c3f74c, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x6352de1613b47f2e, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x0807a6b4c6fa7404, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xb57d05b4f3731b20, xrsr._internal_state.state.list[9]);
            EXPECT_EQ(0x68cfd3386fe39985, xrsr._internal_state.state.list[12]);
            EXPECT_EQ(0x09893880ff74f9ea, xrsr._internal_state.state.list[15]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0x157a3807a48faa9d, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xa2d419334c4667ec, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0xb8fc5b1060708c05, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x2680d065cb73ece7, xrsr._internal_state.state.list[9]);
            EXPECT_EQ(0x8eba85b28df77747, xrsr._internal_state.state.list[12]);
            EXPECT_EQ(0xd7ebcca19d49c3f5, xrsr._internal_state.state.list[15]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa2c2a42038d4ec3d, 0x3819987c267eb726, 0xa437023430223ecf, 0x26c27c4ef6c0b41b, 0x8dac31b4ce3806cb };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0x648a17705da44419, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x1fd7e2f11d1d3f70, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0x8931545f4f9ea651, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0xcdb8c9cd9a62da0f, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0x97f6c69811cfb13b, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(-8870000000000000000);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0xe2fbc345a799b5aa, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x2a03b9aff2bfd421, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xe6d2502493ff622e, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0x4592e2e878ff1b75, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0xfbe6cd715ff52a4a, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x20a99f3b027772ef, 0x1d40ab3e9da385d9, 0x71dfa5dcbd118b38, 0x53d1f6d5dc24ea31, 0x85517526373bffd0 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0xe3a48c440454e9b1, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xe765fa1b8c5b69e9, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x2a6e10124e1efad4, xrsr._internal_state.state.list[8]);
            EXPECT_EQ(0x93822f3315b6d4e7, xrsr._internal_state.state.list[11]);
            EXPECT_EQ(0xb8c110d712c66128, xrsr._internal_state.state.list[14]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(8870000000000000000);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0x4246cbb1a64bf70c, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x56d25f68391b2f83, xrsr._internal_state.state.list[5]);
            EXPECT_EQ(0x13d184a1443e3dbe, xrsr._internal_state.state.list[8]);
            EXPECT_EQ(0xff42f03c6e8cba89, xrsr._internal_state.state.list[11]);
            EXPECT_EQ(0x74d601c8c6c14f90, xrsr._internal_state.state.list[14]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb053076abfcc1fa9, 0x38e71d1dad368f4d, 0xdfd977837b4ed466, 0x0e13691d65c14154, 0x7d62a904e3ad06a1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0xdc446a554bde4591, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xb1a19ce4baba1c25, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x1408795faf81b73d, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x04443a1051eede9a, xrsr._internal_state.state.list[9]);
            EXPECT_EQ(0xc6afab58afb8fb4e, xrsr._internal_state.state.list[12]);
            EXPECT_EQ(0x4a80a9e791a99572, xrsr._internal_state.state.list[15]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(0.357);

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0x5fee464f36fc42c3, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x77714db9e870d702, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x1c4d126a40f3f8a9, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0xe8f9525bf6c56aef, xrsr._internal_state.state.list[9]);
            EXPECT_EQ(0x102227a35cb75364, xrsr._internal_state.state.list[12]);
            EXPECT_EQ(0xd619e21c3a243eb0, xrsr._internal_state.state.list[15]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x80e9769bafcbd01d, 0x36aeef896aecfb5f, 0x7554d6edeae5ae7a, 0x8241b87e93fc5ee1, 0x449b805d6871b018 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0xe89e10d299125d92, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x9a65fbb429f385fb, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xe6b536617ee8b60c, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0x0df3d30dc1390db9, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0xee8fd4bfccca5ee3, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro1024 xrsr(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, xrsr._internal_state.state.index);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);
            EXPECT_EQ(0x7a5f67e38e997e3f, xrsr._internal_state.state.list[6]);
            EXPECT_EQ(0x56a7458a6eece57b, xrsr._internal_state.state.list[9]);
            EXPECT_EQ(0x149cc0b2e9f5efed, xrsr._internal_state.state.list[12]);
            EXPECT_EQ(0x4a78cd4fccb7e9f8, xrsr._internal_state.state.list[15]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x833acc0157b09947, 0x277adef5288150e5, 0x88fe984e5a0c61cf, 0x678fb580803b5cd7, 0xf45efd0d0a2c77b4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(5, xrsr._internal_state.state.index);
            EXPECT_EQ(0x5b625bd06219df92, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xf6915518d3f172cc, xrsr._internal_state.state.list[4]);
            EXPECT_EQ(0xd7c07017388fa2af, xrsr._internal_state.state.list[7]);
            EXPECT_EQ(0x71da8c61bc0cfda9, xrsr._internal_state.state.list[10]);
            EXPECT_EQ(0x69f17ee1a874dbdd, xrsr._internal_state.state.list[13]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }

        EXPECT_THROW(Xoroshiro1024(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Xoroshiro1024(1.0001), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Xoroshiro1024 xrsr(xrsr_1);

            EXPECT_TRUE(xrsr_1._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_1._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_1._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Xoroshiro1024 xrsr_0;

        {
            Xoroshiro1024 xrsr_mem(xrsr_0);
            Xoroshiro1024 xrsr(std::move(xrsr_mem));

            EXPECT_TRUE(xrsr_0._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_0._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_0._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Xoroshiro1024 xrsr;

            xrsr = xrsr_1;
            EXPECT_TRUE(xrsr_1._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_1._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_1._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Xoroshiro1024 xrsr;

        {
            Xoroshiro1024 xrsr_mem(xrsr_0);
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
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x382ff84cb27281e9, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xd31dadbda438bb33, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xc4fea708156e0c84, xrsr._internal_state.state.list[8]);
        EXPECT_EQ(0xce755952d3025da7, xrsr._internal_state.state.list[11]);
        EXPECT_EQ(0x354d0df8b25878c1, xrsr._internal_state.state.list[14]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0x8f5520d52a7ead08, 0x3752bdaf106afaec, 0x1c450fe665ff7590, 0x164192b0c949cd5b, 0x1bc52aeefc73fc07 };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, xrsr.next());
        EXPECT_EQ(5, xrsr._internal_state.state.index);
        EXPECT_EQ(0x44f5f9621b409119, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x3363eb6f5922fadd, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xf14f2cf802083fa5, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x031e50fe7bbd6e1c, xrsr._internal_state.state.list[9]);
        EXPECT_EQ(0x01c9558bd006badb, xrsr._internal_state.state.list[12]);
        EXPECT_EQ(0xaceea13ca07e34e8, xrsr._internal_state.state.list[15]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(1);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1658eec67, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x71bb54d8d101b5b9, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x85e7bb0f12278575, xrsr._internal_state.state.list[7]);
        EXPECT_EQ(0x6775dc7701564f61, xrsr._internal_state.state.list[10]);
        EXPECT_EQ(0x87b341d690d7a28a, xrsr._internal_state.state.list[13]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-2);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xba56949915dcf9e9, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x7842841591543f1d, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0x1e2b53fb7bd63f05, xrsr._internal_state.state.list[7]);
        EXPECT_EQ(0x2b724bbbfb591868, xrsr._internal_state.state.list[10]);
        EXPECT_EQ(0x8457d34b5125f667, xrsr._internal_state.state.list[13]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(9L);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xaeaf52febe706064, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xc8e98cd697316060, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xa553b8a65aacb8cc, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xca06743146f19573, xrsr._internal_state.state.list[9]);
        EXPECT_EQ(0xfc5a343f8fd7765d, xrsr._internal_state.state.list[12]);
        EXPECT_EQ(0xe2c451a59ccc7479, xrsr._internal_state.state.list[15]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-11L);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x96caee613260cfca, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x69e6fff0691d876d, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xd830cf06dc6b4874, xrsr._internal_state.state.list[7]);
        EXPECT_EQ(0x17b1379019c20f06, xrsr._internal_state.state.list[10]);
        EXPECT_EQ(0xe5561582cef81501, xrsr._internal_state.state.list[13]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(17UL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x540d6c3702d41b8c, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x14db9121e4c732ea, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x067c24523a89bd3a, xrsr._internal_state.state.list[8]);
        EXPECT_EQ(0x147927e3f3e07aaa, xrsr._internal_state.state.list[11]);
        EXPECT_EQ(0xcd16dbb0c9679e35, xrsr._internal_state.state.list[14]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x157a3807a48faa9d, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xa2d419334c4667ec, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0xb8fc5b1060708c05, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x2680d065cb73ece7, xrsr._internal_state.state.list[9]);
        EXPECT_EQ(0x8eba85b28df77747, xrsr._internal_state.state.list[12]);
        EXPECT_EQ(0xd7ebcca19d49c3f5, xrsr._internal_state.state.list[15]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xe2fbc345a799b5aa, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x2a03b9aff2bfd421, xrsr._internal_state.state.list[4]);
        EXPECT_EQ(0xe6d2502493ff622e, xrsr._internal_state.state.list[7]);
        EXPECT_EQ(0x4592e2e878ff1b75, xrsr._internal_state.state.list[10]);
        EXPECT_EQ(0xfbe6cd715ff52a4a, xrsr._internal_state.state.list[13]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x4246cbb1a64bf70c, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x56d25f68391b2f83, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0x13d184a1443e3dbe, xrsr._internal_state.state.list[8]);
        EXPECT_EQ(0xff42f03c6e8cba89, xrsr._internal_state.state.list[11]);
        EXPECT_EQ(0x74d601c8c6c14f90, xrsr._internal_state.state.list[14]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(0.357);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x5fee464f36fc42c3, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x77714db9e870d702, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x1c4d126a40f3f8a9, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0xe8f9525bf6c56aef, xrsr._internal_state.state.list[9]);
        EXPECT_EQ(0x102227a35cb75364, xrsr._internal_state.state.list[12]);
        EXPECT_EQ(0xd619e21c3a243eb0, xrsr._internal_state.state.list[15]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x7a5f67e38e997e3f, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x56a7458a6eece57b, xrsr._internal_state.state.list[9]);
        EXPECT_EQ(0x149cc0b2e9f5efed, xrsr._internal_state.state.list[12]);
        EXPECT_EQ(0x4a78cd4fccb7e9f8, xrsr._internal_state.state.list[15]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        EXPECT_THROW(xrsr.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(xrsr.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        xrsr._setstate(-1LL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x382ff84cb27281e9, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xd31dadbda438bb33, xrsr._internal_state.state.list[5]);
        EXPECT_EQ(0xc4fea708156e0c84, xrsr._internal_state.state.list[8]);
        EXPECT_EQ(0xce755952d3025da7, xrsr._internal_state.state.list[11]);
        EXPECT_EQ(0x354d0df8b25878c1, xrsr._internal_state.state.list[14]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);
        EXPECT_EQ(0x7a5f67e38e997e3f, xrsr._internal_state.state.list[6]);
        EXPECT_EQ(0x56a7458a6eece57b, xrsr._internal_state.state.list[9]);
        EXPECT_EQ(0x149cc0b2e9f5efed, xrsr._internal_state.state.list[12]);
        EXPECT_EQ(0x4a78cd4fccb7e9f8, xrsr._internal_state.state.list[15]);
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
