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
    
    return -std::log(1.0 - random());
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
            const double u1{ random() };
            if (EPSILON < u1 && u1 < 1.0 - EPSILON) {
                const double u2{ 1.0 - random() };
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
        return -std::log(1.0 - random()) * beta;
    }
    else {
        // alpha is between 0 and 1 (exclusive)
        // so, uses ALGORITHM GS of Statistical Computing - Kennedy & Gentle
        double x, u;
        while (true) {
            u = random();
            const double b{ (E + alpha) / E };
            const double p{ b * u };
            x = p <= 1.0 ? std::pow(p, 1.0 / alpha) : -std::log((b - p) / alpha);
            u = random();
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

    double z = _state.gauss_next;
    _state.gauss_next = GAUSS_NULL;
    if (z == GAUSS_NULL) {
        const double u{ uniform(TWO_PI) };
        const double g{ std::sqrt(-2.0 * std::log(1.0 - random())) };
        z = std::cos(u) * g;
        _state.gauss_next = std::sin(u) * g;
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
    return std::pow(1.0 - random(), -1.0 / alpha);
}


/** Circular data distribution. */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::vonmisesvariate(const double mu, const double kappa)
{
    // Based upon an algorithm published in : Fisher, N.I.,
    // "Statistical Analysis of Circular Data", Cambridge University Press, 1993.
    //
    // Thanks to Magnus Kessler for a correction to the implementation of step 4.

    if (kappa <= 1e-6)
        return uniform(TWO_PI);

    const double s = 0.5 / kappa;
    const double r = s + std::sqrt(1.0 + s * s);
    double z;

    while (true) {
        z = std::cos(uniform(PI));
        const double d{ z / (r + z) };
        const double u{ random() };
        if (u < 1.0 - d * d || u < (1.0 - d) * std::exp(d))
            break;
    }

    const double q{ 1.0 / r };
    const double f{ (q + z) / (1.0 + q * z) };
    if (random() >= 0.5)
        return std::fmod(mu + std::acos(f), TWO_PI);
    else
        return std::fmod(mu - std::acos(f), TWO_PI);
}


/** Weibull distribution. */
template<typename SeedStateType>
const double BaseRandom<SeedStateType>::weibullvariate(const double alpha, const double beta)
{
    if (beta <= 0.0)
        throw std::invalid_argument("shape argument beta must not be 0.0, current value is.");

    return alpha * std::pow(-std::log(1.0 - random()), 1.0 / beta);
}
