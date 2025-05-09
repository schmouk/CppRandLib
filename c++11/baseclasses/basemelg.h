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

#include "baserandom.h"
#include "../internalstates/listseedstate.h"
#include "../utils/splitmix.h"


//===========================================================================
/** @brief The base class for all Maximally Equidistributed Long-period Linear Generators (MELG).
*
*   Maximally  Equidistributed  Long-period  Linear  Generators  (MELG)   use   linear
*   recurrence  based  on  state  transitions  with double feedbacks and linear output
*   transformations with several memory references. See reference [11] in README.md.
*
*   MELGs offer large to very large periods with best known results in the  evaluation
*   of their randomness.  They ensure a maximally equidistributed generation of pseudo
*   random numbers.  They pass all TestU01 tests and newer ones but are the slowest to
*   compute ones in the base of PRNGs that have been implemented in PyRandLib.
*
*   Notice: while the WELL algorithms use 32-bits integers as their internal state and
*   output pseudo-random 32-bits integers also, the MELG algorithm is full 64-bits.
*
*   See Melg607 for a large period MELG-Generator (2^607, i.e. 5.31e+182)  with medium
*   computation  time  and  the  equivalent  of  21  32-bits  integers  memory  little
*   consumption. This is the shortest period version proposed in paper [11].
* 
*   See Melg19937 for an even larger period MELG-Generator (2^19,937, i.e. 4.32e+6001),
*   same computation time and equivalent of 625 integers memory consumption.
* 
*   See Melg44497 for a very large period (2^44,497,  i.e. 8.55e+13,395)  with  similar
*   computation  time  but  use  of even more memory space (equivalent of 1,393 32-bits
*   integers). This is the longest period version proposed in paper [11].
*
*   Furthermore this class is callable:
* @code
*     BaseMELG rand();  // CAUTION: Replace 'BaseMELG' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     BaseMELG diceRoll();  // CAUTION: Replace 'BaseMELG' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7)) << std::endl;    // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the MELGs that have
*   been implemented in PyRandLib,  as provided in paper "TestU01, ..."  -  see
*   file README.md.
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRabndLib class | TU01 generator name | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------- | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Melg607          | melg607-64          |    21 x 4-bytes | 2^607   |    n.a.     |      n.a.    |        n.a.      |     n.a.    |     n.a.       |
* | Melg19937        | melg19937-64        |   625 x 4-bytes | 2^19937 |    n.a.     |     4.21     |          0       |       0     |       0        |
* | Melg44497        | melg44497-64        | 1,393 x 4-bytes | 2^44497 |    n.a.     |      n.a.    |        n.a.      |     n.a.    |     n.a.       |
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
class BaseMELG : public BaseRandom<ListSeedState<utils::SplitMix64, std::uint64_t, SIZE>, std::uint64_t>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<ListSeedState<utils::SplitMix64, std::uint64_t, SIZE>, std::uint64_t>;

    using output_type = typename MyBaseClass::output_type;
    using state_type  = typename MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;


    //---   Constructors / Destructor   -------------------------------------
    inline BaseMELG() noexcept;                                     //!< Default empty constructor.

    inline BaseMELG(const int                seed) noexcept;        //!< Valued constructor (int).
    inline BaseMELG(const unsigned int       seed) noexcept;        //!< Valued constructor (unsigned int).
    inline BaseMELG(const long               seed) noexcept;        //!< Valued constructor (long)
    inline BaseMELG(const unsigned long      seed) noexcept;        //!< Valued constructor (unsigned long).
    inline BaseMELG(const long long          seed) noexcept;        //!< Valued constructor (long long).
    inline BaseMELG(const unsigned long long seed) noexcept;        //!< Valued constructor (unsigned long long).
    inline BaseMELG(const utils::UInt128&    seed) noexcept;        //!< Valued constructor (unsigned 128-bits).
    inline BaseMELG(const double             seed) noexcept;        //!< Valued constructor (double).

    inline BaseMELG(const state_type& internal_state) noexcept;     //!< Valued constructor (full state).

    virtual inline ~BaseMELG() noexcept = default;                  //!< default destructor.


    //---   Operations   ----------------------------------------------------
    void inline seed() noexcept;                                    //!< Initializes internal state (empty signature).
    void inline seed(const int                seed_) noexcept;      //!< Initializes internal state (int).
    void inline seed(const unsigned int       seed_) noexcept;      //!< Initializes internal state (unsigned int).
    void inline seed(const long               seed_) noexcept;      //!< Initializes internal state (long)
    void inline seed(const unsigned long      seed_) noexcept;      //!< Initializes internal state (unsigned long).
    void inline seed(const long long          seed_) noexcept;      //!< Initializes internal state (long long).
    void inline seed(const unsigned long long seed_) noexcept;      //!< Initializes internal state (unsigned long long).
    void inline seed(const utils::UInt128&    seed_) noexcept;      //!< Initializes internal state (unsigned 128-bits).
    void inline seed(const double             seed_) noexcept;      //!< Initializes internal state (double).

    virtual inline void _setstate(const std::uint64_t   seed) noexcept override;    //!< Sets the internal state of this PRNG with an integer seed.
    virtual inline void _setstate(const utils::UInt128& seed) noexcept override;    //!< Sets the internal state of this PRNG with an integer seed.

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Empty constructor. */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long long). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned long long). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (utils::UInt128). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (double). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const double seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<const std::uint32_t SIZE>
inline BaseMELG<SIZE>::BaseMELG(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG from current time (empty signature). */
template<const std::uint32_t SIZE>
inline void BaseMELG<SIZE>::seed() noexcept
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
template<const std::uint32_t SIZE>
void BaseMELG<SIZE>::seed(const double seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with an integer seed. */
template<const std::uint32_t SIZE>
inline void BaseMELG<SIZE>::_setstate(const std::uint64_t seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 128-bits integer seed. */
template<const std::uint32_t SIZE>
inline void BaseMELG<SIZE>::_setstate(const utils::UInt128& seed) noexcept
{
    MyBaseClass::_setstate(seed);
}
