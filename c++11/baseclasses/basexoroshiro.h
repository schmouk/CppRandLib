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
/** @brief The base class for all Scrambled Linear Pseudorandom Number Generators based on 64-bits numbers.
*
*   Definition of the base class for  all  Scrambled  Linear  pseudorandom  generators
*   based on 64-bits generated numbers.
*
*   The xoroshiro algorithm is a version of the Scrambled Linear  Pseudorandom  Number
*   Generators.  The xoroshiro linear transformation updates cyclically two words of a
*   larger state array. The base xoroshiro linear transformation is obtained combining
*   a rotation, a shift, and again a rotation.
*   (extracted from the original paper, see [10] in file README.md)
*
*   An addition or a multiplication operation is internally applied also to the  state
*   of  the  PRNGs.  Doubling the same operation has proven to enhance then randomness
*   quality of the PRNG.  This is the model of the algorithms that  is  implemeted  in
*   PyRandLib.
*
*   The implemented algorithms shortly escape from the zeroland (10 to 100  calls  are
*   enough  to  get  equiprobability  of bits 0 and 1 on 4 successive calls).  The 256
*   version of the algorithm has nevertheless shown close repeats flaws,  with  a  bad
*   Hamming weight near zero. Xoroshiro512 seems to best fit this property.
*   (see https://www.pcg-random.org/posts/xoshiro-repeat-flaws.html).
*
*   See Xoroshiro256, Xoroshiro512, Xoroshiro1024 for long  period  generators  (resp.
*   2^256,  2^512  and  2^1024 periods,  i.e. resp. 1.16e+77,  1.34e+154 and 1.80e+308
*   periods),  64-bits precision calculations and short memory consumption  (resp.  4,
*   8 and 16 integers coded on 64 bits.
*
*   Please notice that this class and all its  inheriting  sub-classes  are  callable.
*   Example:
* @code
*     BaseXoroshiro rand{}; // CAUTION: Replace 'BaseXoroshiro' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     BaseXoroshiro diceRoll{}; // CAUTION: Replace 'BaseXoroshiro' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Inheriting classes have to define class attribute '_STATE_SIZE'. See Xoroshiro1024
*   for an example.
*
*   Reminder:
*   We give you here below a copy of the table of tests for the xoroshiros  that  have
*   been  implemented  in PyRandLib,  as  described  by the authors of xoroshiro - see
*   reference [10] in file README.md.
*
* +-------------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRandLib class | initial xoroshiro algo name | Memory Usage | Period | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | --------------- | --------------------------- | ------------ | ------ | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Xoroshiro256    | xoroshiro256**              |  8 x 4-bytes | 2^256  |    n.a.     |     0.84     |          0       |       0     |       0        |
* | Xoroshiro512    | xoroshiro512**              | 16 x 4-bytes | 2^512  |    n.a.     |     0.99     |          0       |       0     |       0        |
* | Xoroshiro1024   | xoroshiro1024**             | 32 x 4-bytes | 2^1024 |    n.a.     |     1.17     |          0       |       0     |       0        |
* +-------------------------------------------------------------------------------------------------------------------------------------------------------+
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
template<const std::uint32_t SIZE>
class BaseXoroshiro : public BaseRandom<ListSeedState<utils::SplitMix64, std::uint64_t, SIZE>, std::uint64_t, 64>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<ListSeedState<utils::SplitMix64, std::uint64_t, SIZE>, std::uint64_t, 64>;
    using output_type = MyBaseClass::output_type;
    using state_type  = MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;


    //---   Constructors / Destructor   -------------------------------------
    inline BaseXoroshiro() noexcept;                                    //!< Default empty constructor.

    inline BaseXoroshiro(const int                seed) noexcept;       //!< Valued constructor (int).
    inline BaseXoroshiro(const unsigned int       seed) noexcept;       //!< Valued constructor (unsigned int).
    inline BaseXoroshiro(const long               seed) noexcept;       //!< Valued constructor (long)
    inline BaseXoroshiro(const unsigned long      seed) noexcept;       //!< Valued constructor (unsigned long).
    inline BaseXoroshiro(const long long          seed) noexcept;       //!< Valued constructor (long long).
    inline BaseXoroshiro(const unsigned long long seed) noexcept;       //!< Valued constructor (unsigned long long).
    inline BaseXoroshiro(const utils::UInt128&    seed) noexcept;       //!< Valued constructor (unsigned 128-bits).
    inline BaseXoroshiro(const double             seed);                //!< Valued constructor (double).

    inline BaseXoroshiro(const state_type& internal_state) noexcept;    //!< Valued constructor (full state).

    virtual inline ~BaseXoroshiro() noexcept = default;                 //!< default destructor.


    //---   Operations   ----------------------------------------------------
    void inline seed() noexcept;                                        //!< Initializes internal state (empty signature).

    void inline seed(const int                seed_) noexcept;          //!< Initializes internal state (int).
    void inline seed(const unsigned int       seed_) noexcept;          //!< Initializes internal state (unsigned int).
    void inline seed(const long               seed_) noexcept;          //!< Initializes internal state (long)
    void inline seed(const unsigned long      seed_) noexcept;          //!< Initializes internal state (unsigned long).
    void inline seed(const long long          seed_) noexcept;          //!< Initializes internal state (long long).
    void inline seed(const unsigned long long seed_) noexcept;          //!< Initializes internal state (unsigned long long).
    void inline seed(const utils::UInt128&    seed_) noexcept;          //!< Initializes internal state (unsigned 128-bits).
    void inline seed(const double             seed_);                   //!< Initializes internal state (double).

    virtual inline void _setstate(const std::uint64_t   seed) noexcept override;    //!< Sets the internal state of this PRNG with a 64-bits integer seed.
    virtual inline void _setstate(const utils::UInt128& seed) noexcept override;    //!< Sets the internal state of this PRNG with a 128-bits integer seed.

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Empty constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro() noexcept
    : MyBaseClass()
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_.lo));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<const std::uint32_t SIZE>
inline BaseXoroshiro<SIZE>::BaseXoroshiro(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG from current time (empty signature). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed() noexcept
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const unsigned int seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const unsigned long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const long long seed_) noexcept
{
    seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::seed(const double seed_)
{
    MyBaseClass::seed(seed_);
}


//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 64-bits integer seed. */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::_setstate(const std::uint64_t seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 128-bits integer seed. */
template<const std::uint32_t SIZE>
inline void BaseXoroshiro<SIZE>::_setstate(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_.lo);
}
