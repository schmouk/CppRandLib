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
*   Maximally  Equidistributed  Long-period  Linear  Generators  (MELG)   use   linear
*   recurrence  based  on  state  transitions  with double feedbacks and linear output
*   transformations with several memory references. See reference [11] in README.md.
*
*   MELGs offer large to very large periods with best known results in the  evaluation
*   of their randomness.  They ensure a maximally equidistributed generation of pseudo
*   random numbers.  They pass all TestU01 tests and newer ones but are the slowest to
*   compute ones in the base of PRNGs that have been implemented in PyRandLib.
*
*   See Melg607 for a large period MELG-Generator (2^607, i.e. 5.31e+182)  with medium
*   computation  time  and  the  equivalent  of  21  32-bits  integers  memory  little
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
    Melg19937() noexcept;                                   //!< Default empty constructor.

    Melg19937(const int                seed) noexcept;      //!< Valued constructor (int).
    Melg19937(const unsigned int       seed) noexcept;      //!< Valued constructor (unsigned int).
    Melg19937(const long               seed) noexcept;      //!< Valued constructor (long)
    Melg19937(const unsigned long      seed) noexcept;      //!< Valued constructor (unsigned long).
    Melg19937(const long long          seed) noexcept;      //!< Valued constructor (long long).
    Melg19937(const unsigned long long seed) noexcept;      //!< Valued constructor (unsigned long long).
    Melg19937(const utils::UInt128&    seed) noexcept;      //!< Valued constructor (unsigned 128-bits).
    Melg19937(const double             seed);               //!< Valued constructor (double).

    Melg19937(const state_type& internal_state) noexcept;   //!< Valued constructor (full state).

    virtual inline ~Melg19937() noexcept = default;         //!< default destructor.


    //---   Operations   ----------------------------------------------------
    virtual const output_type next() noexcept override;     //!< The internal PRNG algorithm.

    void seed() noexcept;                                   //!< Initializes internal state (empty signature).

    void seed(const int                seed_) noexcept;     //!< Initializes internal state (int).
    void seed(const unsigned int       seed_) noexcept;     //!< Initializes internal state (unsigned int).
    void seed(const long               seed_) noexcept;     //!< Initializes internal state (long)
    void seed(const unsigned long      seed_) noexcept;     //!< Initializes internal state (unsigned long).
    void seed(const long long          seed_) noexcept;     //!< Initializes internal state (long long).
    void seed(const unsigned long long seed_) noexcept;     //!< Initializes internal state (unsigned long long).
    void seed(const utils::UInt128&    seed_) noexcept;     //!< Initializes internal state (unsigned 128-bits).
    void seed(const double             seed_);              //!< Initializes internal state (double).


private:
    // this definition will avoid an 'if' in method 'next()'
    static constexpr value_type _A_COND[]{ 0ull, 0x5c32'e06d'f730'fc42ull };

};
