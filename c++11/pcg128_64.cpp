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
#include "utils/uint128.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Empty constructor. */
Pcg128_64::Pcg128_64() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Pcg128_64::Pcg128_64(const int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Pcg128_64::Pcg128_64(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Pcg128_64::Pcg128_64(const long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long). */
Pcg128_64::Pcg128_64(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Pcg128_64::Pcg128_64(const long long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Pcg128_64::Pcg128_64(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned 128-bits). */
Pcg128_64::Pcg128_64(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Pcg128_64::Pcg128_64(const double seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
/** Initializes internal state (empty signature). */
inline void Pcg128_64::seed() noexcept
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
void Pcg128_64::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
void Pcg128_64::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
void Pcg128_64::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
void Pcg128_64::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
void Pcg128_64::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
void Pcg128_64::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
void Pcg128_64::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
void Pcg128_64::seed(const double seed_) noexcept
{
    const double s{ seed_ < 0.0 ? -seed_ : seed_ };
    if (s >= 1.8446744073709552e+19) {
        _setstate(utils::UInt128(0, 1) * s);
    }
    else if (s >= 1.0) {
        seed(std::uint64_t(s));
    }
    else {
        _setstate(utils::UInt128(0xffff'ffff'ffff'ffff, 0xffff'ffff'ffff'ffff) * s);
    }

    /** /
    //---------------------------------------------------------------------------
    UInt128& UInt128::operator*= (const double coeff) noexcept
    {
        const long double low{ coeff * lo };
        const long double high{ (coeff * hi) * 1.8446744073709551616e+19l };

        this->hi = std::uint64_t((high + low) / 1.8446744073709551616e+19l);
        this->lo = std::uint64_t(low);

        return *this;
    }
    /**/
}

//---------------------------------------------------------------------------
/** Sets the internal state with an integer seed. */
void Pcg128_64::_setstate(const std::uint64_t seed) noexcept
{
    _internal_state.state = utils::UInt128(seed, ~seed);
}

//---------------------------------------------------------------------------
/** Sets the internal state with an UInt128 seed. */
void Pcg128_64::_setstate(const utils::UInt128& seed) noexcept
{
    _internal_state.state = seed;
}


//===========================================================================
/** The private constants used for the engine algorithm. */
const utils::UInt128 Pcg128_64::_a(0x2360'ed05'1fc6'5da4ull, 0x4385'df64'9fcc'f645ull);
const utils::UInt128 Pcg128_64::_c(0x5851'f42d'4c95'7f2dull, 0x1405'7b7e'f767'814full);
