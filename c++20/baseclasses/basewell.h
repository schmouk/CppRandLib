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
/** @brief The base class for all WELL pseudo-random generators.
*
*   Well-Equidistributed Long-period Linear Generators (WELL)  use  linear  recurrence
*   based  on  primitive  characteristic  polynomials associated with left- and right-
*   shifts and xor operations to fastly evaluate pseudo-random numbers suites.
*
*   WELLs offer large to very large periods with best known results in the  evaluation
*   of their randomness,  as stated in the evaluation  done  by  Pierre  L'Ecuyer  and
*   Richard Simard (Universite de Montreal) in  "TestU01:  A C Library  for  Empirical
*   Testing of Random  Number Generators  - ACM Transactions on Mathematical Software,
*   vol.33 n.4, pp.22-40, August 2007".  It is recommended to use  such  pseudo-random
*   numbers generators rather than LCG ones for serious simulation applications.
*   Furthermore, WELLs have proven their great ability  to  very  fastly  escape  from
*   zeroland.
*
*   Notice: the algorithm in the 4 different versions implemented here has been  coded
*   here  as  a  direct  implementation  of  their  descriptions  in the initial paper
*   "Improved Long-Period Generators Based on Linear Recurrences  Modulo 2",  François
*   PANNETON  and  Pierre  L’ECUYER  (Université  de  Montréal)  and  Makoto MATSUMOTO
*   (Hiroshima University),  in ACM Transactions on  Mathematical  Software,  Vol. 32,
*   No. 1, March 2006, Pages 1–16.
*   (see https://www.iro.umontreal.ca/~lecuyer/myftp/papers/wellrng.pdf).
*   So,  only minimalist optimization has been coded,  with  the  aim  at  easing  the
*   verification of its proper implementation.
*
*   See Well512a for a large period WELL-Generator (2^512,  i.e. 1.34e+154)  with  low
*   computation time and 16 integers memory little consumption.
*   See Well1024a for a longer period WELL-Generator (2^1,024,  i.e. 1.80e+308),  same
*   computation time and 32 integers memory consumption.
*   See Well199937c for a far longer period  (2^19,937, i.e. 4.32e+6,001) with similar
*   computation time but use of more memory space (624 integers).
*   See Well44497b for a very large period (2^44,497,  i.e. 15.1e+13,466) with similar
*   computation time but use of even more memory space (1,391 integers).
*
*   Please notice that this class and all its  inheriting  sub-classes  are  callable.
*   Example:
* @code
*     BaseWell rand{};                      // CAUTION: Replace 'BaseWell' with any inheriting class constructor!
*     std::cout << rand() << std::endl;     // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;    // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     BaseWell diceRoll{};                  // CAUTION: Replace 'BaseWell' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the WELL  algorithms  that
*   have  been implemented in CppRandLib, as provided in paper "TestU01, ..." and when
*   available.
*
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | TU01 generator name | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------- | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Well512a         | not available       |    16 x 4-bytes | 2^512   |    n.a.     |     n.a.     |        n.a.      |     n.a.    |     n.a.       |
* | Well1024         | WELL1024a           |    32 x 4-bytes | 2^1024  |    4.0      |     1.1      |          0       |       4     |       4        |
* | Well19937b (1)   | WELL19937a          |   624 x 4-bytes | 2^19937 |    4.3      |     1.3      |          0       |       2     |       2        |
* | Well44497c       | not available       | 1,391 x 4-bytes | 2^44497 |    n.a.     |     n.a.     |        n.a.      |     n.a.    |     n.a.       |
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
*
*   (1) The Well19937b generator  provided  with  library  CppRandLib  implement s the
*   Well19937a algorithm augmented with an associated tempering algorithm.
*
*   * _small crush_ is a small set of simple tests that  quickly  tests  some  of  the
*   expected characteristics for a pretty good PRNG;
*
*   * _crush_ is a  bigger  set  of  tests  that  test  more  deeply  expected  random
*   characteristics;
*
*   * _big crush_ is the ultimate set of difficult tests that  any  GOOD  PRNG  should
*   definitively pass.
*/
template<const std::uint32_t SIZE>
class BaseWell : public BaseRandom<ListSeedState<utils::SplitMix32, std::uint32_t, SIZE>, std::uint32_t, 32>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<ListSeedState<utils::SplitMix32, std::uint32_t, SIZE>, std::uint32_t, 32>;
    using output_type = MyBaseClass::output_type;
    using state_type = MyBaseClass::state_type;
    using value_type = typename state_type::value_type;

    static constexpr std::uint32_t STATE_SIZE{ SIZE };


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Default Empty constructor. */
    inline BaseWell() noexcept;

    /** @brief Valued construtor. */
    inline BaseWell(const int seed_) noexcept;
    inline BaseWell(const unsigned int seed_) noexcept;
    inline BaseWell(const long seed_) noexcept;
    inline BaseWell(const unsigned long seed_) noexcept;
    inline BaseWell(const long long seed_) noexcept;
    inline BaseWell(const unsigned long long seed_) noexcept;
    inline BaseWell(const double seed_);

    /** @brief Valued constructor (full state). */
    inline BaseWell(const state_type& internal_state) noexcept;

    /** @brief Default destructor. */
    virtual ~BaseWell() noexcept = default;

    /** @brief Sets the internal state of this PRNG with an integer seed. */
    virtual inline void _setstate(const std::uint64_t seed) noexcept override;


