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
#include "utils/splitmix.h"


//===========================================================================
/** @brief Permutated Congruential Generator dedicated to 64-bits calculations and 32-bits output with medium period (about 1.84e+19).
*
*   This Pcg1024_32 class implements the "PCG XSH RS 64/32 (EXT 1024)" version
*   of the PCG algorithm, as specified in the related paper (see reference [7]
*   in document README.md). Output values are returned on 32 bits.
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
class Pcg1024_32 : public BasePCG<std::vector<std::uint32_t>, std::uint32_t>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BasePCG<std::vector<std::uint32_t>, std::uint32_t>;
    using value_type = std::uint32_t;

    static const std::uint64_t _MODULO{ (1ull << 32) - 1ull };
    static const std::size_t   _STATE_SIZE{ 1024 };
    static const std::size_t   _STATE_INDEX{ _STATE_SIZE };


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline Pcg1024_32() noexcept
        : MyBaseClass()
    {
        MyBaseClass::seed();
    }

    /** @brief Valued construtor. */
    inline Pcg1024_32(const std::uint64_t seed_) noexcept
        : MyBaseClass()
    {
        MyBaseClass::seed(seed_);
    }

    Pcg1024_32(const Pcg1024_32&) noexcept = default;   //!< default copy constructor.
    Pcg1024_32(Pcg1024_32&&) noexcept = default;        //!< default move constructor.
    virtual ~Pcg1024_32() noexcept = default;           //!< default destructor.


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
        // implementation notice: the original paper sets a one 64-bits integer as
        // the internal state and 1,024 others as the extended internal state.  We
        // put all of these in a single vector that finally contains 1,025 items.
        _internal_state.state.resize(_STATE_SIZE + 1);

        utils::SplitMix64 splitmix_64(seed);
        for (auto& s : _internal_state.state)
            s = splitmix_64();
    }


private:
    //---   Operations   ----------------------------------------------------
    /** Evaluates the inversion of an xor-shift operation. */
    static const value_type _invxrs(
        const value_type value,
        const unsigned int bits_count,
        const unsigned int shift
    )
    {
        if (shift * 2 >= bits_count)
            return value ^ (value >> shift);

        const unsigned int new_bits_shift{ bits_count - shift };
        const value_type bot_mask{ (1ull << (bits_count - shift * 2)) - 1ull };
        const value_type top_mask{ ~bot_mask & 0xffff'ffffull };
        const value_type top{ (value ^ (value >> shift)) };
        const value_type bot{ _invxrs((top | (value & bot_mask)) & ((1ull << new_bits_shift) - 1), new_bits_shift, shift) };

        return (top & top_mask) | (bot & bot_mask);
    }

};
