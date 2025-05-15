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

#include "lfib116.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsLFib116)
    {
        //-- tests empty constructor
        LFib116 lfib_1;

        EXPECT_EQ(55ULL, lfib_1._internal_state.state.list.size());
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
            LFib116 lfib(1);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x71bb54d8d101b5b9, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x6f9b6dae6f4c57a8, lfib._internal_state.state.list[14]);
            EXPECT_EQ(0x497305c5d1aab99f, lfib._internal_state.state.list[24]);
            EXPECT_EQ(0x40d6824e2ef3fc17, lfib._internal_state.state.list[34]);
            EXPECT_EQ(0xde70d1019fc66081, lfib._internal_state.state.list[44]);
            EXPECT_EQ(0x64c70b0b0c5b4a8f, lfib._internal_state.state.list[54]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x273547545209e67b, 0x24987009bf9618d4, 0x68f5121e440f357a, 0xb29808df1d36c522, 0xf95982fb2800b4c5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x273547545209e67b, lfib._internal_state.state.list[0]);
            EXPECT_EQ(0x6775dc7701564f61, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0x10e2c46865e98746, lfib._internal_state.state.list[20]);
            EXPECT_EQ(0x990cd70b12c5d084, lfib._internal_state.state.list[30]);
            EXPECT_EQ(0xdca0c749607e2c86, lfib._internal_state.state.list[40]);
            EXPECT_EQ(0x4d4673ef77ba0574, lfib._internal_state.state.list[50]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(-2);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xba56949915dcf9e9, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0xf79e3f6d8cc3172a, lfib._internal_state.state.list[11]);
            EXPECT_EQ(0x95439471158019f4, lfib._internal_state.state.list[21]);
            EXPECT_EQ(0x5575497b9a16aed3, lfib._internal_state.state.list[31]);
            EXPECT_EQ(0x19750724928a9c3d, lfib._internal_state.state.list[41]);
            EXPECT_EQ(0xfd2b90429b71400b, lfib._internal_state.state.list[51]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x4895880bd40b56f4, 0xfc0323acf8b975fb, 0xb6bc5eeb563336e4, 0x70422578cc5c03b3, 0x40acd899109c1848 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xb6bc5eeb563336e4, lfib._internal_state.state.list[2]);
            EXPECT_EQ(0x8e1f0e39007de2c6, lfib._internal_state.state.list[12]);
            EXPECT_EQ(0xf9e842708a0e97c6, lfib._internal_state.state.list[22]);
            EXPECT_EQ(0x41ac8f13e2dc7c12, lfib._internal_state.state.list[32]);
            EXPECT_EQ(0xd65cb97518bc8569, lfib._internal_state.state.list[42]);
            EXPECT_EQ(0xc1687a3bd57fdb05, lfib._internal_state.state.list[52]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(9);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x43ec2be544b589b6, lfib._internal_state.state.list[2]);
            EXPECT_EQ(0xfc5a343f8fd7765d, lfib._internal_state.state.list[12]);
            EXPECT_EQ(0x77fdc7a8429e48dd, lfib._internal_state.state.list[22]);
            EXPECT_EQ(0xed08f9be18c7912, lfib._internal_state.state.list[32]);
            EXPECT_EQ(0x6ac4b2f18eeba85c, lfib._internal_state.state.list[42]);
            EXPECT_EQ(0xbac63a617ea8789a, lfib._internal_state.state.list[52]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xaeeba46e8c879300, 0xcefe19fa693c6374, 0x1e608da8224635a4, 0xe43749170ced2597, 0x2e8cef0ba0962b15 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xe43749170ced2597, lfib._internal_state.state.list[3]);
            EXPECT_EQ(0x3d8599a83b71b57c, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x5fb6864115cf0f2a, lfib._internal_state.state.list[23]);
            EXPECT_EQ(0xda7461c2dd90abee, lfib._internal_state.state.list[33]);
            EXPECT_EQ(0xd08113911b36d0e, lfib._internal_state.state.list[43]);
            EXPECT_EQ(0x4edce344121c8333, lfib._internal_state.state.list[53]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(-11);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x46d40b90622a734b, lfib._internal_state.state.list[2]);
            EXPECT_EQ(0x16e30748223c0df1, lfib._internal_state.state.list[12]);
            EXPECT_EQ(0xd88e76c22399ab7c, lfib._internal_state.state.list[22]);
            EXPECT_EQ(0x1013c044bddb20fb, lfib._internal_state.state.list[32]);
            EXPECT_EQ(0x85cd2388593f966e, lfib._internal_state.state.list[42]);
            EXPECT_EQ(0xabda70c1e590195a, lfib._internal_state.state.list[52]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x1fef0bbe82765daa, 0xa6deaea5f03bf0c5, 0x93093fdaf27e1122, 0xb8c5e515c444ffc, 0x8ab739cb3833568d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xb8c5e515c444ffc, lfib._internal_state.state.list[3]);
            EXPECT_EQ(0xe5561582cef81501, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xea1c6ed144e1bdd7, lfib._internal_state.state.list[23]);
            EXPECT_EQ(0x4c35344a90539dd7, lfib._internal_state.state.list[33]);
            EXPECT_EQ(0xd4e74006072176fb, lfib._internal_state.state.list[43]);
            EXPECT_EQ(0x2c84a40d97d6a7c0, lfib._internal_state.state.list[53]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(17);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x808475f02ee37363, lfib._internal_state.state.list[0]);
            EXPECT_EQ(0x41515d2e8802f2a0, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xb5e817a845aa74a3, lfib._internal_state.state.list[20]);
            EXPECT_EQ(0xaa512888d31785b9, lfib._internal_state.state.list[30]);
            EXPECT_EQ(0xc239673438aab0eb, lfib._internal_state.state.list[40]);
            EXPECT_EQ(0xcb6480055ef570a3, lfib._internal_state.state.list[50]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xe12ff21d1216ff7f, 0xa5436a9b41fd172a, 0xe9a86a7f0e4a6d2f, 0x197b0fa66603153b, 0x88706bc87b5856c9 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xa5436a9b41fd172a, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x147927e3f3e07aaa, lfib._internal_state.state.list[11]);
            EXPECT_EQ(0x1ec47e3500d39ee8, lfib._internal_state.state.list[21]);
            EXPECT_EQ(0x60ab7c2ce3338c1c, lfib._internal_state.state.list[31]);
            EXPECT_EQ(0x67aba9896c5f183f, lfib._internal_state.state.list[41]);
            EXPECT_EQ(0x1e8844ccf9c484c5, lfib._internal_state.state.list[51]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xa2d419334c4667ec, lfib._internal_state.state.list[3]);
            EXPECT_EQ(0x97f6c69811cfb13b, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0xf7e9ff7484731d95, lfib._internal_state.state.list[23]);
            EXPECT_EQ(0xa3c27a0df00dbde8, lfib._internal_state.state.list[33]);
            EXPECT_EQ(0x374ca94be4ab03ac, lfib._internal_state.state.list[43]);
            EXPECT_EQ(0x597bee355c27a849, lfib._internal_state.state.list[53]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5ed07fdb39cacf94, 0x5b95dda2595d5fdb, 0xd353313c897b8aa6, 0x9a76e5c13ef92ce2, 0x42e3075999073f4b };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x42e3075999073f4b, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x380e8b5c685039cf, lfib._internal_state.state.list[14]);
            EXPECT_EQ(0x5e4d770f93e9e90a, lfib._internal_state.state.list[24]);
            EXPECT_EQ(0xf7a2cc8df2b2c4f6, lfib._internal_state.state.list[34]);
            EXPECT_EQ(0xa659ac05d6767b6f, lfib._internal_state.state.list[44]);
            EXPECT_EQ(0xfadc7d62c4f8c2f9, lfib._internal_state.state.list[54]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(-8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x637c87187035ea06, lfib._internal_state.state.list[3]);
            EXPECT_EQ(0xfbe6cd715ff52a4a, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x2b47cdf0d48354fb, lfib._internal_state.state.list[23]);
            EXPECT_EQ(0x68489cc40e3b45a7, lfib._internal_state.state.list[33]);
            EXPECT_EQ(0x81d1c195787bcaa, lfib._internal_state.state.list[43]);
            EXPECT_EQ(0xdfad412cf84777b3, lfib._internal_state.state.list[53]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xac8c33ddcf106af, 0x6b525d078f683be2, 0xef16b6654436e685, 0x1111e3764f01e6d4, 0xef730e6c98000a8c };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xef730e6c98000a8c, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0xb8c110d712c66128, lfib._internal_state.state.list[14]);
            EXPECT_EQ(0xfb0a032274aa1b, lfib._internal_state.state.list[24]);
            EXPECT_EQ(0xad955c5ddecbfcce, lfib._internal_state.state.list[34]);
            EXPECT_EQ(0x9152c6b9f4b5768e, lfib._internal_state.state.list[44]);
            EXPECT_EQ(0xaed47b30d04a3c2, lfib._internal_state.state.list[54]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(8870000000000000000);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xaf6aa8f43ebb8659, lfib._internal_state.state.list[3]);
            EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x3e2bc8837ce7ec22, lfib._internal_state.state.list[23]);
            EXPECT_EQ(0xd2c9c36a8585312d, lfib._internal_state.state.list[33]);
            EXPECT_EQ(0x4ab4eb00216eb318, lfib._internal_state.state.list[43]);
            EXPECT_EQ(0x4048712b5ed9d636, lfib._internal_state.state.list[53]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x65a06707e9b956a9, 0x71eddd40f9b76300, 0x15108f1c2bd12839, 0xf2f11a8dbc2a26fc, 0x8680178e5b0c203a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0x8680178e5b0c203a, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x74d601c8c6c14f90, lfib._internal_state.state.list[14]);
            EXPECT_EQ(0x7c374de5f5ad099a, lfib._internal_state.state.list[24]);
            EXPECT_EQ(0x438671997d6ea0a3, lfib._internal_state.state.list[34]);
            EXPECT_EQ(0xef667528f697eea3, lfib._internal_state.state.list[44]);
            EXPECT_EQ(0xfb0ee064fa29b632, lfib._internal_state.state.list[54]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(0.357);

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0x77714db9e870d702, lfib._internal_state.state.list[3]);
            EXPECT_EQ(0xee8fd4bfccca5ee3, lfib._internal_state.state.list[13]);
            EXPECT_EQ(0x57988e812351fc14, lfib._internal_state.state.list[23]);
            EXPECT_EQ(0xd394e8454bdb01ba, lfib._internal_state.state.list[33]);
            EXPECT_EQ(0x6d59ad10fc02d912, lfib._internal_state.state.list[43]);
            EXPECT_EQ(0x2a2852b20445bdd9, lfib._internal_state.state.list[53]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf0a16a2497e98a9a, 0xe9ad933c54510151, 0x7d1a2e9f963ac7fe, 0x6e2bfd0cac2bbaff, 0xa81fe325117cecda };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xa81fe325117cecda, lfib._internal_state.state.list[4]);
            EXPECT_EQ(0x1f98fc5261287247, lfib._internal_state.state.list[14]);
            EXPECT_EQ(0x7ce1cb9dcab69ba6, lfib._internal_state.state.list[24]);
            EXPECT_EQ(0xf6baaf52c3bae3fd, lfib._internal_state.state.list[34]);
            EXPECT_EQ(0x450c87aa0290d0f0, lfib._internal_state.state.list[44]);
            EXPECT_EQ(0x4e20b3e2838fd640, lfib._internal_state.state.list[54]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }
        {
            LFib116 lfib(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, lfib._internal_state.state.index);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, lfib._internal_state.state.list[0]);
            EXPECT_EQ(0x71da8c61bc0cfda9, lfib._internal_state.state.list[10]);
            EXPECT_EQ(0xed6e859bfa5e8dcc, lfib._internal_state.state.list[20]);
            EXPECT_EQ(0xd1de816e066fa972, lfib._internal_state.state.list[30]);
            EXPECT_EQ(0x5353e264bb834579, lfib._internal_state.state.list[40]);
            EXPECT_EQ(0x5ba1c1d335e210df, lfib._internal_state.state.list[50]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xaf9d9d5b766f1e22, 0xa4d3afb8f194466e, 0x6630a6ccb50e9bd6, 0xb494e6dab0ecd8d7, 0xb6fc71b91c97846a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, lfib.next());

            EXPECT_EQ(5, lfib._internal_state.state.index);
            EXPECT_EQ(0xa4d3afb8f194466e, lfib._internal_state.state.list[1]);
            EXPECT_EQ(0x8808168a65259cb5, lfib._internal_state.state.list[11]);
            EXPECT_EQ(0x84a75e4601ce1330, lfib._internal_state.state.list[21]);
            EXPECT_EQ(0xb83e988fc0cd7c45, lfib._internal_state.state.list[31]);
            EXPECT_EQ(0x3b598c3790a16243, lfib._internal_state.state.list[41]);
            EXPECT_EQ(0x7915a8a138203cdb, lfib._internal_state.state.list[51]);
            EXPECT_FALSE(lfib._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);
        }

        EXPECT_THROW(LFib116(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(LFib116(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            LFib116 lfib(lfib_1);

            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move constructor
        LFib116 lfib_0;

        {
            LFib116 lfib_mem(lfib_0);
            LFib116 lfib(std::move(lfib_mem));

            EXPECT_TRUE(lfib_0._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_0._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_0._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            LFib116 lfib;

            lfib = lfib_1;
            EXPECT_TRUE(lfib_1._internal_state.state == lfib._internal_state.state);
            EXPECT_EQ(lfib_1._internal_state.gauss_next, lfib._internal_state.gauss_next);
            EXPECT_EQ(lfib_1._internal_state.gauss_valid, lfib._internal_state.gauss_valid);
        }


        //-- tests move assignement
        LFib116 lfib;

        {
            LFib116 lfib_mem(lfib_0);
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
        EXPECT_EQ(0x382ff84cb27281e9, lfib._internal_state.state.list[2]);
        EXPECT_EQ(0x1c9558bd006badb, lfib._internal_state.state.list[12]);
        EXPECT_EQ(0x78a0a3eb16c17603, lfib._internal_state.state.list[22]);
        EXPECT_EQ(0x69d22506dd4562e7, lfib._internal_state.state.list[32]);
        EXPECT_EQ(0xbe2af7de053863b, lfib._internal_state.state.list[42]);
        EXPECT_EQ(0xbca720bf33d872b2, lfib._internal_state.state.list[52]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(1);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x71bb54d8d101b5b9, lfib._internal_state.state.list[4]);
        EXPECT_EQ(0x6f9b6dae6f4c57a8, lfib._internal_state.state.list[14]);
        EXPECT_EQ(0x497305c5d1aab99f, lfib._internal_state.state.list[24]);
        EXPECT_EQ(0x40d6824e2ef3fc17, lfib._internal_state.state.list[34]);
        EXPECT_EQ(0xde70d1019fc66081, lfib._internal_state.state.list[44]);
        EXPECT_EQ(0x64c70b0b0c5b4a8f, lfib._internal_state.state.list[54]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-2);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xba56949915dcf9e9, lfib._internal_state.state.list[1]);
        EXPECT_EQ(0xf79e3f6d8cc3172a, lfib._internal_state.state.list[11]);
        EXPECT_EQ(0x95439471158019f4, lfib._internal_state.state.list[21]);
        EXPECT_EQ(0x5575497b9a16aed3, lfib._internal_state.state.list[31]);
        EXPECT_EQ(0x19750724928a9c3d, lfib._internal_state.state.list[41]);
        EXPECT_EQ(0xfd2b90429b71400b, lfib._internal_state.state.list[51]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(9L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x43ec2be544b589b6, lfib._internal_state.state.list[2]);
        EXPECT_EQ(0xfc5a343f8fd7765d, lfib._internal_state.state.list[12]);
        EXPECT_EQ(0x77fdc7a8429e48dd, lfib._internal_state.state.list[22]);
        EXPECT_EQ(0xed08f9be18c7912, lfib._internal_state.state.list[32]);
        EXPECT_EQ(0x6ac4b2f18eeba85c, lfib._internal_state.state.list[42]);
        EXPECT_EQ(0xbac63a617ea8789a, lfib._internal_state.state.list[52]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-11L);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x46d40b90622a734b, lfib._internal_state.state.list[2]);
        EXPECT_EQ(0x16e30748223c0df1, lfib._internal_state.state.list[12]);
        EXPECT_EQ(0xd88e76c22399ab7c, lfib._internal_state.state.list[22]);
        EXPECT_EQ(0x1013c044bddb20fb, lfib._internal_state.state.list[32]);
        EXPECT_EQ(0x85cd2388593f966e, lfib._internal_state.state.list[42]);
        EXPECT_EQ(0xabda70c1e590195a, lfib._internal_state.state.list[52]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(17UL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x808475f02ee37363, lfib._internal_state.state.list[0]);
        EXPECT_EQ(0x41515d2e8802f2a0, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0xb5e817a845aa74a3, lfib._internal_state.state.list[20]);
        EXPECT_EQ(0xaa512888d31785b9, lfib._internal_state.state.list[30]);
        EXPECT_EQ(0xc239673438aab0eb, lfib._internal_state.state.list[40]);
        EXPECT_EQ(0xcb6480055ef570a3, lfib._internal_state.state.list[50]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xa2d419334c4667ec, lfib._internal_state.state.list[3]);
        EXPECT_EQ(0x97f6c69811cfb13b, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0xf7e9ff7484731d95, lfib._internal_state.state.list[23]);
        EXPECT_EQ(0xa3c27a0df00dbde8, lfib._internal_state.state.list[33]);
        EXPECT_EQ(0x374ca94be4ab03ac, lfib._internal_state.state.list[43]);
        EXPECT_EQ(0x597bee355c27a849, lfib._internal_state.state.list[53]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x637c87187035ea06, lfib._internal_state.state.list[3]);
        EXPECT_EQ(0xfbe6cd715ff52a4a, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x2b47cdf0d48354fb, lfib._internal_state.state.list[23]);
        EXPECT_EQ(0x68489cc40e3b45a7, lfib._internal_state.state.list[33]);
        EXPECT_EQ(0x81d1c195787bcaa, lfib._internal_state.state.list[43]);
        EXPECT_EQ(0xdfad412cf84777b3, lfib._internal_state.state.list[53]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xaf6aa8f43ebb8659, lfib._internal_state.state.list[3]);
        EXPECT_EQ(0x39390f80db89e31d, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x3e2bc8837ce7ec22, lfib._internal_state.state.list[23]);
        EXPECT_EQ(0xd2c9c36a8585312d, lfib._internal_state.state.list[33]);
        EXPECT_EQ(0x4ab4eb00216eb318, lfib._internal_state.state.list[43]);
        EXPECT_EQ(0x4048712b5ed9d636, lfib._internal_state.state.list[53]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(0.357);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x77714db9e870d702, lfib._internal_state.state.list[3]);
        EXPECT_EQ(0xee8fd4bfccca5ee3, lfib._internal_state.state.list[13]);
        EXPECT_EQ(0x57988e812351fc14, lfib._internal_state.state.list[23]);
        EXPECT_EQ(0xd394e8454bdb01ba, lfib._internal_state.state.list[33]);
        EXPECT_EQ(0x6d59ad10fc02d912, lfib._internal_state.state.list[43]);
        EXPECT_EQ(0x2a2852b20445bdd9, lfib._internal_state.state.list[53]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        lfib.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, lfib._internal_state.state.list[0]);
        EXPECT_EQ(0x71da8c61bc0cfda9, lfib._internal_state.state.list[10]);
        EXPECT_EQ(0xed6e859bfa5e8dcc, lfib._internal_state.state.list[20]);
        EXPECT_EQ(0xd1de816e066fa972, lfib._internal_state.state.list[30]);
        EXPECT_EQ(0x5353e264bb834579, lfib._internal_state.state.list[40]);
        EXPECT_EQ(0x5ba1c1d335e210df, lfib._internal_state.state.list[50]);
        EXPECT_FALSE(lfib._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, lfib._internal_state.gauss_next);

        EXPECT_THROW(lfib.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(lfib.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        lfib._setstate(-1LL);
        EXPECT_EQ(0, lfib._internal_state.state.index);
        EXPECT_EQ(0x382ff84cb27281e9, lfib._internal_state.state.list[2]);
        EXPECT_EQ(0x1c9558bd006badb, lfib._internal_state.state.list[12]);
        EXPECT_EQ(0x78a0a3eb16c17603, lfib._internal_state.state.list[22]);
        EXPECT_EQ(0x69d22506dd4562e7, lfib._internal_state.state.list[32]);
        EXPECT_EQ(0xbe2af7de053863b, lfib._internal_state.state.list[42]);
        EXPECT_EQ(0xbca720bf33d872b2, lfib._internal_state.state.list[52]);
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
