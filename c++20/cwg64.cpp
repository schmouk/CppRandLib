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

#include "cwg64.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Cwg64::output_type Cwg64::next() noexcept
{
    // evaluates next internal state
    _internal_state.state.a += _internal_state.state.state;
    _internal_state.state.weyl += _internal_state.state.s;
    _internal_state.state.state = ((_internal_state.state.state >> 1) * (_internal_state.state.a | 1)) ^ _internal_state.state.weyl;

    // returns the xored - shifted output value
    return _internal_state.state.state ^ (_internal_state.state.a >> 48);
}

/** Initializes internal state (empty signature). */
void Cwg64::seed() noexcept
{
    MyBaseClass::seed();
}

/** Initializes internal state (int). */
void Cwg64::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned int). */
void Cwg64::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (long). */
void Cwg64::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned long). */
void Cwg64::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (long long). */
void Cwg64::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned long long). */
void Cwg64::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

/** Initializes internal state (double). */
void Cwg64::seed(const double seed_) noexcept
{
    MyBaseClass::seed(seed_);
}
