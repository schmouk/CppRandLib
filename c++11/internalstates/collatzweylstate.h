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
#include <cstdint>

#include "../utils/splitmix.h"
#include "../utils/uint128.h"


//===========================================================================
/** @brief The internal state of counter-based Pseudo Random Numbers Generators. */
template<typename ValueType, typename StateValueType>
struct CollatzWeylState
{
    using value_type       = ValueType;
    using state_value_type = StateValueType;

    value_type       a{ value_type(0) };
    value_type       s{ value_type(1) };  // notice: _s must be odd
    state_value_type state{ state_value_type(0) };
    value_type       weyl{ value_type(0) };


    inline CollatzWeylState() noexcept = default;                                           //!< Default empty constructor.

    inline CollatzWeylState(const CollatzWeylState& other) noexcept = default;              //!< Copy constructor.
    inline CollatzWeylState(CollatzWeylState&& other) noexcept = default;                   //!< Move constructor.

    inline virtual ~CollatzWeylState() noexcept = default;                                  //!< Default destructor.


    inline CollatzWeylState& operator= (const CollatzWeylState& other) noexcept = default;  //!< Assignment copy operator.
    inline CollatzWeylState& operator= (CollatzWeylState&& other) noexcept = default;       //!< Assignment move operator.
    

    inline bool const operator== (const CollatzWeylState& other) const noexcept;                  //!< equality operator.


    /** @brief Initalizes the internal state according to a 64-bits integer seed. */
    void seed(const std::uint64_t seed_) noexcept;


    /** @brief Initalizes the internal state according to a 128-bits integer seed. */
    void seed(const utils::UInt128& seed_) noexcept;

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** equality operator. */
template<typename ValueType, typename StateValueType>
inline const bool CollatzWeylState<ValueType, StateValueType>::operator== (const CollatzWeylState& other) const noexcept
{
    return a == other.a && s == other.s && state == other.state && weyl == other.weyl;
}

//---------------------------------------------------------------------------
/** Initalizes the internal state according to a 64-bits integer seed. */
template<typename ValueType, typename StateValueType>
inline void CollatzWeylState<ValueType, StateValueType>::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    a = weyl = ValueType(0);
    s = ValueType(splitmix_64()) | 1;  // Notice : s must be odd
    state = StateValueType(splitmix_64());
}

template<>
inline void CollatzWeylState<std::uint64_t, std::uint64_t>::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    a = weyl = 0;
    s = splitmix_64() | 1;  // Notice : s must be odd
    state = splitmix_64();
}

template<>
inline void CollatzWeylState<std::uint64_t, utils::UInt128>::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    a = weyl = 0;
    s = splitmix_64() | 1;  // Notice : s must be odd

    state.hi = splitmix_64();  // Notice: in the original paper, the internal state seems to be erroneously initialized on its sole 64 lowest bits
    state.lo = splitmix_64();
}

template<>
inline void CollatzWeylState<utils::UInt128, utils::UInt128>::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    a = weyl = utils::UInt128(0);

    s.hi = splitmix_64();
    s.lo = splitmix_64() | 1;  // Notice : s must be odd

    state.hi = splitmix_64();  // Notice: in the original paper, the internal state seems to be erroneously initialized on the sole 64 lowest bits
    state.lo = splitmix_64();
}


//---------------------------------------------------------------------------
/** Initalizes the internal state according to a 128-bits integer seed. */
template<typename ValueType, typename StateValueType>
inline void CollatzWeylState<ValueType, StateValueType>::seed(const utils::UInt128& seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_.lo);

    a = weyl = ValueType(0);
    s = ValueType(splitmix_64()) | 1;  // Notice : s must be odd
    state = StateValueType(splitmix_64());
}

template<>
inline void CollatzWeylState<std::uint64_t, std::uint64_t>::seed(const utils::UInt128& seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_.lo);

    a = weyl = 0;
    s = splitmix_64() | 1;  // Notice : s must be odd
    state = splitmix_64();  // Notice: state is coded on 64-bits here
}

template<>
inline void CollatzWeylState<std::uint64_t, utils::UInt128>::seed(const utils::UInt128& seed_) noexcept
{
    utils::SplitMix64 splitmix_hi(seed_.hi);
    utils::SplitMix64 splitmix_lo(seed_.lo);

    a = weyl = 0;
    s = splitmix_lo() | 1;  // Notice : s must be odd

    state.hi = splitmix_hi();  // Notice: in the original paper, the internal state seems to be erroneously initialized on the sole 64 lowest bits
    state.lo = splitmix_lo();
}

template<>
inline void CollatzWeylState<utils::UInt128, utils::UInt128>::seed(const utils::UInt128& seed_) noexcept
{
    utils::SplitMix64 splitmix_hi(seed_.hi);
    utils::SplitMix64 splitmix_lo(seed_.lo);

    a = weyl = utils::UInt128(0);

    s.hi = splitmix_hi();
    s.lo = splitmix_lo() | 1;  // Notice : s must be odd

    state.hi = splitmix_hi();  // Notice: in the original paper, the internal state seems to be erroneously initialized on the sole 64 lowest bits
    state.lo = splitmix_lo();
}
