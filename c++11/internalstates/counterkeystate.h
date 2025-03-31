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
#include <algorithm>
#include <type_traits>
#include <vector>

#include "utils/seed_generation.h"
#include "utils/splitmix.h"


//===========================================================================
/** @brief The internal state of counter-based Pseudo Random Numbers Generators. */
struct CounterKeyState
{
    using value_type = std::uint64_t;

    value_type counter{ 0 };
    value_type key{ 0 };


    inline void init_key() noexcept
    {}

    /** @brief Initalizes the attribute key according to the original recommendations in document [9] - see file README.md. */
    inline void init_key(const value_type seed) noexcept;

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
void CounterKeyState::init_key(
    const value_type seed
) noexcept
{
    constexpr double NORMALIZE{ 0.5 / double(0x8000'0000'0000'0000ull) };

    std::vector<value_type> hex_digits{ 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
    utils::SplitMix64 init_rand(seed);

    key = 0;

    // let's initialize the 8 high hexa digits of the key - all different
    for (std::uint32_t n = 15; n >= 8; ) {
        const std::uint32_t i{ std::uint32_t(double(n) * double(init_rand()) * NORMALIZE) };

        key = (key << 4) + hex_digits[i];
        std::swap(hex_digits[i], hex_digits[--n]);
    }

    // then let's initialize the 8 low hexa digits of the key - all different
    for (std::uint32_t n = 15; n >= 8; ) {
        const std::uint32_t i{ std::uint32_t(double(n) * double(init_rand()) * NORMALIZE) };

        key = (key << 4) + hex_digits[i];
        std::swap(hex_digits[i], hex_digits[--n]);
    }

    key |= 1;  // notice: key must be odd
}