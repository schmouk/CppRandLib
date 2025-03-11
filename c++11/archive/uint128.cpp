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
#include "uint128.h"


//===========================================================================
namespace utils
{
    //---------------------------------------------------------------------------
    UInt128& UInt128::operator+= (const UInt128& other) noexcept
    {
        bool carry{ false };
        carry = _add_carry(data.i32.w0, other.data.i32.w0, false);
        carry = _add_carry(data.i32.w1, other.data.i32.w1, carry);
        carry = _add_carry(data.i32.w2, other.data.i32.w2, carry);
        _add_carry(data.i32.w3, other.data.i32.w3, carry);  // notice: last carry can be ignored.
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator+= (const std::uint64_t other) noexcept
    {
        bool carry{ false };
        carry = _add_carry(data.i32.w0, other & 0xffff'ffff, false);
        carry = _add_carry(data.i32.w1, other >> 32, carry);
        carry = _add_carry(data.i32.w2, 0, carry);
        _add_carry(data.i32.w3, 0, carry);  // notice: last carry can be ignored.
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator+= (const std::uint32_t other) noexcept
    {
        bool carry{ false };
        carry = _add_carry(data.i32.w0, other, false);
        carry = _add_carry(data.i32.w1, 0, carry);
        carry = _add_carry(data.i32.w2, 0, carry);
        _add_carry(data.i32.w3, 0, carry);  // notice: last carry can be ignored.
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator*= (const UInt128& other) noexcept
    {
        const std::uint64_t
            a0{ data.i32.w0 },
            a1{ data.i32.w1 },
            b0{ other.data.i32.w0 },
            b1{ other.data.i32.w1 },
            a0b0{ a0 * b0 },
            a1b0{ a1 * b0 + (a0b0 >> 32) },
            a0b1{ a0 * b1 + (a1b0 & 0xffff'ffff) },
            a1b1{ a1 * b1 };

        const std::uint64_t
            hi{ a1b1 + (a1b0 >> 32) + (a0b1 >> 32) },
            lo{ (a0b1 << 32) + (a0b0 & 0xffff'ffff) };

        this->data.i64.hi = hi + (this->data.i64.hi * other.data.i64.lo) + (this->data.i64.lo * other.data.i64.hi);
        this->data.i64.lo = lo;
        
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator*= (const std::uint64_t other) noexcept
    {
        //TODO: implement this
        return *this;
    }

    //---------------------------------------------------------------------------
    UInt128& UInt128::operator*= (const std::uint32_t other) noexcept
    {
        //TODO: implement this
        return *this;
    }

}
