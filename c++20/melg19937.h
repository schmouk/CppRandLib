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
#include "baseclasses/basemelg.h"


//===========================================================================
/** @brief A 64-bits Maximally Equidistributed Long-period Linear Generator with a long period (4.32e+6,001).
*
*   Maximally  Equidistributed  Long-period  Linear  Generators   (MELG)   use   linear
*   recurrence  based  on  state  transitions  with  double feedbacks and linear output
*   transformations with several memory references. See reference [11] in README.md.
*
*   MELGs offer large to very large periods with best known results in  the  evaluation
*   of  their randomness.  They ensure a maximally equidistributed generation of pseudo
*   random numbers.  They pass all TestU01 tests and newer ones but are the slowest  to
*   compute ones in the base of PRNGs that have been implemented in PyRandLib.
*
*   See Melg607 for a large period MELG-Generator (2^607,  i.e. 5.31e+182)  with medium
*   computation   time  and  the  equivalent  of  21  32-bits  integers  memory  little
*   consumption. This is the shortest period version proposed in paper [11].
*
*   See Melg44497 for a very large period (2^44,497,  i.e. 8.55e+13,395)  with  similar
*   computation  time  but  use  of even more memory space (equivalent of 1,393 32-bits
*   integers). This is the longest period version proposed in paper [11].
*
*   Furthermore this class is callable:
* @code
*     Melg19937 rand();
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     Melg19937 diceRoll();
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
* | Melg607          | melg607-64          |    21 x 4-bytes | 2^607   |    n.a.     |      n.a.    |        n.a.      |     n.a.    |     n.a.       |
* | Melg19937        | melg19937-64        |   625 x 4-bytes | 2^19937 |    n.a.     |     4.21     |          0       |       0     |       0        |
* | Melg44497        | melg44497-64        | 1,393 x 4-bytes | 2^44497 |    n.a.     |      n.a.    |        n.a.      |     n.a.    |     n.a.       |
* +---------------------------------------------------------------------------------------------------------------------------------------------------+
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
class Melg19937 : public BaseMELG<312>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseMELG<312>;

    using output_type = MyBaseClass::output_type;
    using state_type  = MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline Melg19937() noexcept
        : MyBaseClass()
    {}

    /** @brief Valued construtor. */
    template<typename T>
    inline Melg19937(const T seed_) noexcept
        : MyBaseClass()
    {
        MyBaseClass::MyBaseClass::seed(seed_);
    }

    /** @brief Valued constructor (full state). */
    inline Melg19937(const state_type& seed_internal_state) noexcept
        : MyBaseClass(seed_internal_state)
    {}

    Melg19937(const Melg19937&) noexcept = default;   //!< default copy constructor.
    Melg19937(Melg19937&&) noexcept = default;        //!< default move constructor.
    virtual ~Melg19937() noexcept = default;        //!< default destructor.


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * @return an integer value coded on OUTPUT_BITS (i.e. 64) bits.
    */
    virtual const output_type next() noexcept override;


private:
    // this definition will avoid an 'if' in method 'next()'
    static constexpr value_type _A_COND[]{ 0ull, 0x5c32'e06d'f730'fc42ull};

};
