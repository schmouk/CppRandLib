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
#include "gtest/gtest.h"

#include "baseclasses/basesquares.h"


//===========================================================================
namespace tests_bases
{
    //-----------------------------------------------------------------------
    TEST(TestSuiteBases, TestsBaseSquares)
    {
        //-- tests empty constructor
        {
            for (int i = 0; i < 100'000; ++i) {
                BaseSquares<int> sqr;

                EXPECT_EQ(0, sqr._internal_state.state.counter);
                EXPECT_EQ(1, sqr._internal_state.state.key & 0x1);
            }
        }


        // notice: all hard coded belowing values have been evaluated with PyRandLib
        
        //-- tests Valued construtor (seed).
        {
            BaseSquares<unsigned long> sqr(1);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(1, sqr._internal_state.state.key & 0x1);
            EXPECT_EQ(0x9bd658ae46c9d5e3, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(-2);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0xfbe269a13c127d8f, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(9L);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0xbf4a3268dabe3f75, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(-11L);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x79465e8f732a18f5, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(17UL);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x86531bae9b4edf83, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(0x0123'4567'89ab'cdefLL);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x2c381b75cd1e96f3, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(-8'870'000'000'000'000'000LL);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x5d7f246839ae54f3, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(8'870'000'000'000'000'000ULL);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0xea49fd182c19435d, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(0.357);
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x69ef8b1a6eda9b27, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            BaseSquares<unsigned long> sqr(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x2c381b75cd1e96f3, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }

        EXPECT_THROW(BaseSquares<unsigned long>(-0.357), FloatValueRange01Exception);
        EXPECT_THROW(BaseSquares<unsigned long>(8.87e+18), FloatValueRange01Exception);


        //-- tests Valued constructor (full state).
        {
            CounterKeyState state;
            state.seed(17UL);
            BaseSquares<unsigned long> sqr(state);

            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x86531bae9b4edf83, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_next);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_valid);
        }


        //-- tests copy constructor
        {
            BaseSquares<unsigned long> sqr_129(129);
            BaseSquares<unsigned long> sqr(sqr_129);

            EXPECT_EQ(sqr_129._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_129._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_129._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_129._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests move constructor
        {
            BaseSquares<unsigned long> sqr_129(129), sqr_tmp(sqr_129);
            BaseSquares<unsigned long> sqr(std::move(sqr_tmp));

            EXPECT_EQ(sqr_129._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_129._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_129._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_129._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests copy assignment
        {
            BaseSquares<unsigned long> sqr_129(129);
            BaseSquares<unsigned long> sqr;
            sqr = sqr_129;

            EXPECT_EQ(sqr_129._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_129._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_129._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_129._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests move assignment
        {
            BaseSquares<unsigned long> sqr_129(129);
            BaseSquares<unsigned long> sqr;
            sqr = std::move(sqr_129);

            EXPECT_EQ(sqr_129._internal_state.state.counter, sqr._internal_state.state.counter);
            EXPECT_EQ(sqr_129._internal_state.state.key, sqr._internal_state.state.key);
            EXPECT_EQ(sqr_129._internal_state.gauss_next, sqr._internal_state.gauss_next);
            EXPECT_EQ(sqr_129._internal_state.gauss_valid, sqr._internal_state.gauss_valid);
        }


        //-- tests _setstate()
        BaseSquares<unsigned long> sqr;
        {
            sqr._setstate(0x0123'4567'89ab'cdefLL);

            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x2c381b75cd1e96f3, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }
        {
            sqr._setstate(utils::UInt128(0xfedc'ba98'7654'3210ULL, 0x0123'4567'89ab'cdefULL));
            EXPECT_EQ(0, sqr._internal_state.state.counter);
            EXPECT_EQ(0x2c381b75cd1e96f3, sqr._internal_state.state.key);
            EXPECT_FALSE(sqr._internal_state.gauss_valid);
            EXPECT_DOUBLE_EQ(0.0, sqr._internal_state.gauss_next);
        }

    }

}
