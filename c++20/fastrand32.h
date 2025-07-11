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


//===========================================================================
#include <cstdint>

#include "baseclasses/baserandom.h"
#include "utils/seed_generation.h"
#include "utils/splitmix.h"
#include "utils/uint128.h"


//===========================================================================
/** @brief Fast Linear Congruential Generator - 32 bits.
*
*   Pseudo-random numbers generator - Linear Congruential Generator dedicated
*   to  32-bits  calculations with very short period (about 4.3e+09) but very
*   short time computation.
*
*   LCG models evaluate pseudo-random numbers suites x(i) as a simple mathem-
*   atical function of
*
*       x(i) = (a * x(i-1) + c) mod m
*
*   Results  are  nevertheless  considered  to  be  poor  as  stated  in  the
*   evaluation done by Pierre L'Ecuyer and Richard Simard (Universite de
*   Montreal) in 'TestU01: A C Library for Empirical Testing of Random Number
*   Generators  -  ACM  Transactions  on Mathematical Software,  vol.33  n.4,
*   pp.22-40,  August 2007'.  It is not recommended to use such pseudo-random
*   numbers generators for serious simulation applications.
*
*   The implementation of this LCG 32-bits model is based  on  (a=69069, c=1)
*   since  these  two  values  have  evaluated to be the 'best' ones for LCGs
*   within TestU01 while m = 2^32.
*
*   See FastRand63 for a 2^63 (i.e. about 9.2e+18) period  LC-Generator  with
*   low  computation  time  also,  longer  period and quite better randomness
*   characteristics than for FastRand32.
*
*   Furthermore this class is callable:
* @code
*     FastRand32 rand{};
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(a) << std::endl;   // prints a uniform pseudo-random value within [0.0, a)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     FastRand32 diceRoll();
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the LCGs that have
*   been implemented in CppRandLib, as provided in paper "TestU01, ..."  - see
*   file README.md.
* +------------------------------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | TU01 generator name                | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ---------------------------------- | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | FastRand32       | LCG(2^32, 69069, 1)                |     1 x 4-bytes | 2^32    |    3.20     |     0.67     |         11       |     106     |   *too many*   |
* | FastRand63       | LCG(2^63, 9219741426499971445, 1)  |     2 x 4-bytes | 2^63    |    4.20     |     0.75     |          0       |       5     |       7        |
* +------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*
*   * _small crush_ is a small set of simple tests that quickly tests some  of
*   the expected characteristics for a pretty good PRNG;
*
*   * _crush_ is a bigger set of tests that test more deeply  expected  random
*   characteristics
*
*   * _big crush_ is the ultimate set of difficult tests  that  any  GOOD  PRNG
*   should definitively pass.
*/
class FastRand32 : public BaseRandom<std::uint32_t, std::uint32_t, 32>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<std::uint32_t, std::uint32_t, 32>;

    //---   Constructors / Destructor   -------------------------------------
    inline FastRand32() noexcept;                                   //!< Empty constructor.
                                                                    
    inline FastRand32(const int                seed_) noexcept;     //!< Valued constructor (int).
    inline FastRand32(const unsigned int       seed_) noexcept;     //!< Valued constructor (unsigned int).
    inline FastRand32(const long               seed_) noexcept;     //!< Valued constructor (long)
    inline FastRand32(const unsigned long      seed_) noexcept;     //!< Valued constructor (unsigned long).
    inline FastRand32(const long long          seed_) noexcept;     //!< Valued constructor (long long).
    inline FastRand32(const unsigned long long seed_) noexcept;     //!< Valued constructor (unsigned long long).
    inline FastRand32(const utils::UInt128&    seed_) noexcept;     //!< Valued constructor (unsigned 128-bits).
    inline FastRand32(const double             seed_);              //!< Valued constructor (double).
                                                                    
    virtual inline ~FastRand32() noexcept = default;                //!< default destructor.


    //---   Operations   ----------------------------------------------------
    virtual inline const output_type next() noexcept override;      //!< The internal PRNG algorithm.

    virtual inline void seed() noexcept override;                   //!< Initializes internal state (empty signature).

    inline void seed(const int                seed_) noexcept;      //!< Initializes internal state (int).
    inline void seed(const unsigned int       seed_) noexcept;      //!< Initializes internal state (unsigned int).
    inline void seed(const long               seed_) noexcept;      //!< Initializes internal state (long)
    inline void seed(const unsigned long      seed_) noexcept;      //!< Initializes internal state (unsigned long).
    inline void seed(const long long          seed_) noexcept;      //!< Initializes internal state (long long).
    inline void seed(const unsigned long long seed_) noexcept;      //!< Initializes internal state (unsigned long long).
    inline void seed(const utils::UInt128&    seed_) noexcept;      //!< Initializes internal state (unsigned 128-bits).
    inline void seed(const double             seed_);               //!< Initializes internal state (double).

    virtual inline void _setstate(const std::uint64_t   seed_) noexcept override;   //!< Sets the internal state with a 64-bits integer seed.
    virtual inline void _setstate(const utils::UInt128& seed_) noexcept override;   //!< Sets the internal state with a 128-bits integer seed.

};


//===========================================================================
//---   IMPLEMENTATION   ----------------------------------------------------
//---------------------------------------------------------------------------
/** Empty constructor. */
inline FastRand32::FastRand32() noexcept
    : MyBaseClass()
{
    seed();
}

/** Valued constructor (int). */
inline FastRand32::FastRand32(const int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (unsigned int). */
inline FastRand32::FastRand32(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (long). */
inline FastRand32::FastRand32(const long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (unsigned long). */
inline FastRand32::FastRand32(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (long long). */
inline FastRand32::FastRand32(const long long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (unsigned long long). */
inline FastRand32::FastRand32(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (unsigned 128-bits). */
inline FastRand32::FastRand32(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

/** Valued constructor (double). */
inline FastRand32::FastRand32(const double seed_)
    : MyBaseClass()
{
    seed(seed_);
}

/** The internal PRNG algorithm. */
inline const FastRand32::output_type FastRand32::next() noexcept
{
    return _internal_state.state = 69'069 * _internal_state.state + 1;
}

/** Initializes internal state (empty signature). */
inline void FastRand32::seed() noexcept
{
    MyBaseClass::seed();
}

/** Initializes internal state (int). */
inline void FastRand32::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned int). */
inline void FastRand32::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (long). */
inline void FastRand32::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned long). */
inline void FastRand32::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (long long). */
inline void FastRand32::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

/** Initializes internal state (unsigned long long). */
inline void FastRand32::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

/** Initializes internal state (unsigned 128-bits). */
inline void FastRand32::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

/** Initializes internal state (double). */
inline void FastRand32::seed(const double seed_)
{
    MyBaseClass::seed(seed_);
}

/** Sets the internal state with an integer seed. */
inline void FastRand32::_setstate(const std::uint64_t seed_) noexcept
{
    utils::SplitMix32 init_rand(seed_);
    _internal_state.state = init_rand();
}

/** Sets the internal state with a 128-bits integer seed. */
inline void FastRand32::_setstate(const utils::UInt128& seed_) noexcept
{
    _setstate(seed_.lo);
}
