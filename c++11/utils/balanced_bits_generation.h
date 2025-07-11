#pragma once
/*
MIT License

Copyright (c) 2025 Philippe Schmouker, ph.schmouker (at) gmail.com

This file is part of library CppRandLib.

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
#include <cassert>
#include <cstdint>
#include <type_traits>

#include "splitmix.h"


//===========================================================================
namespace utils
{
    //=======================================================================
    /** @brief Generates balanced bits patterns in integers.
    *
    * This is a free local  implementation  of  the  algorithm  described  in
    * document  referenced  [9] in README.md and of the coding of all 64-bits
    * keys generation that  is  available  in  file  keys/keys.c  in  related
    * software package https://squaresrng.wixsite.com/rand.
    * ( Bernard Widynski1, March 2022, extracted text from keys/keys.c:
    *   The keys are created so that the upper 8 digits are different and also  *
    *   that the lower 8 digits are different.  The lower 8 digits are created  *
    *   systematically so that all possible  combinations  are  produced.  The  *
    *   ninth digit is chosen to be different than the eighth digit.  The rest  *
    *   of the upper 7 digits are chosen randomly.  For any two keys produced,  *
    *   it  is  certain  that  at  least one digit is different in the lower 9  *
    *   digits.  Testing has shown that this prevents  similarities  that  can  *
    *   arise in streams produced by keys that vary only in the upper digits. ) *
    *
    * Notice: Should you need to call this function many times to  initialize 
    * multiple streams of PRNGs,  ensure that no two initial seeds values are 
    * finaly the same on their 9 lowest hexa digits.
    */
    template<typename IntT>
    inline const IntT balanced_bits_generation(const std::uint64_t seed)
    {
        static_assert(std::is_integral<IntT>::value, "balanced bits are only generated for integers.");

        constexpr std::uint32_t HEX_DIGITS_COUNT{ 2 * sizeof(IntT) };
        constexpr double NORMALIZE{ 1.0 / (1ull << 32) };

        std::uint64_t hex_digits[]{ 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
        utils::SplitMix32 splitmix_32(seed);

        IntT balanced_value{ 0 };

        // let's initialize the up to 8 low hexa digits of the returned value - all different (i.e. returned value on 32-bits or less)
        for (std::uint32_t n = 0; n < (HEX_DIGITS_COUNT < 8 ? HEX_DIGITS_COUNT : 8); ++n) {
            const std::uint32_t i{ std::uint32_t(double(15-n) * double(splitmix_32()) * NORMALIZE) };

            balanced_value = IntT((std::uint64_t(balanced_value) << 4) + hex_digits[i]);
            std::swap(hex_digits[i], hex_digits[14-n]);
        }

        // if more than 8 hexa digits to evaluate (i.e. 64-bits returned value)
        if (HEX_DIGITS_COUNT > 8) {
            // let's choose the 9th one as different from the 8th one
            std::swap(hex_digits[7], hex_digits[14]);
            const std::uint32_t i{ std::uint32_t(14.0 * double(splitmix_32()) * NORMALIZE) };

            balanced_value = IntT((std::uint64_t(balanced_value) << 4) + hex_digits[i]);
            std::swap(hex_digits[i], hex_digits[14]);

            // finaly, let's initialize the 7 high hexa digits of the returned value - all different
            for (std::uint32_t n = 0; n < 7; ++n) {
                const std::uint32_t i{ std::uint32_t(double(14-n) * double(splitmix_32()) * NORMALIZE) };

                balanced_value = IntT((std::uint64_t(balanced_value) << 4) + hex_digits[i]);
                std::swap(hex_digits[i], hex_digits[13 - n]);
            }
        }

        return balanced_value;
    }
}