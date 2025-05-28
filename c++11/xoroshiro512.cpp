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
#include "xoroshiro512.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Empty constructor. */
Xoroshiro512::Xoroshiro512() noexcept
    : MyBaseClass()
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Xoroshiro512::Xoroshiro512(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Xoroshiro512::Xoroshiro512(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Xoroshiro512::Xoroshiro512(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor(unsigned long). */
Xoroshiro512::Xoroshiro512(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Xoroshiro512::Xoroshiro512(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Xoroshiro512::Xoroshiro512(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned 128-bits). */
Xoroshiro512::Xoroshiro512(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Xoroshiro512::Xoroshiro512(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
Xoroshiro512::Xoroshiro512(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
const Xoroshiro512::output_type Xoroshiro512::next() noexcept
{
    const std::uint64_t current_s1{ _internal_state.state.list[1] };

    // advances the internal state of the PRNG
    _internal_state.state.list[2] ^= _internal_state.state.list[0];
    _internal_state.state.list[5] ^= current_s1;  // _internal_state.state[1];
    _internal_state.state.list[1] ^= _internal_state.state.list[2];
    _internal_state.state.list[7] ^= _internal_state.state.list[3];
    _internal_state.state.list[3] ^= _internal_state.state.list[4];
    _internal_state.state.list[4] ^= _internal_state.state.list[5];
    _internal_state.state.list[0] ^= _internal_state.state.list[6];
    _internal_state.state.list[6] ^= _internal_state.state.list[7];
    _internal_state.state.list[6] ^= current_s1 << 11;
    _internal_state.state.list[7] = utils::rot_left(_internal_state.state.list[7], 21);

    // finally, returns pseudo random value as a 64-bits integer
    return utils::rot_left(current_s1 * 5, 7) * 9;
}
