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


//===========================================================================
namespace utils
{
    //===========================================================================
    /** @brief The splitting and mixing algorithm used to initialize 64-bits internal states of PRNGs.
    * 
    * This method is used to split and mix bits of  64-bits  integers.  It  is
    * internally  used  in  CppRandLib  to initialize internal state of PRNGs. 
    * It implements the 64-bits version of the  Fast  Splittable  Pseudorandom 
    * Number Generators proposed by Steele Jr, Guy L., Doug Lea, and Christine
    * H. Flood in "Fast splittable pseudorandom number  generators.",  in  ACM 
    * SIGPLAN Notices 49.10 (2014): pp. 453-472.
    *
    * It uses the Gamma method inited by Sebastiano Vigna  (vigna@acm.org)  in
    * 2015, provided under the Creative Commons license and modified under the
    * same license by D. Lemire by Aug. 2017.
    * (see https://github.com/lemire/testingRNG/blob/master/source/splitmix64.h).
    *
    * It SHOULD NOT BE USED as a generic PRNG due to is randomness big limitations.
    */
    const std::uint64_t splitmix_64(const std::uint64_t value) noexcept;
    

    //===========================================================================
    /** @brief The splitting and mixing algorithm used to initialize 63-bits internal states of PRNGs.
    *
    * This method is used to split and mix bits of  64-bits  integers.  It  is
    * internally  used  in  CppRandLib  to initialize internal state of PRNGs.
    * It implements the 64-bits version of the  Fast  Splittable  Pseudorandom
    * Number Generators proposed by Steele Jr, Guy L., Doug Lea, and Christine
    * H. Flood in "Fast splittable pseudorandom number  generators.",  in  ACM
    * SIGPLAN Notices 49.10 (2014): pp. 453-472.
    *
    * It uses the Gamma method inited by Sebastiano Vigna  (vigna@acm.org)  in
    * 2015, provided under the Creative Commons license and modified under the
    * same license by D. Lemire by Aug. 2017.
    * (see https://github.com/lemire/testingRNG/blob/master/source/splitmix64.h).
    *
    * It SHOULD NOT BE USED as a generic PRNG due to is randomness big limitations.
    */
    inline const std::uint64_t splitmix_63(const std::uint64_t value) noexcept
    {
        return splitmix_64(value) >> 1;
    }


    //===========================================================================
    /** @brief The splitting and mixing algorithm used to initialize 32-bits internal states of PRNGs.
    *
    * This method is used to split and mix bits of  64-bits  integers.  It  is
    * internally  used  in  CppRandLib  to initialize internal state of PRNGs.
    * It implements the 64-bits version of the  Fast  Splittable  Pseudorandom
    * Number Generators proposed by Steele Jr, Guy L., Doug Lea, and Christine
    * H. Flood in "Fast splittable pseudorandom number  generators.",  in  ACM
    * SIGPLAN Notices 49.10 (2014): pp. 453-472.
    *
    * It uses the Gamma method inited by Sebastiano Vigna  (vigna@acm.org)  in
    * 2015, provided under the Creative Commons license and modified under the
    * same license by D. Lemire by Aug. 2017.
    * (see https://github.com/lemire/testingRNG/blob/master/source/splitmix64.h).
    *
    * It SHOULD NOT BE USED as a generic PRNG due to is randomness big limitations.
    */
    inline const std::uint64_t splitmix_32(const std::uint64_t value) noexcept
    {
        return splitmix_64(value) >> 32;
    }


    //===========================================================================
    /** @brief The splitting and mixing algorithm used to initialize 31-bits internal states of PRNGs.
    *
    * This method is used to split and mix bits of  64-bits  integers.  It  is
    * internally  used  in  CppRandLib  to initialize internal state of PRNGs.
    * It implements the 64-bits version of the  Fast  Splittable  Pseudorandom
    * Number Generators proposed by Steele Jr, Guy L., Doug Lea, and Christine
    * H. Flood in "Fast splittable pseudorandom number  generators.",  in  ACM
    * SIGPLAN Notices 49.10 (2014): pp. 453-472.
    *
    * It uses the Gamma method inited by Sebastiano Vigna  (vigna@acm.org)  in
    * 2015, provided under the Creative Commons license and modified under the
    * same license by D. Lemire by Aug. 2017.
    * (see https://github.com/lemire/testingRNG/blob/master/source/splitmix64.h).
    *
    * It SHOULD NOT BE USED as a generic PRNG due to is randomness big limitations.
    */
    inline const std::uint64_t splitmix_31(const std::uint64_t value) noexcept
    {
        return splitmix_64(value) >> 33;
    }

}