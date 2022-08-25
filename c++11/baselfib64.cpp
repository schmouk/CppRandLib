/*
MIT License
Copyright (c) 2022 Philippe Schmouker, ph.schmouker (at) gmail.com
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
#include <chrono>

#include "baselfib64.h"
#include "fastrand63.h"


//===========================================================================
/** Sets the internal state of this PRNG from current time (empty signature). */
template<const size_t SIZE>
void BaseLFib64<SIZE>::setstate() noexcept
{
    const uint64_t ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    MyBaseClass::setstate(((ticks & 0x0000'0000'7fff'ffff) << 32) +
                          ((ticks & 0xff00'0000'0000'0000) >> 56) +
                          ((ticks & 0x00ff'0000'0000'0000) >> 40) +
                          ((ticks & 0x0000'ff00'0000'0000) >> 24) +
                          ((ticks & 0x0000'00ff'0000'0000) >> 8));
}


/** Sets the internal state of this PRNG with an integer seed. */
template<const size_t SIZE>
void BaseLFib64<SIZE>::setstate(const uint64_t seed) noexcept
{
    FastRand63 myRand(seed);
    for (auto it = MyBaseClass::_state.seed.begin(); it != MyBaseClass::_state.seed.end(); )
        *it++ = myRand(0x7fff'ffff'ffff'ffffULL) * 2 + myRand(2);
}


/** Sets the internal state of this PRNG with a double seed. */
template<const size_t SIZE>
void BaseLFib64<SIZE>::setstate(const double seed) noexcept
{
    setstate(uint64_t(seed * double(0xffff'ffff'ffff'ffffUL)));
}



/** /
*
#=============================================================================
from .baserandom import BaseRandom
from .fastrand32 import FastRand32
from .types      import SeedStateType, StateType


#=============================================================================
class BaseLFib64( BaseRandom ):


    #------------------------------------------------------------------------=
    def _initIndex(self, _index: int) -> None:
        """Inits the internal index pointing to the internal list.
        """
        try:
            self._index = int( _index ) % self._LIST_SIZE
        except:
            self._index = 0


    #------------------------------------------------------------------------=
    def _initList(self, _initialSeed: StateType = None) -> None:
        """Inits the internal list of values.

        Inits the internal list of values according to some initial
        seed  that  has  to be an integer or a float ranging within
        [0.0, 1.0).  Should it be None or anything  else  then  the
        current local time value is used as initial seed value.
        """
        myRand = FastRand32( _initialSeed )
        self._list = [ (int(myRand(0x1_0000_0000)) << 32) + int(myRand(0x1_0000_0000)) for _ in range(self._LIST_SIZE) ]
/**/