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

#include "melg44497.h"
#include "g_utils/histogram.h"
#include "utils/time.h"
#include "utils/uint128.h"


//===========================================================================
namespace tests_prng
{
    //-----------------------------------------------------------------------
    TEST(TestSuitePrng, TestsMelg44497)
    {
        //-- tests empty constructor
        Melg44497 melg_1;

        EXPECT_EQ(696ULL, melg_1._internal_state.state.list.size());
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
            Melg44497 melg(1);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xbeeb8da1658eec67, melg._internal_state.state.list[1]);
            EXPECT_EQ(0xa6fefb55c353a1ea, melg._internal_state.state.list[140]);
            EXPECT_EQ(0xb762715eb23cd3d7, melg._internal_state.state.list[279]);
            EXPECT_EQ(0x041fe2b35f3a75fd, melg._internal_state.state.list[418]);
            EXPECT_EQ(0x6698b211b671b46f, melg._internal_state.state.list[557]);
            EXPECT_EQ(0x6bbc0a80a7487e21, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x65e91b062db707c3, 0x34d0f409caaa7c42, 0xb342b8909a505ec8, 0xab7accf231022eaf, 0x77e697a671f58dc6 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x29663e9ea0ec2561, melg._internal_state.state.list[70]);
            EXPECT_EQ(0x66e5c983a8893ed9, melg._internal_state.state.list[209]);
            EXPECT_EQ(0xaee49ed5eb5e2f99, melg._internal_state.state.list[348]);
            EXPECT_EQ(0x42914c1bd530f635, melg._internal_state.state.list[487]);
            EXPECT_EQ(0x1bf88565b19db3e9, melg._internal_state.state.list[626]);
            EXPECT_EQ(0xb375680cbb8c9da5, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(-2);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x1f4aea7af6513705, melg._internal_state.state.list[137]);
            EXPECT_EQ(0x74345ae408f3d48a, melg._internal_state.state.list[276]);
            EXPECT_EQ(0x9f1b299ea71cb462, melg._internal_state.state.list[415]);
            EXPECT_EQ(0x803ab216bda954f7, melg._internal_state.state.list[554]);
            EXPECT_EQ(0x0a8f137c062ac922, melg._internal_state.state.list[693]);
            EXPECT_EQ(0x79a6b61c50037b24, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x41bc9f50e84f3db0, 0x9a10f62b84b309aa, 0x5e5726893497af88, 0xa6031aa7387121e9, 0x666c3ab71afd0748 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xa126d6b63214585d, melg._internal_state.state.list[67]);
            EXPECT_EQ(0xf53df59d33ca1ba5, melg._internal_state.state.list[206]);
            EXPECT_EQ(0x7f14dc82c304bf17, melg._internal_state.state.list[345]);
            EXPECT_EQ(0x3db088bc77b4178a, melg._internal_state.state.list[484]);
            EXPECT_EQ(0xa2b9ee05cfd10ea0, melg._internal_state.state.list[623]);
            EXPECT_EQ(0xc72e68bf54fdd724, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(9);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xca06743146f19573, melg._internal_state.state.list[9]);
            EXPECT_EQ(0x64a7c90af8c871f4, melg._internal_state.state.list[148]);
            EXPECT_EQ(0xd788268ad8f5c07e, melg._internal_state.state.list[287]);
            EXPECT_EQ(0x5690ef2e94bde531, melg._internal_state.state.list[426]);
            EXPECT_EQ(0x72441cde256dd714, melg._internal_state.state.list[565]);
            EXPECT_EQ(0x086f6f3b7df5d2fd, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xb3119844e29f98e6, 0x56acbcaf3c292eeb, 0x5d0c83e8054f9d35, 0xa458b3a7ff5c86e0, 0xea67a93b56d46087 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x5e454bebdf320510, melg._internal_state.state.list[78]);
            EXPECT_EQ(0xbc03350d7ba6288e, melg._internal_state.state.list[217]);
            EXPECT_EQ(0x1efff3de750d3dc5, melg._internal_state.state.list[356]);
            EXPECT_EQ(0x040b3c715c953cd7, melg._internal_state.state.list[495]);
            EXPECT_EQ(0x0a8a1923c3ec1aee, melg._internal_state.state.list[634]);
            EXPECT_EQ(0x93de4c4c1e70cb3b, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(-11);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xee186c27e50eeb68, melg._internal_state.state.list[128]);
            EXPECT_EQ(0x7b7c45529c65082b, melg._internal_state.state.list[267]);
            EXPECT_EQ(0x6865e9c640602667, melg._internal_state.state.list[406]);
            EXPECT_EQ(0xaf22e3fcd31ba75a, melg._internal_state.state.list[545]);
            EXPECT_EQ(0xf558e462ab44d6e8, melg._internal_state.state.list[684]);
            EXPECT_EQ(0x8683593aa9ac8456, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x80368a685c13dabc, 0x1afe0f79fb42ba60, 0x6f2f6f240769817b, 0xe1e52b28bca752f6, 0x8fb8a6565310b7b9 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x5450e825c1ce6aa7, melg._internal_state.state.list[58]);
            EXPECT_EQ(0x04cbee58fc5ff63b, melg._internal_state.state.list[197]);
            EXPECT_EQ(0x466d648a329e1c03, melg._internal_state.state.list[336]);
            EXPECT_EQ(0x15a221f4f23a01d7, melg._internal_state.state.list[475]);
            EXPECT_EQ(0x21ae0b4450ad3b4e, melg._internal_state.state.list[614]);
            EXPECT_EQ(0x1e0cf1d725bf4943, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(17);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x6cb7d6f5a174672b, melg._internal_state.state.list[17]);
            EXPECT_EQ(0x4bdf273c0cf56b26, melg._internal_state.state.list[156]);
            EXPECT_EQ(0x697e2650f0a71bec, melg._internal_state.state.list[295]);
            EXPECT_EQ(0x8b11419098f6f4b9, melg._internal_state.state.list[434]);
            EXPECT_EQ(0x1e55c2449e96aa9a, melg._internal_state.state.list[573]);
            EXPECT_EQ(0x4c5da20fafe28721, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x42eb3b3e824488ee, 0x6c4b11d90dcc183b, 0x17dfa0758a1702cf, 0x834df9650f68fd95, 0x099c6b15333efebb };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xd1230010289185b3, melg._internal_state.state.list[86]);
            EXPECT_EQ(0x2548353cf409ba16, melg._internal_state.state.list[225]);
            EXPECT_EQ(0x396931462c2c03df, melg._internal_state.state.list[364]);
            EXPECT_EQ(0x87c86a70ee7c8b7f, melg._internal_state.state.list[503]);
            EXPECT_EQ(0x1970c423d0c368ee, melg._internal_state.state.list[642]);
            EXPECT_EQ(0x5931e6976e14d3c2, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(0x0123'4567'89ab'cdef);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x7820abc18567251a, melg._internal_state.state.list[62]);
            EXPECT_EQ(0x2ac534eb0ce5739d, melg._internal_state.state.list[201]);
            EXPECT_EQ(0x4c897d6599c3ca4f, melg._internal_state.state.list[340]);
            EXPECT_EQ(0x55161c61f946dd8b, melg._internal_state.state.list[479]);
            EXPECT_EQ(0xf4340a4c70e46ee9, melg._internal_state.state.list[618]);
            EXPECT_EQ(0x4ec2c4758dcffadd, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9907105396f37998, 0x580d9d1d30bf41b9, 0x4bdba4870acb0784, 0x161ada0c406c26c8, 0x345eb35a58ba5a7e };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x43856098c604fda6, melg._internal_state.state.list[131]);
            EXPECT_EQ(0x7c33528010383106, melg._internal_state.state.list[270]);
            EXPECT_EQ(0xc1432f2d5a7ca12e, melg._internal_state.state.list[409]);
            EXPECT_EQ(0x5b1cb64a20b14d85, melg._internal_state.state.list[548]);
            EXPECT_EQ(0xe5822e6f04b94654, melg._internal_state.state.list[687]);
            EXPECT_EQ(0x48bcfda3458883ef, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(-8870000000000000000);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x23ef9d9e302b0672, melg._internal_state.state.list[30]);
            EXPECT_EQ(0x5094e18722769c12, melg._internal_state.state.list[169]);
            EXPECT_EQ(0x8bab6be09cbdcc0e, melg._internal_state.state.list[308]);
            EXPECT_EQ(0x4dd2b81fbbd6db3a, melg._internal_state.state.list[447]);
            EXPECT_EQ(0x1dcf6ae042f2df4e, melg._internal_state.state.list[586]);
            EXPECT_EQ(0x9598d0afcf36edcf, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x17e54d8f1b236de5, 0x1aefcd3098bae3d2, 0x3662f993424e5f22, 0xddb96cea07063219, 0xffd3112cf9041fa2 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x282bd970b8c54fec, melg._internal_state.state.list[99]);
            EXPECT_EQ(0xc97c694fe3055a3a, melg._internal_state.state.list[238]);
            EXPECT_EQ(0x0f216e9ee1933a4e, melg._internal_state.state.list[377]);
            EXPECT_EQ(0xef9970ce78e6e7d0, melg._internal_state.state.list[516]);
            EXPECT_EQ(0xfa0006328ec302a5, melg._internal_state.state.list[655]);
            EXPECT_EQ(0x319283814c66b11a, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(8870000000000000000);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x8d72a9d4ef692c9f, melg._internal_state.state.list[109]);
            EXPECT_EQ(0xd0c40d7c017a67a9, melg._internal_state.state.list[248]);
            EXPECT_EQ(0x4450c907cea976ad, melg._internal_state.state.list[387]);
            EXPECT_EQ(0x05f9fc1655c71da5, melg._internal_state.state.list[526]);
            EXPECT_EQ(0xd303031f8d6093e4, melg._internal_state.state.list[665]);
            EXPECT_EQ(0x76c82ac41f7c0e44, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x57b02774f9c13018, 0x291a6fdef10bee09, 0xa758531c01076bf3, 0x8ae8f3fcd18d7b2a, 0x68ddd795f3bfd95b };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x642ccab3caeed394, melg._internal_state.state.list[39]);
            EXPECT_EQ(0x7e5fb0d2218d9336, melg._internal_state.state.list[178]);
            EXPECT_EQ(0x2a4b22fe03bd29d7, melg._internal_state.state.list[317]);
            EXPECT_EQ(0x389ddb2d561a1d05, melg._internal_state.state.list[456]);
            EXPECT_EQ(0x62aa592ae500de1c, melg._internal_state.state.list[595]);
            EXPECT_EQ(0x07939dd147b5535d, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(0.357);

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0x5fee464f36fc42c3, melg._internal_state.state.list[0]);
            EXPECT_EQ(0xd823f5cb86381fa6, melg._internal_state.state.list[139]);
            EXPECT_EQ(0x65be0e01a9329abd, melg._internal_state.state.list[278]);
            EXPECT_EQ(0x1ba644087d1e8937, melg._internal_state.state.list[417]);
            EXPECT_EQ(0x3468d12e0ed446b8, melg._internal_state.state.list[556]);
            EXPECT_EQ(0xa046f7cca1c0b35c, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0xa74def89031d7ffb, 0x48af133670a6f10f, 0x385628befdd1ee66, 0xe6f87805031745ff, 0x131ba98e409a1e35 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0x8a07cef5793ef3c8, melg._internal_state.state.list[69]);
            EXPECT_EQ(0x1cb4434025591740, melg._internal_state.state.list[208]);
            EXPECT_EQ(0xe9e09a739544f7d0, melg._internal_state.state.list[347]);
            EXPECT_EQ(0xf0dcd58a7777215b, melg._internal_state.state.list[486]);
            EXPECT_EQ(0x53bc6568e1c1c411, melg._internal_state.state.list[625]);
            EXPECT_EQ(0x97343b56e0f0af35, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }
        {
            Melg44497 melg(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));

            EXPECT_EQ(0, melg._internal_state.state.index);
            EXPECT_EQ(0xe189cea064a6f2ec, melg._internal_state.state.list[14]);
            EXPECT_EQ(0xd0ad13dad13c2a5e, melg._internal_state.state.list[153]);
            EXPECT_EQ(0x0bbb6b2e84548ecd, melg._internal_state.state.list[292]);
            EXPECT_EQ(0xbc6657fe06f2e294, melg._internal_state.state.list[431]);
            EXPECT_EQ(0xaf4a5e323cd715c5, melg._internal_state.state.list[570]);
            EXPECT_EQ(0x0986697ff828bfdf, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

            const std::uint64_t expected[]{ 0x9db82bcb804d06dd, 0x253ff071b26b0b1c, 0xba52679ecf3efe4c, 0xd52b992e5992d5cf, 0xb12d9ab98cb95735 };
            for (std::uint64_t e : expected)
                EXPECT_EQ(e, melg.next());

            EXPECT_EQ(5, melg._internal_state.state.index);
            EXPECT_EQ(0xdcff66df0615afee, melg._internal_state.state.list[83]);
            EXPECT_EQ(0xaa33b2e1b4a63293, melg._internal_state.state.list[222]);
            EXPECT_EQ(0xd9ca8cb8db937e89, melg._internal_state.state.list[361]);
            EXPECT_EQ(0x1248557ac0a50a86, melg._internal_state.state.list[500]);
            EXPECT_EQ(0x73dedf40c045d348, melg._internal_state.state.list[639]);
            EXPECT_EQ(0x65cd710420f87e23, melg._internal_state.state.list[695]);
            EXPECT_FALSE(melg._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);
        }

        EXPECT_THROW(Melg44497(-8.87e+18), FloatValueRange01Exception);
        EXPECT_THROW(Melg44497(1.0), FloatValueRange01Exception);


        //-- tests copy constructor
        {
            Melg44497 melg(melg_1);

            EXPECT_TRUE(melg_1._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_1._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_1._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move constructor
        Melg44497 melg_0;

        {
            Melg44497 melg_mem(melg_0);
            Melg44497 melg(std::move(melg_mem));

            EXPECT_TRUE(melg_0._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_0._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_0._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            Melg44497 melg;

            melg = melg_1;
            EXPECT_TRUE(melg_1._internal_state.state == melg._internal_state.state);
            EXPECT_EQ(melg_1._internal_state.gauss_next, melg._internal_state.gauss_next);
            EXPECT_EQ(melg_1._internal_state.gauss_valid, melg._internal_state.gauss_valid);
        }


        //-- tests move assignement
        Melg44497 melg;

        {
            Melg44497 melg_mem(melg_0);
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
        EXPECT_EQ(0xb13f526ded6e3453, melg._internal_state.state.list[138]);
        EXPECT_EQ(0x18f4800d3a2c81c1, melg._internal_state.state.list[277]);
        EXPECT_EQ(0x987ba75510d0d598, melg._internal_state.state.list[416]);
        EXPECT_EQ(0x5e78858ac660ba35, melg._internal_state.state.list[555]);
        EXPECT_EQ(0xfaa80a3249c34d60, melg._internal_state.state.list[694]);
        EXPECT_EQ(0xa62b70c633abd5a7, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(1);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xbeeb8da1658eec67, melg._internal_state.state.list[1]);
        EXPECT_EQ(0xa6fefb55c353a1ea, melg._internal_state.state.list[140]);
        EXPECT_EQ(0xb762715eb23cd3d7, melg._internal_state.state.list[279]);
        EXPECT_EQ(0x041fe2b35f3a75fd, melg._internal_state.state.list[418]);
        EXPECT_EQ(0x6698b211b671b46f, melg._internal_state.state.list[557]);
        EXPECT_EQ(0x6bbc0a80a7487e21, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-2);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x1f4aea7af6513705, melg._internal_state.state.list[137]);
        EXPECT_EQ(0x74345ae408f3d48a, melg._internal_state.state.list[276]);
        EXPECT_EQ(0x9f1b299ea71cb462, melg._internal_state.state.list[415]);
        EXPECT_EQ(0x803ab216bda954f7, melg._internal_state.state.list[554]);
        EXPECT_EQ(0x0a8f137c062ac922, melg._internal_state.state.list[693]);
        EXPECT_EQ(0x79a6b61c50037b24, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(9L);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xca06743146f19573, melg._internal_state.state.list[9]);
        EXPECT_EQ(0x64a7c90af8c871f4, melg._internal_state.state.list[148]);
        EXPECT_EQ(0xd788268ad8f5c07e, melg._internal_state.state.list[287]);
        EXPECT_EQ(0x5690ef2e94bde531, melg._internal_state.state.list[426]);
        EXPECT_EQ(0x72441cde256dd714, melg._internal_state.state.list[565]);
        EXPECT_EQ(0x086f6f3b7df5d2fd, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-11L);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xee186c27e50eeb68, melg._internal_state.state.list[128]);
        EXPECT_EQ(0x7b7c45529c65082b, melg._internal_state.state.list[267]);
        EXPECT_EQ(0x6865e9c640602667, melg._internal_state.state.list[406]);
        EXPECT_EQ(0xaf22e3fcd31ba75a, melg._internal_state.state.list[545]);
        EXPECT_EQ(0xf558e462ab44d6e8, melg._internal_state.state.list[684]);
        EXPECT_EQ(0x8683593aa9ac8456, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(17UL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x6cb7d6f5a174672b, melg._internal_state.state.list[17]);
        EXPECT_EQ(0x4bdf273c0cf56b26, melg._internal_state.state.list[156]);
        EXPECT_EQ(0x697e2650f0a71bec, melg._internal_state.state.list[295]);
        EXPECT_EQ(0x8b11419098f6f4b9, melg._internal_state.state.list[434]);
        EXPECT_EQ(0x1e55c2449e96aa9a, melg._internal_state.state.list[573]);
        EXPECT_EQ(0x4c5da20fafe28721, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(0x0123'4567'89ab'cdefLL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x7820abc18567251a, melg._internal_state.state.list[62]);
        EXPECT_EQ(0x2ac534eb0ce5739d, melg._internal_state.state.list[201]);
        EXPECT_EQ(0x4c897d6599c3ca4f, melg._internal_state.state.list[340]);
        EXPECT_EQ(0x55161c61f946dd8b, melg._internal_state.state.list[479]);
        EXPECT_EQ(0xf4340a4c70e46ee9, melg._internal_state.state.list[618]);
        EXPECT_EQ(0x4ec2c4758dcffadd, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(-8'870'000'000'000'000'000LL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x23ef9d9e302b0672, melg._internal_state.state.list[30]);
        EXPECT_EQ(0x5094e18722769c12, melg._internal_state.state.list[169]);
        EXPECT_EQ(0x8bab6be09cbdcc0e, melg._internal_state.state.list[308]);
        EXPECT_EQ(0x4dd2b81fbbd6db3a, melg._internal_state.state.list[447]);
        EXPECT_EQ(0x1dcf6ae042f2df4e, melg._internal_state.state.list[586]);
        EXPECT_EQ(0x9598d0afcf36edcf, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(8'870'000'000'000'000'000ULL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x8d72a9d4ef692c9f, melg._internal_state.state.list[109]);
        EXPECT_EQ(0xd0c40d7c017a67a9, melg._internal_state.state.list[248]);
        EXPECT_EQ(0x4450c907cea976ad, melg._internal_state.state.list[387]);
        EXPECT_EQ(0x05f9fc1655c71da5, melg._internal_state.state.list[526]);
        EXPECT_EQ(0xd303031f8d6093e4, melg._internal_state.state.list[665]);
        EXPECT_EQ(0x76c82ac41f7c0e44, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        melg.seed(0.357);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0x5fee464f36fc42c3, melg._internal_state.state.list[0]);
        EXPECT_EQ(0xd823f5cb86381fa6, melg._internal_state.state.list[139]);
        EXPECT_EQ(0x65be0e01a9329abd, melg._internal_state.state.list[278]);
        EXPECT_EQ(0x1ba644087d1e8937, melg._internal_state.state.list[417]);
        EXPECT_EQ(0x3468d12e0ed446b8, melg._internal_state.state.list[556]);
        EXPECT_EQ(0xa046f7cca1c0b35c, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        EXPECT_THROW(melg.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(melg.seed(-0.001), FloatValueRange01Exception);

        melg.seed(utils::UInt128(0xffff'ffff'ffff'fffe, 0xffff'ffff'ffff'fffd));
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xe189cea064a6f2ec, melg._internal_state.state.list[14]);
        EXPECT_EQ(0xd0ad13dad13c2a5e, melg._internal_state.state.list[153]);
        EXPECT_EQ(0x0bbb6b2e84548ecd, melg._internal_state.state.list[292]);
        EXPECT_EQ(0xbc6657fe06f2e294, melg._internal_state.state.list[431]);
        EXPECT_EQ(0xaf4a5e323cd715c5, melg._internal_state.state.list[570]);
        EXPECT_EQ(0x0986697ff828bfdf, melg._internal_state.state.list[695]);
        EXPECT_FALSE(melg._internal_state.gauss_valid);
        EXPECT_DOUBLE_EQ(0.0, melg._internal_state.gauss_next);

        EXPECT_THROW(melg.seed(1.0), FloatValueRange01Exception);
        EXPECT_THROW(melg.seed(-0.001), FloatValueRange01Exception);


        //-- tests _setstate(seed_)
        melg._setstate(-1LL);
        EXPECT_EQ(0, melg._internal_state.state.index);
        EXPECT_EQ(0xb13f526ded6e3453, melg._internal_state.state.list[138]);
        EXPECT_EQ(0x18f4800d3a2c81c1, melg._internal_state.state.list[277]);
        EXPECT_EQ(0x987ba75510d0d598, melg._internal_state.state.list[416]);
        EXPECT_EQ(0x5e78858ac660ba35, melg._internal_state.state.list[555]);
        EXPECT_EQ(0xfaa80a3249c34d60, melg._internal_state.state.list[694]);
        EXPECT_EQ(0xa62b70c633abd5a7, melg._internal_state.state.list[695]);
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
