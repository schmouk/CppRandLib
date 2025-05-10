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
#include "mrg287.h"
#include "utils/uint128.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Empty constructor. */
Mrg287::Mrg287() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Mrg287::Mrg287(const int seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Mrg287::Mrg287(const unsigned int seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Mrg287::Mrg287(const long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long). */
Mrg287::Mrg287(const unsigned long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Mrg287::Mrg287(const long long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Mrg287::Mrg287(const unsigned long long seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (utils::UInt128). */
Mrg287::Mrg287(const utils::UInt128& seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Mrg287::Mrg287(const double seed_) noexcept
    : MyBaseClass(seed_)
{}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
Mrg287::Mrg287(const state_type& internal_state) noexcept
    : MyBaseClass(internal_state)
{}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
const Mrg287::output_type Mrg287::next() noexcept
{
    // The Marsa - LIBF4 version uses the recurrence
    //    x(i) = (x(i-55) + x(i-119) + x(i-179) + x(i-256)) mod 2 ^ 32

    // evaluates indexes in suite
    const std::uint32_t index{ _internal_state.state.index };
    const std::uint32_t k55{ (index < 55) ? (index + SEED_SIZE) - 55 : index - 55 };
    const std::uint32_t k119{ (index < 119) ? (index + SEED_SIZE) - 119 : index - 119 };
    const std::uint32_t k179{ (index < 179) ? (index + SEED_SIZE) - 179 : index - 179 };

    // evaluates current value and modifies internal state
    const std::uint32_t value{
        _internal_state.state.list[k55] +
        _internal_state.state.list[k119] +
        _internal_state.state.list[k179] +
        _internal_state.state.list[index]
    };
    _internal_state.state.list[index] = value;

    // next index
    _internal_state.state.index = (index + 1) & _INDEX_MODULO;

    // finally, returns pseudo random value as a 32-bits integer
    return value;
}
