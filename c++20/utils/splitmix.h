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

#include "seed_generation.h"


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
    class SplitMix64
    {
    public:
        /** @brief Empty constructor, uses the shuffled current time to initialize the internal state. */
        inline SplitMix64()  noexcept
            : _state(utils::set_random_seed64())
        {
        }

        /** @brief Valued constructor - integer. */
        inline SplitMix64(const std::uint64_t seed) noexcept
            : _state(seed)
        {
        }

        /** @brief Valued constructor - double. */
        inline SplitMix64(const double seed) noexcept
            : _state((seed <= 0.0) ? 0ull : (seed >= 1.0) ? 0xffff'ffff'ffff'ffffull : std::uint64_t(0xffff'ffff'ffff'ffffull * seed))
        {
        }

        /** @brief Evaluates next pseudorandom value. */
        const std::uint64_t operator() () noexcept;

    private:
        std::uint64_t _state;

    };


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
    class SplitMix63 : public SplitMix64
    {
    public:
        /** @brief Empty constructor, uses the shuffled current time to initialize the internal state. */
        inline SplitMix63()  noexcept
            : SplitMix64()
        {
        }

        /** @brief Valued constructor - integer. */
        inline SplitMix63(const std::uint64_t seed) noexcept
            : SplitMix64(seed)
        {
        }

        /** @brief Valued constructor - double. */
        inline SplitMix63(const double seed) noexcept
            : SplitMix64(seed)
        {
        }

        /** @brief Evaluates next pseudorandom value. */
        const std::uint64_t operator() () noexcept
        {
            return SplitMix64::operator()() >> 1;
        }

    };



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
    class SplitMix32 : public SplitMix64
    {
    public:
        /** @brief Empty constructor, uses the shuffled current time to initialize the internal state. */
        inline SplitMix32()  noexcept
            : SplitMix64()
        {
        }

        /** @brief Valued constructor - integer. */
        inline SplitMix32(const std::uint64_t seed) noexcept
            : SplitMix64(seed)
        {
        }

        /** @brief Valued constructor - double. */
        inline SplitMix32(const double seed) noexcept
            : SplitMix64(seed)
        {
        }

        /** @brief Evaluates next pseudorandom value. */
        const std::uint32_t operator() () noexcept
        {
            return SplitMix64::operator()() >> 32;
        }

    };



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
    class SplitMix31 : public SplitMix64
    {
    public:
        /** @brief Empty constructor, uses the shuffled current time to initialize the internal state. */
        inline SplitMix31()  noexcept
            : SplitMix64()
        {
        }

        /** @brief Valued constructor - integer. */
        inline SplitMix31(const std::uint64_t seed) noexcept
            : SplitMix64(seed)
        {
        }

        /** @brief Valued constructor - double. */
        inline SplitMix31(const double seed) noexcept
            : SplitMix64(seed)
        {
        }

        /** @brief Evaluates next pseudorandom value. */
        const std::uint32_t operator() () noexcept
        {
            return SplitMix64::operator()() >> 33;
        }

    };

}