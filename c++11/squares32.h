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
 * @addtogroup Squares-algorithms
 *
 *  @{
 */


//===========================================================================
#include <cstdint>

#include "baseclasses/basesquares.h"


//===========================================================================
/** @brief Squares pseudo-random Generators dedicated to 64-bits calculations and 32-bits output values with small period (min 2^64, i.e. 1.84e+19).
*
*   This Squares models is based on a  four  rounds  of  squaring  and
*   exchanging of upper and lower bits of the successive combinations.
*   Output values are provided on 32-bits.
*
*   See Squares64 for a 2^64 (i.e. about 1.84e+19)  period  PRNG  with
*   low  computation  time,  medium period,  64-bits output values and
*   very good randomness characteristics. Caution: the 64-bits version
*   should  not  pass the birthday test,  which is a randomness issue,
*   while this is not mentionned in the original paper - see reference
*   [9] in file README.md.
*
*   Furthermore this class is callable:
* @code
*     Squares32 rand{};
*     std::cout << rand() << std::endl;     // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;    // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     Squares32 diceRoll{};
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the WELL  algorithms  that
*   have  been implemented in CppRandLib, as provided in paper "TestU01, ..." and when
*   available.
*
* +--------------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | [9] generator name | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------ | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Squares32        | squares32          |  4 x 4-bytes    |   2^64  |    n.a.     |     n.a.     |          0       |       0     |       0        |
* | Squares64        | squares64          |  4 x 4-bytes    |   2^64  |    n.a.     |     n.a.     |          0       |       0     |       0        |
* +--------------------------------------------------------------------------------------------------------------------------------------------------+
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
class Squares32 : public BaseSquares<std::uint32_t>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseSquares<std::uint32_t>;


    //---   Constructors / Destructor   -------------------------------------
    Squares32() noexcept;                                    //!< Default empty constructor.

    Squares32(const int                seed) noexcept;       //!< Valued constructor (int).
    Squares32(const unsigned int       seed) noexcept;       //!< Valued constructor (unsigned int).
    Squares32(const long               seed) noexcept;       //!< Valued constructor (long)
    Squares32(const unsigned long      seed) noexcept;       //!< Valued constructor (unsigned long).
    Squares32(const long long          seed) noexcept;       //!< Valued constructor (long long).
    Squares32(const unsigned long long seed) noexcept;       //!< Valued constructor (unsigned long long).
    Squares32(const utils::UInt128&    seed) noexcept;       //!< Valued constructor (unsigned 128-bits).
    Squares32(const double             seed);                //!< Valued constructor (double).

    Squares32(const state_type& internal_state) noexcept;    //!< Valued constructor (full state).

    virtual inline ~Squares32() noexcept = default;          //!< default destructor.


    //---   Operations   ----------------------------------------------------
    virtual const output_type next() noexcept override;      //!< The internal PRNG algorithm. @return an integer value coded on 32 bits.

};

/** @}*/
