#pragma once
/*
MIT License

Copyright (c) 2022-2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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
#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>


//===========================================================================
/** @brief This is the base class for all pseudo-random numbers generators.
*
*   This module is part of library CppRandLib.
*
*   Copyright (c) 2022-2025 Philippe Schmouker
*
*   See FastRand32 for a 2^32 (i.e. 4.3e+9) period LC-Generator and  FastRand63  for a
*   2^63 (i.e. about 9.2e+18) period LC-Generator with low computation time.
*
*   See MRGRand287 for a short period  MR-Generator (2^287,  i.e. 2.49e+86)  with  low
*   computation time but 256 integers memory consumption.
*
*   See MRGRand1457 for a  longer  period  MR-Generator  (2^1457,  i.e. 4.0e+438)  and
*   longer  computation  time  (2^31-1  modulus  calculations)  but  less memory space
*   consumption (47 integers).
*
*   See MRGRand49507 for a far  longer  period  (2^49507,  i.e. 1.2e+14903)  with  low
*   computation  time  too  (31-bits  modulus)  but  use  of  more  memory space (1597
*   integers).
*
*   See LFibRand78, LFibRand116, LFibRand668 and LFibRand1340  for  long  period  LFib
*   generators  (resp.  2^78,  2^116,  2^668  and 2^1340 periods,  i.e. resp. 3.0e+23,
*   8.3e+34, 1.2e+201 and 2.4e+403 periods) while same computation time and far higher
*   precision  (64-bits  calculations) but memory consumption (resp. 17,  55,  607 and
*   1279 integers).
*
*   Furthermore this class and all its inheriting sub-classes are callable. Example:
* @code
*     BaseRandom rand{}; // CAUTION: this won't compile since BaseRandom is an abstract class. Replace 'BaseRandom' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
*     std::cout << rand(a,b) << std::endl; // prints a uniform pseudo-random value within [a  , b)
* @endcode
*
*   Please notice that for simulating the roll of a dice you may use any of:
* @code
*     FastRand32 diceRoll{};                            // notice: use of FastRand32 is for sole example purpose
*     std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within range {1, ..., 6}
*     std::cout << diceRoll.randint(1, 6) << std::endl; // prints also a uniform roll within range {1, ..., 6}
* @endcode
*
*   Conforming to the former version PyRandLib  of  this  library,  next  methods  are
*   available:
*    |
*    |  betavariate(alpha, beta)
*    |      Beta distribution.
*    |      https://en.wikipedia.org/wiki/Beta_distribution
*    |
*    |      Conditions on the parameters are alpha > 0 and beta > 0.
*    |      Returned values range between 0 and 1.
*    |
*    |
*    |  binomialvariate(n=1, p=0.5)
*    |      Binomial distribution. Return the number of successes for n
*    |      independent trials with the probability of success in each
*    |      trial being p.
*    |      n >= 0, 0.0 <= p <= 1.0,
*    |      the result is an integer in the range 0 <= X <= n.
*    |
*    |
*    |  choice(seq)
*    |      Choose a random element from a non-empty sequence.
*    |
*    |
*    |  expovariate(lambda = 1.0)
*    |      Exponential distribution.
*    |      https://en.wikipedia.org/wiki/Exponential_distribution
*    |
*    |      lambda is 1.0 divided by the desired mean.  It should be
*    |      nonzero.
*    |      Returned values range from 0 to
*    |      positive infinity if lambda is positive, and from negative
*    |      infinity to 0 if lambda is negative.
*    |
*    |
*    |  gammavariate(alpha, beta)
*    |      Gamma distribution.  Not the gamma function!
*    |      https://en.wikipedia.org/wiki/Gamma_distribution
*    |
*    |      Conditions on the parameters are alpha > 0 and beta > 0.
*    |
*    |
*    |  gauss(mu, sigma)
*    |      Gaussian distribution.
*    |      https://en.wikipedia.org/wiki/Normal_distribution
*    |
*    |      mu is the mean, and sigma is the standard deviation.  This is
*    |      slightly faster than the normalvariate() function.
*    |
*    |      Not thread-safe without a lock around calls.
*    |
*    |
*    |  getstate()
*    |      Return internal state; can be passed to setstate() later.
*    |
*    |
*    |  lognormvariate(mu, sigma)
*    |      Log normal distribution.
*    |      https://en.wikipedia.org/wiki/Log-normal_distribution
*    |
*    |      If you take the natural logarithm of this distribution, you'll get a
*    |      normal distribution with mean mu and standard deviation sigma.
*    |      mu can have any value, and sigma must be greater than zero.
*    |
*    |
*    |  normalvariate(mu, sigma)
*    |      Normal distribution.
*    |      https://en.wikipedia.org/wiki/Normal_distribution
*    |
*    |      mu is the mean, and sigma is the standard deviation.
*    |
*    |
*    |  paretovariate(alpha)
*    |      Pareto distribution.  alpha is the shape parameter.
*    |      https://en.wikipedia.org/wiki/Pareto_distribution
*    |
*    |
*    |  randbytes(n)
*    |      Generate n random bytes.
*    |      This method should not be used for generating security tokens.
*    |
*    |
*    |  randint(a, b)
*    |      Return random integer in range [a, b], including both end points.
*    |
*    |
*    |  randrange(start, stop, step=1)
*    |      Choose a random item from range(start, stop[, step]).
*    |
*    |      This fixes the problem with randint() which includes the
*    |      endpoint.
*    |
*    |
*    |  sample(population, k)
*    |      Chooses k unique random elements from a population sequence or set.
*    |
*    |      Returns a new list containing elements from the population while
*    |      leaving the original population unchanged.  The resulting list is
*    |      in selection order so that all sub-slices will also be valid random
*    |      samples.  This allows raffle winners (the sample) to be partitioned
*    |      into grand prize and second place winners (the subslices).
*    |
*    |      Members of the population need not be hashable or unique.  If the
*    |      population contains repeats, then each occurrence is a possible
*    |      selection in the sample.
*    |
*    |      To choose a sample in a range of integers, use range as an argument.
*    |      This is especially fast and space efficient for sampling from a
*    |      large population:   sample(range(10000000), 60)
*    |
*    |
*    |  seed()
*    |  seed(a)
*    |      Initialize internal state.
*    |      No argument seeds from current time.
*    |      If *a* is an int, all bits are used.
*    |
*    |
*    |  setstate(state)
*    |      Restore internal state from object returned by getstate().
*    |
*    |
*    |  shuffle(x)
*    |      x-> shuffle vector x in place.
*    |
*    |
*    |  triangular()
*    |  triangular(low, high)
*    |  triangular(low, high, mode)
*    |      Triangular distribution.
*    |      http://en.wikipedia.org/wiki/Triangular_distribution
*    |
*    |      Continuous distribution bounded by given lower and upper limits,
*    |      and having a given mode value in-between.
*    |      When missing, low = 0.0, high = 1.0, mode = (low + high) / 2
*    |
*    |
*    |  uniform()
*    |  uniform(b)
*    |  uniform(a, b)
*    |      Get a random number in the range [a, b) or [a, b] depending on rounding.
*    |      When missing, a = 0.0 and b = 1.0
*    |
*    |
*    |  vonmisesvariate(mu, kappa)
*    |      Circular data distribution.
*    |      https://en.wikipedia.org/wiki/Von_Mises_distribution
*    |
*    |      mu is the mean angle, expressed in radians between 0 and 2*pi, and
*    |      kappa is the concentration parameter, which must be greater than or
*    |      equal to zero.  If kappa is equal to zero, this distribution reduces
*    |      to a uniform random angle over the range 0 to 2*pi.
*    |
*    |
*    |  weibullvariate(alpha, beta)
*    |      Weibull distribution.
*    |      https://en.wikipedia.org/wiki/Weibull_distribution
*    |
*    |      alpha is the scale parameter and beta is the shape parameter.
*/
template<typename SeedStateT, typename OutputT = std::uint32_t, const std::uint8_t OUTPUT_BITS = 32>
class BaseRandom
{
public:
    //---   Wrappers   ------------------------------------------------------
    using state_type = SeedStateT;
    using output_type = OutputT;


