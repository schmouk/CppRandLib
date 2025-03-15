#pragma once
/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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

#include "baserandom.h"
#include "listseedstate.h"
#include "utils/seed_generation.h"
#include "utils/splitmix.h"


//===========================================================================
/** @brief The base support for 32-bits MRG Pseudo Random Number Generators.
*
*   This module is part of library CppRandLib.
*/
export template<const std::uint32_t SIZE>
class BaseMRG32 : public BaseRandom<ListSeedState<std::uint32_t, SIZE>, std::uint32_t, 32>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<ListSeedState<uint32_t, SIZE>, std::uint32_t, 32>;

    using output_type = MyBaseClass::output_type;
    using state_type = MyBaseClass::state_type;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline BaseMRG32() noexcept
        : MyBaseClass()
    {}

    /** @brief Default Destructor. */
    virtual ~BaseMRG32() noexcept = default;


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state of this PRNG from shuffled current time (empty signature). */
    inline virtual void setstate() noexcept override
    {
        setstate(utils::set_random_seed32());
    }

    /** @brief Sets the internal state of this PRNG with an integer seed. */
    void setstate(const uint32_t seed) noexcept
    {
        utils::SplitMix32 splitmix_32(seed);
        std::ranges::generate(MyBaseClass::_state.seed.list, [&]() { return splitmix_32(); });
    }

    /** @brief Sets the internal state of this PRNG with a double seed. */
    inline void setstate(const double seed) noexcept
    {
        const double s = (seed <= 0.0) ? 0.0 : (seed >= 1.0) ? 1.0 : seed;
        setstate(std::uint64_t(s * double(_MODULO)));
    }

    /** @brief Restores the internal state of this PRNG from seed. */
    inline void setstate(const state_type& seed) noexcept
    {
        MyBaseClass::_state.seed = seed;
        MyBaseClass::_state.gauss_valid = false;
    }

    /** @brief Restores the internal state of this PRNG from seed and gauss_next. */
    inline  void setstate(const state_type& seed, const double gauss_next) noexcept
    {
        MyBaseClass::_state.seed = seed;
        MyBaseClass::_state.gauss_next = gauss_next;
        MyBaseClass::_state.gauss_valid = true;
    }

private:
    static constexpr state_type _MODULO{ 0xffff'fffful };

};
