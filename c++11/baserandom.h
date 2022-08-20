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
#include <array>
#include <limits>
#include <random>
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

    Furthermore this class and all its inheriting sub-classes are callable. Example:
      rand = BaseRandom()
      std::cout << rand();   // prints a uniform pseudo-random value within [0.0, 1.0)
      std::cout << rand(a);  // prints a uniform pseudo-random value within [0.0, a)
      std::cout << rand(a,b);// prints a uniform pseudo-random value within [a  , b)

    Please notice that for simulating the roll of a dice you may use any of:
      diceRoll = UFastRandom();
      std::cout << int(diceRoll(1, 7))    << std::endl; // prints a uniform roll within {1, ..., 6}.
      std::cout << diceRoll.randint(1, 6) << std::endl; // idem

    Conforming to the former version PyRandLib  of  this  library,  next  methods  are
    available:
     |
     |  betavariate(alpha, beta)
     |      Beta distribution.
     |      https://en.wikipedia.org/wiki/Beta_distribution
     |
     |      Conditions on the parameters are alpha > 0 and beta > 0.
     |      Returned values range between 0 and 1.
     |
     |
     |  choice(seq)
     |      Choose a random element from a non-empty sequence.
     |
     |
     |  expovariate(lambda)
     |      Exponential distribution.
     |      https://en.wikipedia.org/wiki/Exponential_distribution
     |
     |      lambda is 1.0 divided by the desired mean.  It should be
     |      nonzero.
     |      Returned values range from 0 to
     |      positive infinity if lambda is positive, and from negative
     |      infinity to 0 if lambda is negative.
     |
     |
     |  gammavariate(alpha, beta)
     |      Gamma distribution.  Not the gamma function!
     |      https://en.wikipedia.org/wiki/Gamma_distribution
     |
     |      Conditions on the parameters are alpha > 0 and beta > 0.
     |
     |
     |  gauss(mu, sigma)
     |      Gaussian distribution.
     |      https://en.wikipedia.org/wiki/Normal_distribution
     |
     |      mu is the mean, and sigma is the standard deviation.  This is
     |      slightly faster than the normalvariate() function.
     |
     |      Not thread-safe without a lock around calls.
     |
     |
     |  getstate()
     |      Return internal state; can be passed to setstate() later.
     |
     |
     |  lognormvariate(mu, sigma)
     |      Log normal distribution.
     |      https://en.wikipedia.org/wiki/Log-normal_distribution
     |
     |      If you take the natural logarithm of this distribution, you'll get a
     |      normal distribution with mean mu and standard deviation sigma.
     |      mu can have any value, and sigma must be greater than zero.
     |
     |
     |  normalvariate(mu, sigma)
     |      Normal distribution.
     |      https://en.wikipedia.org/wiki/Normal_distribution
     |
     |      mu is the mean, and sigma is the standard deviation.
     |
     |
     |  paretovariate(alpha)
     |      Pareto distribution.  alpha is the shape parameter.
     |      https://en.wikipedia.org/wiki/Pareto_distribution
     |
     |
     |  randint(a, b)
     |      Return random integer in range [a, b], including both end points.
     |
     |
     |  randrange(start, stop, step=1)
     |      Choose a random item from range(start, stop[, step]).
     |
     |      This fixes the problem with randint() which includes the
     |      endpoint.
     |
     |
     |  sample(population, k)
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
     |  seed()
     |  seed(a)
     |      Initialize internal state.
     |      No argument seeds from current time.
     |      If *a* is an int, all bits are used.
     |
     |
     |  setstate(state)
     |      Restore internal state from object returned by getstate().
     |
     |
     |  shuffle(x)
     |      x-> shuffle vector x in place.
     |
     |
     |  triangular()
     |  triangular(low, high)
     |  triangular(low, high, mode)
     |      Triangular distribution.
     |      http://en.wikipedia.org/wiki/Triangular_distribution
     |
     |      Continuous distribution bounded by given lower and upper limits,
     |      and having a given mode value in-between.
     |      When missing, low = 0.0, high = 1.0, mode = (low + high) / 2
     |
     |
     |  uniform()
     |  uniform(b)
     |  uniform(a, b)
     |      Get a random number in the range [a, b) or [a, b] depending on rounding.
     |      When missing, a = 0.0 and b = 1.0
     |
     |
     |  vonmisesvariate(mu, kappa)
     |      Circular data distribution.
     |      https://en.wikipedia.org/wiki/Von_Mises_distribution
     |
     |      mu is the mean angle, expressed in radians between 0 and 2*pi, and
     |      kappa is the concentration parameter, which must be greater than or
     |      equal to zero.  If kappa is equal to zero, this distribution reduces
     |      to a uniform random angle over the range 0 to 2*pi.
     |
     |
     |  weibullvariate(alpha, beta)
     |      Weibull distribution.
     |      https://en.wikipedia.org/wiki/Weibull_distribution
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
    inline BaseRandom() noexcept
        : _seed{}
    {}

    /** @brief Value Constructor. */
    inline BaseRandom(const SeedStateType& seed) noexcept
        :_seed{ seed }
    {}

    /** @brief Default Copy Constructor. */
    BaseRandom(const BaseRandom&) noexcept = default;

    /** @brief Default Move Constructor. */
    BaseRandom(BaseRandom&&) noexcept = default;

    /** @brief Default Destructor. */
    virtual ~BaseRandom() noexcept = default;


    //---   Internal PRNG   -------------------------------------------------
    /** @brief The internal PRNG algorithm.
    *
    * This method must be overriden in inheriting classes.
    * @return a double value uniformly contained within the interval [0.0, 1.0).
    */
    virtual inline const double random()
    {
        return double(m_mt19937()) / MAX_64;
    }


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
        return uniform();
    }

    /** @brief Valued call operator (1 scalar).
    *
    * @return a value that is uniformly contained within the interval [0; max).
    */
    template<typename T>
    inline const T operator() (const T max)
    {
        return uniform(T(0), max);
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
    * @return  a vector of value that are uniformly contained within the
    *   interval [0; max[i])  --  i  being the index of the value in the
    *   returned vector.
    */
    template<typename T>
    std::vector<T> operator() (const std::vector<T> max)
    {
        std::vector<T> ret;
        ret.reserve(max.size());
        for (T m : max)
            ret.emplace_back(uniform(m));
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
            ret.emplace_back(uniform(*min_it, *max_it));
        return ret;
    }


    //---   Operations   ----------------------------------------------------
    /** @brief Chooses a random element from a non-empty sequence (std::vector<>). */
    template<typename T>
    T& choice(const std::vector<T>& seq)
    {
        const size_t size{ seq.size };
        if (size == 0)
            throw std::invalid_argument("cannot make a choice from an empty sequence");
        return seq[random(size)];
    }


    /** @brief Chooses a random element from a non-empty sequence (std::array<>). */
    template<typename T, const size_t S>
    T& choice(const std::array<T, S>& seq)
    {
        if (S == 0)
            throw std::invalid_argument("cannot make a choice from an empty sequence");
        return seq[random(S)];
    } 


    /** @brief Chooses a random element from a non-empty sequence (buffer_ptr). */
    template<typename T>
    T& choice(const size_t size, const T* buffer_ptr)
    {
        if (size == 0)
            throw std::invalid_argument("cannot make a choice from an empty sequence");
        if (buffer_ptr == nullptr)
            throw std::invalid_argument("cannot make a choice from a null sequence");
        return buffer_ptr[random(size)];
    }


    /** @brief Chooses a random element from a non-empty sequence (templated container type).
    *
    * Important notice: the ContainerType class MUST provide method '.size()'.
    * It  may  also  provide  the  type of the contained objects or values via 
    * class attribute '::value_type', in which case the template argument  'T'
    * may be ommitted.
    */
    template<typename ContainerType, typename T = typenameContainerType::value_type>
    T& choice(const ContainerType& seq)
    {
        const size_t size{ seq.size };
        if (size == 0)
            throw std::invalid_argument("cannot make a choice from an empty sequence");
        return seq[random(size)];
    }


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
            out.emplace_back(uniform(min, max));
    }

    /** @brief Returns n vectors of values that are uniformly contained within the interval [0; max[i]) */
    template<typename T>
    inline void n_evaluate(size_t n, std::vector<std::vector<T>>& out, const std::vector<T> max)
    {
        out.reserve(n);
        while (n-- > 0)
            out.emplace_back(uniform(max));
    }

    /** @brief Returns n vectors of values that are uniformly contained within the interval [min[i]; max[i]) */
    template<typename T>
    inline void n_evaluate(size_t n, std::vector<std::vector<T>>& out, const std::vector<T> min, const std::vector<T> max)
    {
        out.reserve(n);
        while (n-- > 0)
            out.emplace_back(uniform(min, max));
    }


    /** @brief Returns random integer in range [a, b], including both end points.
    *
    * Template argument T must be an integral type.
    */
    template<typename T>
    inline const T randint(const T a, const int b)
    {
        if (!std::is_integral<T>)
            throw std::exception("type of arguments is not integral");
        return uniform(a, b + 1);
    }


    /** @brief Choosse a random item from range {start, stop} with specified step.
    *
    * Template argument T must be an integral type.
    */
    template<typename T>
    const T randrange(const T start, const T stop, const T step = 1)
    {
        if (!std::is_integral<T>)
            throw std::exception("type of arguments must be integral");
        if (start == stop)
            throw std::invalid_argument("start and stop arguments must be different");
        if (step == 0)
            throw std::invalid_argument("step argument cannot be 0");

        const T width{ stop - start };

        if (step == 1)
            return start + uniform(width);

        const T n{ (width + step + (step > 0 ? -1 : 1)) / step };
        return start + stop * uniform(n);
    }


    /*** /

    def randrange(self, start, stop=None, step=_ONE):
        """Choose a random item from range(start, stop[, step]).
        This fixes the problem with randint() which includes the
        endpoint; in Python this is usually not what you want.
        """

        # Non-unit step argument supplied.
        if istep > 0:
            n = (width + istep - 1) // istep
        elif istep < 0:
            n = (width + istep + 1) // istep
        else:
            raise ValueError("zero step for randrange()")
        if n <= 0:
            raise ValueError("empty range for randrange()")
        return istart + istep * self._randbelow(n)


    /***/




    //---   Random distribution functions   ---------------------------------
    /** @brief Beta distribution.
    *
    * @arg alpha: double, must be greater than 0
    * @arg beta: double, must be greater than 0
    * @return a value in interval [0.0, 1.0].
    * 
    * Important notice: the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    * The original code is due to Janne Sinkkonen and matches all the std 
    * texts (e.g., Knuth Vol 2 Ed 3 pg 134 "the beta distribution").
    */
    const double betavariate(const double alpha, const double beta);


    /** @brief Exponential distribution.
    *
    * @arg lambda: double, this should get the value (1.0 / desired_mean).
    *   It cannot be 0.0.
    * @return a value in range [0.0, Infinity) if lambda is  positive,  or
    *   a value in range (-Infinity, 0.0] if lambda is negative.
    * 
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++. 
    */
    const double expovariate(const double lambda);
    

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
    * @arg alpha : double, the shape parameter - must be greater than 0.0.
    * @arg beta : double, the scale parameter - must be greater than 0.0.
    *   With these two arguments: mean is alpha * beta and variance is alpha * beta * beta
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++. 
    * As such, some comments present in the Python original code have been
    * copied as is in this c++ implementation, naming then the authors of 
    * the related parts of code.
    */
    const double gammavariate(const double alpha, const double beta);


    /** @brief Default Gaussian distribution (mean=0.0, stdev=1.0).
    *
    * This is slightly faster than the normalvariate() function.
    * Notice: not thread-safe without a lock around calls.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double gauss()
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
    const double gauss(const double mu, const double sigma);


    /** @brief Default Log normal distribution (mean=0.0, stdev=1.0).
    *
    * If you take the natural logarithm of this distribution, you'll get 
    * a normal distribution with mean 0.0 and standard deviation 1.0.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double lognormvariate()
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
    inline const double lognormvariate(const double mu, const double sigma)
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
    * gauss() instead here, in CRandLib.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double normalvariate()
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
    * This method is slightlly slower than the gauss  method,  so  we  call
    * gauss() instead here, in CRandLib.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    inline const double normalvariate(const double mu, const double sigma)
    {
        return gauss(mu, sigma);
    }


    /** @brief Pareto distribution.
    *
    * @arg alpha: double, the shape parameter. Cannot be 0.0.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    const double paretorvariate(const double alpha);


    /** @brief Triangular distribution (low=0.0, high=1.0, mode=0.5). */
    inline const double triangular()
    {
        return triangular(0.0, 1.0, 0.5);
    }


    /** @brief Triangular distribution (low, high, default mode). */
    template<typename T>
    const T triangular(const T low, const T high)
    {
        return triangular(low, high, (low + high) / 2);
    }


    /** @briefTriangular distribution (low, high, mode).
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++.
    */
    template<typename T>
    const T triangular(T low, T high, const T mode)
    {
        if (high == low)
            return high;
        
        const double u{ random() };
        const double c{ double(mode - low) / double(high - low) };
        if (u > c) {
            u = 1.0 - u;
            c = 1.0 - c;
            std::swap(low, high);
        }

        return T(double(low) + double(high - low) * std::sqrt(u * c));
    }


    /** @brief Uniform distribution (0.0, 1.0). */
    inline const double uniform()
    {
        return random();
    }


    /** @brief Uniform distribution (0.0, max). */
    template<typename T>
    inline const T uniform(const T max)
    {
        return T(max * random());
    }


    /** @brief Uniform distribution (min and max values).*/
    template<typename T>
    const T uniform(const T min, const T max)
    {
        return min + T(double(max - min) * random());
    }


    /** @brief Circular data distribution.
    * 
    * @arg mu is the mean angle, expressed in radians between 0 and 2*pi
    * @arg kappa is the concentration parameter, which must be greater than or
    *   equal to zero.  If kappa is equal to zero, this distribution reduces
    *   to a uniform random angle over the range 0 to 2*pi.
    *
    * Important notice:  the implemented code is a translation from Python
    * https://github.com/python/cpython/blob/3.11/Lib/random.py into c++. 
    * As such, some comments present in the Python original code have been
    * copied as is in this c++ implementation, naming then the authors of 
    * the related parts of code.
    */
    const double vonmisesvariate(const double mu, const double kappa);


    /** @brief Weibull distribution.
    *
    * @arg alpha: double, the scale parameter.
    * @arg beta: double, the shape parameter. Must be non null.
    */
    const double weibullvariate(const double alpha, const double beta);

    /*** /

    def weibullvariate(self, alpha, beta):
        """Weibull distribution.
        alpha is the scale parameter and beta is the shape parameter.
        """
        # Jain, pg. 499; bug fix courtesy Bill Arms

        u = 1.0 - self.random()
        return alpha * (-_log(u)) ** (1.0 / beta)

    /***/


protected:
    //---   Constants   -----------------------------------------------------
    const double BPF          { 53 };  // Number of bits in a float
    const double E            { std::exp(1.0) };
    const double LOG4         { std::log(4.0) };
    const double NV_MAGICCONST{ 4 * std::exp(-0.5) / std::sqrt(2.0) };
    const double GAUSS_NULL   { -1.0 };
    const double PI           { 3.14159265358979323846 };
    const double RECIP_BPF    { std::exp2(-BPF) };
    const double SG_MAGICCONST{ 1.0 + std::log(4.5) };
    const double TWO_PI       { 2.0 * PI };


    //---   Attributes   ----------------------------------------------------
    SeedStateType _seed;                      //!< The internal current state of this PRNG
    double        _gauss_next{ GAUSS_NULL };  //!< smart optimization for Gaussian distribution computation


private:
    std::mt19937_64 m_mt19937{};  //!< this base class internal PRNG
    const double MAX_64{ (double(std::numeric_limits<uint_fast64_t>::max()) + 1.0) };
};
