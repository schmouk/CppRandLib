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

#include "well19937c.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Empty constructor. */
Well19937c::Well19937c() noexcept
    : MyBaseClass()
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Well19937c::Well19937c(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Well19937c::Well19937c(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Well19937c::Well19937c(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor(unsigned long). */
Well19937c::Well19937c(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Well19937c::Well19937c(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Well19937c::Well19937c(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned 128-bits). */
Well19937c::Well19937c(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Well19937c::Well19937c(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
Well19937c::Well19937c(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
const Well19937c::output_type Well19937c::next() noexcept
{
    const std::uint32_t i = _internal_state.state.index;
    std::uint32_t i_1, i_2;

    switch (i) {  // just to avoid modulo 624 calculations
    case 0:
        i_1 = 623;
        i_2 = 622;
        break;

    case 1:
        i_1 = 0;
        i_2 = 623;
        break;

    default:
        i_1 = i - 1;
        i_2 = i - 2;
        break;
    }

    const value_type z0{ (_internal_state.state.list[i_1] & 0x0000'0001ul) ^ _internal_state.state.list[i_2] & 0xffff'fffeul };
    const value_type z1{ _M3_neg(_internal_state.state.list[i], 25) ^ _M3_pos(_internal_state.state.list[(i + 70) % STATE_SIZE], 27) };
    const value_type z2{ _M2_pos(_internal_state.state.list[(i + 179) % STATE_SIZE], 9) ^ _M3_pos(_internal_state.state.list[(i + 449) % STATE_SIZE], 1) };
    const value_type z3{ z1 ^ z2 };

    _internal_state.state.list[i] = z3;
    _internal_state.state.list[i_1] = z0 ^ _M3_neg(z1, 9) ^ _M2_neg(z2, 21) ^ _M3_pos(z3, 21);
        // notice: the first term of the above equation in the WELL generic algorithm is, for its Well19937c
    //       version, the Identity matrix '_M1' which we do not call here for calculations optimization purpose
    _internal_state.state.index = i_1;

    return _tempering(z3, 0xe46e'1700ul, 0x9b86'8000ul);

}
