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
#include "splitmix.h"


//===========================================================================
namespace utils
{
    //-----------------------------------------------------------------------
    const std::uint64_t splitmix_64(std::uint64_t value) noexcept
    {
        // this is the 'Golden' Gamma value : std::uint64_t( ((1.0 + math.sqrt(5)) / 2.0) * 1<<64 )
        constexpr std::uint64_t GOLDEN_GAMMA{ 0x9e37'79b9'7f4a'7c15 };

        value *= GOLDEN_GAMMA;
        value ^= (value ^ (value >> 30)) * 0xbf58'476d'1ce4'e5b9;
        value ^= (value ^ (value >> 27)) * 0x94d0'49bb'1331'11eb;
        return value ^ (value >> 31);
    }

}
