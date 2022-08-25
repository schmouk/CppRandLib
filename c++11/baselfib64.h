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
#include <array>
#include <cstdint>

#include "baserandom.h"
#include "fastrand63.h"


//===========================================================================
/** @brief The internal state of LFIb PRNG based on 64-bits numbers. */
template<const size_t SIZE>
class LFib64SeedState
{
public:
    std::array<uint64_t, SIZE>  list;
    size_t                      index;
};


//===========================================================================
/** @brief The base class for all LFib PRNG based on 64-bits numbers.
*
*   Definition of the base class for all LFib pseudo-random generators based
*   on 64-bits generated numbers.
*   This module is part of library PyRandLib.
*   
*   Lagged Fibonacci generators LFib( m, r, k, op) use the recurrence
*   
*       x(i) = (x(i-r) op (x(i-k)) mod m
*   
*   where op is an operation that can be:
*       + (addition),
*       - (substraction),
*       * (multiplication),
*       ^(bitwise exclusive-or).
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
*   
*     BaseLFib64 rand();
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
*     std::cout << rand(a,b) << std::endl; // prints a uniform pseudo-random value within [a  , b)
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
template<const size_t SIZE>
class BaseLFib64 : public BaseRandom<LFib64SeedState<SIZE>>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using value_type  = uint64_t;
    using StateType   = LFib64SeedState<SIZE>;
    using MyBaseClass = BaseRandom<StateType>;


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
    void setstate(const double seed) noexcept;


protected:
    /** @brief Inits the internal index pointing to the internal list. */
    inline void _initIndex(const size_t _index) noexcept
    {
        MyBaseClass::_state.seed.index = _index % SIZE;
    }
};
