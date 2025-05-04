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
*     std::cout << int(diceRoll(1, 7)) << std::endl;    // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the CWGs that have
*   been  implemented  in  PyRandLib,  as  presented in paper [8]  -  see file 
    README.md.
*
* +-----------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRandLib class | [8] generator name | Memory Usage | Period   | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | --------------- | ------------------ | ------------ | -------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Cwg64           | CWG64              |  8 x 4-bytes | >= 2^70  |    n.a.     |     n.a.     |         0        |      0      |       0        |
* | Cwg128_64       | CWG128_64          | 10 x 4-bytes | >= 2^71  |    n.a.     |     n.a.     |         0        |      0      |       0        |
* | Cwg128          | CWG128             | 16 x 4-bytes | >= 2^135 |    n.a.     |     n.a.     |         0        |      0      |       0        |
* +-----------------------------------------------------------------------------------------------------------------------------------------------+
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
    using state_type = typename MyBaseClass::state_type;
    using value_type = typename state_type::value_type;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline BaseCWG() noexcept;

    /** @brief Valued constructor (seed). */
    inline BaseCWG(const int seed_) noexcept;
    inline BaseCWG(const unsigned int seed_) noexcept;
    inline BaseCWG(const long seed_) noexcept;
    inline BaseCWG(const unsigned long seed_) noexcept;
    inline BaseCWG(const long long seed_) noexcept;
    inline BaseCWG(const unsigned long long seed_) noexcept;
    inline BaseCWG(const double seed_) noexcept;

    /** @brief Valued constructor (full state). */
    inline BaseCWG(const state_type& internal_state) noexcept;

    /** @brief Default Destructor. */
    virtual ~BaseCWG() noexcept = default;


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state of this PRNG with a 64-bits integer seed. */
    virtual inline void _setstate(const std::uint64_t seed_) noexcept override;

    /** @brief Sets the internal state of this PRNG with a 128-bits integer seed. */
    inline void _setstate(const utils::UInt128& seed_) noexcept;

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
/** Valued construtor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const int seed_) noexcept
: MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued construtor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued construtor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

/** Valued construtor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

/** Valued construtor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

/** Valued construtor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

/** Valued construtor. */
template<typename ValueType, typename StateValueType, typename OutputType, const std::uint32_t OUTPUT_BITS>
inline BaseCWG<ValueType, StateValueType, OutputType, OUTPUT_BITS>::BaseCWG(const double seed_) noexcept
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
