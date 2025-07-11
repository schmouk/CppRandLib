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
#include "baseclasses/baselfib64.h"


//===========================================================================
/** @brief A fast 64-bits Lagged Fibonacci Generator with a short period (3.0e+23).
*
*   Lagged Fibonacci generators LFib( m, r, k, op) use the recurrence
*
*       x(i) = (x(i-r) op (x(i-k)) mod m
*
*   where op is an operation that can be:
*       + (addition),
*       - (substraction),
*       * (multiplication),
*       ^ (bitwise exclusive-or).
*
*   With the + or - operation, such generators are in fact MRGs. They offer very large
*   periods  with  the  best  known  results in the evaluation of their randomness, as
*   stated in the evaluation done by Pierre L'Ecuyer and Richard Simard (Universite de
*   Montreal)  in  "TestU01:  A  C  Library  for Empirical Testing  of  Random  Number
*   Generators - ACM Transactions  on  Mathematical  Software,  vol.33 n.4,  pp.22-40,
*   August 2007".  It  is  recommended  to  use  such pseudo-random numbers generators
*   rather than LCG ones for serious simulation applications.
*
*   The implementation of this LFib 64-bits model  is  based  on  a  Lagged  Fibonacci
*   generator (LFIB) that uses the recurrence
*
*       x(i) = ( x(i-5) + x(i-17) ) mod 2^64
*
*   and offers a period of about 2^78 - i.e. 3.0e+23 - with low computation  time  due
*   to the use of a 2^64 modulo and few memory space consumption (17 long integers).
*
*   Please notice that the TestUO1 article states that  the  operator  should  be  '*'
*   while Mascagni & Srinivasan  in their original article stated that the operator is
*   '+'.  We've implemented here the original operator: '+'.
*
*   See LFib116,  LFib668 and LFib1340 for long period LFib generators  (resp.  2^116,
*   2^668  and  2^1340  periods,  i.e. resp. 8.3e+34,  1.2e+201  and 2.4e+403 periods)
*   while same computation time and far higher precision (64-bits  calculations)  than
*   MRGs,  but memory consumption (resp. 55, 607 and 1279 integers).
*
*   Please notice that this class and all its  inheriting  sub-classes  are  callable.
*   Example:
* @code
*     LFib78 rand{};
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
* @endcode
* *
*   Notice that for simulating the roll of a dice you should program:
* @code
*     LFib78 diceRoll();
*     std::cout << 1 + int(diceRoll(6)) << std::endl;   // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode

*   Reminder:
*   We give you here below a copy of the table of tests for the LFibs that have
*   been  implemented in CppRandLib,  as provided in paper "TestU01, ..." - see
*   file README.md.
* +--------------------------------------------------------------------------------------------------------------------------------------------------------+
* | CppRandLib class | TU01 generator name      | Memory Usage    | Period  | time-32bits | time-64 bits | SmallCrush fails | Crush fails | BigCrush fails |
* | ---------------- | ------------------------ | --------------- | ------- | ----------- | ------------ | ---------------- | ----------- | -------------- |
* | LFib78           | LFib(2^64, 17, 5, +)     |    34 x 4-bytes | 2^78    |    n.a.     |     1.1      |          0       |       0     |       0        |
* | LFib116          | LFib(2^64, 55, 24, +)    |   110 x 4-bytes | 2^116   |    n.a.     |     1.0      |          0       |       0     |       0        |
* | LFib668          | LFib(2^64, 607, 273, +)  | 1,214 x 4-bytes | 2^668   |    n.a.     |     0.9      |          0       |       0     |       0        |
* | LFib1340         | LFib(2^64, 1279, 861, +) | 2,558 x 4-bytes | 2^1340  |    n.a.     |     0.9      |          0       |       0     |       0        |
* +--------------------------------------------------------------------------------------------------------------------------------------------------------+
*
*   * _small crush_ is a small set of simple tests that quickly tests some  of
*   the expected characteristics for a pretty good PRG;
*
*   * _crush_ is a bigger set of tests that test more deeply  expected  random
*   characteristics;
*
*   * _big crush_ is the ultimate set of difficult tests  that  any  GOOD  PRG
*   should definitively pass.
*/
using LFib78 = BaseLFib64<17, 5>;
