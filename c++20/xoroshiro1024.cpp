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
#include <cstdint>

#include "utils/bits_rotations.h"
#include "utils/uint128.h"
#include "xoroshiro1024.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Empty constructor. */
Xoroshiro1024::Xoroshiro1024() noexcept
    : MyBaseClass()
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Xoroshiro1024::Xoroshiro1024(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Xoroshiro1024::Xoroshiro1024(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Xoroshiro1024::Xoroshiro1024(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor(unsigned long). */
Xoroshiro1024::Xoroshiro1024(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Xoroshiro1024::Xoroshiro1024(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Xoroshiro1024::Xoroshiro1024(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned 128-bits). */
Xoroshiro1024::Xoroshiro1024(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Xoroshiro1024::Xoroshiro1024(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
Xoroshiro1024::Xoroshiro1024(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
const Xoroshiro1024::output_type Xoroshiro1024::next() noexcept
{
    const std::uint32_t previous_index{ _internal_state.state.index };
    const std::uint32_t new_index{ (previous_index + 1) & 0xf };

    // advances the internal state of the PRNG
    const std::uint64_t s_low{ _internal_state.state.list[new_index] };
    const std::uint64_t s_high{ _internal_state.state.list[previous_index] ^ s_low };

    _internal_state.state.list[previous_index] = utils::rot_left(s_low, 25) ^ s_high ^ (s_high << 27);
    _internal_state.state.list[new_index] = utils::rot_left(s_high, 36);

    _internal_state.state.index = new_index;

    // finally, returns pseudo random value as a 64-bits integer
    return utils::rot_left(s_low * 5, 7) * 9;
}
