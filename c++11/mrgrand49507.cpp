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
#include "mrgrand49507.h"


//===========================================================================
/** The internal PRNG algorithm. */
const double MRGRand49507::random() noexcept
{
    // evaluates indexes in suite for the i-1, i-24 (and i-47) -th values
    const size_t index = MyBaseClass::_state.seed.index;
    const size_t k7 = (index < 7) ? (index + SEED_SIZE) - 7 : index - 7;

    // evaluates current value and modifies internal state
    const uint64_t value = (0xffff'ffff'fdff'ff80 * (uint64_t(MyBaseClass::_state.seed.list[k7]) +
                                                     uint64_t(MyBaseClass::_state.seed.list[index]))) % MODULO;
    MyBaseClass::_state.seed.list[index] = uint32_t(value);

    // next index
    MyBaseClass::_state.seed.index = (index + 1) % SEED_SIZE;

    // finally, returns pseudo random value in range [0.0, 1.0)
    return double(value) / double(MODULO);
}
