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
#include <cstring>
#include <format>
#include <stdexcept>
#include <stdio.h>

#include "baserandom.h"


//===========================================================================
/** Beta distribution. */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::betavariate(const double alpha, const double beta) const
{
    constexpr char* fmt = "%s value must be greater than 0.0 (currently is %g)";
    constexpr int MAX_SIZE = 80;
    char err_msg[MAX_SIZE];

    if (alpha <= 0.0) {
        snprintf(err_msg, MAX_SIZE, fmt, "alpha", alpha);
        throw std::invalid_argument(err_msg);
    }

    if (beta <= 0.0) {
        std::snprintf(err_msg, MAX_SIZE, fmt, "beta", beta);
        throw std::invalid_argument(err_msg);
    }

    const double y = gammavariate(alpha, 1.0);
    return (y == 0.0) ? 0.0 : (y / y + gammavariate(beta, 1.0));
}

