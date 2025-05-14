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

#include "baserandom.h"
#include "../internalstates/listseedstate.h"
#include "../utils/splitmix.h"


//===========================================================================
/** @brief The base support for 32-bits MRG Pseudo Random Number Generators.
*
*   Multiple Recursive Generators (MRGs)  use  recurrence  to  evaluate  pseudo-random
*   numbers suites. Recurrence is of the form:
*
*      x(i) = A * SUM[ x(i-k) ]  mod M
*
*   for 2 to more k different values.
*
*   MRGs offer very large periods with the best known results  in  the  evaluation  of
*   their  randomness,  as  stated  in  the  evaluation  done  by  Pierre L'Ecuyer and
*   Richard Simard (Universite de Montreal)  in "TestU01:  A C Library  for  Empirical
*   Testing of Random  Number Generators  - ACM Transactions on Mathematical Software,
*   vol.33 n.4, pp.22-40, August 2007".  It is recommended to use  such  pseudo-random
*   numbers generators rather than LCG ones for serious simulation applications.
*
*   See Mrg287 for  a  short  period  MR-Generator  (2^287,  i.e. 2.49e+86)  with  low
*   computation time but 256 integers memory consumption (2^32 modulus calculations).
*   See Mrg1457 for a longer period MR-Generator  (2^1457,  i.e. 4.0e+438)  and longer
*   computation  time  (2^31-1 modulus calculations) but less memory space consumption
*   (i.e. 47 integers).
*   See Mrg49507 for  a  far  longer  period  (2^49_507,  i.e. 1.2e+14_903)  with  low
*   computation  time  too  (31-bits  modulus)  but  use  of  more memory space (1_597
*   integers).
*
*   Furthermore this class is callable:
* @code
*     BaseMRG32 rand();  // CAUTION: Replace 'BaseMRG32' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     BaseMRG32 diceRoll();  // CAUTION: Replace 'BaseMRG32' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7)) << std::endl;    // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the LCGs that have
*   been implemented in PyRandLib, as provided in paper "TestU01, ..."  -  see
*   file README.md.
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRabndLib class | TU01 generator name | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------- | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Mrg287           | Marsa-LFIB4         |   256 x 4-bytes | 2^287   |    3.40     |     0.8      |          0       |       0     |       0        |
* | Mrg1457          | DX-47-3             |    47 x 4-bytes | 2^1457  |    n.a.     |     1.4      |          0       |       0     |       0        |
* | Mrg49507         | DX-1597-2-7         | 1,597 x 4-bytes | 2^49507 |    n.a.     |     1.4      |          0       |       0     |       0        |
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
*
*   * _small crush_ is a small set of simple tests that quickly tests some  of
*   the expected characteristics for a pretty good PRNG;
*
*   * _crush_ is a bigger set of tests that test more deeply  expected  random
*   characteristics;
*
*   * _big crush_ is the ultimate set of difficult tests  that  any  GOOD  PRNG
*   should definitively pass.
*/
template<const std::uint32_t SIZE>
struct BaseMRG32 : public BaseRandom<ListSeedState<utils::SplitMix32, std::uint32_t, SIZE>, std::uint32_t, 32>
{
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<ListSeedState<utils::SplitMix32, std::uint32_t, SIZE>, std::uint32_t, 32>;

    using output_type = MyBaseClass::output_type;
    using state_type  = MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;

    static constexpr std::uint32_t SEED_SIZE{ SIZE };


    //---   Constructors / Destructor   -------------------------------------
    inline BaseMRG32() noexcept;                                    //!< Default empty constructor.

    inline BaseMRG32(const int                seed) noexcept;       //!< Valued constructor (int).
    inline BaseMRG32(const unsigned int       seed) noexcept;       //!< Valued constructor (unsigned int).
    inline BaseMRG32(const long               seed) noexcept;       //!< Valued constructor (long)
    inline BaseMRG32(const unsigned long      seed) noexcept;       //!< Valued constructor (unsigned long).
    inline BaseMRG32(const long long          seed) noexcept;       //!< Valued constructor (long long).
    inline BaseMRG32(const unsigned long long seed) noexcept;       //!< Valued constructor (unsigned long long).
    inline BaseMRG32(const utils::UInt128&    seed) noexcept;       //!< Valued constructor (unsigned 128-bits).
    inline BaseMRG32(const double             seed);                //!< Valued constructor (double).

    inline BaseMRG32(const state_type& internal_state) noexcept;    //!< Valued constructor (full state).

    virtual inline ~BaseMRG32() noexcept = default;                 //!< default destructor.


    //---   Operations   ----------------------------------------------------
    void inline seed() noexcept;                                    //!< Initializes internal state (empty signature).

    void inline seed(const int                seed_) noexcept;      //!< Initializes internal state (int).
    void inline seed(const unsigned int       seed_) noexcept;      //!< Initializes internal state (unsigned int).
    void inline seed(const long               seed_) noexcept;      //!< Initializes internal state (long)
    void inline seed(const unsigned long      seed_) noexcept;      //!< Initializes internal state (unsigned long).
    void inline seed(const long long          seed_) noexcept;      //!< Initializes internal state (long long).
    void inline seed(const unsigned long long seed_) noexcept;      //!< Initializes internal state (unsigned long long).
    void inline seed(const utils::UInt128&    seed_) noexcept;      //!< Initializes internal state (unsigned 128-bits).
    void inline seed(const double             seed_);               //!< Initializes internal state (double).

    virtual inline void _setstate(const std::uint64_t   seed) noexcept override;    //!< Sets the internal state of this PRNG with an integer seed.
    virtual inline void _setstate(const utils::UInt128& seed) noexcept override;    //!< Sets the internal state of this PRNG with an integer seed.

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Empty constructor. */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32() noexcept
    : MyBaseClass()
{
    seed();
}

//-------------------------------------------
/** Valued constructor (int). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//-------------------------------------------
/** Valued constructor (unsigned int). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//-------------------------------------------
/** Valued constructor (long). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//-------------------------------------------
/** Valued constructor (unsigned long). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//-------------------------------------------
/** Valued constructor (long long). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//-------------------------------------------
/** Valued constructo (unsigned long long)r. */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//-------------------------------------------
/** Valued constructor (unsigned 128-bits). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//-------------------------------------------
/** Valued constructor (double). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<const std::uint32_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG from current time (empty signature). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed() noexcept
{
    _setstate(utils::set_random_seed32());
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const int seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const unsigned int seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const unsigned long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const long long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::seed(const double seed_)
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with an integer seed. */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::_setstate(const std::uint64_t seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with an integer seed. */
template<const std::uint32_t SIZE>
inline void BaseMRG32<SIZE>::_setstate(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_.lo);
}
