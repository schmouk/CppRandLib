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
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <vector>

#include "../exceptions.h"
#include "../utils/seed_generation.h"
#include "../utils/type_traits.h"
#include "../utils/uint128.h"


//===========================================================================
/** @brief This is the base class for all pseudo-random numbers generators.
*
*   See FastRand32 for a 2^32 (i.e. 4.3e+9) period LC-Generator and  FastRand63  for a
*   2^63 (i.e. about 9.2e+18) period LC-Generator with low computation time.
*
*   See FastRand63 for a 2^63  (i.e.  about  9.2e+18)  period  LC-Generator  with  low
*   computation  time also,  longer period and quite better randomness characteristics 
*   than for FastRand32.

*   See Mrg287 for a short period  MR-Generator (2^287,  i.e. 2.49e+86)  with  low
*   computation time but 256 integers memory consumption.
*
*   See Mrg1457 for a  longer  period  MR-Generator  (2^1457,  i.e. 4.0e+438)  and
*   longer  computation  time  (2^31-1  modulus  calculations)  but  less memory space
*   consumption (47 integers).
*
*   See Mrg49507 for a far  longer  period  (2^49507,  i.e. 1.2e+14903)  with  low
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
*     BaseRandom rand{}; // CAUTION: replace 'BaseRandom' with any inheriting class constructor!
*     std::cout << rand() << std::endl;    // prints a uniform pseudo-random value within [0.0, 1.0)
*     std::cout << rand(b) << std::endl;   // prints a uniform pseudo-random value within [0.0, b)
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
*    |      Returned values range from 0 to positive infinity if lambda
*    |      is positive, and from negative infinity to 0 if lambda is
*    |      negative.
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
template<
    typename StateT,
    typename OutputT = std::uint32_t,
    const std::uint8_t OUTPUT_BITS = 8 * sizeof(OutputT)
>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
class BaseRandom
{
public:
    //---   Wrappers   ------------------------------------------------------
    using state_type = StateT;
    using output_type = OutputT;


    //---   Attributes   ----------------------------------------------------
    struct _InternalState
    {
        StateT state{};       //!< The internal current state of this PRNG
        double gauss_next{};  //!< smart optimization for Gaussian distribution computation (1/2)
        bool   gauss_valid{}; //!< smart optimization for Gaussian distribution computation (2/2)
    } _internal_state;


    //---   Constructors / Destructor   -------------------------------------
    BaseRandom() noexcept = default;                    //!< default empty constructor
    BaseRandom(const BaseRandom&) noexcept = default;   //!< default copy constructor.
    BaseRandom(BaseRandom&&) noexcept = default;        //!< default move constructor.

    virtual ~BaseRandom() noexcept = default;           //!< default destructor.


    //---   Assignments operators   -----------------------------------------
    BaseRandom& operator= (const BaseRandom&) noexcept = default;   //!< default copy assignment.
    BaseRandom& operator= (BaseRandom&&) noexcept = default;        //!< default move assignment.

    inline BaseRandom& operator= (const StateT& seed) noexcept  //!< valued assignment.
    {
        setstate(seed);
        return *this;
    }


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * This method is pure virtual. It MUST be overriden in inheriting classes.
    * @return an integer value coded on OUTPUT_BITS bits.
    */
    inline virtual const output_type next() noexcept
    {
        return output_type(0);
    }


    //---   Uniform [0, 1.0) random   ---------------------------------------
    /** @brief The uniform distribution on [0.0, 1.0).
    *
    * @return a double value uniformly contained within range [0.0, 1.0).
    */
    template<typename T = double>
        requires std::is_floating_point_v<T>
    inline const T random() noexcept
    {
        return T(double(next()) * _NORMALIZE);
    }

    template<>
    inline const long double random() noexcept
    {
        return (long double)next() * _NORMALIZE_LD;
    }


    //---   Calling operators   ---------------------------------------------
    /** @brief Empty Call operator.
    *
    * @return a value that is uniformly contained within range [0.0, 1.0).
    */
    template<typename T = long double>
    inline const T operator() () noexcept
    {
        return uniform<T>();
    }

    /** @brief Valued call operator (1 scalar).
    *
    * @return a value that is uniformly contained within range [0; max).
    */
    template<typename T = OutputT>
        requires std::is_arithmetic_v<T>
    inline const T operator() (const T max) noexcept;

    /**@brief Valued call operator (max and n scalars).
    *
    * @return a value that is uniformly contained within range [min; max).
    */
    template<typename T = OutputT>
        requires std::is_arithmetic_v<T>
    std::vector<T> operator() (const T max, const std::size_t n) noexcept(false);

    /**@brief Valued call operator (min, max and n scalars).
    *
    * @return a value that is uniformly contained within range [min; max).
    */
    template<typename T>
        requires std::is_arithmetic_v<T>
    std::vector<T> operator() (const T min, const T max, const std::size_t n) noexcept(false);

    /** @brief Valued call operator (1 std::vector of scalars).
    *
    * @return  a vector of values that are uniformly contained within
    *   the interval [0; max[i]) -- i being the index of the value in
    *   the returned vector.
    */
    template<typename T>
        requires std::is_arithmetic_v<T>
    std::vector<T> operator() (const std::vector<T>& max) noexcept(false);

    /** @brief Valued call operator (1 std::array of scalars).
    *
    * @return  an array of values that are uniformly contained within
    *   the interval [0; max[i]) -- i being the index of the value in
    *   the returned array.
    */
    template<typename T, const std::size_t n>
        requires std::is_arithmetic_v<T> && (n != 0)
    std::array<T, n> operator() (const std::array<T, n>& max) noexcept
    {
        std::array<T, n> out;
        auto max_it{ max.cbegin() };
        std::ranges::generate(out, [&]() { return uniform<T>(*max_it++); });
        return out;
    }

    /** @brief Valued call operator (2 std::vector of scalars).
    *
    * @return  a vector of values that are uniformly contained within
    *   the range [min[i]; max[i]), i being the index of the value in
    *   the returned vector.
    */
    template<typename T>
        requires std::is_arithmetic_v<T>
    std::vector<T> operator() (const std::vector<T>& min, const std::vector<T>& max) noexcept;

    /** @brief Valued call operator (2 std::array of scalars).
    *
    * @return  an array of values that are uniformly contained within
    *   the range [min[i]; max[i]), i being the index of the value in
    *   the returned array.
    */
    template<typename T, const std::size_t n>
        requires std::is_arithmetic_v<T> && (n != 0)
    std::array<T, n> operator() (const std::array<T, n>& min, const std::array<T, n>& max) noexcept
    {
        std::array<T, n> out;
        auto min_it = min.cbegin();
        auto max_it = max.cbegin();
        std::ranges::generate(out, [&]() { return uniform<T>(*min_it++, *max_it++); });
        return out;
    }


    //---   Operations   ----------------------------------------------------
    /** @brief Returns the number of successes for n>=0 independent trials. */
    template<typename CountT, typename ProbaT>
        requires std::is_integral_v<CountT>&& std::is_floating_point_v<ProbaT>
    const CountT binomialvariate(const CountT n = 1, const ProbaT p = ProbaT(0.5)) noexcept(false);


    /** @brief Chooses a random element from a non-empty sequence (std::vector). */
    template<typename T>
    const T& choice(const std::vector<T>& seq) noexcept(false);

    /** @brief Chooses a random element from a non-empty sequence (std::array). */
    template<typename T, const std::size_t n>
    const T& choice(const std::array<T, n>& seq) noexcept(false)
    {
        if (n == 0)
            throw ChoiceEmptySequenceException();
        return seq[uniform<T>(n)];
    }


    /** @brief Returns the internal state of this PRNG; can be passed to setstate() later. */
    inline struct _InternalState getstate() const noexcept
    {
        return _internal_state;
    }


    /** @brief Returns n values that are uniformly contained within range [0.0, 1.0). */
    template<typename T>
        requires std::is_floating_point_v<T>
    inline std::vector<T> n_evaluate(const std::size_t n) noexcept(false);

    /** @brief Returns a vector of n values that are uniformly contained within range [0, max). */
    template<typename T, typename U = T>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    std::vector<T> n_evaluate(const std::size_t n, const U max) noexcept(false);

    /** @brief Returns a vector of n values in range [0; max[i]). */
    template<typename T, typename U = T>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    std::vector<T> n_evaluate(const std::vector<U>& max) noexcept(false);

    /** @brief Returns a vector of n values in range [min[i]; max[i]). */
    template<typename T, typename U = T, typename V = U>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
    std::vector<T> n_evaluate(const std::vector<U>& min, const std::vector<V>& max) noexcept(false);

    /** @brief Returns an array of n values that are uniformly contained within range [0.0, 1.0). */
    template<typename T, const std::size_t n>
        requires std::is_floating_point_v<T> && (n != 0)
    std::array<T, n> n_evaluate() noexcept
    {
        std::array<T, n> out;
        std::ranges::generate(out, [&]() { return uniform<T>(1.0); });
        return out;
    }

    /** @brief Returns n values that are uniformly contained within range [0, max). */
    template<typename T, const std::size_t n, typename U = T>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && (n != 0)
    std::array<T, n> n_evaluate(const U max) noexcept
    {
        std::array<T, n> out;
        std::ranges::generate(out, [&]() { return uniform<T>(max); });
        return out;
    }

    /** @brief Returns n values that are uniformly contained within range [min, max). */
    template<typename T, const std::size_t n, typename U = T, typename V = U>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && (n != 0)
    std::array<T, n> n_evaluate(const U min, const V max) noexcept
    {
        std::array<T, n> out;
        std::ranges::generate(out, [&]() { return uniform<T>(min, max); });
        return out;
    }

    /** @brief Returns an array of min(m, n) values in range [0; max[i]). */
    template<typename T, const std::size_t m, typename U = T, const std::size_t n = m>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && (m != 0) && (n != 0)
    std::array<T, m> n_evaluate(const std::array<U, n>& max) noexcept(false)
    {
        const std::size_t count{ std::min(m, n) };

        std::array<T, m> out;
        auto out_it{ out.begin() };
        auto max_it{ max.cbegin() };
        for (int i = 0; i < count; ++i)
            *out_it++ = uniform<T>(*max_it++);
        while (out_it != out.end())
            *out_it++ = T{};

        return out;
    }

    /** @brief Returns an array min(m, n, p) values in range [min[i]; max[i]). */
    template<
        typename T, const std::size_t m,
        typename U = T, const std::size_t n = m,
        typename V = U, const std::size_t p = n
    > requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>&& std::is_arithmetic_v<V> && (n != 0) && (m != 0) && (p != 0)
    std::array<T, m> n_evaluate(const std::array<U, n>& min, const std::array<V, p>& max) noexcept
    {
        std::array<T, m> out;

        const std::size_t count{ std::min({m, n, p}) };
        auto out_it{ out.begin() };
        auto min_it{ min.cbegin() };
        auto max_it{ max.cbegin() };
        for (int i = 0; i < count; ++i)
            *out_it++ = uniform<T>(*min_it++, *max_it++);
        while (out_it != out.end())
            *out_it++ = T{};

        return out;
    }


    /** @brief Generates n random bytes.
    *
    * This method should not be used for generating security tokens.
    */
    inline std::vector<std::uint8_t> randbytes(const std::size_t n) noexcept(false);


    /** @brief Returns random integer in range [a, b], including both end points.
    *
    * Template argument T must be an integral type.
    */
    template<typename T>
        requires std::is_integral_v<T>
    inline const T randint(const T a, const T b) noexcept;


    /** @brief Chooses a random item from range [start, stop) with specified step.
    *
    * Template arguments T and S must be an integral type.
    */
    template<typename T, typename S = T>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<S>
    const T randrange(const T start, const T stop, const S step = S(1)) noexcept(false);


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
    void sample(std::vector<T>& out, const std::vector<T>& population, const std::size_t k) noexcept(false);

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
        requires (k != 0)
    void sample(std::array<T, k>& out, const std::array<T, n>& population) noexcept(false)
    {
        if (k > n)
            throw SampleCountException(k, n);

        std::array<T, n> samples{ population };

        auto out_it{ out.begin() };
        for (std::size_t i = 0; i < k; ++i) {
            const std::size_t index = uniform<std::size_t>(i, n);
            *out_it++ = samples[index];
            if (i != index)
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
    * The implemented algorithm in CRandLib is NOT the one that is implemented
    * in Python 3.11 library Random.  In CRandLib, we use a simpler form which
    * should be more efficient as long as population's items are movable (i.e.
    * Move Constructor and maybe Move assignment are defined).
    */
    template<typename T, typename C>
        requires std::is_integral_v<C>
    void sample(std::vector<T>& out, const std::vector<T>& population, const std::vector<C>& counts, const std::size_t k) noexcept(false);


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
    * The implemented algorithm in CRandLib is NOT the one that is implemented
    * in Python 3.11 library Random.  In CRandLib, we use a simpler form which
    * should be more efficient as long as population's items are movable (i.e.
    * Move Constructor and maybe Move assignment are defined).
    */
    template<typename T, typename C, const std::size_t k, const std::size_t n>
        requires std::is_integral_v<C> && (k != 0)
    void sample(std::array<T, k>& out, const std::array<T, n>& population, const std::array<C, n>& counts) noexcept(false)
    {
        const std::size_t samples_count = std::size_t(std::accumulate(counts.begin(), counts.end(), C(0)));
        if (k > samples_count)
            throw SampleCountException(k, samples_count);

        std::vector<T> samples(samples_count);
        auto c_it = counts.begin();
        auto s_it{ samples.begin() };
        for (auto& p : population) {
            for (std::size_t j = std::size_t(*c_it++); j > 0; --j)
                *s_it++ = p;
        }

        auto out_it{ out.begin() };
        for (std::size_t i = 0; i < k; ++i) {
            const std::size_t index = uniform<std::size_t>(i, samples_count);
            *out_it++ = samples[index];
            if (i != index)
                std::swap(samples[i], samples[index]);
        }
    }


    /** @brief Initializes internal state (empty signature).
    *
    * The seed value is evaluated from current time.
    */
    virtual inline void seed() noexcept;

    /** @brief Initializes internal state from a 32-bits signed integer seed. */
    inline void seed(const int seed_) noexcept;

    /** @brief Initializes internal state from a 32-bits unsigned integer seed. */
    inline void seed(const unsigned int seed_) noexcept;

    /** @brief Initializes internal state from a 32-bits unsigned integer seed. */
    inline void seed(const long seed_) noexcept;

    /** @brief Initializes internal state from a 32-bits unsigned integer seed. */
    inline void seed(const unsigned long seed_) noexcept;

    /** @brief Initializes internal state from a 64-bits unsigned integer seed. */
    inline void seed(const long long seed_) noexcept;

    /** @brief Initializes internal state from a 64-bits unsigned integer seed. */
    inline void seed(const unsigned long long seed_) noexcept;

    /** @brief Initializes the internal state of this PRNG with a 128-bits integer seed. */
    virtual inline void seed(const utils::UInt128& seed_) noexcept;

    /** @brief Initalizes internal state from a double seed. */
    inline void seed(const double seed_);


    /** @brief Restores the internal state of this PRNG from seed. */
    inline void setstate(const StateT& new_internal_state) noexcept;

    /** @brief Restores the internal state of this PRNG from seed and gauss_next. */
    inline void setstate(const StateT& new_internal_state, const double gauss_next) noexcept;


    /** @brief eturns the current internal state value. */
    inline const StateT state() const noexcept;


    /** @brief In place Shuffles the specified sequence.
    *
    * The container type must provide method '.size()'.
     */
    template<typename ContainerType>
        requires utils::is_indexable_v<ContainerType>
    void shuffle(ContainerType& seq) noexcept(false);


    //---   Random distribution functions   ---------------------------------
    /** @brief Beta distribution.
    *
    * @param alpha: double, must be greater than 0
    * @param beta: double, must be greater than 0
    * @return a value in range [0.0, 1.0].
    *
    * Important notice: the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    * The original code is due to Janne Sinkkonen and matches all the std
    * texts (e.g., Knuth Vol 2 Ed 3 pg 134 "the beta distribution").
    */
    const double betavariate(const double alpha, const double beta) noexcept(false);


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
    const double expovariate(const double lambda = 1.0) noexcept(false);


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
    const double gammavariate(const double alpha, const double beta) noexcept(false);


    /** @brief Default Gaussian distribution (mean=0.0, stdev=1.0).
    *
    * This is slightly faster than the normalvariate() function.
    * Notice: not thread-safe without a lock around calls.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double gauss() noexcept;


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
    const double gauss(const double mu, const double sigma) noexcept(false);


    /** @brief Default Log normal distribution (mean=0.0, stdev=1.0).
    *
    * If you take the natural logarithm of this distribution, you'll get
    * a normal distribution with mean 0.0 and standard deviation 1.0.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double lognormvariate() noexcept(false);


    /** @brief Log normal distribution (mean=mu, stdev=sigma).
    *
    * If you take the natural logarithm of this distribution, you'll get
    * a normal distribution with mean mu and standard deviation sigma.
    * mu can have any value, and sigma must be greater than zero.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double lognormvariate(const double mu, const double sigma) noexcept(false);


    /** @brief Normal distribution (mean=0.0, stdev=1.0).
    *
    * The Python version of this method uses Kindermanand Monahan  method.
    * Reference: Kinderman, A.J.and Monahan, J.F., "Computer generation of
    * random variables using the ratio of  uniform  deviates",  ACM  Trans
    * Math Software, 3, (1977), pp257 - 260.
    * This method is slightlly slower than the gauss method.  Furthermore,
    * we've s lightly modified the original algorithm here to fulfill very
    * special cases that might happen in very  specific  conditions.  This
    * slows  down  also  the  running  of  normalvariate()  in  these very
    * specific  conditions.  You should prefer then to use method  gauss()
    * instead of this one.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double normalvariate() noexcept(false);


    /** @brief Normal distribution (mean=mu, stdev=sigma).
    *
    * mu is the mean, and sigma is the standard deviation.
    * mu can be any value, sigma must be greater than 0.0.
    *
    * The Python version of this method uses Kindermanand Monahan  method.
    * Reference: Kinderman, A.J.and Monahan, J.F., "Computer generation of
    * random variables using the ratio of  uniform  deviates",  ACM  Trans
    * Math Software, 3, (1977), pp257 - 260.
    * This method is slightlly slower than the gauss method.  Furthermore,
    * we've s lightly modified the original algorithm here to fulfill very
    * special cases that might happen in very  specific  conditions.  This
    * slows  down  also  the  running  of  normalvariate()  in  these very
    * specific  conditions.  You should prefer then to use method  gauss()
    * instead of this one.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double normalvariate(const double mu, const double sigma) noexcept(false);


    /** @brief Pareto distribution.
    *
    * @param alpha: double, the shape parameter. Cannot be 0.0.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    const double paretovariate(const double alpha) noexcept(false);


    /** @brief Triangular distribution (low=0.0, high=1.0, mode=0.5). */
    inline const double triangular() noexcept;


    /** @brief Triangular distribution (low, high, default mode). */
    const double triangular(const double low, const double high) noexcept;


    /** @brief Triangular distribution (low, high, mode).
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    const double triangular(const double low, const double high, const double mode) noexcept;


    /** @brief Uniform distribution in [0.0, 1.0). */
    template<typename T = double>
        requires std::is_floating_point_v<T>
    inline const T uniform() noexcept;


    /** @brief Uniform distribution (0.0, max). */
    template<typename T = double, typename U = T>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    inline const T uniform(const U max) noexcept;

    template<>
    inline const float uniform(const float max) noexcept
    {
        return max * random<float>();
    }

    template<>
    inline const double uniform(const double max) noexcept
    {
        return max * random<double>();
    }

    template<>
    inline const long double uniform(const long double max) noexcept
    {
        return max * random<long double>();
    }


    /** @brief Uniform distribution in [min, max).*/
    template<typename T, typename U = T, typename V = U>
        requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
    inline const T uniform(const U min, const V max) noexcept;


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
    const double vonmisesvariate(const double mu, const double kappa) noexcept(false);


    /** @brief Weibull distribution.
    *
    * @param alpha: double, the scale parameter.
    * @param beta: double, the shape parameter. Must be non null.
    */
    const double weibullvariate(const double alpha, const double beta) noexcept(false);


