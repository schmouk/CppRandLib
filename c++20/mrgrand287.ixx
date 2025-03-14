/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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
module;

#include <chrono>


export module mrgrand287;

import basemrg32;
import fastrand32;
import listseedstate;


//===========================================================================
/** @brief A fast 32-bits Multiple Recursive Generator with a long period (2.49e+86).
*
*   This module is part of library CppRandLib.
*
*   Multiple Recursive Generators (MRGs)  use  recurrence  to  evaluate  pseudo-random
*   numbers suites. Recurrence is of the form:
*
*      x(i) = A * SUM[ x(i-k) ]  mod M
*
*   for 2 to more k different values.
*
*   MRGs offer very large periods with the best known results  in  the  evaluation  of
*   their  randomness,  as  stated  in  the  evaluation  done  by  Pierre L'Ecuyer and
*   Richard Simard (Universite de Montreal)  in "TestU01:  A C Library  for  Empirical
*   Testing of Random  Number Generators  - ACM Transactions on Mathematical Software,
*   vol.33 n.4, pp.22-40, August 2007".  It is recommended to use  such  pseudo-random
*   numbers generators rather than LCG ones for serious simulation applications.
*
*   The implementation of this MRG 32-bits  model  is  based  on  a  Lagged  Fibonacci
*   generator (LFIB), the Marsa-LFIB4 one.
*   Lagged Fibonacci generators LFib( m, r, k, op) use the recurrence
*
*       x(i) = (x(i-r) op (x(i-k)) mod m
*
*   where op is an operation that can be
*       + (addition),
*       - (substraction),
*       * (multiplication),
*       ^(bitwise exclusive-or).
*
*   With the + or - operation, such generators are in fact MRGs. They offer very large
*   periods  with  the  best  known  results in the evaluation of their randomness, as
*   stated in the evaluation done by Pierre L'Ecuyer and Richard Simard (Universite de
*   Montreal) paper.
*
*   The Marsa-LIBF4 version uses the recurrence
*
*       x(i) = (x(i-55) + x(i-119) + x(i-179) + x(i-256)) mod 2^32
*
*   and offers a period of about 2^287 - i.e. 2.49e+86 - with low computation time due
*   to the use of a 2^32 modulo.
*
*   See MRGRand1457 for a  longer  period  MR-Generator  (2^1457,  i.e. 4.0e+438)  and
*   longer  computation  time  (2^31-1  modulus  calculations)  but  less memory space
*   consumption (47 integers).
*   See MRGRand49507 for a far longer period  (2^49_507,  i.e. 1.2e+14_903)  with  low
*   computation  time  too  (31-bits  modulus)  but  use  of  more memory space (1_597
*   integers).
*
*   Furthermore this class is callable:
* @code
*     MRGRand287 rand();
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
*     std::cout << rand(a,b) << std::endl; // prints a uniform pseudo-random value within [a  , b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     MRGRand287 diceRoll();
*     std::cout << int(diceRoll(1, 7)) << std::endl;    // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the LCGs that have
*   been implemented in PyRandLib, as provided in paper "TestU01, ..."  -  see
*   file README.md.
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRabndLib class | TU01 generator name | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------- | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | MRGRand287       | Marsa-LFIB4         |   256 x 4-bytes | 2^287   |    3.40     |     0.8      |          0       |       0     |       0        |
* | MRGRand1457      | DX-47-3             |    47 x 4-bytes | 2^1457  |    n.a.     |     1.4      |          0       |       0     |       0        |
* | MRGRand49507     | DX-1597-2-7         | 1,597 x 4-bytes | 2^49507 |    n.a.     |     1.4      |          0       |       0     |       0        |
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
*
*   * _small crush_ is a small set of simple tests that quickly tests some  of
*   the expected characteristics for a pretty good PRG;
*
*   * _crush_ is a bigger set of tests that test more deeply  expected  random
*   characteristics;
*
*   * _big crush_ is the ultimate set of difficult tests  that  any  GOOD  PRG
*   should definitively pass.
*/
export class MRGRand287 : public BaseMRG32<256>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseMRG32<256>;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline MRGRand287() noexcept
        : MyBaseClass()
    {
        MyBaseClass::setstate();
    }

    /** @brief Valued construtor (integer). */
    inline MRGRand287(const uint32_t seed) noexcept
        : MyBaseClass()
    {
        MyBaseClass::setstate(seed);
    }

    /** @brief Valued construtor (double). */
    inline MRGRand287(const double seed) noexcept
        : MyBaseClass()
    {
        MyBaseClass::setstate(seed);
    }

    /** @brief Valued constructor (full state). */
    inline MRGRand287(const StateType& seed) noexcept
        : MyBaseClass()
    {
        setstate(seed);
    }

    /** @brief Default Copy constructor. */
    MRGRand287(const MRGRand287&) noexcept = default;

    /** @brief Default Move constructor. */
    MRGRand287(MRGRand287&&) noexcept = default;

    /** @brief Default Destructor. */
    virtual ~MRGRand287() noexcept = default;


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * @return an integer value coded on BITS bits.
    */
    virtual const output_type next() noexcept override;
};
