#pragma once
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
#include <cstdint>

#include "basemrg31.h"
#include "listseedstate.h"


//===========================================================================
/** @brief A fast 31-bits Multiple Recursive Generator with a somewhat long period (3.98e+438)
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
*   The implementation of this MRG 31-bits model is  based  on  DX-47-3  pseudo-random
*   generator  proposed  by  Deng  and  Lin.  The  DX-47-3 version uses the recurrence
*
*       x(i) = (-2^25-2^7) * (x(i-7) + x(i-1597)) mod (2^31-1)
*
*   and offers a period of about 2^1457  - i.e. nearly 4.0e+438 - with low computation
*   time.
*
*   See Mrg287 for  a  short  period  MR-Generator  (2^287,  i.e. 2.49e+86)  with  low
*   computation time but 256 integers memory consumption.
*   See Mrg49507 for  a  far  longer  period  (2^49_507,  i.e. 1.2e+14_903)  with  low
*   computation  time  too  (31-bits  modulus)  but  use  of  more memory space (1_597
*   integers).
*
*   Furthermore this class is callable:
* @code
*     Mrg49507 rand();
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     Mrg49507 diceRoll();
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
* | Mrg287           | Marsa-LFIB4         |   256 x 4-bytes | 2^287   |    3.40     |     0.8      |          0       |       0     |       0        |
* | Mrg1457          | DX-47-3             |    47 x 4-bytes | 2^1457  |    n.a.     |     1.4      |          0       |       0     |       0        |
* | Mrg49507         | DX-1597-2-7         | 1,597 x 4-bytes | 2^49507 |    n.a.     |     1.4      |          0       |       0     |       0        |
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
class Mrg49507 : public BaseMRG31<1597>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseMRG31<1597>;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline Mrg49507() noexcept
        : MyBaseClass()
    {
        setstate();
    }

    /** @brief Valued construtor (integer). */
    inline Mrg49507(const uint32_t seed) noexcept
        : MyBaseClass()
    {
        setstate(seed);
    }

    /** @brief Valued construtor (double). */
    inline Mrg49507(const double seed) noexcept
        : MyBaseClass()
    {
        setstate(seed);
    }

    /** @brief Valued constructor (full state). */
    inline Mrg49507(const state_type& seed) noexcept
        : MyBaseClass()
    {
        setstate(seed);
    }

    Mrg49507(const Mrg49507&) noexcept = default;   //!< defaul copy constructor.
    Mrg49507(Mrg49507&&) noexcept = default;        //!< default move constructor.
    virtual ~Mrg49507() noexcept = default;         //!< default destructor.


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * @return an integer value coded on OUTPUT_BITS bits.
    */
    virtual const output_type next() noexcept override;

};
