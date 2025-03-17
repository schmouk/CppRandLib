/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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
#include "mrg1457.h"


//===========================================================================
/** The internal PRNG algorithm. */
const Mrg1457::output_type Mrg1457::next() noexcept
{
    // evaluates indexes in suite for the i-1, i-24 (and i-47) -th values
    const std::uint32_t index = _state.seed.index;
    const std::uint32_t k1    = (index <  1) ? (index + SEED_SIZE) -  1 : index -  1;
    const std::uint32_t k24   = (index < 24) ? (index + SEED_SIZE) - 24 : index - 24;

    // evaluates current value and modifies internal state
    std::uint64_t value = (0x0408'0000ull * (std::uint64_t(_state.seed.list[k1]) +
                                             std::uint64_t(_state.seed.list[k24]) +
                                             std::uint64_t(_state.seed.list[index]))) % (_MODULO - 1);
    _state.seed.list[index] = std::uint32_t(value &= _MODULO);

    // next index
    _state.seed.index = (index + 1) % SEED_SIZE;

    // finally, returns pseudo random value
    return output_type(value);
}
