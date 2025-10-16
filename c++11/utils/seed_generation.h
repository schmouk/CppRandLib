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
#include <cstdint>

#include "splitmix.h"
#include "time.h"


//===========================================================================
namespace utils
{
    //=======================================================================
    /** @brief Generates a 64-bits random seed for PRNGs, based on the current system time.
    * 
    * This method is used to generate an as much random seed as  possible
    * without using the STL method 'std::random_device' which is known to
    * not always use hardwara features to generate random numbers and for
    * which  no ensured way exist to check if such features are available
    * on all platforms and on all hardware.
    */
    inline const std::uint64_t set_random_seed64()
    {
        return SplitMix64(utils::get_time_us())();
    }


    //=======================================================================
    /** @brief Generates a 63-bits random seed for PRNGs, based on the current system time.
    *
    * This method is used to generate an as much random seed as  possible
    * without using the STL method 'std::random_device' which is known to
    * not always use hardwara features to generate random numbers and for
    * which  no ensured way exist to check if such features are available
    * on all platforms and on all hardware.
    */
    inline const std::uint64_t set_random_seed63()
    {
        return set_random_seed64() >> 1ull;  // & 0x7fff'ffff'ffff'ffffull;
    }


    //=======================================================================
    /** @brief Generates a 32-bits random seed for PRNGs, based on the current system time.
    *
    * This method is used to generate an as much random seed as  possible
    * without using the STL method 'std::random_device' which is known to
    * not always use hardwara features to generate random numbers and for
    * which  no ensured way exist to check if such features are available
    * on all platforms and on all hardware.
    */
    inline const std::uint32_t set_random_seed32()
    {
        return set_random_seed64() >> 32ull;  // & 0xffff'fffful;
    }


    //=======================================================================
    /** @brief Generates a 31-bits random seed for PRNGs, based on the current system time.
    *
    * This method is used to generate an as much random seed as  possible
    * without using the STL method 'std::random_device' which is known to
    * not always use hardwara features to generate random numbers and for
    * which  no ensured way exist to check if such features are available
    * on all platforms and on all hardware.
    */
    inline const std::uint32_t set_random_seed31()
    {
        return set_random_seed64() >> 33ull;  // & 0x7fff'fffful;
    }

}

/** @} */