    //---   Constructors / Destructor   -------------------------------------
    inline BaseRandom(const SeedStateT& seed) noexcept  //!< valued constructor.
    {
        setstate(seed);
    }

    BaseRandom() noexcept = default;                    //!< default empty constructor
    BaseRandom(const BaseRandom&) noexcept = default;   //!< default copy constructor.
    BaseRandom(BaseRandom&&) noexcept = default;        //!< default move constructor.

    virtual ~BaseRandom() noexcept = default;           //!< default destructor.


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * This method MUST be implemented in inheriting classes.
    * @return an integer value coded on OUTPUT_BITS bits, related to the uniform distribution.
    */
    inline virtual const output_type next()
    {
        return output_type(0);
    }


    //---   Uniform [0, 1.0) random   ---------------------------------------
    /** @brief The uniform distribution on [0.0, 1.0).
    *
    * @return a double value uniformly contained within range [0.0, 1.0).
    */
    inline const double random() noexcept
    {
        return next() * _NORMALIZE;
    }


    //---   Assignments operators   -----------------------------------------
    BaseRandom& operator= (const BaseRandom&) noexcept = default;   //!< default copy assignment.
    BaseRandom& operator= (BaseRandom&&) noexcept = default;        //!< default move assignment.

    inline BaseRandom& operator= (const SeedStateT& seed) noexcept  //!< valued assignment.
    {
        setstate(seed);
    }


    //---   Calling operators   ---------------------------------------------
    /** @brief Empty Call operator.
    *
    * @return a value that is uniformly contained within range [0.0, 1.0).
    */
    inline const double operator() () noexcept
    {
        return uniform();
    }

    /** @brief Valued call operator (1 scalar).
    *
    * @return a value that is uniformly contained within range [0; max).
    */
    template<typename T>
    const T operator() (const T max)
    {
        if (!std::is_arithmetic<T>::value)
            throw ArithmeticValueTypeException();

        return uniform(max);
    }

    /**@brief Valued call operator (max and n scalars).
    *
    * @return a value that is uniformly contained within range [min; max).
    */
    template<typename T>
    std::vector<T> operator() (const T max, const std::size_t n)
    {
        if (!std::is_arithmetic<T>::value)
            throw ArithmeticValueTypeException();
        if (n == 0)
            throw ZeroLengthException();

        std::vector<T> out(n);
        for (T& o : out)
            o = uniform(max);
        return out;
    }

