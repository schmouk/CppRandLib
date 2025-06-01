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

#include "baseclasses/basecwg.h"
#include "utils/uint128.h"


//===========================================================================
/** @brief A 128-/64- bits Collatz-Weyl pseudorandom Generator with a short period (1.18e+21).
*
*   Pseudo-random numbers  generator  -  Collatz-Weyl  pseudorandom  Generator
*   dedicated  to  128-bits  calculations and 64-bits output values with small
*   period (min 2^71, i.e. 2.36e+21)  but  short  computation  time.  All  CWG
*   algorithms offer multi streams features, by simply using different initial
*   settings for control value 's' - see below.
*
*   This CWG model evaluates pseudo-random numbers suites  x(i)  as  a  simple
*   mathematical function of
*
*       x(i+1) = (x(i) | 1) * ((a += x(i)) >> 1) ^ (weyl += s)
*
*   and returns as the output value the xored shifted: a >> 48 ^ x(i+1)
*
*   where a, weyl and s are the control values and x the internal state of the
*   PRNG.  's' must be initally odd.  'a', 'weyl' and initial state 'x' may be
*   initialized each with any 64-bits value.
*
*   See Cwg64 for a minimum  2^70  (i.e. about 1.18e+21)  period  CW-Generator
*   with very low computation time, medium period,  64- bits output values and
*   very good randomness characteristics.
*
*   See Cwg128_64 for a minimum 2^135 (i.e. about 4.36e+40)  period  CW-generator
*   with very low computation time, medium period,  128-bits output values and
*   very good randomness characteristics.
*
*   Furthermore this class is callable:
* @code
*     Cwg128_64 rand();
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     Cwg128_64 diceRoll();
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the CWGs that have
*   been  implemented  in  CppRandLib,  as  presented  in paper [8] - see file
*   README.md.
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
class Cwg128_64 : public BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseCWG<std::uint64_t, utils::UInt128, std::uint64_t, 64>;

    using output_type = typename MyBaseClass::output_type;
    using state_type  = typename MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;


    //---   Constructors / Destructor   -------------------------------------
    inline Cwg128_64() noexcept = default;                  //!< Default empty constructor.

    Cwg128_64(const int                seed) noexcept;      //!< Valued constructor (int).
    Cwg128_64(const unsigned int       seed) noexcept;      //!< Valued constructor (unsigned int).
    Cwg128_64(const long               seed) noexcept;      //!< Valued constructor (long)
    Cwg128_64(const unsigned long      seed) noexcept;      //!< Valued constructor (unsigned long).
    Cwg128_64(const long long          seed) noexcept;      //!< Valued constructor (long long).
    Cwg128_64(const unsigned long long seed) noexcept;      //!< Valued constructor (unsigned long long).
    Cwg128_64(const utils::UInt128&    seed) noexcept;      //!< Valued constructor (unsigned 128-bits).
    Cwg128_64(const double             seed);               //!< Valued constructor (double).

    Cwg128_64(const state_type& internal_state) noexcept;   //!< Valued constructor (full state).

    virtual ~Cwg128_64() noexcept = default;                //!< Default Destructor.


    //---   Internal PRNG   -------------------------------------------------
    virtual const output_type next() noexcept override;     // The internal PRNG algorithm.


    //---   Operations   ----------------------------------------------------
    void seed() noexcept;                                   //!< Initializes internal state (empty signature).

    void seed(const int                seed_) noexcept;     //!< Initializes internal state (int).
    void seed(const unsigned int       seed_) noexcept;     //!< Initializes internal state (unsigned int).
    void seed(const long               seed_) noexcept;     //!< Initializes internal state (long)
    void seed(const unsigned long      seed_) noexcept;     //!< Initializes internal state (unsigned long).
    void seed(const long long          seed_) noexcept;     //!< Initializes internal state (long long).
    void seed(const unsigned long long seed_) noexcept;     //!< Initializes internal state (unsigned long long).
    void seed(const utils::UInt128&    seed_) noexcept;     //!< Initializes internal state (unsigned 128-bits).
    void seed(const double             seed_);              //!< Initializes internal state (double).

    virtual void _setstate(const std::uint64_t   seed_) noexcept override;  //!< Sets the internal state with a 64-bits integer seed.
    virtual void _setstate(const utils::UInt128& seed_) noexcept override;  //!< Sets the internal state with a 128-bits integer seed.

};
