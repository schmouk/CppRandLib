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

#include "melg19937.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsMelg19937)
    {
        //-- tests empty constructor
        Melg19937 melg_1;

        EXPECT_EQ(312ULL, melg_1._internal_state.state.list.size());
        EXPECT_EQ(0, melg_1._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                melg_1._internal_state.state.list.cbegin(),
                melg_1._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(melg_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg_1._internal_state.gauss_next);


        // Notice: hard coded values below have been evaluated with PyRandLib")

        //-- tests Valued construtor (seed) AND next()
        {
            Melg19937 melg(1);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1658eec67, melg._internal_state.state.list[1]);
            EXPECT_EQ(0x88b894e1401ed25b, melg._internal_state.state.list[63]);
            EXPECT_EQ(0x32647003725b6ed3, melg._internal_state.state.list[125]);
            EXPECT_EQ(0xeaeb4814b3a728d7, melg._internal_state.state.list[187]);
            EXPECT_EQ(0x3e17e6dfc3cb0bac, melg._internal_state.state.list[249]);
            EXPECT_EQ(0xe9316fe9c2c04c2d, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x8337b3f21128d0fb, 0x626fe223f5ea21c9, 0x331b17f1e09050ae, 0x92d99deddc4659ba, 0xacd463db31fe1f52 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x65ace2685a072c6d, melg._internal_state.state.list[32]);
            EXPECT_EQ(0x98d0ff43e17386ae, melg._internal_state.state.list[94]);
            EXPECT_EQ(0xe23e7fe1b4b4114d, melg._internal_state.state.list[156]);
            EXPECT_EQ(0x13671a141437aab9, melg._internal_state.state.list[218]);
            EXPECT_EQ(0x776b84c53f497613, melg._internal_state.state.list[280]);
            EXPECT_EQ(0x8ce20fd0eed71a96, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(-2);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xfaebc45a40c96857, melg._internal_state.state.list[60]);
            EXPECT_EQ(0x8f1841b5ba07c168, melg._internal_state.state.list[122]);
            EXPECT_EQ(0x0aa802900261ebcf, melg._internal_state.state.list[184]);
            EXPECT_EQ(0xf9eb62c0b405ceef, melg._internal_state.state.list[246]);
            EXPECT_EQ(0xabe17a9b9affd4c2, melg._internal_state.state.list[308]);
            EXPECT_EQ(0xbc8964c3874e4207, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x7e8303f79ca95b09, 0xf87e4b6028b477c9, 0xde8797964daeb770, 0x6e8cce9e70a2a9f2, 0x9ee9b37de0a89ea5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xcc6d17e080e97285, melg._internal_state.state.list[29]);
            EXPECT_EQ(0x3fdea865bbdfbbed, melg._internal_state.state.list[91]);
            EXPECT_EQ(0x2cb0cc39883c5d89, melg._internal_state.state.list[153]);
            EXPECT_EQ(0x5e332bff0379714a, melg._internal_state.state.list[215]);
            EXPECT_EQ(0x57262a10f0ab485f, melg._internal_state.state.list[277]);
            EXPECT_EQ(0xd143f91095514bdf, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(9);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xca06743146f19573, melg._internal_state.state.list[9]);
            EXPECT_EQ(0xbbe726b627bfc026, melg._internal_state.state.list[71]);
            EXPECT_EQ(0x92ef45675d70e361, melg._internal_state.state.list[133]);
            EXPECT_EQ(0x61e8776e94c718af, melg._internal_state.state.list[195]);
            EXPECT_EQ(0xa54ea65eec3a4297, melg._internal_state.state.list[257]);
            EXPECT_EQ(0x83a9d836b6ff6d93, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xfacf0f02813521af, 0x1147ef520865d63f, 0x3637a28147e09f5b, 0x941df6a041f2c0b7, 0x212cddcaa6f00d50 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x3d88ccec360bf807, melg._internal_state.state.list[40]);
            EXPECT_EQ(0xe79e764c6fc5228c, melg._internal_state.state.list[102]);
            EXPECT_EQ(0xbb9f50d7b2591b3e, melg._internal_state.state.list[164]);
            EXPECT_EQ(0x71b76d004c3001de, melg._internal_state.state.list[226]);
            EXPECT_EQ(0x9ef210f64b4fdda8, melg._internal_state.state.list[288]);
            EXPECT_EQ(0xc53e5ef9541a41fa, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(-11);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x00800b7214371fbc, melg._internal_state.state.list[51]);
            EXPECT_EQ(0xfc3a2ba88fa3ecba, melg._internal_state.state.list[113]);
            EXPECT_EQ(0x045cf171f7da2bed, melg._internal_state.state.list[175]);
            EXPECT_EQ(0x386f42721c805822, melg._internal_state.state.list[237]);
            EXPECT_EQ(0x2affa75258578d40, melg._internal_state.state.list[299]);
            EXPECT_EQ(0xe5f4a5f364c6cb5c, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x8e075a5f69a2cebf, 0x38d413ae0ff17926, 0x716ca8ade586a769, 0x3061d1dd35c93ba1, 0x8d0ed6b0866166dd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x0176192fa4ffc55e, melg._internal_state.state.list[20]);
            EXPECT_EQ(0x097aa6f6eb9cfa8a, melg._internal_state.state.list[82]);
            EXPECT_EQ(0xa5637705d96a4c88, melg._internal_state.state.list[144]);
            EXPECT_EQ(0x75899bcad2c51cde, melg._internal_state.state.list[206]);
            EXPECT_EQ(0xafd1097caed1df79, melg._internal_state.state.list[268]);
            EXPECT_EQ(0xe25c9349520c707a, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(17);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x6cb7d6f5a174672b, melg._internal_state.state.list[17]);
            EXPECT_EQ(0x2c3cf8448e7e649b, melg._internal_state.state.list[79]);
            EXPECT_EQ(0x079919e90964ce9c, melg._internal_state.state.list[141]);
            EXPECT_EQ(0x40694772f7c43337, melg._internal_state.state.list[203]);
            EXPECT_EQ(0x1ef76fe5e390174c, melg._internal_state.state.list[265]);
            EXPECT_EQ(0xabf67d9459639ac9, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5ab70e0e96d97c7e, 0x79793201a32bbec0, 0xf9ffd73ab650c001, 0xa73133989c7bee08, 0x6f2f64c5bb59cbe5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x2c5e59fc92494337, melg._internal_state.state.list[48]);
            EXPECT_EQ(0x30dea1e036d9d274, melg._internal_state.state.list[110]);
            EXPECT_EQ(0x9590b6fd25ab0f74, melg._internal_state.state.list[172]);
            EXPECT_EQ(0x489c95b2bd72c71d, melg._internal_state.state.list[234]);
            EXPECT_EQ(0x4c133a7331944416, melg._internal_state.state.list[296]);
            EXPECT_EQ(0x3f5422f48fd9e87d, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xc79841f4a60c9b64, melg._internal_state.state.list[61]);
            EXPECT_EQ(0x49a17debdb062ce4, melg._internal_state.state.list[123]);
            EXPECT_EQ(0xb568f29ddb496c83, melg._internal_state.state.list[185]);
            EXPECT_EQ(0x7e07ab8606a92cfc, melg._internal_state.state.list[247]);
            EXPECT_EQ(0xc4c23a6e338d6a6e, melg._internal_state.state.list[309]);
            EXPECT_EQ(0x8c3b5029dac57ba8, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xe6fc8387bf0c4793, 0x1c14b3d27dd7fbd9, 0x3319dba9ee4fc6ae, 0x81f9e8038014de15, 0x8bf4406be63716de };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x09193ec65cf7a972, melg._internal_state.state.list[30]);
            EXPECT_EQ(0xb2a8d8135941cab2, melg._internal_state.state.list[92]);
            EXPECT_EQ(0x1dc7ebca191a4f9f, melg._internal_state.state.list[154]);
            EXPECT_EQ(0x42ff9df57c595809, melg._internal_state.state.list[216]);
            EXPECT_EQ(0xd049b13564d10022, melg._internal_state.state.list[278]);
            EXPECT_EQ(0x221c86a9577b017c, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(-8870000000000000000);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xe40640323ee3c568, melg._internal_state.state.list[58]);
            EXPECT_EQ(0xaa478927b114ab8c, melg._internal_state.state.list[120]);
            EXPECT_EQ(0xe331abee50258b0a, melg._internal_state.state.list[182]);
            EXPECT_EQ(0xffaaf04c2b0d84e9, melg._internal_state.state.list[244]);
            EXPECT_EQ(0xea019e7bb100fef9, melg._internal_state.state.list[306]);
            EXPECT_EQ(0xe1b94c7c698e0d1d, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd874ed2983d06167, 0x05e3ae2fdea59a56, 0x22e239b6bb483df9, 0x731a3894faaf0b8d, 0xca9c360e9c7f3135 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xd5cd0eb557113dcc, melg._internal_state.state.list[27]);
            EXPECT_EQ(0x49bffd5ac3eb5994, melg._internal_state.state.list[89]);
            EXPECT_EQ(0xfc998cc8b8924d50, melg._internal_state.state.list[151]);
            EXPECT_EQ(0xd75164230ac29562, melg._internal_state.state.list[213]);
            EXPECT_EQ(0xf12503e3caa1c08f, melg._internal_state.state.list[275]);
            EXPECT_EQ(0x110562718dfeeac7, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(8870000000000000000);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xe1b0fb2c7e764cdb, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x170c62c362d3fc96, melg._internal_state.state.list[66]);
            EXPECT_EQ(0xbf6832f228c09d7a, melg._internal_state.state.list[128]);
            EXPECT_EQ(0xfae814b8b37adbd3, melg._internal_state.state.list[190]);
            EXPECT_EQ(0x0d069f480330275a, melg._internal_state.state.list[252]);
            EXPECT_EQ(0x396bcd270b364e2c, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x79e5462d1b6aac5a, 0x8858de2f481f0501, 0x02797563cbc2c66f, 0xb784ad410d2bc943, 0xa09db76523302e15 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xa4cf1c61dc95d35f, melg._internal_state.state.list[35]);
            EXPECT_EQ(0x017cb479fc497666, melg._internal_state.state.list[97]);
            EXPECT_EQ(0x4e2d79f6a6334c41, melg._internal_state.state.list[159]);
            EXPECT_EQ(0x0089090b37587e4f, melg._internal_state.state.list[221]);
            EXPECT_EQ(0x8dbcfb245e9443bd, melg._internal_state.state.list[283]);
            EXPECT_EQ(0x2d46bd6e1e1e7701, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(-0.357);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x5fee464f36fc42c3, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x847e1c96f63aadf2, melg._internal_state.state.list[62]);
            EXPECT_EQ(0xa3e2c96ef9705f8a, melg._internal_state.state.list[124]);
            EXPECT_EQ(0x6ab908c535def3ff, melg._internal_state.state.list[186]);
            EXPECT_EQ(0x0d99e1061e0c196b, melg._internal_state.state.list[248]);
            EXPECT_EQ(0x89bb9f67b51ff62a, melg._internal_state.state.list[310]);
            EXPECT_EQ(0x02659929a25fa4dd, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5a424dc00c26a38d, 0xc12cc1e9bb1ad975, 0x552fd21da33853cb, 0x9997dfbf7d0e2c47, 0xc27b7be6c7d9f175 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x90b323d560ed47d7, melg._internal_state.state.list[31]);
            EXPECT_EQ(0x25af3cf75b50bc87, melg._internal_state.state.list[93]);
            EXPECT_EQ(0xaba16e36fa628fad, melg._internal_state.state.list[155]);
            EXPECT_EQ(0x11890688de496012, melg._internal_state.state.list[217]);
            EXPECT_EQ(0x263040ef511d0c7e, melg._internal_state.state.list[279]);
            EXPECT_EQ(0xd3873488e8d51c37, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(8.87e+18);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xe1b0fb2c7e764cdb, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x170c62c362d3fc96, melg._internal_state.state.list[66]);
            EXPECT_EQ(0xbf6832f228c09d7a, melg._internal_state.state.list[128]);
            EXPECT_EQ(0xfae814b8b37adbd3, melg._internal_state.state.list[190]);
            EXPECT_EQ(0x0d069f480330275a, melg._internal_state.state.list[252]);
            EXPECT_EQ(0x396bcd270b364e2c, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x79e5462d1b6aac5a, 0x8858de2f481f0501, 0x02797563cbc2c66f, 0xb784ad410d2bc943, 0xa09db76523302e15 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xa4cf1c61dc95d35f, melg._internal_state.state.list[35]);
            EXPECT_EQ(0x017cb479fc497666, melg._internal_state.state.list[97]);
            EXPECT_EQ(0x4e2d79f6a6334c41, melg._internal_state.state.list[159]);
            EXPECT_EQ(0x0089090b37587e4f, melg._internal_state.state.list[221]);
            EXPECT_EQ(0x8dbcfb245e9443bd, melg._internal_state.state.list[283]);
            EXPECT_EQ(0x2d46bd6e1e1e7701, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg19937 melg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x7915a8a138203cdb, melg._internal_state.state.list[51]);
            EXPECT_EQ(0xdc4c3bc7f395318f, melg._internal_state.state.list[113]);
            EXPECT_EQ(0x7a272b00b69cf47d, melg._internal_state.state.list[175]);
            EXPECT_EQ(0x78f88cbf6920a5a7, melg._internal_state.state.list[237]);
            EXPECT_EQ(0x68f0cee92ea416ea, melg._internal_state.state.list[299]);
            EXPECT_EQ(0x01490dff1371e896, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x43447773e2629ccf, 0x62b19d677d244f82, 0xc192ddee50edc9bc, 0x1937dded1976d5d8, 0x34b5ebfc52b6bac9 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xed6e859bfa5e8dcc, melg._internal_state.state.list[20]);
            EXPECT_EQ(0x4857ad64f158cec8, melg._internal_state.state.list[82]);
            EXPECT_EQ(0x03ee4172e448a931, melg._internal_state.state.list[144]);
            EXPECT_EQ(0x21efc45aac90d366, melg._internal_state.state.list[206]);
            EXPECT_EQ(0x8843a5980d28413b, melg._internal_state.state.list[268]);
            EXPECT_EQ(0x240aa79ea5460224, melg._internal_state.state.list[311]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }


        //-- tests copy constructor
        {
            Melg19937 melg(melg_1);

            EXPECT_TRUE(melg_1._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_1._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_1._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Melg19937 melg_0;

        {
            Melg19937 melg_mem(melg_0);
            Melg19937 melg(std::move(melg_mem));

            EXPECT_TRUE(melg_0._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_0._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_0._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Melg19937 melg;

            melg = melg_1;
            EXPECT_TRUE(melg_1._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_1._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_1._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Melg19937 melg;

        {
            Melg19937 melg_mem(melg_0);
            melg = std::move(melg_mem);

            EXPECT_TRUE(melg_0._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_0._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_0._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests seed()
        melg.seed();
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_TRUE(
            std::any_of(
                melg._internal_state.state.list.cbegin(),
                melg._internal_state.state.list.cend(),
                [](auto s) { return s != 0; }
            )
        );
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);


        //-- tests seed(value)
        melg.seed(-1);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xaf9e296a11fa84c8, melg._internal_state.state.list[61]);
        EXPECT_EQ(0x4add2e2de07d40e9, melg._internal_state.state.list[123]);
        EXPECT_EQ(0x7989069ab6b2943f, melg._internal_state.state.list[185]);
        EXPECT_EQ(0xe4112727768d91ab, melg._internal_state.state.list[247]);
        EXPECT_EQ(0xa161e9bbe1f6990d, melg._internal_state.state.list[309]);
        EXPECT_EQ(0x126d6ba38db6a3d6, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(1);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1658eec67, melg._internal_state.state.list[1]);
        EXPECT_EQ(0x88b894e1401ed25b, melg._internal_state.state.list[63]);
        EXPECT_EQ(0x32647003725b6ed3, melg._internal_state.state.list[125]);
        EXPECT_EQ(0xeaeb4814b3a728d7, melg._internal_state.state.list[187]);
        EXPECT_EQ(0x3e17e6dfc3cb0bac, melg._internal_state.state.list[249]);
        EXPECT_EQ(0xe9316fe9c2c04c2d, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-2);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xfaebc45a40c96857, melg._internal_state.state.list[60]);
        EXPECT_EQ(0x8f1841b5ba07c168, melg._internal_state.state.list[122]);
        EXPECT_EQ(0x0aa802900261ebcf, melg._internal_state.state.list[184]);
        EXPECT_EQ(0xf9eb62c0b405ceef, melg._internal_state.state.list[246]);
        EXPECT_EQ(0xabe17a9b9affd4c2, melg._internal_state.state.list[308]);
        EXPECT_EQ(0xbc8964c3874e4207, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(9L);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xca06743146f19573, melg._internal_state.state.list[9]);
        EXPECT_EQ(0xbbe726b627bfc026, melg._internal_state.state.list[71]);
        EXPECT_EQ(0x92ef45675d70e361, melg._internal_state.state.list[133]);
        EXPECT_EQ(0x61e8776e94c718af, melg._internal_state.state.list[195]);
        EXPECT_EQ(0xa54ea65eec3a4297, melg._internal_state.state.list[257]);
        EXPECT_EQ(0x83a9d836b6ff6d93, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-11L);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x00800b7214371fbc, melg._internal_state.state.list[51]);
        EXPECT_EQ(0xfc3a2ba88fa3ecba, melg._internal_state.state.list[113]);
        EXPECT_EQ(0x045cf171f7da2bed, melg._internal_state.state.list[175]);
        EXPECT_EQ(0x386f42721c805822, melg._internal_state.state.list[237]);
        EXPECT_EQ(0x2affa75258578d40, melg._internal_state.state.list[299]);
        EXPECT_EQ(0xe5f4a5f364c6cb5c, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(17UL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x6cb7d6f5a174672b, melg._internal_state.state.list[17]);
        EXPECT_EQ(0x2c3cf8448e7e649b, melg._internal_state.state.list[79]);
        EXPECT_EQ(0x079919e90964ce9c, melg._internal_state.state.list[141]);
        EXPECT_EQ(0x40694772f7c43337, melg._internal_state.state.list[203]);
        EXPECT_EQ(0x1ef76fe5e390174c, melg._internal_state.state.list[265]);
        EXPECT_EQ(0xabf67d9459639ac9, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xc79841f4a60c9b64, melg._internal_state.state.list[61]);
        EXPECT_EQ(0x49a17debdb062ce4, melg._internal_state.state.list[123]);
        EXPECT_EQ(0xb568f29ddb496c83, melg._internal_state.state.list[185]);
        EXPECT_EQ(0x7e07ab8606a92cfc, melg._internal_state.state.list[247]);
        EXPECT_EQ(0xc4c23a6e338d6a6e, melg._internal_state.state.list[309]);
        EXPECT_EQ(0x8c3b5029dac57ba8, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xe40640323ee3c568, melg._internal_state.state.list[58]);
        EXPECT_EQ(0xaa478927b114ab8c, melg._internal_state.state.list[120]);
        EXPECT_EQ(0xe331abee50258b0a, melg._internal_state.state.list[182]);
        EXPECT_EQ(0xffaaf04c2b0d84e9, melg._internal_state.state.list[244]);
        EXPECT_EQ(0xea019e7bb100fef9, melg._internal_state.state.list[306]);
        EXPECT_EQ(0xe1b94c7c698e0d1d, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xe1b0fb2c7e764cdb, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x170c62c362d3fc96, melg._internal_state.state.list[66]);
        EXPECT_EQ(0xbf6832f228c09d7a, melg._internal_state.state.list[128]);
        EXPECT_EQ(0xfae814b8b37adbd3, melg._internal_state.state.list[190]);
        EXPECT_EQ(0x0d069f480330275a, melg._internal_state.state.list[252]);
        EXPECT_EQ(0x396bcd270b364e2c, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-0.357);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x5fee464f36fc42c3, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x847e1c96f63aadf2, melg._internal_state.state.list[62]);
        EXPECT_EQ(0xa3e2c96ef9705f8a, melg._internal_state.state.list[124]);
        EXPECT_EQ(0x6ab908c535def3ff, melg._internal_state.state.list[186]);
        EXPECT_EQ(0x0d99e1061e0c196b, melg._internal_state.state.list[248]);
        EXPECT_EQ(0x89bb9f67b51ff62a, melg._internal_state.state.list[310]);
        EXPECT_EQ(0x02659929a25fa4dd, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(8.87e+18);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xe1b0fb2c7e764cdb, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x170c62c362d3fc96, melg._internal_state.state.list[66]);
        EXPECT_EQ(0xbf6832f228c09d7a, melg._internal_state.state.list[128]);
        EXPECT_EQ(0xfae814b8b37adbd3, melg._internal_state.state.list[190]);
        EXPECT_EQ(0x0d069f480330275a, melg._internal_state.state.list[252]);
        EXPECT_EQ(0x396bcd270b364e2c, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x7915a8a138203cdb, melg._internal_state.state.list[51]);
        EXPECT_EQ(0xdc4c3bc7f395318f, melg._internal_state.state.list[113]);
        EXPECT_EQ(0x7a272b00b69cf47d, melg._internal_state.state.list[175]);
        EXPECT_EQ(0x78f88cbf6920a5a7, melg._internal_state.state.list[237]);
        EXPECT_EQ(0x68f0cee92ea416ea, melg._internal_state.state.list[299]);
        EXPECT_EQ(0x01490dff1371e896, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);


        //-- tests _setstate(seed_)
        melg._setstate(-1LL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xaf9e296a11fa84c8, melg._internal_state.state.list[61]);
        EXPECT_EQ(0x4add2e2de07d40e9, melg._internal_state.state.list[123]);
        EXPECT_EQ(0x7989069ab6b2943f, melg._internal_state.state.list[185]);
        EXPECT_EQ(0xe4112727768d91ab, melg._internal_state.state.list[247]);
        EXPECT_EQ(0xa161e9bbe1f6990d, melg._internal_state.state.list[309]);
        EXPECT_EQ(0x126d6ba38db6a3d6, melg._internal_state.state.list[311]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        melg.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint64_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 60) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[(Histogram::index_type)melg(ENTRIES_COUNT)]++;
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
