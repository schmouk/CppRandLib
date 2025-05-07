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
#include <cstdint>

#include "cwg128_64.h"


//===========================================================================
/** Valued constructor (int). */
Cwg128_64::Cwg128_64(const int seed) noexcept
    : MyBaseClass(std::uint64_t(seed))
{}

/** Valued constructor (unsigned int). */
Cwg128_64::Cwg128_64(const unsigned int seed) noexcept
    : MyBaseClass(std::uint64_t(seed))
{}

/** Valued constructor (long). */
Cwg128_64::Cwg128_64(const long seed) noexcept
    : MyBaseClass(std::uint64_t(seed))
{}

/** Valued constructor (unsigned long). */
Cwg128_64::Cwg128_64(const unsigned long seed) noexcept
    : MyBaseClass(std::uint64_t(seed))
{}

/** Valued constructor (long long). */
Cwg128_64::Cwg128_64(const long long seed) noexcept
    : MyBaseClass(std::uint64_t(seed))
{}

/** Valued constructor (unsigned long long). */
Cwg128_64::Cwg128_64(const unsigned long long seed) noexcept
    : MyBaseClass(std::uint64_t(seed))
{}

/** Valued constructor (unsigned 128-bits). */
Cwg128_64::Cwg128_64(const utils::UInt128& seed_) noexcept
    : MyBaseClass(0)
{
    seed(seed_);
}

/** Valued constructor (double). */
Cwg128_64::Cwg128_64(const double seed) noexcept
    : MyBaseClass(seed)
{}

/** Valued constructor (full state). */
Cwg128_64::Cwg128_64(const state_type& internal_state) noexcept
    : MyBaseClass(internal_state)
{}

/** The internal PRNG algorithm. */
const Cwg128_64::output_type Cwg128_64::next() noexcept
{
    // evaluates next internal state
    _internal_state.state.a += _internal_state.state.state.lo;
    _internal_state.state.weyl += _internal_state.state.s;
    _internal_state.state.state = ((_internal_state.state.state | 1) * (_internal_state.state.a >> 1)) ^ _internal_state.state.weyl;

    // returns the xored - shifted output value
    return (_internal_state.state.state ^ (_internal_state.state.a >> 48)).lo;
}

/** Initializes internal state (empty signature). */
void Cwg128_64::seed() noexcept
{
    MyBaseClass::seed();
}

/** Initializes internal state (int). */
void Cwg128_64::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned int). */
void Cwg128_64::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (long). */
void Cwg128_64::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned long). */
void Cwg128_64::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (long long). */
void Cwg128_64::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned long long). */
void Cwg128_64::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

/** Initializes internal state (unsigned 128-bits). */
void Cwg128_64::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

/** Initializes internal state (double). */
void Cwg128_64::seed(const double seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

/** Sets the internal state with a 64-bits integer seed. */
void Cwg128_64::_setstate(const std::uint64_t seed_) noexcept
{
    MyBaseClass::_setstate(seed_);
}

/** Sets the internal state with a 128-bits integer seed. */
void Cwg128_64::_setstate(const utils::UInt128 seed_) noexcept
{
    _internal_state.state.seed(seed_);
}
