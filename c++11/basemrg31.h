#pragma once
/*
MIT License

Copyright (c) 2022 Philippe Schmouker, ph.schmouker (at) gmail.com

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
#include <chrono>

#include "baserandom.h"
#include "fastrand32.h"
#include "listseedstate.h"


//===========================================================================
/** @brief The base support for 32-bits MRG Pseudo Random Number Generators.
*
*   This module is part of library CppRandLib.
*/
template<const size_t SIZE>
class BaseMRG31 : public BaseRandom<ListSeedState<uint32_t, SIZE>>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using StateType = ListSeedState<uint32_t, SIZE>;
    using MyBaseClass = BaseRandom<ListSeedState<uint32_t, SIZE>>;

    
        //---   Class constants   -----------------------------------------------
    static const uint32_t MODULO    = 0x7fff'ffff;  // i.e. (1 << 31) - 1
    static const size_t   SEED_SIZE = SIZE;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline BaseMRG31() noexcept
        : MyBaseClass()
    {}

    /** @brief Default Destructor. */
    virtual ~BaseMRG31() noexcept = default;


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state of this PRNG from current time (empty signature). */
    virtual void setstate() noexcept override;

    /** @brief Sets the internal state of this PRNG with an integer seed. */
    void setstate(const uint32_t seed) noexcept;

    /** @brief Sets the internal state of this PRNG with a double seed. */
    inline void setstate(const double seed) noexcept
    {
        const double s = (seed <= 0.0) ? 0.0 : (seed >= 1.0) ? 1.0 : seed;
        setstate(uint32_t(s * double(MODULO)));
    }

    /** @brief Restores the internal state of this PRNG from seed. */
    inline void setstate(const StateType& seed) noexcept
    {
        MyBaseClass::_state.seed = seed;
        MyBaseClass::_state.gauss_valid = false;
    }

    /** @brief Restores the internal state of this PRNG from seed and gauss_next. */
    inline  void setstate(const StateType& seed, const double gauss_next) noexcept
    {
        MyBaseClass::_state.seed = seed;
        MyBaseClass::_state.gauss_next = gauss_next;
        MyBaseClass::_state.gauss_valid = true;
    }

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
/** Sets the internal state of this PRNG from current time (empty signature). */
template<const size_t SIZE>
void BaseMRG31<SIZE>::setstate() noexcept
{
    const uint64_t ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    const uint32_t t32 = uint32_t(ticks & 0xffff'ffff);
    setstate((((t32 & 0xff00'0000) >> 24) +
               ((t32 & 0x00ff'0000) >> 8) +
               ((t32 & 0x0000'ff00) << 8) +
               ((t32 & 0x0000'00ff) << 24)) % MODULO);
}


/** Sets the internal state of this PRNG with an integer seed. */
template<const size_t SIZE>
void BaseMRG31<SIZE>::setstate(const uint32_t seed) noexcept
{
    FastRand32 rand(seed);
    //for (auto it = MyBaseClass::_state.seed.list.begin(); it != MyBaseClass::_state.seed.list.end(); )
    for (auto it = MyBaseClass::_state.seed.list.begin(); it != MyBaseClass::_state.seed.list.end(); )
        *it++ = uint32_t(rand(MODULO));
}
