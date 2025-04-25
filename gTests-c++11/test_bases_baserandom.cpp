/*
MIT License

Copyright (c) 2025 Philippe Schmouker, ph.schmouker (at) gmail.com

This file is part of library CppRandLib Google Tests.

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
#include <array>
#include <cmath>
#include <cstdint>
#include <list>
#include <map>
#include <vector>

#include "gtest/gtest.h"

#include "baseclasses/baserandom.h"
#include "exceptions.h"


//===========================================================================
namespace tests_bases
{
    // A default object class, for test purpose only
    struct Object
    {
        inline Object(const int x)
        {}

        Object() = default;
        Object(const Object&) = default;

        inline const bool operator== (const Object& rhs) { return true; }
        inline const bool operator== (const std::uint8_t rhs) const { return true; }
        inline const bool operator== (const std::uint16_t rhs) const { return true; }
        inline const bool operator== (const std::uint32_t rhs) const { return true; }
        inline const bool operator== (const int rhs) const { return true; }
        inline const bool operator== (const std::uint64_t rhs) const { return true; }
        inline const bool operator== (const float rhs) const { return true; }
        inline const bool operator== (const double rhs) const { return true; }
        inline const bool operator== (const long double rhs) const { return true; }

        inline const bool operator<= (const Object& rhs) { return true; }
        inline const bool operator<= (const std::uint8_t rhs) const { return true; }
        inline const bool operator<= (const std::uint16_t rhs) const { return true; }
        inline const bool operator<= (const std::uint32_t rhs) const { return true; }
        inline const bool operator<= (const int rhs) const { return true; }
        inline const bool operator<= (const std::uint64_t rhs) const { return true; }
        inline const bool operator<= (const float rhs) const { return true; }
        inline const bool operator<= (const double rhs) const { return true; }
        inline const bool operator<= (const long double rhs) const { return true; }

        inline const bool operator>= (const Object& rhs) { return true; }
        inline const bool operator>= (const std::uint8_t rhs) const { return true; }
        inline const bool operator>= (const std::uint16_t rhs) const { return true; }
        inline const bool operator>= (const std::uint32_t rhs) const { return true; }
        inline const bool operator>= (const int rhs) const { return true; }
        inline const bool operator>= (const std::uint64_t rhs) const { return true; }
        inline const bool operator>= (const float rhs) const { return true; }
        inline const bool operator>= (const double rhs) const { return true; }
        inline const bool operator>= (const long double rhs) const { return true; }

        inline const bool operator< (const Object& rhs) { return true; }
        inline const bool operator< (const std::uint8_t rhs) const { return true; }
        inline const bool operator< (const std::uint16_t rhs) const { return true; }
        inline const bool operator< (const std::uint32_t rhs) const { return true; }
        inline const bool operator< (const int rhs) const { return true; }
        inline const bool operator< (const std::uint64_t rhs) const { return true; }
        inline const bool operator< (const float rhs) const { return true; }
        inline const bool operator< (const double rhs) const { return true; }
        inline const bool operator< (const long double rhs) const { return true; }

        inline const bool operator> (const Object& rhs) { return true; }
        inline const bool operator> (const std::uint8_t rhs) const { return true; }
        inline const bool operator> (const std::uint16_t rhs) const { return true; }
        inline const bool operator> (const std::uint32_t rhs) const { return true; }
        inline const bool operator> (const int rhs) const { return true; }
        inline const bool operator> (const std::uint64_t rhs) const { return true; }
        inline const bool operator> (const float rhs) const { return true; }
        inline const bool operator> (const double rhs) const { return true; }
        inline const bool operator> (const long double rhs) const { return true; }

        inline const Object& operator+ (const Object& rhs) { return rhs; }
        inline const std::uint8_t operator+ (const std::uint8_t rhs) const { return rhs; }
        inline const std::uint16_t operator+ (const std::uint16_t rhs) const { return rhs; }
        inline const std::uint32_t operator+ (const std::uint32_t rhs) const { return rhs; }
        inline const int operator+ (const int rhs) const { return rhs; }
        inline const std::uint64_t operator+ (const std::uint64_t rhs) const { return rhs; }
        inline const float operator+ (const float rhs) const { return rhs; }
        inline const double operator+ (const double rhs) const { return rhs; }
        inline const long double operator+ (const long double rhs) const { return rhs; }

        inline const Object& operator- (const Object& rhs) { return rhs; }
        inline const std::uint8_t operator- (const std::uint8_t rhs) const { return rhs; }
        inline const std::uint16_t operator- (const std::uint16_t rhs) const { return rhs; }
        inline const std::uint32_t operator- (const std::uint32_t rhs) const { return rhs; }
        inline const int operator- (const int rhs) const { return rhs; }
        inline const std::uint64_t operator- (const std::uint64_t rhs) const { return rhs; }
        inline const float operator- (const float rhs) const { return rhs; }
        inline const double operator- (const double rhs) const { return rhs; }
        inline const long double operator- (const long double rhs) const { return rhs; }

        inline const Object& operator-() const { return *this; };

        inline const Object& operator* (const Object& rhs) { return rhs; }
        inline const std::uint8_t operator* (const std::uint8_t rhs) const { return rhs; }
        inline const std::uint16_t operator* (const std::uint16_t rhs) const { return rhs; }
        inline const std::uint32_t operator* (const std::uint32_t rhs) const { return rhs; }
        inline const int operator* (const int rhs) const { return rhs; }
        inline const std::uint64_t operator* (const std::uint64_t rhs) const { return rhs; }
        inline const float operator* (const float rhs) const { return rhs; }
        inline const double operator* (const double rhs) const { return rhs; }
        inline const long double operator* (const long double rhs) const { return rhs; }

        inline const Object& operator/ (const Object& rhs) { return rhs; }
        inline const std::uint8_t operator/ (const std::uint8_t rhs) const { return rhs; }
        inline const std::uint16_t operator/ (const std::uint16_t rhs) const { return rhs; }
        inline const std::uint32_t operator/ (const std::uint32_t rhs) const { return rhs; }
        inline const int operator/ (const int rhs) const { return rhs; }
        inline const std::uint64_t operator/ (const std::uint64_t rhs) const { return rhs; }
        inline const float operator/ (const float rhs) const { return rhs; }
        inline const double operator/ (const double rhs) const { return rhs; }
        inline const long double operator/ (const long double rhs) const { return rhs; }

        template<typename T = Object&>
        friend inline const bool operator<= (const T lhs, const Object& rhs) { return false; };

        template<typename T>
        friend inline const int operator+ (const T lhs, const Object& rhs) { return lhs; };

        template<typename T>
        friend inline const int operator- (const T lhs, const Object& rhs) { return lhs; };

        template<typename T>
        friend inline const int operator* (const T lhs, const Object& rhs) { return lhs; };

        template<typename T>
        friend inline const int operator/ (const T lhs, const Object& rhs) { return lhs; };


        inline operator int() const { return 0; }

    };


    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseRandom)
    {
        //-- Definitions of local testing classes
        // 
        // Notice: next() always returns 0
        struct BaseRandom0 : public BaseRandom<std::uint64_t, std::uint32_t, 32>
        {
            inline const double gauss_next() const noexcept
            {
                return _internal_state.gauss_next;
            }

            inline const bool gauss_valid() const noexcept
            {
                return _internal_state.gauss_valid;
            }
        };

        // Notice: next() always returns max value
        struct BaseRandom1 : public BaseRandom0
        {
            inline virtual const std::uint32_t next() noexcept override
            {
                return 0xffff'ffffUL;
            }

        };

        // Notice: random() always returns 1.0
        struct BaseRandom1_0 : public BaseRandom0
        {
            inline const double random() noexcept
            {
                return 1.0;
            }

        };

        // Notice: next() always returns the integer equivalent of 0.333333
        struct BaseRandom33 : public BaseRandom<std::uint32_t, std::uint32_t, 32>
        {
            inline const double gauss_next() const noexcept
            {
                return _internal_state.gauss_next;
            }

            inline const bool gauss_valid() const noexcept
            {
                return _internal_state.gauss_valid;
            }

            inline virtual const std::uint32_t next() noexcept override
            {
                return 0x5555'5555UL;  // i.e. std::uint32_t(double(0xffff'ffffUL) / 3.0);
            }

        };

        constexpr double _NORM33{ double(0x5555'5555UL) / double(0x1'0000'0000ULL) };



        //-- tests default empty constructor
        BaseRandom0 br0;
        EXPECT_EQ(0ULL, br0.state());
        EXPECT_FALSE(br0.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br0.gauss_next());
        
        BaseRandom1 br1;
        EXPECT_EQ(0ULL, br1.state());
        EXPECT_FALSE(br1.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br1.gauss_next());

        BaseRandom33 br33;
        EXPECT_EQ(0ULL, br33.state());
        EXPECT_FALSE(br33.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br33.gauss_next());


        //-- tests default copy constructor
        BaseRandom33 br;
        br.setstate(1ULL);

        BaseRandom33 br33copy(br);
        EXPECT_EQ(1ULL, br.state());
        EXPECT_FALSE(br.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br.gauss_next());


        //-- tests default move constructor
        BaseRandom33 br_(std::move(br));
        EXPECT_EQ(1ULL, br_.state());
        EXPECT_FALSE(br_.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br_.gauss_next());


        //-- tests copy assignment
        br = br33;
        EXPECT_EQ(0ULL, br.state());
        EXPECT_FALSE(br.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br.gauss_next());


        //-- tests move assignment
        br = std::move(br_);
        EXPECT_EQ(1ULL, br.state());
        EXPECT_FALSE(br.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br.gauss_next());


        //-- tests valued assignment
        BaseRandom<std::uint64_t, std::uint32_t, 32> brbase;
        brbase = 0xf00f'0ff0'f00f'0ff0ULL;
        EXPECT_EQ(0xf00f'0ff0'f00f'0ff0ULL, brbase.state());


        //-- tests next()
        EXPECT_EQ(0UL, br0.next());
        EXPECT_EQ(0xffff'ffffUL, br1.next());
        EXPECT_EQ(0x5555'5555UL, br33.next());


        //-- tests random()
        EXPECT_FLOAT_EQ(0.0f, br0.random<float>());
        EXPECT_DOUBLE_EQ(0.0, br0.random<double>());
        EXPECT_DOUBLE_EQ(0.0, br0.random());
        EXPECT_NEAR(0.0L, br0.random<long double>(), 1.0e-20L);

        EXPECT_FLOAT_EQ(1.0f, br1.random<float>());
        EXPECT_NEAR(1.0, br1.random<double>(), 1.0e-9);
        EXPECT_NEAR(1.0, br1.random(), 1.0e-9);
        EXPECT_NEAR(1.0L, br1.random<long double>(), 1.0e-9L);

        EXPECT_FLOAT_EQ(0.333333333f, br33.random<float>());
        EXPECT_NEAR(1.0 / 3.0, br33.random<double>(), 1.0e-9);
        EXPECT_NEAR(1.0 / 3.0, br33.random(), 1.0e-9);
        EXPECT_NEAR(1.0L / 3.0L, br33.random<long double>(), 1.0e-9L);


        //-- tests operator()
        EXPECT_FLOAT_EQ(0.0f, br0.operator()<float>());
        EXPECT_DOUBLE_EQ(0.0, br0.operator()<double>());
        EXPECT_NEAR(0.0L, br0.operator()<long double>(), 1.0e-20L);
        EXPECT_NEAR(0.0L, br0(), 1.0e-20L);

        EXPECT_FLOAT_EQ(1.0f, br1.operator()<float>());
        EXPECT_NEAR(1.0, br1.operator()<double>(), 1.0e-9);
        EXPECT_NEAR(1.0L, br1.operator()<long double>(), 1.0e-9L);
        EXPECT_NEAR(1.0L, br1(), 1.0e-9L);

        EXPECT_FLOAT_EQ(0.333333333f, br33.operator()<float>());
        EXPECT_NEAR(1.0 / 3.0, br33.operator()<double>(), 1.0e-9);
        EXPECT_NEAR(1.0L / 3.0L, br33.operator()<long double>(), 1.0e-9L);
        EXPECT_NEAR(1.0L / 3.0L, br33(), 1.0e-9L);


        //-- tests operator(max)
        EXPECT_EQ(0UL, br0(150UL));
        EXPECT_EQ(0ULL, br0(1500ULL));
        EXPECT_FLOAT_EQ(0.0f, br0(150.0f));

        EXPECT_EQ(149UL, br1(150UL));
        EXPECT_EQ(1499ULL, br1(1500ULL));
        EXPECT_NEAR(150.0, br1(150.0), 1.0e-7);

        EXPECT_EQ(49UL, br33(150UL));
        EXPECT_EQ(499ULL, br33(1500ULL));
        EXPECT_NEAR(50.0, br33(150.0), 1.0e-7);


        //-- tests operator(max, n)
        constexpr int n{ 5 };

        std::vector<std::uint32_t> vect = br0.operator()<std::uint32_t>(150UL, n);
        for (int i = 0; i < n; ++i)
            EXPECT_EQ(0UL, vect[i]);

        vect = br1.operator()<std::uint32_t>(1500UL, n);
        for (int i = 0; i < n; ++i)
            EXPECT_EQ(1499UL, vect[i]);

        vect = br33.operator()<std::uint32_t>(1500UL, n);
        for (int i = 0; i < n; ++i)
            EXPECT_EQ(499UL, vect[i]);


        //-- tests operator(min, max, n)
        vect = br0.operator()<std::uint32_t>(15UL, 150UL, n);
        for (int i = 0; i < n; ++i)
            EXPECT_EQ(15UL, vect[i]);

        vect = br1.operator()<std::uint32_t>(15UL, 1500UL, n);
        for (int i = 0; i < n; ++i)
            EXPECT_EQ(1499UL, vect[i]);

        vect = br33.operator()<std::uint32_t>(300UL, 1500UL, n);
        for (int i = 0; i < n; ++i)
            EXPECT_EQ(699UL, vect[i]);


        //-- tests operator(vect max)
        std::vector<std::uint32_t> max_vect{ 333, 555, 777, 999 };
        std::vector<double> max_vect_d{ 333., 555., 777., 999. };
        std::vector<double> vect_d;

        std::size_t mn{ max_vect.size() };

        vect = br0.operator()<std::uint32_t>(max_vect);
        for (std::uint32_t v : vect)
            EXPECT_EQ(0UL, v);

        vect_d = br0.operator()<double>(max_vect_d);
        for (double v : vect_d)
            EXPECT_DOUBLE_EQ(0., v);

        vect = br1.operator()<std::uint32_t>(max_vect);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(max_vect[i] - 1, vect[i]);

        vect_d = br1.operator()<double>(max_vect_d);
        for (int i = 0; i < mn; ++i)
            EXPECT_NEAR(max_vect_d[i], vect_d[i], 1.0e-6);

        vect = br33.operator()<std::uint32_t>(max_vect);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(std::uint32_t(max_vect[i] * _NORM33), vect[i]);


        //-- tests operator(array max)
        std::array<std::uint32_t, n> max_arr{ 444, 666, 888, 1110, 1332 };
        std::array<std::uint32_t, n> arr;

        arr = br0.operator() < std::uint32_t > (max_arr);
        for (std::uint32_t v : arr)
            EXPECT_EQ(0UL, v);

        arr = br1.operator() < std::uint32_t > (max_arr);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(std::uint32_t(max_arr[i] * 0.999999), arr[i]);

        arr = br33.operator() < std::uint32_t > (max_arr);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(::uint32_t(max_arr[i] * _NORM33), arr[i]);


        //-- tests operator(vect min, vect max)
        std::vector<std::uint32_t> min_vect{ 111, 222, 333, 444 };
        mn = max_vect.size();

        vect = br0.operator()<std::uint32_t>(min_vect, max_vect);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(min_vect[i], vect[i]);

        vect = br1.operator()<std::uint32_t>(min_vect, max_vect);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(std::uint32_t(max_vect[i] * 0.999999), vect[i]);

        vect = br33.operator()<std::uint32_t>(min_vect, max_vect);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(min_vect[i] + std::uint32_t((max_vect[i] - min_vect[i]) * _NORM33), vect[i]);


        //-- tests operator(array min, array max)
        std::array<std::uint32_t, n> min_arr{ 111, 222, 333, 444, 555 };

        arr = br0.operator()<std::uint32_t>(min_arr, max_arr);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(min_arr[i], arr[i]);

        arr = br1.operator()<std::uint32_t>(min_arr, max_arr);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(std::uint32_t(max_arr[i] * 0.999999), arr[i]);

        arr = br33.operator()<std::uint32_t>(min_arr, max_arr);
        for (int i = 0; i < mn; ++i)
            EXPECT_EQ(min_arr[i] + std::uint32_t((max_arr[i] - min_arr[i]) * _NORM33), arr[i]);


        //-- tests binomialvariate()
        EXPECT_EQ(15UL, br0.binomialvariate(15UL, 0.5));
        EXPECT_EQ(0UL, br1.binomialvariate(15UL, 0.99));
        EXPECT_EQ(15UL, br33.binomialvariate(15UL, 0.3334f));

        EXPECT_EQ(0, br0.binomialvariate(0, 0.5));
        EXPECT_EQ(0, br1.binomialvariate(0, 0.99));
        EXPECT_EQ(0, br33.binomialvariate(0, 0.3334f));

        EXPECT_THROW(br0.binomialvariate(-1.0f, 0.1f), IntegralValueTypeException);
        EXPECT_THROW(br1.binomialvariate(-1.0, 0.1), IntegralValueTypeException);
        EXPECT_THROW(br33.binomialvariate(-1.0L, 0.1L), IntegralValueTypeException);

        EXPECT_THROW(br0.binomialvariate(0, std::uint8_t(1)), FloatingPointTypeException);
        EXPECT_THROW(br1.binomialvariate(0, 2UL), FloatingPointTypeException);
        EXPECT_THROW(br33.binomialvariate(0, 3ULL), FloatingPointTypeException);

        EXPECT_THROW(br0.binomialvariate(-1, 0.1f), PositiveValueException);
        EXPECT_THROW(br1.binomialvariate(-1, 0.1), PositiveValueException);
        EXPECT_THROW(br33.binomialvariate(-1, 0.1L), PositiveValueException);

        EXPECT_THROW(br0.binomialvariate(11, -0.1f), ProbaOutOfRangeException);
        EXPECT_THROW(br1.binomialvariate(11, -0.1), ProbaOutOfRangeException);
        EXPECT_THROW(br33.binomialvariate(11, -0.1L), ProbaOutOfRangeException);

        EXPECT_THROW(br0.binomialvariate(11, 1.1f), ProbaOutOfRangeException);
        EXPECT_THROW(br1.binomialvariate(11, 1.1), ProbaOutOfRangeException);
        EXPECT_THROW(br33.binomialvariate(11, 1.1L), ProbaOutOfRangeException);


        //-- tests choice(vect)
        EXPECT_EQ(br0.choice(max_vect), max_vect.front());
        EXPECT_EQ(br1.choice(max_vect), max_vect.back());
        EXPECT_EQ(br33.choice(max_vect), max_vect[max_vect.size() / 3]);

        EXPECT_THROW(br0.choice(std::vector<std::uint32_t>()), ChoiceEmptySequenceException);
        EXPECT_THROW(br1.choice(std::vector<std::uint32_t>()), ChoiceEmptySequenceException);
        EXPECT_THROW(br33.choice(std::vector<std::uint32_t>()), ChoiceEmptySequenceException);


        //-- tests choice(array)
        EXPECT_EQ(br0.choice(max_arr), max_arr.front());
        EXPECT_EQ(br1.choice(max_arr), max_arr.back());
        EXPECT_EQ(br33.choice(max_arr), max_arr[max_arr.size() / 3]);

        EXPECT_THROW(br0.choice(std::array<std::uint32_t, 0>()), ChoiceEmptySequenceException);
        EXPECT_THROW(br1.choice(std::array<std::uint32_t, 0>()), ChoiceEmptySequenceException);
        EXPECT_THROW(br33.choice(std::array<std::uint32_t, 0>()), ChoiceEmptySequenceException);


        //-- tests getstate()
        struct BaseRandom<std::uint64_t, std::uint32_t, 32>::_InternalState internal_state{ brbase.getstate() };

        EXPECT_EQ(0xf00f'0ff0'f00f'0ff0ULL, internal_state.state);
        EXPECT_DOUBLE_EQ(0.0, internal_state.gauss_next);
        EXPECT_FALSE(internal_state.gauss_valid);


        //-- tests vect n_evaluate(n)
        std::vector<float> vf0{ br0.n_evaluate<float>(5) };
        for (float v : vf0)
            EXPECT_FLOAT_EQ(0.0f, v);

        std::vector<double> vd1{ br1.n_evaluate<double>(7) };
        for (double v : vd1)
            EXPECT_NEAR(1.0, v, 1.e-6);

        std::vector<long double> vld33{ br33.n_evaluate<long double>(9) };
        for (long double v : vld33)
            EXPECT_NEAR(0.333333333L, v, 1.e-6L);

        EXPECT_THROW(br0.n_evaluate<int>(5), FloatingPointTypeException);
        EXPECT_THROW(br1.n_evaluate<std::uint64_t>(5), FloatingPointTypeException);
        EXPECT_THROW(br33.n_evaluate<std::int8_t>(5), FloatingPointTypeException);


        //-- tests vect n_evaluate(n, max)
        vf0 = br0.n_evaluate<float>(5, 20.0f);
        for (float v : vf0)
            EXPECT_FLOAT_EQ(0.0f, v);

        vd1 = br1.n_evaluate<double>(7, 30.0);
        for (double v : vd1)
            EXPECT_NEAR(30.0, v, 1.e-6);

        vld33 = br33.n_evaluate<long double>(9, 40.0L);
        for (long double v : vld33)
            EXPECT_NEAR(13.333333333L, v, 1.e-6L);

        EXPECT_THROW(br0.n_evaluate<Object>(5, Object()), ValueTypeException);
        EXPECT_THROW(br1.n_evaluate<Object>(5, Object()), ValueTypeException);
        EXPECT_THROW(br33.n_evaluate<Object>(5, Object()), ValueTypeException);

        EXPECT_THROW((br0.n_evaluate<std::uint32_t, Object>(5, Object())), MaxValueTypeException);
        EXPECT_THROW((br1.n_evaluate<double, Object>(5, Object())), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, Object>(5, Object())), MaxValueTypeException);

        EXPECT_THROW(br0.n_evaluate<int>(0, 5), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<std::uint64_t, double>(0, 5.0)), ZeroLengthException);
        EXPECT_THROW((br33.n_evaluate<float, int>(0, 5)), ZeroLengthException);


        //-- tests vect n_evaluate(vect max)
        max_vect = { 6UL, 8UL, 1UL, 0UL };
        max_vect_d = { 6.0, 8.0, 1.0, 0.0 };

        std::vector<std::uint32_t> vu0{ br0.n_evaluate<std::uint32_t, double>({11.0, 22.0, 33.0, 44.0, 55.0}) };
        for (auto v : vu0)
            EXPECT_EQ(0UL, v);

        std::vector<std::uint32_t> vu1{ br1.n_evaluate<std::uint32_t, double>(max_vect_d) };
        for (int i = 0; i < max_vect_d.size(); ++i)
            EXPECT_EQ(vu1[i], std::uint32_t(max_vect_d[i] * 0.99999999));

        std::vector<std::uint32_t> vu33{ br33.n_evaluate<std::uint32_t>(max_vect) };
        for (int i = 0; i < max_vect.size(); ++i)
            EXPECT_EQ(vu33[i], std::uint32_t(max_vect[i] * _NORM33));

        std::vector<Object> obj_vect(2);
        EXPECT_THROW(br0.n_evaluate<Object>(obj_vect), ValueTypeException);
        EXPECT_THROW((br1.n_evaluate<Object, double>(max_vect_d)), ValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, Object>(obj_vect)), MaxValueTypeException);

        EXPECT_THROW(br0.n_evaluate<int>(std::vector<int>()), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<std::uint64_t, float>(std::vector<float>())), ZeroLengthException);
        EXPECT_THROW(br33.n_evaluate<std::int8_t>(std::vector<std::int8_t>()), ZeroLengthException);


        //-- tests vect n_evaluate(n, min, max)
        min_vect = { 1UL, 2UL, 3UL };
        std::vector<float> min_vect_f{ 1.0f, 2.0f, 3.0f };

        vu0 = br0.n_evaluate<std::uint32_t>(min_vect, max_vect);
        for (int i=0; i < std::min(min_vect.size(), max_vect.size()); ++i)
            EXPECT_EQ(vu0[i], std::min(min_vect[i], max_vect[i]));

        vu1 = br1.n_evaluate<std::uint32_t>(min_vect_f, max_vect);
        for (int i = 0; i < std::min(min_vect_f.size(), max_vect.size()); ++i)
            EXPECT_EQ(vu1[i], std::uint32_t(std::max(min_vect_f[i], float(max_vect[i])) * 0.999999));

        vu33 = br33.n_evaluate<std::uint32_t>(min_vect_f, max_vect_d);
        for (int i = 0; i < std::min(min_vect_f.size(), max_vect_d.size()); ++i) {
            double a{ std::min(double(min_vect_f[i]), max_vect_d[i]) };
            double b{ std::max(double(min_vect_f[i]), max_vect_d[i]) };
            EXPECT_EQ(vu33[i], std::uint32_t(a + (b - a) * _NORM33));
        }

        std::vector<Object> minv(5);
        std::vector<Object> maxv(5);
        EXPECT_THROW(br0.n_evaluate<Object>(minv, maxv), ValueTypeException);
        EXPECT_THROW(br1.n_evaluate<Object>(minv, maxv), ValueTypeException);
        EXPECT_THROW(br33.n_evaluate<Object>(minv, maxv), ValueTypeException);

        EXPECT_THROW((br0.n_evaluate<Object, std::uint32_t>(min_vect, max_vect)), ValueTypeException);
        EXPECT_THROW((br1.n_evaluate<Object, float, std::uint32_t>(min_vect_f, max_vect)), ValueTypeException);
        EXPECT_THROW((br33.n_evaluate<Object, float, double>(min_vect_f, max_vect_d)), ValueTypeException);

        EXPECT_THROW((br0.n_evaluate<std::uint32_t, Object, std::uint32_t>(minv, max_vect)), MinValueTypeException);
        EXPECT_THROW((br1.n_evaluate<int, float, Object>(min_vect_f, maxv)), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<float, Object>(minv, maxv)), MinValueTypeException);

        EXPECT_THROW(br0.n_evaluate<int>({ 1, 2 }, std::vector<int>()), ZeroLengthException);
        EXPECT_THROW(br1.n_evaluate<int>(std::vector<int>(), std::vector<int>()), ZeroLengthException);
        EXPECT_THROW(br33.n_evaluate<int>(std::vector<int>(), { 1, 2 }), ZeroLengthException);

        EXPECT_THROW(br0.n_evaluate<int>({ 1, 2 }, std::vector<Object>()), MaxValueTypeException);
        EXPECT_THROW(br1.n_evaluate<float>(std::vector<Object>(), std::vector<Object>()), MinValueTypeException);
        EXPECT_THROW(br33.n_evaluate<double>(std::vector<Object>(), { 1, 2 }), MinValueTypeException);


        //-- tests array<T, n> n_evaluate()
        std::array<float, 5> af0{ br0.n_evaluate<float, 5>() };
        for (float a : af0)
            EXPECT_FLOAT_EQ(0.0f, a);

        std::array<double, 7> ad1{ br1.n_evaluate<double, 7>() };
        for (double a : ad1)
            EXPECT_NEAR(1.0, a, 1.e-6);

        std::array<long double, 9> ald33{ br33.n_evaluate<long double, 9>() };
        for (long double a : ald33)
            EXPECT_NEAR(0.333333333L, a, 1.e-6);

        EXPECT_THROW((br0.n_evaluate<int, 5>()), FloatingPointTypeException);
        EXPECT_THROW((br1.n_evaluate<Object, 7>()), FloatingPointTypeException);
        EXPECT_THROW((br33.n_evaluate<std::uint64_t, 9>()), FloatingPointTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 0>()), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<float, 0>()), ZeroLengthException);
        EXPECT_THROW((br33.n_evaluate<double, 0>()), ZeroLengthException);


        //-- tests array<T, n> n_evaluate(max)
        af0 = br0.n_evaluate<float, 5>(10ULL);
        for (float a : af0)
            EXPECT_FLOAT_EQ(0.0f, a);

        std::array<std::uint64_t, 7> au1{ br1.n_evaluate<std::uint64_t, 7>(20.0) };
        for (std::uint64_t a : au1)
            EXPECT_EQ(19ULL, a);

        ald33 = br33.n_evaluate<long double, 9>(30.0L);
        for (long double a : ald33)
            EXPECT_NEAR(10.0L, a, 1.e-6);

        EXPECT_THROW((br0.n_evaluate<Object, 5>(Object())), ValueTypeException);
        EXPECT_THROW((br1.n_evaluate<Object, 7>(8)), ValueTypeException);
        EXPECT_THROW((br33.n_evaluate<Object, 9>(11.1)), ValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1>(Object())), MaxValueTypeException);
        EXPECT_THROW((br1.n_evaluate<float, 2>(Object())), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 3>(Object())), MaxValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 0>(2.5L)), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<float, 0>(2.5f)), ZeroLengthException);
        EXPECT_THROW((br33.n_evaluate<double, 0>(2.5)), ZeroLengthException);


        //-- tests array<T, n> n_evaluate(min, max)
        af0 = br0.n_evaluate<float, 5>(1.5, 10);
        for (float a : af0)
            EXPECT_FLOAT_EQ(1.5f, a);

        au1 = br1.n_evaluate<std::uint64_t, 7>(2ULL, 20.0L);
        for (std::uint64_t a : au1)
            EXPECT_EQ(19ULL, a);

        ald33 = br33.n_evaluate<long double, 9>(3.0L, 30.0L);
        for (long double a : ald33)
            EXPECT_NEAR(12.0L, a, 1.e-6);

        EXPECT_THROW((br0.n_evaluate<Object, 5>(Object(), Object())), ValueTypeException);
        EXPECT_THROW((br1.n_evaluate<Object, 7>(Object(), 5UL)), ValueTypeException);
        EXPECT_THROW((br33.n_evaluate<Object, 9>(Object(), 0.0f)), ValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1>(Object(), Object())), MinValueTypeException);
        EXPECT_THROW((br1.n_evaluate<float, 2>(Object(), 5UL)), MinValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 3>(Object(), 0.0)), MinValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1>(1, Object())), MaxValueTypeException);
        EXPECT_THROW((br1.n_evaluate<float, 2>(5UL, Object())), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 3>(0.0, Object())), MaxValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 0>(2.5L, 3.5L)), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<float, 0>(2.5f, 3.5f)), ZeroLengthException);
        EXPECT_THROW((br33.n_evaluate<double, 0>(2.5, 3.5)), ZeroLengthException);


        //-- tests array<T, n> n_evaluate(array max)
        // reminder:
        //  std::array<std::uint32_t, n> max_arr{ 444, 666, 888, 1110, 1332 };
        //  std::array<std::uint32_t, n> min_arr{ 111, 222, 333, 444, 555 };
        std::array<float, 5> au0{ br0.n_evaluate<float, 5>(max_arr) };
        for (std::uint32_t a : au0)
            EXPECT_EQ(0.0f, a);

        std::array<std::uint32_t, 4> au41{ br1.n_evaluate<std::uint32_t, 4, std::uint32_t, 5>(max_arr) };
        for (int i = 0; i < 4; ++i)
            EXPECT_EQ(max_arr[i] - 1, au41[i]);

        std::array<float, 5> max_arr_f{ 444.0f, 666.0f, 8889.0f, 1110.0f, 1332.0f };
        std::array<std::uint32_t, 9> au33{ br33.n_evaluate<std::uint32_t, 9, float, 5>(max_arr_f) };
        for (int i = 0; i < 5; ++i)
            EXPECT_EQ(std::uint32_t(max_arr_f[i] * _NORM33), au33[i]);
        for (int i = 5; i < 9; ++i)
            EXPECT_EQ(0UL, au33[i]);

        EXPECT_THROW((br0.n_evaluate<Object, 5>(std::array<Object, 5>())), ValueTypeException);
        EXPECT_THROW((br1.n_evaluate<Object, 7>(std::array<Object, 7>())), ValueTypeException);
        EXPECT_THROW((br33.n_evaluate<Object, 9>(std::array<Object, 9>())), ValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1, Object, 2>(std::array<Object, 2>())), MaxValueTypeException);
        EXPECT_THROW((br1.n_evaluate<float, 2, Object, 3>(std::array<Object, 3>())), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 3, Object, 1>(std::array<Object, 1>())), MaxValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1, Object, 0>(std::array<Object, 0>())), MaxValueTypeException);
        EXPECT_THROW((br1.n_evaluate<float, 2, Object, 0>(std::array<Object, 0>())), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 3, Object, 0>(std::array<Object, 0>())), MaxValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1, long double, 0>(std::array<long double, 0>())), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<float, 0, int, 0>(std::array<int, 0>())), ZeroLengthException);
        EXPECT_THROW((br33.n_evaluate<double, 0, std::uint32_t, 1>(std::array<std::uint32_t, 1>())), ZeroLengthException);


        //-- tests array<T, n> n_evaluate(array min, array max)
        std::array<std::uint64_t, 5> max_arr_5{ 444, 666, 888, 444, 1332 };
        std::array<std::uint16_t, 4> max_arr_4{ 444, 666, 888, 444 };
        std::array<float, 5> min_arr_5{ 111.0f, 222.0f, 333.0f, 1110.0f, 555.0f };
        std::array<float, 4> min_arr_4{ 111.0f, 222.0f, 333.0f, 1110.0f };

        std::array<float, 6> arr6{ br0.n_evaluate<float, 6>(min_arr_4, max_arr_5) };
        for (int i = 0; i < 4; ++i) {
            EXPECT_FLOAT_EQ(std::min(float(min_arr_4[i]),float(max_arr_5[i])), arr6[i]);
        }
        for (int i=4; i < 6; ++i)
            EXPECT_EQ(0.0f, arr6[i]);

        std::array<std::uint32_t, 5> arr5{ br1.n_evaluate<std::uint32_t, 5>(min_arr_5, max_arr_4) };
        for (int i = 0; i < 4; ++i) {
            EXPECT_EQ(std::max(std::uint32_t(min_arr_5[i] * 0.999999f), std::uint32_t(max_arr_4[i] * 0.999999f)), arr5[i]);
        }
        for (int i = 4; i < 5; ++i)
            EXPECT_EQ(0UL, arr5[i]);

        std::array<std::uint32_t, 4> arr4{ br33.n_evaluate<std::uint32_t, 4>(min_arr_4, max_arr_4) };
        for (int i = 0; i < 4; ++i) {
            double a{ std::min(double(min_arr_4[i]), double(max_arr_4[i])) };
            double b{ std::max(double(min_arr_4[i]), double(max_arr_4[i])) };
            EXPECT_EQ(std::uint32_t(a + (b - a) * 0.333333), arr4[i]);
        }

        EXPECT_THROW((br0.n_evaluate<Object, 5>(min_arr_4, max_arr_5)), ValueTypeException);
        EXPECT_THROW((br1.n_evaluate<Object, 7>(std::array<Object, 7>(), max_arr_4)), ValueTypeException);
        EXPECT_THROW((br33.n_evaluate<Object, 9>(min_arr_5, std::array<Object, 9>())), ValueTypeException);
        EXPECT_THROW((br33.n_evaluate<Object, 0>(min_arr_5, std::array<Object, 9>())), ValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1>(std::array<Object, 2>(), max_arr_5)), MinValueTypeException);
        EXPECT_THROW((br1.n_evaluate<float, 2>(std::array<Object, 3>(), max_arr_4)), MinValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 3>(std::array<Object, 1>(), std::array<Object, 3>())), MinValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 0>(std::array<Object, 1>(), std::array<Object, 3>())), MinValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 1>(min_arr_4, std::array<Object, 2>())), MaxValueTypeException);
        EXPECT_THROW((br1.n_evaluate<float, 2>(min_arr_5, std::array<Object, 3>())), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 3>(min_arr, std::array<Object, 1>())), MaxValueTypeException);
        EXPECT_THROW((br33.n_evaluate<int, 0>(min_arr, std::array<Object, 1>())), MaxValueTypeException);

        EXPECT_THROW((br0.n_evaluate<long double, 0>(min_arr_4, max_arr_4)), ZeroLengthException);
        EXPECT_THROW((br0.n_evaluate<long double, 0>(std::array<long double, 0>(), max_arr_4)), ZeroLengthException);
        EXPECT_THROW((br0.n_evaluate<long double, 1>(std::array<long double, 0>(), max_arr_4)), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<float, 0>(min_arr_5, std::array<int, 0>())), ZeroLengthException);
        EXPECT_THROW((br1.n_evaluate<float, 1>(min_arr_5, std::array<int, 0>())), ZeroLengthException);
        EXPECT_THROW((br33.n_evaluate<double, 0>(std::array<std::uint32_t, 0>(), std::array<int, 0>())), ZeroLengthException);
        EXPECT_THROW((br33.n_evaluate<double, 1>(std::array<std::uint32_t, 0>(), std::array<int, 0>())), ZeroLengthException);


        //-- tests randbytes(n)
        std::vector<std::uint8_t> vb0{ br0.randbytes(7) };
        for (auto b : vb0)
            EXPECT_EQ(0, b);

        std::vector<unsigned char> vb1{ br1.randbytes(3) };
        for (auto b : vb1)
            EXPECT_EQ(255, b);

        std::vector<unsigned char> vb33{ br33.randbytes(11) };
        for (auto b : vb33)
            EXPECT_EQ(std::uint8_t(256 * 0.333333f), b);

        EXPECT_THROW(br0.randbytes(0), ZeroLengthException);
        EXPECT_THROW(br1.randbytes(0), ZeroLengthException);
        EXPECT_THROW(br33.randbytes(0), ZeroLengthException);


        //-- tests randint()
        EXPECT_EQ(1, br0.randint(1, 5));
        EXPECT_EQ(10ULL, br1.randint(0ULL, 10ULL));
        EXPECT_EQ(std::int8_t(double(7 * .3333333 - 7)), br33.randint(std::int8_t(-7), std::int8_t(-1)));

        EXPECT_EQ(1, br0.randint(5, 1));
        EXPECT_EQ(10ULL, br1.randint(10ULL, 0ULL));
        EXPECT_EQ(std::int8_t(double(7 * .3333333 - 7)), br33.randint(std::int8_t(-1), std::int8_t(-7)));

        EXPECT_THROW(br0.randint(1.9, 3.0), IntegralValueTypeException);
        EXPECT_THROW(br1.randint(Object(), Object()), IntegralValueTypeException);
        EXPECT_THROW(br33.randint(-7.0f, -1.0f), IntegralValueTypeException);


        //-- tests randrange()
        EXPECT_EQ(br0.randrange(std::uint8_t(1), std::uint8_t(4)), std::uint8_t(1));
        EXPECT_EQ(br1.randrange(std::uint8_t(1), std::uint8_t(4)), std::uint8_t(3));
        EXPECT_EQ(br33.randrange(std::uint8_t(1), std::uint8_t(5)), std::uint8_t(4 * 0.333333 + 1));

        EXPECT_EQ(br0.randrange(std::uint8_t(4), std::uint8_t(1), -1), std::uint8_t(4));
        EXPECT_EQ(br1.randrange(std::uint8_t(4), std::uint8_t(1), -1), std::uint8_t(2));
        EXPECT_EQ(br33.randrange(std::uint8_t(5), std::uint8_t(1), -1), std::uint8_t(4));

        EXPECT_EQ(br0.randrange(1, 4, 2), 1);
        EXPECT_EQ(br1.randrange(1, 5, 2), 3);
        EXPECT_NEAR(br33.randrange(1.0, 5.0, 0.5), 2.0, 1.0e-6);
        EXPECT_NEAR(br33.randrange(1.0, 5.0, 0.25), 2.25, 1.0e-6);
        EXPECT_NEAR(br1.randrange(1.0, 5.5, 0.35), 5.2, 1.0e-6);

        EXPECT_EQ(br0.randrange(4, 1, -2), 4);
        EXPECT_EQ(br1.randrange(5, 1, -2), 3);
        EXPECT_NEAR(br33.randrange(5.0, 1.0, -0.5), 4.0, 1.0e-6);
        EXPECT_NEAR(br33.randrange(5.0, 1.0, -0.25), 3.75, 1.0e-6);
        EXPECT_NEAR(br1.randrange(5.5, 1.0, -0.35), 1.30, 1.0e-6);

        EXPECT_THROW(br0.randrange(Object(), Object(), Object()), ValueTypeException);
        EXPECT_THROW(br1.randrange(15, 25, 0), RangeZeroStepException);
        EXPECT_THROW(br33.randrange(25ULL, 25ULL, 2ULL), RangeSameValuesException);
        EXPECT_THROW(br0.randrange(15L, 25L, -1L), RangeIncoherentValuesException);
        EXPECT_THROW(br1.randrange(25UL, 15UL, 3UL), RangeIncoherentValuesException);


        //-- tests samples(vector, vector, k)
        std::vector<char> vect_population{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M' };
        const size_t N_vect_population{ vect_population.size()};
        std::vector<char> vect_c;

        int k{ 0 };
        br0.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[i], vect_c[i]);
        k = 5;
        br0.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[i], vect_c[i]);
        k = N_vect_population;
        br0.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[i], vect_c[i]);

        k = 0;
        br1.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[N_vect_population - i - 1], vect_c[i]);
        k = 5;
        br1.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("MABCD"[i], vect_c[i]);
        k = N_vect_population;
        br1.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("MABCDEFGHIJKL"[i], vect_c[i]);

        k = 0;
        br33.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[N_vect_population - i - 1], vect_c[i]);
        k = 5;
        br33.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("EAFGD"[i], vect_c[i]);
        k = N_vect_population;
        br33.sample(vect_c, vect_population, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], vect_c[i]);

        EXPECT_THROW(br0.sample(vect_c, vect_population, N_vect_population + 1), SampleCountException);


        //-- tests samples(array, k)
        std::array<char, 13> arr_population{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M' };

        std::array<char, 0> arr_c0;
        std::array<char, 5> arr_c5;
        std::array<char, 13> arr_c13;
        std::array<char, 14> arr_c14;

        br0.sample(arr_c0, arr_population);
        for (int i = 0; i < 0; ++i)
            EXPECT_EQ(arr_population[i], arr_c0[i]);
        br0.sample(arr_c5, arr_population);
        for (int i = 0; i < 5; ++i)
            EXPECT_EQ(arr_population[i], arr_c5[i]);
        br0.sample(arr_c13, arr_population);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ(arr_population[i], arr_c13[i]);

        br1.sample(arr_c0, arr_population);
        for (int i = 0; i < 0; ++i)
            EXPECT_EQ(arr_population[13 - i - 1], arr_c0[i]);
        br1.sample(arr_c5, arr_population);
        for (int i = 0; i < 5; ++i)
            EXPECT_EQ("MABCD"[i], arr_c5[i]);
        br1.sample(arr_c13, arr_population);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("MABCDEFGHIJKL"[i], arr_c13[i]);

        br33.sample(arr_c0, arr_population);
        for (int i = 0; i < 0; ++i)
            EXPECT_EQ(arr_population[13 - i - 1], arr_c0[i]);
        br33.sample(arr_c5, arr_population);
        for (int i = 0; i < 5; ++i)
            EXPECT_EQ("EAFGD"[i], vect_c[i]);
        br33.sample(arr_c13, arr_population);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], vect_c[i]);

        EXPECT_THROW(br0.sample(arr_c14, arr_population), SampleCountException);


        //-- tests samples(vector, vector, vector, k)

        // first, with all counts set to 1
        std::vector<int> vect_counts(vect_population.size(), 1);

        k = 0 ;
        br0.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[i], vect_c[i]);
        k = 5;
        br0.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[i], vect_c[i]);
        k = N_vect_population;
        br0.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[i], vect_c[i]);

        k = 0;
        br1.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[N_vect_population - i - 1], vect_c[i]);
        k = 5;
        br1.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("MABCD"[i], vect_c[i]);
        k = N_vect_population;
        br1.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("MABCDEFGHIJKL"[i], vect_c[i]);

        k = 0;
        br33.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], vect_c[i]);
        k = 5;
        br33.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("EAFGD"[i], vect_c[i]);
        k = N_vect_population;
        br33.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], vect_c[i]);


        // then, with some counts different from 1
        vect_counts = { 0, 2, 1, 3, 1, 2, 0, 2, 1, 3, 2, 2, 0 };
        const char SAMPLES[]{ "BBCDDDEFFHHIJJJKKLL" };
        const int N_COUNTS{ 19 };

        k = 0;
        br0.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(vect_population[i], vect_c[i]);
        k = 5;
        br0.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(SAMPLES[i], vect_c[i]);
        k = N_COUNTS;
        br0.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(SAMPLES[i], vect_c[i]);

        k = 0;
        br1.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(SAMPLES[N_vect_population - i - 1], vect_c[i]);
        k = 5;
        br1.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("LBBCD"[i], vect_c[i]);
        k = N_COUNTS;
        br1.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("LBBCDDDEFFHHIJJJKKL"[i], vect_c[i]);

        k = 0;
        br33.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ(SAMPLES[i], vect_c[i]);
        k = 5;
        br33.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("EBFFD"[i], vect_c[i]);
        k = N_COUNTS;
        br33.sample(vect_c, vect_population, vect_counts, k);
        for (int i = 0; i < k; ++i)
            EXPECT_EQ("EBFFDHHBIJDJJCKKDLL"[i], vect_c[i]);


        // what about all counts set to 0?
        vect_counts = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

        k = 0;
        br0.sample(vect_c, vect_population, vect_counts, k);
        EXPECT_EQ(0ULL, vect_c.size());
        k = 5;
        EXPECT_THROW(br0.sample(vect_c, vect_population, vect_counts, k), SampleCountException);
        k = N_COUNTS;
        EXPECT_THROW(br0.sample(vect_c, vect_population, vect_counts, k), SampleCountException);

        k = 0;
        br1.sample(vect_c, vect_population, vect_counts, k);
        EXPECT_EQ(0ULL, vect_c.size());
        k = 5;
        EXPECT_THROW(br1.sample(vect_c, vect_population, vect_counts, k), SampleCountException);
        k = N_COUNTS;
        EXPECT_THROW(br1.sample(vect_c, vect_population, vect_counts, k), SampleCountException);

        k = 0;
        br33.sample(vect_c, vect_population, vect_counts, k);
        EXPECT_EQ(0ULL, vect_c.size());
        k = 5;
        EXPECT_THROW(br33.sample(vect_c, vect_population, vect_counts, k), SampleCountException);
        k = N_COUNTS;
        EXPECT_THROW(br33.sample(vect_c, vect_population, vect_counts, k), SampleCountException);


        // finally, with exceptions thrown
        std::vector<Object> vect_obj(13);
        EXPECT_THROW(br0.sample(vect_c, vect_population, vect_obj, 0), SampleCountsTypeException);
        EXPECT_THROW(br1.sample(vect_c, vect_population, vect_obj, 5), SampleCountsTypeException);
        EXPECT_THROW(br33.sample(vect_c, vect_population, vect_obj, 13), SampleCountsTypeException);
        EXPECT_THROW(br0.sample(vect_c, vect_population, std::vector<float>(13), 0), SampleCountsTypeException);
        EXPECT_THROW(br1.sample(vect_c, vect_population, std::vector<double>(13), 5), SampleCountsTypeException);
        EXPECT_THROW(br33.sample(vect_c, vect_population, std::vector<long double>(13), 13), SampleCountsTypeException);

        EXPECT_THROW(br0.sample(vect_c, std::vector<char>{'Z'}, vect_counts, 0), SampleSizesException);
        EXPECT_THROW(br1.sample(vect_c, std::vector<char>{'Z'}, vect_counts, 5), SampleSizesException);
        EXPECT_THROW(br33.sample(vect_c, std::vector<char>{'Z'}, vect_counts, 13), SampleSizesException);

        vect_counts = { 0, 2, 1, 3, 1, 2, 0, 2, 1, 3, 2, 2, 0 };
        EXPECT_THROW(br0.sample(vect_c, vect_population, vect_counts, N_COUNTS + 1), SampleCountException);
        EXPECT_THROW(br1.sample(vect_c, vect_population, vect_counts, N_COUNTS + 5), SampleCountException);
        EXPECT_THROW(br33.sample(vect_c, vect_population, vect_counts, 0xffff'ffff'ffff'ffffULL), SampleCountException);


        //-- tests samples(array, array, k)

        // first, with all counts set to 1
        constexpr int N_ARR{ 13 };
        std::array<int, N_ARR> arr_counts{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        std::array<char, 19> arr_c19;
        std::array<char, 20> arr_c20;

        br0.sample(arr_c0, arr_population, arr_counts);
        for (int i = 0; i < arr_c0.size(); ++i)
            EXPECT_EQ(arr_population[i], arr_c0[i]);
        br0.sample(arr_c5, arr_population, arr_counts);
        for (int i = 0; i < arr_c5.size(); ++i)
            EXPECT_EQ(arr_population[i], arr_c5[i]);
        br0.sample(arr_c13, arr_population, arr_counts);
        for (int i = 0; i < arr_c13.size(); ++i)
            EXPECT_EQ(arr_population[i], arr_c13[i]);
        EXPECT_THROW(br0.sample(arr_c19, arr_population, arr_counts), SampleCountException);

        br1.sample(arr_c0, arr_population, arr_counts);
        for (int i = 0; i < arr_c0.size(); ++i)
            EXPECT_EQ(arr_population[i], arr_c0[i]);
        br1.sample(arr_c5, arr_population, arr_counts);
        for (int i = 0; i < arr_c5.size(); ++i)
            EXPECT_EQ("MABCD"[i], arr_c5[i]);
        br1.sample(arr_c13, arr_population, arr_counts);
        for (int i = 0; i < arr_c13.size(); ++i)
            EXPECT_EQ("MABCDEFGHIJKL"[i], arr_c13[i]);
        EXPECT_THROW(br1.sample(arr_c19, arr_population, arr_counts), SampleCountException);

        br33.sample(arr_c0, arr_population, arr_counts);
        for (int i = 0; i < arr_c0.size(); ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], arr_c0[i]);
        br33.sample(arr_c5, arr_population, arr_counts);
        for (int i = 0; i < arr_c5.size(); ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], arr_c5[i]);
        br33.sample(arr_c13, arr_population, arr_counts);
        for (int i = 0; i < arr_c13.size(); ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], arr_c13[i]);
        EXPECT_THROW(br33.sample(arr_c19, arr_population, arr_counts), SampleCountException);


        // then, with some counts different from 1
        arr_counts = { 0, 2, 1, 3, 1, 2, 0, 2, 1, 3, 2, 2, 0 };
        // reminder: SAMPLES[] = "BBCDDDEFFHHIJJJKKLL";  N_COUNTS = 19;

        br0.sample(arr_c0, arr_population, arr_counts);
        for (int i = 0; i < arr_c0.size(); ++i)
            EXPECT_EQ(SAMPLES[i], arr_c0[i]);
        br0.sample(arr_c5, arr_population, arr_counts);
        for (int i = 0; i < arr_c5.size(); ++i)
            EXPECT_EQ(SAMPLES[i], arr_c5[i]);
        br0.sample(arr_c13, arr_population, arr_counts);
        for (int i = 0; i < arr_c13.size(); ++i)
            EXPECT_EQ(SAMPLES[i], arr_c13[i]);
        EXPECT_THROW(br0.sample(arr_c20, arr_population, arr_counts), SampleCountException);

        br1.sample(arr_c0, arr_population, arr_counts);
        for (int i = 0; i < arr_c0.size(); ++i)
            EXPECT_EQ("LBBCDDDEFFHHIJJJKKL"[i], arr_c0[i]);
        br1.sample(arr_c5, arr_population, arr_counts);
        for (int i = 0; i < arr_c5.size(); ++i)
            EXPECT_EQ("LBBCDDDEFFHHIJJJKKL"[i], arr_c5[i]);
        br1.sample(arr_c13, arr_population, arr_counts);
        for (int i = 0; i < arr_c13.size(); ++i)
            EXPECT_EQ("LBBCDDDEFFHHIJJJKKL"[i], arr_c13[i]);
        EXPECT_THROW(br1.sample(arr_c20, arr_population, arr_counts), SampleCountException);

        br33.sample(arr_c0, arr_population, arr_counts);
        for (int i = 0; i < arr_c0.size(); ++i)
            EXPECT_EQ("EBFFDHHBIJDJJCKKDLL"[i], arr_c0[i]);
        br33.sample(arr_c5, arr_population, arr_counts);
        for (int i = 0; i < arr_c5.size(); ++i)
            EXPECT_EQ("EBFFDHHBIJDJJCKKDLL"[i], arr_c5[i]);
        br33.sample(arr_c13, arr_population, arr_counts);
        for (int i = 0; i < arr_c13.size(); ++i)
            EXPECT_EQ("EBFFDHHBIJDJJCKKDLL"[i], arr_c13[i]);
        EXPECT_THROW(br33.sample(arr_c20, arr_population, arr_counts), SampleCountException);


        // what about all counts set to 0?
        arr_counts = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

        br0.sample(arr_c0, arr_population, arr_counts);
        EXPECT_EQ(0ULL, arr_c0.size());
        EXPECT_THROW(br0.sample(arr_c5, arr_population, arr_counts), SampleCountException);
        EXPECT_THROW(br0.sample(arr_c19, arr_population, arr_counts), SampleCountException);

        br1.sample(arr_c0, arr_population, arr_counts);
        EXPECT_EQ(0ULL, arr_c0.size());
        EXPECT_THROW(br1.sample(arr_c5, arr_population, arr_counts), SampleCountException);
        EXPECT_THROW(br1.sample(arr_c19, arr_population, arr_counts), SampleCountException);

        br33.sample(arr_c0, arr_population, arr_counts);
        EXPECT_EQ(0ULL, arr_c0.size());
        EXPECT_THROW(br33.sample(arr_c5, arr_population, arr_counts), SampleCountException);
        EXPECT_THROW(br33.sample(arr_c19, arr_population, arr_counts), SampleCountException);


        // finally, with exceptions thrown
        std::array<Object, 13> arr_obj;
        EXPECT_THROW(br0.sample(arr_c0, arr_population, arr_obj), SampleCountsTypeException);
        EXPECT_THROW(br1.sample(arr_c5, arr_population, arr_obj), SampleCountsTypeException);
        EXPECT_THROW(br33.sample(arr_c13, arr_population, arr_obj), SampleCountsTypeException);

        EXPECT_THROW(br0.sample(arr_c0, arr_population, std::array<float, 13>()), SampleCountsTypeException);
        EXPECT_THROW(br1.sample(arr_c5, arr_population, std::array<double, 13>()), SampleCountsTypeException);
        EXPECT_THROW(br33.sample(arr_c13, arr_population, std::array<long double, 13>()), SampleCountsTypeException);


        //-- tests seed() -- notice: tests _setstate() and state() also
        br0.seed();
        EXPECT_EQ(br0.state(), 0ULL);
        br1.seed();
        EXPECT_EQ(br1.state(), 0ULL);
        br33.seed();
        EXPECT_EQ(br33.state(), 0UL);

        br0.seed(123UL);
        EXPECT_EQ(br0.state(), 0ULL);
        br1.seed(456789UL);
        EXPECT_EQ(br1.state(), 0ULL);
        br33.seed(0xffff'ffffUL);
        EXPECT_EQ(br33.state(), 0UL);

        br0.seed(0ULL);
        EXPECT_EQ(br0.state(), 0ULL);
        br1.seed(0x999'777'555'333ULL);
        EXPECT_EQ(br1.state(), 0ULL);
        br33.seed(0xffff'ffff'ffff'ffffULL);
        EXPECT_EQ(br33.state(), 0UL);

        br0.seed(0.0f);
        EXPECT_EQ(br0.state(), 0ULL);
        br1.seed(123.0);
        EXPECT_EQ(br1.state(), 0ULL);
        br33.seed(-1.0);
        EXPECT_EQ(br33.state(), 0UL);


        //-- tests setstate()
        br0.setstate(0xffff'ffff'ffff'ffffULL);
        EXPECT_EQ(br0.state(), 0xffff'ffff'ffff'ffffULL);
        EXPECT_FALSE(br0.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br0.gauss_next());

        br1.setstate(0x1234'5678'9abc'def0ULL);
        EXPECT_EQ(br1.state(), 0x1234'5678'9abc'def0ULL);
        EXPECT_FALSE(br1.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br1.gauss_next());

        br33.setstate(0x1'0123'4567ULL);
        EXPECT_EQ(br33.state(), 0x123'4567ULL);
        EXPECT_FALSE(br33.gauss_valid());
        EXPECT_DOUBLE_EQ(0.0, br33.gauss_next());


        br0.setstate(0xffff'ffff'ffff'ffffULL, 0.987);
        EXPECT_EQ(br0.state(), 0xffff'ffff'ffff'ffffULL);
        EXPECT_TRUE(br0.gauss_valid());
        EXPECT_DOUBLE_EQ(0.987, br0.gauss_next());

        br1.setstate(0x1234'5678'9abc'def0ULL, 0.654f);
        EXPECT_EQ(br1.state(), 0x1234'5678'9abc'def0ULL);
        EXPECT_TRUE(br1.gauss_valid());
        EXPECT_DOUBLE_EQ(double(0.654f), br1.gauss_next());

        br33.setstate(0x1'0123'4567ULL, 0.321);
        EXPECT_EQ(br33.state(), 0x123'4567ULL);
        EXPECT_TRUE(br33.gauss_valid());
        EXPECT_DOUBLE_EQ(0.321, br33.gauss_next());


        //-- tests shuffle()
        std::vector<char> vec_s(vect_population);
        std::array<char, 13> arr_s(arr_population);

        br0.shuffle(vec_s);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("ABCDEFGHIJKLM"[i], vec_s[i]);

        vec_s = vect_population;
        br1.shuffle(vec_s);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("MABCDEFGHIJKL"[i], vec_s[i]);

        vec_s = vect_population;
        br33.shuffle(vec_s);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], vec_s[i]);

        br0.shuffle(arr_s);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("ABCDEFGHIJKLM"[i], arr_s[i]);

        arr_s = arr_population;
        br1.shuffle(arr_s);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("MABCDEFGHIJKL"[i], arr_s[i]);

        arr_s = arr_population;
        br33.shuffle(arr_s);
        for (int i = 0; i < 13; ++i)
            EXPECT_EQ("EAFGDHIBJKCLM"[i], arr_s[i]);

        EXPECT_THROW(br0.shuffle(std::map<int, Object>()), IndexableContainerException);


        //-- tests betavariate()
        // Notice: hard coded values here all come from same calls in PyRandLib. See README.md
        // br0
        for (double alpha : {0.13, 0.23, 1.00, 1.13, 2.23})
            for (double beta : {0.13, 0.23, 1.00, 1.13, 2.23})
                EXPECT_DOUBLE_EQ(0.0, br0.gammavariate(alpha, beta));

        // br1
        EXPECT_NEAR(0.16711240545381284, br1.betavariate(1.00, 0.20), 1.0e-6);
        EXPECT_DOUBLE_EQ(0.5, br1.betavariate(1.00, 1.00));
        EXPECT_NEAR(0.0038129414259181348, br1.betavariate(1.00, 2.23), 1.0e-6);
        EXPECT_DOUBLE_EQ(0.63924876589595836, br1.betavariate(0.13, 0.23));
        EXPECT_DOUBLE_EQ(0.36075123410404181, br1.betavariate(0.23, 0.13));
        EXPECT_DOUBLE_EQ(0.5, br1.betavariate(0.23, 0.23));
        EXPECT_NEAR(0.8328875945461871, br1.betavariate(0.20, 1.00), 1.0e-6);
        EXPECT_NEAR(0.0285419914624108, br1.betavariate(0.13, 2.23), 1.0e-6);
        EXPECT_NEAR(0.9999442127674986, br1.betavariate(1.13, 0.23), 1.0e-6);
        EXPECT_NEAR(0.9999871212259168, br1.betavariate(1.13, 1.00), 1.0e-6);
        EXPECT_DOUBLE_EQ(0.5, br1.betavariate(1.13, 1.13));
        EXPECT_NEAR(0.99664647140794072, br1.betavariate(1.13, 2.23), 1.0e-6);

        // br33
        EXPECT_NEAR(0.985732, br33.betavariate(1.00, 0.20), 1.0e-6);
        EXPECT_DOUBLE_EQ(0.5, br33.betavariate(1.00, 1.00));
        EXPECT_NEAR(0.208299, br33.betavariate(1.00, 2.23), 1.0e-6);
        EXPECT_NEAR(0.024890, br33.betavariate(0.13, 0.23), 1.0e-6);
        EXPECT_NEAR(0.975110, br33.betavariate(0.23, 0.13), 1.0e-6);
        EXPECT_NEAR(0.500000, br33.betavariate(0.23, 0.23), 1.0e-6);
        EXPECT_NEAR(0.014268, br33.betavariate(0.20, 1.00), 1.0e-6);
        EXPECT_NEAR(0.000199, br33.betavariate(0.13, 2.23), 1.0e-6);
        EXPECT_NEAR(0.980101, br33.betavariate(1.13, 0.23), 1.0e-6);
        EXPECT_NEAR(0.592979, br33.betavariate(1.13, 1.00), 1.0e-6);
        EXPECT_NEAR(0.500000, br33.betavariate(1.13, 1.13), 1.0e-6);
        EXPECT_NEAR(0.277096, br33.betavariate(1.13, 2.23), 1.0e-6);


        EXPECT_THROW(br0.betavariate(-0.23, 0.31), AlphaBetaArgsException);
        EXPECT_THROW(br1.betavariate(0.23, -0.31), AlphaBetaArgsException);
        EXPECT_THROW(br33.betavariate(-0.23, -0.31), AlphaBetaArgsException);


        //-- tests expovariate()
        BaseRandom1_0 br1_0;
        constexpr double LAMBDAS[] = { 0.10, 0.50, 1.00, 3.33, 20.0 };

        for (int i=0; i < 5; ++i)
            EXPECT_DOUBLE_EQ(0.0, br0.expovariate(LAMBDAS[i]));

        for (int i = 0; i < 5; ++i)
            EXPECT_DOUBLE_EQ(-std::log(1.0 - double(0xffff'ffffUL) / double(1ULL << 32)) / LAMBDAS[i], br1.expovariate(LAMBDAS[i]));
        
        for (int i=0; i<5; ++i)
            EXPECT_DOUBLE_EQ(0.0, br1_0.expovariate(LAMBDAS[i]));

        for (int i = 0; i < 5; ++i)
            EXPECT_DOUBLE_EQ(-std::log(1.0 - double(0x5555'5555UL) / double(1ULL << 32)) / LAMBDAS[i], br33.expovariate(LAMBDAS[i]));

        EXPECT_THROW(br0.expovariate(0.0), ExponentialZeroLambdaException);
        EXPECT_THROW(br1_0.expovariate(-0.00001), ExponentialZeroLambdaException);


        //-- tests gammavariate()
        // Notice: hard coded values here all come from same calls in PyRandLib. See README.md
        // br0
        for (double alpha : {0.13, 0.23, 1.00, 1.13, 2.23})
            for (double beta : {0.13, 0.23, 1.00, 1.13, 2.23})
                EXPECT_DOUBLE_EQ(0.0, br0.gammavariate(alpha, beta));

        // br1
        EXPECT_NEAR(22.133994234816, br1.gammavariate(0.13, 0.13), 1.0e-7);
        EXPECT_NEAR(39.160143646214, br1.gammavariate(0.13, 0.23), 1.0e-7);
        EXPECT_NEAR(170.26149411397, br1.gammavariate(0.13, 1.00), 1.0e-7);
        EXPECT_NEAR(192.39548834879, br1.gammavariate(0.13, 1.13), 1.0e-7);
        EXPECT_NEAR(379.68313187416, br1.gammavariate(0.13, 2.23), 1.0e-7);

        EXPECT_NEAR(12.491014706411, br1.gammavariate(0.23, 0.13), 1.0e-7);
        EXPECT_NEAR(22.099487557497, br1.gammavariate(0.23, 0.23), 1.0e-7);
        EXPECT_NEAR(96.084728510857, br1.gammavariate(0.23, 1.00), 1.0e-7);
        EXPECT_NEAR(108.57574321727, br1.gammavariate(0.23, 1.13), 1.0e-7);
        EXPECT_NEAR(214.26894457921, br1.gammavariate(0.23, 2.23), 1.0e-7);

        EXPECT_NEAR(2.8834922711298, br1.gammavariate(1.00, 0.13), 1.0e-7);
        EXPECT_NEAR(5.1015632489212, br1.gammavariate(1.00, 0.23), 1.0e-7);
        EXPECT_NEAR(22.180709777918, br1.gammavariate(1.00, 1.00), 1.0e-7);
        EXPECT_NEAR(25.064202049048, br1.gammavariate(1.00, 1.13), 1.0e-7);
        EXPECT_NEAR(49.462982804758, br1.gammavariate(1.00, 2.23), 1.0e-7);

        EXPECT_NEAR(223892.05033507, br1.gammavariate(1.13, 0.13), 1.0e-7);
        EXPECT_NEAR(396116.70443896, br1.gammavariate(1.13, 0.23), 1.0e-7);
        EXPECT_NEAR(1722246.5410390, br1.gammavariate(1.13, 1.00), 1.0e-7);
        EXPECT_NEAR(1946138.5913740, br1.gammavariate(1.13, 1.13), 1.0e-7);
        EXPECT_NEAR(3840609.7865169, br1.gammavariate(1.13, 2.23), 1.0e-7);

        EXPECT_NEAR(753.35478915882, br1.gammavariate(2.23, 0.13), 1.0e-7);
        EXPECT_NEAR(1332.8584731271, br1.gammavariate(2.23, 0.23), 1.0e-7);
        EXPECT_NEAR(5795.0368396832, br1.gammavariate(2.23, 1.00), 1.0e-7);
        EXPECT_NEAR(6548.3916288420, br1.gammavariate(2.23, 1.13), 1.0e-7);
        EXPECT_NEAR(12922.932152493, br1.gammavariate(2.23, 2.23), 1.0e-7);

        // br33
        EXPECT_NEAR(3.9796516918848e-5, br33.gammavariate(0.13, 0.13), 1.0e-7);
        EXPECT_NEAR(7.0409222241039e-5, br33.gammavariate(0.13, 0.23), 1.0e-7);
        EXPECT_NEAR(0.0003061270532, br33.gammavariate(0.13, 1.00), 1.0e-7);
        EXPECT_NEAR(0.0003459235701, br33.gammavariate(0.13, 1.13), 1.0e-7);
        EXPECT_NEAR(0.0006826633287, br33.gammavariate(0.13, 2.23), 1.0e-7);

        EXPECT_NEAR(0.0015590877717, br33.gammavariate(0.23, 0.13), 1.0e-7);
        EXPECT_NEAR(0.0027583860575, br33.gammavariate(0.23, 0.23), 1.0e-7);
        EXPECT_NEAR(0.0119929828589, br33.gammavariate(0.23, 1.00), 1.0e-7);
        EXPECT_NEAR(0.0135520706305, br33.gammavariate(0.23, 1.13), 1.0e-7);
        EXPECT_NEAR(0.0267443517753, br33.gammavariate(0.23, 2.23), 1.0e-7);

        EXPECT_NEAR(0.0527104640389, br33.gammavariate(1.00, 0.13), 1.0e-7);
        EXPECT_NEAR(0.0932569748381, br33.gammavariate(1.00, 0.23), 1.0e-7);
        EXPECT_NEAR(0.4054651079917, br33.gammavariate(1.00, 1.00), 1.0e-7);
        EXPECT_NEAR(0.4581755720307, br33.gammavariate(1.00, 1.13), 1.0e-7);
        EXPECT_NEAR(0.9041871908216, br33.gammavariate(1.00, 2.23), 1.0e-7);

        EXPECT_NEAR(0.0767924941018, br33.gammavariate(1.13, 0.13), 1.0e-7);
        EXPECT_NEAR(0.1358636434109, br33.gammavariate(1.13, 0.23), 1.0e-7);
        EXPECT_NEAR(0.5907114930907, br33.gammavariate(1.13, 1.00), 1.0e-7);
        EXPECT_NEAR(0.6675039871925, br33.gammavariate(1.13, 1.13), 1.0e-7);
        EXPECT_NEAR(1.3172866295924, br33.gammavariate(1.13, 2.23), 1.0e-7);

        EXPECT_NEAR(0.2003411261479, br33.gammavariate(2.23, 0.13), 1.0e-7);
        EXPECT_NEAR(0.3544496847232, br33.gammavariate(2.23, 0.23), 1.0e-7);
        EXPECT_NEAR(1.5410855857529, br33.gammavariate(2.23, 1.00), 1.0e-7);
        EXPECT_NEAR(1.7414267119008, br33.gammavariate(2.23, 1.13), 1.0e-7);
        EXPECT_NEAR(3.4366208562290, br33.gammavariate(2.23, 2.23), 1.0e-7);


        EXPECT_THROW(br0.gammavariate(-0.01, 1.00), AlphaBetaArgsException);
        EXPECT_THROW(br1.gammavariate(0.01, -1.00), AlphaBetaArgsException);
        EXPECT_THROW(br33.gammavariate(-0.01, -1.00), AlphaBetaArgsException);

        EXPECT_THROW(br0.gammavariate(0, 1.00), AlphaBetaArgsException);
        EXPECT_THROW(br1.gammavariate(0.01, 0), AlphaBetaArgsException);
        EXPECT_THROW(br33.gammavariate(0, 0), AlphaBetaArgsException);


        //-- test gauss()
        // Notice: hard coded values here all come from same calls in PyRandLib. See README.md
        br0.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_EQ(0.0, br0.gauss());
            EXPECT_TRUE(br0.gauss_valid());
            EXPECT_EQ(0.0, br0.gauss());
            EXPECT_FALSE(br0.gauss_valid());
        }

        br1.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_DOUBLE_EQ(6.6604368892615815, br1.gauss());
            EXPECT_TRUE(br1.gauss_valid());
            EXPECT_DOUBLE_EQ(-9.743673225226533e-09, br1.gauss());
            EXPECT_FALSE(br1.gauss_valid());
        }

        br33.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_DOUBLE_EQ(-0.45025831880534095, br33.gauss());
            EXPECT_TRUE(br33.gauss_valid());
            EXPECT_DOUBLE_EQ(0.7798702855796508, br33.gauss());
            EXPECT_FALSE(br33.gauss_valid());
        }


        //-- test gauss(mu, sigma)
        // Notice: hard coded values here all come from same calls in PyRandLib. See README.md
        br0.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_EQ(1.0, br0.gauss(1.0, 2.5));
            EXPECT_TRUE(br0.gauss_valid());
            EXPECT_EQ(1.0, br0.gauss(1.0, 2.5));
            EXPECT_FALSE(br0.gauss_valid());
        }

        br1.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_DOUBLE_EQ(17.651092223153952, br1.gauss(1.0, 2.5));
            EXPECT_TRUE(br1.gauss_valid());
            EXPECT_DOUBLE_EQ(0.9999999756408169, br1.gauss(1.0, 2.5));
            EXPECT_FALSE(br1.gauss_valid());
        }

        br33.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_DOUBLE_EQ(-0.12564579701335243, br33.gauss(1.0, 2.5));
            EXPECT_TRUE(br33.gauss_valid());
            EXPECT_DOUBLE_EQ(2.949675713949127, br33.gauss(1.0, 2.5));
            EXPECT_FALSE(br33.gauss_valid());
        }

        br0.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_EQ(-0.21, br0.gauss(-0.21, 0.17));
            EXPECT_TRUE(br0.gauss_valid());
            EXPECT_EQ(-0.21, br0.gauss(-0.21, 0.17));
            EXPECT_FALSE(br0.gauss_valid());
        }

        br1.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_DOUBLE_EQ(0.9222742711744689, br1.gauss(-0.21, 0.17));
            EXPECT_TRUE(br1.gauss_valid());
            EXPECT_DOUBLE_EQ(-0.21000000165642443, br1.gauss(-0.21, 0.17));
            EXPECT_FALSE(br1.gauss_valid());
        }

        br33.setstate(0);
        for (int i = 0; i < 2; ++i) {
            EXPECT_DOUBLE_EQ(-0.28654391419690795, br33.gauss(-0.21, 0.17));
            EXPECT_TRUE(br33.gauss_valid());
            EXPECT_DOUBLE_EQ(-0.07742205145145936, br33.gauss(-0.21, 0.17));
            EXPECT_FALSE(br33.gauss_valid());
        }

        EXPECT_THROW(br33.gauss(-0.21, -0.01), GaussSigmaException);


        //-- tests lognormvariate()
        // Notice: hard coded values here all come from same calls in PyRandLib. See README.md
        EXPECT_EQ(br0.lognormvariate(0.0, 1.0), br0.lognormvariate());
        EXPECT_EQ(br1.lognormvariate(0.0, 1.0), br1.lognormvariate());
        EXPECT_EQ(br33.lognormvariate(0.0, 1.0), br33.lognormvariate());

        EXPECT_DOUBLE_EQ(std::exp(0.0 + 1.0 * 6.67 * 0.0), br0.lognormvariate(0.0, 1.0));
        EXPECT_DOUBLE_EQ(std::exp(0.0 + 1.0 * 6.67 * double(0xffff'ffffULL) / double(1ULL << 32)), br1.lognormvariate(0.0, 1.0));
        EXPECT_DOUBLE_EQ(0.651236807947594, br33.lognormvariate(0.0, 1.0));

        EXPECT_DOUBLE_EQ(std::exp(1.0 + 2.5 * 6.67 * 0.0), br0.lognormvariate(1.0, 2.5));
        EXPECT_DOUBLE_EQ(std::exp(1.0 + 2.5 * 6.67 * double(0xffff'ffffULL) / double(1ULL << 32)), br1.lognormvariate(1.0, 2.5));
        EXPECT_DOUBLE_EQ(0.9303402899627329, br33.lognormvariate(1.0, 2.5));

        EXPECT_DOUBLE_EQ(std::exp(-0.21 + 0.17 * 6.67 * 0.0), br0.lognormvariate(-0.21, 0.17));
        EXPECT_DOUBLE_EQ(std::exp(-0.21 + 0.17 * 6.67 * double(0xffff'ffffULL) / double(1ULL << 32)), br1.lognormvariate(-0.21, 0.17));
        EXPECT_DOUBLE_EQ(0.7535876602573764, br33.lognormvariate(-0.21, 0.17));

        EXPECT_THROW(br33.lognormvariate(-0.21, -0.01), NormalSigmaException);


        //-- tests normalvariate()
        // Notice: hard coded values here all come from same calls in PyRandLib. See README.md
        EXPECT_EQ(br0.normalvariate(0.0, 1.0), br0.normalvariate());
        EXPECT_EQ(br1.normalvariate(0.0, 1.0), br1.normalvariate());
        EXPECT_EQ(br33.normalvariate(0.0, 1.0), br33.normalvariate());

        EXPECT_DOUBLE_EQ(0.0 + 1.0 * 6.67 * 0.0, br0.normalvariate(0.0, 1.0));
        EXPECT_DOUBLE_EQ(0.0 + 1.0 * 6.67 * double(0xffff'ffffULL) / double(1ULL << 32), br1.normalvariate(0.0, 1.0));
        EXPECT_DOUBLE_EQ(-0.4288819426301386, br33.normalvariate(0.0, 1.0));

        EXPECT_DOUBLE_EQ(1.0 + 2.5 * 6.67 * 0.0, br0.normalvariate(1.0, 2.5));
        EXPECT_DOUBLE_EQ(1.0 + 2.5 * 6.67 * double(0xffff'ffffULL) / double(1ULL << 32), br1.normalvariate(1.0, 2.5));
        EXPECT_DOUBLE_EQ(-0.07220485657534659, br33.normalvariate(1.0, 2.5));

        EXPECT_DOUBLE_EQ(-0.21 + 0.17 * 6.67 * 0.0, br0.normalvariate(-0.21, 0.17));
        EXPECT_DOUBLE_EQ(-0.21 + 0.17 * 6.67 * double(0xffff'ffffULL) / double(1ULL << 32), br1.normalvariate(-0.21, 0.17));
        EXPECT_DOUBLE_EQ(-0.2829099302471236, br33.normalvariate(-0.21, 0.17));

        EXPECT_THROW(br33.normalvariate(-0.21, -0.01), NormalSigmaException);


        //-- tests paretovariate()
        std::vector<double> alphas{ 0.5, 0.75, 1.0, 1.25, 1.50, 1.75, 2.00, 2.25, 2.50, 2.75, 3.00, 3.50, 4.00, 5.00 };

        for (double alpha : alphas) {
            EXPECT_EQ(1.0, br0.paretovariate(alpha));
            EXPECT_DOUBLE_EQ(std::pow(1.0 - double(0xffff'ffffULL) / double(1ULL << 32), -1.0 / alpha), br1.paretovariate(alpha));
            EXPECT_DOUBLE_EQ(std::pow(1.0 - double(0x5555'5555ULL) / double(1ULL << 32), -1.0 / alpha), br33.paretovariate(alpha));
        }

        for (double alpha : alphas) {
            EXPECT_EQ(1.0, br0.paretovariate(-alpha));
            EXPECT_DOUBLE_EQ(std::pow(1.0 - double(0xffff'ffffULL) / double(1ULL << 32), -1.0 / -alpha), br1.paretovariate(-alpha));
            EXPECT_DOUBLE_EQ(std::pow(1.0 - double(0x5555'5555ULL) / double(1ULL << 32), -1.0 / -alpha), br33.paretovariate(-alpha));
        }

        // Notice: hard coded values here all come from same calls in PyRandLib. See README.md
        std::vector<double> expected{
            1.8446744073709552e+19, 6981463658331.548 , 4294967296.0      , 50859008.46224668 ,
            2642245.949629131     , 319557.11536777776, 65536.0           , 19112.411784415082,
            7131.5502145218525    , 3183.4240650668435, 1625.4986772154357, 565.2938310009918 ,
            256.0                 , 84.44850628946526
        };
        for (auto alpha_it = alphas.cbegin(), expected_it = expected.cbegin(); alpha_it != alphas.cend(); ++alpha_it, ++expected_it)
            EXPECT_DOUBLE_EQ(*expected_it, br1.paretovariate(*alpha_it));

        expected = {
            5.421010862427522e-20 , 1.4323643994144677e-13, 2.3283064365386963e-10, 1.9662200074984027e-08,
            3.78465903274584e-07  , 3.1293310394578496e-06, 1.52587890625e-05     , 5.232202043780965e-05 ,
            0.00014022196716272393, 0.00031412717236558387, 0.0006151958251439813 , 0.0017689915317654432 ,
            0.00390625            , 0.011841535675862483

        };
        for (auto alpha_it = alphas.cbegin(), expected_it = expected.cbegin(); alpha_it != alphas.cend(); ++alpha_it, ++expected_it)
            EXPECT_DOUBLE_EQ(*expected_it, br1.paretovariate(-*alpha_it));

        expected = {
            2.249999999476131 , 1.7170713635634731, 1.499999999825377 , 1.3831618670937746,
            1.3103706970027502, 1.2607343232374941, 1.2247448713202995, 1.1974648710864466,
            1.176079022469908 , 1.1588659034539632, 1.1447142425089112, 1.1228242619562039,
            1.1066819196681128, 1.0844717711724488
        };
        for (auto alpha_it = alphas.cbegin(), expected_it = expected.cbegin(); alpha_it != alphas.cend(); ++alpha_it, ++expected_it)
            EXPECT_DOUBLE_EQ(*expected_it, br33.paretovariate(*alpha_it));

        expected = {
            0.44444444454792476, 0.5823869765812643, 0.6666666667442769, 0.7229811808657985,
            0.7631428284281156 , 0.7931885263756894, 0.8164965809752524, 0.8350975666557225,
            0.8502830004567883 , 0.8629126088010111, 0.8735804647701982, 0.8906113217199124,
            0.9036020036361431 , 0.9221079115031973
        };
        for (auto alpha_it = alphas.cbegin(), expected_it = expected.cbegin(); alpha_it != alphas.cend(); ++alpha_it, ++expected_it)
            EXPECT_DOUBLE_EQ(*expected_it, br33.paretovariate(-*alpha_it));


        EXPECT_THROW(br1.paretovariate(0.0), ParetoArgsValueException);


        //-- tests triangular()
        EXPECT_EQ(br0.triangular(0.0, 1.0, 0.5), br0.triangular());
        EXPECT_EQ(br1.triangular(0.0, 1.0, 0.5), br1.triangular());
        EXPECT_EQ(br33.triangular(0.0, 1.0, 0.5), br33.triangular());


        //-- tests triangular(low, high)
        double d_values[]{ -31.0, -1.0, 0.0, 1.2, 23.1 };
        int i_values[]{ -31, -1, 0, 1, 23 };

        for (double low : d_values)
            for (double high : d_values) {
                EXPECT_DOUBLE_EQ(br0.triangular(low, high, (low + high) / 2.0), br0.triangular(low, high));
                EXPECT_DOUBLE_EQ(br1.triangular(low, high, (low + high) / 2.0), br1.triangular(low, high));
                EXPECT_DOUBLE_EQ(br33.triangular(low, high, (low + high) / 2.0), br33.triangular(low, high));
            }

        for (int low : i_values)
            for (int high : i_values) {
                EXPECT_DOUBLE_EQ(br0.triangular(low, double(high), (low + high) / 2.0), br0.triangular(low, high));
                EXPECT_DOUBLE_EQ(br1.triangular(low, double(high), (low + high) / 2.0), br1.triangular(low, high));
                EXPECT_DOUBLE_EQ(br33.triangular(low, double(high), (low + high) / 2.0), br33.triangular(low, high));
            }

        for (short low : i_values)
            for (double high : d_values) {
                EXPECT_DOUBLE_EQ(br0.triangular(low, high, (low + high) / 2.0), br0.triangular(low, high));
                EXPECT_DOUBLE_EQ(br1.triangular(low, high, (low + high) / 2.0), br1.triangular(low, high));
                EXPECT_DOUBLE_EQ(br33.triangular(low, high, (low + high) / 2.0), br33.triangular(low, high));
            }

        for (float low : d_values)
            for (long high : i_values) {
                EXPECT_DOUBLE_EQ(br0.triangular(low, high, (double(low) + double(high)) / 2.0), br0.triangular(low, high));
                EXPECT_DOUBLE_EQ(br1.triangular(low, high, (double(low) + double(high)) / 2.0), br1.triangular(low, high), 1.0e-7);
                EXPECT_DOUBLE_EQ(br33.triangular(low, high, (double(low) + double(high)) / 2.0), br33.triangular(low, high), 1.0e-7);
            }


        //-- tests triangular(low, high, mode)
        double d_modes[]{ -32.0, -31.0, -5.0, 0.0, 0.7, 15.0, 23.1, 32.0 };
        int i_modes[]{ -32, -31, -5, 0, 1, 15, 23, 32 };

        // br0
        for (double low : d_values)
            for (double high : d_values)
                for (double mode : d_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - (mode - low) / (high - low))), br0.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (double high : d_values)
                for (int mode : i_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - (mode - low) / (high - low))), br0.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (int high : i_values)
                for (double mode : d_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - (mode - low) / (high - low))), br0.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (int high : i_values)
                for (int mode : i_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - (mode - low) / (high - low))), br0.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (double high : d_values)
                for (double mode : d_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - (mode - low) / (high - low))), br0.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (double high : d_values)
                for (int mode : i_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - (mode - low) / (high - low))), br0.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (int high : i_values)
                for (double mode : d_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - (mode - low) / (high - low))), br0.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (int high : i_values)
                for (int mode : i_modes) {
                    if (low == high || 0.0 <= double(mode - low) / double(high - low))
                        EXPECT_EQ(low, br0.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt(1.0 * (1.0 - double(mode - low) / double(high - low))), br0.triangular(low, high, mode));
                }

        // br1
        double u{ double(0xffff'ffffULL) / double(1ULL << 32) };

        for (double low : d_values)
            for (double high : d_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (double high : d_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (int high : i_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (int high : i_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (double high : d_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (double high : d_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (int high : i_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (int high : i_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br1.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br1.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br1.triangular(low, high, mode));
                }

        // br33
        u = double(0x5555'5555ULL) / double(1ULL << 32);

        for (double low : d_values)
            for (double high : d_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (double high : d_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (int high : i_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }

        for (double low : d_values)
            for (int high : i_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (double high : d_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (double high : d_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (int high : i_values)
                for (double mode : d_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }

        for (int low : i_values)
            for (int high : i_values)
                for (int mode : i_modes) {
                    double c{ double(mode - low) / double(high - low) };
                    if (low == high)
                        EXPECT_EQ(low, br33.triangular(low, high, mode));
                    else if (u > c)
                        EXPECT_DOUBLE_EQ(high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c)), br33.triangular(low, high, mode));
                    else
                        EXPECT_DOUBLE_EQ(low + (high - low) * std::sqrt(u * c), br33.triangular(low, high, mode));
                }


        //-- tests uniform()
        EXPECT_EQ(0.0f, br0.uniform<float>());
        EXPECT_EQ(0.0, br0.uniform());
        EXPECT_EQ(0.0L, br0.uniform<long double>());

        u = double(0xffff'ffff) / double(1ULL << 32);
        EXPECT_EQ(float(u), br1.uniform<float>());
        EXPECT_EQ(u, br1.uniform());
        EXPECT_EQ((long double)u, br1.uniform<long double>());

        u = double(0x5555'5555) / double(1ULL << 32);
        EXPECT_EQ(float(u), br33.uniform<float>());
        EXPECT_EQ(u, br33.uniform());
        EXPECT_EQ((long double)u, br33.uniform<long double>());

        EXPECT_THROW(br0.uniform<int>(), FloatingPointTypeException);
        EXPECT_THROW(br1.uniform<std::vector<double>>(), FloatingPointTypeException);
        EXPECT_THROW(br33.uniform<Object>(), FloatingPointTypeException);


        //-- test uniform(max)
        EXPECT_EQ(0, br0.uniform(101));
        EXPECT_EQ(0, br0.uniform<int>(101));
        EXPECT_EQ(0.0f, br0.uniform(101.0f));
        EXPECT_EQ(0LL, br0.uniform(0xffff'ffff'ffff'ffffLL));
        EXPECT_EQ(0.0L, br0.uniform<long double>(-157L));

        u = double(0xffff'ffff) / double(1ULL << 32);
        EXPECT_EQ(u * 101, br1.uniform(101));
        EXPECT_EQ(100, br1.uniform<int>(101));
        EXPECT_EQ(u * 101.0f, br1.uniform(101.0f));
        EXPECT_EQ(u * -1, br1.uniform(0xffff'ffff'ffff'ffffLL));
        EXPECT_EQ((long double)u * -157L, br1.uniform<long double>(-157L));

        u = double(0x5555'5555) / double(1ULL << 32);
        EXPECT_EQ(u * 101, br33.uniform(101));
        EXPECT_EQ(int(u * 101), br33.uniform<int>(101));
        EXPECT_EQ(u * 101.0f, br33.uniform(101.0f));
        EXPECT_EQ(u * -1, br33.uniform(0xffff'ffff'ffff'ffffLL));
        EXPECT_EQ((long double)u * -157L, br33.uniform<long double>(-157L));


        EXPECT_THROW(br0.uniform<Object>(101), ArithmeticValueTypeException);
        EXPECT_THROW(br1.uniform(Object()), MaxValueTypeException);
        EXPECT_THROW(br33.uniform<std::vector<int>>(Object()), ArithmeticValueTypeException);


        //-- test uniform(min, max)
        EXPECT_EQ(1.0, br0.uniform<double>(1.0f, 101));
        EXPECT_EQ(1, br0.uniform<int>(1, 101));
        EXPECT_EQ(1.0f, br0.uniform<float>(1.0f, 101.0));
        EXPECT_EQ(-1LL, br0.uniform<long long>(129, 0xffff'ffff'ffff'ffffLL));
        EXPECT_EQ(-157.0L, br0.uniform<long double>(-157.0L, 139.0L));

        u = double(0xffff'ffff) / double(1ULL << 32);
        EXPECT_EQ(1.0 + u * 100, br1.uniform<double>(1.0f, 101));
        EXPECT_EQ(100, br1.uniform<int>(1, 101));
        EXPECT_EQ(1.0 + float(u * 100.0), br1.uniform<float>(1.0f, 101.0));
        EXPECT_EQ(128, br1.uniform<long long>(129, 0xffff'ffff'ffff'ffffLL));
        EXPECT_EQ(-157.0L + (long double)u * 296.0L, br1.uniform<long double>(-157.0L, 139.0L));

        u = double(0x5555'5555) / double(1ULL << 32);
        EXPECT_EQ(1.0 + u * 100, br33.uniform<double>(1.0f, 101));
        EXPECT_EQ(1 + 33, br33.uniform<int>(1, 101));
        EXPECT_EQ(1.0 + float(u * 100.0), br33.uniform<float>(1.0f, 101.0));
        EXPECT_EQ((long long)(-1 + 130 * u), br33.uniform<long long>(129, 0xffff'ffff'ffff'ffffLL));
        EXPECT_EQ(-157.0L + (long double)u * 296.0L, br33.uniform<long double>(-157.0L, 139.0L));


        //-- tests vonmisesvariate()
        double mus[]{ 0.0, 0.8, 3.141592653 / 2, 2.6, 3.141592653 };
        double kappas[]{ 0.01, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 8.0 };

        for (double mu : mus) {
            EXPECT_EQ(0.0, br0.vonmisesvariate(mu, 0.0));
            for (double kap : kappas)
                EXPECT_EQ(mu, br0.vonmisesvariate(mu, kap));
        }

        u = double(0xffff'ffffULL) / double(1ULL << 32);
        for (double mu : mus) {
            EXPECT_NEAR(2 * 3.141592653, br1.vonmisesvariate(mu, 0.0), 1.0e-7);
            for (double kap : kappas)
                EXPECT_NEAR(mu + 3.141592653, br1.vonmisesvariate(mu, kap), 1.0e-7);
        }

        // Notice: hard coded expected values here below have been evaluated with PyRandLib
        u = double(0x5555'5555ULL) / double(1ULL << 32);
        EXPECT_NEAR(2.0943951019055, br33.vonmisesvariate(0.0            , 0.0), 1.0e-7);
        EXPECT_NEAR(5.5716486148173, br33.vonmisesvariate(0.0            , 0.5), 1.0e-7);
        EXPECT_NEAR(5.7362107270429, br33.vonmisesvariate(0.0            , 1.0), 1.0e-7);
        EXPECT_NEAR(5.8261542345922, br33.vonmisesvariate(0.0            , 1.5), 1.0e-7);
        EXPECT_NEAR(5.8834514689426, br33.vonmisesvariate(0.0            , 2.0), 1.0e-7);
        EXPECT_NEAR(5.9540007159598, br33.vonmisesvariate(0.0            , 3.0), 1.0e-7);
        EXPECT_NEAR(5.9970387621021, br33.vonmisesvariate(0.0            , 4.0), 1.0e-7);
        EXPECT_NEAR(6.0267227633299, br33.vonmisesvariate(0.0            , 5.0), 1.0e-7);
        EXPECT_NEAR(6.0487664484707, br33.vonmisesvariate(0.0            , 6.0), 1.0e-7);
        EXPECT_NEAR(6.0798640040855, br33.vonmisesvariate(0.0            , 8.0), 1.0e-7);
        EXPECT_NEAR(2.0943951019055, br33.vonmisesvariate(0.8            , 0.0), 1.0e-7);
        EXPECT_NEAR(0.0884633076377, br33.vonmisesvariate(0.8            , 0.5), 1.0e-7);
        EXPECT_NEAR(0.2530254198633, br33.vonmisesvariate(0.8            , 1.0), 1.0e-7);
        EXPECT_NEAR(0.3429689274126, br33.vonmisesvariate(0.8            , 1.5), 1.0e-7);
        EXPECT_NEAR(0.4002661617630, br33.vonmisesvariate(0.8            , 2.0), 1.0e-7);
        EXPECT_NEAR(0.4708154087802, br33.vonmisesvariate(0.8            , 3.0), 1.0e-7);
        EXPECT_NEAR(0.5138534549225, br33.vonmisesvariate(0.8            , 4.0), 1.0e-7);
        EXPECT_NEAR(0.5435374561503, br33.vonmisesvariate(0.8            , 5.0), 1.0e-7);
        EXPECT_NEAR(0.5655811412911, br33.vonmisesvariate(0.8            , 6.0), 1.0e-7);
        EXPECT_NEAR(0.5966786969059, br33.vonmisesvariate(0.8            , 8.0), 1.0e-7);
        EXPECT_NEAR(2.0943951019055, br33.vonmisesvariate(3.141592653 / 2, 0.0), 1.0e-7);
        EXPECT_NEAR(0.8592596341377, br33.vonmisesvariate(3.141592653 / 2, 0.5), 1.0e-7);
        EXPECT_NEAR(1.0238217463633, br33.vonmisesvariate(3.141592653 / 2, 1.0), 1.0e-7);
        EXPECT_NEAR(1.1137652539126, br33.vonmisesvariate(3.141592653 / 2, 1.5), 1.0e-7);
        EXPECT_NEAR(1.1710624882630, br33.vonmisesvariate(3.141592653 / 2, 2.0), 1.0e-7);
        EXPECT_NEAR(1.2416117352802, br33.vonmisesvariate(3.141592653 / 2, 3.0), 1.0e-7);
        EXPECT_NEAR(1.2846497814225, br33.vonmisesvariate(3.141592653 / 2, 4.0), 1.0e-7);
        EXPECT_NEAR(1.3143337826503, br33.vonmisesvariate(3.141592653 / 2, 5.0), 1.0e-7);
        EXPECT_NEAR(1.3363774677911, br33.vonmisesvariate(3.141592653 / 2, 6.0), 1.0e-7);
        EXPECT_NEAR(1.3674750234059, br33.vonmisesvariate(3.141592653 / 2, 8.0), 1.0e-7);
        EXPECT_NEAR(2.0943951019055, br33.vonmisesvariate(2.6            , 0.0), 1.0e-7);
        EXPECT_NEAR(1.8884633076377, br33.vonmisesvariate(2.6            , 0.5), 1.0e-7);
        EXPECT_NEAR(2.0530254198633, br33.vonmisesvariate(2.6            , 1.0), 1.0e-7);
        EXPECT_NEAR(2.1429689274126, br33.vonmisesvariate(2.6            , 1.5), 1.0e-7);
        EXPECT_NEAR(2.2002661617630, br33.vonmisesvariate(2.6            , 2.0), 1.0e-7);
        EXPECT_NEAR(2.2708154087802, br33.vonmisesvariate(2.6            , 3.0), 1.0e-7);
        EXPECT_NEAR(2.3138534549225, br33.vonmisesvariate(2.6            , 4.0), 1.0e-7);
        EXPECT_NEAR(2.3435374561503, br33.vonmisesvariate(2.6            , 5.0), 1.0e-7);
        EXPECT_NEAR(2.3655811412911, br33.vonmisesvariate(2.6            , 6.0), 1.0e-7);
        EXPECT_NEAR(2.3966786969059, br33.vonmisesvariate(2.6            , 8.0), 1.0e-7);
        EXPECT_NEAR(2.0943951019055, br33.vonmisesvariate(3.141592653    , 0.0), 1.0e-7);
        EXPECT_NEAR(2.4300559606377, br33.vonmisesvariate(3.141592653    , 0.5), 1.0e-7);
        EXPECT_NEAR(2.5946180728633, br33.vonmisesvariate(3.141592653    , 1.0), 1.0e-7);
        EXPECT_NEAR(2.6845615804126, br33.vonmisesvariate(3.141592653    , 1.5), 1.0e-7);
        EXPECT_NEAR(2.7418588147630, br33.vonmisesvariate(3.141592653    , 2.0), 1.0e-7);
        EXPECT_NEAR(2.8124080617802, br33.vonmisesvariate(3.141592653    , 3.0), 1.0e-7);
        EXPECT_NEAR(2.8554461079225, br33.vonmisesvariate(3.141592653    , 4.0), 1.0e-7);
        EXPECT_NEAR(2.8851301091503, br33.vonmisesvariate(3.141592653    , 5.0), 1.0e-7);
        EXPECT_NEAR(2.9071737942911, br33.vonmisesvariate(3.141592653    , 6.0), 1.0e-7);
        EXPECT_NEAR(2.9382713499059, br33.vonmisesvariate(3.141592653    , 8.0), 1.0e-7);


        EXPECT_THROW(br33.vonmisesvariate(1.7, -1), NegativeKappaException);


        //-- tests weibull
        alphas = { 0.0, 0.5, 1.0, 1.3, 1.6 };
        double betas[]{0.1, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0};

        for (double alpha : alphas)
            for (double beta : betas)
                EXPECT_EQ(0.0, br0.weibullvariate(alpha, beta));

        u = double(0xffff'ffffULL) / double(1ULL << 32);
        for (double alpha : alphas)
            for (double beta : betas)
                EXPECT_EQ(alpha * std::pow(-std::log(1.0 - u), 1.0 / beta), br1.weibullvariate(alpha, beta));

        u = double(0x5555'5555ULL) / double(1ULL << 32);
        for (double alpha : alphas)
            for (double beta : betas)
                EXPECT_EQ(alpha * std::pow(-std::log(1.0 - u), 1.0 / beta), br33.weibullvariate(alpha, beta));

        EXPECT_THROW(br0.weibullvariate(-1, -1), WeibullArgsValueException);
        EXPECT_THROW(br0.weibullvariate(-1, 0), WeibullArgsValueException);
        EXPECT_THROW(br0.weibullvariate(-1, 1), WeibullArgsValueException);
        EXPECT_THROW(br0.weibullvariate(0, -1), WeibullArgsValueException);
        EXPECT_THROW(br0.weibullvariate(0, 0), WeibullArgsValueException);
        EXPECT_THROW(br0.weibullvariate(1, -0.0001), WeibullArgsValueException);
        EXPECT_THROW(br0.weibullvariate(1, 0), WeibullArgsValueException);

    }
}
