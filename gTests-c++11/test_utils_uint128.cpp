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
#include <utility>

#include "gtest/gtest.h"

#include "utils/uint128.h"


//===========================================================================
namespace tests_utils
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteUtils, TestsUtilsUInt128)
    {
        //-- tests valued constructor (UInt128) and equality/inequality operator
        utils::UInt128 v128(1, 3217);
        EXPECT_EQ(1ULL, v128.hi);
        EXPECT_EQ(3217ULL, v128.lo);
        EXPECT_TRUE(v128 == v128);
        EXPECT_FALSE(v128 != v128);


        //-- tests valued constructor (integer) and equality/inequality operator
        utils::UInt128 v128_(3217ULL);
        EXPECT_EQ(1ULL, v128.hi);
        EXPECT_EQ(3217ULL, v128.lo);
        EXPECT_TRUE(v128_ == std::int16_t(3217));
        EXPECT_TRUE(v128_ == std::uint16_t(3217));
        EXPECT_TRUE(v128_ == 3217L);
        EXPECT_TRUE(v128_ == 3217UL);
        EXPECT_TRUE(v128_ == 3217LL);
        EXPECT_TRUE(v128_ == 3217ULL);
        EXPECT_FALSE(v128_ != std::int16_t(3217));
        EXPECT_FALSE(v128_ != std::uint16_t(3217));
        EXPECT_FALSE(v128_ != 3217L);
        EXPECT_FALSE(v128_ != 3217UL);
        EXPECT_FALSE(v128_ != 3217LL);
        EXPECT_FALSE(v128_ != 3217ULL);


        //-- tests empty constructor and equality/inequality operator
        utils::UInt128 v0;
        EXPECT_EQ(0ull, v0.hi);
        EXPECT_EQ(0ull, v0.lo);
        EXPECT_TRUE(v0 == std::int8_t(0));
        EXPECT_TRUE(v0 == std::uint8_t(0));
        EXPECT_TRUE(v0 == std::int16_t(0));
        EXPECT_TRUE(v0 == std::uint16_t(0));
        EXPECT_TRUE(v0 == 0L);
        EXPECT_TRUE(v0 == 0UL);
        EXPECT_TRUE(v0 == 0LL);
        EXPECT_TRUE(v0 == 0ULL);
        EXPECT_FALSE(v0 != std::int8_t(0));
        EXPECT_FALSE(v0 != std::uint8_t(0));
        EXPECT_FALSE(v0 != std::int16_t(0));
        EXPECT_FALSE(v0 != std::uint16_t(0));
        EXPECT_FALSE(v0 != 0L);
        EXPECT_FALSE(v0 != 0UL);
        EXPECT_FALSE(v0 != 0LL);
        EXPECT_FALSE(v0 != 0ULL);


        //-- tests copy constructor and equality/inequality operator
        utils::UInt128 v(v128);
        EXPECT_EQ(v.hi, v128.hi);
        EXPECT_EQ(v.lo, v128.lo);
        EXPECT_EQ(v, v128);
        EXPECT_EQ(v128, v);
        EXPECT_NE(v, v128_);
        EXPECT_NE(v128_, v);
        EXPECT_TRUE(v == v128);
        EXPECT_TRUE(v128 == v);
        EXPECT_FALSE(v != v128);
        EXPECT_FALSE(v128 != v);
        EXPECT_NE(v, v128_);
        EXPECT_NE(v128_, v);
    

        //-- tests move constructor and equality/inequality operator
        utils::UInt128 vtmp(v);
        utils::UInt128 vc{ std::move(vtmp) };
        EXPECT_EQ(vc.hi, v.hi);
        EXPECT_EQ(vc.lo, v.lo);
        EXPECT_EQ(vc, v);
        EXPECT_EQ(v, vc);
        EXPECT_NE(vc, v128_);
        EXPECT_NE(v128_, vc);
        EXPECT_TRUE(vc == v);
        EXPECT_TRUE(v == vc);
        EXPECT_FALSE(vc != v);
        EXPECT_FALSE(v != vc);
        EXPECT_NE(vc, v128_);
        EXPECT_NE(v128_, vc);


        //-- tests copy assignment and equality/inequality operator
        vc = v128_;
        EXPECT_EQ(vc.hi, v128_.hi);
        EXPECT_EQ(vc.lo, v128_.lo);
        EXPECT_EQ(vc, v128_);
        EXPECT_EQ(v128_, vc);
        EXPECT_NE(vc, v128);
        EXPECT_NE(v128, vc);
        EXPECT_TRUE(vc == v128_);
        EXPECT_TRUE(v128_ == vc);
        EXPECT_FALSE(vc != v128_);
        EXPECT_FALSE(v128_ != vc);
        EXPECT_NE(vc, v128);
        EXPECT_NE(v128, vc);


        //-- tests move assignment and equality/inequality operator
        vtmp = v;
        vc = std::move(vtmp);
        EXPECT_EQ(vc.hi, v.hi);
        EXPECT_EQ(vc.lo, v.lo);
        EXPECT_EQ(vc, v);
        EXPECT_EQ(v, vc);
        EXPECT_NE(vc, v128_);
        EXPECT_NE(v128_, vc);
        EXPECT_TRUE(vc == v);
        EXPECT_TRUE(v == vc);
        EXPECT_FALSE(vc != v);
        EXPECT_FALSE(v != vc);
        EXPECT_NE(vc, v128_);
        EXPECT_NE(v128_, vc);


        //-- tests integer assignment
        v = std::int8_t(1);
        EXPECT_TRUE(v == 1ull);
        v = std::int16_t(2);
        EXPECT_TRUE(v == 2ULL);
        v = 3L;
        EXPECT_TRUE(v == 3ULL);
        v = 4LL;
        EXPECT_TRUE(v == 4ULL);
        v = std::uint8_t(1);
        EXPECT_TRUE(v == 1ull);
        v = std::uint16_t(2);
        EXPECT_TRUE(v == 2ULL);
        v = 3UL;
        EXPECT_TRUE(v == 3ULL);
        v = 4ULL;
        EXPECT_TRUE(v == 4ULL);


        //-- tests cast operator (double)
        const double d{ double(vc) };
        const double dd{ 18.446'744'073'709'551'616e+18 * vc.hi + vc.lo };
        EXPECT_DOUBLE_EQ(d, dd);


        //-- tests cast operator (long double)
        const long double ld{ long double(vc) };
        const long double ldd{ 18.446'744'073'709'551'616e+18L * vc.hi + vc.lo };
        EXPECT_TRUE(ld == ldd);


        //-- tests add operator (UInt128)
        utils::UInt128 va{ v128 + v128 };  // Notice: runs code of operator +=(const UInt128)
        EXPECT_EQ(va.hi, v128.hi + v128.hi);
        EXPECT_EQ(va.lo, v128.lo + v128.lo);
        utils::UInt128 u1(1);
        utils::UInt128 u2(0xffff'ffff'ffff'ffffULL, 0xffff'ffff'ffff'fffeULL);
        utils::UInt128 u = u1 + u2;
        EXPECT_EQ(u.hi, 0xffff'ffff'ffff'ffffULL);
        EXPECT_EQ(u.lo, 0xffff'ffff'ffff'ffffULL);
        utils::UInt128 u3 = u2 + u2;
        EXPECT_EQ(u3.hi, 0xffff'ffff'ffff'ffffULL);
        EXPECT_EQ(u3.lo, 0xffff'ffff'ffff'fffcULL);
        u3 = 4;
        u3 += u2 + u2;
        EXPECT_TRUE(u3 == 0);


        //-- tests add operator (integer)
        v = u2 + std::int8_t(1);  // Notice: runs also code of operator +=(std::int8_t)
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::int8_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::int8_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::int8_t(2) + u2;
        EXPECT_EQ(v, 0ULL);

        v = u2 + std::uint8_t(1);
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::uint8_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::uint8_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::uint8_t(2) + u2;
        EXPECT_EQ(v, 0ULL);

        v = u2 + std::int16_t(1);
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::int16_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::int16_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::int16_t(2) + u2;
        EXPECT_EQ(v, 0ULL);

        v = u2 + std::uint16_t(1);
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::uint16_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::uint16_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::uint16_t(2) + u2;
        EXPECT_EQ(v, 0ULL);

        v = u2 + std::int32_t(1);
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::int32_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::int32_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::int32_t(2) + u2;
        EXPECT_EQ(v, 0ULL);

        v = u2 + std::uint32_t(1);
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::uint32_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::uint32_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::uint32_t(2) + u2;
        EXPECT_EQ(v, 0ULL);

        v = u2 + std::int64_t(1);
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::int64_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::int64_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::int64_t(2) + u2;
        EXPECT_EQ(v, 0ULL);

        v = u2 + std::uint64_t(1);
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = std::uint64_t(1) + u2;
        EXPECT_EQ(v.hi, u2.hi);
        EXPECT_EQ(v.lo, u2.lo + 1ull);
        v = u2 + std::uint64_t(2);
        EXPECT_EQ(v, 0ULL);
        v = std::uint64_t(2) + u2;
        EXPECT_EQ(v, 0ULL);


        //-- tests bit-or operator (UInt128)
        v.hi = v.lo = 1;  // Notice: runs code of operator |=(const UInt128)
        va = 0;
        va = va | v;
        EXPECT_EQ(va, v);
        va = va | v;
        EXPECT_EQ(va, v);


        //-- tests bit-or operator (integer)
        va = 0;
        va = va | std::int8_t(1);  // Notice: runs code of operator |=(const UInt128)
        EXPECT_EQ(va, 1);
        va = va | std::int8_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::int8_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::int8_t(1) | va;
        EXPECT_EQ(va, 1);

        va = 0;
        va = va | std::uint8_t(1);
        EXPECT_EQ(va, 1);
        va = va | std::uint8_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::uint8_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::uint8_t(1) | va;
        EXPECT_EQ(va, 1);

        va = 0;
        va = va | std::int16_t(1);
        EXPECT_EQ(va, 1);
        va = va | std::int16_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::int16_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::int16_t(1) | va;
        EXPECT_EQ(va, 1);

        va = 0;
        va = va | std::uint16_t(1);
        EXPECT_EQ(va, 1);
        va = va | std::uint16_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::uint16_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::uint16_t(1) | va;
        EXPECT_EQ(va, 1);

        va = 0;
        va = va | std::int32_t(1);
        EXPECT_EQ(va, 1);
        va = va | std::int32_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::int32_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::int32_t(1) | va;
        EXPECT_EQ(va, 1);

        va = 0;
        va = va | std::uint32_t(1);
        EXPECT_EQ(va, 1);
        va = va | std::uint32_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::uint32_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::uint32_t(1) | va;
        EXPECT_EQ(va, 1);

        va = 0;
        va = va | std::int64_t(1);
        EXPECT_EQ(va, 1);
        va = va | std::int64_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::int64_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::int64_t(1) | va;
        EXPECT_EQ(va, 1);

        va = 0;
        va = va | std::uint64_t(1);
        EXPECT_EQ(va, 1);
        va = va | std::uint64_t(1);
        EXPECT_EQ(va, 1);
        va = 0;
        va = std::uint64_t(1) | va;
        EXPECT_EQ(va, 1);
        va = std::uint64_t(1) | va;
        EXPECT_EQ(va, 1);


        //-- tests multiply operator (UInt128)
        va = utils::UInt128(1, 0xffff'ffff'ffff'ffffULL);
        vc = 0xffff'ffff'ffff'fffeULL;
        v = va * vc;  // Notice: runs code of operator *=(const UInt128)
        EXPECT_EQ(v.hi, 0xffff'ffff'ffff'fffbULL);
        EXPECT_EQ(v.lo, 2);
        va = 100;
        vc = 1000;
        v = va * vc;
        EXPECT_EQ(v, 100'000ULL);
        va.hi = 100;
        va.lo = 0;
        v = va * vc;
        EXPECT_EQ(100'000ULL, v.hi);
        va.hi = 100;
        vc.hi = 1000;
        va.lo = vc.lo = 0;
        v = va * vc;
        EXPECT_EQ(0, v);
        va.lo = vc.lo = 3917;
        v = va * vc;
        EXPECT_EQ(3917 * 3917, v.lo);
        EXPECT_EQ(4'308'700ULL, v.hi);


        //-- tests multiply operator (integers)
        va = utils::UInt128(1, 0xffff'ffff'ffff'ffffULL);
        v = va * 1;  // Notice: runs code of operator *=(IntT)
        EXPECT_EQ(v, va);
        v = 1 * va;
        EXPECT_EQ(v, va);
        v = va * 0;
        EXPECT_EQ(v, 0);
        v = 0 * va;
        EXPECT_EQ(v, 0);

        va.hi = 0xffff'ffffULL;
        v = va * std::int8_t(3);
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fffdULL);
        EXPECT_EQ(v.hi, 0x2'ffff'ffffULL);
        v = std::int8_t(4) * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fffcULL);
        EXPECT_EQ(v.hi, 0x3'ffff'ffffULL);

        v = va * std::uint8_t(5);
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fffbULL);
        EXPECT_EQ(v.hi, 0x4'ffff'ffffULL);
        v = std::uint8_t(6) * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fffaULL);
        EXPECT_EQ(v.hi, 0x5'ffff'ffffULL);

        v = va * std::int16_t(7);
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff9ULL);
        EXPECT_EQ(v.hi, 0x6'ffff'ffffULL);
        v = std::int16_t(8) * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff8ULL);
        EXPECT_EQ(v.hi, 0x7'ffff'ffffULL);

        v = va * std::uint16_t(9);
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff7ULL);
        EXPECT_EQ(v.hi, 0x8'ffff'ffffULL);
        v = std::uint16_t(10) * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff6ULL);
        EXPECT_EQ(v.hi, 0x9'ffff'ffffULL);

        v = va * 11L;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff5ULL);
        EXPECT_EQ(v.hi, 0xa'ffff'ffffULL);
        v = 12L * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff4ULL);
        EXPECT_EQ(v.hi, 0xb'ffff'ffffULL);

        v = va * 13UL;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff3ULL);
        EXPECT_EQ(v.hi, 0xc'ffff'ffffULL);
        v = 14UL * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff2ULL);
        EXPECT_EQ(v.hi, 0xd'ffff'ffffULL);

        v = va * 15LL;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff1ULL);
        EXPECT_EQ(v.hi, 0xe'ffff'ffffULL);
        v = 16LL * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'fff0ULL);
        EXPECT_EQ(v.hi, 0xf'ffff'ffffULL);

        v = va * 17ULL;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'ffefULL);
        EXPECT_EQ(v.hi, 0x10'ffff'ffffULL);
        v = 18ULL * va;
        EXPECT_EQ(v.lo, 0xffff'ffff'ffff'ffeeULL);
        EXPECT_EQ(v.hi, 0x11'ffff'ffffULL);

        v = va * 0xffff'ffff'ffff'fffeULL;
        EXPECT_EQ(v.lo, 2ULL);
        EXPECT_EQ(v.hi, 0xffff'fffd'ffff'ffffULL);  // Notice: correct value is 0xffff'ffff'ffff'fffd'ffff'ffff, truncated on the 64 lower bits


        //-- tests right-shift operator
        std::uint64_t mask_hi{ 0xaaaa'aaaa'aaaa'aaaaULL };
        std::uint64_t mask_lo{ 0xaaaa'aaaa'aaaa'aaaaULL };

        va.hi = mask_hi;
        va.lo = mask_lo;
        v = va >> 0;  // Notice: runs code of operator >>=
        EXPECT_EQ(v, va);

        for (int i = 1; i < 64; i+=2) {
            v = va >> i;
            mask_hi >>= 1;
            EXPECT_EQ(v.hi, mask_hi);
            EXPECT_EQ(v.lo, mask_lo >> 1);

            v = va >> (i + 1);
            mask_hi >>= 1;
            EXPECT_EQ(v.hi, mask_hi);
            EXPECT_EQ(v.lo, mask_lo);
        }
        
        for (int i = 65; i < 128; ++i) {
            v = va >> i;
            mask_lo >>= 1;
            EXPECT_EQ(v.hi, 0);
            EXPECT_EQ(v.lo, mask_lo);
        }

        for (int i = 128; i < 130; ++i) {
            v = va >> i;
            EXPECT_EQ(v, 0ULL);
        }


        //-- tests left-shift operator
        mask_hi = 0xaaaa'aaaa'aaaa'aaaaULL;
        mask_lo = 0xaaaa'aaaa'aaaa'aaaaULL;

        va.hi = mask_hi;
        va.lo = mask_lo;
        v = va << 0;  // Notice: runs code of operator <<=
        EXPECT_EQ(v, va);

        for (int i = 1; i < 64; i += 2) {
            v = va << i;
            mask_lo <<= 1;
            EXPECT_EQ(v.hi, mask_hi >> 1);  // Notice: '>>' is the correct shifting here, to swap btw. 0xaaa... and 0x555...!
            EXPECT_EQ(v.lo, mask_lo);

            v = va << (i + 1);
            mask_lo <<= 1;
            EXPECT_EQ(v.hi, mask_hi);
            EXPECT_EQ(v.lo, mask_lo);
        }

        for (int i = 65; i < 128; ++i) {
            v = va << i;
            mask_hi <<= 1;
            EXPECT_EQ(v.hi, mask_hi);
            EXPECT_EQ(v.lo, 0);
        }

        for (int i = 128; i < 130; ++i) {
            v = va << i;
            EXPECT_EQ(v, 0ULL);
        }


        //-- tests bit-xor operator
        for (int i = 0; i < 128; ++i) {
            v = 0;
            va = utils::UInt128(1) << i;
            v = v ^ va;  // Notice: runs code of operator ^=
            EXPECT_TRUE(v == va);
        }

        mask_lo = 1ULL;
        for (int i = 0; i < 64; ++i, mask_lo <<= 1) {
            v = 0;
            v = v ^ mask_lo;
            EXPECT_TRUE(v == mask_lo);
        }

        mask_lo = 1ULL;
        for (int i = 0; i < 64; ++i, mask_lo <<= 1) {
            v = 0;
            v = mask_lo ^ v;
            EXPECT_TRUE(v == mask_lo);
        }

        const utils::UInt128 vf(0xffff'ffff'ffff'ffffULL, 0xffff'ffff'ffff'ffffULL);
        for (int i = 0; i < 128; ++i) {
            v = vf;
            va = utils::UInt128(1) << i;
            v = v ^ va;  // Notice: runs code of operator ^=
            EXPECT_EQ(v.hi, ~va.hi);
            EXPECT_EQ(v.lo, ~va.lo);
        }

        mask_lo = 1ULL;
        for (int i = 0; i < 64; ++i, mask_lo <<= 1) {
            v = vf;
            v = v ^ mask_lo;
            EXPECT_EQ(v.hi, vf.hi);
            EXPECT_EQ(v.lo, ~mask_lo);
        }

        mask_lo = 1ULL;
        for (int i = 0; i < 64; ++i, mask_lo <<= 1) {
            v = vf;
            v = mask_lo ^ v;
            EXPECT_EQ(v.hi, vf.hi);
            EXPECT_EQ(v.lo, ~mask_lo);
        }

    }
}
