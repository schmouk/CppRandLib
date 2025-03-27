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

#include "well44497b.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Well44497b::output_type Well44497b::next() noexcept
{
    const std::uint32_t i = _internal_state.state.index;
    std::uint32_t i_1, i_2;

    switch (i) {  // just to avoid modulo 624 calculations
    case 0:
        i_1 = 1390;
        i_2 = 1389;
        break;

    case 1:
        i_1 = 0;
        i_2 = 1390;
        break;

    default:
        i_1 = i - 1;
        i_2 = i - 2;
        break;
    }

    const value_type z0{ (_internal_state.state.list[i_1] & 0x0001'fffful) ^ _internal_state.state.list[i_2] & 0xfffe'0000ul };
    const value_type z1{ _M3_neg(_internal_state.state.list[i], 24) ^ _M3_pos(_internal_state.state.list[(i + 23) % STATE_SIZE], 30) };
    const value_type z2{ _M3_neg(_internal_state.state.list[(i + 481) % STATE_SIZE], 10) ^ _M2_neg(_internal_state.state.list[(i + 229) % STATE_SIZE], 26) };
    const value_type z3{ z1 ^ z2 };

    _internal_state.state.list[i] = z3;
    _internal_state.state.list[i_1] = z0 ^ _M3_pos(z1, 20) ^ _M6(z2, 9, 14, 5, _a7) ^ z3;
    // notice: the first and the last terms of the above equation in the WELL generic algorithm is, for its Well44497b
    //       version, the Identity matrix '_M1' which we do not call here for calculations optimization purpose
    _internal_state.state.index = i_1;

    return _tempering(z3, 0x93dd'1400ul, 0xfa11'8000ul);

}
