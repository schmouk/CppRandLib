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
#include <type_traits>

#include "collatzweylstate.h"
#include "../utils/splitmix.h"
#include "../utils/uint128.h"


//===========================================================================
/** Initalizes the internal state according to a 64-bits integer seed. */
void CollatzWeylState::seed(const std::uint64_t seed_) noexcept
{
    utils::SplitMix64 splitmix_64(seed_);

    _a = _weyl = 0;

    _state.hi = splitmix_64();  // Notice: in the original paper, this seems to be erroneously initialized on sole 64 lowest bits
    _state.lo = splitmix_64();
    
    _s.hi = splitmix_64();
    _s.lo = splitmix_64() | 1; // Notice : _s must be odd
}

//===========================================================================
/** Initalizes the internal state according to a 128-bits integer seed. */
void CollatzWeylState::seed(const value_type seed_) noexcept
{
    utils::SplitMix64 splitmix_hi(seed_.hi);
    utils::SplitMix64 splitmix_lo(seed_.lo);

    _a = _weyl = 0;

    _state.hi = splitmix_hi();  // Notice: in the original paper, this seems to be erroneously initialized on sole 64 lowest bits
    _state.lo = splitmix_lo();

    _s.hi = splitmix_hi();
    _s.lo = splitmix_lo() | 1; // Notice : _s must be odd
}