    /**@brief Valued call operator (min, max and n scalars).
    *
    * @return a value that is uniformly contained within range [min; max).
    */
    template<typename T>
    std::vector<T> operator() (const T min, const T max, const std::size_t n)
    {
        if (!std::is_arithmetic<T>::value)
            throw ArithmeticValueTypeException();
        if (n == 0)
            throw ZeroLengthException();

        std::vector<T> out(n);
        for (T& o : out)
            o = uniform(min, max);
        return out;
    }

    /** @brief Valued call operator (1 std::vector of scalars).
    *
    * @return  a vector of values that are uniformly contained within
    *   the interval [0; max[i]) -- i being the index of the value in
    *   the returned vector.
    */
    template<typename T>
    std::vector<T> operator() (const std::vector<T>& max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();

        std::vector<T> out(max.size());
        auto max_it{ max.cbegin() };
        for (T& o : out)
            o = uniform(*max_it++);
        return out;
    }

    /** @brief Valued call operator (1 std::array of scalars).
    *
    * @return  an array of values that are uniformly contained within
    *   the interval [0; max[i]) -- i being the index of the value in
    *   the returned array.
    */
    template<typename T, const std::size_t n>
    std::array<T, n> operator() (const std::array<T, n>& max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();
        if (n == 0)
            throw ZeroLengthException();

        std::array<T, n> out(max.size());
        auto max_it{ max.cbegin() };
        for (T& o : out)
            o = uniform(*max_it++);
        return out;
    }

    /** @brief Valued call operator (2 std::vector of scalars).
    *
    * @return  a vector of values that are uniformly contained within the
    *   interval [min[i]; max[i]) - i being the index of the value in the
    *   returned vector.
    */
    template<typename T>
    std::vector<T> operator() (const std::vector<T>& min, const std::vector<T>& max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();

        const std::size_t count = std::min(min.size(), max.size());
        std::vector<T> out(count);
        auto min_it = min.cbegin();
        auto max_it = max.cbegin();
        for (T& o : out )
            o = uniform(*min_it++, *max_it++);
        return out;
    }

    /** @brief Valued call operator (2 std::array of scalars).
    *
    * @return  an array of values that are uniformly contained within the
    *   interval [min[i]; max[i]) - i being the index of the value in the
    *   returned array.
    */
    template<typename T, const std::size_t n>
    std::array<T, n> operator() (const std::array<T, n>& min, const std::array<T, n>& max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();
        if (n == 0)
            throw ZeroLengthException();

        const std::size_t count = std::min(min.size(), max.size());
        std::array<T, n> out(count);
        auto min_it = min.cbegin();
        auto max_it = max.cbegin();
        for (T& o : out )
            o = uniform(*min_it++, *max_it++);
        return out;
    }


    //---   Operations   ----------------------------------------------------
    /** @brief Returns the number of successes for n>=0 independent trials. */
    template<typename CountT, typename ProbaT>
    const CountT binomialvariate(CountT n = 1, const ProbaT p = ProbaT(0.5))
    {
        if (!std::is_integral<CountT>::value)
            throw IntegralValueTypeException();
        if (!std::is_floating_point<ProbaT>::value)
            throw FloatingPointTypeException();

        if (n < 0)
            throw PositiveValueException();
        if (p < 0.0 || p > 1.0)
            throw ProbaOutOfRangeException();

        CountT count{ 0 };
        while (n > 0) {
            count += uniform() < p;
            --n;
        }

        return count;
    }

    /** @brief Chooses a random element from a non-empty sequence (std::vector). */
    template<typename T>
    const T& choice(const std::vector<T>& seq)
    {
        const std::size_t n{ seq.size() };
        if (n == 0)
            throw ChoiceEmptySequenceException();
        return seq[uniform(n)];
    }

    /** @brief Chooses a random element from a non-empty sequence (std::array). */
    template<typename T, const std::size_t n>
    const T& choice(const std::array<T, n>& seq) noexcept(false)
    {
        if (n == 0)
            throw ChoiceEmptySequenceException();
        return seq[uniform(n)];
    }


    /** @brief Returns the internal state of this PRNG; can be passed to setstate() later. */
    inline struct _InternalState& getstate() const noexcept
    {
        return _state;
    }


    /** @brief Returns n values that are uniformly contained within range [0.0, 1.0). */
    template<typename T>
    inline std::vector<T> n_evaluate(const std::size_t n)
    {
        if (!std::is_floating_point<T>::value)
            throw FloatingPointTypeException();

        return (*this)(1.0, n);
    }

    /** @brief Returns a vector of n vectors that each contain m values in range [min[i]; max[i]). */
    template<typename T>
    std::vector<std::vector<T>> n_evaluate(const std::size_t n, const std::vector<T>& min, const std::vector<T>& max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();
        if (n == 0)
            throw ZeroLengthException();

        const std::size_t count = std::min({ n, min.size(), max.size() });
        std::vector<T> out(n);
        for (auto out_it = out.begin(), min_it = min.cbegin(), max_it = max.cbegin(); out_it != out.begin() + count; )
            *out_it++ = uniform(*min_it++, *max_it++);
        return out;
    }

    /** @brief Returns an array of n values that are uniformly contained within range [0.0, 1.0). */
    template<typename T, const std::size_t n>
    inline std::array<T, n> n_evaluate()
    {
        if (!std::is_floating_point<T>::value)
            throw FloatingPointTypeException();
        if (n == 0)
            throw ZeroLengthException();

        return n_evaluate(T(1.0));
    }

