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
#include "uint128.h"


//===========================================================================
namespace utils
{
    //---------------------------------------------------------------------------
    UInt128& UInt128::operator+= (const UInt128& other) noexcept
    {
        bool carry{ false };

        std::uint32_t w0{ lo & 0xffff'ffffull }, w1{ lo >> 32 };
        carry = _add_carry(w0, other.lo & 0xffff'ffffull, false);
        carry = _add_carry(w1, other.lo >> 32, carry);

        std::uint32_t w2{ hi & 0xffff'ffffull }, w3{ hi >> 32 };
        carry = _add_carry(w2, other.hi & 0xffff'ffffull, carry);
        _add_carry(w3, other.hi >> 32, carry);  // notice: last carry can be ignored.

        this->hi = (std::uint64_t(w3) << 32) | w2;
        this->lo = (std::uint64_t(w1) << 32) | w0;
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator+= (const std::uint64_t value) noexcept
    {
        bool carry{ false };

        std::uint32_t w0{ lo & 0xffff'ffffull }, w1{ lo >> 32 };
        carry = _add_carry(w0, value & 0xffff'ffffull, false);
        carry = _add_carry(w1, value >> 32, carry);

        std::uint32_t w2{ hi & 0xffff'ffffull }, w3{ hi >> 32 };
        carry = _add_carry(w2, 0, carry);
        _add_carry(w3, 0, carry);  // notice: last carry can be ignored.

        this->hi = (std::uint64_t(w3) << 32) | w2;
        this->lo = (std::uint64_t(w1) << 32) | w0;
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator*= (const UInt128& other) noexcept
    {
        const std::uint64_t
            a0{ lo & 0xffff'ffffull },
            a1{ lo >> 32 },
            b0{ other.lo & 0xffff'ffffull },
            b1{ other.lo >> 32 },
            a0b0{ a0 * b0 },
            a1b0{ a1 * b0 + (a0b0 >> 32) },
            a0b1{ a0 * b1 + (a1b0 & 0xffff'ffffull) },
            a1b1{ a1 * b1 };

        const std::uint64_t
            hi{ a1b1 + (a1b0 >> 32) + (a0b1 >> 32) },
            lo{ (a0b1 << 32) + (a0b0 & 0xffff'ffffull) };

        this->hi = hi + (this->hi * other.lo) + (this->lo * other.hi);
        this->lo = lo;
        
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator*= (const std::uint64_t value) noexcept
    {
        const std::uint64_t
            a0{ lo & 0xffff'ffffull },
            a1{ lo >> 32 },
            b0{ value & 0xffff'ffffull },
            b1{ value >> 32 },
            a0b0{ a0 * b0 },
            a1b0{ a1 * b0 + (a0b0 >> 32) },
            a0b1{ a0 * b1 + (a1b0 & 0xffff'ffffull) },
            a1b1{ a1 * b1 };

        const std::uint64_t
            hi{ a1b1 + (a1b0 >> 32) + (a0b1 >> 32) },
            lo{ (a0b1 << 32) + (a0b0 & 0xffff'ffffull) };

        this->hi = hi + (this->hi * value);
        this->lo = lo;

        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator>>= (const unsigned int shift) noexcept
    {
        if (shift > 128) {
            hi = lo = 0ull;
        }
        else if (shift >= 64) {
            lo = hi >> (shift - 64);
            hi = 0ull;
        }
        else if (shift > 0) {
            const std::uint64_t hi_mask{ (1ull << shift) - 1 };
            lo = (lo >> shift) | ((hi & hi_mask) << (64 - shift));
            hi >>= shift;
        }

        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator<<= (const unsigned int shift) noexcept
    {
        if (shift > 128) {
            hi = lo = 0ull;
        }
        else if (shift >= 64) {
            hi = lo << (shift - 64);
            lo = 0ull;
        }
        else if (shift > 0) {
            hi = (hi << shift) | (lo >> (64 - shift));
            lo <<= shift;
        }

        return *this;
    }

}
