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
#include <cstdint>

#include "gtest/gtest.h"

#include "exceptions.h"


//===========================================================================
namespace tests_cpprl
{

    //-----------------------------------------------------------------------
    TEST(TestSuiteCpprl, TestsExceptions)
    {
        //-- tests BaseException
        {
            BaseException<double> be;
            EXPECT_FALSE(be._inited);
            EXPECT_EQ(0.0, be._value);
            EXPECT_EQ(0.0, be._value2);
            EXPECT_EQ(0.0, be._value3);
        }
        {
            BaseException<int> be;
            EXPECT_FALSE(be._inited);
            EXPECT_EQ(0, be._value);
            EXPECT_EQ(0, be._value2);
            EXPECT_EQ(0, be._value3);
        }
        {
            BaseException<float> be;
            EXPECT_FALSE(be._inited);
            EXPECT_EQ(0.0f, be._value);
            EXPECT_EQ(0.0f, be._value2);
            EXPECT_EQ(0.0f, be._value3);
        }
        {
            BaseException<double> be(1.234);
            EXPECT_TRUE(be._inited);
            EXPECT_EQ(1.234, be._value);
            EXPECT_EQ(0.0, be._value2);
            EXPECT_EQ(0.0, be._value3);
        }
        {
            BaseException<float> be(1.234f, 5.678f);
            EXPECT_TRUE(be._inited);
            EXPECT_EQ(1.234f, be._value);
            EXPECT_EQ(5.678f, be._value2);
            EXPECT_EQ(0.0, be._value3);
        }
        {
            BaseException<std::int64_t> be(0x1234'5678'9abc'def0, 0xfedc'ba98'7654'3201, 0x753a'8624'91bc'de0f);
            EXPECT_TRUE(be._inited);
            EXPECT_EQ(0x1234'5678'9abc'def0, be._value);
            EXPECT_EQ(0xfedc'ba98'7654'3201, be._value2);
            EXPECT_EQ(0x753a'8624'91bc'de0f, be._value3);
        }

        //-- tests AlphaBetaArgsException
        {
            AlphaBetaArgsException aba;
            EXPECT_STREQ("both arguments alpha and beta must be greater than 0.0.", aba.what());
        }
        {
            AlphaBetaArgsException aba(-0.23, 0.31);
            EXPECT_STREQ("both arguments alpha (-0.230000) and beta (0.310000) must be greater than 0.0.", aba.what());
        }

        //-- tests ChoiceEmptySequenceException
        {
            ChoiceEmptySequenceException ces;
            EXPECT_STREQ("cannot make a choice from an empty sequence.", ces.what());
        }

        //-- tests ExponentialZeroLambdaException
        {
            ExponentialZeroLambdaException ezl;
            EXPECT_STREQ("lambda value cannot be 0.0 (currently is).", ezl.what());
        }

        //-- tests FloatValueRange01Exception
        {
            FloatValueRange01Exception fvr01;
            EXPECT_STREQ("Float value is out of range [0.0, 1.0).", fvr01.what());
        }
        {
            FloatValueRange01Exception fvr01(1.0);
            EXPECT_STREQ("Float value (1.000000) is out of range [0.0, 1.0).", fvr01.what());
        }

        //-- tests GaussSigmaException
        {
            GaussSigmaException gs;
            EXPECT_STREQ("value for argument sigma must be greater than 0.0.", gs.what());
        }
        {
            GaussSigmaException gs(0.0);
            EXPECT_STREQ("value for argument sigma (0.000000) must be greater than 0.0.", gs.what());
        }

        //-- tests NegativeKappaException
        {
            NegativeKappaException nk;
            EXPECT_STREQ("'kappa' parameter cannot be negative.", nk.what());
        }
        {
            NegativeKappaException nk(-2.1);
            EXPECT_STREQ("'kappa' parameter (-2.100000) cannot be negative.", nk.what());
        }

        //-- tests NegativeRotationException
        {
            NegativeRotationException nr;
            EXPECT_STREQ("rotation bits count cannot be negative.", nr.what());
        }
        {
            NegativeRotationException nr(-2);
            EXPECT_STREQ("rotation bits count (-2) cannot be negative.", nr.what());
        }

        //-- tests NormalSigmaException
        {
            NormalSigmaException ns;
            EXPECT_STREQ("value for argument sigma must be greater than 0.0.", ns.what());
        }
        {
            NormalSigmaException ns(0.0);
            EXPECT_STREQ("value for argument sigma (0.000000) must be greater than 0.0.", ns.what());
        }

        //-- tests ParetoArgsValueException
        {
            ParetoArgsValueException pv;
            EXPECT_STREQ("shape argument 'alpha' must not be 0.0 (actually is).", pv.what());
        }

        //-- tests PositiveValueException
        {
            PositiveValueException pv;
            EXPECT_STREQ("argument value must not be negative (actually is).", pv.what());
        }
        {
            PositiveValueException pv(-1);
            EXPECT_STREQ("argument value (-1) must not be negative.", pv.what());
        }

        //-- tests ProbaOutOfRangeException
        {
            ProbaOutOfRangeException poor;
            EXPECT_STREQ("probabilitiy values must range in [0.0, 1.0].", poor.what());
        }
        {
            ProbaOutOfRangeException poor(1.2);
            EXPECT_STREQ("probabilitiy values must range in [0.0, 1.0] (actually is 1.200000).", poor.what());
        }

        //-- tests RangeIncoherentValuesException
        {
            RangeIncoherentValuesException<> riv;
            EXPECT_STREQ("'stop' value will never be reached associated with 'start' and 'step' arguments.", riv.what());
        }
        {
            RangeIncoherentValuesException<double, int> riv(1.2, 2.5, 0);
            EXPECT_STREQ("'stop' value (2.500000) will never be reached associated with 'start' (1.200000) and 'step' (0) arguments.", riv.what());
        }
        {
            RangeIncoherentValuesException<long, float> riv(3, 5, -1.0f);
            EXPECT_STREQ("'stop' value (5) will never be reached associated with 'start' (3) and 'step' (-1.000000) arguments.", riv.what());
        }

        //-- tests RangeSameValuesException
        {
            RangeSameValuesException<> rsv;
            EXPECT_STREQ("'start' and 'stop' arguments must be different.", rsv.what());
        }
        {
            RangeSameValuesException<> rsv(2, 2);
            EXPECT_STREQ("'start' (2) and 'stop' (2) arguments must be different.", rsv.what());
        }
        {
            RangeSameValuesException<float> rsv(3.5f, 3.5f);
            EXPECT_STREQ("'start' (3.500000) and 'stop' (3.500000) arguments must be different.", rsv.what());
        }

        //-- tests RangeZeroStepException
        {
            RangeZeroStepException rzs;
            EXPECT_STREQ("'step' argument cannot be 0 (actually is).", rzs.what());
        }

        //-- tests SampleCountException
        {
            SampleCountException sc;
            EXPECT_STREQ("cannot sample a number of items that is greater than the overall population.", sc.what());
        }
        {
            SampleCountException sc(15, 11);
            EXPECT_STREQ("cannot sample a number of items (15) that is greater than the overall population (11).", sc.what());
        }

        //-- tests SampleSizesException
        {
            SampleSizesException sse;
            EXPECT_STREQ("sizes of arguments 'population' and 'counts' must be the same.", sse.what());
        }
        {
            SampleSizesException sse(15, 11);
            EXPECT_STREQ("sizes of arguments 'population' (15) and 'counts' (11) must be the same.", sse.what());
        }

        //-- tests StepValueTypeException
        {
            StepValueTypeException svt;
            EXPECT_STREQ("Type of 'step' values must be arithmetic.", svt.what());
        }

        //-- tests TooBigRotationException
        {
            TooBigRotationException<> tbr;
            EXPECT_STREQ("rotation bits count is too big (must not exceed the rotated integer size).", tbr.what());
        }
        {
            TooBigRotationException<> tbr(65);
            EXPECT_STREQ("rotation bits count (65) is too big (must not exceed the rotated integer size: 64).", tbr.what());
        }
        {
            TooBigRotationException<long> tbr(48);
            EXPECT_STREQ("rotation bits count (48) is too big (must not exceed the rotated integer size: 32).", tbr.what());
        }
        {
            TooBigRotationException<std::uint8_t> tbr(9);
            EXPECT_STREQ("rotation bits count (9) is too big (must not exceed the rotated integer size: 8).", tbr.what());
        }

        //-- tests WeibullArgsValueException
        {
            WeibullArgsValueException wav;
            EXPECT_STREQ("shape argument 'beta' must not be 0.0 (actually is).", wav.what());
        }

        //-- tests WeibullArgsValueException
        {
            WeibullArgsValueException wav;
            EXPECT_STREQ("shape argument 'beta' must not be 0.0 (actually is).", wav.what());
        }

        //-- tests ZeroLengthException
        {
            ZeroLengthException zl;
            EXPECT_STREQ("length or count argument value must not be zero (actually is).", zl.what());
        }

        //-- tests ZeroValueException
        {
            ZeroValueException zv;
            EXPECT_STREQ("argument value must not be zero (actually is).", zv.what());
        }

    }

}
