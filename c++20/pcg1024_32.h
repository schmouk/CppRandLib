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
#include <vector>

#include "baseclasses/basepcg.h"
#include "internalstates/extendedstate.h"
#include "pcg64_32.h"
#include "utils/splitmix.h"


//===========================================================================
/** @brief Permutated Congruential Generator dedicated to 64-bits calculations and 32-bits output with medium period (about 1.84e+19).
*
*   This Pcg1024_32 class implements the "PCG XSH RS 64/32 (EXT 1024)" version
*   of the PCG algorithm, as specified in the related paper (see reference [7]
*   in document README.md). Output values are returned on 32 bits. State value
*   is coded on 64-bits. Each value in extended state is coded on 32-bits.
*
*   PCGs are very fast generators, with low memory usage except for a very few
*   of them and medium to very large periods.  They offer jump ahead and multi
*   streams features for most of them. They are difficult to very difficult to
*   invert and to predict.
*
*   See Pcg64_32 for a 2^64 (i.e. 1.84e+19) period PC-Generator with very  low
*   computation  time  and  medium period, with 2 32-bits word integers memory
*   consumption. Output values are returned on 32 bits.

*   See Pcg128_64 for a 2^128 (i.e. about 3.40e+38) period  PC-Generator  with
*   low  computation  time also and a longer period than for Pcg64_32,  with 4
*   32-bits word integers memory consumption.  Output values are  returned  on
*   64 bits.
*
*   Please notice that this class and all its  inheriting  sub-classes
*   are callable. Example:
* @code
*     Pcg1024_32 rand{};
*     std::cout << rand() << std::endl;     // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;    // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     Pcg1024_32 diceRoll{};
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the PCG  algorithms  that
*   have been implemented in CppRandLib, as provided in paper "TestU01, ..." and when
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
class Pcg1024_32 : public BasePCG<ExtendedState<Pcg64_32, std::uint32_t, 1024>, std::uint32_t>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BasePCG<ExtendedState<Pcg64_32, std::uint32_t, 1024>, std::uint32_t>;
    using state_type = MyBaseClass::state_type;
    using value_type = MyBaseClass::state_type::value_type;
    using extended_value_type = MyBaseClass::state_type::extended_value_type;

    static const std::uint64_t _MODULO_32{ (1ull << 32) - 1ull };
    static const unsigned int  _STATE_SIZE{ 1024 };
    static const unsigned int  _INDEX_MODULO{ _STATE_SIZE - 1 };  // notice: this is ok because _STATE_SIZE is a power of two


    //---   Constructors / Destructor   -------------------------------------
    Pcg1024_32() noexcept;                                  //!< Default empty constructor.

    Pcg1024_32(const int                seed) noexcept;     //!< Valued constructor (int).
    Pcg1024_32(const unsigned int       seed) noexcept;     //!< Valued constructor (unsigned int).
    Pcg1024_32(const long               seed) noexcept;     //!< Valued constructor (long)
    Pcg1024_32(const unsigned long      seed) noexcept;     //!< Valued constructor (unsigned long).
    Pcg1024_32(const long long          seed) noexcept;     //!< Valued constructor (long long).
    Pcg1024_32(const unsigned long long seed) noexcept;     //!< Valued constructor (unsigned long long).
    Pcg1024_32(const utils::UInt128& seed) noexcept;     //!< Valued constructor (unsigned 128-bits).
    Pcg1024_32(const double             seed);              //!< Valued constructor (double).


    //---   Operations   ----------------------------------------------------
    virtual const output_type next() noexcept override;     //!< The internal PRNG algorithm.

    virtual void seed() noexcept override;                  //!< Initializes internal state (empty signature).

    void seed(const int                seed_) noexcept;     //!< Initializes internal state (int).
    void seed(const unsigned int       seed_) noexcept;     //!< Initializes internal state (unsigned int).
    void seed(const long               seed_) noexcept;     //!< Initializes internal state (long)
    void seed(const unsigned long      seed_) noexcept;     //!< Initializes internal state (unsigned long).
    void seed(const long long          seed_) noexcept;     //!< Initializes internal state (long long).
    void seed(const unsigned long long seed_) noexcept;     //!< Initializes internal state (unsigned long long).
    void seed(const utils::UInt128& seed_) noexcept;     //!< Initializes internal state (unsigned 128-bits).
    void seed(const double             seed_);              //!< Initializes internal state (double).

    virtual void _setstate(const std::uint64_t   seed_) noexcept override;   //!< Sets the internal state with a 64-bits integer seed.
    virtual void _setstate(const utils::UInt128& seed_) noexcept override;   //!< Sets the internal state with a 128-bits integer seed.


private:
    //---   Operations   ----------------------------------------------------
    /** Advances the extended states. */
    void _advance_table() noexcept;

    /** Evaluates new extended state indexed value in the extended state table.
    *
    *   Returns True when the evaluated extended value is set to zero on all bits
    *   but its two lowest ones - these two bits never change with MCGs.
    */
    const bool _external_step(extended_value_type e, unsigned int i) noexcept;

    /** Evaluates the inversion of an xor-shift operation. */
    static const extended_value_type _invxrs(
        const extended_value_type value,
        const unsigned int bits_count,
        const unsigned int shift
    );

};
