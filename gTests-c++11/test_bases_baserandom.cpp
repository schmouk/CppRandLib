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
#include <cstdint>
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

        inline const bool operator<= (const Object& other) const { return true; }
        inline const bool operator<= (const int rhs) const { return true; }
        inline const bool operator<= (const unsigned int rhs) const { return true; }
        inline const bool operator<= (const double rhs) const { return true; }
        inline const bool operator<= (const long double rhs) const { return true; }

        inline const bool operator< (const Object& other) const { return true; }
        inline const bool operator< (const int rhs) const { return true; }
        inline const bool operator< (const unsigned int rhs) const { return true; }
        inline const bool operator< (const double rhs) const { return true; }
        inline const bool operator< (const long double rhs) const { return true; }

        friend inline const bool operator<= (const int lhs, const Object& rhs) { return false; };
        friend inline const bool operator<= (const float lhs, const Object& rhs) { return false; };

        inline const int operator+ (const int rhs) const { return 0; }
        inline const unsigned int operator+ (const unsigned int rhs) { return 0; }
        inline const double operator+ (const double rhs) const { return 0.0; }
        inline const double operator+ (const long double rhs) const { return 0.0; }
        inline const int operator+ (const Object& rhs) const { return 0; }

        inline const int operator- (const Object& other) { return 0; }

        inline const double operator* (const double rhs) { return 0.0; }
        inline const double operator* (const long double rhs) { return 0.0; }
        inline const double operator* (const Object& rhs) { return 0.0; }

        inline operator int() const { return 0; }
        inline operator unsigned int() const { return 0; }
        inline operator float() const { return 0.0f; }
        inline operator double() const { return 0.0; }
        inline operator long double() const { return 0.0L; }
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
        EXPECT_NEAR(0.0L, br0.random<long double>(), 1.0e-20L);

        EXPECT_FLOAT_EQ(1.0f, br1.random<float>());
        EXPECT_NEAR(1.0, br1.random<double>(), 1.0e-9);
        EXPECT_NEAR(1.0L, br1.random<long double>(), 1.0e-9L);

        EXPECT_FLOAT_EQ(0.333333333f, br33.random<float>());
        EXPECT_NEAR(1.0 / 3.0, br33.random<double>(), 1.0e-9);
        EXPECT_NEAR(1.0L / 3.0L, br33.random<long double>(), 1.0e-9L);


        //-- tests operator()
        EXPECT_FLOAT_EQ(0.0f, br0.operator()<float>());
        EXPECT_DOUBLE_EQ(0.0, br0.operator()<double>());
        EXPECT_NEAR(0.0L, br0.operator()<long double>(), 1.0e-20L);

        EXPECT_FLOAT_EQ(1.0f, br1.operator()<float>());
        EXPECT_NEAR(1.0, br1.operator()<double>(), 1.0e-9);
        EXPECT_NEAR(1.0L, br1.operator()<long double>(), 1.0e-9L);

        EXPECT_FLOAT_EQ(0.333333333f, br33.operator()<float>());
        EXPECT_NEAR(1.0 / 3.0, br33.operator()<double>(), 1.0e-9);
        EXPECT_NEAR(1.0L / 3.0L, br33.operator()<long double>(), 1.0e-9L);


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


        //-- tests



        int DBG{ 0 };
    }
}
