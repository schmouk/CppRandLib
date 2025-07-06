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

#include "well512a.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsWell512a)
    {
        //-- tests empty constructor
        Well512a wll_1;

        EXPECT_EQ(16ULL, wll_1._internal_state.state.list.size());
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
            Well512a wll(1);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x71bb54d8, wll._internal_state.state.list[4]);
            EXPECT_EQ(0x85e7bb0f, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x6775dc77, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x87b341d6, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x50e458df, 0x23583e39, 0x83dab7be, 0x0a68c750, 0x7d8e1823 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0xf893a2ee, wll._internal_state.state.list[2]);
            EXPECT_EQ(0xc34d0bff, wll._internal_state.state.list[5]);
            EXPECT_EQ(0x491718de, wll._internal_state.state.list[8]);
            EXPECT_EQ(0xabeee307, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x83dab7be, wll._internal_state.state.list[14]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(-2);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xf3203e90, wll._internal_state.state.list[0]);
            EXPECT_EQ(0x1ef156bb, wll._internal_state.state.list[3]);
            EXPECT_EQ(0xea909a92, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x19fbbd62, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x8e1f0e39, wll._internal_state.state.list[12]);
            EXPECT_EQ(0x52ef36bb, wll._internal_state.state.list[15]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb9baefce, 0x9f752805, 0x7adbba6a, 0x935c06cc, 0xd78df6ca };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0xba569499, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x78428415, wll._internal_state.state.list[4]);
            EXPECT_EQ(0x1e2b53fb, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x2b724bbb, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x935c06cc, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(9);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xc02d8a5e, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x4336b378, wll._internal_state.state.list[4]);
            EXPECT_EQ(0xfbc9d618, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x96f90d64, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x3d8599a8, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc71fffa9, 0x646807c5, 0x534deafc, 0xa71f429f, 0x21745d78 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0x43ec2be5, wll._internal_state.state.list[2]);
            EXPECT_EQ(0x1d56f4a5, wll._internal_state.state.list[5]);
            EXPECT_EQ(0x3812b742, wll._internal_state.state.list[8]);
            EXPECT_EQ(0x464e83e8, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x534deafc, wll._internal_state.state.list[14]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(-11);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x96caee61, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x69e6fff0, wll._internal_state.state.list[4]);
            EXPECT_EQ(0xd830cf06, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x17b13790, wll._internal_state.state.list[10]);
            EXPECT_EQ(0xe5561582, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xfa1f12d2, 0xbc4e9c74, 0x8c3fec08, 0x9bcb6dc7, 0xb807c34d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0x46d40b90, wll._internal_state.state.list[2]);
            EXPECT_EQ(0xdbc92595, wll._internal_state.state.list[5]);
            EXPECT_EQ(0x87422545, wll._internal_state.state.list[8]);
            EXPECT_EQ(0x63e2dc23, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x8c3fec08, wll._internal_state.state.list[14]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(17);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x6434ff62, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x046b1664, wll._internal_state.state.list[4]);
            EXPECT_EQ(0xa74db96e, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x41515d2e, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x826229cb, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd698762f, 0x8ab54d5a, 0x0076809c, 0xcf192450, 0x1b543e7f };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0x540d6c37, wll._internal_state.state.list[2]);
            EXPECT_EQ(0x14db9121, wll._internal_state.state.list[5]);
            EXPECT_EQ(0x067c2452, wll._internal_state.state.list[8]);
            EXPECT_EQ(0xfbf0bf1c, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x0076809c, wll._internal_state.state.list[14]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xd573529b, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x01404ce9, wll._internal_state.state.list[4]);
            EXPECT_EQ(0x8931545f, wll._internal_state.state.list[7]);
            EXPECT_EQ(0xcdb8c9cd, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x97f6c698, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xff43fee0, 0xab5a9c3d, 0x7fa6da51, 0xd6c5abfb, 0x79f26a62 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0x2f90b72e, wll._internal_state.state.list[2]);
            EXPECT_EQ(0x14bc574c, wll._internal_state.state.list[5]);
            EXPECT_EQ(0xf984db4e, wll._internal_state.state.list[8]);
            EXPECT_EQ(0x07bd2fcf, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x7fa6da51, wll._internal_state.state.list[14]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(-8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x48bbc5b8, wll._internal_state.state.list[0]);
            EXPECT_EQ(0x637c8718, wll._internal_state.state.list[3]);
            EXPECT_EQ(0x95d0c8e5, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x5f29354e, wll._internal_state.state.list[9]);
            EXPECT_EQ(0xba17e257, wll._internal_state.state.list[12]);
            EXPECT_EQ(0xfeb66399, wll._internal_state.state.list[15]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x4f7f58a1, 0x6acb0632, 0x2ee82f06, 0xace8c2cf, 0xd95aad19 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0xe2fbc345, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x2a03b9af, wll._internal_state.state.list[4]);
            EXPECT_EQ(0xe6d25024, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x4592e2e8, wll._internal_state.state.list[10]);
            EXPECT_EQ(0xace8c2cf, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(8870000000000000000);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xeede014d, wll._internal_state.state.list[0]);
            EXPECT_EQ(0xaf6aa8f4, wll._internal_state.state.list[3]);
            EXPECT_EQ(0x1408795f, wll._internal_state.state.list[6]);
            EXPECT_EQ(0x04443a10, wll._internal_state.state.list[9]);
            EXPECT_EQ(0xc6afab58, wll._internal_state.state.list[12]);
            EXPECT_EQ(0x4a80a9e7, wll._internal_state.state.list[15]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x552ebc5a, 0x1a8ae025, 0x151069fe, 0x69b02770, 0x3b636d5b };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0xa6eb6466, wll._internal_state.state.list[1]);
            EXPECT_EQ(0xe1b0fb2c, wll._internal_state.state.list[4]);
            EXPECT_EQ(0xe0c07d94, wll._internal_state.state.list[7]);
            EXPECT_EQ(0xa92d263b, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x69b02770, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(0.357);

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
            EXPECT_EQ(0x77714db9, wll._internal_state.state.list[3]);
            EXPECT_EQ(0x1c4d126a, wll._internal_state.state.list[6]);
            EXPECT_EQ(0xe8f9525b, wll._internal_state.state.list[9]);
            EXPECT_EQ(0x102227a3, wll._internal_state.state.list[12]);
            EXPECT_EQ(0xd619e21c, wll._internal_state.state.list[15]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xf5955f81, 0x22322858, 0xaaeaa9ca, 0x09d68741, 0x5375bd2b };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0x954faf5a, wll._internal_state.state.list[1]);
            EXPECT_EQ(0xa3aac457, wll._internal_state.state.list[4]);
            EXPECT_EQ(0xe6b53661, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x0df3d30d, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x09d68741, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }
        {
            Well512a wll(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, wll._internal_state.state.index);
            EXPECT_EQ(0xec779c36, wll._internal_state.state.list[1]);
            EXPECT_EQ(0x260ffb02, wll._internal_state.state.list[4]);
            EXPECT_EQ(0xd7c07017, wll._internal_state.state.list[7]);
            EXPECT_EQ(0x71da8c61, wll._internal_state.state.list[10]);
            EXPECT_EQ(0x69f17ee1, wll._internal_state.state.list[13]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x73b86b48, 0xd42a0729, 0x081bc819, 0xca482c32, 0x927554e8 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, wll.next());

            EXPECT_EQ(11, wll._internal_state.state.index);
            EXPECT_EQ(0xfed9eeb4, wll._internal_state.state.list[2]);
            EXPECT_EQ(0x082cfe88, wll._internal_state.state.list[5]);
            EXPECT_EQ(0x4f6d6a27, wll._internal_state.state.list[8]);
            EXPECT_EQ(0x25f9bab5, wll._internal_state.state.list[11]);
            EXPECT_EQ(0x081bc819, wll._internal_state.state.list[14]);

            EXPECT_FALSE(wll._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        }

        EXPECT_THROW(Well512a(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Well512a(1.0001), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Well512a wll(wll_1);

            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Well512a wll_0;

        {
            Well512a wll_mem(wll_0);
            Well512a wll(std::move(wll_mem));

            EXPECT_TRUE(wll_0._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_0._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_0._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Well512a wll;

            wll = wll_1;
            EXPECT_TRUE(wll_1._internal_state.state == wll._internal_state.state);
            EXPECT_EQ(wll_1._internal_state.gauss_next, wll._internal_state.gauss_next);
            EXPECT_EQ(wll_1._internal_state.gauss_valid, wll._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Well512a wll;

        {
            Well512a wll_mem(wll_0);
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
        EXPECT_EQ(0xe99ff867, wll._internal_state.state.list[1]);
        EXPECT_EQ(0xb4a0472e, wll._internal_state.state.list[4]);
        EXPECT_EQ(0x405da438, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x03b23496, wll._internal_state.state.list[10]);
        EXPECT_EQ(0xdd90e10f, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0x3ba7234c, 0x1dfcd2af, 0xf23ef13a, 0x140dde34, 0x31c59c4c };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, wll.next());
        EXPECT_EQ(11, wll._internal_state.state.index);
        EXPECT_EQ(0x382ff84c, wll._internal_state.state.list[2]);
        EXPECT_EQ(0xd31dadbd, wll._internal_state.state.list[5]);
        EXPECT_EQ(0xc4fea708, wll._internal_state.state.list[8]);
        EXPECT_EQ(0xf5b7fb12, wll._internal_state.state.list[11]);
        EXPECT_EQ(0xf23ef13a, wll._internal_state.state.list[14]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(1);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x71bb54d8, wll._internal_state.state.list[4]);
        EXPECT_EQ(0x85e7bb0f, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x6775dc77, wll._internal_state.state.list[10]);
        EXPECT_EQ(0x87b341d6, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-2);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xf3203e90, wll._internal_state.state.list[0]);
        EXPECT_EQ(0x1ef156bb, wll._internal_state.state.list[3]);
        EXPECT_EQ(0xea909a92, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x19fbbd62, wll._internal_state.state.list[9]);
        EXPECT_EQ(0x8e1f0e39, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x52ef36bb, wll._internal_state.state.list[15]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(9L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xc02d8a5e, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x4336b378, wll._internal_state.state.list[4]);
        EXPECT_EQ(0xfbc9d618, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x96f90d64, wll._internal_state.state.list[10]);
        EXPECT_EQ(0x3d8599a8, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-11L);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x96caee61, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x69e6fff0, wll._internal_state.state.list[4]);
        EXPECT_EQ(0xd830cf06, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x17b13790, wll._internal_state.state.list[10]);
        EXPECT_EQ(0xe5561582, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(17UL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x6434ff62, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x046b1664, wll._internal_state.state.list[4]);
        EXPECT_EQ(0xa74db96e, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x41515d2e, wll._internal_state.state.list[10]);
        EXPECT_EQ(0x826229cb, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xd573529b, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x01404ce9, wll._internal_state.state.list[4]);
        EXPECT_EQ(0x8931545f, wll._internal_state.state.list[7]);
        EXPECT_EQ(0xcdb8c9cd, wll._internal_state.state.list[10]);
        EXPECT_EQ(0x97f6c698, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x48bbc5b8, wll._internal_state.state.list[0]);
        EXPECT_EQ(0x637c8718, wll._internal_state.state.list[3]);
        EXPECT_EQ(0x95d0c8e5, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x5f29354e, wll._internal_state.state.list[9]);
        EXPECT_EQ(0xba17e257, wll._internal_state.state.list[12]);
        EXPECT_EQ(0xfeb66399, wll._internal_state.state.list[15]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xeede014d, wll._internal_state.state.list[0]);
        EXPECT_EQ(0xaf6aa8f4, wll._internal_state.state.list[3]);
        EXPECT_EQ(0x1408795f, wll._internal_state.state.list[6]);
        EXPECT_EQ(0x04443a10, wll._internal_state.state.list[9]);
        EXPECT_EQ(0xc6afab58, wll._internal_state.state.list[12]);
        EXPECT_EQ(0x4a80a9e7, wll._internal_state.state.list[15]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(0.357);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0x5fee464f, wll._internal_state.state.list[0]);
        EXPECT_EQ(0x77714db9, wll._internal_state.state.list[3]);
        EXPECT_EQ(0x1c4d126a, wll._internal_state.state.list[6]);
        EXPECT_EQ(0xe8f9525b, wll._internal_state.state.list[9]);
        EXPECT_EQ(0x102227a3, wll._internal_state.state.list[12]);
        EXPECT_EQ(0xd619e21c, wll._internal_state.state.list[15]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xec779c36, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x260ffb02, wll._internal_state.state.list[4]);
        EXPECT_EQ(0xd7c07017, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x71da8c61, wll._internal_state.state.list[10]);
        EXPECT_EQ(0x69f17ee1, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        EXPECT_THROW(wll.seed(1.0001), FloatValueRange01Exception);
        EXPECT_THROW(wll.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        wll._setstate(-1LL);
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xe99ff867, wll._internal_state.state.list[1]);
        EXPECT_EQ(0xb4a0472e, wll._internal_state.state.list[4]);
        EXPECT_EQ(0x405da438, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x03b23496, wll._internal_state.state.list[10]);
        EXPECT_EQ(0xdd90e10f, wll._internal_state.state.list[13]);
        EXPECT_FALSE(wll._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, wll._internal_state.gauss_next);

        wll._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, wll._internal_state.state.index);
        EXPECT_EQ(0xec779c36, wll._internal_state.state.list[1]);
        EXPECT_EQ(0x260ffb02, wll._internal_state.state.list[4]);
        EXPECT_EQ(0xd7c07017, wll._internal_state.state.list[7]);
        EXPECT_EQ(0x71da8c61, wll._internal_state.state.list[10]);
        EXPECT_EQ(0x69f17ee1, wll._internal_state.state.list[13]);
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
