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

/** \addtogroup internalstates
 *
 *  @{
 */


//===========================================================================
#include <type_traits>
#include <vector>

#include "../utils/splitmix.h"


//===========================================================================
/** @brief The internal extended state of some Pseudo Random Numbers Generators. */
template<typename StateType, typename ExtendedValueType, const size_t EXTENDED_SIZE>
struct ExtendedState
{
    static_assert(std::is_integral<ExtendedValueType>::value);

    using value_type = typename StateType::value_type;
    using extended_value_type = ExtendedValueType;

    std::vector<extended_value_type> extended_state{};
    StateType                        state{};

    inline ExtendedState() noexcept;    //!< Empty constructor

    inline void seed(const std::uint64_t seed_) noexcept;   //!< state and external state initialization

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
template<typename StateType, typename ExtendedValueType, const size_t EXTENDED_SIZE>
inline ExtendedState<StateType, ExtendedValueType, EXTENDED_SIZE>::ExtendedState() noexcept
    : state{}
{
    extended_state.resize(EXTENDED_SIZE);
}

//---------------------------------------------------------------------------
template<typename StateType, typename ExtendedValueType, const size_t EXTENDED_SIZE>
inline void ExtendedState<StateType, ExtendedValueType, EXTENDED_SIZE>::seed(const std::uint64_t seed_) noexcept
{
    state = StateType(seed_);
    
    utils::SplitMix32 splitmix_32(seed_);
    for (auto& e : extended_state)
        e = splitmix_32();
}

/** @} */