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

#include "basexoroshiro.h"


//===========================================================================
/** @brief A fast 64-bits Scrambled Linear Pseudorandom Number Generators with a long period (1.34e+154)
*
    This pseudorandom numbers generator implements  the  xoroshiro512**  pseudo-random
    generator,  the eight 64-bits integers state array version of the Scrambled Linear
    Pseudorandom Number Generators. It provides 64-bits pseudo random values, a medium
    period  2^512 (i.e. about 1.34e+154),  jump ahead feature,  very short escape from
    zeroland (30 iterations only) and passes TestU01 tests.
*
*   The base xoroshiro linear transformation  is  obtained  combining  a  rotation,  a
*   shift,  and  again  a  rotation.  An  additional  scrambling  method  based on two
*   multiplications is also computed for this version xoroshiro256** of the algorithm.
*
*   See Xoroshiro512 for a large 2^256 period (i.e. about  1.16e+77)  scramble  linear
*   PRNG,  with  low  computation  time,  64-bits  output  values  and good randomness
*   characteristics.
*   See Xoroshiro1024 for a large 2^1024 period (i.e. about 1.80e+308) scramble linear
*   PRNG,  with  low computation time,  64-bits output values and very good randomness
*   characteristics.
*
*   Reminder:
*   We give you here below a copy of the table of tests for the xoroshiros  that  have
*   been  implemented  in CppRandLib,  as  described by the authors of xoroshiro - see
*   reference [10] in file README.md.
*
* +------------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRandLib class | initial xoroshiro algo name | Memory Usage | Period | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | --------------- | --------------------------- | ------------ | ------ | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Xoroshiro512    | xoroshiro256**              |  8 x 4-bytes | 2^256  |    n.a.     |     0.84     |          0       |       0     |       0        |
* | Xoroshiro512    | xoroshiro512**              | 16 x 4-bytes | 2^512  |    n.a.     |     0.99     |          0       |       0     |       0        |
* | Xoroshiro1024   | xoroshiro1024**             | 32 x 4-bytes | 2^1024 |    n.a.     |     1.17     |          0       |       0     |       0        |
* +------------------------------------------------------------------------------------------------------------------------------------------------------+
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
class Xoroshiro512 : public BaseXoroshiro<8>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseXoroshiro<8>;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty constructor. */
    inline Xoroshiro512() noexcept
        : MyBaseClass()
    {
    }

    /** @brief Valued construtor. */
    template<typename T>
    inline Xoroshiro512(const T seed_) noexcept
        : MyBaseClass()
    {
        MyBaseClass::seed(seed_);
    }

    /** @brief Valued constructor (full state). */
    inline Xoroshiro512(const state_type& seed) noexcept
        : MyBaseClass(seed)
    {
    }

    Xoroshiro512(const Xoroshiro512&) noexcept = default;   //!< default copy constructor.
    Xoroshiro512(Xoroshiro512&&) noexcept = default;        //!< default move constructor.
    virtual ~Xoroshiro512() noexcept = default;             //!< default destructor.


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * @return an integer value coded on OUTPUT_BITS bits.
    */
    virtual const output_type next() noexcept override;

};
