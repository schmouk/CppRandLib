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

#include "well512a.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Well512a::output_type Well512a::next() noexcept
{
    const std::uint32_t i{ _internal_state.state.index };
    const std::uint32_t i_1{ (i - 1) & 0xf };

    const value_type z0{ _internal_state.state.list[i_1] };
    // notice:  all blocks of bits in the internal state are 32 bits wide, which leads to a great
    // simplification for the implementation of the generic WELL algorithm when evaluating z0.
    const value_type z1{ _M3_neg(_internal_state.state.list[i], 16) ^ _M3_neg(_internal_state.state.list[(i + 13) & 0x0f], 15) };
    const value_type z2{ _M3_pos(_internal_state.state.list[(i + 9) & 0xf], 11) };
    // notice: the last term of the above equation in the WELL generic algorithm is, for its Well512a
    // version, the zero matrix _M0 which we suppress here for calculations optimization purpose
    const value_type z3{ z1 ^ z2 };

    _internal_state.state.list[i] = z3;
    _internal_state.state.list[i_1] = _M3_neg(z0, 2) ^ _M3_neg(z1, 18) ^ _M2_neg(z2, 28) ^ _M5_neg(z3, 5, _a1);
    _internal_state.state.index = i_1;

    return z3;
}
