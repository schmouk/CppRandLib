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
#include <array>
#include <vector>


//===========================================================================
namespace utils
{
    /** \defgroup type_traits CppRandLib specific traits utilities
     *
     * Defines traits utilities that are internally used in CppRandLib.
     *
     *  @{
     */

    //-----------------------------------------------------------------------
    /** \brief The default container-trait class. Always states the a template type is NOT a container. */
    template<typename ContainerType>
    class is_indexable
    {
    public:
        static const bool value{ false };
    };

    template<typename ContainerType>
    static constexpr bool is_indexable_v{ is_indexable<ContainerType>::value };


    //-----------------------------------------------------------------------
    /** \brief Specialization of class is_indexable<> for std::vectors. States that std::vectors are of container type. */
    template<typename T>
    class is_indexable<std::vector<T>>
    {
    public:
        static const bool value{ true };
    };

    //-----------------------------------------------------------------------
    /** \brief Specialization of class is_indexable<> for std::arrays. States that std::arrays are of container type. */
    template<typename T, const std::size_t n>
    class is_indexable<std::array<T, n>>
    {
    public:
        static const bool value{ true };
    };

    /** @} */
}

/** @} */
