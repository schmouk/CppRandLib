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
#include <string>


//===========================================================================
/** @brief The base class for CppRandLib specific exceptions. */
template<typename T = double, typename S = T>
struct BaseException : public std::exception
{
    inline BaseException() noexcept = default;
    inline virtual ~BaseException() noexcept = default;

    inline BaseException(const T value) noexcept
        : std::exception()
        , _inited(true)
        , _value(value)
    {
    }

    inline BaseException(const T value, const T value2) noexcept
        : std::exception()
        , _inited(true)
        , _value(value)
        , _value2(value2)
    {
    }

    inline BaseException(const T value, const T value2, const S value3) noexcept
        : std::exception()
        , _inited(true)
        , _value(value)
        , _value2(value2)
        , _value3(value3)
    {
    }


    std::string _msg{};
    T _value{};
    T _value2{};
    S _value3{};
    bool _inited{ false };
};


//===========================================================================
//---------------------------------------------------------------------------
/** @brief Negative values for alpha or beta arguments of Betavariate function exception. */
struct AlphaBetaArgsException : public BaseException<double>
{
    inline AlphaBetaArgsException() noexcept = default;
    inline virtual ~AlphaBetaArgsException() noexcept = default;

    inline AlphaBetaArgsException(const double alpha, const double beta)
        : BaseException<double>(alpha, beta)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "both arguments alpha (";
            _msg += std::to_string(_value);
            _msg += ") and beta (";
            _msg += std::to_string(_value2);
            _msg += ") must be greater than 0.0.";
            return _msg.c_str();
        }
        else {
            return "both arguments alpha and beta must be greater than 0.0.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Empty sequence exception. */
class ChoiceEmptySequenceException : public std::exception
{
public:
    const char* what() noexcept { return "cannot make a choice from an empty sequence."; }
};


//---------------------------------------------------------------------------
/** @brief Exponential law null lambda exception. */
class ExponentialZeroLambdaException : public std::exception
{
public:
    const char* what() noexcept { return "lambda value cannot be 0.0 (currently is)."; }
};


//---------------------------------------------------------------------------
/** @brief Float value is out of range [0.0, 1.0) exception. */
struct FloatValueRange01Exception : public BaseException<double>
{
    inline FloatValueRange01Exception() noexcept = default;
    inline virtual ~FloatValueRange01Exception() noexcept = default;

    inline FloatValueRange01Exception(const double value)
        : BaseException<double>(value)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "Float value (";
            _msg += std::to_string(_value);
            _msg += ") is out of range [0.0, 1.0).";
            return _msg.c_str();
        }
        else {
            return "Float value is out of range [0.0, 1.0).";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Exponential law null lambda exception. */
struct GaussSigmaException : public BaseException<double>
{
    inline GaussSigmaException() noexcept = default;
    inline virtual ~GaussSigmaException() noexcept = default;

    inline GaussSigmaException(const double sigma)
        : BaseException<double>(sigma)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "value for argument sigma (";
            _msg += std::to_string(_value);
            _msg += ") must be greater than 0.0.";
            return _msg.c_str();
        }
        else {
            return "value for argument sigma must be greater than 0.0.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Negative value for kappa parameter of Vvonmises law exception. */
struct NegativeKappaException : public BaseException<double>
{
    inline NegativeKappaException() noexcept = default;
    inline virtual ~NegativeKappaException() noexcept = default;

    inline NegativeKappaException(const double kappa)
        : BaseException<double>(kappa)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "'kappa' parameter (";
            _msg += std::to_string(_value);
            _msg += ") cannot be negative.";
            return _msg.c_str();
        }
        else {
            return "'kappa' parameter cannot be negative.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Negative value for rotation bits count exception. */
struct NegativeRotationException : public BaseException<int>
{
    inline NegativeRotationException() noexcept = default;
    inline virtual ~NegativeRotationException() noexcept = default;

    inline NegativeRotationException(const int rot_count)
        : BaseException<int>(rot_count)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "rotation bits count (";
            _msg += std::to_string(_value);
            _msg += ") cannot be negative.";
            return _msg.c_str();
        }
        else {
            return "rotation bits count cannot be negative.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Negative value for sigma paramater of Gauss law exception. */
struct NormalSigmaException : public GaussSigmaException
{
    inline NormalSigmaException() noexcept = default;
    inline virtual ~NormalSigmaException() noexcept = default;

    inline NormalSigmaException(const double sigma)
        : GaussSigmaException(sigma)
    {}
};


//---------------------------------------------------------------------------
/** @brief Not same sizes of containers exception. */
class ParetoArgsValueException : public std::exception
{
public:
    const char* what() noexcept { return "shape argument 'alpha' must not be 0.0 (actually is)."; }
};


//---------------------------------------------------------------------------
/** @brief Not a positive value exception. */
struct PositiveValueException : public BaseException<long long>
{
    inline PositiveValueException() noexcept = default;
    inline virtual ~PositiveValueException() noexcept = default;

    inline PositiveValueException(const long long value)
        : BaseException<long long>(value)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "argument value (";
            _msg += std::to_string(_value);
            _msg += ") must not be negative.";
            return _msg.c_str();
        }
        else {
            return "argument value must not be negative (actually is).";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Probability value out of range exception. */
struct ProbaOutOfRangeException : public BaseException<double>
{
    inline ProbaOutOfRangeException() noexcept = default;
    inline virtual ~ProbaOutOfRangeException() noexcept = default;

    inline ProbaOutOfRangeException(const double proba)
        : BaseException<double>(proba)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "probabilitiy values must range in [0.0, 1.0] (actually is ";
            _msg += std::to_string(_value);
            _msg += ").";
            return _msg.c_str();
        }
        else {
            return "probabilitiy values must range in [0.0, 1.0].";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Range arguments with incoherent values exception. */
template<typename T = long long, typename S = T>
struct RangeIncoherentValuesException : public BaseException<T, S>
{
    inline RangeIncoherentValuesException() noexcept
        : BaseException<T, S>()
    {}

    inline virtual ~RangeIncoherentValuesException() noexcept = default;

    inline RangeIncoherentValuesException(const T start, const T stop, const S step)
        : BaseException<T, S>(start, stop, step)
    {}

    const char* what() noexcept
    {
        if (BaseException<T, S>::_inited) {
            BaseException<T, S>::_msg = "'stop' value (";
            BaseException<T, S>::_msg += std::to_string(BaseException<T, S>::_value2);
            BaseException<T, S>::_msg += ") will never be reached associated with 'start' (";
            BaseException<T, S>::_msg += std::to_string(BaseException<T, S>::_value);
            BaseException<T, S>::_msg += ") and 'step' (";
            BaseException<T, S>::_msg += std::to_string(BaseException<T, S>::_value3);
            BaseException<T, S>::_msg += ") arguments.";
            return BaseException<T, S>::_msg.c_str();
        }
        else {
            return "'stop' value will never be reached associated with 'start' and 'step' arguments.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Range arguments with same value exception. */
template<typename T = long long>
struct RangeSameValuesException : public BaseException<T>
{
    inline RangeSameValuesException() noexcept = default;
    inline virtual ~RangeSameValuesException() noexcept = default;

    inline RangeSameValuesException(const T start, const T stop)
        : BaseException<T>(start, stop)
    {}

    const char* what() noexcept
    {
        if (BaseException<T>::_inited) {
            BaseException<T>::_msg = "'start' (";
            BaseException<T>::_msg += std::to_string(BaseException<T>::_value);
            BaseException<T>::_msg += ") and 'stop' (";
            BaseException<T>::_msg += std::to_string(BaseException<T>::_value2);
            BaseException<T>::_msg += ") arguments must be different.";
            return BaseException<T>::_msg.c_str();
        }
        else {
            return "'start' and 'stop' arguments must be different.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Zero step argument in range exception. */
class RangeZeroStepException : public std::exception
{
public:
    const char* what() noexcept { return "'step' argument cannot be 0 (actually is)."; }
};


//---------------------------------------------------------------------------
/** @brief Range arguments with same value exception. */
struct SampleCountException : public BaseException<std::size_t>
{
    inline SampleCountException() noexcept = default;
    inline virtual ~SampleCountException() noexcept = default;

    inline SampleCountException(const std::size_t sample_size, const std::size_t population_size)
        : BaseException<std::size_t>(sample_size, population_size)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "cannot sample a number of items (";
            _msg += std::to_string(_value);
            _msg += ") that is greater than the overall population (";
            _msg += std::to_string(_value2);
            _msg += ").";
            return _msg.c_str();
        }
        else {
            return "cannot sample a number of items that is greater than the overall population.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Range arguments with same value exception. */
struct SampleSizesException : public BaseException<std::size_t>
{
    inline SampleSizesException() noexcept = default;
    inline virtual ~SampleSizesException() noexcept = default;

    inline SampleSizesException(const std::size_t population_size, const std::size_t count_size)
        : BaseException<std::size_t>(population_size, count_size)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "sizes of arguments 'population' (";
            _msg += std::to_string(_value);
            _msg += ") and 'counts' (";
            _msg += std::to_string(_value2);
            _msg += ") must be the same.";
            return _msg.c_str();
        }
        else {
            return "sizes of arguments 'population' and 'counts' must be the same.";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Step value type exception. */
struct StepValueTypeException : public std::exception
{
    const char* what() noexcept { return "Type of 'step' values must be arithmetic."; }
};


//---------------------------------------------------------------------------
/** @brief Too big value for rotation bits count exception. */
template<typename IntT = unsigned long long>
struct TooBigRotationException : public BaseException<int>
{
    inline TooBigRotationException() noexcept = default;
    inline virtual ~TooBigRotationException() noexcept = default;

    inline TooBigRotationException(const int rot_count)
        : BaseException<int>(rot_count)
    {}

    const char* what() noexcept
    {
        if (_inited) {
            _msg = "rotation bits count (";
            _msg += std::to_string(_value);
            _msg += ") is too big (must not exceed the rotated integer size: ";
            _msg += std::to_string(8 * sizeof(IntT));
            _msg += ").";
            return _msg.c_str();
        }
        else {
            return "rotation bits count is too big (must not exceed the rotated integer size).";
        }
    }
};


//---------------------------------------------------------------------------
/** @brief Weibull law arguments exception. */
class WeibullArgsValueException : public std::exception
{
public:
    const char* what() noexcept { return "shape argument 'beta' must not be 0.0 (actually is)."; }
};


//---------------------------------------------------------------------------
/** @brief Not a positive value exception. */
class ZeroLengthException : public std::exception
{
public:
    const char* what() noexcept { return "length or count argument value must not be zero (actually is)."; }
};


//---------------------------------------------------------------------------
/** @brief Not a positive value exception. */
struct ZeroValueException : public std::exception
{
    const char* what() noexcept { return "argument value must not be zero (actually is)."; }
};
