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

#include "melg607.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsMelg607)
    {
        //-- tests empty constructor
        Melg607 melg_1;

        EXPECT_EQ(10ULL, melg_1._internal_state.state.list.size());
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
            Melg607 melg(1);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x910a2dec89025cc1, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xf893a2eefb32555e, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x71bb54d8d101b5b9, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xe099ec6cd7363ca5, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x491718de357e3da8, melg._internal_state.state.list[8]);
            EXPECT_EQ(0xcb435c8e74616796, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x89cc9fe3a1f1d1b0, 0x18b0815477e51d1b, 0x6851950251a7f4ca, 0x3c565e3f08a1db87, 0xbdf32cc567babffd };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x3be15f8f4bb119b2, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x9e716a1ad1b7f4ca, melg._internal_state.state.list[2]);
            EXPECT_EQ(0xf0702139259a3fd9, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xe099ec6cd7363ca5, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x491718de357e3da8, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x81cb75e1a5b653e5, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(-2);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xf3203e9039f4a821, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xd0d5127a96e8d90d, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x7842841591543f1d, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xea909a92e113bf3c, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x24b37710c55c43d9, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x19fbbd62c13ae39f, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x755d9c2259a1595a, 0xa432edff813a1bb3, 0x8782fca8e7d176f5, 0x9383fd39376a829e, 0x48ed713d085823f2 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xbd4c8e573bc1517c, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x066a253706817ef7, melg._internal_state.state.list[2]);
            EXPECT_EQ(0xf62639eae3882bf6, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xea909a92e113bf3c, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x24b37710c55c43d9, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x8e64bdff4310b513, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(9);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xaeaf52febe706064, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x43ec2be544b589b6, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x4336b3782f5887a1, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xa553b8a65aacb8cc, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x3812b7427a48e169, melg._internal_state.state.list[8]);
            EXPECT_EQ(0xca06743146f19573, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x6e99bfb73a49e1d8, 0x8d3853ff3816c776, 0xb635ef9de4a64edc, 0xd86da7498d492b6a, 0xfe72c190444641ec };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xe02e53cb3979a1f8, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x6b7aaa03642e06fa, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x1fd2a7ea0da681c8, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xa553b8a65aacb8cc, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x3812b7427a48e169, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x5ce4149206b468a4, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(-11);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x6fc5530939fb94c3, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x46d40b90622a734b, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x69e6fff0691d876d, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xd20091d031cd373d, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x87422545f121192f, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x29417c7688150820, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xfbd4a09d0b0ecbc4, 0x788280944ad86f2b, 0x93117c0a0d9c5b3f, 0x6d1aec7161380ee5, 0xcc7bb7f21777f14c };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x8521726c60e643e4, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xd8417ec426641b39, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x1b9c9faa5f1fb968, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xd20091d031cd373d, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x87422545f121192f, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x727a605a2eab92a4, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(17);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x808475f02ee37363, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x540d6c3702d41b8c, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x046b1664f61a205e, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x0807a6b4c6fa7404, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x067c24523a89bd3a, melg._internal_state.state.list[8]);
            EXPECT_EQ(0xb57d05b4f3731b20, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb0b81a69c98343e0, 0xc55a36643a4adae5, 0xb582feeb77b160ae, 0xe59677ecfda63170, 0xe175fdcfd614b27a };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x4027b89b437b83e2, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xb49726e81771608c, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x508761725efc725e, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x0807a6b4c6fa7404, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x067c24523a89bd3a, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x54ec7716b0a6ce56, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x157a3807a48faa9d, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x2f90b72e996dccbe, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x01404ce914938008, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xb8fc5b1060708c05, melg._internal_state.state.list[6]);
            EXPECT_EQ(0xf984db4ef14fde1b, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x2680d065cb73ece7, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x6d1c8dcc2f39eb32, 0x2b3d47b953db5234, 0x4c5d559f75fbd847, 0x77acf1a2b79c185e, 0x758119c3447e5459 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xb606e72be779ab16, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xcf05f78e1fd39065, melg._internal_state.state.list[2]);
            EXPECT_EQ(0xa659e8df4fe6d459, melg._internal_state.state.list[4]);
            EXPECT_EQ(0xb8fc5b1060708c05, melg._internal_state.state.list[6]);
            EXPECT_EQ(0xf984db4ef14fde1b, melg._internal_state.state.list[8]);
            EXPECT_EQ(0xa719a436712eacad, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(-8870000000000000000);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x48bbc5b84275f3ca, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x86ce19a135fba0de, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x2a03b9aff2bfd421, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x95d0c8e531644d42, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x2a6e10124e1efad4, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x5f29354ebb479e63, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9011cff531617f08, 0x8bef952556d3c183, 0x7b4bae10528196b7, 0x421d9c7bda87b445, 0x137d8d3f0eebce10 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x4629243ed151b70e, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x77b0199d3ad9de95, melg._internal_state.state.list[2]);
            EXPECT_EQ(0xd6f92e928d138e36, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x95d0c8e531644d42, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x2a6e10124e1efad4, melg._internal_state.state.list[8]);
            EXPECT_EQ(0xfcfa973d3ed1a6f3, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(8870000000000000000);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xeede014d9a5a6108, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x4246cbb1a64bf70c, melg._internal_state.state.list[2]);
            EXPECT_EQ(0xe1b0fb2c7e764cdb, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x1408795faf81b73d, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x13d184a1443e3dbe, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x04443a1051eede9a, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x5f8c7bc5bb79208d, 0xb4f9652bb92395b9, 0xaa6df28e91636909, 0x2b5ada87ed488a37, 0x22f918afc2746158 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xcd9493c6d1c1a08d, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xf2b36ce4787b610b, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x5a9874f86284a15e, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x1408795faf81b73d, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x13d184a1443e3dbe, melg._internal_state.state.list[8]);
            EXPECT_EQ(0xbb288fd44cfa9f27, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(0.357);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x5fee464f36fc42c3, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xa985465a4a5fc644, melg._internal_state.state.list[2]);
            EXPECT_EQ(0xa3aac457d81d552c, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x1c4d126a40f3f8a9, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x89b7be31ad4c739f, melg._internal_state.state.list[8]);
            EXPECT_EQ(0xe8f9525bf6c56aef, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xba94143022cf49ee, 0xabd911badf8f412e, 0xf5ef4d745967b451, 0x07ffe4e0733ba781, 0xf56e57b2cdd98f34 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x0e5ab2634abf89ec, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xf57d706891cffc53, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x3a07125ea7310f30, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x1c4d126a40f3f8a9, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x89b7be31ad4c739f, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x99add60938abfaf3, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg607 melg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xf75f04cbb5a1a1dd, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xfed9eeb4936de39d, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x260ffb0260bbbe5f, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x7a5f67e38e997e3f, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x4f6d6a273422e220, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x56a7458a6eece57b, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xac329b154f3a9818, 0xa8174670aa22b22e, 0xecf2a94ec01da815, 0xacd9b51aacfc6af4, 0x35ee7f61db54d538 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xbb3b8d19c612581a, melg._internal_state.state.list[0]);
            EXPECT_EQ(0x7467354a62e56833, melg._internal_state.state.list[2]);
            EXPECT_EQ(0x6fd92a2473dc551e, melg._internal_state.state.list[4]);
            EXPECT_EQ(0x7a5f67e38e997e3f, melg._internal_state.state.list[6]);
            EXPECT_EQ(0x4f6d6a273422e220, melg._internal_state.state.list[8]);
            EXPECT_EQ(0x49d6d1261c1c4c5c, melg._internal_state.state.list[9]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }

        EXPECT_THROW(Melg607(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Melg607(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Melg607 melg(melg_1);

            EXPECT_TRUE(melg_1._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_1._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_1._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Melg607 melg_0;

        {
            Melg607 melg_mem(melg_0);
            Melg607 melg(std::move(melg_mem));

            EXPECT_TRUE(melg_0._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_0._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_0._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Melg607 melg;

            melg = melg_1;
            EXPECT_TRUE(melg_1._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_1._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_1._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Melg607 melg;

        {
            Melg607 melg_mem(melg_0);
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
        EXPECT_EQ(0xe4d971771b652c20, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x382ff84cb27281e9, melg._internal_state.state.list[2]);
        EXPECT_EQ(0xb4a0472e578069ae, melg._internal_state.state.list[4]);
        EXPECT_EQ(0xf14f2cf802083fa5, melg._internal_state.state.list[6]);
        EXPECT_EQ(0xc4fea708156e0c84, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x031e50fe7bbd6e1c, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(1);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x910a2dec89025cc1, melg._internal_state.state.list[0]);
        EXPECT_EQ(0xf893a2eefb32555e, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x71bb54d8d101b5b9, melg._internal_state.state.list[4]);
        EXPECT_EQ(0xe099ec6cd7363ca5, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x491718de357e3da8, melg._internal_state.state.list[8]);
        EXPECT_EQ(0xcb435c8e74616796, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-2);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xf3203e9039f4a821, melg._internal_state.state.list[0]);
        EXPECT_EQ(0xd0d5127a96e8d90d, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x7842841591543f1d, melg._internal_state.state.list[4]);
        EXPECT_EQ(0xea909a92e113bf3c, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x24b37710c55c43d9, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x19fbbd62c13ae39f, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(9L);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xaeaf52febe706064, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x43ec2be544b589b6, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x4336b3782f5887a1, melg._internal_state.state.list[4]);
        EXPECT_EQ(0xa553b8a65aacb8cc, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x3812b7427a48e169, melg._internal_state.state.list[8]);
        EXPECT_EQ(0xca06743146f19573, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-11L);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x6fc5530939fb94c3, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x46d40b90622a734b, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x69e6fff0691d876d, melg._internal_state.state.list[4]);
        EXPECT_EQ(0xd20091d031cd373d, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x87422545f121192f, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x29417c7688150820, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(17UL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x808475f02ee37363, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x540d6c3702d41b8c, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x046b1664f61a205e, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x0807a6b4c6fa7404, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x067c24523a89bd3a, melg._internal_state.state.list[8]);
        EXPECT_EQ(0xb57d05b4f3731b20, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x157a3807a48faa9d, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x2f90b72e996dccbe, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x01404ce914938008, melg._internal_state.state.list[4]);
        EXPECT_EQ(0xb8fc5b1060708c05, melg._internal_state.state.list[6]);
        EXPECT_EQ(0xf984db4ef14fde1b, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x2680d065cb73ece7, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x48bbc5b84275f3ca, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x86ce19a135fba0de, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x2a03b9aff2bfd421, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x95d0c8e531644d42, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x2a6e10124e1efad4, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x5f29354ebb479e63, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xeede014d9a5a6108, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x4246cbb1a64bf70c, melg._internal_state.state.list[2]);
        EXPECT_EQ(0xe1b0fb2c7e764cdb, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x1408795faf81b73d, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x13d184a1443e3dbe, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x04443a1051eede9a, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(0.357);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x5fee464f36fc42c3, melg._internal_state.state.list[0]);
        EXPECT_EQ(0xa985465a4a5fc644, melg._internal_state.state.list[2]);
        EXPECT_EQ(0xa3aac457d81d552c, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x1c4d126a40f3f8a9, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x89b7be31ad4c739f, melg._internal_state.state.list[8]);
        EXPECT_EQ(0xe8f9525bf6c56aef, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, melg._internal_state.state.list[0]);
        EXPECT_EQ(0xfed9eeb4936de39d, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x260ffb0260bbbe5f, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x7a5f67e38e997e3f, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x4f6d6a273422e220, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x56a7458a6eece57b, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        EXPECT_THROW(melg.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(melg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        melg._setstate(-1LL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xe4d971771b652c20, melg._internal_state.state.list[0]);
        EXPECT_EQ(0x382ff84cb27281e9, melg._internal_state.state.list[2]);
        EXPECT_EQ(0xb4a0472e578069ae, melg._internal_state.state.list[4]);
        EXPECT_EQ(0xf14f2cf802083fa5, melg._internal_state.state.list[6]);
        EXPECT_EQ(0xc4fea708156e0c84, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x031e50fe7bbd6e1c, melg._internal_state.state.list[9]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg._setstate(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xf75f04cbb5a1a1dd, melg._internal_state.state.list[0]);
        EXPECT_EQ(0xfed9eeb4936de39d, melg._internal_state.state.list[2]);
        EXPECT_EQ(0x260ffb0260bbbe5f, melg._internal_state.state.list[4]);
        EXPECT_EQ(0x7a5f67e38e997e3f, melg._internal_state.state.list[6]);
        EXPECT_EQ(0x4f6d6a273422e220, melg._internal_state.state.list[8]);
        EXPECT_EQ(0x56a7458a6eece57b, melg._internal_state.state.list[9]);
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