protected:
    //---   Constants   -----------------------------------------------------
    static constexpr double BPF{ 53 };
    static constexpr double GAUSS_NULL{ -1.0 };
    static constexpr double PI{ 3.141'592'653'589'793'238'46 };
    static constexpr double TWO_PI{ 2.0 * PI };

    static const double E;
    static const double LOG4;
    static const double NV_MAGICCONST;
    static const double RECIP_BPF;
    static const double SG_MAGICCONST;

    static constexpr std::uint64_t _MODULO{ (((1ull << ((OUTPUT_BITS > 64 ? 64 : OUTPUT_BITS) - 1)) - 1) << 1) | 0xf };  // notice: complex formula to avoid warning on bits overflow, should be (1 << OUTPUT_BITS) - 1

    static constexpr long double _NORMALIZE_LD{ (OUTPUT_BITS <= 64)
        ? 1.0l / ((long double)_MODULO + 1.0l)
        : 2.938'735'877'055'718'769'921'841'343'055'6e-39l  // i.e. 1.0 / (1 << 128). Notice: no other case than 128 here
    };
    static constexpr double _NORMALIZE{ double(_NORMALIZE_LD) };


    //---   Operations   ----------------------------------------------------
    /** @brief Sets the internal state with an integer seed.
    *
    * MUST BE overridden in inheriting classes.
    */
    virtual inline void _setstate(const std::uint64_t seed) noexcept
    {}

    /** @brief Sets the internal state with a 128-bits integer seed. */
    virtual inline void _setstate(const utils::UInt128& seed_) noexcept
    {
        _setstate(seed_.lo);  // notice: minimalist default behavior. Must be overridden in 128-bits inheriting classes.
    }

};


