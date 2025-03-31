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
#include "melg607.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Melg607::output_type Melg607::next() noexcept
{
    const std::uint32_t i{ _internal_state.state.index };
    const std::uint32_t i_1{ (i + 1) % 9 };

    // sets next index in states list
    _internal_state.state.index = i_1;

    // modifies the internal states
    const value_type x{
        (_internal_state.state.list[i]   & 0xffff'ffff'8000'0000ull) |  // notice: | instead of ^ as erroneously printed in [11]
        (_internal_state.state.list[i_1] & 0x0000'0000'7fff'ffffull)
    };
    value_type s9{ _internal_state.state.list[9] };

    s9 = (x >> 1) ^ _A_COND[x & 0x01] ^ _internal_state.state.list[(i + 5) % 9] ^ s9 ^ (s9 << 13);
    _internal_state.state.list[9] = s9;

    const value_type si{ x ^ s9 ^ (s9 >> 35) };
    _internal_state.state.list[i] = si;

    // finally, returns pseudo random value as a 64-bits integer
    return si ^ (si << 30) ^ (_internal_state.state.list[(i + 3) % 9] & 0x66ed'c62a'6bf8'c826ull);
}
