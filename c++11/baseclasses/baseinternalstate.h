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
#include <vector>

#include "../utils/splitmix.h"


//===========================================================================
/** @brief The base class for all internal states of PRNGs that contain vectors of integers. */
class BaseInternalState
{
protected:
    /** @brief Initializes the internal state container items. */
    template<typename ItemT, const std::uint32_t STATE_ITEM_BITS_COUNT>
    inline void _init_state(std::vector<ItemT>& state_content, const std::uint64_t seed_) noexcept;

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Initializes the internal state container items - General case, 64-bits items. */
template<typename ItemT, const std::uint32_t STATE_ITEM_BITS_COUNT>
inline void BaseInternalState::_init_state(std::vector<ItemT>& state_content, const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);
    for (ItemT& s : state_content)
        s = ItemT(splitmix_64());
}

/** Specialization for 64-bits items. */
template<>
inline void BaseInternalState::_init_state<std::uint64_t, 64>(std::vector<std::uint64_t>& state_content, const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);
    for (std::uint64_t& s : state_content)
        s = splitmix_64();
}

/** Specialization for 32-bits items. */
template<>
inline void BaseInternalState::_init_state<std::uint32_t, 32>(std::vector<std::uint32_t>& state_content, const std::uint64_t seed_) noexcept
{
    utils::SplitMix32 splitmix_32(seed_);
    for (std::uint32_t& s : state_content)
        s = splitmix_32();
}

/** Specialization for 31-bits items. */
template<>
inline void BaseInternalState::_init_state<std::uint32_t, 31>(std::vector<std::uint32_t>& state_content, const std::uint64_t seed_) noexcept
{
    utils::SplitMix31 splitmix_31(seed_);
    for (std::uint32_t& s : state_content)
        s = splitmix_31();
}
