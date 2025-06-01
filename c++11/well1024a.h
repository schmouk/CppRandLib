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

#include "baseclasses/basewell.h"
#include "utils/uint128.h"


//===========================================================================
/** @brief A fast 32-bits Well-Equidistributed Long-period Linear generator with a large period (2^1,024, i.e. 1.80e+308).
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
*   Notice: the algorithm in its Well1024a version has been coded  here  as  a  direct
*   implementation  of  its  description  in the initial paper:  "Improved Long-Period
*   Generators Based on Linear Recurrences Modulo 2",  François  PANNETON  and  Pierre
*   L'ECUYER (Université de Montréal) and Makoto MATSUMOTO (Hiroshima University),  in
*   ACM Transactions on Mathematical Software, Vol. 32, No. 1, March 2006, Pages 1-16.
*   (see https://www.iro.umontreal.ca/~lecuyer/myftp/papers/wellrng.pdf).
*   As such,  only minimalist optimization has been coded,  with the aim at easing the
*   verification of its proper implementation.
*
*   See Well512a for a large period WELL-Generator (2^512,  i.e. 1.34e+154)  with  low
*   computation time and 16 integers memory consumption.
*   See Well199937c for a far longer period  (2^19,937, i.e. 4.32e+6,001) with similar
*   computation time but use of more memory space (624 integers).
*   See Well44497b for a very large period (2^44,497,  i.e. 15.1e+13,466) with similar
*   computation time but use of even more memory space (1,391 integers).
*
*   Furthermore this class is callable:
* @code
*     Well1024a rand();
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     Well1024a diceRoll();
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the WELL  algorithms  that
*   have been implemented in CppRandLib,  as provided in paper "TestU01, ..." and when
*   available.
*
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | TU01 generator name | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------- | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Well512a         | not available       |    16 x 4-bytes | 2^512   |    n.a.     |     n.a.     |        n.a.      |     n.a.    |     n.a.       |
* | Well1024a        | WELL1024a           |    32 x 4-bytes | 2^1024  |    4.0      |     1.1      |          0       |       4     |       4        |
* | Well19937c (1)   | WELL19937a          |   624 x 4-bytes | 2^19937 |    4.3      |     1.3      |          0       |       2     |       2        |
* | Well44497b       | not available       | 1,391 x 4-bytes | 2^44497 |    n.a.     |     n.a.     |        n.a.      |     n.a.    |     n.a.       |
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
*
*   (1) The Well19937c generator provided with library  CppRandLib  implements
*   the Well19937a algorithm augmented with an associated tempering algorithm.
*   This should very slightly slow down its CPU  performance  while  enhancing
*   its pseudo-randomness quality, as measured by TestU01.
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
class Well1024a : public BaseWell<32>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseWell<32>;


    //---   Constructors / Destructor   -------------------------------------
    Well1024a() noexcept;                                   //!< Default empty constructor.

    Well1024a(const int                seed) noexcept;      //!< Valued constructor (int).
    Well1024a(const unsigned int       seed) noexcept;      //!< Valued constructor (unsigned int).
    Well1024a(const long               seed) noexcept;      //!< Valued constructor (long)
    Well1024a(const unsigned long      seed) noexcept;      //!< Valued constructor (unsigned long).
    Well1024a(const long long          seed) noexcept;      //!< Valued constructor (long long).
    Well1024a(const unsigned long long seed) noexcept;      //!< Valued constructor (unsigned long long).
    Well1024a(const utils::UInt128&    seed) noexcept;      //!< Valued constructor (unsigned 128-bits).
    Well1024a(const double             seed);               //!< Valued constructor (double).

    Well1024a(const state_type& internal_state) noexcept;   //!< Valued constructor (full state).

    virtual inline ~Well1024a() noexcept = default;         //!< default destructor.


    //---   Operations   ----------------------------------------------------
    virtual const output_type next() noexcept override;     //!< The internal PRNG algorithm. @return an integer value coded on 32 bits.

};
