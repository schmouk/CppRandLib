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

/** \addtogroup utils
 *  @{
 */

//===========================================================================
#include <cassert>
#include <type_traits>

#include "exceptions.h"


//===========================================================================
namespace utils
{
    /** \defgroup bits_rotations utils: Bits rotation utility on unsigned integers
    *
    * @{
    */

    //=======================================================================
    /** @brief Left bits rotation on unsigned integers.
    *
    * Evaluates left rotation to bits on the passed value. The rot_count left 
    * bits  are  finally inserted with same ordering at the right side of the
    * returned result. 
    */
    template<typename IntT>
    inline const IntT rot_left(const IntT value, const int rot_count, const int BITS_COUNT = 8 * sizeof(IntT))
    {
        static_assert(std::is_unsigned<IntT>::value, "left bits rotation are only applied on unsigned integer values.");

        if (rot_count < 0)
            throw NegativeRotationException(rot_count);
        if (rot_count > BITS_COUNT)
            throw TooBigRotationException<IntT>(rot_count);

        if (rot_count == 0 || rot_count == BITS_COUNT)
            return value;

        const IntT lo_mask{ IntT((IntT(1) << IntT(BITS_COUNT - rot_count)) - IntT(1)) };
        const IntT hi_mask{ IntT(IntT(-1) ^ lo_mask) };

        return ((value & lo_mask) << rot_count) | ((value & hi_mask) >> (BITS_COUNT - rot_count));
    }

    /** @} */
}

/** @} */
