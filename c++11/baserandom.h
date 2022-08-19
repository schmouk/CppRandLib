#pragma once
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
#include <stdexcept>
#include <vector>


//===========================================================================
/** @brief This is the base class for all pseudo-random numbers generators.
*
*
    This module is part of library CppRandLib.
    Copyright (c) 2022 Philippe Schmouker
    See FastRand32 for a 2^32 (i.e. 4.3e+9) period LC-Generator and  FastRand63  for a
    2^63 (i.e. about 9.2e+18) period LC-Generator with low computation time.
    See MRGRand287 for a short period  MR-Generator (2^287,  i.e. 2.49e+86)  with  low
    computation time but 256 integers memory consumption.
    See MRGRand1457 for a  longer  period  MR-Generator  (2^1457,  i.e. 4.0e+438)  and
    longer  computation  time  (2^31-1  modulus  calculations)  but  less memory space
    consumption (47 integers).
    See MRGRand49507 for a far  longer  period  (2^49507,  i.e. 1.2e+14903)  with  low
    computation  time  too  (31-bits  modulus)  but  use  of  more  memory space (1597
    integers).
    See LFibRand78, LFibRand116, LFibRand668 and LFibRand1340  for  long  period  LFib
    generators  (resp.  2^78,  2^116,  2^668  and 2^1340 periods,  i.e. resp. 3.0e+23,
    8.3e+34, 1.2e+201 and 2.4e+403 periods) while same computation time and far higher
    precision  (64-bits  calculations) but memory consumption (resp. 17,  55,  607 and
    1279 integers).
    Python built-in class random.Random is subclassed here to use  a  different  basic
    generator of our own devising: in that case, overriden methods are:
      random(), seed(), getstate(), and setstate().
    Furthermore this class and all its inheriting sub-classes are callable. Example:
      rand = BaseRandom()
      std::cout << rand();   // prints a uniform pseudo-random value within [0.0, 1.0)
      std::cout << rand(a);  // prints a uniform pseudo-random value within [0.0, a)
      std::cout << rand(a,b);// prints a uniform pseudo-random value within [a  , b)
    Please notice that for simulating the roll of a dice you should program:
      diceRoll = UFastRandom();
      std::cout << int(diceRoll(1, 7)); // prints a uniform roll within {1, ..., 6}.
    Conforming to the former version PyRandLib  of  this  library,  next  methods  are
    available:
     |
     |  betavariate(self, alpha, beta)
     |      Beta distribution.
     |
     |      Conditions on the parameters are alpha > 0 and beta > 0.
     |      Returned values range between 0 and 1.
     |
     |
     |  choice(self, seq)
     |      Choose a random element from a non-empty sequence.
     |
     |
     |  expovariate(self, lambd)
     |      Exponential distribution.
     |
     |      lambd is 1.0 divided by the desired mean.  It should be
     |      nonzero.  (The parameter would be called "lambda", but that is
     |      a reserved word in Python.)  Returned values range from 0 to
     |      positive infinity if lambd is positive, and from negative
     |      infinity to 0 if lambd is negative.
     |
     |
     |  gammavariate(self, alpha, beta)
     |      Gamma distribution.  Not the gamma function!
     |
     |      Conditions on the parameters are alpha > 0 and beta > 0.
     |
     |
     |  gauss(self, mu, sigma)
     |      Gaussian distribution.
     |
     |      mu is the mean, and sigma is the standard deviation.  This is
     |      slightly faster than the normalvariate() function.
     |
     |      Not thread-safe without a lock around calls.
     |
     |
     |  getstate(self)
     |      Return internal state; can be passed to setstate() later.
     |
     |
     |  lognormvariate(self, mu, sigma)
     |      Log normal distribution.
     |
     |      If you take the natural logarithm of this distribution, you'll get a
     |      normal distribution with mean mu and standard deviation sigma.
     |      mu can have any value, and sigma must be greater than zero.
     |
     |
     |  normalvariate(self, mu, sigma)
     |      Normal distribution.
     |
     |      mu is the mean, and sigma is the standard deviation.
     |
     |
     |  paretovariate(self, alpha)
     |      Pareto distribution.  alpha is the shape parameter.
     |
     |
     |  randint(self, a, b)
     |      Return random integer in range [a, b], including both end points.
     |
     |
     |  randrange(self, start, stop=None, step=1, int=<class 'int'>)
     |      Choose a random item from range(start, stop[, step]).
     |
     |      This fixes the problem with randint() which includes the
     |      endpoint; in Python this is usually not what you want.
     |
     |      Do not supply the 'int' argument.
     |
     |
     |  sample(self, population, k)
     |      Chooses k unique random elements from a population sequence or set.
     |
     |      Returns a new list containing elements from the population while
     |      leaving the original population unchanged.  The resulting list is
     |      in selection order so that all sub-slices will also be valid random
     |      samples.  This allows raffle winners (the sample) to be partitioned
     |      into grand prize and second place winners (the subslices).
     |
     |      Members of the population need not be hashable or unique.  If the
     |      population contains repeats, then each occurrence is a possible
     |      selection in the sample.
     |
     |      To choose a sample in a range of integers, use range as an argument.
     |      This is especially fast and space efficient for sampling from a
     |      large population:   sample(range(10000000), 60)
     |
     |
     |  seed(self, a=None, version=2)
     |      Initialize internal state from hashable object.
     |
     |      None or no argument seeds from current time or from an operating
     |      system specific randomness source if available.
     |
     |      For version 2 (the default), all of the bits are used if *a *is a str,
     |      bytes, or bytearray.  For version 1, the hash() of *a* is used instead.
     |
     |      If *a* is an int, all bits are used.
     |
     |
     |  setstate(self, state)
     |      Restore internal state from object returned by getstate().
     |
     |
     |  shuffle(self, x, random=None, int=<class 'int'>)
     |      x, random=random.random -> shuffle list x in place; return None.
     |
     |      Optional arg random is a 0-argument function returning a random
     |      float in [0.0, 1.0); by default, the standard random.random.
     |
     |
     |  triangular(self, low=0.0, high=1.0, mode=None)
     |      Triangular distribution.
     |
     |      Continuous distribution bounded by given lower and upper limits,
     |      and having a given mode value in-between.
     |
     |      http://en.wikipedia.org/wiki/Triangular_distribution
     |
     |
     |  uniform(self, a, b)
     |      Get a random number in the range [a, b) or [a, b] depending on rounding.
     |
     |
     |  vonmisesvariate(self, mu, kappa)
     |      Circular data distribution.
     |
     |      mu is the mean angle, expressed in radians between 0 and 2*pi, and
     |      kappa is the concentration parameter, which must be greater than or
     |      equal to zero.  If kappa is equal to zero, this distribution reduces
     |      to a uniform random angle over the range 0 to 2*pi.
     |
     |
     |  weibullvariate(self, alpha, beta)
     |      Weibull distribution.
     |
     |      alpha is the scale parameter and beta is the shape parameter.
*/
template<typename SeedStateType>
class BaseRandom
{
public:
    //---   Constructors / Destructor   -------------------------------------
    /** @brief Empty Constructor.
    *
    * Inheriting classes use a shuffled value of the local time as a seed
    * to initialize their related PRNG.
    */
    BaseRandom() noexcept;