//===========================================================================
//---   TEMPLATES IMPLEMENTATION   ------------------------------------------
//---------------------------------------------------------------------------
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::E{ std::exp(1.0) };

template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::LOG4{ std::log(4.0) };

template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::NV_MAGICCONST{ 4 * std::exp(-0.5) / std::sqrt(2.0) };

template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::RECIP_BPF{ std::exp2(-BPF) };

template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::SG_MAGICCONST{ 1.0 + std::log(4.5) };


//---------------------------------------------------------------------------
/** Valued call operator (1 scalar). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_arithmetic_v<T>
const T BaseRandom<StateT, OutputT, OUTPUT_BITS>::operator() (const T max) noexcept
{
    return uniform<T>(max);
}

//---------------------------------------------------------------------------
/** Valued call operator (max and n scalars). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_arithmetic_v<T>
std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::operator() (const T max, const std::size_t n)  noexcept(false)
{
    if (n == 0)
        throw ZeroLengthException();

    std::vector<T> out(n);
    std::ranges::generate(out, [&]() { return uniform<T>(max); });
    return out;
}

//---------------------------------------------------------------------------
/** Valued call operator (min, max and n scalars). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_arithmetic_v<T>
std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::operator() (const T min, const T max, const std::size_t n) noexcept(false)
{
    if (n == 0)
        throw ZeroLengthException();

    std::vector<T> out(n);
    std::ranges::generate(out, [&]() { return uniform<T>(min, max); });
    return out;
}

//---------------------------------------------------------------------------
/** Valued call operator (1 std::vector of scalars). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_arithmetic_v<T>
std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::operator() (const std::vector<T>& max) noexcept(false)
{
    std::vector<T> out(max.size());
    auto max_it{ max.cbegin() };
    std::ranges::generate(out, [&]() { return uniform<T>(*max_it++); });
    return out;
}

//---------------------------------------------------------------------------
/** Valued call operator (2 std::vector of scalars). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_arithmetic_v<T>
std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::operator() (const std::vector<T>& min, const std::vector<T>& max) noexcept
{
    const std::size_t count = std::min(min.size(), max.size());
    std::vector<T> out(count);
    auto min_it = min.cbegin();
    auto max_it = max.cbegin();
    std::ranges::generate(out, [&]() { return uniform<T>(*min_it++, *max_it++); });
    return out;
}

//---------------------------------------------------------------------------
/** Returns the number of successes for n>=0 independent trials. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename CountT, typename ProbaT>
    requires std::is_integral_v<CountT> && std::is_floating_point_v<ProbaT>
const CountT BaseRandom<StateT, OutputT, OUTPUT_BITS>::binomialvariate(CountT n, const ProbaT p) noexcept(false)
{
    if (n < 0)
        throw PositiveValueException(n);
    if (p < 0.0 || p > 1.0)
        throw ProbaOutOfRangeException(p);

    CountT count{ 0 };
    while (n > 0) {
        count += uniform<ProbaT>() < p;
        --n;
    }

    return count;
}

//---------------------------------------------------------------------------
/** Chooses a random element from a non-empty sequence (std::vector). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
const T& BaseRandom<StateT, OutputT, OUTPUT_BITS>::choice(const std::vector<T>& seq) noexcept(false)
{
    const std::size_t n{ seq.size() };
    if (n == 0)
        throw ChoiceEmptySequenceException();
    return seq[uniform<std::size_t>(T(n))];
}

//---------------------------------------------------------------------------
/** Returns n values that are uniformly contained within range [0.0, 1.0). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_floating_point_v<T>
inline std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::n_evaluate(const std::size_t n) noexcept(false)
{
    return (*this)(T(1.0), n);
}

//---------------------------------------------------------------------------
/** Returns a vector of n values that are uniformly contained within range [0, max). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T, typename U>
    requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::n_evaluate(const std::size_t n, const U max) noexcept(false)
{
    if (n == 0)
        throw ZeroLengthException();

    std::vector<T> out(n);
    std::ranges::generate(out, [&]() { return uniform<T>(max); });
    return out;
}

//---------------------------------------------------------------------------
/** Returns a vector of n values in range [0; max[i]). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T, typename U>
    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::n_evaluate(const std::vector<U>& max) noexcept(false)
{
    const std::size_t n{ max.size() };
    if (n == 0)
        throw ZeroLengthException();

    std::vector<T> out(n);
    auto max_it = max.cbegin();
    std::ranges::generate(out, [&]() { return uniform<T>(*max_it++); });
    return out;
}

//---------------------------------------------------------------------------
/** Returns a vector of n values in range [min[i]; max[i]). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T, typename U, typename V>
    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
std::vector<T> BaseRandom<StateT, OutputT, OUTPUT_BITS>::n_evaluate(const std::vector<U>& min, const std::vector<V>& max) noexcept(false)
{
    const std::size_t n{ std::min(min.size(), max.size()) };
    if (n == 0)
        throw ZeroLengthException();

    std::vector<T> out(n);
    auto min_it = min.cbegin();
    auto max_it = max.cbegin();
    std::ranges::generate(out, [&]() { return uniform<T>(*min_it++, *max_it++); });
    return out;
}

//---------------------------------------------------------------------------
/** Generates n random bytes. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline std::vector<std::uint8_t> BaseRandom<StateT, OutputT, OUTPUT_BITS>::randbytes(const std::size_t n) noexcept(false)
{
    if (n == 0)
        throw ZeroLengthException();

    std::vector<std::uint8_t> out(n);
    std::ranges::generate(out, [&]() { return uniform<std::uint8_t>(256ul); });
    return out;
}

//---------------------------------------------------------------------------
/** Returns random integer in range [a, b], including both end points. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_integral_v<T>
inline const T BaseRandom<StateT, OutputT, OUTPUT_BITS>::randint(const T a, const T b) noexcept
{
    if (a <= b)
        return uniform<T>(a, b + 1);
    else
        return uniform<T>(b, a + 1);
}


//---------------------------------------------------------------------------
/** Chooses a random item from range [start, stop) with specified step. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T, typename S>
    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<S>
const T BaseRandom<StateT, OutputT, OUTPUT_BITS>::randrange(const T start, const T stop, const S step) noexcept(false)
{
    if (step == 0)
        throw RangeZeroStepException();
    if (start == stop)
        throw RangeSameValuesException<T>(start, stop);
    if ((stop > start && step < 0) || (stop < start && step > 0))
        throw RangeIncoherentValuesException<T>(start, stop, step);

    if (step == 1)
        return start + uniform<T>(stop - start);

    const std::uint64_t n_steps{
        std::uint64_t(step >= 0
            ? (stop - start + (step / 2)) / step
            : (start - stop - (step / 2)) / -step
        )
    };
    return start + step * T(uniform<std::uint64_t>(n_steps));
}

//---------------------------------------------------------------------------
/** Chooses k unique random elements from a population sequence (out std::vector, in container, default counts = 1). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
void BaseRandom<StateT, OutputT, OUTPUT_BITS>::sample(
    std::vector<T>& out,
    const std::vector<T>& population,
    const std::size_t k
) noexcept(false)
{
    const std::size_t n{ population.size() };
    if (k > n)
        throw SampleCountException(k, n);

    out.clear();
    out.resize(k);
    std::vector<T> samples{ population };

    auto out_it = out.begin();
    for (std::size_t i = 0; i < k; ++i) {
        const std::size_t index = uniform<std::size_t>(i, n);
        *out_it++ = samples[index];
        if (i != index)
            std::swap(samples[i], samples[index]);
    }
}

//---------------------------------------------------------------------------
/** Chooses k unique random elements from a population sequence (std::vector<>, with counts vector). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T, typename C>
    requires std::is_integral_v<C>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::sample(
    std::vector<T>& out,
    const std::vector<T>& population,
    const std::vector<C>& counts,
    const std::size_t k
) noexcept(false)
{
    if (population.size() != counts.size())
        throw SampleSizesException(population.size(), counts.size());

    const std::size_t samples_count = std::size_t(std::accumulate(counts.cbegin(), counts.cend(), C(0)));
    if (k > samples_count)
        throw SampleCountException(k, samples_count);

    std::vector<T> samples(samples_count);
    auto c_it = counts.cbegin();
    auto s_it = samples.begin();
    for (auto& p : population) {
        for (std::size_t j = std::size_t(*c_it++); j > 0; --j)
            *s_it++ = p;
    }

    out.clear();
    out.resize(k);
    auto out_it{ out.begin() };
    for (std::size_t i = 0; i < k; ++i) {
        const std::size_t index = uniform<std::size_t>(i, samples_count);
        *out_it++ = samples[index];
        if (i != index)
            std::swap(samples[i], samples[index]);
    }
}

//---------------------------------------------------------------------------
/** Initializes internal state (empty signature). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed() noexcept
{
    seed(utils::set_random_seed64());
}

//---------------------------------------------------------------------------
/** Initializes internal state from a 32-bits signed integer seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const int seed_) noexcept
{
    seed((const long)seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state from a 32-bits unsigned integer seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const unsigned int seed_) noexcept
{
    seed((const unsigned long)seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state from a 32-bits signed integer seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const long seed_) noexcept
{
    seed((const unsigned long)seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state from a 32-bits unsigned integer seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const unsigned long seed_) noexcept
{
    _setstate(seed_);
    _internal_state.gauss_valid = false;
}

//---------------------------------------------------------------------------
/** Initializes internal state from a 64-bits signed integer seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const long long seed_) noexcept
{
    seed((const unsigned long long)seed_);
}

//---------------------------------------------------------------------------
/** Initializes internal state from a 64-bits unsigned integer seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const unsigned long long seed_) noexcept
{
    _setstate(seed_);
    _internal_state.gauss_valid = false;
}

//---------------------------------------------------------------------------
/** Initializes the internal state of this PRNG with a 128-bits integer seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const utils::UInt128& seed_) noexcept
{
    _setstate(seed_);
    _internal_state.gauss_valid = false;
}

//---------------------------------------------------------------------------
/** ief Initalizes internal state from a double seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::seed(const double seed_)
{
    if (seed_ < 0.0 || 1.0 <= seed_)
        throw FloatValueRange01Exception();

    seed(std::uint64_t(seed_ * double(0xffff'ffff'ffff'ffffULL)));
}

//---------------------------------------------------------------------------
/** Restores the internal state of this PRNG from seed. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::setstate(const StateT& new_internal_state) noexcept
{
    _internal_state.state = new_internal_state;
    _internal_state.gauss_next = 0.0;
    _internal_state.gauss_valid = false;
}

//---------------------------------------------------------------------------
/** Restores the internal state of this PRNG from seed and gauss_next. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline void BaseRandom<StateT, OutputT, OUTPUT_BITS>::setstate(const StateT& new_internal_state, const double gauss_next) noexcept
{
    _internal_state.state = new_internal_state;
    _internal_state.gauss_next = gauss_next;
    _internal_state.gauss_valid = true;
}

//---------------------------------------------------------------------------
/** Returns the current internal state value. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline const StateT BaseRandom<StateT, OutputT, OUTPUT_BITS>::state() const noexcept
{
    return _internal_state.state;
}

//---------------------------------------------------------------------------
/** Shuffles specified sequence in place. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename ContainerType>
    requires utils::is_indexable_v<ContainerType>
void BaseRandom<StateT, OutputT, OUTPUT_BITS>::shuffle(ContainerType& seq) noexcept(false)
{
    const std::size_t n{ seq.size() };

    if (n != 0) {
        for (std::size_t i = 0; i < n - 1; ++i) {
            const std::size_t index = uniform<std::size_t>(i, n);
            std::swap(seq[i], seq[index]);
        }
    }
}

//---------------------------------------------------------------------------
/** Beta distribution. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::betavariate(const double alpha, const double beta) noexcept(false)
{
    if (alpha <= 0.0 || beta <= 0.0)
        throw AlphaBetaArgsException(alpha, beta);

    const double y = gammavariate(alpha, 1.0);
    return (y == 0.0) ? 0.0 : (y / (y + gammavariate(beta, 1.0)));
}

//---------------------------------------------------------------------------
/** Exponential distribution. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::expovariate(const double lambda) noexcept(false)
{
    if (lambda <= 0.0)
        throw ExponentialZeroLambdaException();

    const double u{ uniform() };
    if (u < 1.0)  // should always happen, let's check for it nevertheless
        return -std::log(1.0 - u) / lambda;
    else
        return 0.0;
}

//---------------------------------------------------------------------------
/** Gamma distribution. This is NOT the gamma function! */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::gammavariate(const double alpha, const double beta) noexcept(false)
{
    constexpr int N_MAX_LOOPS{ 10 };
    int n_loops{ 0 };

    if (alpha <= 0.0 || beta <= 0.0)
        throw AlphaBetaArgsException(alpha, beta);

    if (alpha > 1.0) {
        // Uses R.C.H.Cheng paper
        // "The generation of Gamma variables with non - integral shape parameters",
        // Applied Statistics, (1977), 26, No. 1, p71 - 74
        // (modified here with n_loops testing against max loops count and with default returned value)
        constexpr double EPSILON{ 1e-7 };
        const double     INV_A{ std::sqrt(2.0 * alpha - 1.0) };
        const double     B{ alpha - LOG4 };
        const double     C{ alpha + INV_A };

        double u1;
        while (n_loops < N_MAX_LOOPS) {  // Notice: while (true) in initial Cheng's algorithm
            u1 = std::min(uniform(), 1.0 - EPSILON);  // Notice: modification from initial algorithm u1 is always less than 1-epsilon
            if (EPSILON < u1) {          // Notice: modification from initial algorithm, removed the test u1 < 1-epsilon
                const double u2{ 1.0 - uniform() };
                const double v{ std::log(u1 / (1.0 - u1)) / INV_A };
                const double x{ alpha - std::exp(v) };
                const double z{ u1 * u1 * u2 };
                const double r{ B + C * v - x };
                if (r + SG_MAGICCONST - 4.5 * z >= 0.0 || r >= std::log(z))
                    // this should eventually happen
                    return x < 0 ? -x * beta : x * beta;
            }
            ++n_loops;
        }
        // added to initial algorithm : u1 < EPSILON happened too many successive times
        return 0.0;
    }
    else if (alpha == 1.0) {
        // this is exponential distribution with lambda = 1 / beta
        return -std::log(1.0 - uniform()) * beta;
    }
    else {
        // alpha is between 0 and 1 (exclusive)
        // so, uses ALGORITHM GS of Statistical Computing - Kennedy & Gentle
        double b, p, x, u;
        while (n_loops < N_MAX_LOOPS) {  // Notice: while (true) in initial Kennedy & Gentle's algorithm
            u = uniform();
            b = (E + alpha) / E;
            p = b * u;
            x = p <= 1.0 ? std::pow(p, 1.0 / alpha) : -std::log((b - p) / alpha);
            u = uniform();
            if (p <= 1.0) {
                if (u <= std::exp(-x))
                    return x * beta;
            }
            else if (u <= std::pow(x, alpha - 1.0))
                return x * beta;

            ++n_loops;  // added to initial algorithm
        }
        // added to initial algorithm
        return beta * -std::log(b - p) / alpha;
    }
}

