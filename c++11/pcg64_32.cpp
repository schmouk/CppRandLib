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

#include "pcg64_32.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Valued constructor (int). */
Pcg64_32::Pcg64_32() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Pcg64_32::Pcg64_32(const int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Pcg64_32::Pcg64_32(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Pcg64_32::Pcg64_32(const long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long). */
Pcg64_32::Pcg64_32(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Pcg64_32::Pcg64_32(const long long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Pcg64_32::Pcg64_32(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned 128-bits). */
Pcg64_32::Pcg64_32(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Pcg64_32::Pcg64_32(const double seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
const Pcg64_32::output_type Pcg64_32::next() noexcept
{
    const value_type previous_state{ _internal_state.state };
    const unsigned int random_shift{ previous_state >> 61 };  // random shift is set with the 3 upper bits of the internal state

    // evaluates next state value
    _internal_state.state = 0x5851'f42d'4c95'7f2dull * previous_state + 0x1405'7b7e'f767'814full;

    // computes the permutated output
    return ((previous_state ^ (previous_state >> 22)) >> (22 + random_shift)) & _MODULO;
}

//---------------------------------------------------------------------------
/** Initializes internal state (empty signature). */
inline void Pcg64_32::seed() noexcept
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
void Pcg64_32::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
void Pcg64_32::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
void Pcg64_32::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
void Pcg64_32::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
void Pcg64_32::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
void Pcg64_32::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
void Pcg64_32::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
void Pcg64_32::seed(const double seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state with a 64-bits integer seed. */
void Pcg64_32::_setstate(const std::uint64_t seed_) noexcept
{
    _internal_state.state = seed_;
}

//---------------------------------------------------------------------------
/** Sets the internal state with a 128-bits integer seed. */
void Pcg64_32::_setstate(const utils::UInt128& seed_) noexcept
{
    _setstate(seed_.lo);
}