    /** @brief Value Constructor. */
    inline BaseRandom(const SeedStateType& seed) noexcept
        :_seed(seed)
    {}

    /** @brief Default Copy Constructor. */
    BaseRandom(const BaseRandom&) noexcept = default;

    /** @brief Default Move Constructor. */
    BaseRandom(BaseRandom&&) noexcept = default;

    /** @brief Default Destructor. */
    virtual ~BaseRandom() noexcept = default;


    //---   Assignments operators   -----------------------------------------
    /** @brief Default Copy assignment. */
    BaseRandom& operator= (const BaseRandom&) noexcept = default;

    /** @brief Default Move assignment. */
    BaseRandom& operator= (BaseRandom&&) noexcept = default;

    /** @brief Valued assignment. */
    inline BaseRandom& operator= (const SeedStateType& seed) noexcept
    {
        setstate(seed);
    }


    //---   Calling operators   ---------------------------------------------
    /** @brief Empty Call operator.
    *
    * @return a value that is uniformly contained within the interval [0.0, 1.0).
    */
    inline const double operator() ()
    {
        return operator()(0.0, 1.0);
    }

    /** @brief Valued call operator (1 scalar).
    *
    * @return a value that is uniformly contained within the interval [0; max).
    */
    template<typename T>
    inline const T operator() (const T max)
    {
        return operator()(T(0), max);
    }

