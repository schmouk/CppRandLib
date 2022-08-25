#include <chrono>

#include "fastrand32.h"


/** Sets the internal state of this PRNG from current time (empty signature). */
void FastRand32::setstate() noexcept
{
    const uint64_t ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    const uint32_t t32 = uint32_t(ticks & 0xffff'ffff);
    MyBaseClass::setstate(((t32 & 0xff00'0000) >> 24) +
                          ((t32 & 0x00ff'0000) >> 8) +
                          ((t32 & 0x0000'ff00) << 8) +
                          ((t32 & 0x0000'00ff) << 24));
}
