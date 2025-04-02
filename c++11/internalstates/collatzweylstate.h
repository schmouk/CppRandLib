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
#include <type_traits>

#include "../utils/uint128.h"


//===========================================================================
/** @brief The internal state of counter-based Pseudo Random Numbers Generators. */
class CollatzWeylState
{
public:
    using value_type = utils::UInt128;

    /** @brief Initalizes the internal state according to a 64-bits integer seed. */
    void seed(const std::uint64_t seed_) noexcept;

    /** @brief Initalizes the internal state according to a 128-bits integer seed. */
    void seed(const value_type seed_) noexcept;

private:
    value_type _a{ value_type(0) };
    value_type _s{ value_type(0) };
    value_type _state{ value_type(0) };
    value_type _weyl{ value_type(0) };

};
