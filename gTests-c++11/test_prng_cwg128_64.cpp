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

#include "cwg128_64.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsCwg128_64)
    {
        //-- tests empty constructor
        Cwg128_64 cwg128_64_1;

        EXPECT_EQ(0ULL, cwg128_64_1._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_64_1._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg128_64_1._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_EQ(0ULL, cwg128_64_1._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64_1._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64_1._internal_state.gauss_next);


        // Notice: all belowing hard coded values have been evaluated with PyRandLib

        //-- tests Valued construtor (seed) AND next()
        {
            Cwg128_64 cwg128_64(1);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x910a2dec89025cc1, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xbeeb8da1658eec67, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xf893a2eefb32555e, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xfe58a46deb3255a3, 0xff5247d888e1f6f9, 0xc8edfbc5db97fbd8, 0x1477776d4bcda574, 0x6b67ce70627acf91 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0xd3a4026896aa2ae1, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x910a2dec89025cc1, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xc87203002bed33bb, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x6b67ce70627a1c35, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0xd532e59ead0bcfc5, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(-2);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xba56949915dcf9e9, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xd0d5127a96e8d90d, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc53b94975ba3603a, 0x4da619774c2acf70, 0x78f8cdb9d76a8b3b, 0xbb9d5d0194c7b4f, 0x9d5ea8e0805c3da8 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x686964132f6d73c9, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x6df3d55f219736e5, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x9d5ea8e0805c55c1, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0xbfa138d121c748a5, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(9);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xaeaf52febe706065, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xc02d8a5e87afea62, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x43ec2be544b589b6, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9bd3024c4362c804, 0x48c45b1c35f22412, 0xca3ebfc43e0172d, 0x354149d905250477, 0xb3c1a04b68f90bf5 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x6a68bf2307108249, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xaeaf52febe706065, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x19969ac656420dca, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xb3c1a04b68f9619d, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0x696c9ef9b831e1f9, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(-11);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x6fc5530939fb94c3, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x96caee613260cfca, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x46d40b90622a734b, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x999c0206b0d4d040, 0x1bdd1db256ffa0ed, 0x9759261c1b791502, 0xe456bb324834aa01, 0xbe7e8dc4c69739d };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x77fd0c97cdac6d72, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x6fc5530939fb94c3, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x033667bbc9639ab1, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x0be7e8dc4c690460, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0x2eda9f2e21e9e7cf, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(17);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x808475f02ee37363, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x6434ff62b4e8edd1, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x540d6c3702d41b8c, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x97d3c4b544365f60, 0x4a86605ebe6192eb, 0x5b9f7057972b0545, 0xd5e866042850db7d, 0x98437e88fbb8c1f5 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x67ef67a6c4e71c9f, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x808475f02ee37363, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x493c0adf7baea455, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x98437e88fbb8a61a, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0x82964db0ea7140ef, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x157a3807a48faa9d, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xd573529b34a1d093, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x2f90b72e996dccbe, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x74c316a37df311ec, 0xef317b6dbb8bb2c0, 0x1ede53528e8f1440, 0xadc9d06765afa5ba, 0x6afa7b40ecc40951 };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x602d6cf9c72ac16b, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x157a3807a48faa9d, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x29303b5b41b2417d, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x6afa7b40ecc4697c, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0x6b63182636ce5511, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(-8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x48bbc5b84275f3cb, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xe2fbc345a799b5aa, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x86ce19a135fba0de, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xbd0a3fdebf4785b4, 0xe2653e1169475b6a, 0x462c74dc8286f3a3, 0xda25d5e2da77cc6a, 0xdf58233d77e91d2c };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x468fe250bb8832a8, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x48bbc5b84275f3cb, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x9c342dd376a3f762, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xdf58233d77e95ba3, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0x6baadc994c4dc2f7, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(8'870'000'000'000'000'000);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xa6eb6466bac9f251, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x4246cbb1a64bf70c, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5d0507d668842c81, 0xd331042444b7ec46, 0xa0e197d6293600d7, 0x72ec7391e58463ed, 0x4b87429035bd3cca };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x864ae3146242bc3e, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x60d4562e4fdab52a, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x4b87429035bdba80, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0xaa56068403c3e52d, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(-0.357);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x5fee464f36fc42c3, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x954faf5a9ad49cf8, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xa985465a4a5fc644, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xc528f6001bce6f6c, 0x2074ad4a7283a9ae, 0x25b7e72bb5a6037d, 0x40ca44afd9b64e2c, 0xebe74cd080e7675d };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0xf5a51580680fdb82, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0x5fee464f36fc42c3, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xdd6604a0ba2e09b3, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xebe74cd080e792f8, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0xdfa75f8c12ed4dcf, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(8.87e+18);

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xa6eb6466bac9f251, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x4246cbb1a64bf70c, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5d0507d668842c81, 0xd331042444b7ec46, 0xa0e197d6293600d7, 0x72ec7391e58463ed, 0x4b87429035bd3cca };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0x864ae3146242bc3e, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0x60d4562e4fdab52a, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0x4b87429035bdba80, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0xaa56068403c3e52d, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);
        }
        {
            Cwg128_64 cwg128_64(utils::UInt128(0xffff'ffff'ffff'fffeULL, 0xffff'ffff'ffff'fffdULL));

            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xec779c3693f88501, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xec288dd0f1298f2a, 0x4e26f7747cde7909, 0x3137387601cab2ab, 0xa1faef3817023fcf, 0xbfa5bbb9b880621a };
            for (std::uint64_t v : expected)
                EXPECT_EQ(v, cwg128_64.next());

            EXPECT_EQ(0xf9f9492a1acd86a4, cwg128_64._internal_state.state.a);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, cwg128_64._internal_state.state.s);
            EXPECT_EQ(0xaa642445fb13ed6e, cwg128_64._internal_state.state.state.hi);
            EXPECT_EQ(0xbfa5bbb9b8809be3, cwg128_64._internal_state.state.state.lo);
            EXPECT_EQ(0xd4db17fa8c282951, cwg128_64._internal_state.state.weyl);
            EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next); 
        }


        //-- tests Valued constructor (full state).
        CollatzWeylState<std::uint64_t, utils::UInt128>   internal_state_128_64_0;
        Cwg128_64 cwg128_64_0(internal_state_128_64_0);

        EXPECT_EQ(internal_state_128_64_0.a, cwg128_64_0._internal_state.state.a);
        EXPECT_EQ(internal_state_128_64_0.s, cwg128_64_0._internal_state.state.s);
        EXPECT_TRUE(internal_state_128_64_0.state == cwg128_64_0._internal_state.state.state);
        EXPECT_EQ(internal_state_128_64_0.weyl, cwg128_64_0._internal_state.state.weyl);


        //-- tests copy constructor
        {
            Cwg128_64 cwg128_64(cwg128_64_1);

            EXPECT_EQ(cwg128_64_1._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            Cwg128_64 cwg64_mem(cwg128_64_0);
            Cwg128_64 cwg128_64(std::move(cwg64_mem));

            EXPECT_EQ(cwg128_64_0._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Cwg128_64 cwg128_64;

            cwg128_64 = cwg128_64_1;
            EXPECT_EQ(cwg128_64_1._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_1._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Cwg128_64 cwg128_64;

        {
            Cwg128_64 cwg64_mem(cwg128_64_0);
            cwg128_64 = std::move(cwg64_mem);

            EXPECT_EQ(cwg128_64_0._internal_state.state, cwg128_64._internal_state.state);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_next, cwg128_64._internal_state.gauss_next);
            EXPECT_EQ(cwg128_64_0._internal_state.gauss_valid, cwg128_64._internal_state.gauss_valid);
        }


        //-- tests seed()
        cwg128_64.seed();

        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.a);
        EXPECT_EQ(1ULL, cwg128_64._internal_state.state.s & 1ULL);
        EXPECT_NE(0ULL, cwg128_64._internal_state.state.state);  // should mostly be non-zero, while it could (but 1 over 2^128)
        EXPECT_NE(cwg128_64_1._internal_state.state.s, cwg128_64._internal_state.state.s);  // (1 over 2^64 risk)
        EXPECT_NE(cwg128_64_1._internal_state.state.state, cwg128_64._internal_state.state.state);  // (1 over 2^128 risk)
        EXPECT_EQ(0ULL, cwg128_64._internal_state.state.weyl);


        //-- tests seed(value)
        cwg128_64.seed(-1);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c21, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(1);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x910a2dec89025cc1, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xbeeb8da1658eec67, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0xf893a2eefb32555e, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(-2);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xf3203e9039f4a821, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xba56949915dcf9e9, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0xd0d5127a96e8d90d, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(9L);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xaeaf52febe706065, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xc02d8a5e87afea62, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x43ec2be544b589b6, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(-11L);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x6fc5530939fb94c3, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0x96caee613260cfca, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x46d40b90622a734b, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(17UL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x808475f02ee37363, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0x6434ff62b4e8edd1, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x540d6c3702d41b8c, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x157a3807a48faa9d, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xd573529b34a1d093, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x2f90b72e996dccbe, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x48bbc5b84275f3cb, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xe2fbc345a799b5aa, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x86ce19a135fba0de, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xa6eb6466bac9f251, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x4246cbb1a64bf70c, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(-0.357);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0x5fee464f36fc42c3, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0x954faf5a9ad49cf8, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0xa985465a4a5fc644, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);

        cwg128_64.seed(8.87e+18);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xeede014d9a5a6109, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xa6eb6466bac9f251, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x4246cbb1a64bf70c, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0x0, cwg128_64._internal_state.state.weyl);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, cwg128_64._internal_state.gauss_next);


        //-- tests _setstate(seed_)
        // Notice: hard coded value below have been evaluated with PyRandLib
        cwg128_64._setstate(-1LL);
        EXPECT_EQ(0, cwg128_64._internal_state.state.a);
        EXPECT_EQ(0xe4d971771b652c21, cwg128_64._internal_state.state.s);
        EXPECT_EQ(0xe99ff867dbf682c9, cwg128_64._internal_state.state.state.hi);
        EXPECT_EQ(0x382ff84cb27281e9, cwg128_64._internal_state.state.state.lo);
        EXPECT_EQ(0, cwg128_64._internal_state.state.weyl);
        EXPECT_EQ(0.0, cwg128_64._internal_state.gauss_next);
        EXPECT_FALSE(cwg128_64._internal_state.gauss_valid);


        //-- tests equidistribution - notice: not more than 1 second of test, self-adaptation to platform and configuration
        cwg128_64.seed();  // notice: tests will be done on very different seed values each time they are run
        constexpr std::uint32_t ENTRIES_COUNT{ 6571 };  // notice: 6571 is a prime number
        Histogram hist(ENTRIES_COUNT);

        std::uint64_t n{ 0 };
        constexpr int INTERNAL_LOOPS_COUNT{ 1'000'000 };

        std::uint64_t start_ms{ utils::get_time_ms() };
        while (n < 50) {
            for (int i = 0; i < INTERNAL_LOOPS_COUNT; ++i)
                hist[cwg128_64(ENTRIES_COUNT)]++;
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