//---------------------------------------------------------------------------
/** Default Gaussian distribution (mean=0.0, stdev=1.0). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::gauss() noexcept
{
    return gauss(0.0, 1.0);
}

//---------------------------------------------------------------------------
/** Gaussian distribution (mean=mu, stdev=sigma). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::gauss(const double mu, const double sigma) noexcept(false)
{
    if (sigma <= 0.0)
        throw GaussSigmaException(sigma);

    double z;
    if (_internal_state.gauss_valid) {
        z = _internal_state.gauss_next;
        _internal_state.gauss_valid = false;
    }
    else {
        const double u{ uniform(TWO_PI) };
        const double g{ std::sqrt(-2.0 * std::log(1.0 - uniform())) };
        z = std::cos(u) * g;
        _internal_state.gauss_next = std::sin(u) * g;
        _internal_state.gauss_valid = true;
    }

    return mu + z * sigma;
}

//---------------------------------------------------------------------------
/** Default Log normal distribution (mean=0.0, stdev=1.0). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::lognormvariate() noexcept(false)
{
    return lognormvariate(0.0, 1.0);
}

//---------------------------------------------------------------------------
/** Log normal distribution (mean=mu, stdev=sigma). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::lognormvariate(const double mu, const double sigma) noexcept(false)
{
    return std::exp(normalvariate(mu, sigma));
}

//---------------------------------------------------------------------------
/** Normal distribution (mean=0.0, stdev=1.0). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::normalvariate() noexcept(false)
{
    return normalvariate(0.0, 1.0);
}

//---------------------------------------------------------------------------
/** Normal distribution (mean=mu, stdev=sigma). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::normalvariate(const double mu, const double sigma) noexcept(false)
{
    if (sigma <= 0.0)
        throw NormalSigmaException();

    constexpr int N_MAX_LOOPS{ 10 };
    int n_loops{ 0 };

    double u1{ 0.0 };
    while (n_loops++ < N_MAX_LOOPS) {
        u1 = uniform();
        const double u2{ 1.0 - u1 };
        const double z{ NV_MAGICCONST * (u1 - 0.5) / u2 };
        if (z * z / 4.0 <= -std::log(u2))
            return mu + z * sigma;
    }

    return mu + u1 * 6.67 * sigma;  //  notice: modification from original algorithm - should happen in very rare cases

    // notice: could have been as simple as "return gauss(mu, sigma);" also
}

//---------------------------------------------------------------------------
/** Pareto distribution. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::paretovariate(const double alpha) noexcept(false)
{
    if (alpha == 0.0)
        throw ParetoArgsValueException();

    // according to Jain, pg. 495
    return std::pow(1.0 - uniform(), -1.0 / alpha);
}

//---------------------------------------------------------------------------
/** Triangular distribution (low=0.0, high=1.0, mode=0.5). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
inline const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::triangular() noexcept
{
    return triangular(0.0, 1.0, 0.5);
}

//---------------------------------------------------------------------------
/** Triangular distribution (low, high, default mode). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::triangular(const double low, const double high) noexcept
{
    return triangular(low, high, (low + high) / 2);
}

//---------------------------------------------------------------------------
/** Triangular distribution (low, high, mode). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::triangular(double low, double high, const double mode) noexcept
{
    if (high == low)
        return high;

    double u{ uniform() };
    double c{ double(mode - low) / double(high - low) };
    if (u > c)
        return high + (low - high) * std::sqrt((1.0 - u) * (1.0 - c));
    else
        return low + (high - low) * std::sqrt(u * c);
}

//---------------------------------------------------------------------------
/** Uniform distribution in [0.0, 1.0). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T>
    requires std::is_floating_point_v<T>
inline const T BaseRandom<StateT, OutputT, OUTPUT_BITS>::uniform() noexcept
{
    return random<T>();
}

//---------------------------------------------------------------------------
/** Uniform distribution in [0.0, max). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T, typename U>
    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
inline const T BaseRandom<StateT, OutputT, OUTPUT_BITS>::uniform(const U max) noexcept
{
    if (max >= U(0))
        return T(std::min<long double>((long double)max * random<long double>(), (long double)(max - 1e-7L)));
    else
        return T(std::max<long double>((long double)max * random<long double>(), (long double)(max - 1e-7L)));
}


//---------------------------------------------------------------------------
/** Uniform distribution in [min, max). */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
template<typename T, typename U, typename V>
    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
