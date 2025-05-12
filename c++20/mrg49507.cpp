/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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

#include "mrg49507.h"
#include "utils/uint128.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Empty constructor. */
Mrg49507::Mrg49507() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Mrg49507::Mrg49507(const int seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Mrg49507::Mrg49507(const unsigned int seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Mrg49507::Mrg49507(const long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long). */
Mrg49507::Mrg49507(const unsigned long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Mrg49507::Mrg49507(const long long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Mrg49507::Mrg49507(const unsigned long long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (utils::UInt128). */
Mrg49507::Mrg49507(const utils::UInt128& seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Mrg49507::Mrg49507(const double seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
Mrg49507::Mrg49507(const state_type& internal_state) noexcept
    : MyBaseClass(internal_state)
{}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
const Mrg49507::output_type Mrg49507::next() noexcept
{
    // The DX-1597-2-7 algorithm uses the recurrence
    //    x(i) = (-2 ^ 25 - 2 ^ 7) * (x(i - 7) + x(i - 1597)) mod(2 ^ 31 - 1)

    // evaluates indexes in suite
    const std::uint32_t index{ _internal_state.state.index };
    const std::uint32_t k7{ (index < 7) ? (index + SEED_SIZE) - 7 : index - 7 };

    // evaluates current value and modifies internal state
    const std::uint64_t value{
        (0xffff'ffff'fdff'ff80ull *  //i.e. (-2^25 - 2^7), or -67'108'992
            std::uint64_t(_internal_state.state.list[k7] + _internal_state.state.list[index])
        ) % _MODULO
    };
    _internal_state.state.list[index] = std::uint32_t(value);

    // next index
    _internal_state.state.index = (index + 1) % SEED_SIZE;

    // finally, returns pseudo random value as a 31-bits integer
    return output_type(value);
}
