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

#include "fastrand32.h"
#include "mrgrand287.h"


//===========================================================================
/** The internal PRNG algorithm. */
const double MRGRand287::random() noexcept
{
    // The Marsa - LIBF4 version uses the recurrence
    //    x(i) = (x(i-55) + x(i-119) + x(i-179) + x(i-256)) mod 2 ^ 32

    // evaluates indexes in suite
    const size_t index = MyBaseClass::_state.seed.index;
    const size_t k55   = (index <  55) ? (index + SEED_SIZE) -  55 : index -  55;
    const size_t k119  = (index < 119) ? (index + SEED_SIZE) - 119 : index - 119;
    const size_t k179  = (index < 179) ? (index + SEED_SIZE) - 179 : index - 179;

    // evaluates current value and modifies internal state
    const uint32_t value = uint64_t(MyBaseClass::_state.seed.list[k55 ]) +
                           uint64_t(MyBaseClass::_state.seed.list[k119]) +
                           uint64_t(MyBaseClass::_state.seed.list[k179]) +
                           uint64_t(MyBaseClass::_state.seed.list[index]);  // automatic 32-bits modulo

    MyBaseClass::_state.seed.list[index] = value;
    // next index
    MyBaseClass::_state.seed.index = (index + 1) % SEED_SIZE;

    // finally, returns pseudo random value in range [0.0, 1.0)
    const double ret = double(value) / double(4'294'967'296.0);
    return ret;
}
