#pragma once
/*
MIT License

Copyright (c) 2022 Philippe Schmouker, ph.schmouker (at) gmail.com

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
#include <chrono>

#include "baserandom.h"
#include "fastrand63.h"
#include "listseedstate.h"


//===========================================================================
/** @brief The base class for all LFib PRNG based on 64-bits numbers.
*
*   Definition of the base class for all LFib pseudo-random generators based
*   on 64-bits generated numbers.
* 
*   This module is part of library CppRandLib.
*   
*   Lagged Fibonacci generators LFib( m, r, k, op) use the recurrence
*   
*       x(i) = (x(i-r) op (x(i-k)) mod m
*   
*   where op is an operation that can be:
*       + (addition),
*       - (substraction),
*       * (multiplication),
*       ^ (bitwise exclusive-or).
*   
*   With the + or - operation, such generators are in fact MRGs. They offer very large
*   periods  with  the  best  known  results in the evaluation of their randomness, as
*   stated in the evaluation done by Pierre L'Ecuyer and Richard Simard (Universite de
*   Montreal)  in  "TestU01:  A  C  Library  for Empirical Testing  of  Random  Number  
*   Generators - ACM Transactions  on  Mathematical  Software,  vol.33 n.4,  pp.22-40, 
*   August 2007".  It  is  recommended  to  use  such pseudo-random numbers generators 
*   rather than LCG ones for serious simulation applications.
*      
*   See LFib78,  LFib116,  LFib668 and LFib1340 for long period LFib generators (resp. 
*   2^78,  2^116,  2^668 and 2^1340 periods, i.e. resp. 3.0e+23, 8.3e+34, 1.2e+201 and 
*   2.4e+403 periods) while same computation time and far  higher  precision  (64-bits  
*   calculations) than MRGs,  but more memory consumption (resp. 17,  55, 607 and 1279 
*   integers).
*   
*   Please notice that this class and all its  inheriting  sub-classes  are  callable.
*   Example:
* @code
*     BaseLFib64 rand{}; // CAUTION: this won't compile since BaseLFib64 is an abstract class. Replace 'BaseLFib64' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
*     std::cout << rand(a,b) << std::endl; // prints a uniform pseudo-random value within [a  , b)
* @endoced
*
*   Notice that for simulating the roll of a dice you should program:
* @code
*     BaseLFib64 diceRoll(); // CAUTION: this won't compile since BaseLFib64 is an abstract class. Replace 'BaseLFib64' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
* 
*   Reminder:
*   We give you here below a copy of the table of tests for the LCGs that have 
*   been implemented in PyRandLib, as provided in paper "TestU01, ..."  -  see
*   file README.md.
* +--------------------------------------------------------------------------------------------------------------------------------------------------------+
* | PyRabndLib class | TU01 generator name      | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------------ | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | LFibRand78       | LFib(2^64, 17, 5, +)     |    34 x 4-bytes | 2^78    |    n.a.     |     1.1      |          0       |       0     |       0        |
* | LFibRand116      | LFib(2^64, 55, 24, +)    |   110 x 4-bytes | 2^116   |    n.a.     |     1.0      |          0       |       0     |       0        |
* | LFibRand668      | LFib(2^64, 607, 273, +)  | 1,214 x 4-bytes | 2^668   |    n.a.     |     0.9      |          0       |       0     |       0        |
* | LFibRand1340     | LFib(2^64, 1279, 861, +) | 2,558 x 4-bytes | 2^1340  |    n.a.     |     0.9      |          0       |       0     |       0        |
* +--------------------------------------------------------------------------------------------------------------------------------------------------------+
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
template<const size_t SIZE, const size_t K>
class BaseLFib64 : public BaseRandom<ListSeedState<uint64_t, SIZE>>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using value_type  = uint64_t;
    using StateType   = ListSeedState<uint64_t, SIZE>;
    using MyBaseClass = BaseRandom<StateType>;

    static inline constexpr size_t SEED_SIZE = SIZE;


    //---   Constructors / Destructor   -------------------------------------
    /** @brief Default Empty constructor. */
    inline BaseLFib64() noexcept
        : MyBaseClass()
    {
        setstate();
    }

    /** @brief Valued construtor (integer). */
    inline BaseLFib64(const uint64_t seed) noexcept
        : MyBaseClass()
    {
        setstate(seed);
    }

    /** @brief Valued construtor (double). */
    inline BaseLFib64(const double seed) noexcept
        : MyBaseClass()
    {
        setstate(seed);
    }

    /** @brief Valued constructor (full state). */
    inline BaseLFib64(const StateType& seed) noexcept
        : MyBaseClass()
    {
        setstate(seed);
    }

    /** @brief Default Copy constructor. */
    BaseLFib64(const BaseLFib64&) noexcept = default;

    /** @brief Default Move constructor. */
    BaseLFib64(BaseLFib64&&) noexcept = default;

    /** @brief Default Destructor. */
    virtual ~BaseLFib64() noexcept = default;


    //---   Assignments   ---------------------------------------------------
    /** @brief Default Copy assignment. */
    BaseLFib64& operator= (const BaseLFib64&) noexcept = default;

    /** @brief Default Move assignment. */
    BaseLFib64& operator= (BaseLFib64&&) noexcept = default;

    /** @brief Seed assignment (integer). */
    inline BaseLFib64& operator= (const uint64_t seed) noexcept
    {
        MyBaseClass::setstate(seed);
        return *this;
    }

    /** @brief Seed assignment (double). */
    inline BaseLFib64& operator= (const double seed) noexcept
    {
        MyBaseClass::setstate(seed);
        return *this;
    }


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state of this PRNG from current time (empty signature). */
    virtual void setstate() noexcept override;

    /** @brief Sets the internal state of this PRNG with an integer seed. */
    void setstate(const uint64_t seed) noexcept;

    /** @brief Sets the internal state of this PRNG with a double seed. */
    inline void setstate(const double seed) noexcept
    {
        setstate(uint64_t(seed * double(0xffff'ffff'ffff'ffffUL)));
    }

    /** @brief Restores the internal state of this PRNG from seed. */
    inline void setstate(const StateType& seed) noexcept
    {
        MyBaseClass::_state.seed = seed;
        MyBaseClass::_state.gauss_valid = false;
    }

    /** @brief Restores the internal state of this PRNG from seed and gauss_next. */
    inline  void setstate(const StateType& seed, const double gauss_next) noexcept
    {
        MyBaseClass::_state.seed = seed;
        MyBaseClass::_state.gauss_next = gauss_next;
        MyBaseClass::_state.gauss_valid = true;
    }


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * @return a double value uniformly contained within range [0.0, 1.0).
    */
    virtual const double random() noexcept override;


protected:
    /** @brief Inits the internal index pointing to the internal list. */
    inline void _initIndex(const size_t _index) noexcept
    {
        MyBaseClass::_state.seed.index = _index % SIZE;
    }
};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
/** The internal PRNG algorithm. */
template<const size_t SIZE, const size_t K>
const double BaseLFib64<SIZE, K>::random() noexcept
{
    // evaluates indexes in suite for the i-5 and i-17 -th values
    const size_t index = MyBaseClass::_state.seed.index;
    const size_t k = (index < K) ? (index + SEED_SIZE) - K : index - K;

    // evaluates current value and modifies internal state
    uint64_t value = MyBaseClass::_state.seed.list[k] + MyBaseClass::_state.seed.list[index];  // automatic 64-bits modulo
    MyBaseClass::_state.seed.list[index] = value;

    // next index
    MyBaseClass::_state.seed.index = (index + 1) % SEED_SIZE;

    // finally, returns pseudo random value in range [0.0, 1.0)
    return double((long double)value / (long double)18'446'744'073'709'551'616.0);
}


/** Sets the internal state of this PRNG from current time (empty signature). */
template<const size_t SIZE, const size_t K>
void BaseLFib64<SIZE, K>::setstate() noexcept
{
    const uint64_t ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    setstate(((ticks & 0x0000'0000'7fff'ffff) << 32) +
             ((ticks & 0xff00'0000'0000'0000) >> 56) +
             ((ticks & 0x00ff'0000'0000'0000) >> 40) +
             ((ticks & 0x0000'ff00'0000'0000) >> 24) +
             ((ticks & 0x0000'00ff'0000'0000) >> 8));
}


/** Sets the internal state of this PRNG with an integer seed. */
template<const size_t SIZE, const size_t K>
void BaseLFib64<SIZE, K>::setstate(const uint64_t seed) noexcept
{
    FastRand63 myRand(seed);
    for (auto it = MyBaseClass::_state.seed.list.begin(); it != MyBaseClass::_state.seed.list.end(); )
        *it++ = myRand(0x7fff'ffff'ffff'ffffULL) * 2 + myRand(2);
}
