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
 * @addtogroup PCG-algorithms
 *
 *  @{
 */


//===========================================================================
#include <cstdint>

#include "baseclasses/basepcg.h"
#include "utils/splitmix.h"
#include "utils/uint128.h"


//===========================================================================
/** @brief Permutated Congruential Generator dedicated to 128-bits calculations and 64-bits output with medium period (about 3.40e+38).
*
*   The Pcg128_64 class implements the  "PCG XSL RR 128/64 (LCG)"  version  of
*   the PCG algorithm, as specified in the related paper (see reference [7] in 
*   document README.md). Output values are returned on 64 bits.
*
*   PCGs are very fast generators, with low memory usage except for a very few
*   of them and medium to very large periods.  They offer jump ahead and multi
*   streams features for most of them. They are difficult to very difficult to
*   invert and to predict.
*
*   See Pcg128_64 for a 2^64 (i.e. about 1.84e+19) period PC-Generator with low
*   computation  time and a shorter period than for Pcg128_64,  with 4 32-bits 
*   word integers memory consumption. Output values are  eturned on 32 bits.
*
*   See Pcg1024_32 for a 2^32,830 (i.e. about 6.53e+9,882) period PC-Generator
*   with low computation time also and a very large period,  but 1,026 32-bits
*   word integers memory consumption. Output values are returned on 32 bits.
*
*   Furthermore this class is callable:
* @code
*     Squares32 rand{};                     // CAUTION: Replace 'BaseSquares' with any inheriting class constructor!
*     std::cout << rand() << std::endl;     // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;    // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     Squares32 diceRoll{};  // CAUTION: Replace 'BaseSquares' with any inheriting class constructor!
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the PCG  algorithms  that
*   have been implemented in CppRandLib, as provided in paper "TestU01, ..." and when
*   available.
*
* +---------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | initial PCG algo name ([7]) | Memory Usage   | Period   | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | --------------------------- | -------------- | -------- | ------------ | ---------------- | ----------- | -------------- |
* | Pcg64_32         | PCG XSH RS 64/32 (LCG)      |    2 x 4-bytes | 2^64     |     0.79     |          0       |       0     |       0        |
* | Pcg128_64        | PCG XSL RR 128/64 (LCG)     |    4 x 4-bytes | 2^128    |     1.70     |          0       |       0     |       0        |
* | Pcg1024_32       | PCG XSH RS 64/32 (EXT 1024) | 1026 x 4-bytes | 2^32,830 |     0.78     |          0       |       0     |       0        |
* +---------------------------------------------------------------------------------------------------------------------------------------------+
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
class Pcg128_64 : public BasePCG<utils::UInt128, std::uint64_t>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BasePCG<utils::UInt128, std::uint64_t>;
    using value_type = utils::UInt128;
    // notice: output_type is defined in base class


    //---   Constructors / Destructor   -------------------------------------
    Pcg128_64() noexcept;                                   //!< Default empty constructor.

    Pcg128_64(const int                seed) noexcept;      //!< Valued constructor (int).
    Pcg128_64(const unsigned int       seed) noexcept;      //!< Valued constructor (unsigned int).
    Pcg128_64(const long               seed) noexcept;      //!< Valued constructor (long)
    Pcg128_64(const unsigned long      seed) noexcept;      //!< Valued constructor (unsigned long).
    Pcg128_64(const long long          seed) noexcept;      //!< Valued constructor (long long).
    Pcg128_64(const unsigned long long seed) noexcept;      //!< Valued constructor (unsigned long long).
    Pcg128_64(const utils::UInt128&    seed) noexcept;      //!< Valued constructor (unsigned 128-bits).
    Pcg128_64(const double             seed);               //!< Valued constructor (double).


    //---   Operations   ----------------------------------------------------
    virtual const output_type next() noexcept override;     //!< The internal PRNG algorithm.

    virtual void seed() noexcept override;                  //!< Initializes internal state (empty signature).

    void seed(const int                seed_) noexcept;     //!< Initializes internal state (int).
    void seed(const unsigned int       seed_) noexcept;     //!< Initializes internal state (unsigned int).
    void seed(const long               seed_) noexcept;     //!< Initializes internal state (long)
    void seed(const unsigned long      seed_) noexcept;     //!< Initializes internal state (unsigned long).
    void seed(const long long          seed_) noexcept;     //!< Initializes internal state (long long).
    void seed(const unsigned long long seed_) noexcept;     //!< Initializes internal state (unsigned long long).
    void seed(const utils::UInt128&    seed_) noexcept;     //!< Initializes internal state (unsigned 128-bits).
    void seed(const double             seed_);              //!< Initializes internal state (double).

    virtual void _setstate(const std::uint64_t   seed_) noexcept override;   //!< Sets the internal state with a 64-bits integer seed.
    virtual void _setstate(const utils::UInt128& seed_) noexcept override;   //!< Sets the internal state with a 128-bits integer seed.


private:
    static const utils::UInt128 _a;  // (std::uint64_t(0x2360'ed05'1fc6'5da4), 0x4385'df64'9fcc'f645ull);
    static const utils::UInt128 _c;  // (std::uint64_t(0x5851'f42d'4c95'7f2d), 0x1405'7b7e'f767'814f);

};

/** @}*/
