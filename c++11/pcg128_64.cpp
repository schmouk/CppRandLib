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

#include "pcg128_64.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Pcg128_64::output_type Pcg128_64::next() noexcept
{
    utils::UInt128 previous_state{ _internal_state.state };

    // evaluates next internal state value, LCG algorithm, 128-bits arithmetic
    _internal_state.state = _a * previous_state + _c;

    // then evaluates and returns the permutated output value
    const unsigned int random_rotation{ previous_state.hi >> 58 };  // random right rotation count is set with the 6 upper bits of internal state
    const output_type value{ previous_state.lo ^ previous_state.hi };
    return (value >> random_rotation) | ((value & ((1ull << random_rotation) - 1ull))) << (64 - random_rotation);
}


//===========================================================================
/** The private constants used for the engine algorithm. */
const utils::UInt128 Pcg128_64::_a(0x2360'ed05'1fc6'5da4ull, 0x4385'df64'9fcc'f645ull);
const utils::UInt128 Pcg128_64::_c(0x5851'f42d'4c95'7f2dull, 0x1405'7b7e'f767'814full);
