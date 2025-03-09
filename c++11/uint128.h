#pragma once
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
#include <cstdint>


namespace utils
{
    //===========================================================================
    /** @brief 128 bits integer minimalist arithmetic.
    *
    *   Visual Studio provides no 128-bits integer arithmetic. Some of the
    *   implemented  PRNGs in CppRandLib use this type of arithmetic.  So,
    *   this class implements a minimalist version of 128-bits arithmetic:
    *   addition, multiplication and xor operators.
    */
    class UInt128
    {
    public:

        //---   Constructors / Destructor   -------------------------------------
        inline UInt128() noexcept = default;                    //!< Default empty constructor
        inline UInt128(const UInt128&) noexcept = default;      //!< Default copy constructor
        inline UInt128(UInt128&&) noexcept = default;           //!< Default move constructor
        inline virtual ~UInt128() noexcept = default;           //!< Default destructor

        inline UInt128(const std::uint64_t hi, const std::uint64_t lo)
            : _data{ hi, lo }
        {}

        inline UInt128(const std::uint64_t val)
            : _data{ 0, val }
        {}

        inline UInt128& operator=(const UInt128&) noexcept = default;   //!< Default copy assignment
        inline UInt128& operator=(UInt128&&) noexcept = default;        //!< Default move assignment


        //---   Add   -----------------------------------------------------------
        UInt128& operator+= (const UInt128& other) noexcept;
        UInt128& operator+= (const std::uint64_t other) noexcept;
        UInt128& operator+= (const std::uint32_t other) noexcept;

        inline const UInt128 operator+ (const UInt128& other) const noexcept
        {
            UInt128 t{ *this };
            return t += other;
        }

        inline const UInt128 operator+ (const std::uint64_t other) const noexcept
        {
            UInt128 t{ *this };
            return t += other;
        }

        inline const UInt128 operator+ (const std::uint32_t other) const noexcept
        {
            UInt128 t{ *this };
            return t += other;
        }

        inline friend const UInt128 operator+ (const std::uint64_t lhs, const UInt128& rhs)
        {
            return rhs + lhs;  // notice: addition is commutative
        }

        inline friend const UInt128 operator+ (const std::uint32_t lhs, const UInt128& rhs)
        {
            return rhs + lhs;  // notice: addition is commutative
        }


        //---   Mul   -----------------------------------------------------------
        UInt128& operator*= (const UInt128& other) noexcept;
        UInt128& operator*= (const std::uint64_t other) noexcept;
        UInt128& operator*= (const std::uint32_t other) noexcept;

        inline const UInt128 operator* (const UInt128& other) const noexcept
        {
            UInt128 t{ *this };
            return t *= other;
        }

        inline const UInt128 operator* (const std::uint64_t other) const noexcept
        {
            UInt128 t{ *this };
            return t *= other;
        }

        inline const UInt128 operator* (const std::uint32_t other) const noexcept
        {
            UInt128 t{ *this };
            return t *= other;
        }

        inline friend const UInt128 operator* (const std::uint64_t lhs, const UInt128& rhs)
        {
            return rhs * lhs;  // notice: multiplication is commutative
        }

        inline friend const UInt128 operator* (const std::uint32_t lhs, const UInt128& rhs)
        {
            return rhs * lhs;  // notice: multiplication is commutative
        }


        //---   Xor   -----------------------------------------------------------
        inline UInt128& operator^= (const UInt128& other) noexcept
        {
            _data.i64.hi ^= other._data.i64.hi;
            _data.i64.lo ^= other._data.i64.lo;
            return *this;
        }

        inline UInt128& operator^= (const std::uint64_t other) noexcept
        {
            _data.i64.lo ^= other;
            return *this;
        }

        inline UInt128& operator^= (const std::uint32_t other) noexcept
        {
            _data.i64.lo ^= std::uint64_t(other);
            return *this;
        }

        inline const UInt128 operator^ (const UInt128& other) const noexcept
        {
            UInt128 t{ *this };
            return t ^= other;
        }

        inline const UInt128 operator^ (const std::uint64_t other) const noexcept
        {
            UInt128 t{ *this };
            return t ^= other;
        }

        inline const UInt128 operator^ (const std::uint32_t other) const noexcept
        {
            UInt128 t{ *this };
            return t ^= other;
        }

        inline friend const UInt128 operator^ (const std::uint64_t lhs, const UInt128& rhs)
        {
            return rhs ^ lhs;  // notice: xor operator is commutative
        }

        inline friend const UInt128 operator^ (const std::uint32_t lhs, const UInt128& rhs)
        {
            return rhs ^ lhs;  // notice: xor operator is commutative
        }


    private:

        //---   internal data representation   ----------------------------------
        union {
            struct i64t {
                std::uint64_t hi{ 0 };
                std::uint64_t lo{ 0 };
            } i64;

            struct i32t {
                std::uint32_t w3;
                std::uint32_t w2;
                std::uint32_t w1;
                std::uint32_t w0;
            } i32;
        } _data;


        //---   internal operations   -------------------------------------------
        inline bool _add_carry(std::uint32_t& w, const std::uint32_t a, const bool carry = false)
        {
            std::uint64_t t{ w };
            t += std::int64_t(a) + carry;
            w = t & 0xffff'ffff;
            return t & 1'0000'0000;
        }

    };

}
