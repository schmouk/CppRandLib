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
#include <cstdint>

#include "gtest/gtest.h"

#include "cwg128.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsCwg128)
    {
        //-- tests empty constructor
        Cwg128 cwg128_1;

        EXPECT_EQ(0ULL, cwg128_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_1._internal_state.state.s.lo & 1ULL);
        EXPECT_NE(0ULL, cwg128_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_EQ(0ULL, cwg128_1._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_1._internal_state.gauss_next);


        // Notice: all belowing hard coded values have been evaluated with PyRandLib

        //-- tests Valued constructor (seed) AND next()
        {
            Cwg128 cwg128(1);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x910a2dec89025cc1, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xbeeb8da1658eec67, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xf893a2eefb32555e, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x71c18690ee42c90b, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0x754ee327c1a233ee, 0x23fcb9247bb8f03e),
                utils::UInt128(0x9fd66bc3ea4ccd07, 0x790e21e4306abd20),
                utils::UInt128(0x7c7021f701a00e33, 0xd6c43207d31390a4),
                utils::UInt128(0x7bd58f7d944d7137, 0x9a6139299f14a0fc),
                utils::UInt128(0xcf5ca544e57e9414, 0x4121cd1f0fd668f2)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x5fea34f3d0ed5bf, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x7ff1cccac2df6bbc, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x910a2dec89025cc1, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xbeeb8da1658eec67, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xcf5ca544e57e9414, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x4121cd1f0a28cbbd, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0xd532e59ead0bcfc8, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0xba99c426fbca9e03, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(-2);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xd0d5127a96e8d90d, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x1ef156bb76650c37, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0xe3638e10ee1ff41d, 0xd1cff6f835c2f85e),
                utils::UInt128(0xfd9b5ffbb45ea04f, 0x7c62d8edd0763a3f),
                utils::UInt128(0x94144ebdf8ec4bf8, 0xe839929cdf396f7a),
                utils::UInt128(0xe117e38f08dac11, 0x19e05ceaf0d6fd07),
                utils::UInt128(0x74f6b6fdf88910d7, 0xb30c057e9afcb8dc)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x53f9cd7e22e16584, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x6f3e1628e3f7b34e, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x74f6b6fdf88910d7, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xb30c057ec90575a2, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0xbfa138d121c748a8, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0xa3b0e6fd6d50e18d, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(9);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xaeaf52febe706064, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xc02d8a5e87afea63, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x43ec2be544b589b6, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xc8e98cd697316060, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0xf75c15a01264ec92, 0x6c58f118345f03b6),
                utils::UInt128(0x7c6c68b228562b0f, 0xd60241bf964bf5e8),
                utils::UInt128(0x6aa891d2f2f914e, 0x9266f2a5ea10ebe8),
                utils::UInt128(0xfed9d6f18be9df5c, 0xb6728e8e49d8eac9),
                utils::UInt128(0x1b94d0ee4c920943, 0xc562c1cc75f193ff)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0xbd390a463a8a1204, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x541e40e31114589c, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xaeaf52febe706064, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xc02d8a5e87afea63, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x1b94d0ee4c920943, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xc562c1ccc8c899b9, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x696c9ef9b831e1f7, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0xc0e3b3d8a66f93ef, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(-11);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x6fc5530939fb94c3, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x96caee613260cfcb, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x46d40b90622a734b, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x6ecc725d7bedada9, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0x2f7dbb9e406fb2e0, 0x5538d19a81d1d1af),
                utils::UInt128(0x59fb8845710791d9, 0x97296718bd32728f),
                utils::UInt128(0xee86fadaee3283e9, 0x269b80b5cd6e8945),
                utils::UInt128(0x7ef375cc2de1d4eb, 0x6847861a89955feb),
                utils::UInt128(0xf565e03362ee7085, 0x1ab5bf8279cb02)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x3dc7c01b2fb610d9, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0xea11b1e062bc195e, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x6fc5530939fb94c3, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x96caee613260cfcb, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xf565e03362ee7085, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x1ab5bfbfbe0b19, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x2eda9f2e21e9e7d1, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0xf1f6a7e5fbe40ef7, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(17);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x808475f02ee37363, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x6434ff62b4e8edd1, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x540d6c3702d41b8c, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x395142ca8efaf003, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0xed8a71279aa259d7, 0x4f2ecc75d516d9e5),
                utils::UInt128(0x61da1020b3ce0e0c, 0xe2d246d82c635621),
                utils::UInt128(0xec76ee2cabdd0e60, 0xdbe64659946c9367),
                utils::UInt128(0xa15a63eda0b614ac, 0x4340a5887a0be0f3),
                utils::UInt128(0x5038a4e0527e8f86, 0x2ae860d299be17d0)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x31433f999dd7a67d, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x8a7941faab0beac4, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x808475f02ee37363, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x6434ff62b4e8edd1, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x5038a4e0527e8f86, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x2ae860d2a8fd2849, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x82964db0ea7140f0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0xf508fced888ca515, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x157a3807a48faa9d, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xd573529b34a1d093, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x2f90b72e996dccbe, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xa2d419334c4667ec, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0x4b5456b801cefdb2, 0x8310efbd2ef27303),
                utils::UInt128(0x5939ecb468a992f5, 0xac7642257f12f0e6),
                utils::UInt128(0x6dd81cbc1e016fad, 0xbab05196fd25d1a2),
                utils::UInt128(0x8b10c583d21efb14, 0x1656addf154ee48f),
                utils::UInt128(0x4e21c10a0b2187a9, 0x7ab330ef2a1e94a1)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0xcd07dcdaf406c828, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0xa3624a8ad196482a, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x157a3807a48faa9d, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xd573529b34a1d093, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x4e21c10a0b2187a9, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x7ab330efe719487b, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x6b63182636ce5515, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x2b409d08072912df, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(-8870000000000000000);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x48bbc5b84275f3ca, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xe2fbc345a799b5ab, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x86ce19a135fba0de, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x637c87187035ea06, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0x774bf77916b0ea5d, 0x84f39691707dd1f),
                utils::UInt128(0xe22bc81543ec9eb9, 0x95c52a43b4b6bf57),
                utils::UInt128(0xb254ddeb262e3ccb, 0xe390edbc3b646fa8),
                utils::UInt128(0xd95f6340c21a7994, 0x716ea418ec3f65bd),
                utils::UInt128(0x8bfd0b95bd021b12, 0xb812273c98aa6b61)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x6bfa1a5b78e1e055, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x56907c9aa673e63f, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x48bbc5b84275f3ca, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xe2fbc345a799b5ab, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x8bfd0b95bd021b12, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xb812273cf350713a, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x6baadc994c4dc2f6, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x6eead05c46008c57, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(8870000000000000000);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xeede014d9a5a6108, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xa6eb6466bac9f251, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x4246cbb1a64bf70c, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xaf6aa8f43ebb8659, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0x30621f22d84676d9, 0xa451abf4cc6adbac),
                utils::UInt128(0x87a1e7d72b96e789, 0x736d7c3767acfcf4),
                utils::UInt128(0xc8fb8b8cabad5377, 0xc422566383c44228),
                utils::UInt128(0x94d1f21119eb7320, 0xb8a32e5b5dc61c25),
                utils::UInt128(0x1c9e3456b00cc022, 0x4919bf92c130e7de)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x581850496fc21c08, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x43ef55def9fa7f36, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xeede014d9a5a6108, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xa6eb6466bac9f251, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x1c9e3456b00cc022, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x4919bf929928b797, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0xaa56068403c3e52b, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x4298f601a5f1bb95, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(0.357);

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x5fee464f36fc42c3, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x954faf5a9ad49cf9, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xa985465a4a5fc644, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x77714db9e870d702, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0xa56a1f0bfbe70516, 0x7018525d1c334320),
                utils::UInt128(0x1990fd15e26c40fc, 0x4c7b39965a1e9edd),
                utils::UInt128(0x5558a89f610b4e27, 0xe2a476a81114b6ec),
                utils::UInt128(0xb2cfc7cd9aa34420, 0x3ad877fba5e38507),
                utils::UInt128(0x34de721b11fe3449, 0x2eedbca28a30ef5e)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x70a8d2e924619e9f, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x5181c85144e83ae3, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0x5fee464f36fc42c3, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0x954faf5a9ad49cf9, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x34de721b11fe3449, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x2eedbca2fa983db7, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0xdfa75f8c12ed4dd1, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0xea8e6cc5062710dd, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }
        {
            Cwg128 cwg128(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));

            EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0xec779c3693f88501, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

            const utils::UInt128 expected[]{
                utils::UInt128(0xae85c9c4e3191d32, 0x6c288dd04b7ff7c4),
                utils::UInt128(0x1fd9e09b1271b43c, 0x4e33950ce3e8275),
                utils::UInt128(0x9dc870ccfe9ae50a, 0x2d83d25ba93a87e2),
                utils::UInt128(0x3e681e8e1ee91ac3, 0xf59c640e4c36251f),
                utils::UInt128(0x892781da9fea0e2, 0x718743f4145e5de1)
            };
            for (utils::UInt128 v : expected)
                EXPECT_EQ(v, cwg128.next());

            EXPECT_EQ(0x64e6ce5428ebcb26, cwg128._internal_state.state.a.hi);
            EXPECT_EQ(0x80a399c1b7da087a, cwg128._internal_state.state.a.lo);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128._internal_state.state.s.lo);
            EXPECT_EQ(0x892781da9fea0e2, cwg128._internal_state.state.state.hi);
            EXPECT_EQ(0x718743f470b893b5, cwg128._internal_state.state.state.lo);
            EXPECT_EQ(0xbfa138d121c748a9, cwg128._internal_state.state.weyl.hi);
            EXPECT_EQ(0xd4db17fa8c282951, cwg128._internal_state.state.weyl.lo);
            EXPECT_FALSE(cwg128._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);
        }

        EXPECT_THROW(Cwg128(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Cwg128(1.0), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        CollatzWeylState<utils::UInt128, utils::UInt128>   internal_state_128_128_0;
        Cwg128 cwg128_0(internal_state_128_128_0);

        EXPECT_EQ(internal_state_128_128_0.a, cwg128_0._internal_state.state.a);
        EXPECT_EQ(internal_state_128_128_0.s, cwg128_0._internal_state.state.s);
        EXPECT_TRUE(internal_state_128_128_0.state == cwg128_0._internal_state.state.state);
        EXPECT_EQ(internal_state_128_128_0.weyl, cwg128_0._internal_state.state.weyl);


        //-- tests copy constructor
        {
            Cwg128 cwg128(cwg128_1);

            EXPECT_EQ(cwg128_1._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_1._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_1._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            Cwg128 cwg64_mem(cwg128_0);
            Cwg128 cwg128(std::move(cwg64_mem));

            EXPECT_EQ(cwg128_0._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_0._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_0._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Cwg128 cwg128;

            cwg128 = cwg128_1;
            EXPECT_EQ(cwg128_1._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_1._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_1._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Cwg128 cwg128;

        {
            Cwg128 cwg64_mem(cwg128_0);
            cwg128 = std::move(cwg64_mem);

            EXPECT_EQ(cwg128_0._internal_state.state, cwg128._internal_state.state);
            EXPECT_EQ(cwg128_0._internal_state.gauss_next, cwg128._internal_state.gauss_next);
            EXPECT_EQ(cwg128_0._internal_state.gauss_valid, cwg128._internal_state.gauss_valid);
        }


        //-- tests random()
        for (int i = 0; i < 1'000'000; ++i) {
            float randf{ cwg128.random<float>() };
            EXPECT_GE(randf, 0.0f);
            EXPECT_LT(randf, 1.0f);

            double rand{ cwg128.random() };
            EXPECT_GE(rand, 0.0);
            EXPECT_LT(rand, 1.0);

            long double randl{ cwg128.random<long double>() };
            EXPECT_GE(randl, 0.0L);
            EXPECT_LT(randl, 1.0L);
        }


        //-- tests seed()
        cwg128.seed();

        EXPECT_EQ(0ULL, cwg128._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128._internal_state.state.s.lo & 1ULL);
        EXPECT_NE(0ULL, cwg128._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_NE(cwg128_1._internal_state.state.s, cwg128._internal_state.state.s);  // (1 over 2^128 risk)
        EXPECT_NE(cwg128_1._internal_state.state.state, cwg128._internal_state.state.state);  // (1 over 2^128 risk)
        EXPECT_EQ(0ULL, cwg128._internal_state.state.weyl);


        //-- tests seed(value)
        cwg128.seed(-1);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xe4d971771b652c20, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x6d1db36ccba982d2, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(1);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x910a2dec89025cc1, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xbeeb8da1658eec67, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xf893a2eefb32555e, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x71c18690ee42c90b, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(-2);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xd0d5127a96e8d90d, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x1ef156bb76650c37, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(9L);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xaeaf52febe706064, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xc02d8a5e87afea63, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x43ec2be544b589b6, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xc8e98cd697316060, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(-11L);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x6fc5530939fb94c3, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0x96caee613260cfcb, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x46d40b90622a734b, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x6ecc725d7bedada9, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(17UL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x808475f02ee37363, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0x6434ff62b4e8edd1, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x540d6c3702d41b8c, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x395142ca8efaf003, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x157a3807a48faa9d, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xd573529b34a1d093, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x2f90b72e996dccbe, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xa2d419334c4667ec, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x48bbc5b84275f3ca, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xe2fbc345a799b5ab, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x86ce19a135fba0de, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x637c87187035ea06, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xeede014d9a5a6108, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xa6eb6466bac9f251, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x4246cbb1a64bf70c, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xaf6aa8f43ebb8659, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        cwg128.seed(0.357);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0x5fee464f36fc42c3, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0x954faf5a9ad49cf9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xa985465a4a5fc644, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x77714db9e870d702, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);

        EXPECT_THROW(cwg128.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(cwg128.seed(-0.001), FloatValueRange01Exception);


        //-- tests random()
        for (int i = 0; i < 1'000'000; ++i) {
            float randf{ cwg128.random<float>() };
            EXPECT_GE(randf, 0.0f);
            EXPECT_LT(randf, 1.0f);

            double rand{ cwg128.random() };
            EXPECT_GE(rand, 0.0);
            EXPECT_LT(rand, 1.0);

            long double randl{ cwg128.random<long double>() };
            EXPECT_GE(randl, 0.0L);
            EXPECT_LT(randl, 1.0L);
        }


        //-- tests uniform()
        for (int i = 0; i < 1'000'000; ++i) {
            const double u{ cwg128.uniform() };
            EXPECT_GE(u, 0.0);
            EXPECT_LT(u, 1.0);

            const float uf{ cwg128.uniform<float>() };
            EXPECT_GE(uf, 0.0f);
            EXPECT_LT(uf, 1.0f);
        }


        //-- tests _setstate(seed_)
        // Notice: hard coded value below have been evaluated with PyRandLib
        cwg128._setstate(-1LL);
        EXPECT_EQ(0, cwg128._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c20, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0x6d1db36ccba982d2, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0, cwg128._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg128._internal_state.gauss_next);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);

        cwg128._setstate(utils::UInt128(0xfffffffffffffffe, 0xfffffffffffffffd));
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.a.lo);
        EXPECT_EQ(0xf3203e9039f4a821, cwg128._internal_state.state.s.hi);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128._internal_state.state.s.lo);
        EXPECT_EQ(0xba56949915dcf9e9, cwg128._internal_state.state.state.hi);
        EXPECT_EQ(0xec779c3693f88501, cwg128._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.hi);
        EXPECT_EQ(0x0, cwg128._internal_state.state.weyl.lo);
        EXPECT_FALSE(cwg128._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128._internal_state.gauss_next);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        cwg128.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint32_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 50) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[cwg128(ENTRIES_COUNT)]++;
            ++n;
            if (utils::get_time_ms() - start_ms >= 2000)
                break;  // no evaluation during more than 2 seconds duration
        }

        const std::uint64_t nloops{ n * INTERNAL_LOOPS_COUNT };
        EXPECT_TRUE(hist.is_mean_median_difference_ok(nloops));
        EXPECT_TRUE(hist.is_stdev_ok(nloops));
        EXPECT_TRUE(hist.is_variance_ok());

    }

}
