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

/**
 * @defgroup CWG-algorithms algos: CWG - Collatz-Weyl Generators
 *
 *  This is the group for all the CppRandLib implementations of the Collatz-Weyl
 *  pseudorandom Generators (CWG) algorithm.
 *
 *  CWG models are chaotic generators that are combined with Weyl sequences to
 *  eliminate  the risk of short cycles.  They have a large period,  a uniform
 *  distribution,  and the ability to generate multiple independent streams by
 *  changing  their  internal  parameters  (Weyl  increment).  CWGs  owe their
 *  exceptional  quality  to  the  arithmetical  dynamics   of  noninvertible,
 *  generalized, Collatz mappings based on the wellknown Collatz conjecture.
 *  There is no jump function, but each  odd  number  of  the  Weyl  increment
 *  initiates  a  new  unique  period,  which  enables quick initialization of
 *  independent streams (this text is extracted from [8], see README.md).
 *
 *  The internal implementation of the CWG algorithm varies according  to  its
 *  implemented  version.  See  implementation  classes  to  get  their formal
 *  description.
 * 
 *  @{
 */

//===========================================================================
#include <cstdint>

#include "baserandom.h"
#include "../internalstates/collatzweylstate.h"
#include "../utils/uint128.h"


//===========================================================================
/** @brief The base class for all Collatz-Weyl pseudorandom Generators (CWG).
*
*   CWG models are chaotic generators that are combined with Weyl sequences to
*   eliminate  the risk of short cycles.  They have a large period,  a uniform
*   distribution,  and the ability to generate multiple independent streams by
*   changing  their  internal  parameters  (Weyl  increment).  CWGs  owe their
*   exceptional  quality  to  the  arithmetical  dynamics   of  noninvertible,
*   generalized, Collatz mappings based on the wellknown Collatz conjecture.
*   There is no jump function, but each  odd  number  of  the  Weyl  increment
*   initiates  a  new  unique  period,  which  enables quick initialization of
*   independent streams (this text is extracted from [8], see README.md).
*
*   The internal implementation of the CWG algorithm varies according  to  its
*   implemented  version.  See  implementation  classes  to  get  their formal
*   description.
*
*   See Cwg64 for a minimum  2^70  (i.e. about 1.18e+21)  period  CW-Generator
*   with low computation time, medium period,  64- bits output values and very
*   good randomness characteristics.
* 
*   See Cwg128_64 for a minimum 2^71 (i.e. about 2.36e+21) period CW-Generator
*   with very low computation time,  medium period,  64-bits output values and
*   very good randomness characteristics.
* 
*   See Cwg128 for a minimum 2^135 (i.e. about 4.36e+40)  period  CW-generator
*   with very low computation time, medium period,  128-bits output values and
*   very good randomness characteristics.
*
*   Furthermore this class is callable:
* @code
*     BaseCWG rand();  // CAUTION: Replace 'BaseCWG' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     BaseCWG diceRoll();  // CAUTION: Replace 'BaseCWG' with any inheriting class constructor!
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the CWGs that have
*   been  implemented  in  CppRandLib,  as  presented  in paper [8] - see file 
    README.md.
*
* +------------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | [8] generator name | Memory Usage | Period   | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------ | ------------ | -------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Cwg64            | CWG64              |  8 x 4-bytes | >= 2^70  |    n.a.     |     n.a.     |         0        |      0      |       0        |
* | Cwg128_64        | CWG128_64          | 10 x 4-bytes | >= 2^71  |    n.a.     |     n.a.     |         0        |      0      |       0        |
* | Cwg128           | CWG128             | 16 x 4-bytes | >= 2^135 |    n.a.     |     n.a.     |         0        |      0      |       0        |
* +------------------------------------------------------------------------------------------------------------------------------------------------+
*
*   * _small crush_ is a small set of simple tests that quickly tests some  of
*   the expected characteristics for a pretty good PRNG;
* 
*   * _crush_ is a bigger set of tests that test more deeply  expected  random
*   characteristics;
* 
*   * _big crush_ is the ultimate set of difficult tests that  any  GOOD  PRNG
*   should definitively pass.
*/

template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS = 8 * sizeof(OutputType)>
class BaseCWG : public BaseRandom<CollatzWeylState<ValueType, StateValueType>, OutputType, OUTPUT_BITS>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<CollatzWeylState<ValueType, StateValueType>, OutputType, OUTPUT_BITS>;

    using output_type = typename MyBaseClass::output_type;
    using state_type  = typename MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;


    //---   Constructors / Destructor   -------------------------------------
    inline BaseCWG() noexcept;                                  //!< Default empty constructor.

    BaseCWG(const int                seed) noexcept;            //!< Valued constructor (int).
    BaseCWG(const unsigned int       seed) noexcept;            //!< Valued constructor (unsigned int).
    BaseCWG(const long               seed) noexcept;            //!< Valued constructor (long)
    BaseCWG(const unsigned long      seed) noexcept;            //!< Valued constructor (unsigned long).
    BaseCWG(const long long          seed) noexcept;            //!< Valued constructor (long long).
    BaseCWG(const unsigned long long seed) noexcept;            //!< Valued constructor (unsigned long long).
    BaseCWG(const utils::UInt128&    seed) noexcept;            //!< Valued constructor (unsigned 128-bits).
    BaseCWG(const double             seed);                     //!< Valued constructor (double).

    BaseCWG(const state_type& internal_state) noexcept;         //!< Valued constructor (full state).

    virtual ~BaseCWG() noexcept = default;                      //!< Default Destructor.


    //---   Operations   ----------------------------------------------------
    void inline seed() noexcept;                                //!< Initializes internal state (empty signature).

    void inline seed(const int                seed_) noexcept;  //!< Initializes internal state (int).
    void inline seed(const unsigned int       seed_) noexcept;  //!< Initializes internal state (unsigned int).
    void inline seed(const long               seed_) noexcept;  //!< Initializes internal state (long)
    void inline seed(const unsigned long      seed_) noexcept;  //!< Initializes internal state (unsigned long).
    void inline seed(const long long          seed_) noexcept;  //!< Initializes internal state (long long).
    void inline seed(const unsigned long long seed_) noexcept;  //!< Initializes internal state (unsigned long long).
    void inline seed(const utils::UInt128&    seed_) noexcept;  //!< Initializes internal state (unsigned 128-bits).
    void inline seed(const double             seed_);           //!< Initializes internal state (double).

    virtual void _setstate(const std::uint64_t   seed_) noexcept override;  //!< Sets the internal state with a 64-bits integer seed.
    virtual void _setstate(const utils::UInt128& seed_) noexcept override;  //!< Sets the internal state with a 128-bits integer seed.

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Empty constructor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG() noexcept
    : MyBaseClass()
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Valued construtor (int). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued construtor (unsigned int). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued construtor (long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued construtor (unsigned long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued construtor (long long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued construtor (unsigned long long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

/** Valued construtor (128-bits integer). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

/** Valued construtor (double). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG from current time (empty signature). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed() noexcept
{
    _setstate(utils::set_random_seed64());
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const int seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const unsigned int seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const unsigned long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const long long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::seed(const double seed_)
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 64-bits integer seed. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::_setstate(const std::uint64_t seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 128-bits integer seed. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline void BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::_setstate(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_);
}

/** @}*/
