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

#include "squares32.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Squares32::output_type Squares32::next() noexcept
{
    _internal_state.state.counter++;  // notice: modulo 2^64 increment

    value_type x, y, z;
    x = y = _internal_state.state.counter * _internal_state.state.key;
    z = y + _internal_state.state.key;

    // squaring - round 1
    x = x * x + y;
    x = (x >> 32) | (x << 32);

    // squaring - round 2
    x = x * x + z;
    x = (x >> 32) | (x << 32);

    // squaring - round 3
    x = x * x + y;
    x = (x >> 32) | (x << 32);

    // squaring - round 4
    return output_type((x * x + z) >> 32);
}
