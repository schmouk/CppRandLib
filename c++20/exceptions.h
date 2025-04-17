#pragma once
/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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


//===========================================================================
#include <stdexcept>


//===========================================================================
/** @brief Exponential law null lambda exception. */
class AlphaBetaArgsException : public std::exception
{
public:
    const char* what() noexcept { return "both arguments alpha and beta must be greater than 0.0."; }
};

/** @brief Empty sequence exception. */
class ChoiceEmptySequenceException : public std::exception
{
public:
    const char* what() noexcept { return "cannot make a choice from an empty sequence."; }
};

/** @brief Exponential law null lambda exception. */
class ExponentialZeroLambdaException : public std::exception
{
public:
    const char* what() noexcept { return "lambda value cannot be 0.0 (currently is)."; }
};

/** @brief Exponential law null lambda exception. */
class GaussSigmaException : public std::exception
{
public:
    const char* what() noexcept { return "value for argument sigma must be greater than 0.0."; }
};

/** @brief Not same sizes of containers exception. */
class ParetoArgsValueException : public std::exception
{
public:
    const char* what() noexcept { return "shape argument 'alpha' must not be 0.0."; }
};

/** @brief Not a positive value exception. */
class PositiveValueException : public std::exception
{
public:
    const char* what() noexcept { return "argument value must not be negative."; }
};

/** @brief Probability value out of range exception. */
class ProbaOutOfRangeException : public std::exception
{
public:
    const char* what() noexcept { return "probabilitiy values must range in [0.0, 1.0]."; }
};

/** @brief Range arguments with same value exception. */
class RangeSameValuesException : public std::exception
{
public:
    const char* what() noexcept { return "'start' and 'stop' arguments must be different."; }
};

/** @brief Range arguments with same value exception. */
class RangeZeroStepException : public std::exception
{
public:
    const char* what() noexcept { return "'step' argument cannot be 0."; }
};

/** @brief Range arguments with same value exception. */
class SampleCountException : public std::exception
{
public:
    const char* what() noexcept { return "cannot sample a number of items that is greater than the overall population."; }
};

/** @brief Range arguments with same value exception. */
class SampleSizesException : public std::exception
{
public:
    const char* what() noexcept { return "sizes of arguments 'population' and 'counts' must be the same."; }
};

/** @brief Weibull law arguments exception. */
class WeibullArgsValueException : public std::exception
{
public:
    const char* what() noexcept { return "shape argument 'beta' must not be 0.0."; }
};

/** @brief Not a positive value exception. */
class ZeroLengthException : public std::exception
{
public:
    const char* what() noexcept { return "argument length must not be zero."; }
};
