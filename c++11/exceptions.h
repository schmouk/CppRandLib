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
struct AlphaBetaArgsException : public std::exception
{
    const char* what() noexcept { return "both arguments alpha and beta must be greater than 0.0."; }
};

/** @brief Wrong argument type - not arithmetic. */
struct ArithmeticValueTypeException : public std::exception
{
    const char* what() noexcept { return "Argument(s) must be an arithmetic type."; }
};

/** @brief Empty sequence exception. */
struct ChoiceEmptySequenceException : public std::exception
{
    const char* what() noexcept { return "cannot make a choice from an empty sequence."; }
};

/** @brief Exponential law null lambda exception. */
struct ExponentialZeroLambdaException : public std::exception
{
    const char* what() noexcept { return "lambda value cannot be 0.0 (currently is)."; }
};

/** @brief Wrong argument type - not floating point. */
struct FloatingPointTypeException : public std::exception
{
    const char* what() noexcept { return "Argument(s) must be a floating pointg type."; }
};

/** @brief Negative value for sigma paramater of Gauss law exception. */
struct GaussSigmaException : public std::exception
{
    const char* what() noexcept { return "value for argument sigma must be greater than 0.0."; }
};

/** @brief Wrong argument type - not integral. */
struct IndexableContainerException : public std::exception
{
    const char* what() noexcept { return "Container type must be std::array or std::vector."; }
};

/** @brief Wrong argument type - not integral exception. */
struct IntegralValueTypeException : public std::exception
{
    const char* what() noexcept { return "Argument(s) must be an integral type."; }
};

/** @brief Max value type exception. */
struct MaxValueTypeException : public std::exception
{
    const char* what() noexcept { return "Type of 'max' values must be arithmetic."; }
};

/** @brief Min value type exception. */
struct MinValueTypeException : public std::exception
{
    const char* what() noexcept { return "Type of 'min' values must be arithmetic."; }
};

/** @brief Not same sizes of containers exception. */
struct MinMaxSizesException : public std::exception
{
    const char* what() noexcept { return "'min' and 'max' container arguments must have same sizes."; }
};

/** @brief Negative value for kappa parameter exception. */
struct NegativeKappaException : public std::exception
{
    const char* what() noexcept { return "'kappa' parameter cannot be negative."; }
};

/** @brief Negative value for rotation bits count exception. */
struct NegativeRotationException : public std::exception
{
    const char* what() noexcept { return "rotation bits count cannot be negative."; }
};

/** @brief Negative value for sigma paramater of Gauss law exception. */
struct NormalSigmaException : public GaussSigmaException
{};

/** @brief Zero value for alpha parameter of Pareto law exception. */
struct ParetoArgsValueException : public std::exception
{
    const char* what() noexcept { return "shape argument 'alpha' must not be 0.0."; }
};

/** @brief Not a positive value exception. */
struct PositiveValueException : public std::exception
{
    const char* what() noexcept { return "argument value must not be negative."; }
};

/** @brief Probability value out of range exception. */
struct ProbaOutOfRangeException : public std::exception
{
    const char* what() noexcept { return "probabilitiy values must range in [0.0, 1.0]."; }
};

/** @brief Range arguments with incoherent values exception. */
struct RangeIncoherentValuesException : public std::exception
{
    const char* what() noexcept { return "'stop' value will never be reached associated with 'start' and 'step' arguments."; }
};

/** @brief Range arguments with same value exception. */
struct RangeSameValuesException : public std::exception
{
    const char* what() noexcept { return "'start' and 'stop' arguments must be different."; }
};

/** @brief Range arguments with same value exception. */
struct RangeZeroStepException : public std::exception
{
    const char* what() noexcept { return "'step' argument cannot be 0."; }
};

/** @brief Range arguments with same value exception. */
struct SampleCountException : public std::exception
{
    const char* what() { return "cannot sample a number of items that is greater than the overall population."; }
};

/** @brief Range arguments with same value exception. */
struct SampleCountsTypeException : public std::exception
{
    const char* what() noexcept { return "type of 'counts' values must be integral."; }
};

/** @brief Range arguments with same value exception. */
struct SampleSizesException : public std::exception
{
    const char* what() noexcept { return "sizes of arguments 'population' and 'counts' must be the same."; }
};

/** @brief Step value type exception. */
struct StepValueTypeException : public std::exception
{
    const char* what() noexcept { return "Type of 'step' values must be arithmetic."; }
};

/** @brief Too big value for rotation bits count exception. */
struct TooBigRotationException : public std::exception
{
    const char* what() noexcept { return "rotation bits count is too big (must not exceed the rotated integer size)."; }
};

/** @brief Empty sequence exception. */
struct ValueTypeException : public std::exception
{
    const char* what() noexcept { return "Type of values must be arithmetic."; }
};

/** @brief Weibull law arguments exception. */
struct WeibullArgsValueException : public std::exception
{
    const char* what() noexcept { return "shape argument 'beta' must not be 0.0."; }
};

/** @brief Not a positive value exception. */
struct ZeroLengthException : public std::exception
{
    const char* what() noexcept { return "argument length must not be zero."; }
};

/** @brief Not a positive value exception. */
struct ZeroValueException : public std::exception
{
    const char* what() noexcept { return "argument value must not be zero."; }
};
