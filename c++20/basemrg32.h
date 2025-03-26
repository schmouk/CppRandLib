#pragma once
/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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
#include <algorithm>
#include <cstdint>

#include "baserandom.h"
#include "listseedstate.h"
#include "utils/splitmix.h"


//===========================================================================
/** @brief The base support for 32-bits MRG Pseudo Random Number Generators.
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
*   See Mrg287 for  a  short  period  MR-Generator  (2^287,  i.e. 2.49e+86)  with  low
*   computation time but 256 integers memory consumption (2^32 modulus calculations).
*   See Mrg1457 for a longer period MR-Generator  (2^1457,  i.e. 4.0e+438)  and longer
*   computation  time  (2^31-1 modulus calculations) but less memory space consumption
*   (i.e. 47 integers).
*   See Mrg49507 for  a  far  longer  period  (2^49_507,  i.e. 1.2e+14_903)  with  low
*   computation  time  too  (31-bits  modulus)  but  use  of  more memory space (1_597
*   integers).
*
*   Furthermore this class is callable:
* @code
*     BaseMRG32 rand(); // CAUTION: Replace 'BaseMRG32' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     BaseMRG32 diceRoll();
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
*   the expected characteristics for a pretty good PRNG;
*
*   * _crush_ is a bigger set of tests that test more deeply  expected  random
*   characteristics;
*
*   * _big crush_ is the ultimate set of difficult tests  that  any  GOOD  PRNG
*   should definitively pass.
*/
template<const size_t SIZE>
class BaseMRG32 : public BaseRandom<ListSeedState<std::uint32_t, SIZE>>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<ListSeedState<std::uint32_t, 256>>;

    using output_type = MyBaseClass::output_type;
    using state_type = MyBaseClass::state_type;
    using value_type = typename state_type::value_type;

    static constexpr std::uint32_t SEED_SIZE{ SIZE };


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline BaseMRG32() noexcept;

    /** @brief Valued construtor. */
    template<typename T>
    inline BaseMRG32(const T seed_) noexcept;

    /** @brief Valued constructor (full state). */
    inline BaseMRG32(const state_type& internal_state) noexcept;

    /** @brief Default Destructor. */
    virtual ~BaseMRG32() noexcept = default;


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state of this PRNG from current time (empty signature). */
    virtual inline void seed() noexcept override;

    /** @brief Sets the internal state of this PRNG with an integer seed. */
    virtual inline void _setstate(const std::uint64_t seed) noexcept override;

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Empty constructor. */
template<const size_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32() noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued construtor. */
template<const size_t SIZE>
template<typename T>
inline BaseMRG32<SIZE>::BaseMRG32(const T seed_) noexcept
    : MyBaseClass()
{
    seed();
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<const size_t SIZE>
inline BaseMRG32<SIZE>::BaseMRG32(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG from current time (empty signature). */
template<const size_t SIZE>
inline void BaseMRG32<SIZE>::seed() noexcept
{
    _setstate(utils::set_random_seed32());
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with an integer seed. */
template<const size_t SIZE>
inline void BaseMRG32<SIZE>::_setstate(const std::uint64_t seed) noexcept
{
    utils::SplitMix32 splitmix_32(std::uint32_t(seed & 0xffff'ffff));
    std::ranges::generate(MyBaseClass::_internal_state.state.list, [&]() { return splitmix_32(); });
}
