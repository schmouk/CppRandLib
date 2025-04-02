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
#include "melg44497.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Melg44497::output_type Melg44497::next() noexcept
{
    const std::uint32_t i{ _internal_state.state.index };
    const std::uint32_t i_1{ (i + 1) % 695 };

    // sets next index in states list
    _internal_state.state.index = i_1;

    // modifies the internal states
    const value_type x{
        (_internal_state.state.list[i]   & 0xffff'8000'0000'0000ull) |  // notice: | instead of ^ as erroneously printed in [11]
        (_internal_state.state.list[i_1] & 0x0000'7fff'ffff'ffffull)
    };
    value_type s695{ _internal_state.state.list[695] };

    s695 = (x >> 1) ^ _A_COND[x & 0x01] ^ _internal_state.state.list[(i + 373) % 695] ^ s695 ^ (s695 << 37);
    _internal_state.state.list[695] = s695;

    const value_type si{ x ^ s695 ^ (s695 >> 14) };
    _internal_state.state.list[i] = si;

    // finally, returns pseudo random value as a 64-bits integer
    return si ^ (si << 6) ^ (_internal_state.state.list[(i + 95) % 695] & 0x06fb'bee2'9aae'fd91);
}
