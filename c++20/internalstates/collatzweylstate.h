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
#include <type_traits>

#include "../utils/splitmix.h"
#include "../utils/uint128.h"


//===========================================================================
/** @brief The internal state of counter-based Pseudo Random Numbers Generators. */
template<typename ValueType, typename StateValueType>
class CollatzWeylState
{
public:
    using value_type = ValueType;
    using state_value_type = StateValueType;

    /** @brief Initalizes the internal state according to a 64-bits integer seed. */
    void seed(const std::uint64_t seed_) noexcept;

    /** @brief Initalizes the internal state according to a 128-bits integer seed. */
    void seed(const utils::UInt128& seed_) noexcept;

private:
    value_type       _a{ value_type(0) };
    value_type       _s{ value_type(0) };
    state_value_type _state{ state_value_type(0) };
    value_type       _weyl{ value_type(0) };

};



//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Initalizes the internal state according to a 64-bits integer seed. */
template<typename ValueType, typename StateValueType>
void CollatzWeylState<ValueType, StateValueType>::seed(const std::uint64_t seed_) noexcept
{
}

template<>
void CollatzWeylState<std::uint64_t, std::uint64_t>::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    _a = _weyl = 0;
    _s = splitmix_64() | 1; // Notice : _s must be odd
    _state = splitmix_64();
}

template<>
void CollatzWeylState<std::uint64_t, utils::UInt128>::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    _a = _weyl = 0;
    _s = splitmix_64() | 1; // Notice : _s must be odd

    _state.hi = splitmix_64();  // Notice: in the original paper, this seems to be erroneously initialized on sole 64 lowest bits
    _state.lo = splitmix_64();
}

template<>
void CollatzWeylState<utils::UInt128, utils::UInt128>::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    _a = _weyl = utils::UInt128(0);

    _s.hi = splitmix_64();
    _s.lo = splitmix_64() | 1; // Notice : _s must be odd

    _state.hi = splitmix_64();  // Notice: in the original paper, this seems to be erroneously initialized on sole 64 lowest bits
    _state.lo = splitmix_64();
}


//---------------------------------------------------------------------------
/** Initalizes the internal state according to a 128-bits integer seed. */
template<typename ValueType, typename StateValueType>
void CollatzWeylState<ValueType, StateValueType>::seed(const utils::UInt128& seed_) noexcept
{
}

template<>
void CollatzWeylState<std::uint64_t, std::uint64_t>::seed(const utils::UInt128& seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_.lo);

    _a = _weyl = 0;
    _s = splitmix_64() | 1; // Notice : _s must be odd
    _state = splitmix_64();
}

template<>
void CollatzWeylState<std::uint64_t, utils::UInt128>::seed(const utils::UInt128& seed_) noexcept
{
    utils::SplitMix64 splitmix_hi(seed_.hi);
    utils::SplitMix64 splitmix_lo(seed_.lo);

    _a = _weyl = 0;
    _s = splitmix_lo() | 1; // Notice : _s must be odd

    _state.hi = splitmix_hi();  // Notice: in the original paper, this seems to be erroneously initialized on sole 64 lowest bits
    _state.lo = splitmix_lo();
}

template<>
void CollatzWeylState<utils::UInt128, utils::UInt128>::seed(const utils::UInt128& seed_) noexcept
{
    utils::SplitMix64 splitmix_hi(seed_.hi);
    utils::SplitMix64 splitmix_lo(seed_.lo);

    _a = _weyl = utils::UInt128(0);

    _s.hi = splitmix_hi();
    _s.lo = splitmix_lo() | 1; // Notice : _s must be odd

    _state.hi = splitmix_hi();  // Notice: in the original paper, this seems to be erroneously initialized on sole 64 lowest bits
    _state.lo = splitmix_lo();
}
