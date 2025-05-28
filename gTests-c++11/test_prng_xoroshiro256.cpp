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

#include "xoroshiro256.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsXoroshiro256)
    {
        //-- tests empty constructor
        Xoroshiro256 xrsr_1;

        EXPECT_EQ(4ULL, xrsr_1._internal_state.state.list.size());
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
            Xoroshiro256 xrsr(1);

            EXPECT_EQ(0x910a2dec89025cc1, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xbeeb8da1658eec67, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xf893a2eefb32555e, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x71c18690ee42c90b, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb3f2af6d0fc710c5, 0x853b559647364cea, 0x92f89756082a4514, 0x642e1c7bc266a3a7, 0xb27a48e29a233673 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x4f4ab19f008d40a1, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x078fdb12a01bbba1, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x01d82a3be31fdc56, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xd67a96f0bd4f172c, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(-2);

            EXPECT_EQ(0xf3203e9039f4a821, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xba56949915dcf9e9, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xd0d5127a96e8d90d, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x1ef156bb76650c37, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9c0f746bebf6fd59, 0xe3b62be9ec055080, 0xf970658bf1ebf2cc, 0xc7bb3d47050a7640, 0x6e8a56b72c710f7d };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x1763d33697c7a188, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xfe2d2bac28e8e330, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x69632d6f97ab922d, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x8a66097b584765f7, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(9);

            EXPECT_EQ(0xaeaf52febe706064, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xc02d8a5e87afea62, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x43ec2be544b589b6, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xc8e98cd697316060, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa94eecf619a060, 0x40619b85d152fbf9, 0x21e90bc830805b17, 0xbb91dca2edee4c4c, 0xebab75b2766c0965 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0xa3e22f54d0b0d698, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x4008783f5daf110f, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x1ddf10b7705d457d, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x45fc55a7fd4dce95, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(-11);

            EXPECT_EQ(0x6fc5530939fb94c3, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x96caee613260cfca, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x46d40b90622a734b, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x6ecc725d7bedada9, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xd5f38aed82434538, 0xcf94d54a1209d057, 0x5d9dabf7f20bd27a, 0x323b3ae5d3b64198, 0xb229f5458d2d19c4 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x963ac28da492c89d, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xeedb46fcb5239d68, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x8afc1a1175a2ddfd, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xc54c9d06203983bc, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(17);

            EXPECT_EQ(0x808475f02ee37363, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x6434ff62b4e8edd1, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x540d6c3702d41b8c, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x395142ca8efaf003, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa8722ce678e6e2ca, 0xb0c58defa535f501, 0xf057b25ffb0bf1b9, 0xf7aba65f754fde47, 0xaa9438aa0aad53a8 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0xde01b9c40e469175, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x09ff55419e763b83, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xd20dc8f2c4ccf2a3, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xd860bc0f2197dd5d, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0x157a3807a48faa9d, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xd573529b34a1d093, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x2f90b72e996dccbe, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xa2d419334c4667ec, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa2c2a42038d4ec3d, 0x5fc25d0738e7b0f, 0x625e7bff938e701e, 0x1ba4ddc6fe2b5726, 0xdf0a2482ac9254cf };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x8b6f756e3cf6d25d, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x4390c3ff2f4e84c9, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xdfd0524fbf0afc81, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x288d5f023136edc7, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(-8870000000000000000);

            EXPECT_EQ(0x48bbc5b84275f3ca, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xe2fbc345a799b5aa, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x86ce19a135fba0de, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x637c87187035ea06, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x20a99f3b027772ef, 0x7dc1a84a19c7b6e7, 0x2f31735444446fb9, 0xe7a4887c0cfbed6f, 0x759af005c27af765 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0xcbb0636c1f29c9a0, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x18acf37107b5ebed, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x76d9e55f06f99cd3, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x869bd993283770b2, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(8870000000000000000);

            EXPECT_EQ(0xeede014d9a5a6108, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xa6eb6466bac9f251, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x4246cbb1a64bf70c, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xaf6aa8f43ebb8659, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb053076abfcc1fa9, 0x2ad894da04d1796a, 0x35d9b6a5f7d4a18f, 0xb87eee82ee1cfe84, 0x292a831db2e368b1 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0xcb368051ac735759, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x38e7111d695e13d5, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x715def1bbf0f65e7, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x202050b0b1c67424, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(0.357);

            EXPECT_EQ(0x5fee464f36fc42c3, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x954faf5a9ad49cf8, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xa985465a4a5fc644, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x77714db9e870d702, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x80e9769bafcbd01d, 0xb96885c177a72daf, 0xb67b6dd8732977df, 0x3c927f5a021714d1, 0xc28bf2d43293a71e };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0xcc7c9cb29a85699c, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x953fc659c1d67eb5, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x18e2756f1ae806e2, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x6e088b6f07e347ae, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }
        {
            Xoroshiro256 xrsr(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0xec779c3693f88501, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0xfed9eeb4936de39d, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x833acc0157b09947, 0xb8e57a6d238338ae, 0x41757e8afe17e619, 0x24f34b752f865157, 0xd1ef3cc7286bab49 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, xrsr.next());

            EXPECT_EQ(0x1e7b70c98e672f97, xrsr._internal_state.state.list[0]);
            EXPECT_EQ(0x8c749d2e7ccd91c4, xrsr._internal_state.state.list[1]);
            EXPECT_EQ(0x5b7b5a182dd8841e, xrsr._internal_state.state.list[2]);
            EXPECT_EQ(0xbf5be0b5f2f77bf9, xrsr._internal_state.state.list[3]);

            EXPECT_FALSE(xrsr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        }

        EXPECT_THROW(Xoroshiro256(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Xoroshiro256(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Xoroshiro256 xrsr(xrsr_1);

            EXPECT_TRUE(xrsr_1._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_1._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_1._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Xoroshiro256 xrsr_0;

        {
            Xoroshiro256 xrsr_mem(xrsr_0);
            Xoroshiro256 xrsr(std::move(xrsr_mem));

            EXPECT_TRUE(xrsr_0._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_0._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_0._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Xoroshiro256 xrsr;

            xrsr = xrsr_1;
            EXPECT_TRUE(xrsr_1._internal_state.state == xrsr._internal_state.state);
            EXPECT_EQ(xrsr_1._internal_state.gauss_next, xrsr._internal_state.gauss_next);
            EXPECT_EQ(xrsr_1._internal_state.gauss_valid, xrsr._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Xoroshiro256 xrsr;

        {
            Xoroshiro256 xrsr_mem(xrsr_0);
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
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);
        const std::uint64_t expected[]{ 0x8f5520d52a7ead08, 0xc476a018caa1802d, 0x81de31c0d260469e, 0xbf658d7e065f3c2f, 0x913593fda1bca32a };
        for (std::uint64_t e : expected)
            EXPECT_EQ(e, xrsr.next());
        EXPECT_EQ(0x12a5ae8ac92df9d8, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x7ef7424878563a1e, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xfecaf32799b1dc5e, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x11beca1dcf6b4628, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(1);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x910a2dec89025cc1, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xbeeb8da1658eec67, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xf893a2eefb32555e, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x71c18690ee42c90b, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-2);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xf3203e9039f4a821, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xba56949915dcf9e9, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xd0d5127a96e8d90d, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x1ef156bb76650c37, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(9L);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xaeaf52febe706064, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xc02d8a5e87afea62, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x43ec2be544b589b6, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xc8e98cd697316060, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-11L);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x6fc5530939fb94c3, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x96caee613260cfca, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x46d40b90622a734b, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x6ecc725d7bedada9, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(17UL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x808475f02ee37363, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x6434ff62b4e8edd1, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x540d6c3702d41b8c, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x395142ca8efaf003, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x157a3807a48faa9d, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xd573529b34a1d093, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x2f90b72e996dccbe, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xa2d419334c4667ec, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x48bbc5b84275f3ca, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xe2fbc345a799b5aa, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x86ce19a135fba0de, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x637c87187035ea06, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xeede014d9a5a6108, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xa6eb6466bac9f251, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0x4246cbb1a64bf70c, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0xaf6aa8f43ebb8659, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(0.357);
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0x5fee464f36fc42c3, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0x954faf5a9ad49cf8, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xa985465a4a5fc644, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x77714db9e870d702, xrsr._internal_state.state.list[3]);
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xec779c3693f88501, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xfed9eeb4936de39d, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);
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
        EXPECT_FALSE(xrsr._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, xrsr._internal_state.gauss_next);

        xrsr._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, xrsr._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, xrsr._internal_state.state.list[0]);
        EXPECT_EQ(0xec779c3693f88501, xrsr._internal_state.state.list[1]);
        EXPECT_EQ(0xfed9eeb4936de39d, xrsr._internal_state.state.list[2]);
        EXPECT_EQ(0x6f9fb04b092bd30a, xrsr._internal_state.state.list[3]);
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