    /** @brief Returns n values that are uniformly contained within range [0, max). */
    template<typename T, const std::size_t n>
    std::array<T, n> n_evaluate(const T max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();

        std::array<T, n> out;
        for (T& o : out)
            o = uniform(max);
        return out;
    }

    /** @brief Returns n values that are uniformly contained within range [min, max). */
    template<typename T, const std::size_t n>
    std::array<T, n> n_evaluate(const T min, const T max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();

        std::array<T, n> out;
        for (T& o : out)
            o = uniform(min, max);
        return out;
    }

    /** @brief Returns an array of n arrays that each contain m values in range [0; max[i]). */
    template<typename T, const std::size_t n, const std::size_t m>
    std::array<std::array<T, m>, n> n_evaluate(const std::array<T, m>& max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();

        std::array<std::array<T, m>, n> out;
        for (auto& o : out)
            o = (*this)(max);
        return out;
    }

    /** @brief Returns an array of n arrays that each contain m values in range [min[i]; max[i]). */
    template<typename T, const std::size_t n, const std::size_t m>
    std::array<std::array<T, m>, n> n_evaluate(const std::array<T, m>& min, const std::array<T, m>& max)
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();

        std::array<std::array<T, m>, n> out;
        for (auto& o : out)
            o = (*this)(min, max);
        return out;
    }


    /** @brief Generates n random bytes.
    *
    * This method should not be used for generating security tokens.
    */
    inline std::vector<std::uint8_t> randbytes(const std::uint32_t n)
    {
        if (n == 0)
            throw ZeroLengthException();

        std::vector<std::uint8_t> out(n);
        for (std::uint8_t& b : out)
            b = (std::uint8_t)uniform(256ul);
        return out;
    }


    /** @brief Returns random integer in range [a, b], including both end points.
    *
    * Template argument T must be an integral type.
    */
    template<typename T>
    inline const T randint(const T a, const int b)
    {
        if (!std::is_integral<T>::value)
            throw IntegralValueTypeException();

        return uniform(a, b + 1);
    }


    /** @brief Chooses a random item from range [start, stop) with specified step. */
    template<typename T>
    const T randrange(const T start, const T stop, const T step = T(1))
    {
        if (!std::is_arithmetic<T>::value)
            throw MaxValueTypeException();
        if (start == stop)
            throw RangeSameValuesException();

        const T width{ stop - start };

        if (step == 1)
            return start + uniform(width);

        const T n{ (width + step + (step > 0 ? -1 : 1)) / step };
        return start + step * uniform(n);
    }


    /** @brief Chooses k unique random elements from a population sequence (out std::vector, in container, default counts = 1).
    *
    * Evaluates a vector containing  elements  from  the  population  while
    * leaving  the  original  population  unchanged.  The resulting list is
    * in selection order so that all sub-slices will also be  valid  random
    * samples.  This  allows  raffle winners (the sample) to be partitioned
    * into grand prize and second place winners (the subslices).
    *
    * Members of the population need not be  hashable  or  unique.  If  the
    * population  contains  repeats,  then  each  occurrence  is a possible
    * selection in the sample.
    *
    * Repeated elements can be specified one at a time or with the optional
    * counts parameter.  For example:
    *     sample(['red', 'blue'], counts=[4, 2], k=5);
    * is equivalent to:
    *     sample(['red', 'red', 'red', 'red', 'blue', 'blue'], k=5);
    *
    * To choose a sample from a range of  integers,  use  range()  for  the
    * population  argument.  This  is  especially  fast and space efficient
    * for sampling from a large population:
    *     sample(range(10000000), 60);
    *
    * Important notice: the ContainerType class MUST provide method '.size()'.
    */
    template<typename T>
    void sample(std::vector<T>& out, const std::vector<T>& population, const std::size_t k)
    {
        const std::size_t n{ population.size() };
        if (k > n)
            throw SampleCountException();

        out.clear();
        out.resize(k);
        std::vector<T> samples{ population };

        for (std::size_t i = 0; i < k; ++i) {
            const std::size_t index = uniform(i, n);
            out.emplace_back(samples[index]);
            std::swap(samples[i], samples[index]);
        }
    }

    /** @brief Chooses k unique random elements from a population sequence (out std::array<>, in std::array<>, default counts = 1).
    *
    * Evaluates a vector containing  elements  from  the  population  while
    * leaving  the  original  population  unchanged.  The resulting list is
    * in selection order so that all sub-slices will also be  valid  random
    * samples.  This  allows  raffle winners (the sample) to be partitioned
    * into grand prize and second place winners (the subslices).
    *
    * Members of the population need not be  hashable  or  unique.  If  the
    * population  contains  repeats,  then  each  occurrence  is a possible
    * selection in the sample.
    *
    * Repeated elements can be specified one at a time or with the optional
    * counts parameter.  For example:
    *     sample(['red', 'blue'], counts=[4, 2], k=5);
    * is equivalent to:
    *     sample(['red', 'red', 'red', 'red', 'blue', 'blue'], k=5);
    *
    * To choose a sample from a range of  integers,  use  range()  for  the
    * population  argument.  This  is  especially  fast and space efficient
    * for sampling from a large population:
    *     sample(range(10000000), 60);
    */
    template<typename T, const std::size_t k, const std::size_t n>
    void sample(std::array<T, k>& out, const std::array<T, n>& population)
    {
        if (k > n)
            throw SampleCountException();

        std::array<T, n> samples{ population };

        for (std::size_t i = 0; i < k; ++i) {
            const std::size_t index = uniform(i, n);
            out[i] = samples[index];
            std::swap(samples[i], samples[index]);
        }
    }


    /** @brief Chooses k unique random elements from a population sequence (std::vector<>, with counts vector).
    *
    * Evaluates a vector containing  elements  from  the  population  while
    * leaving  the  original  population  unchanged.  The resulting list is
    * in selection order so that all sub-slices will also be  valid  random
    * samples.  This  allows  raffle winners (the sample) to be partitioned
    * into grand prize and second place winners (the subslices).
    *
    * Members of the population need not be  hashable  or  unique.  If  the
    * population  contains  repeats,  then  each  occurrence  is a possible
    * selection in the sample.
    *
    * Repeated elements can be specified one at a time or with the optional
    * counts parameter.  For example:
    *     sample(['red', 'blue'], counts=[4, 2], k=5);
    * is equivalent to:
    *     sample(['red', 'red', 'red', 'red', 'blue', 'blue'], k=5);
    *
    * To choose a sample from a range of  integers,  use  range()  for  the
    * population  argument.  This  is  especially  fast and space efficient
    * for sampling from a large population:
    *     sample(range(10000000), 60);
    *
    * The implemented algorithm in CppRandLib is NOT the one that is  implem-
    * ented  in  Python 3  library Random.  In CppRandLib, we use a simpler 
    * form which should be more efficient as  long  as  population's  items 
    * are  movable  (i.e.  Move  Constructor  and maybe Move assignment are 
    * defined).
    */
    template<typename T, typename C>
    inline void sample(std::vector<T>& out, const std::vector<T>& population, const std::vector<C>& counts, const std::size_t k)
    {
        if (!std::is_integral<T>::value)
            throw IntegralValueTypeException();
        if (counts.size() != population.size())
            throw SampleSizesException();
        if (!std::is_integral<C>::value)
            throw SampleCountsTypeException();

        const std::size_t samples_count = std::size_t(std::accumulate(counts.begin(), counts.end(), C(0)));
        if (k > samples_count)
            throw SampleCountException();

        std::vector<T> samples(samples_count);
        auto c_it = counts.cbegin();
        auto s_it = samples.begin();
        for (auto& p : population) {
            for (std::size_t j = std::size_t(*c_it++); j > 0; --j)
                *s_it++ = p;
        }

        out.clear();
        out.resize(k);
        for (std::size_t i = 0; i < k; ++i) {
            const std::size_t index = uniform(i, samples_count);
            out.emplace_back(samples[index]);
            std::swap(samples[i], samples[index]);
        }
    }


    /** @brief Chooses k unique random elements from a population sequence (std::array<>, with counts array).
    *
    * Evaluates a vector containing  elements  from  the  population  while
    * leaving  the  original  population  unchanged.  The resulting list is
    * in selection order so that all sub-slices will also be  valid  random
    * samples.  This  allows  raffle winners (the sample) to be partitioned
    * into grand prize and second place winners (the subslices).
    *
    * Members of the population need not be  hashable  or  unique.  If  the
    * population  contains  repeats,  then  each  occurrence  is a possible
    * selection in the sample.
    *
    * Repeated elements can be specified one at a time or with the optional
    * counts parameter.  For example:
    *     sample(['red', 'blue'], counts=[4, 2], k=5);
    * is equivalent to:
    *     sample(['red', 'red', 'red', 'red', 'blue', 'blue'], k=5);
    *
    * To choose a sample from a range of  integers,  use  range()  for  the
    * population  argument.  This  is  especially  fast and space efficient
    * for sampling from a large population:
    *     sample(range(10000000), 60);
    *
    * The implemented algorithm in CppRandLib is NOT the one that is implem-
    * ented  in  Python 3  library Random.  In CppRandLib, we use a simpler
    * form which should be more efficient as  long  as  population's  items
    * are  movable  (i.e.  Move  Constructor  and maybe Move assignment are
    * defined).
    */
    template<typename T, typename C, const std::size_t k, const std::size_t n>
    inline void sample(std::array<T, k>& out, const std::array<T, n>& population, const std::array<C, n>& counts)
    {
        if (!std::is_integral<C>::value)
            throw IntegralValueTypeException();

        const std::size_t samples_count = std::size_t(std::accumulate(counts.begin(), counts.end(), C(0)));
        if (k > samples_count)
            throw SampleCountException();

        std::vector<T> samples;
        samples.resize(samples_count);
        auto c_it = counts.begin();
        for (auto& p : population) {
            for (std::size_t j = std::size_t(*c_it++); j > 0; --j)
                samples.emplace_back(p);
        }

        for (std::size_t i = 0; i < k; ++i) {
            const std::size_t index = uniform(i, samples_count);
            out[i] = samples[index];
            std::swap(samples[i], samples[index]);
        }
    }


    /** @brief Initializes internal state (empty signature).
    *
    * The seed value is evaluated from shuffled and xored current time.
    */
    inline void seed() noexcept
    {
        setstate();
    }


    /** @brief Initializes internal state from a seed state. */
    template<typename SeedStateT>
    inline void seed(const SeedStateT& seed_) noexcept
    {
        setstate(seed_);
    }


    /** @brief Initializes internal state from a long integer. */
    inline void seed(const std::uint32_t seed_) noexcept
    {
        setstate(seed_);
    }

    /** @brief Sets the internal state of this PRNG from shuffled and xored current time.
    *
    * MUST BE IMPLEMENTED in inheriting classes.
    */
    virtual void setstate() noexcept
    {}

    /** @brief Restores the internal state of this PRNG from seed. */
    inline void setstate(const SeedStateT& seed) noexcept
    {
        _state.seed = seed;
        _state.gauss_valid = false;
    }

    /** @brief Restores the internal state of this PRNG from seed and gauss_next. */
    inline void setstate(const SeedStateT& seed, const double gauss_next) noexcept
    {
        _state.seed = seed;
        _state.gauss_next = gauss_next;
        _state.gauss_valid = true;
    }

    /** @brief Restores the internal state of this PRNG from object returned by getstate(). */
    inline void setstate(const _InternalState& state) noexcept
    {
        _state = state;
    }


    /** @brief Shuffles specified sequence in place.
    *
    * The container type must provide method '.size()'.
    */
    template<typename ContainerType>
    void shuffle(ContainerType& seq)
    {
        if (!m_is_indexable<ContainerType>::value)
            throw IndexableContainerException();

        const std::size_t n{ seq.size() };
        for (std::size_t i = 0; i < n - 1; ++i) {
            const std::size_t index = uniform(i, n);
            std::swap(seq[i], seq[index]);
        }
    }


    //---   Random distribution functions   ---------------------------------
    /** @brief Beta distribution.
    *
    * @param alpha: double, must be greater than 0
    * @param beta: double, must be greater than 0
    * @return a value in interval [0.0, 1.0].
    * 
    * Important notice: the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    * The original code is due to Janne Sinkkonen and matches all the std 
    * texts (e.g., Knuth Vol 2 Ed 3 pg 134 "the beta distribution").
    */
    const double betavariate(const double alpha, const double beta)
    {
        if (alpha <= 0.0 || beta <= 0.0)
            throw AlphaBetaArgsException();

        const double y = gammavariate(alpha, 1.0);
        return (y == 0.0) ? 0.0 : (y / (y + gammavariate(beta, 1.0)));
    }



    /** @brief Exponential distribution.
    *
    * @param lambda: double, this should get the value (1.0 / desired_mean).
    *   It cannot be 0.0.
    * @return a value in range [0.0, Infinity) if lambda is  positive,  or
    *   a value in range (-Infinity, 0.0] if lambda is negative.
    * 
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++. 
    */
    const double expovariate(const double lambda = 1.0)
    {
        if (lambda == 0.0)
            throw ExponentialZeroLambdaException();

        return -std::log(1.0 - uniform());
    }

 

    /** @brief Gamma distribution. This is NOT the gamma function!
    *
    * The probability distribution function is :
    *            x^(alpha - 1) * std::exp(-x / beta)
    *   pdf(x) = -----------------------------------
    *              std::tgamma(alpha) * beta^alpha
    * where:
    *   pdf is the probability density function
    *   a^b is std::pow(a, b)
    *   std::tgamma() is the Gamma funtion as implemented in the c++ math library.
    * 
    * The Gamma function is the below integral summation from 0 to Infinity:
    *   Γ(x) = ∫0∞ t^(x−1) * std::exp(−t) dt
    * 
    * @param alpha : double, the shape parameter - must be greater than 0.0.
    * @param beta : double, the scale parameter - must be greater than 0.0.
    *   With these two arguments: mean is alpha * beta and variance is alpha * beta * beta
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++. 
    * As such, some comments present in the Python original code have been
    * copied as is in this c++ implementation, naming then the authors of 
    * the related parts of code.
    */
    const double gammavariate(const double alpha, const double beta)
    {
        if (alpha <= 0.0 || beta <= 0.0)
            throw AlphaBetaArgsException();

        if (alpha > 1.0) {
            // Uses R.C.H.Cheng paper
            // "The generation of Gamma variables with non - integral shape parameters",
            // Applied Statistics, (1977), 26, No. 1, p71 - 74
            constexpr double EPSILON{ 1e-7 };
            const double     INV_A{ std::sqrt(2.0 * alpha - 1.0) };
            const double     B{ alpha - LOG4 };
            const double     C{ alpha + INV_A };

            while (true) {
                const double u1{ uniform() };
                if (EPSILON < u1 && u1 < 1.0 - EPSILON) {
                    const double u2{ 1.0 - uniform() };
                    const double v{ std::log(u1 / (1.0 - u1)) / INV_A };
                    const double x{ alpha - std::exp(v) };
                    const double z{ u1 * u1 * u2 };
                    const double r{ B + C * v - x };
                    if (r + SG_MAGICCONST - 4.5 * z >= 0.0 || r >= std::log(z))
                        // this will eventually happen
                        return x * beta;
                }
            }
        }
        else if (alpha == 1.0) {
            // this is exponential distribution with lambda = 1 / beta
            return -std::log(1.0 - uniform()) * beta;
        }
        else {
            // alpha is between 0 and 1 (exclusive)
            // so, uses ALGORITHM GS of Statistical Computing - Kennedy & Gentle
            double x, u;
            while (true) {
                u = uniform();
                const double b{ (E + alpha) / E };
                const double p{ b * u };
                x = p <= 1.0 ? std::pow(p, 1.0 / alpha) : -std::log((b - p) / alpha);
                u = uniform();
                if (p <= 1.0) {
                    if (u <= std::exp(-x))
                        break;
                }
                else if (u <= std::pow(x, alpha - 1.0))
                    break;
            }
            return x * beta;
        }
    }



    /** @brief Default Gaussian distribution (mean=0.0, stdev=1.0).
    *
    * This is slightly faster than the normalvariate() function.
    * Notice: not thread-safe without a lock around calls.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double gauss() noexcept
    {
        return gauss(0.0, 1.0);
    }


    /** @brief Gaussian distribution (mean=mu, stdev=sigma).
    *
    * mu is the mean, and sigma is the standard deviation.
    * mu can be any value, sigma must be greater than 0.0.
    * This is slightly faster than the normalvariate() function.
    *
    * Notice: not thread-safe without a mutex around calls.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    const double gauss(const double mu, const double sigma)
    {
        if (sigma <= 0.0)
            throw GaussSigmaException();

        double z;
        if (_state.gauss_valid) {
            z = _state.gauss_next;
            _state.gauss_valid = false;
        }
        else {
            const double u{ uniform(TWO_PI) };
            const double g{ std::sqrt(-2.0 * std::log(1.0 - uniform())) };
            z = std::cos(u) * g;
            _state.gauss_next = std::sin(u) * g;
            _state.gauss_valid = true;
        }

        return mu + z * sigma;
    }


    /** @brief Default Log normal distribution (mean=0.0, stdev=1.0).
    *
    * If you take the natural logarithm of this distribution, you'll get 
    * a normal distribution with mean 0.0 and standard deviation 1.0.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double lognormvariate() noexcept
    {
        return lognormvariate(0.0, 1.0);
    }


    /** @brief Log normal distribution (mean=mu, stdev=sigma).
    *
    * If you take the natural logarithm of this distribution, you'll get 
    * a normal distribution with mean mu and standard deviation sigma.
    * mu can have any value, and sigma must be greater than zero.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double lognormvariate(const double mu, const double sigma) noexcept
    {
        return std::exp(gauss(mu, sigma));
    }


    /** @brief Normal distribution (mean=0.0, stdev=1.0).
    *
    * The Python version of this method uses Kindermanand Monahan  method.
    * Reference: Kinderman, A.J.and Monahan, J.F., "Computer generation of 
    * random variables using the ratio of  uniform  deviates",  ACM  Trans
    * Math Software, 3, (1977), pp257 - 260.
    * This method is slightlly slower than the gauss  method,  so  we  call 
    * gauss() instead here, in CppRandLib.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double normalvariate() noexcept
    {
        return gauss();
    }


    /** @brief Normal distribution (mean=mu, stdev=sigma).
    *
    * mu is the mean, and sigma is the standard deviation.
    * mu can be any value, sigma must be greater than 0.0.
    *
    * The Python version of this method uses Kindermanand Monahan  method.
    * Reference: Kinderman, A.J.and Monahan, J.F., "Computer generation of
    * random variables using the ratio of  uniform  deviates",  ACM  Trans
    * Math Software, 3, (1977), pp257 - 260.
    * This method is slightlly slower than the gauss method,  so  we  call
    * gauss() instead here, in CppRandLib.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double normalvariate(const double mu, const double sigma) noexcept
    {
        return gauss(mu, sigma);
    }


    /** @brief Pareto distribution.
    *
    * @param alpha: double, the shape parameter. Cannot be 0.0.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    const double paretovariate(const double alpha)
    {
        if (alpha == 0.0)
            throw ParetoArgsValueException();

        // Jain, pg. 495
        return std::pow(1.0 - random(), -1.0 / alpha);
    }


    /** @brief Triangular distribution (low=0.0, high=1.0, mode=0.5). */
    inline const double triangular()
    {
        return triangular(0.0, 1.0, 0.5);
    }


    /** @brief Triangular distribution (low, high, default mode). */
    template<typename T>
    const T triangular(const T low, const T high)
    {
        if (!std::is_arithmetic<T>::value)
            throw ArithmeticValueTypeException();

        return triangular(low, high, (low + high) / 2);
    }


    /** @brief Triangular distribution (low, high, mode).
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    template<typename T>
    const T triangular(T low, T high, const T mode)
    {
        if (!std::is_arithmetic<T>::value)
            throw ArithmeticValueTypeException();

        if (high == low)
            return high;
        
        double u{ uniform() };
        double c{ double(mode - low) / double(high - low) };
        if (u > c) {
            u = 1.0 - u;
            c = 1.0 - c;
            std::swap(low, high);
        }

        return T(double(low) + double(high - low) * std::sqrt(u * c));
    }


    /** @brief Uniform distribution [0.0, 1.0). */
    inline const double uniform() noexcept
    {
        return random();
    }


    /** @brief Uniform distribution (0.0, max). */
    template<typename T>
    inline const T uniform(const T max)
    {
        if (!std::is_arithmetic<T>::value)
            throw ArithmeticValueTypeException();

        return T(max * random());
    }


    /** @brief Uniform distribution (min and max values).*/
    template<typename T>
    inline const T uniform(const T min, const T max)
    {
        if (!std::is_arithmetic<T>::value)
            throw ArithmeticValueTypeException();

        return min + T(double(max - min) * random());
    }


    /** @brief Circular data distribution.
    * 
    * @param mu is the mean angle, expressed in radians between 0 and 2*pi
    * @param kappa is the concentration parameter, which must be greater than or
    *   equal to zero.  If kappa is equal to zero, this distribution reduces
    *   to a uniform random angle over the range 0 to 2*pi.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++. 
    * As such, some comments present in the Python original code have been
    * copied as is in this c++ implementation, naming then the authors of 
    * the related parts of code.
    */
    const double vonmisesvariate(const double mu, const double kappa)
    {
        // extracted from Python 3.11 comments:
        // Based upon an algorithm published in : Fisher, N.I.,
        // "Statistical Analysis of Circular Data", Cambridge University Press, 1993.
        //
        // Thanks to Magnus Kessler for a correction to the implementation of step 4.

        if (kappa <= 1e-6)
            return uniform(TWO_PI);

        const double s = 0.5 / kappa;
        const double r = s + std::sqrt(1.0 + s * s);
        double z;

        while (true) {
            z = std::cos(uniform(PI));
            const double d{ z / (r + z) };
            const double u{ uniform() };
            if (u < 1.0 - d * d || u < (1.0 - d) * std::exp(d))
                break;
        }

        const double q{ 1.0 / r };
        const double f{ (q + z) / (1.0 + q * z) };
        if (uniform() >= 0.5)
            return std::fmod(mu + std::acos(f), TWO_PI);
        else
            return std::fmod(mu - std::acos(f), TWO_PI);
    }


    /** @brief Weibull distribution.
    *
    * @param alpha: double, the scale parameter.
    * @param beta: double, the shape parameter. Must be non null.
    */
    const double weibullvariate(const double alpha, const double beta)
    {
        if (beta <= 0.0)
            throw WeibullArgsValueException();

        return alpha * std::pow(-std::log(1.0 - uniform()), 1.0 / beta);
    }


    //---   Exceptions   ----------------------------------------------------
     /** @brief Exponential law null lambda exception. */
    class AlphaBetaArgsException : public std::exception
    {
    public:
        const char* what() noexcept { return "both arguments alpha and beta must be greater than 0.0."; }
    };

    /** @brief Wrong argument type - not arithmetic. */
    class ArithmeticValueTypeException : public std::exception
    {
    public:
        const char* what() noexcept { return "Argument(s) must be an arithmetic type."; }
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

    /** @brief Wrong argument type - not floating point. */
    class FloatingPointTypeException : public std::exception
    {
    public:
        const char* what() noexcept { return "Argument(s) must be a floating pointg type."; }
    };

    /** @brief Exponential law null lambda exception. */
    class GaussSigmaException : public std::exception
    {
    public:
        const char* what() noexcept { return "value for argument sigma must be greater than 0.0."; }
    };

    /** @brief Wrong argument type - not integral. */
    class IndexableContainerException : public std::exception
    {
    public:
        const char* what() noexcept { return "Container type must be std::array or std::vector."; }
    };
    
    /** @brief Wrong argument type - not integral. */
    class IntegralValueTypeException : public std::exception
    {
    public:
        const char* what() noexcept { return "Argument(s) must be an integral type."; }
    };

    /** @brief Empty sequence exception. */
    class MaxValueTypeException : public std::exception
    {
    public:
        const char* what() noexcept { return "Type of values embedded in container must be arithmetic ones."; }
    };

    /** @brief Not same sizes of containers exception. */
    class MinMaxSizesException : public std::exception
    {
    public:
        const char* what() noexcept { return "'min' and 'max' container arguments must have same sizes."; }
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
        const char* what() { return "cannot sample a number of items that is greater than the overall population."; }
    };

    /** @brief Range arguments with same value exception. */
    class SampleCountsTypeException : public std::exception
    {
    public:
        const char* what() noexcept { return "type of 'counts' values must be integral."; }
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

    /** @brief Not a positive value exception. */
    class ZeroValueException : public std::exception
    {
    public:
        const char* what() noexcept { return "argument value must not be zero."; }
    };



protected:
    //---   Constants   -----------------------------------------------------
    static const double BPF;
    static const double E;
    static const double GAUSS_NULL;
    static const double LOG4;
    static const double NV_MAGICCONST;
    static const double PI;
    static const double RECIP_BPF;
    static const double SG_MAGICCONST;
    static const double TWO_PI;

    static const double _NORMALIZE;


    //---   Attributes   ----------------------------------------------------
    struct _InternalState
    {
        SeedStateT seed{};        //!< The internal current state of this PRNG
        double     gauss_next{};  //!< smart optimization for Gaussian distribution computation (1/2)
        bool       gauss_valid{}; //!< smart optimization for Gaussian distribution computation (2/2)
    } _state;


private:
    template<typename ContainerType>
    class m_is_indexable
    {
    public:
        static const bool value = false;
    };

    template<typename T>
    class m_is_indexable<std::vector<T>>
    {
    public:
        static const bool value = true;
    };

    template<typename T, const std::size_t n>
    class m_is_indexable<std::array<T, n>>
    {
    public:
        static const bool value = true;
    };
};

//---------------------------------------------------------------------------
template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::BPF{ 53 };  // Number of bits in a float

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::E{ std::exp(1.0) };

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::GAUSS_NULL = -1.0;

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::LOG4{ std::log(4.0) };

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::NV_MAGICCONST{ 4 * std::exp(-0.5) / std::sqrt(2.0) };

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::PI{ 3.14159265358979323846 };

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::RECIP_BPF{ std::exp2(-BPF) };

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::SG_MAGICCONST{ 1.0 + std::log(4.5) };

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::TWO_PI{ 2.0 * BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::PI };

template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const double BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>::_NORMALIZE{ 0.5 / (1ull << (OUTPUT_BITS - 1)) };
