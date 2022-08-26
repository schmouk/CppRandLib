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

    // evaluates indexes in suite for the i-5 and i-17 -th values
    const size_t index = MyBaseClass::_state.seed.index;
    const size_t k55 = (index < 55) ? (index + SEED_SIZE) - 55 : index - 55;
    const size_t k119 = (index < 119) ? (index + SEED_SIZE) - 119 : index - 119;
    const size_t k179 = (index < 179) ? (index + SEED_SIZE) - 179 : index - 179;

    // evaluates current value and modifies internal state
    const uint32_t value = MyBaseClass::_state.seed.list[k55] +
        MyBaseClass::_state.seed.list[k119] +
        MyBaseClass::_state.seed.list[k179] +
        MyBaseClass::_state.seed.list[index];  // automatic 32-bits modulo
    MyBaseClass::_state.seed.list[index] = value;

    // next index
    MyBaseClass::_state.seed.index = (index + 1) % SEED_SIZE;

    // finally, returns pseudo random value in range [0.0, 1.0)
    return double(value) / double(4'294'967'295.0);
}

/** Sets the internal state of this PRNG from current time (empty signature). */
void MRGRand287::setstate() noexcept
{
    const uint64_t ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    const uint32_t t32 = uint32_t(ticks & 0xffff'ffff);
    setstate(((t32 & 0xff00'0000) >> 24) +
             ((t32 & 0x00ff'0000) >> 8) +
             ((t32 & 0x0000'ff00) << 8) +
             ((t32 & 0x0000'00ff) << 24));
}


/** Sets the internal state of this PRNG with an integer seed. */
void MRGRand287::setstate(const uint32_t seed) noexcept
{
    FastRand32 rand(seed);
    for (auto it = MyBaseClass::_state.seed.list.begin(); it != MyBaseClass::_state.seed.list.end(); )
        *it++ = uint32_t(rand() * 0x1'0000'0000ull);
}