protected:
    // declaration of transformation matrices
    static inline value_type _M0(const value_type x = 0) noexcept;
    static inline value_type _M1(const value_type x) noexcept;
    static inline value_type _M2_pos(const value_type x, const value_type t) noexcept;
    static inline value_type _M2_neg(const value_type x, const value_type t) noexcept;
    static inline value_type _M3_pos(const value_type x, const value_type t) noexcept;
    static inline value_type _M3_neg(const value_type x, const value_type t) noexcept;
    static inline value_type _M4(const value_type x, const value_type a) noexcept;
    static inline value_type _M5_pos(const value_type x, const value_type t, const value_type a) noexcept;
    static inline value_type _M5_neg(const value_type x, const value_type t, const value_type a) noexcept;
    static inline value_type _M6(const value_type x, const value_type q, const value_type t, const value_type s, const value_type a) noexcept;

    static inline value_type _d(const value_type s) noexcept;
    static inline value_type _tempering(const value_type x, const value_type b, const value_type c) noexcept;

    // declaration of algorithm constants
    static constexpr value_type _a1{ 0xda44'2d24ul };
    static constexpr value_type _a2{ 0xd3e4'3ffdul };
    static constexpr value_type _a3{ 0x8bdc'b91eul };
    static constexpr value_type _a4{ 0x86a9'd87eul };
    static constexpr value_type _a5{ 0xa8c2'96d1ul };
    static constexpr value_type _a6{ 0x5d6b'45ccul };
    static constexpr value_type _a7{ 0xb729'fcecul };

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Default Empty constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell() noexcept
    : MyBaseClass()
{
    MyBaseClass::seed();
}

//-------------------------------------------
/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

/** Valued constructor. */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<const std::uint32_t SIZE>
inline BaseWell<SIZE>::BaseWell(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with an integer seed. */
template<const std::uint32_t SIZE>
inline void BaseWell<SIZE>::_setstate(const std::uint64_t seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_);
}


//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M0(
    const value_type x
) noexcept
{
    return 0;
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M1(
    const value_type x
) noexcept
{
    return x;
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M2_pos(
    const value_type x,
    const value_type t
) noexcept
{
    return x >> t;
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M2_neg(
    const value_type x,
    const value_type t
) noexcept
{
    return x << t;
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M3_pos(
    const value_type x,
    const value_type t
) noexcept
{
    return x ^ (x >> t);
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M3_neg(
    const value_type x,
    const value_type t
) noexcept
{
    return x ^ (x << t);
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M4(
    const value_type x,
    const value_type a
) noexcept
{
    return (x & 0x8000'0000ul) ? (x >> 1) ^ a : x >> 1;
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M5_pos(
    const value_type x,
    const value_type t,
    const value_type a
) noexcept
{
    return x ^ ((x >> t) & a);
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M5_neg(
    const value_type x,
    const value_type t,
    const value_type a
) noexcept
{
    return x ^ ((x << t) & a);
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_M6(
    const value_type x,
    const value_type q,
    const value_type t,
    const value_type s,
    const value_type a
) noexcept
{
    value_type y{ (((x << q) & 0xffff'fffful) ^ (x >> (32 - q))) & BaseWell<SIZE>::_d(s) };
    return (x & (1 << t)) ? (y ^ a) : y;
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_d(
    const value_type s
) noexcept
{
    return 0xffff'fffful ^ (1 << s);
}

//---------------------------------------------------------------------------
template<const std::uint32_t SIZE>
inline typename BaseWell<SIZE>::value_type BaseWell<SIZE>::_tempering(
    const value_type x,
    const value_type b,
    const value_type c
) noexcept
{
    // notice:  the generic algorithm truncs x on w-bits. All of the implemented
    // ones in CppRandLib are set on 32-bits. So, no truncation takes place here
    value_type x_{ x ^ (((x << 7) & 0xffff'fffful) & b) };
    return x_ ^ (((x_ << 15) & 0xffff'fffful) & c);
}
