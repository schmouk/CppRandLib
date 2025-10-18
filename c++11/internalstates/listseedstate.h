#pragma once
/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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


//===========================================================================
/** @brief The internal state of many Pseudo Random Numbers Generators. */
template<typename RandomT, typename ItemT, const std::uint32_t SIZE>
struct ListSeedState
{
    static_assert(!std::is_signed<ItemT>::value);

    using value_type = ItemT;

    std::vector<ItemT> list{};
    std::uint32_t      index{ 0UL };


    inline ListSeedState() noexcept  //!< Empty constructor.
    {
        list.resize(SIZE);
    }


    /** @brief Increments the internal index pointing to the internal list. */
    inline void inc_index() noexcept
    {
        index = (index + 1) % SIZE;
    }


    /** @brief Initializes the internal index pointing to the internal list. */
    inline void init_index(const std::uint32_t new_index) noexcept
    {
        index = new_index % SIZE;
    }


    /** @brief Initializes the internal state container items.
    *
    * Initializes the container associated with the internal state of PRNGs.
    * template argument ItemT must be an integral type.
    * Notice:  MELG algorithm states that at least one of its internal state
    * items must be non zero. Since we now use an internal implementation of
    * `SplitMix` that never uses its internal state when its value is 0, not
    * more  than  one  item  in the list of internal state items of any PRNG
    * will be zero.
    */
    inline void seed(const std::uint64_t seed_) noexcept
    {
        index = 0UL;
        RandomT init_rand(seed_);
        for (ItemT& item : list)
            item = ItemT(init_rand());
    }


    /** @brief Returns true if both states are the same. */
    inline const bool operator== (const ListSeedState& other) const noexcept
    {
        return index == other.index && list == other.list;
    }


    /** @brief Returns true if states differ. */
    inline const bool operator!= (const ListSeedState& other) const noexcept
    {
        return !(*this == other);
    }

};

/** @}*/