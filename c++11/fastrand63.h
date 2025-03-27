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
#include "utils/seed_generation.h"


//===========================================================================
/** @brief Fast Linear Congruential Generator - 63 bits.
*
*   Pseudo-random numbers generator - Linear Congruential Generator dedicated
*   to  63-bits calculations with very short period (about 9.2e+18) and short
*   time computation.
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
*   The implementation of this LCG 63-bits model is based on (a=9219741426499971445, c=1)
*   since  these  two  values  have  evaluated  to be the 'best' ones for LCGs
*   within TestU01 while m = 2^63.
*
*   See FastRand32 for a 2^32 (i.e. 4.3e+9) period LC-Generator with very  low
*   computation  time  but shorter period and worse randomness characteristics
*   than for FastRand63.
*
*   Furthermore this class is callable:
* @code
*     FastRand63 rand{};
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(a) << std::endl;   // prints a uniform pseudo-random value within [0.0, a)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     FastRand63 diceRoll();
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the LCGs that have
*   been implemented in CppRandLib, as provided in paper "TestU01, ..."  - see
*   file README.md.
* +------------------------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRabndLib class | TU01 generator name                | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ---------------------------------- | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | FastRand63       | LCG(2^32, 69069, 1)                |     1 x 4-bytes | 2^32    |    3.20     |     0.67     |         11       |     106     |   *too many*   |
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
class FastRand63 : public BaseRandom<std::uint64_t, std::uint64_t, 63>
{
private:
    static const std::uint64_t _MODULO_63{ 0x7fff'ffff'ffff'ffffull };


public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<std::uint64_t, std::uint64_t, 63>;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Default Empty constructor. */
    inline FastRand63() noexcept
        : MyBaseClass()
    {
        seed();
    }

    /** @brief Valued construtor. */
    template<typename T>
    inline FastRand63(const T seed_)
        : MyBaseClass()
    {
        MyBaseClass::seed(seed_);
    }

    FastRand63(const FastRand63&) noexcept = default;   //!< default copy constructor.
    FastRand63(FastRand63&&) noexcept = default;        //!< default move constructor.
    virtual ~FastRand63() noexcept = default;           //!< default destructor.


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm. */
    virtual inline const output_type next() noexcept override
    {
        return _internal_state.state = (0x7ff3'19fa'a77b'f52dull * _internal_state.state + 1) & _MODULO_63;
    }


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state of this PRNG from current time (empty signature). */
    virtual void seed() noexcept override
    {
        setstate(utils::set_random_seed63());
    }

    /** @brief Sets the internal state with an integer seed. */
    virtual inline void _setstate(const std::uint64_t seed_) noexcept override
    {
        _internal_state.state = seed_ & 0x7fff'ffff'ffff'ffff;
    }

};
