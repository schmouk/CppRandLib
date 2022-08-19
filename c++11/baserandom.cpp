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
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <stdio.h>

#include "baserandom.h"


//===========================================================================
/** Beta distribution. */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::betavariate(const double alpha, const double beta)
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


/** Exponential distribution. */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::expovariate(const double lambda)
{
    if (lambda == 0.0)
        throw std::invalid_argument("lambda value cannot be 0.0 (currently is)");
    
    return -std::log(1.0 - uniform());
}


/** Gamma distribution. */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::gammavariate(const double alpha, const double beta)
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

    if (alpha > 1.0) {
        // Uses R.C.H.Cheng paper
        // "The generation of Gamma variables with non - integral shape parameters",
        // Applied Statistics, (1977), 26, No. 1, p71 - 74
        constexpr double EPSILON{ 1e-7 };
        const double     INV_A{ std::sqrt(2.0 * alpha - 1.0) };
        const double     B{ alpha - LOG4 };
        const double     C{ alpha + INV_A };

        while (true) {
            const double u1{ uniform() };
            if (EPSILON < u1 && u1 < 1.0 - EPSILON) {
                const double u2{ 1.0 - uniform() };
                const double v{ std::log(u1 / (1.0 - u1)) / INV_A };
                const double x{ alpha - std::exp(v) };
                const double z{ u1 * u1 * u2 };
                const double r{ B + C * v - x };
                if (r + SG_MAGICCONST - 4.5 * z >= 0.0 || r >= std::log(z))
                    // this will eventually happen
                    return x * beta;
            }
        }
    }
    else if (alpha == 1.0) {
        // this is exponential distribution with lambda = 1 / beta
        return -std::log(1.0 - uniform()) * beta;
    }
    else {
        // alpha is between 0 and 1 (exclusive)
        // so, uses ALGORITHM GS of Statistical Computing - Kennedy & Gentle
        double x, u;
        while (true) {
            u = uniform();
            const double b{ (E + alpha) / E };
            const double p{ b * u };
            x = p <= 1.0 ? std::pow(p, 1.0 / alpha) : -std::log((b - p) / alpha);
            u = uniform();
            if (p <= 1.0) {
                if (u <= std::exp(-x))
                    break;
            }
            else if (u <= std::pow(x, alpha - 1.0))
                break;
        }
        return x * beta;
    }
}


/** Gaussian distribution (mean=mu, stdev=sigma). */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::gauss(const double mu, const double sigma)
{
    if (sigma <= 0.0)
        throw std::invalid_argument("value for argument sigma must be greater than 0.0, current value is not");

    double z = _gauss_next;
    _gauss_next = GAUSS_NULL;
    if (z == GAUSS_NULL) {
        const double u{ uniform(TWO_PI) };
        const double g{ std::sqrt(-2.0 * std::log(1.0 - uniform())) };
        z = std::cos(u) * g;
        _gauss_next = std::sin(u) * g;
    }

    return mu + z * sigma;
}


/** Pareto distribution. */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::paretorvariate(const double alpha)
{
    if (alpha <= 0.0)
        throw std::invalid_argument("shape argument alpha must not be 0.0, current value is.");

    // Jain, pg. 495
    return std::pow(1.0 - uniform(), -1.0 / alpha);
}

