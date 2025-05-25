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

#include "well19937c.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsWell19937c)
    {
        //-- tests empty constructor
        Well19937c wll_1;

        EXPECT_EQ(624ULL, wll_1._internal_state.state.list.size());
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
            Well19937c wll(1);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x764176e3, wll._internal_state.state.list[104]);
            EXPECT_EQ(0x116a7537, wll._internal_state.state.list[207]);
            EXPECT_EQ(0xafff2161, wll._internal_state.state.list[310]);
            EXPECT_EQ(0x4cdddfb3, wll._internal_state.state.list[413]);
            EXPECT_EQ(0xc9788c94, wll._internal_state.state.list[516]);
            EXPECT_EQ(0x2a93b073, wll._internal_state.state.list[619]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc67d4efe, 0x5b97a4c0, 0xe941f25a, 0xdb3d4e0c, 0xf2a50b0e };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0x536000f4, wll._internal_state.state.list[52]);
            EXPECT_EQ(0x49e92cf9, wll._internal_state.state.list[155]);
            EXPECT_EQ(0x7d350fc5, wll._internal_state.state.list[258]);
            EXPECT_EQ(0x94b16b71, wll._internal_state.state.list[361]);
            EXPECT_EQ(0x614b0464, wll._internal_state.state.list[464]);
            EXPECT_EQ(0x0f252671, wll._internal_state.state.list[567]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(-2);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x4e2f3186, wll._internal_state.state.list[106]);
            EXPECT_EQ(0x3175c25a, wll._internal_state.state.list[209]);
            EXPECT_EQ(0x19880db1, wll._internal_state.state.list[312]);
            EXPECT_EQ(0x9f1b299e, wll._internal_state.state.list[415]);
            EXPECT_EQ(0x0537578d, wll._internal_state.state.list[518]);
            EXPECT_EQ(0xf2fd44a7, wll._internal_state.state.list[621]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x989526f8, 0x272a666c, 0x1d3e5582, 0x2d3104e0, 0xd859e67b };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0xbcda6015, wll._internal_state.state.list[54]);
            EXPECT_EQ(0x975fb291, wll._internal_state.state.list[157]);
            EXPECT_EQ(0x3a5ce3c7, wll._internal_state.state.list[260]);
            EXPECT_EQ(0xa7d5ef9e, wll._internal_state.state.list[363]);
            EXPECT_EQ(0x7b7df1a0, wll._internal_state.state.list[466]);
            EXPECT_EQ(0x2b9b659a, wll._internal_state.state.list[569]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(9);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xca067431, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x9ef45b9a, wll._internal_state.state.list[112]);
            EXPECT_EQ(0x37070ce0, wll._internal_state.state.list[215]);
            EXPECT_EQ(0x6b994d20, wll._internal_state.state.list[318]);
            EXPECT_EQ(0xb8ae8668, wll._internal_state.state.list[421]);
            EXPECT_EQ(0xccdbb235, wll._internal_state.state.list[524]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x08bbb079, 0x5a4b002d, 0xd0890fff, 0x76738039, 0x412a3482 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0x251c72af, wll._internal_state.state.list[60]);
            EXPECT_EQ(0xac115ff4, wll._internal_state.state.list[163]);
            EXPECT_EQ(0x2a579bc3, wll._internal_state.state.list[266]);
            EXPECT_EQ(0x3877e7ae, wll._internal_state.state.list[369]);
            EXPECT_EQ(0xea979fa3, wll._internal_state.state.list[472]);
            EXPECT_EQ(0xc8d1c6d9, wll._internal_state.state.list[575]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(-11);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x4a1a27c1, wll._internal_state.state.list[97]);
            EXPECT_EQ(0xf2ad38bd, wll._internal_state.state.list[200]);
            EXPECT_EQ(0x3b823709, wll._internal_state.state.list[303]);
            EXPECT_EQ(0x6865e9c6, wll._internal_state.state.list[406]);
            EXPECT_EQ(0xdc360235, wll._internal_state.state.list[509]);
            EXPECT_EQ(0xf4340cc6, wll._internal_state.state.list[612]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x2eacc470, 0x11286db2, 0xc12a620d, 0xec45b0b2, 0xe4ec37bb };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0xaaf89ddd, wll._internal_state.state.list[45]);
            EXPECT_EQ(0x5a168de1, wll._internal_state.state.list[148]);
            EXPECT_EQ(0xbc7b3d87, wll._internal_state.state.list[251]);
            EXPECT_EQ(0x6bf49c20, wll._internal_state.state.list[354]);
            EXPECT_EQ(0xc0b49e60, wll._internal_state.state.list[457]);
            EXPECT_EQ(0x62f7dc5e, wll._internal_state.state.list[560]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(17);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x6cb7d6f5, wll._internal_state.state.list[17]);
            EXPECT_EQ(0xebb58674, wll._internal_state.state.list[120]);
            EXPECT_EQ(0xdfc0e933, wll._internal_state.state.list[223]);
            EXPECT_EQ(0xc86f3f8a, wll._internal_state.state.list[326]);
            EXPECT_EQ(0xbac8a310, wll._internal_state.state.list[429]);
            EXPECT_EQ(0x9de9d6f7, wll._internal_state.state.list[532]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd297b603, 0xf1d0892d, 0x18312805, 0xdc5d0ef6, 0x5bfd86c5 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0x585554b9, wll._internal_state.state.list[68]);
            EXPECT_EQ(0x911227ec, wll._internal_state.state.list[171]);
            EXPECT_EQ(0x64582ae5, wll._internal_state.state.list[274]);
            EXPECT_EQ(0x4c4f8528, wll._internal_state.state.list[377]);
            EXPECT_EQ(0x32cae455, wll._internal_state.state.list[480]);
            EXPECT_EQ(0x887918a8, wll._internal_state.state.list[583]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xaf9321d7, wll._internal_state.state.list[87]);
            EXPECT_EQ(0x19f5a875, wll._internal_state.state.list[190]);
            EXPECT_EQ(0xf2805263, wll._internal_state.state.list[293]);
            EXPECT_EQ(0x98dd341e, wll._internal_state.state.list[396]);
            EXPECT_EQ(0xe9512ec1, wll._internal_state.state.list[499]);
            EXPECT_EQ(0x2736fee2, wll._internal_state.state.list[602]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xec5c8d8b, 0x79358173, 0xe15b206b, 0x4a10e5e0, 0x3a0973cc };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0x41a2ba70, wll._internal_state.state.list[35]);
            EXPECT_EQ(0x42808a00, wll._internal_state.state.list[138]);
            EXPECT_EQ(0x922a5840, wll._internal_state.state.list[241]);
            EXPECT_EQ(0xfb76130a, wll._internal_state.state.list[344]);
            EXPECT_EQ(0xb910bdc8, wll._internal_state.state.list[447]);
            EXPECT_EQ(0xda35f666, wll._internal_state.state.list[550]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(-8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xbad5b1a4, wll._internal_state.state.list[40]);
            EXPECT_EQ(0xf06ea580, wll._internal_state.state.list[143]);
            EXPECT_EQ(0x0fb469ce, wll._internal_state.state.list[246]);
            EXPECT_EQ(0xcee933c0, wll._internal_state.state.list[349]);
            EXPECT_EQ(0x2db9dbaf, wll._internal_state.state.list[452]);
            EXPECT_EQ(0xcac8d27f, wll._internal_state.state.list[555]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x91b59fab, 0xd2e082fe, 0x5bffd019, 0xee6c94b1, 0xb65d1c38 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0xaee160eb, wll._internal_state.state.list[91]);
            EXPECT_EQ(0x2d226f32, wll._internal_state.state.list[194]);
            EXPECT_EQ(0x0ea6806f, wll._internal_state.state.list[297]);
            EXPECT_EQ(0xc9ec22eb, wll._internal_state.state.list[400]);
            EXPECT_EQ(0x2f3ece87, wll._internal_state.state.list[503]);
            EXPECT_EQ(0x3a38a7be, wll._internal_state.state.list[606]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x1870948e, wll._internal_state.state.list[68]);
            EXPECT_EQ(0x417a54c5, wll._internal_state.state.list[171]);
            EXPECT_EQ(0xad464210, wll._internal_state.state.list[274]);
            EXPECT_EQ(0xb3c666a4, wll._internal_state.state.list[377]);
            EXPECT_EQ(0x5ca8aae2, wll._internal_state.state.list[480]);
            EXPECT_EQ(0xb6794803, wll._internal_state.state.list[583]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa4153969, 0xc2e4701c, 0xa533ba6b, 0xfa1957a0, 0x6a5d0ca0 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0xcbe9dce4, wll._internal_state.state.list[16]);
            EXPECT_EQ(0x4fb8ba65, wll._internal_state.state.list[119]);
            EXPECT_EQ(0x1f2d5ee5, wll._internal_state.state.list[222]);
            EXPECT_EQ(0xf6688241, wll._internal_state.state.list[325]);
            EXPECT_EQ(0x72c13f3e, wll._internal_state.state.list[428]);
            EXPECT_EQ(0x4936be6a, wll._internal_state.state.list[531]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(0.357);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
            EXPECT_EQ(0x1d890ddc, wll._internal_state.state.list[103]);
            EXPECT_EQ(0x95c03c83, wll._internal_state.state.list[206]);
            EXPECT_EQ(0x92964cbc, wll._internal_state.state.list[309]);
            EXPECT_EQ(0xd24c1d7d, wll._internal_state.state.list[412]);
            EXPECT_EQ(0x9993f3e8, wll._internal_state.state.list[515]);
            EXPECT_EQ(0xeb7f4250, wll._internal_state.state.list[618]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x99ebdc45, 0xdf2354b1, 0xc8ebe74b, 0x07c4502d, 0x56530c36 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0x2ae121f0, wll._internal_state.state.list[51]);
            EXPECT_EQ(0xa16ff169, wll._internal_state.state.list[154]);
            EXPECT_EQ(0x88cb7c17, wll._internal_state.state.list[257]);
            EXPECT_EQ(0x47c5abfc, wll._internal_state.state.list[360]);
            EXPECT_EQ(0xdad46cf9, wll._internal_state.state.list[463]);
            EXPECT_EQ(0x19636935, wll._internal_state.state.list[566]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well19937c wll(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x06eb55fc, wll._internal_state.state.list[57]);
            EXPECT_EQ(0xf5f8ddc6, wll._internal_state.state.list[160]);
            EXPECT_EQ(0x79406d2f, wll._internal_state.state.list[263]);
            EXPECT_EQ(0x92eefa95, wll._internal_state.state.list[366]);
            EXPECT_EQ(0xba090bad, wll._internal_state.state.list[469]);
            EXPECT_EQ(0x95f11813, wll._internal_state.state.list[572]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x4b286302, 0x7fc21fc6, 0x9a2df61e, 0x23fd8b6f, 0x9c3adebb };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(619, wll._internal_state.state.index);
            EXPECT_EQ(0x082cfe88, wll._internal_state.state.list[5]);
            EXPECT_EQ(0xd3fa02d3, wll._internal_state.state.list[108]);
            EXPECT_EQ(0x037c658f, wll._internal_state.state.list[211]);
            EXPECT_EQ(0xc4901e77, wll._internal_state.state.list[314]);
            EXPECT_EQ(0xcee14334, wll._internal_state.state.list[417]);
            EXPECT_EQ(0x2a1089e0, wll._internal_state.state.list[520]);
            EXPECT_EQ(0x504e1cc6, wll._internal_state.state.list[623]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }

        EXPECT_THROW(Well19937c(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Well19937c(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Well19937c wll(wll_1);

            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Well19937c wll_0;

        {
            Well19937c wll_mem(wll_0);
            Well19937c wll(std::move(wll_mem));

            EXPECT_TRUE(wll_0._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_0._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_0._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Well19937c wll;

            wll = wll_1;
            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Well19937c wll;

        {
            Well19937c wll_mem(wll_0);
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
        EXPECT_EQ(0xc91b5fe5, wll._internal_state.state.list[107]);
        EXPECT_EQ(0x2703436a, wll._internal_state.state.list[210]);
        EXPECT_EQ(0x32fa728b, wll._internal_state.state.list[313]);
        EXPECT_EQ(0x987ba755, wll._internal_state.state.list[416]);
        EXPECT_EQ(0x6a71fc3a, wll._internal_state.state.list[519]);
        EXPECT_EQ(0x9e44cf1e, wll._internal_state.state.list[622]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0xcb09592a, 0xc87590c8, 0x6c16c427, 0xe5b66cb7, 0x1539d60e };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, wll.next());
        EXPECT_EQ(619, wll._internal_state.state.index);
        EXPECT_EQ(0x4b39ba29, wll._internal_state.state.list[55]);
        EXPECT_EQ(0x4e2df9dd, wll._internal_state.state.list[158]);
        EXPECT_EQ(0x379406a6, wll._internal_state.state.list[261]);
        EXPECT_EQ(0x9adacbcc, wll._internal_state.state.list[364]);
        EXPECT_EQ(0x83cb4bb2, wll._internal_state.state.list[467]);
        EXPECT_EQ(0x76a38f98, wll._internal_state.state.list[570]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(1);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x764176e3, wll._internal_state.state.list[104]);
        EXPECT_EQ(0x116a7537, wll._internal_state.state.list[207]);
        EXPECT_EQ(0xafff2161, wll._internal_state.state.list[310]);
        EXPECT_EQ(0x4cdddfb3, wll._internal_state.state.list[413]);
        EXPECT_EQ(0xc9788c94, wll._internal_state.state.list[516]);
        EXPECT_EQ(0x2a93b073, wll._internal_state.state.list[619]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-2);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x4e2f3186, wll._internal_state.state.list[106]);
        EXPECT_EQ(0x3175c25a, wll._internal_state.state.list[209]);
        EXPECT_EQ(0x19880db1, wll._internal_state.state.list[312]);
        EXPECT_EQ(0x9f1b299e, wll._internal_state.state.list[415]);
        EXPECT_EQ(0x0537578d, wll._internal_state.state.list[518]);
        EXPECT_EQ(0xf2fd44a7, wll._internal_state.state.list[621]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(9L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xca067431, wll._internal_state.state.list[9]);
        EXPECT_EQ(0x9ef45b9a, wll._internal_state.state.list[112]);
        EXPECT_EQ(0x37070ce0, wll._internal_state.state.list[215]);
        EXPECT_EQ(0x6b994d20, wll._internal_state.state.list[318]);
        EXPECT_EQ(0xb8ae8668, wll._internal_state.state.list[421]);
        EXPECT_EQ(0xccdbb235, wll._internal_state.state.list[524]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-11L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x4a1a27c1, wll._internal_state.state.list[97]);
        EXPECT_EQ(0xf2ad38bd, wll._internal_state.state.list[200]);
        EXPECT_EQ(0x3b823709, wll._internal_state.state.list[303]);
        EXPECT_EQ(0x6865e9c6, wll._internal_state.state.list[406]);
        EXPECT_EQ(0xdc360235, wll._internal_state.state.list[509]);
        EXPECT_EQ(0xf4340cc6, wll._internal_state.state.list[612]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(17UL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x6cb7d6f5, wll._internal_state.state.list[17]);
        EXPECT_EQ(0xebb58674, wll._internal_state.state.list[120]);
        EXPECT_EQ(0xdfc0e933, wll._internal_state.state.list[223]);
        EXPECT_EQ(0xc86f3f8a, wll._internal_state.state.list[326]);
        EXPECT_EQ(0xbac8a310, wll._internal_state.state.list[429]);
        EXPECT_EQ(0x9de9d6f7, wll._internal_state.state.list[532]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xaf9321d7, wll._internal_state.state.list[87]);
        EXPECT_EQ(0x19f5a875, wll._internal_state.state.list[190]);
        EXPECT_EQ(0xf2805263, wll._internal_state.state.list[293]);
        EXPECT_EQ(0x98dd341e, wll._internal_state.state.list[396]);
        EXPECT_EQ(0xe9512ec1, wll._internal_state.state.list[499]);
        EXPECT_EQ(0x2736fee2, wll._internal_state.state.list[602]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xbad5b1a4, wll._internal_state.state.list[40]);
        EXPECT_EQ(0xf06ea580, wll._internal_state.state.list[143]);
        EXPECT_EQ(0x0fb469ce, wll._internal_state.state.list[246]);
        EXPECT_EQ(0xcee933c0, wll._internal_state.state.list[349]);
        EXPECT_EQ(0x2db9dbaf, wll._internal_state.state.list[452]);
        EXPECT_EQ(0xcac8d27f, wll._internal_state.state.list[555]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x1870948e, wll._internal_state.state.list[68]);
        EXPECT_EQ(0x417a54c5, wll._internal_state.state.list[171]);
        EXPECT_EQ(0xad464210, wll._internal_state.state.list[274]);
        EXPECT_EQ(0xb3c666a4, wll._internal_state.state.list[377]);
        EXPECT_EQ(0x5ca8aae2, wll._internal_state.state.list[480]);
        EXPECT_EQ(0xb6794803, wll._internal_state.state.list[583]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0.357);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
        EXPECT_EQ(0x1d890ddc, wll._internal_state.state.list[103]);
        EXPECT_EQ(0x95c03c83, wll._internal_state.state.list[206]);
        EXPECT_EQ(0x92964cbc, wll._internal_state.state.list[309]);
        EXPECT_EQ(0xd24c1d7d, wll._internal_state.state.list[412]);
        EXPECT_EQ(0x9993f3e8, wll._internal_state.state.list[515]);
        EXPECT_EQ(0xeb7f4250, wll._internal_state.state.list[618]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x06eb55fc, wll._internal_state.state.list[57]);
        EXPECT_EQ(0xf5f8ddc6, wll._internal_state.state.list[160]);
        EXPECT_EQ(0x79406d2f, wll._internal_state.state.list[263]);
        EXPECT_EQ(0x92eefa95, wll._internal_state.state.list[366]);
        EXPECT_EQ(0xba090bad, wll._internal_state.state.list[469]);
        EXPECT_EQ(0x95f11813, wll._internal_state.state.list[572]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        EXPECT_THROW(wll.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(wll.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        wll._setstate(-1LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xc91b5fe5, wll._internal_state.state.list[107]);
        EXPECT_EQ(0x2703436a, wll._internal_state.state.list[210]);
        EXPECT_EQ(0x32fa728b, wll._internal_state.state.list[313]);
        EXPECT_EQ(0x987ba755, wll._internal_state.state.list[416]);
        EXPECT_EQ(0x6a71fc3a, wll._internal_state.state.list[519]);
        EXPECT_EQ(0x9e44cf1e, wll._internal_state.state.list[622]);
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