    /**@brief Valued call operator (min and max scalars).
    *
    * @return a value that is uniformly contained within the interval [min; max).
    */
    template<typename T>
    inline const T operator() (const T min, const T max)
    {
        return uniform(min, max);
    }

    /** @brief Valued call operator (1 vector of scalars).
    *
    * @return a vector of value that are uniformly contained within the
    *   interval  [0; max[i])  -  i  being the index of the value in the
    *   returned vector.
    */
    template<typename T>
    std::vector<T> operator() (const std::vector<T> max)
    {
        std::vector<T> ret;
        ret.reserve(max.size());
        for (T m : max)
            ret.emplace_back(operator()(m));
        return ret;
    }

    /** @brief Valued call operator (2 vectors of scalars).
    *
    * @return a vector of value that are uniformly contained within  the
    *   interval [min[i]; max[i]) - i being the index of the value in the
    *   returned vector.
    */
    template<typename T>
    std::vector<T> operator() (const std::vector<T> min, const std::vector<T> max)
    {
        std::vector<T> ret;
        ret.reserve(std::min(min.size(), max.size()));
        for (auto min_it = min.cbegin(), max_it = max.cbegin(); min_it != min.cend() && max_it != max.cend(); ++min_it, ++max_it)
            ret.emplace_back(operator()(*min_it, *max_it));
        return ret;
    }


    //---   Operations   ----------------------------------------------------
    /** @brief Returns n values that are uniformly contained within the interval [0.0, 1.0). */
    inline void n_evaluate(size_t n, std::vector<double>& out)
    {
        n_evaluate(n, out, 0.0, 1.0);
    }

    /** @brief Returns n values that are uniformly contained within the interval [0, max). */
    template<typename T>
    inline void n_evaluate(size_t n, std::vector<T>& out, const T max)
    {
        n_evaluate(n, out, T(0), max);
    }

    /** @brief Returns n values that are uniformly contained within the interval [min, max). */
    template<typename T>
    inline void n_evaluate(size_t n, std::vector<T>& out, const T min, const T max)
    {
        out.reserve(n);
        while (n-- > 0)
            out.emplace_back(operator()(min, max));
    }

    /** @brief Returns n vectors of values that are uniformly contained within the interval [0; max[i]) */
    template<typename T>
    inline void n_evaluate(size_t n, std::vector<std::vector<T>>& out, const std::vector<T> max)
    {
        out.reserve(n);
        while (n-- > 0)
            out.emplace_back(operator()(max));
    }

    /** @brief Returns n vectors of values that are uniformly contained within the interval [min[i]; max[i]) */
    template<typename T>
    inline void n_evaluate(size_t n, std::vector<std::vector<T>>& out, const std::vector<T> min, const std::vector<T> max)
    {
        out.reserve(n);
        while (n-- > 0)
            out.emplace_back(operator()(min, max));
    }


    //---   Random distribution functions   ---------------------------------
    /** @brief Beta distribution.
    *
    * @arg alpha: double, must be greater than 0
    * @arg beta: double, must be greater than 0
    * @return a value in interval [0.0, 1.0].
    * 
    * Important  notice:  the implemented  code  is  a  translation  from 
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++. 
    * The original code is due to Janne Sinkkonen and matches all the std 
    * texts (e.g., Knuth Vol 2 Ed 3 pg 134 "the beta distribution").
    */
    const double betavariate(const double alpha, const double beta) const;


    /** @brief Uniform distribution. */
    template<typename T>
    inline const T uniform(const T min, const T max)
    {
        //TODO: implement this method - current code is for compilation tests purpose only
        return max;
    }


protected:
    //---   Attributes   ----------------------------------------------------
    SeedStateType _seed;  //!< The internal current state of this PRNG
};


