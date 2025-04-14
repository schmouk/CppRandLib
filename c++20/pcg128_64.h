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
*   See Pcg64_32 for a 2^64 (i.e. about 1.84e+19) period PC-Generator with low
*   computation  time and a shorter period than for Pcg128_64,  with 4 32-bits 
*   word integers memory consumption. Output values are  eturned on 32 bits.
*
*   See Pcg1024_32 for a 2^32,830 (i.e. about 6.53e+9,882) period PC-Generator
*   with low computation time also and a very large period,  but 1,026 32-bits
*   word integers memory consumption. Output values are returned on 32 bits.
*
*   Please notice that this class and all its  inheriting  sub-classes
*   are callable. Example:
* @code
*     Squares32 rand{};                     // CAUTION: Replace 'BaseSquares' with any inheriting class constructor!
*     std::cout << rand() << std::endl;     // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;    // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     Squares32 diceRoll{};  // CAUTION: Replace 'BaseSquares' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the WELL  algorithms  that
*   have  been implemented in CppRandLib, as provided in paper "TestU01, ..." and when
*   available.
*
* +--------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRandLib class | initial PCG algo name ([7]) | Memory Usage   | Period   | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | --------------- | --------------------------- | -------------- | -------- | ------------ | ---------------- | ----------- | -------------- |
* | Pcg64_32        | PCG XSH RS 64/32 (LCG)      |    2 x 4-bytes | 2^64     |     0.79     |          0       |       0     |       0        |
* | Pcg128_64       | PCG XSL RR 128/64 (LCG)     |    4 x 4-bytes | 2^128    |     1.70     |          0       |       0     |       0        |
* | Pcg1024_32      | PCG XSH RS 64/32 (EXT 1024) | 1026 x 4-bytes | 2^32,830 |     0.78     |          0       |       0     |       0        |
* +--------------------------------------------------------------------------------------------------------------------------------------------+
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


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline Pcg128_64() noexcept
        : MyBaseClass()
    {
        MyBaseClass::seed();
    }

    /** @brief Valued construtor. */
    inline Pcg128_64(const std::uint64_t seed_) noexcept
        : MyBaseClass()
    {
        MyBaseClass::seed(seed_);
    }

    Pcg128_64(const Pcg128_64&) noexcept = default;   //!< default copy constructor.
    Pcg128_64(Pcg128_64&&) noexcept = default;        //!< default move constructor.
    virtual ~Pcg128_64() noexcept = default;          //!< default destructor.


    //---   Assignments operators   -----------------------------------------
    Pcg128_64& operator= (const Pcg128_64&) noexcept = default;   //!< default copy assignment.
    Pcg128_64& operator= (Pcg128_64&&) noexcept = default;        //!< default move assignment.


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * @return an integer value coded on 32 bits.
    */
    virtual const output_type next() noexcept override;  // notice: output_type is defined in base class.


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state with an integer seed. */
    virtual inline void _setstate(const std::uint64_t seed) noexcept override
    {
        utils::SplitMix64 splitmix64(seed);
        _internal_state.state = utils::UInt128(splitmix64(), splitmix64());
    }

    /** @brief Sets the internal state with an UInt128 seed. */
    virtual inline void _setstate(const utils::UInt128 seed) noexcept
    {
        _internal_state.state = seed;
    }


private:
    static const utils::UInt128 _a;  // (std::uint64_t(0x2360'ed05'1fc6'5da4), 0x4385'df64'9fcc'f645ull);
    static const utils::UInt128 _c;  // (std::uint64_t(0x5851'f42d'4c95'7f2d), 0x1405'7b7e'f767'814f);

};