inline const T BaseRandom<StateT, OutputT, OUTPUT_BITS>::uniform(const U min, const V max) noexcept
{
    const long double a{ (long double)min };
    const long double b{ (long double)max };
    if (a <= b)
        return T(a + (b - a) * random<long double>());
    else
        return T(b + (a - b) * random<long double>());
}

//---------------------------------------------------------------------------
/** Circular data distribution. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::vonmisesvariate(const double mu, const double kappa) noexcept(false)
{
    // extracted from Python 3.11 comments:
    // Based upon an algorithm published in : Fisher, N.I.,
    // "Statistical Analysis of Circular Data", Cambridge University Press, 1993.
    //
    // Thanks to Magnus Kessler for a correction to the implementation of step 4.
    // (modified here with n_loops testing against max loops count and with default returned value)

    if (kappa < 0)
        throw NegativeKappaException(kappa);

    if (kappa <= 1e-6)
        return uniform(TWO_PI);

    const double s = 0.5 / kappa;
    const double r = s + std::sqrt(1.0 + s * s);
    double d, u, z;

    constexpr int N_MAX_LOOPS{ 10 };  // notice: modification from initial algorithm, avoids infinite looping in specific cases
    int n_loops{ 0 };
    while (n_loops++ < N_MAX_LOOPS) {
        z = std::cos(uniform(PI));
        d = z / (r + z);
        u = uniform();
        if (u < 1.0 - d * d || u <= (1.0 - d) * std::exp(d))
            break;
    }

    // notice: modification from initial algorithm, after too much looping in specific cases
    if (n_loops == N_MAX_LOOPS) {
        const double du1{ u - (1.0 - d * d) };
        const double du2{ u - (1.0 - d) * std::exp(d) };
        u -= std::min(du1, du2) + 1.0e-7;
    }

    const double q{ 1.0 / r };
    const double f{ (q + z) / (1.0 + q * z) };
    double theta;
    if (uniform() > 0.5)
        theta = std::fmod(mu + std::acos(f), TWO_PI);
    else
        theta = std::fmod(mu - std::acos(f), TWO_PI);

    return (theta < 0.0) ? TWO_PI + theta : theta;
}

//---------------------------------------------------------------------------
/** Weibull distribution. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
    requires std::is_integral_v<OutputT> || std::is_same_v<OutputT, utils::UInt128>
const double BaseRandom<StateT, OutputT, OUTPUT_BITS>::weibullvariate(const double alpha, const double beta) noexcept(false)
{
    if (alpha < 0.0 || beta <= 0.0)
        throw WeibullArgsValueException();

    return alpha * std::pow(-std::log(1.0 - uniform()), 1.0 / beta);
}
