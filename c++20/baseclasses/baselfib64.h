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
#include "../utils/uint128.h"


//===========================================================================
/** @brief The base class for all LFib PRNG based on 64-bits numbers.
*
*   Definition of the base class for all LFib pseudo-random generators based on 64-bits
*   generated numbers.
*
*   Lagged Fibonacci generators LFib( m, r, k, op) use the recurrence
*
*       x(i) = (x(i-r) op (x(i-k)) mod m
*
*   where op is an operation that can be:
*       + (addition),
*       - (substraction),
*       * (multiplication),
*       ^ (bitwise exclusive-or).
*
*   With the + or - operation, such generators are in fact MRGs.  They offer very large
*   periods  with  the  best  known  results  in the evaluation of their randomness, as
*   stated in the evaluation done by Pierre L'Ecuyer and Richard Simard  (Universite de
*   Montreal)  in  "TestU01:  A  C  Library  for  Empirical Testing  of  Random  Number
*   Generators  - ACM Transactions  on  Mathematical  Software,  vol.33 n.4,  pp.22-40,
*   August  2007".  It  is  recommended  to  use  such pseudo-random numbers generators
*   rather than LCG ones for serious simulation applications.
*
*   See LFib78,  LFib116,  LFib668 and LFib1340 for long period LFib generators  (resp.
*   2^78,  2^116,  2^668  and 2^1340 periods, i.e. resp. 3.0e+23, 8.3e+34, 1.2e+201 and
*   2.4e+403 periods) while same computation time and  far  higher  precision  (64-bits
*   calculations)  than MRGs,  but more memory consumption (resp. 17,  55, 607 and 1279
*   integers).
*
*   Please notice that this class and all its  inheriting  sub-classes  are  callable.
*   Example:
* @code
*     BaseLFib64 rand{}; // CAUTION: rplace 'BaseLFib64' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endoced
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     BaseLFib64 diceRoll(); // CAUTION: replace 'BaseLFib64' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the LCGs that have
*   been implemented in PyRandLib, as provided in paper "TestU01, ..."  -  see
*   file README.md.
* +--------------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRabndLib class | TU01 generator name      | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------------ | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | LFibRand78       | LFib(2^64, 17, 5, +)     |    34 x 4-bytes | 2^78    |    n.a.     |     1.1      |          0       |       0     |       0        |
* | LFibRand116      | LFib(2^64, 55, 24, +)    |   110 x 4-bytes | 2^116   |    n.a.     |     1.0      |          0       |       0     |       0        |
* | LFibRand668      | LFib(2^64, 607, 273, +)  | 1,214 x 4-bytes | 2^668   |    n.a.     |     0.9      |          0       |       0     |       0        |
* | LFibRand1340     | LFib(2^64, 1279, 861, +) | 2,558 x 4-bytes | 2^1340  |    n.a.     |     0.9      |          0       |       0     |       0        |
* +--------------------------------------------------------------------------------------------------------------------------------------------------------+
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
template<const std::uint32_t SIZE, const std::uint32_t K>
class BaseLFib64 : public BaseRandom<ListSeedState<utils::SplitMix64, std::uint64_t, SIZE>, std::uint64_t, 64>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<ListSeedState<utils::SplitMix64, std::uint64_t, SIZE>, std::uint64_t, 64>;
    using output_type = MyBaseClass::output_type;
    using state_type  = MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;

    static const std::uint32_t SEED_SIZE{ SIZE };


    //---   Constructors / Destructor   -------------------------------------
    inline BaseLFib64() noexcept;                                   //!< Default empty constructor.

    inline BaseLFib64(const int                seed) noexcept;      //!< Valued constructor (int).
    inline BaseLFib64(const unsigned int       seed) noexcept;      //!< Valued constructor (unsigned int).
    inline BaseLFib64(const long               seed) noexcept;      //!< Valued constructor (long)
    inline BaseLFib64(const unsigned long      seed) noexcept;      //!< Valued constructor (unsigned long).
    inline BaseLFib64(const long long          seed) noexcept;      //!< Valued constructor (long long).
    inline BaseLFib64(const unsigned long long seed) noexcept;      //!< Valued constructor (unsigned long long).
    inline BaseLFib64(const utils::UInt128&    seed) noexcept;      //!< Valued constructor (unsigned 128-bits).
    inline BaseLFib64(const double             seed);               //!< Valued constructor (double).

    inline BaseLFib64(const state_type& internal_state) noexcept;   //!< Valued constructor (full state).

    virtual inline ~BaseLFib64() noexcept = default;                //!< default destructor.


    //---   Internal PRNG   -------------------------------------------------
    virtual const output_type next() noexcept override;             //!< The internal PRNG algorithm.

    inline void _initIndex(const size_t _index) noexcept;           //!< Inits the internal index pointing to the internal list.

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
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (int). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned int). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor (long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (unsigned long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (long long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const long long seed_) noexcept
    : MyBaseClass()
{
    seed(std::uint64_t(seed_));
}

/** Valued constructor (unsigned long long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

/** Valued constructor (utils::UInt128). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    seed(seed_);
}

/** Valued constructor (double). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const double seed_)
    : MyBaseClass()
{
    seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline BaseLFib64<SIZE, K>::BaseLFib64(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** The internal PRNG algorithm. */
template<const std::uint32_t SIZE, std::uint32_t K >
const typename BaseLFib64<SIZE, K>::output_type BaseLFib64<SIZE, K>::next() noexcept
{
    // evaluates indexes in suite for the i-5 and i-17 -th values
    const std::uint32_t index{ MyBaseClass::_internal_state.state.index };
    const std::uint32_t k{ (index < K) ? (index + SEED_SIZE) - K : index - K };

    // evaluates current value and modifies internal state
    output_type value{
        MyBaseClass::_internal_state.state.list[k] +
        MyBaseClass::_internal_state.state.list[index]
    };
    MyBaseClass::_internal_state.state.list[index] = value;

    // next index
    MyBaseClass::_internal_state.state.index = (index + 1) % SEED_SIZE;

    // finally, returns pseudo random value as a 64-bits integer
    return value;
}

//---------------------------------------------------------------------------
/** Inits the internal index pointing to the internal list. */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::_initIndex(const size_t _index) noexcept
{
    MyBaseClass::_internal_state.state.index = _index % SIZE;
}

//---------------------------------------------------------------------------
/** Initializes internal state (empty signature). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed() noexcept
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::seed(const double seed_)
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with an integer seed. */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::_setstate(const std::uint64_t seed) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 128-bits integer seed. */
template<const std::uint32_t SIZE, std::uint32_t K >
inline void BaseLFib64<SIZE, K>::_setstate(const utils::UInt128& seed) noexcept
{
    MyBaseClass::_setstate(seed);
}
