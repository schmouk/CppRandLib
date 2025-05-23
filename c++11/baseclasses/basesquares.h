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

#include "baserandom.h"
#include "../internalstates/counterkeystate.h"


//===========================================================================
/** @brief The base class for all Squares counter-based pseudorandom Generators.
*
*   Squares models are based on an incremented counter and a key.  The
*   algorithm squares a combination of the counter and the key values,
*   and exchanges the upper and lower bits  of  the  combination,  the
*   whole  repeated  a number of times (4 to 5 rounds).  Output values
*   are provided on 32-bits or on 64-bits according to the model.  See
*   [9] in README.md.
*
*   See Squares32 for a 2^64 (i.e. about 1.84e+19)  period  PRNG  with
*   low  computation  time,  medium period,  32-bits output values and
*   very good randomness characteristics.
*
*   See Squares64 for a 2^64 (i.e. about 1.84e+19)  period  PRNG  with
*   low  computation  time,  medium period,  64-bits output values and
*   very good randomness characteristics. Caution: the 64-bits version
*   should  not  pass the birthday test,  which is a randomness issue,
*   while this is not mentionned in the original paper - see reference
*   [9] in file README.md.
*
*   Please notice that this class and all its  inheriting  sub-classes  
*   are callable. Example:
* @code
*     BaseSquares rand{};                   // CAUTION: Replace 'BaseSquares' with any inheriting class constructor!
*     std::cout << rand() << std::endl;     // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;    // prints a uniform pseudo-random value within [0.0, b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     BaseSquares diceRoll{};               // CAUTION: Replace 'BaseSquares' with any inheriting class constructor!
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Reminder:
*   We give you here below a copy of the table of tests for the WELL  algorithms  that
*   have  been implemented in CppRandLib, as provided in paper "TestU01, ..." and when
*   available.
*
* +--------------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | [9] generator name | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------ | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | Squares32        | squares32          |  4 x 4-bytes    |   2^64  |    n.a.     |     n.a.     |          0       |       0     |       0        |
* | Squares64        | squares64          |  4 x 4-bytes    |   2^64  |    n.a.     |     n.a.     |          0       |       0     |       0        |
* +--------------------------------------------------------------------------------------------------------------------------------------------------+
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
template<typename OutputT>
class BaseSquares : public BaseRandom<CounterKeyState, OutputT, 8 * sizeof(OutputT)>
{
public:
    //---   Wrappers   ------------------------------------------------------
    using MyBaseClass = BaseRandom<CounterKeyState, OutputT, 8 * sizeof(OutputT)>;
    using output_type = OutputT;
    using state_type  = MyBaseClass::state_type;
    using value_type  = typename state_type::value_type;


    //---   Constructors / Destructor   -------------------------------------
    inline BaseSquares() noexcept;                                  //!< Default empty constructor.

    inline BaseSquares(const int                seed) noexcept;     //!< Valued constructor (int).
    inline BaseSquares(const unsigned int       seed) noexcept;     //!< Valued constructor (unsigned int).
    inline BaseSquares(const long               seed) noexcept;     //!< Valued constructor (long)
    inline BaseSquares(const unsigned long      seed) noexcept;     //!< Valued constructor (unsigned long).
    inline BaseSquares(const long long          seed) noexcept;     //!< Valued constructor (long long).
    inline BaseSquares(const unsigned long long seed) noexcept;     //!< Valued constructor (unsigned long long).
    inline BaseSquares(const utils::UInt128&    seed) noexcept;     //!< Valued constructor (unsigned 128-bits).
    inline BaseSquares(const double             seed);              //!< Valued constructor (double).

    inline BaseSquares(const state_type& internal_state) noexcept;  //!< Valued constructor (full state).

    virtual inline ~BaseSquares() noexcept = default;               //!< default destructor.


    //---   Operations   ----------------------------------------------------
    void inline seed() noexcept;                                    //!< Initializes internal state (empty signature).

    void inline seed(const int                seed_) noexcept;      //!< Initializes internal state (int).
    void inline seed(const unsigned int       seed_) noexcept;      //!< Initializes internal state (unsigned int).
    void inline seed(const long               seed_) noexcept;      //!< Initializes internal state (long)
    void inline seed(const unsigned long      seed_) noexcept;      //!< Initializes internal state (unsigned long).
    void inline seed(const long long          seed_) noexcept;      //!< Initializes internal state (long long).
    void inline seed(const unsigned long long seed_) noexcept;      //!< Initializes internal state (unsigned long long).
    void inline seed(const utils::UInt128&    seed_) noexcept;      //!< Initializes internal state (unsigned 128-bits).
    void inline seed(const double             seed_);               //!< Initializes internal state (double).

    virtual inline void _setstate(const std::uint64_t   seed) noexcept override;    //!< Sets the internal state of this PRNG with a 64-bits integer seed.
    virtual inline void _setstate(const utils::UInt128& seed) noexcept override;    //!< Sets the internal state of this PRNG with a 128-bits integer seed.

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
/** Empty constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares() noexcept
    : MyBaseClass()
{
    MyBaseClass::seed();
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const unsigned int seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const unsigned long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const unsigned long long seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (unsigned 128-bits). */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const utils::UInt128& seed_) noexcept
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor. */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const double seed_)
    : MyBaseClass()
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Valued constructor (full state). */
template<typename OutputT>
inline BaseSquares<OutputT>::BaseSquares(const state_type& internal_state) noexcept
    : MyBaseClass()
{
    MyBaseClass::setstate(internal_state);
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG from current time (empty signature). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed() noexcept
{
    _setstate(utils::set_random_seed64());
}

//---------------------------------------------------------------------------
/** Initializes internal state (int). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const int seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned int). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const unsigned int seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const unsigned long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (long long). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const long long seed_) noexcept
{
    MyBaseClass::seed(std::uint64_t(seed_));
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned long long). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const unsigned long long seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (unsigned 128-bits). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::seed(seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state (double). */
template<typename OutputT>
inline void BaseSquares<OutputT>::seed(const double seed_)
{
    MyBaseClass::seed(seed_);
}


//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 64-bits integer seed. */
template<typename OutputT>
inline void BaseSquares<OutputT>::_setstate(const std::uint64_t seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_);  // notice: the std::uint64_t specialization of this method is automatically called here
    MyBaseClass::_internal_state.state.counter = 0;
}

//---------------------------------------------------------------------------
/** Sets the internal state of this PRNG with a 128-bits integer seed. */
template<typename OutputT>
inline void BaseSquares<OutputT>::_setstate(const utils::UInt128& seed_) noexcept
{
    MyBaseClass::_internal_state.state.seed(seed_.lo);
    MyBaseClass::_internal_state.state.counter = 0;
}
