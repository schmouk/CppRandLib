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

#include "pcg1024_32.h"


//===========================================================================
//---------------------------------------------------------------------------
/** Empty constructor. */
Pcg1024_32::Pcg1024_32() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
Pcg1024_32::Pcg1024_32(const int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
Pcg1024_32::Pcg1024_32(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
Pcg1024_32::Pcg1024_32(const long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long). */
Pcg1024_32::Pcg1024_32(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
Pcg1024_32::Pcg1024_32(const long long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
Pcg1024_32::Pcg1024_32(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned 128-bits). */
Pcg1024_32::Pcg1024_32(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
Pcg1024_32::Pcg1024_32(const double seed_)
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
const Pcg1024_32::output_type Pcg1024_32::next() noexcept
{
    // evaluates a to-be-xor'ed 32-bits value from current extended state
    const value_type current_state{ _internal_state.state.state.state() };  // (sic!)
    if ((current_state & 0xffff'ffff) == 0)
        _advance_table();

    const std::uint64_t index{ current_state >> 22 };
    const extended_value_type extended_value{ _internal_state.state.extended_state[index & _INDEX_MODULO] };

    // then xor's it with the next 32-bits value evaluated with the internal state
    return _internal_state.state.state.next() ^ extended_value;
}

//---------------------------------------------------------------------------
/** Initializes internal state (empty signature). */
inline void Pcg1024_32::seed() noexcept
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
void Pcg1024_32::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
void Pcg1024_32::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
void Pcg1024_32::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
void Pcg1024_32::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
void Pcg1024_32::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
void Pcg1024_32::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
void Pcg1024_32::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_.lo);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
void Pcg1024_32::seed(const double seed_)
{
    if (0.0 <= seed_ && seed_ <= 1.0)
        MyBaseClass::seed(std::uint64_t(0xffff'ffff'ffff'ffffULL * seed_ + seed_));
    else
        throw FloatValueRange01Exception(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state with an integer seed. */
void Pcg1024_32::_setstate(const std::uint64_t seed_) noexcept
{
    _internal_state.state.seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state with an UInt128 seed. */
void Pcg1024_32::_setstate(const utils::UInt128& seed_) noexcept
{
    _internal_state.state.seed(seed_.lo);
}


//---------------------------------------------------------------------------
/** Advances the extended states. */
void Pcg1024_32::_advance_table() noexcept
{
    bool carry{ false };
    unsigned int i{ 0 };
    for (auto& e : _internal_state.state.extended_state) {
        if (carry)
            carry = _external_step(e, i);
        if (_external_step(e, i))
            carry = true;
        i++;
    }
}

//---------------------------------------------------------------------------
/** @brief Evaluates new extended state indexed value in the extended state table. */
const bool Pcg1024_32::_external_step(extended_value_type value, unsigned int i) noexcept
{
    extended_value_type state{ 0xacb8'6d69ul * (value ^ (value >> 22)) };
    state = _invxrs(state, 32, 4 + (state >> 28));
    state = 0x2c92'77b5ul * state + 2 * (i + 1);

    state ^= state >> 16;
    _internal_state.state.extended_state[i] = state;

    return state == (state & 0b11);
}

//---------------------------------------------------------------------------
/** Evaluates the inversion of an xor-shift operation. */
const Pcg1024_32::extended_value_type Pcg1024_32::_invxrs(
    const extended_value_type value,
    const unsigned int bits_count,
    const unsigned int shift
)
{
    if (shift * 2 >= bits_count)
        return value ^ (value >> shift);

    const unsigned int new_bits_shift{ bits_count - shift };
    const extended_value_type bot_mask{ (1ul << (bits_count - shift * 2)) - 1ul };
    const extended_value_type top_mask{ ~bot_mask & 0xffff'fffful };
    const extended_value_type top{ (value ^ (value >> shift)) };
    const extended_value_type bot{ _invxrs((top | (value & bot_mask)) & ((1ull << new_bits_shift) - 1), new_bits_shift, shift) };

    return (top & top_mask) | (bot & bot_mask);
}
