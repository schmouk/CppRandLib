<img src="lib-banner.jpg" alt="Library banner">

[![license](http://img.shields.io/github/license/schmouk/cpprandlib.svg?style=plastic&labelColor=blueviolet&color=lightblue)](https://github.com/schmouk/cpprandlib/license)  [![Latest release](http://img.shields.io/github/release/schmouk/cpprandlib.svg?style=plastic&labelColor=blueviolet&color=success)](https://github.com/schmouk/cpprandlib/releases)  [![code_coverage](https://img.shields.io/badge/code_coverage-100%25-success?style=plastic&labelColor=blueviolet)]()  [![tests](https://img.shields.io/badge/tests-passed-success?style=plastic&labelColor=blueviolet)]()
Many best in class pseudo random generators grouped into one simple library - c++11 and c++20 versions.

This is a c++ counterpart of library PyRandLib (Python).

CppRandLib github web pages are here: [https://schmouk.github.io/CppRandLib/](https://schmouk.github.io/CppRandLib/)

---
## License
**CppRandLib** is distributed under the MIT license for its largest use.  
If you decide to use this library, please mention it and add the copyright notice to your software as stated in the LICENSE file.

```
Copyright (c) 2022-2025 Philippe Schmouker, <ph.schmouker (at) gmail.com>

Permission is hereby granted,  free of charge,  to any person obtaining a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction, including  without  limitation the rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies of the Software,  and  to  permit  persons  to  whom  the  Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND,  EXPRESS  OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  TORT OR OTHERWISE, ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```



---
## Intro
This library implements some of the best-in-class pseudo-random generators as evaluated by Pierre L'Ecuyer and Richard Simard in their famous paper "TestU01:  A C library for empirical testing of random  number generators" (ACM Trans. Math. Softw. Vol. 33 N.4, August 2007 -  see reference [1]. The reader might then want to take the benefit of reading L'Ecuyer & Simard's paper.

The latest release of **CppRandLib** is version **2.0**, released by June 2025. It provides additional implementations of recent pseudo-random generators with very good randomness characteristics. It provides also implementations dedicated to different standards of c++: c++11 and c++20. Time performances of every PRNG have been evaluated and are provided in a table below - see section *CPU Performances*. 

Each of the Pseudo Random Numbers Generators (PRNGs) implemented in **CppRandLib** is self documented. Names of classes directly refer to the type of PRNG they implement augmented with some number characterizing their periodicity. All of their randomness characteristics are explained in every related module.

Exhaustive list of currently implemented algorithms (CppRandLib 2.0, 2025/06):
* **Collatz-Weyl Generator** (2023)  
 (CWG, 64 bits, 128 bits or 128/64 bits, 3 different values of periodicities, see reference [8]);
* **Linear Congruential Generator**  
 (LCG, or FastRand, 32 bits or 63 bits, 2 different values of periodicities, see reference [1]);
* **Lagged Fibonacci Generator** (1985)  
 (LFib, 64 bits, 4 different periodicities, see reference [4]);
* **Maximally Equidistributed Long-period Linear Generator** (2018)  
 (MELG, 64/32 bits, 3 different values of periodicities, see reference [11]);
* **Multiple Recursive Generator** (2000, 2005)  
 (MRG, 31 bits or 32 bits, 3 different values of periodicities, see references [2] and [3]);
* **Permutated Congruential Generator** (2014)  
 (PCG, 64, 128 bits or 64/32 bits, 3 different values of periodicities, see reference [7]);
* **Squares** (2022)  
 (Squares, 32 or 64 bits, 1 value of periodicity but 32- or 64-bits output values, see reference [9]);
* **Well-Equilibrated Long-period Linear generators** (2006)  
 (WELL, 32 bits, 4 different values of periodicities, see reference [6]);
* **Scrambled Linear Pseudorandom Number Generators** (2018)  
 (Xoroshiro, 64 bits, 4 different values of periodicities, see reference [10]).
 


### Why not Mersenne twister?

The Mersenne Twister PRNG (MT) proposed by Matsumoto and Nishimura - see [5] - is currently the most widely used PRNG algorithm. The c++ STL implements this PRNG as the standard default one. It is also implemented in Python and Java standard libraries for instance.

MT offers a very good period (2^19937, i.e. about 4.3e+6,001). Unfortunately, this PRNG is a little bit long to compute (up to 3 times than LCGs, or 60% more than LFibs, see below  at section 'Architecture overview'). It embeds an internal state of 624 32-bits integers, which is larger to far larger than some other PRNGs. Moreover, MT fails four of the hardest TestU01 tests. You can still use it as your preferred PRNG but **CppRandLib** implements many other PRNGs that are either far faster, or that are far better in terms of generated pseudo-randomness than the Mersenne twister PRNG while consuming less memory space.


---
## Installation
Currently, the only way to install **CppRandLib** is to download the .zip or .tar.gz archive, then to directly put sub-directory `c++11` or `c++20` from archive into your project directory.  
See [CppRandLib repository](https://schmouk.github.io/CppRandLib/) for an easy access to download versions or click on link [**Releases**](https://github.com/schmouk/CppRandLib/releases) on the home page of GitHub repository.



---
## Randomness evaluation
In [1], every known PRNG at the time of the editing (2007) has been tested according to three different sets of tests:
* **_small crush_** is a small set of simple tests that quickly tests  some of the expected characteristics for a pretty good PRNG;
* **_crush_** is a bigger set of tests that test  more  deeply expected  random characteristics;
* **_big crush_** is the ultimate set of difficult tests that any **good**  PRNG should definitively pass.

We give you here below a copy of the resulting table for the PRNGs that have been implemented in **CppRandLib**, as provided in [1], plus the Mersenne twister one which is not implemented in **CppRandLib**. Times present in this table are the measured ones in [1] by the time of their evaluations (i.e. 2007).  
We add in this table the evaluations provided by the authors of every new PRNGs that have been published after the publication of [1]. Some fields may be missing for them in the belowing table, then.  
Notice: a comparison of the computation times for all implemented PRNGs in **CppRandLib** is provided in an another table - see next subsection.

 | CppRandLib class | TU01 generator name (1)            | Memory Usage    | Period   | SmallCrush fails | Crush fails | BigCrush fails | time-64 bits | time-32bits |
 | ---------------- | ---------------------------------- | --------------- | -------- | ---------------- | ----------- | -------------- | ------------ | ----------- |
 | Cwg64            | *CWG64*                            |     8 x 4-bytes | >= 2^70  |          0       |       0     |       0        |     n.a.     |    n.a.     |
 | Cwg128_64        | *CWG128-64*                        |    10 x 4-bytes | >= 2^71  |          0       |       0     |       0        |     n.a.     |    n.a.     |
 | Cwg128           | *CWG128*                           |    16 x 4-bytes | >= 2^135 |          0       |       0     |       0        |     n.a.     |    n.a.     |
 | FastRand32       | LCG(2^32, 69069, 1)                |     1 x 4-bytes | 2^32     |         11       |     106     |   *too many*   |     0.67     |    3.20     |
 | FastRand63       | LCG(2^63, 9219741426499971445, 1)  |     2 x 4-bytes | 2^63     |          0       |       5     |       7        |     0.75     |    4.20     |
 | LFib78           | LFib(2^64, 17, 5, +)               |    34 x 4-bytes | 2^78     |          0       |       0     |       0        |     1.1      |    n.a.     |
 | LFib116          | LFib(2^64, 55, 24, +)              |   110 x 4-bytes | 2^116    |          0       |       0     |       0        |     1.0      |    n.a.     |
 | LFib668          | LFib(2^64, 607, 273, +)            | 1,214 x 4-bytes | 2^668    |          0       |       0     |       0        |     0.9      |    n.a.     |
 | LFib1340         | LFib(2^64, 1279, 861, +)           | 2,558 x 4-bytes | 2^1,340  |          0       |       0     |       0        |     0.9      |    n.a.     |
 | Melg607          | *Melg607-64*                       |    21 x 4-bytes | 2^607    |          0       |       0     |       0        |     n.a.     |    n.a      |
 | Melg19937        | *Melg19937-64*                     |   625 x 4-bytes | 2^19,937 |          0       |       0     |       0        |     n.a.     |    n.a      |
 | Melg44497        | *Melg44497-64*                     | 1,392 x 4-bytes | 2^44,497 |          0       |       0     |       0        |     n.a.     |    n.a      |
 | Mrg287           | Marsa-LFIB4                        |   256 x 4-bytes | 2^287    |          0       |       0     |       0        |     0.8      |    3.40     |
 | Mrg1457          | DX-47-3                            |    47 x 4-bytes | 2^1,457  |          0       |       0     |       0        |     1.4      |    n.a.     |
 | Mrg49507         | DX-1597-2-7                        | 1,597 x 4-bytes | 2^49,507 |          0       |       0     |       0        |     1.4      |    n.a.     |
 | Pcg64_32         | *PCG XSH RS 64/32 (LCG)*           |     2 x 4 bytes | 2^64     |          0       |       0     |       0        |     n.a.     |    n.a.     |
 | Pcg128_64        | *PCG XSL RR 128/64 (LCG)*          |     4 x 4 bytes | 2^128    |          0       |       0     |       0        |     n.a.     |    n.a.     |
 | Pcg1024_32       | *PCG XSH RS 64/32 (EXT 1024)*      | 1,026 x 4 bytes | 2^32,830 |          0       |       0     |       0        |     n.a.     |    n.a.     | 
 | Squares32        | *squares32*                        |     4 x 4-bytes | 2^64     |          0       |       0     |       0        |     n.a.     |    n.a.     |
 | Squares64        | *squares64*                        |     4 x 4-bytes | 2^64     |          0       |       0     |       0        |     n.a.     |    n.a.     |
 | Well512a         | not available                      |    16 x 4-bytes | 2^512    |        n.a.      |     n.a.    |     n.a.       |     n.a.     |    n.a.     |
 | Well1024a        | WELL1024a                          |    32 x 4-bytes | 2^1,024  |          0       |       4     |       4        |     1.1      |    4.0      |
 | Well19937c (2)   | WELL19937a                         |   624 x 4-bytes | 2^19,937 |          0       |       2     |       2        |     1.3      |    4.3      |
 | Well44497b (3)   | not available                      | 1,391 x 4-bytes | 2^44,497 |        n.a.      |     n.a.    |     n.a.       |     n.a.     |    n.a.     |
 | Mersenne Twister | MT19937                            |   624 x 4-bytes | 2^19,937 |          0       |       2     |       2        |     1.6      |    4.30     |
 | Xoroshiro256     | *xiroshiro256***                   |    16 x 4-bytes | 2^256    |          0       |       0     |       0        |     0.84     |    n.a.     |
 | Xoroshiro512     | *xiroshiro512***                   |    32 x 4-bytes | 2^512    |          0       |       0     |       0        |     0.99     |    n.a.     |
 | Xoroshiro1024    | *xiroshiro1024***                  |    64 x 4-bytes | 2^1,024  |          0       |       0     |       0        |     1.17     |    n.a.     |

(1) *or the generator original name in the related more recent paper*  
(2) The Well19937c generator provided with library CppRandLib implements the Well19937a algorithm augmented with an associated *tempering* algorithm - see [6] p.9.  
(3) The Well44497b generator provided with library CppRandLib implements the Well44497a algorithm augmented with an associated *tempering* algorithm - see [6] p.9.


---
## CPU Performances - Times evaluation

The above table provides times related to the C implementation of the specified PRNGs as measured with TestU01 [1] by the authors of the paper.  
We provide in the table below the evaluation of times spent in calling method `next()` for all PRNGs implemented in library **CppRandLib**. Doing so, the measured elapsed time eventually includes the calling and returning c++ mechanisms and not only the computation time of the sole algorithm code. This is the duration of interest to you since this is the main use that you will have of the library. It only helps comparing the performances between the implemented PRNGs.  
Notice: times are similar btw. the c++11 and c++20 versions of the code, except for *FastRand63* which has proven to be 33% slower for the c++20 version of the code than for the c++11 version (we don't know why) and for *Squares64* which is 18% faster for the c++20 version.  
Notice also: some of the PRNG algorithms involve 128-bits integer artihemtics. **CppRandLib** provides its own minimalist library for such computations since not all c++ compilers provide it (e.g. Microsoft compiler). Meanwhile, some other c++ compilers do implement 128-bits integer arithmetics (e.g. gcc). It might be of interest for users aware of this that they modify **CppRandLib** code by their side to take benefit of this. Conditional code is currently not implemented in **CppRandLib**.

Time unit is nanosecond. Tests have been run on an Intel&reg; Core&trade; 7 150U @ 1.80 GHz, 10 cores, 64-bits, with 16 GB RAM (5,600 MHz) and over Microsoft Windows 11 ed. Family (build 26100.4061, 18 Apr. 2025).  
Measures have been done with 32 bits and 64 bits generated code versions, in fully optimized mode and on the same 64 bits CPU.

The evaluation source code file is provided in subdirectories `c++11/testCPUPerfs` and `c++20/testCPUPerfs` and is named `testCPUPerfs.cpp`. You'll have to install **gTests** Google library to be able to use it.

**CppRandLib** time 64 bits and 32 bits table:

 | CppRandLib class | 64-bits |  32-bits  | SmallCrush fails | Crush fails | BigCrush fails |
 | ---------------- | ------- | --------- | ---------------- | ----------- | -------------- |
 | Cwg64            |   1.52  |    2.74   |        *0*       |      *0*    |      *0*       |
 | Cwg128_64        |   2.54  |    7.32   |        *0*       |      *0*    |      *0*       |
 | Cwg128           |   4.60  |   29.64   |        *0*       |      *0*    |      *0*       |
 | FastRand32       |   0.75  |    1.68   |       *11*       |    *106*    |   *too many*   |
 | FastRand63       |   1.14  |    1.89   |        *0*       |      *5*    |      *7*       |
 | LFib78           |   1.96  |    3.16   |        *0*       |      *0*    |      *0*       |
 | LFib116          |   2.54  |    3.16   |        *0*       |      *0*    |      *0*       |
 | LFib668          |   1.97  |    3.16   |        *0*       |      *0*    |      *0*       |
 | LFib1340         |   2.55  |    3.17   |        *0*       |      *0*    |      *0*       |
 | Melg607          |   2.43  |    4.13   |        *0*       |      *0*    |      *0*       |
 | Melg19937        |   2.73  |    3.78   |        *0*       |      *0*    |      *0*       |
 | Melg44497        |   3.20  |    3.94   |        *0*       |      *0*    |      *0*       |
 | Mrg287           |   1.33  |    2.06   |        *0*       |      *0*    |      *0*       |
 | Mrg1457          |   4.28  |   10.44   |        *0*       |      *0*    |      *0*       |
 | Mrg49507         |   2.81  |    4.25   |        *0*       |      *0*    |      *0*       |
 | Pcg64_32         |   1.15  |    2.45   |        *0*       |      *0*    |      *0*       |
 | Pcg128_64        |   3.69  |   20.25   |        *0*       |      *0*    |      *0*       |
 | Pcg1024_32       |   2.24  |    3.45   |        *0*       |      *0*    |      *0*       | 
 | Squares32        |   1.15  |    8.66   |        *0*       |      *0*    |      *0*       |
 | Squares64        |   1.14  |   10.67   |        *0*       |      *0*    |      *0*       |
 | Well512a         |   3.57  |    3.61   |      *n.a.*      |    *n.a.*   |    *n.a.*      |
 | Well1024a        |   2.30  |    2.34   |        *0*       |      *4*    |      *4*       |
 | Well19937c (1)   |   3.60  |    3.45   |        *0*       |      *2*    |      *2*       |
 | Well44497b (2)   |   3.42  |    3.80   |      *n.a.*      |    *n.a.*   |    *n.a.*      |
 | Xoroshiro256     |   2.41  |    3.71   |        *0*       |      *0*    |      *0*       |
 | Xoroshiro512     |   2.64  |    5.23   |        *0*       |      *0*    |      *0*       |
 | Xoroshiro1024    |   1.44  |    3.46   |        *0*       |      *0*    |      *0*       |

(1) The Well19937c generator provided with library CppRandLib implements the Well19937a algorithm augmented with an associated *tempering* algorithm - see [6] p.9.  
(2) The Well44497b generator provided with library CppRandLib implements the Well44497a algorithm augmented with an associated *tempering* algorithm - see [6] p.9.


---
## Implementation
Current implementation of **CppRandLib** is provided for c++11 and c++20 standards. Final performances are similar, except for *FastRand63* which has proven to be 33% slower for the c++20 version of the code than for the c++11 version (we don't know why) and for *Squares64* which is 18% faster for the c++20 version.  
Notice also: some of the PRNG algorithms involve 128-bits integer artihmetics. **CppRandLib** provides its own minimalist library for such computations since not all c++ compilers provide it (e.g. Microsoft compiler). Meanwhile, some other c++ compilers do implement 128-bits integer arithmetics (e.g. gcc). It might be of interest for users aware of this that they modify **CppRandLib** code by their side to take benefit of this. Conditional code is currently not implemented in **CppRandLib**.


---
## What's new in release 2.1

Release **2.1** is an enhancement of release 2.0:

* Tests on float values for the initialization of `SplitMixXX` instances have been fixed: value `1.0` is now accepted as it is a correct value;
* Fixed also the same test of the initialization float value for all `seed()` methods;
* Fixed a bug in method `Pcg1024_32.next()`: release 2.0 is not removed but **should no more be used**;
* Augmented unitary tests on `utils::UInt128`;
* Augmented unitary tests on every `MELGxxx` tests;
* Fixed typos in doxygen comments in nearly all header files;
* Added two documents references at end of file `README.md`.


---
## What's new in release 2.0
First of all, Release 1.0 (2022/09) is NO MORE available. Release 2.0 implements now far more PRNG algorithms than release 1.0, with **fully validated code**. 

This is available starting at version 2.0 of **CppRandLib**:

* The call operator (i.e., '()') gets a new signature. Its new use is described here below. The implementation code can be found in class `BaseRandom`.
```
    #include <iostream>
    #include <vector>
    #include "fastrand63.h"
    
    FastRand63 rand;
    
    // prints a float random value ranging in [0.0, 1.0)
    std::cout << rand() << std::endl;
    
    // prints an integer random value ranging in [0, 5)
    std::cout << rand(5) << std::endl;
    
    // prints a float random value ranging in [0.0, 20.0)
    std::cout << rand(20.0) << std::endl;
    
    // prints a list of 10 integer values each ranging in [0, 5)
    std::vector<int> vect_i{ rand(5, 10) };
    for (const double d : vect_d)
        std::cout << d << std::endl;
    
    // prints a list of 10 float values each ranging in [0.0, 1.0)
    std::vector<double> vect_d{ rand(1.0, 10) };
    for (const double d : vect_d)
        std::cout << d << std::endl;
    
    // prints a list of 4 random values ranging respectively in
    //    [0, 5), [0.0, 50.0), [0.0, 500.0) and [0, 5000)
    std::vector<double> vect{ rand({5, 50.0, 500.0, 5000}) };
    for (auto v : vect)
        std::cout << v << std::endl;  // notice: all results are of type double with fractional parts
    						
    // evaluates 5 random integer values ranging respectively in min[i] and max[i] values, for 0 <= i < 5
    // (first initialization list is min values, second one is max values)
    vect_i = rand( {1, 2, 3, 8, 6}, {10, 15, 20, 25, 30} );
```

* Version 2.0 of **CppRandLib** implements some new other "recent" PRNGs - see their list below. It also provides two Google tests codes, enhanced documentation and some other internal development features. Finally, it is splitted in two subdirectories each dedicated to a specific standard of c++: c++11 and c++20.

**Major 2.0 novelties are listed below:**

1. The WELL algorithm (Well-Equilibrated Long-period Linear, see [6], 2006) is now implemented in **CppRandLib**. This algorithm has proven to very quickly escape from the zeroland (up to 1,000 times faster than the Mersenne-Twister algorithm, for instance) while providing large to very large periods and rather small computation time.  
In **CppRandLib**, the WELL algorithm is provided in next forms: Well512a, Well1024a, Well19937c and Well44497b - they all generate output values coded on 32-bits.

1. The PCG algorithm (Permuted Congruential Generator, see [7], 2014) is now implemented in **CppRandLib**. This algorithm is a very fast and enhanced on randomness quality version of Linear Congruential Generators. It is based on solid Mathematics foundation and is clearly explained in technical report [7]. It offers jumping ahead, a hard to discover internal state characteristic, and easy multi-streams feature. It passes all crush and big crush tests of TestU01.  
**CppRandLib** implements its 3 major versions with resp. 2^32, 2^64 and 2^128 periodicities: resp. Pcg64_32, Pcg128_64 and Pcg1024_32 classes which generate output values coded on resp. 32-, 64- and 32- bits. The original library (C and C++) can be downloaded from here [pcg-cpp-0.98.zip](https://www.pcg-random.org/downloads/pcg-cpp-0.98.zip) as well as can its code be cloned from Github, here: [https://github.com/imneme/pcg-cpp](https://github.com/imneme/pcg-cpp).

1. The CWG algorithm (Collatz-Weyl Generator, see [8], 2024) is now implemented in **CppRandLib**. This algorithm is fast, uses four integers as its internal state and generates chaos via multiplication and xored-shifted instructions. Periods are medium to large and the generated randomness is of up quality. It does not offer jump ahead but multi-streams feature is available via the simple modification of a well specified integer from its four integers state.  
In **CppRandLib**, the CWG algorithm is provided in next forms: Cwg64, Cwg64-128 and Cwg128 that  generate output values coded on resp. 64-, 64- and 128- bits .

1. The Squares algorithm (see "Squares: A Fast Counter-Based RNG" [9], 2022) is now implemented in **CppRandLib**. This algorithm is fast, uses two 64-bits integers as its internal state (a counter and a key), gets a period of 2^64 and runs through 4 to 5 rounds of squaring, exchanging high and low bits and xoring intermediate values. Multi-streams feature is available via the value of the key.  
In **CppRandLib**, the Squares32 and Squares64 versions of the algorithm are implemented. They provide resp. 32- and 64- bits output values. Caution: the 64-bits versions should not pass the birthday test, which is a randmoness issue, while this is not mentionned in the original paper [9].

1. The xoroshiro algorithm ("Scrambled Linear Pseudorandom Number Generators", see [10], 2018) is now implemented in **CppRandLib**, in its *mult-mult* form for the output scrambler. This algorithm is fast, uses 64-bits integers as its internal state and outputs 64-bits values. It uses few memory space (4, 8 or 16 64-bits integers for resp. its 256-, 512- and 1024- versions that are implemented in **CppRandLib**. Notice: the 256 version of the algorithm is known to show close repeats flaws, with a bad Hamming weight near zero. *xoroshiro512* seems to best fit this property nevertheless, according to the tables proposed by the authors in [10].

1. The MELG algorithm ("Maximally Equidistributed Long-period Linear Generators", see [11], 2018) is now implemented in **CppRandLib**. It can be considered as an extension of the WELL algorithm, with a maximization of the equidistribution of generated values, making computations on 64-bits integers and outputing 64-bits values.  
**CppRandLib** implements its versions numbered *627-64*, *19937-64* and *44497-64* related to the power of 2 of their periods: resp. Melg627, Melg19937 and Melg44497.

1. The SplitMix algorithm is now implemented in **CppRandLib**. It is used to initialize the internal state of all other PRNGs and is provided as a utility. It SHOULD NOT be used as a PRNG due to its random properties poorness.

1. Method `bytesrand()` has been added to base class `BaseRandom`.

1. Method `binomialvariate()`has been added to base class `BaseRandom`.

1. A default value has been specified (i.e. = 1.0) for parameter `lambda` in method `expovariate()` of base class `BaseRandom`.

1. A CPU performance evaluation module `testCPUPerfs.cpp` is now avaliable for testing CPU performance of the different implemented algorithms. It has been used to enhance this documentation by providing a new *CPU Evaluations* table.

1. Documentation has been enhanced, with typos and erroneous documentation strings fixed also.

1. All developments are now done under a newly created branch named `release-xx-yy` on GitHub (currently, xx=2, yy=0). This development branch may be derived into sub-branches for the implementation of new features. Merges from `release-xx-yy` to branch `main` only happens when creating new releases.  
So, if you want to see what is currently going on for the next release of **CppRandLib**, just check-out the most recent branch `release-xx-yy`. If none is avalaible then branch `main` contains the very last release code et no enhancement is currently in progress.


---
## Architecture overview
c++11 and c++20 versions of the code are coded in separate subdirectories. These two directories are both provided at root level of **CppRandLib** repository.

They each contain three subdirectories:
* `baseclasses`:  
 contains the definition of every base classes related to the implemented algorithms;
* `internalstates`:  
 contains the definition of generic classes that implement the different internal states of the PRNG algorithms avaliable in **CppRandLib**;
* `utils`:  
 contains the implementation of utilities - some of which could be of interest to your projects.

Each of the implemented PRNGs is defined in an independent header file. If not templated, it is implemented in the related `.cpp` file. The name of the header and implementation files is directly related to the name of the related PRNG class.

Furthermore, a c++11 version and a c++20 version of Google tests are provided in two separate subdirectories, resp. `gTests-c++11` and `gTests-c++20`. Those tests have been implemented to fully validated the code. The code coverage is 100% and all tests passed for Release 2.0.

The user is strongly encouraged to have a look at Google tests code. This code provides examples of how to use **CppRandLib** and how to call templated methods.

---
### BaseRandom  -  the base class for all PRNGs

**BaseRandom** is the base class for every implemented PRNG in library **CppRandLib**. It is a templated class. It aims at providing common behavior for all PRNG classes of the library, the most noticeable one being the 'callable' nature of every implemented PRNG.

**CppRandLib** being a counterpart of inital library **PyRandLib** with aiming at providing the same level of functionnalities, **BaseRandom** provides in **CppRandLib** the access to many useful distribution functions as described in further section **Inherited Distribution Functions**. This is not the way the STL numerics library functions (see the [CPP Reference](https://en.cppreference.com/w/cpp/numeric/random.html) dedicated page site) to get an overview of it). Notice: Release 3.0 of **CppRandLib** will implement an interface for all **CppRandLib** PRNG classes to conform to the implementation of PRNGs in the c++ STL.

Furthermore, every inheriting class MUST override the next methods :

* `next()`,
* `_setstate()`

and may override the next three methods:

* `random()`,
* `seed()`,
* `getrandbits()`,

Notice: Since **CppRandLib 2.0**, class `BaseRandom` declares the new method `next()` which is substituted to `random()`. `next()` should now contain the core of the pseudo-random numbers generator while `random()` calls it to return a float value in the interval [0.0, 1.0) according to the uniform distribution, just as did all previous versions of the library.  
Since version **2.0** of **CppRandLib** also, the newly implemented method `getrandbits()` is provided as well the `choices()` and `choices_cum()` methods.


---
### Cwg64  --  minimum 2^70 period

**Cwg64** implements the full 64 bits version of the Collatz-Weyl Generator algorithm: computations are done on 64-bits, the output generated value is coded on 64-bits also. It provides a medium period which is at minimum 2^70 (i.e. about 1.18e+21), short computation time and a four 64-bits integers internal state (x, a, weyl, s).

This version of the CGW algorithm evaluates pseudo-random suites *output(i)* as the combination of the next instructions applied to *state(i-1)*:

    a(i)      = a(i-1) + x(i-1)
    weyl(i)   = weyl(i-1) + s  // s is constant over time and must be odd, this is the value to modify to get multi-streams
    x(i)      = ((x(i-1) >> 1) * ((a(i)) | 1)) ^ (weyl(i)))
    output(i) = (a(i) >> 48) ^ x(i)



### Cwg64  --  minimum 2^70 period

**Cwg64** implements the full 64 bits version of the Collatz-Weyl Generator algorithm: computations are done on 64-bits. The output generated value is coded on 64-bits also. It provides a medium period which is at minimum 2^70 (i.e. about 1.18e+21), short computation time and a four 64-bits integers internal state (x, a, weyl, s).

This version of the CGW algorithm evaluates pseudo-random suites *output(i)* as the combination of the next instructions applied to *state(i-1)*:

    a(i)      = a(i-1) + x(i-1)
    weyl(i)   = weyl(i-1) + s  // s is constant over time and must be odd, this is the value to modify to get multi-streams
    x(i)      = ((x(i-1) >> 1) * ((a(i)) | 1)) ^ (weyl(i)))
    output(i) = (a(i) >> 48) ^ x(i)


### Cwg128_64  --  minimum 2^71 period

**Cwg128_64** implements the mixed 128/64 bits version of the Collatz-Weyl Generator algorithm: computations are done on 128- and 64- bits. The output generated value is coded on 64-bits also. It provides a medium period which is at minimum 2^71 (i.e. about 2.36e+21), short computation time and a three 64-bits (a, weyl, s) plus one 128-bits integer internal state (x). 

This version of the CGW algorithm evaluates pseudo-random suites *output(i)* as the combination of the next instructions applied to *state(i-1)*:

    a(i)      = a(i-1) + x(i-1)
    weyl(i)   = weyl(i+1) + s  // s is constant over time and must be odd, this is the value to modify to get multi-streams
    x(i)      = ((x(i-1) | 1) * (a(i) >> 1)) ^ (weyl(i))
    output(i) = (a(i) >> 48) ^ x(i)



### Cwg128  --  minimum 2^135 period

**Cwg128** implements the full 128 bits version of the Collatz-Weyl Generator algorithm: computations are done on 128-bits. The output generated value is coded on 128-bits also. It provides a medium period which is at minimum 2^135 (i.e. about 4.36e+40), short computation time and a four 128-bits integers internal state (x, a, weyl, s).

This version of the CGW algorithm evaluates pseudo-random suites *output(i)* as the combination of the next instructions applied to *state(i-1)*:

    a(i)      = a(i-1) + x(i-1)
    weyl(i)   = weyl(i-1) + s  // s is constant over time and must be odd, this is the value to modify to get multi-streams
    x(i)      = ((x(i-1) >> 1) * ((a(i)) | 1)) ^ (weyl(i)))
    output(i) = (a(i) >> 96) ^ x(i)


---
### FastRand32  --  2^32 periodicity

**FastRand32** implements a Linear Congruential Generator dedicated to 32-bits calculations with very short period (about 4.3e+09) but very short 
time computation.

LCG models evaluate pseudo-random numbers suites *x(i)* as a simple mathematical function of *x(i-1)*:

    x(i) = ( a * x(i-1) + c ) mod m 
   
The implementation of **FastRand32** is based on  (*a*=69069, *c*=1)  since these two values have evaluated to be the 'best' ones for LCGs within TestU01 with m = 2^32.
 
Results are nevertheless considered to be poor as stated in the evaluation done by Pierre L'Ecuyer and Richard Simard. Therefore, it is not recommended to use such pseudo-random numbers generators for serious simulation applications.

See FastRand63 for a 2^63 (i.e. about 9.2e+18) period LC-Generator with low computation time and 'better' randomness characteristics.



### FastRand63  --  2^63 periodicity

**FastRand63** implements a Linear Congruential Generator dedicated to  63-bits calculations with a short period (about 9.2e+18) and very short time computation.

LCG model  evaluate pseudo-random numbers suites *x(i)* as a simple mathematical function of *x(i-1)*:

    x(i) = ( a * x(i-1) + c ) mod m 
   
The implementation of this LCG 63-bits model is based on (*a*=9219741426499971445, *c*=1) since these two values have evaluated to be the *best* ones for LCGs within TestU01 while *m* = 2^63.
 
Results are nevertheless considered to be poor as stated in the evaluation done by Pierre L'Ecuyer and Richard Simard. Therefore, it is not recommended to use this pseudo-random numbers generators for serious simulation applications, even if FastRandom63 fails on very far less tests than does FastRandom32.

See FastRand32 for a 2^32 period (i.e. about 4.3e+09) LC-Generator with 34% lower computation time.


---
### LFibRand78  --  2^78 periodicity

**LFibRand78** implements a fast 64-bits Lagged Fibonacci generator (LFib). Lagged Fibonacci generators *LFib(m, r, k, op)* use the recurrence:

    x(i) = ( x(i-r) op (x(i-k) ) mod m

where op is an operation that can be
    + (addition),
    - (substraction),
    * (multiplication),
    ^(bitwise exclusive-or).

With the + or - operation, such generators are MRGs. They offer very large periods  with the best known results in the evaluation of their randomness, as stated in the evaluation done by Pierre L'Ecuyer and Richard Simard while offering very low computation times.

The implementation of  **LFibRand78** is based on a Lagged Fibonacci generator (LFib) which uses the recurrence:

    x(i) = ( x(i-5) + x(i-17) ) mod 2^64

It offers a period of about 2^78 - i.e. 3.0e+23 - with low computation time due to the use of a 2^64 modulo (less than twice the computation time of LCGs) and low memory consumption (17 integers 32-bits coded).

Please notice that the TestU01 article states that the operator should be '*' while George Marsaglia in its original article [4] used the operator '+'. We've implemented in **CppRandLib** the original operator '+'.



### LFibRand116  --  2^116 periodicity

**LFibRand116** implements an LFib 64-bits generator proposed by George Marsaglia in [4]. This PRNG uses the recurrence:

    x(i) = ( x(i-24) + x(i-55) ) mod 2^64
    
It offers a period of about 2^116 - i.e. 8.3e+34 - with low computation time due to the use of a 2^64 modulo (less than twice the computation time of LCGs) and some memory consumption (55 integers 32-bits coded).

Please notice that the TestU01 article states that the operator should be '*' while George Marsaglia in its original article [4] used the operator '+'. We've implemented in **CppRandLib**  the original operator '+'.



### LFibRand668  --  2^668 periodicity

**LFibRand668** implements an LFib 64-bits generator proposed by George Marsaglia in [4]. This PRNG uses the recurrence:

    x(i) = ( x(i-273) + x(i-607) ) mod 2^64
    
It offers a period of about 2^668 - i.e. 1.2e+201 - with low computation time due to the use of a 2^64 modulo (less than twice the computation time of LCGs) and much memory consumption (607 integers 32-bits coded).

Please notice that the TestU01 article states that the operator should be '*' while George Marsaglia in its original article [4] used the operator '+'. We've implemented in **CppRandLib**  the original operator '+'.



### LFibRand1340  --  2^1,340 periodicity

**LFibRand1340** implements an LFib 64-bits generator proposed by George Marsaglia in [4]. This PRNG uses the recurrence:

    x(i) = ( x(i-861) + x(i-1279) ) mod 2^64
    
It offers a period of about 2^1340 - i.e. 2.4e+403 - with low computation time due to the use of a 2^64 modulo (less than twice the computation time of LCGs) and much more memory consumption (1279 integers 32-bits coded).

Please notice that the TestU01 article states that the operator should be '*' while George Marsaglia in its original article [4] used the operator '+'. We've implemented in **CppRandLib**  the original operator '+'.


---
### Melg627  -- 2^627 periodicity

**Melg627** implements a fast 64-bits Maximally Equidistributed Long-period Linear Generator (MELG) with a large period (2^627, i.e. 5.31e+182) and low computation time. The internal state of this PRNG is equivalent to 21 integers 32-bits coded.

The base MELG algorithm mixes, xor's and shifts its internal state and offers large to very large periods with the best known results in the evaluation of their randomness. It escapes the zeroland at a fast pace. Its specializations are set with parameters that ensure a maximized equidistribution. It might be valuable to use these rather than the WELL algorithm derivations.



### Melg19937  --  2^19937 periodicity

**Melg19937** implements a fast 64-bits Maximally Equidistributed Long-period Linear Generator (MELG) with a large period (2^19,937, i.e. 4.32e+6,001) and low computation time. The internal state of this PRNG is equivalent to 625 integers 32-bits coded.

The base MELG algorithm mixes, xor's and shifts its internal state and offers large to very large periods with the best known results in the evaluation of their randomness. It escapes the zeroland at a fast pace. Its specializations are set with parameters that ensure a maximized equidistribution. It might be valuable to use these rather than the WELL algorithm derivations.



### Melg44497  --  2^44497 periodicity

**Melg44497** implements a fast 64-bits Maximally Equidistributed Long-period Linear Generator (MELG) with a very large period (2^44,497,  i.e. 15.1e+13,466) and low computation time. The internal state of this PRNG is equivalent to 1.393 integers 32-bits coded.

The base MELG algorithm mixes, xor's and shifts its internal state and offers large to very large periods with the best known results in the evaluation of their randomness. It escapes the zeroland at a fast pace. Its specializations are set with parameters that ensure a maximized equidistribution. It might be valuable to use these rather than the WELL algorithm derivations.


---
### Mrg287  --  2^287 periodicity

**Mrg287** implements a fast 32-bits Multiple Recursive Generator (MRG) with a long period  (2^287, i.e. 2.49e+86) and low computation time (about twice the computation time of above LCGs) but 256 integers 32-bits coded memory consumption.

Multiple Recursive Generators (MRGs) use recurrence to evaluate pseudo-random numbers suites. For 2 to more different values of *k*, recurrence is of the form:

    x(i) = A * SUM[ x(i-k) ]  mod M

MRGs offer very large periods with the best known results in the evaluation of their randomness, as evaluated by Pierre L'Ecuyer and Richard Simard in [1]. It is therefore strongly recommended to use such pseudo-random numbers generators rather than LCG ones for serious simulation applications.

The implementation of this specific MRG 32-bits model is finally based on a Lagged Fibonacci generator (LFIB), the Marsa-LFIB4 one.

Lagged Fibonacci generators *LFib( m, r, k, op)* use the recurrence:

    x(i) = ( x(i-r) op (x(i-k) ) mod m

where op is an operation that can be
    + (addition),
    - (substraction),
    * (multiplication),
    ^ (bitwise exclusive-or).
    
With the + or - operation, such generators are true MRGs. They offer very large periods with the best known results in the evaluation of their randomness, as evaluated by Pierre L'Ecuyer and Richard Simard in their paper.

The Marsa-LIBF4 version, i.e. **Mrg287** implementation, uses the recurrence:

    x(i) = ( x(i-55) + x(i-119) + x(i-179) + x(i-256) ) mod 2^32



### Mrg1457  --  2^1,457 periodicity

**Mrg1457** implements a fast 31-bits Multiple Recursive Generator with a longer period than MRG287 (2^1457, i.e. 4.0e+438) and 3.2x computation time but with much less memory space consumption (47 vs. 256 integers 32-bits coded).
   
The implementation of this MRG 31-bits model is based on  DX-47-3 pseudo-random generator proposed by Deng and Lin, see [2]. The DX-47-3 version uses the recurrence:

    x(i) = (2^26+2^19) * ( x(i-1) + x(i-24) + x(i-47) ) mod (2^31-1)

See Mrg287 above description for an explanation of the MRG original algorithm.



### Mrg49507  --  2^49,507 periodicity

**Mrg49507** implements a fast 31-bits Multiple Recursive Generator with the longer period of all of the PRNGs that are implemented in **CppRandLib** (2^49,507, i.e. 1.2e+14,903) with low computation time also (x2.1 as for Mrg287) but use of much more memory space (1,597 integers 32-bits coded).
     
The implementation of this MRG 31-bits model is based on the 'DX-1597-2-7' MRG proposed by Deng, see [3]. It uses the recurrence:

    x(i) = (-2^25-2^7) * ( x(i-7) + x(i-1597) ) mod (2^31-1)

See Mrg287 above description for an explanation of the MRG original algorithm.


---
### Pcg64_32  --  2^64 periodicity

**Pcg64_32** implements a fast 64-bits state and 32-bits output Permutated Congruential Generator with a medium period (2^64, i.e. 1.84e+19) with low computation time and very small memory space consumption (2 integers 32-bits coded).

The underlying algorithm acts as an LCG associated with a bits permutation as its final step before outputing next random value. It is known to succesfully pass all TestU01 tests. It provides multi streams and jump ahead features and is hard to be reverted and predicted.  
**CppRandLib** implements for this the *PCG XSH RS 64/32 (LCG)* version of the PCG algorithm, as explained in [7] and coded in c++ on [www.pcg-random.org](https::/www.pcg-random.org).




### Pcg128_64  -  2^128 periodicity

**Pcg128_64** implements a fast 128-bits state and 64-bits output Permutated Congruential Generator with a medium period (2^128, i.e. 3.40e+38) with low computation time and very small memory space consumption (4 integers 32-bits coded).

The underlying algorithm acts as an LCG associated with a bits permutation as its final step before outputing next random value. It is known to succesfully pass all TestU01 tests. It provides multi streams and jump ahead features and is very hard to be reverted and predicted.  
**CppRandLib** implements for this the *PCG XSL RR 128/64 (LCG)* version of the PCG algorithm, as explained in [7] and coded in c++ on [www.pcg-random.org](https::/www.pcg-random.org).



### Pcg1024_32  -  2^32,830 periodicity

**Pcg1024_32** implements a fast 64-bits based state and 32-bits output Permutated Congruential Generator with a very large period (2^32,830, i.e. 6.53e+9,882) with low computation time and large memory space consumption (1,026 integers 32-bits coded).

The underlying algorithm acts as an LCG associated with a bits permutation as its final step before outputing next random value, and an array of 32-bits independant MCG (multiplied congruential generators) used to create huge chaos. It is known to succesfully pass all TestU01 tests. It provides multi streams and jump ahead features and is very hard to be reverted and predicted.  
**CppRandLib** implements for this the *PCG XSH RS 64/32 (EXT 1024)* version of the PCG algorithm, as explained in [7] and coded in c++ on [www.pcg-random.org](https::/www.pcg-random.org).


---
### Squares32  --  2^64 periodicity

**Squares32** implements a fast counter-based pseudo-random numbers generator which outputs 32-bits random values.  
The core of the algorithm evaluates and squares 64-bits intermediate values, then exchanges their higher and lower bits on a four rounds operations. It uses a 64-bits counter and a 64-bits key. It provides multi-streams feature via different values of key and gets robust randomness characteristics.  
The counter starts counting at 0. Once returning to 0 modulo 2^64 the whole period of the algorithm will have been exhausted. Values for keys have to be cautiously chosen: the **CppRandLib** implementation of the manner to do it as recommended in [9] is of our own but stricly respects the original recommendation and is implemented in `utils/balanced_bits_generation.h`.  
**CppRandLib** Squares32 class implements the *squares32* version of the algorithm as described in [9]. 



### Squares64  --  2^64 periodicity

**Squares64** implements a fast counter-based pseudo-random numbers generator which outputs 64-bits random values.  
The core of the algorithm evaluates and squares 64-bits intermediate values then exchanges their higher and lower bits on a five rounds operations. It uses a 64-bits counter and a 64-bits key. It provides multi-streams feature via different values of key and gets robust randomness characteristics.  
The counter starts counting at 0. Once returning to 0 modulo 2^64 the whole period of the algorithm will have been exhausted. Values for keys have to be cautiously chosen: the **CppRandLib** implementation of the manner to do it as recommended in [9] is of our own but stricly respects the original recommendation and is implemented in `utils/balanced_bits_generation.h`.  
Notice: this version of the algorithm should not pass the birthday test, which is a randmoness issue, while this is not mentionned in the original paper [9].  
**CppRandLib** Squares64 class implements the *squares64* version of the algorithm as described in [9]. 


---
### Well512a  --  2^512 periodicity

**Well512a** implements the Well-Equilibrated Long-period Linear generators (WELL) proposed by François Panneton, Pierre L'Ecuyer and Makoto Matsumoto in [6]. This PRNG uses linear recurrence based on primitive characteristic polynomials associated with left- and right- shifts and xor operations to fastly evaluate pseudo-random numbers suites.

It offers a long period of value 2^252 - i.e. 1.34e+154 - with short computation time and 16 integers 32-bits coded memory consumption.  
It escapes the zeroland at a fast pace.  
Meanwhile, it should not be able to pass some of the *crush* and *big-crush* tests of TestU01 - notice: this version of the WELL algorithm has not been tested in original TestU01 paper.



### Well1024a  --  2^1,024 periodicity

**Well1024a** implements the Well-Equilibrated Long-period Linear generators (WELL) proposed by François Panneton, Pierre L'Ecuyer and Makoto Matsumoto in [6]. This PRNG uses linear recurrence based on primitive characteristic polynomials associated with left- and right- shifts and xor operations to fastly evaluate pseudo-random numbers suites.

It offers a long period of value 2^1,024 - i.e. 2.68+308 - with short computation time and 32 integers 32-bits coded memory consumption.  
It escapes the zeroland at a fast pace.  
Meanwhile, it does not pass 4 of the *crush* and 4 of the *big-crush* tests of TestU01.



### Well199937c  --  2^19,937 periodicity

**Well199937c** implements the Well-Equilibrated Long-period Linear generators (WELL) proposed by François Panneton, Pierre L'Ecuyer and Makoto Matsumoto in [6]. This PRNG uses linear recurrence based on primitive characteristic polynomials associated with left- and right- shifts and xor operations to fastly evaluate pseudo-random numbers suites.

It offers a long period of value 2^19,937 - i.e. 4.32e+6,001 - with short computation time and 624 integers 32-bits coded memory consumption - just as the Mersenne-Twister algorithm).  
It escapes the zeroland at a very fast pace.  
Meanwhile, it does not pass 2 of the *crush* and 2 of the *big-crush* tests of TestU01.



### Well44497b  --  2^44,497 periodicity

**WellWell44497b** implements the Well-Equilibrated Long-period Linear generators (WELL) proposed by François Panneton, Pierre L'Ecuyer and Makoto Matsumoto in [6]. This PRNG uses linear recurrence based on primitive characteristic polynomials associated with left- and right- shifts and xor operations to fastly evaluate pseudo-random numbers suites.

It offers a long period of value 2^44,497 - i.e. 1.51e+13,466 - with short computation time and 1,391 integers 32-bits coded memory consumption.  
It escapes the zeroland at a fast pace.  
Meanwhile, it might not be able to pass a very few of the *crush* and *big-crush* tests of TestU01, while it can be expected to better behave than the Well19937c version - notice: this version of the WELL algorithm has not been tested in original TestU01 paper.


---
### Xoroshiro256  --  2^256 periodicity

**Xoroshiro256** implements the *xoroshiro256*** version of the Scrambled Linear Pseudorandom Number Generators algorithm proposed by David Blackman and Sebastiano Vigna in [10].  
This xoroshiro linear transformation updates cyclically two words of a 4 integers state array. The base xoroshiro linear transformation is obtained combining a rotation, a shift, and again a rotation. It also applies a double multiplication as the scrambler model before outputing values. Internal state and output values are coded on 64 bits.

It offers a medium period of value 2^256 - i.e. 1.16e+77 - with short computation time and 4 integers 64-bits coded memory consumption.  
It escapes the zeroland at a very fast pace (about 10 loops) and offers jump-ahead feature. Notice: the 256 version of the algorithm has shown close repeats flaws, with a bad Hamming weight near zero as explained by the authors in [10] and explained in [xoshiro-repeat-flaws.html](https://www.pcg-random.org/posts/xoshiro-repeat-flaws.html).



### Xoroshiro512  --  2^512 periodicity

**Xoroshiro512** implements the *xoroshiro512*** version of the Scrambled Linear Pseudorandom Number Generators algorithm proposed by David Blackman and Sebastiano Vigna in[10].  
This xoroshiro linear transformation updates cyclically two words of an 8 integers state array. The base xoroshiro linear transformation is obtained combining a rotation, a shift, and again a rotation. It also applies a double multiplication as the scrambler model before outputing values. Internal state and output values are coded on 64 bits.

It offers a medium period of value 2^512 - i.e. 1.34e+154 - with short computation time and 4 integers 64-bits coded memory consumption.  
It escapes the zeroland at a very fast pace (about 30 loops) and offers jump-ahead feature.



### Xoroshiro1024  --  2^1,024 periodicity

**Xoroshiro** implements the *xoroshiro1024*** version of the Scrambled Linear Pseudorandom Number Generators algorithm proposed by David Blackman and Sebastiano Vigna in[10].  
This xoroshiro linear transformation updates cyclically two words of a 16 integers state array and a 4 bits index. The base xoroshiro linear transformation is obtained combining a rotation, a shift, and again a rotation. It also applies a double multiplication as the scrambler model before outputing values. Internal state and output values are coded on 64 bits.

It offers a medium period of value 2^1,024 - i.e. 1.80e+308 - with short computation time and 4 integers 64-bits coded memory consumption.  
It escapes the zeroland at a fast pace (about 100 loops) and offers jump-ahead feature.



---
## Distribution Functions and Generic Functions
(*notice: some parts of the next explanation may be free or exact copy of [Python documentation](https://docs.python.org/3.13/library/random.html?highlight=random#module-random)*).

Since the base class **BaseRandom** implements all these distribution and generic functions, every PRNG class of **CppRandLib** gets automatic access to the next distribution and generic methods:


---
`const double `**`betavariate`**` (const double alpha, const double beta);`


Beta distribution.

Conditions on the parameters are `alpha > 0` and `beta > 0`.  
Returned values range between 0 and 1.


---
`template<typename T>`   
`const T& `**`choice`**` (const std::vector<T>& seq);`

`template<typename T, const std::size_t n>`  
`const T& `**`choice`**` (const std::array<T, n>& seq);`

Chooses a random element from a non-empty sequence. 'seq' must not be empty.


---
`template<typename T>`  
`std::vector<T> `**`choices`**` (const std::vector<T>& population, const std::size_t k);`

Returns a k sized vector of elements chosen from the population with replacement (same weight for each element).


---
`template<typename T, typename C>`  
`requires std::is_arithmetic_v<C>`  
`std::vector<T> `**`choices`**` (const std::vector<T>& population, std::vector<C>& weights, const std::size_t k);`

Returns a k sized vector of elements chosen from the population with replacement (individual weight for each element).


---
`template<typename T, typename C>`  
`requires std::is_arithmetic_v<C>`  
`std::vector<T> `**`choices_cum`**` (const std::vector<T>& population, const std::vector<C>& cum_weights, const std::size_t k);`

Returns a k sized vector of elements chosen from the population with replacement (cumulative weights over elements).


---
`const double `**`expovariate`**` (const double lambda = 1.0);`

Exponential distribution.

`lambda` is 1.0 divided by the desired  mean. It should be nonzero.  
Returned values range from 0 to positive infinity if lambda is positive, and from negative infinity to 0 if lambda is negative.


---
`const double `**`gammavariate`**` (const double alpha, const double beta);`

Gamma distribution. Not the gamma function!
    
Conditions on the parameters are `alpha > 0` and `beta > 0`.


---
`const double `**`gauss`**` () noexcept;`

Gaussian distribution with default values `mu = 0.0` and `sigma = 1.0`.  
This is slightly faster than the normalvariate() function.  
Notice: not thread-safe without a lock around calls.

Important notice: the implemented code is a translation from Python built-in library module [random.py](https://github.com/python/cpython/blob/3.11/Lib/random.py) into c++.



---
`const double `**`gauss`**` (const double mu, const double sigma);`

Gaussian distribution.

`mu` is the mean, and `sigma` is the standard deviation.  
This is slightly faster than the normalvariate() function.  
Notice: not thread-safe without a lock around calls.

Important notice: the implemented code is a translation from Python built-in library module [random.py](https://github.com/python/cpython/blob/3.11/Lib/random.py) into c++.


---
`OutputT `**`getrandbits`**` (const unsigned int k)`

Returns an unsigned integer with k random bits. Notice: `OutputT` is a template argment of templated class `BaseRandom`. It specifies the type of integer that any inheriting PRNG returns on class of method `next()`. 


---
`struct _InternalState `**`getstate`**` () const noexcept;`

Returns the internal state of this PRNG. Can be later passed to setstate().


---
`const double `**`lognormvariate`**` ();`

If you take the natural logarithm of this distribution, you'll get a normal distribution with mean 0.0 and standard deviation 1.0.


---
`const double `**`lognormvariate`**` (const double mu, const double sigma)`

Log normal distribution.

If you take the natural logarithm of this distribution, you'll get a normal distribution with mean mu and standard deviation sigma.  
`mu` can have any value, and `sigma` must be greater than zero.


---
`template<typename T>`  
`requires std::is_floating_point_v<T>`  
`std::vector<T> `**`n_evaluate`**` (const std::size_t n);`

Returns a vector of n values that are uniformly contained within range [0.0, 1.0).


---
`template<typename T, typename U = T>`  
`requires std::is_floating_point_v<T> && std::is_arithmetic_v<U>`  
`std::vector<T> `**`n_evaluate`**` (const std::size_t n, const U max);`

Returns a vector of n values that are uniformly contained within range [0, max).


---
`template<typename T, typename U = T>`  
`requires std::is_floating_point_v<T> && std::is_arithmetic_v<U>`  
`std::vector<T> `**`n_evaluate`**` (const std::vector<U>& max);`

Returns a vector of max.size() values that are uniformly contained within range [0, max[i]), 0 <= i < max.size().


---
`template<typename T, typename U = T, typename V = U>`  
`requires std::is_floating_point_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>`  
`std::vector<T> `**`n_evaluate`**` (const std::vector<U>& min, const std::vector<V>& max);`

Returns a vector of std::min(min.size(), max.size()) values that are uniformly contained within range [min[i], max[i]), 0 <= i < std::min(min.size(), max.size()).


---
`template<typename T, const std::size_t n>`  
`requires std::is_floating_point_v<T> && (n != 0)`  
`std::array<T, n> `**`n_evaluate`**` () noexcept;`

Returns an array of n values that are uniformly contained within range [0.0, 1.0).


---
`template<typename T, const std::size_t n, typename U = T>`  
`requires std::is_floating_point_v<T> && std::is_arithmetic_v<U> && (n != 0)`  
`std::array<T, n> `**`n_evaluate`**` (const U max) noexcept;`

Returns an array of n values that are uniformly contained within range [0.0, max).


---
`template<typename T, const std::size_t n, typename U = T, typename V = U>`  
`requires std::is_floating_point_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && (n != 0)`  
`std::array<T, n> `**`n_evaluate`**` (const U min, const U max) noexcept;`

Returns an array of n values that are uniformly contained within range [min, max).


---
`template<typename T, const std::size_t m, typename U = T, const std::size_t n = m>`  
`requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && (m != 0) && (n != 0)`  
`std::array<T, m> `**`n_evaluate`**` (const std::array<U, n>& max);`

Returns an array of std::min(m, n) values in range [0; max[i]), 0 <= i < std::min(m, n).


---
`template<typename T, const std::size_t m, typename U = T, const std::size_t n = m, typename V = U, const std::size_t p = n>`  
`requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && (m != 0) && (n != 0) && (p != 0)`  
`std::array<T, m> `**`n_evaluate`**` (const std::array<U, n>& min, const std::array<V, p>& max) noexcept;`

Returns an array of std::min(m, n, p) values in range [min[i]; max[i]), std::min(m, n, p).


---
`const double `**`normalvariate`**` ();`

The Python version of this method uses Kinderman and Monahan method (reference: Kinderman, A.J.and Monahan, J.F., "Computer generation of random variables using the ratio of  uniform  deviates", ACM Trans. Math Software, 3, (1977), pp. 257 - 260).  
This method is slightlly slower than the gauss method. Furthermore, we've s lightly modified the original algorithm in **CppRandLib** to fulfill very special cases that might happen in very specific conditions. This slows down also the running of **normalvariate()** in these very specific conditions. You should prefer then to use method  gauss() instead of this one.

Important notice:  the implemented code is a translation from Python built-in library module [random.py](https://github.com/python/cpython/blob/3.11/Lib/random.py) into c++.


---
`const double `**`normalvariate`**` (const double mu, const double sigma);`

Normal distribution.

`mu` is the mean, and `sigma` is the standard deviation.  
`mu` can be any value, `sigma` must be greater than 0.0.  
See method gauss() for a faster equivalent.

The Python version of this method uses Kinderman and Monahan method (reference: Kinderman, A.J.and Monahan, J.F., "Computer generation of random variables using the ratio of  uniform  deviates", ACM Trans. Math Software, 3, (1977), pp. 257 - 260).  
This method is slightlly slower than the gauss method. Furthermore, we've slightly modified the original algorithm here to fulfill very special cases that might happen in very specific conditions. This slows down also the running of **normalvariate()** in these very specific conditions. You should prefer then to use method  gauss() instead of this one.

Important notice:  the implemented code is a translation from Python built-in library module [random.py](https://github.com/python/cpython/blob/3.11/Lib/random.py) into c++.


---
`const double `**`paretovariate`**` (const double alpha);`

Pareto distribution.  
`alpha` is the shape parameter. It cannot be 0.0.

Important notice:  the implemented code is a translation from Python built-in library module [random.py](https://github.com/python/cpython/blob/3.11/Lib/random.py) into c++.


---
`std::vector<std::uint8_t> `**`randbytes`**` (const std::size_t n);`

Generates n random bytes.  
Important notice: this method should not be used for generating security tokens.


---
`template<typename T>`  
`requires std::is_integral_v<T>`  
`inline const T `**`randint`**` (const T a, const T b) noexcept;`

Returns a random integer in range [a, b], including both end points.


---
`template<typename T, typename S = T>`  
`requires std::is_arithmetic_v<T> && std::is_arithmetic_v<S>`  
`const T `**`randrange`**` (const T start, const T stop, const S step = S(1));`

Returns a random value in range [start, stop) with specified step. step value defaults to 1.


---
`template<typename T>`  
`void `**`sample`**` (std::vector<T>& out, const std::vector<T>& population, const std::size_t k);`

Chooses k unique random elements from a population sequence. All population elements have same weight for the sampling and are each chosen only once.

Evaluates a vector containing elements from the population while leaving the original population unchanged. The resulting vector is in selection order so that all sub-slices will also be valid random samples. This allows raffle winners (the sample) to be partitioned into grand prize and second place winners (the subslices).

Members of the population need not be unique. If the population contains repeats, then each occurrence is a possible selection in the sample.


---
`template<typename T\, const std::size_t k, const std::size_t n>`  
`void `**`sample`**` (std::vector<T>& out, const std::vector<T>& population, const std::size_t k);`

Chooses k unique random elements from a population sequence. All population elements have same weight for the sampling and are each chosen only once.

Evaluates a vector containing  elements from the population while leaving the original population unchanged. The resulting vector is in selection order so that all sub-slices will also be valid random samples. This allows raffle winners (the sample) to be partitioned into grand prize and second place winners (the subslices).

Members of the population need not be unique. If the population contains repeats, then each occurrence is a possible selection in the sample.


---
`template<typename T, const std::size_t k, const std::size_t n>`  
`requires (k != 0)`  
`void `**`sample`**` (std::array<T, k>& out, const std::array<T, n>& population);`

Chooses k unique random elements from a population sequence. All population elements have same weight for the sampling and are each chosen only once.

Evaluates a vector containing  elements from the population while leaving the original population unchanged. The resulting vector is in selection order so that all sub-slices will also be valid random samples. This allows raffle winners (the sample) to be partitioned into grand prize and second place winners (the subslices).

Members of the population need not be unique. If the population contains repeats, then each occurrence is a possible selection in the sample.  
Notice: k must be greater than n.


---
`template<typename T, typename C>`  
`requires std::is_integral_v<C>`  
`void `**`sample`**` (std::vector<T>& out, const std::vector<T>& population, const std::vector<C>& counts, const std::size_t k);`

Chooses k unique random elements from a population sequence (std::vector<>, with counts vector).  
k must not be greater than the sum of all counts.

Evaluates a vector containing k elements from the population while leaving the original population unchanged. The resulting list is in selection order so that all sub-slices will also be valid random samples. This allows raffle winners (the sample) to be partitioned into grand prize and second place winners (the subslices).

Members of the population need not be unique. If the population contains repeats, then each occurrence is a possible selection in the sample.  

Repeated elements are specified by the counts parameter. For example:

    sample(out, {"red", "blue"}, {4, 2}, 5);

is equivalent to:

    sample(out, {"red", "red", "red", "red", "blue", "blue"}, 5);


---
`template<typename T, typename C, const std::size_t k, const std::size_t n>`  
`requires std::is_integral_v<C> && (k != 0)`  
`void `**`sample`**` (std::array<T, k>& out, const std::array<T, n>& population, const std::array<C, n>& counts);`

Chooses k unique random elements from a population sequence (std::array<>, with counts array).  
k must not be greater than the sum of all counts.

Evaluates an array containing k elements from the population while leaving the original population unchanged. The resulting list is in selection order so that all sub-slices will also be valid random samples. This allows raffle winners (the sample) to be partitioned into grand prize and second place winners (the subslices).

Members of the population need not be unique. If the population contains repeats, then each occurrence is a possible selection in the sample.  

Repeated elements are specified by the counts parameter. For example:

    std::array<char*, 5> out;
    sample(out, std::array<char*, 2>{"red", "blue"}, std::array<int, 2>{4, 2});

is equivalent to:

    std::array<char*, 5> out;
    sample(out, std::array<char*, 6>{"red", "red", "red", "red", "blue", "blue"});


---
`void `**`seed`**` () noexcept;`

Initializes the internal state of the PRNG (empty signature).

The final seed integer value is evaluated from shuffled current system time.


---
`void `**`seed`**` (const int seed_) noexcept;`  
`void `**`seed`**` (const unsigned int seed_) noexcept;`  
`void `**`seed`**` (const long seed_) noexcept;`  
`void `**`seed`**` (const unsigned long seed_) noexcept;`  
`void `**`seed`**` (const long long seed_) noexcept;`  
`void `**`seed`**` (const unsigned long long seed_) noexcept;`  
`void `**`seed`**` (const utils::UInt128&) noexcept;`  
`void `**`seed`**` (const double seed_);`  

Initializes the internal state of the PRNG (valued signature).


---
`void `**`setstate`**` (const StateT& new_internal_state) noexcept;`

Restores internal state from object returned by getstate().


---
`void `**`setstate`**` (const StateT& new_internal_state, const double gauss_next) noexcept;`

Restores internal state from object returned by getstate() and with gauss_next.


---
`virtual void `**`_setstate`**` (const std::uint64_t seed) noexcept;`

Sets the internal state with a 64-bits integer seed.

MUST BE overridden in inheriting classes: this method does nothing in base class `BaseRandom`.


---
`virtual void `**`_setstate`**` (const utils::UInt128& seed) noexcept;`

Sets the internal state with a 128-bits integer seed.

MUST BE overridden in **128-bits** inheriting classes : this method uses the 64-bits lowest bits per default in base class `BaseRandom`.


---
`template<typename ContainerType>`  
`requires utils::is_indexable_v<ContainerType>`  
`void `**`shuffle`**` (ContainerType& seq);`

In place shuffles the specified sequence.

The Container type must be either std::vector or std::array.


---
`const double `**`triangular`**` () noexcept;`

Triangular distribution with default values low = 0.0, high = 1.0 and mode (i.e. midpoint) = 0.5.

This is a continuous distribution bounded by given lower and upper limits, and having a given mode value in-between.  
Returns a random floating point number *N* such that low <= *N* <= high and with the specified mode between those bounds. The low and high bounds default to zero and one. The mode argument defaults to the midpoint between the bounds, giving a symmetric distribution.

See [http://en.wikipedia.org/wiki/Triangular_distribution](http://en.wikipedia.org/wiki/Triangular_distribution).


---
`const double `**`triangular`**` (const double low, const double high, const double mode) noexcept;`

Triangular distribution.

This is a continuous distribution bounded by given lower and upper limits, and having a given mode value in-between.  
Returns a random floating point number *N* such that low <= *N* <= high and with the specified mode between those bounds. The low and high bounds default to zero and one. The mode argument defaults to the midpoint between the bounds, giving a symmetric distribution.

See [http://en.wikipedia.org/wiki/Triangular_distribution](http://en.wikipedia.org/wiki/Triangular_distribution).


---
`template <typename T = double>`  
`requires std::is_floating_point_v<T>`  
`const T `**`uniform`**` () noexcept;`

The uniform distribution.  
Returns a random number in the range [0.0, 1.0).


---
t`emplate <typename T = double, typename U = T>`  
`requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>`  
`const T `**`uniform`**` (const U max) noexcept;`

The uniform distribution.  
Returns a random number in the range [0, max).


---
`template <typename T = double, typename U = T, typename V = U>`  
`requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>`  
`const T `**`uniform`**` (const U min, const V max) noexcept;`

The uniform distribution.  
Returns a random number in the range [min, max).


---
`const double `**`vonmisesvariate`**` (const double mu, const double kappa);`

Circular data distribution.

`mu` is the mean angle, expressed in radians between `0` and `2*pi`, and `kappa` is the concentration parameter, which must be greater than or equal to zero. If `kappa` is equal to zero, this distribution reduces to a uniform random angle over the range `0` to `2*pi`.

Important notice:  the implemented code is a translation from Python built-in library module [random.py](https://github.com/python/cpython/blob/3.11/Lib/random.py) into c++.  
As such, some comments present in the Python original code have been copied as they are in this c++ implementation, naming then the authors of the related parts of code.


---
`const double `**`weibullvariate`**` (const double alpha, const double beta);`

Weibull distribution.

`alpha` is the scale parameter and `beta` is the shape parameter. `beta` connot be zero.


---
## References

**[1]** Pierre L'Ecuyer and Richard Simard. 2007.  
"*TestU01: A C library for empirical testing of random number generators*".  
ACM Transaction on Mathematical Software, Vol.33 N.4, Article 22 (August 2007), 40 pages. DOI: http://dx.doi.org/10.1145/1268776.1268777

BibTex:
@article{L'Ecuyer:2007:TCL:1268776.1268777,
 author = {L'Ecuyer, Pierre and Simard, Richard},
 title = {TestU01: A C Library for Empirical Testing of Random Number Generators},
 journal = {ACM Trans. Math. Softw.},
 issue_date = {August 2007},
 volume = {33},
 number = {4},
 month = aug,
 year = {2007},
 issn = {0098-3500},
 pages = {22:1--22:40},
 articleno = {22},
 numpages = {40},
 url = {http://doi.acm.org/10.1145/1268776.1268777},
 doi = {10.1145/1268776.1268777},
 acmid = {1268777},
 publisher = {ACM},
 address = {New York, NY, USA},
 keywords = {Statistical software, random number generators, random number tests, statistical test},
}  


**[2]** Lih-Yuan Deng  &  Dennis K. J. Lin. 2000.  
"*Random number generation for the new century*".  
The American Statistician Vol.54, N.2, pp. 145–150.

BibTex:
@article{doi:10.1080/00031305.2000.10474528,
author = { Lih-Yuan   Deng  and  Dennis K. J.   Lin },
title = {Random Number Generation for the New Century},
journal = {The American Statistician},
volume = {54},
number = {2},
pages = {145-150},
year = {2000},
doi = {10.1080/00031305.2000.10474528},
URL = {ttp://amstat.tandfonline.com/doi/abs/10.1080/00031305.2000.10474528},
eprint = {http://amstat.tandfonline.com/doi/pdf/10.1080/00031305.2000.10474528}
}


**[3]** Lih-Yuan Deng. 2005.  
"*Efficient and portable multiple recursive generators of large order*".  
ACM Transactions on Modeling and Computer. Simulation 15:1.


**[4]** Georges Marsaglia. 1985.  
"*A current view of random number generators*".  
In Computer Science and Statistics, Sixteenth Symposium on the Interface. Elsevier Science Publishers, North-Holland, Amsterdam, 1985, The Netherlands. pp. 3–10.


**[5]** Makoto Matsumoto and Takuji Nishimura. 1998.  
"*Mersenne twister: A 623-dimensionally equidistributed uniform pseudo-random number generator*".  
In ACM Transactions on Modeling and Computer Simulation (TOMACS) - Special issue on uniform random number generation. Vol.8 N.1, Jan. 1998, pp. 3-30.  


**[6]** François Panneton and Pierre L'Ecuyer (Université de Montréal) and Makoto Matsumoto (Hiroshima University). 2006.  
"*Improved Long-Period Generators Based on Linear Recurrences Modulo 2*".  
In ACM Transactions on Mathematical Software, Vol. 32, No. 1, March 2006, pp. 1–16.  
see [https://www.iro.umontreal.ca/~lecuyer/myftp/papers/wellrng.pdf](https://www.iro.umontreal.ca/~lecuyer/myftp/papers/wellrng.pdf).


**[7]** Melissa E. O'Neill. 2014.  
"*PCG: A Family of Simple Fast Space-Efficient Statistically Good Algorithms for Random Number Generation*".  
Submitted to ACM Transactions on Mathematical Software (47 pages)  
Finally: Harvey Mudd College Computer Science Department Technical Report, HMC-CS-2014-0905, Issued: September 5, 2014 (56 pages).  
@techreport{oneill:pcg2014,
    title = "PCG: A Family of Simple Fast Space-Efficient Statistically Good Algorithms for Random Number Generation",
    author = "Melissa E. O'Neill",
    institution = "Harvey Mudd College",
    address = "Claremont, CA",
    number = "HMC-CS-2014-0905",
    year = "2014",
    month = Sep,
    xurl = "https://www.cs.hmc.edu/tr/hmc-cs-2014-0905.pdf",
}  
see also [https://www.pcg-random.org/pdf/hmc-cs-2014-0905.pdf](https://www.pcg-random.org/pdf/hmc-cs-2014-0905.pdf).


**[8]** Tomasz R. Dziala. 2023.  
"*Collatz-Weyl Generators: High Quality and High Throughput Parameterized Pseudorandom Number Generators*".  
Published at arXiv, December 2023 (11 pages),  
Last reference: arXiv:2312.17043v4 [cs.CE], 2 Dec 2024, see [https://arxiv.org/abs/2312.17043](https://arxiv.org/abs/2312.17043)  
DOI: https://doi.org/10.48550/arXiv.2312.17043


**[9]** Bernard Widynski. March 2022.  
"*Squares: A Fast Counter-Based RNG*".  
Published at arXiv, March 2022 (5 pages)  
Last reference: arXiv:2004.06278v7 [cs.DS] 13 Mar 2022, see [https://arxiv.org/pdf/2004.06278](https://arxiv.org/pdf/2004.06278).  
DOI: https://doi.org/10.48550/arXiv.2004.06278


**[10]** David Blackman, Sebastiano Vigna. 2018.  
"*Scrambled Linear Pseudorandom Number Generators*".  
Published in arXiv, March 2022 (32 pages)  
Last reference: arXiv:1805.01407v3 [cs.DS] 28 Mar 2022, see [https://arxiv.org/pdf/1805.01407](https://arxiv.org/pdf/1805.01407).  
DOI: https://doi.org/10.48550/arXiv.1805.01407


**[11]** Shin Harase, Takamitsu Kimoto, 2018.  
"*Implementing 64-bit Maximally Equidistributed F2-Linear Generators with Mersenne Prime Period*".  
In ACM Transactions on Mathematical Software, Volume 44, Issue 3, April 2018, Article No. 30 (11 Pages)  
Also published in arXiv, March 2022 (11 pages)  
Last reference: arXiv:1505.06582v6 [cs.DS] 20 Nov 2017, see [https://arxiv.org/pdf/1505.06582](https://arxiv.org/pdf/1505.06582).  
DOI: https://doi.org/10.1145/3159444, https://doi.org/10.48550/arXiv.1505.06582


**[12]** Marsaglia, G. 1972.  
"*The structure of linear congruential sequences.*"  
In Applications of Number Theory to Numerical Analysis, S. K. Zaremba, Ed. Academic Press, 249–285.


**[13]** Brown, F. B. and Nagaya, Y. 2002.  
"*The MCNP5 random number generator.*"  
Tech. rep. LA-UR-02-3782, Los Alamos National Laboratory
