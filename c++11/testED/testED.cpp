/*
MIT License

Copyright (c) 2025 Philippe Schmouker, ph.schmouker (at) gmail.com

This file is provided with library CppRandLib.

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
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

#include "cpprandlib.h"


//===========================================================================
/** @brief The class of histograms and their associated statistics evaluations. */
class Histogram
{
public:
    using value_type = std::uint32_t;
    using index_type = std::uint32_t;

    //-----------------------------------------------------------------------
    inline Histogram(const std::uint32_t n)
    {
        reset(n);
    }

    virtual ~Histogram() noexcept = default;

    //-----------------------------------------------------------------------
    inline value_type& operator[] (const index_type index)
    {
        return _data[index];
    }

    inline const value_type& operator[] (const index_type index) const
    {
        return _data[index];
    }

    //-----------------------------------------------------------------------
    void reset(const std::uint32_t n)
    {
        _data.clear();
        _data.resize(n);
        _mean.evaluated = _median.evaluated = _stdev.evaluated = false;
    }

    //-----------------------------------------------------------------------
    void print()
    {
        std::uint32_t n{ 0 };
        for (value_type d : _data) {
            std::cout << std::setw(6) << d << ' ';
            if (++n % 10 == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }

    //-----------------------------------------------------------------------
    const value_type max() const
    {
        return *std::max_element(_data.cbegin(), _data.cend());
    }

    //-----------------------------------------------------------------------
    const value_type min() const
    {
        return *std::min_element(_data.cbegin(), _data.cend());
    }
    
    //-----------------------------------------------------------------------
    const double mean() noexcept
    {
        if (!_mean && _data.size() > 0) {
            _mean.value = std::accumulate(_data.cbegin(), _data.cend(), 0.0) / _data.size();
            _mean.evaluated = true;
        }

        return _mean ? _mean.value : 0.0;
    }

    //-----------------------------------------------------------------------
    const double median() noexcept
    {
        if (!_median && _data.size() > 0) {
            const std::uint32_t mid_index{ std::uint32_t(_data.size() / 2) };
            
            std::vector<std::uint32_t> copied_data{ _data };  // not to alter the original content of this histogram
            std::sort(copied_data.begin(), copied_data.end());

            if (copied_data.size() & 0x01 || copied_data.size() == 1)
                _median.value = double(copied_data[mid_index]);
            else
                _median.value = (copied_data[mid_index - 1] + copied_data[mid_index]) / 2.0;

            _median.evaluated = true;
        }

        return _median ? _median.value : 0.0;
    }

    //-----------------------------------------------------------------------
    const double stdev()
    {
        if (!_stdev && _data.size() > 1) {
            const double m{ mean() };
            std::vector<double> diff_m(_data.size());

            std::transform(
                _data.cbegin(), _data.cend(),
                diff_m.begin(),
                std::bind2nd(std::minus<double>(), m)
            );
            _stdev.value = std::inner_product(
                diff_m.cbegin(), diff_m.cend(),
                diff_m.cbegin(),
                0.0
            );
            _stdev.value = std::sqrt(_stdev.value / _data.size());

            _stdev.evaluated = true;
        }

        return _stdev ? _stdev.value : 0.0;
    }


private:
    std::vector<value_type> _data{};

    struct _StatItem
    {
        double value{ 0.0 };
        bool evaluated{ false };

        inline operator bool() const
        {
            return evaluated;
        }
    };

    _StatItem _mean{};
    _StatItem _median{};
    _StatItem _stdev{};

};


//===========================================================================
/** @brief Tests the equidistribution of every PRNGs as implemented in library CppRandLib.

    Copyright(c) 2025 Philippe Schmouker
    
    The Pseudo-Random Numbers Generators implemented in library  CppRandLib 
    have been chosen as being the best in class ones about their randmoness 
    quality - as evaluated with test program  TestU01(Pierre  L'Ecuyer  and  
    Richard  Simard  (Université  de Montréal) in 'TestU01: A C Library for 
    Empirical Testing of Random  Number  Generators - ACM  Transactions  on 
    Mathematical Software, vol.33 n.4, pp.22 - 40, August 2007').

    One of the main characteristics of these PRNGs is the  equidistribution 
    of the  generated  random numbers.Validating this equidistribution does 
    not ensure the correctness of any implementation  BUT  the  failure  of
    this  validation  ensures a not correct implementation.This is the sole 
    goal of this litle script.

    This script runs an N-times loop on each algprithm. At  each  loop,  it 
    draws  a  pseudorandom  number  in  the interval [0; 3,217) and sets an
    histogram of the drawings(3,217 entries).  It then evaluates statistics
    values  mean, median and standard  eviation for each histogram and, for
    each histogram entry,  evaluates its variance. Should mean value be far
    from N/3,217 or any variance get a too large value,  the script outputs
    all faulty values on console.
*/
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
const bool test_algo(
    const std::string& title,
    BaseRandom<StateT, OutputT, OUTPUT_BITS>* rnd_algo_ptr,
    const std::uint32_t nb_entries = 3'217,  // notice: 3217 is a prime number
    const std::uint32_t nb_loops = 30'000'000,
    const bool print_hist = false
)
{
    std::string rule{ std::string(title.size() + 1, '-') };
    std::cout << rule << std::endl << title << std::endl << rule << std::endl;

    Histogram hist(nb_entries);

    double expected_max_diff_mean_median{ (nb_loops / nb_entries) * 0.002 };  // i.e.difference should be less than 0.2 % of expected mean
    double expected_max_stdev{ 1.04 * sqrt(nb_loops / nb_entries) };          // i.e. + 4 % max over expected stdandard deviation
    constexpr double expected_max_variance{ 5.0 };                            // this is the absolute value of the expected max on local variance

    if (expected_max_diff_mean_median < 0.5)
        expected_max_diff_mean_median = 0.5;

    for (std::uint32_t i = 0; i < nb_loops; ++i) {
        const std::uint32_t index{ std::uint32_t((*rnd_algo_ptr)() * nb_entries) };
        hist[index]++;
    }

    if (print_hist)
        hist.print(); 

    const double mean{ hist.mean() };
    const double median{ hist.median() };
    const double stdev{ hist.stdev() };

    std::cout << nb_loops
        << " loops, "
        << nb_entries
        << " entries in histogram, expected mean: "
        << std::fixed << std::setprecision(1) << std::round(nb_loops / nb_entries)
        << std::endl
        << "  mean: " << mean
        << ", median: " << median
        << ", standard deviation " << std::fixed << std::setprecision(3) << stdev
        << std::endl;
    
    bool err{ false };

    if (std::abs(median - mean) > expected_max_diff_mean_median) {
        err = true;
        std::cout << "  incoherence btw. mean and median values, difference expected to be less than "
            << std::fixed << std::setprecision(1) << expected_max_diff_mean_median
            << std::endl;
    }

    if (stdev > expected_max_stdev) {
        err = true;
        std::cout << "  standard deviation is out of range, should be less than "
            << std::fixed << std::setprecision(3) << expected_max_stdev << " <<<<<"
            << std::endl;
    }

    double min_variance{ 0.0 };
    double max_variance{ 0.0 };

    for (std::uint32_t i = 0; i < nb_entries; ++i) {
        const double variance{ (hist[i] - mean) / stdev };
        if (std::abs(variance) > expected_max_variance) {
            err = true;
            std::cout << "  entry " << i
                << ": hist = " << hist[i]
                << ", variance = " << std::fixed << std::setprecision(4) << variance << " seems too large <<<<<" << std::endl;
        }

        if (variance < min_variance)
            min_variance = variance;
        else if (variance > max_variance)
            max_variance = variance;
    }

    std::cout << "  variances are in range ["
        << std::fixed << std::setprecision(3) << min_variance
        << " ; " << ((max_variance > 0.0) ? '+' : ' ') << max_variance
        << "], min: " << hist.min()
        << ", max: " << hist.max()
        << std::endl << std::endl;

    std::cout << "  Test " << (err ? "FAILED <<<<<" : "OK.") << std::endl;
    std::cout << std::endl;

    return !err;  // returns true if things were ok and false otherwise
}


//---------------------------------------------------------------------------
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
inline const bool test_algo(
    const std::string& title,
    BaseRandom<StateT, OutputT, OUTPUT_BITS>* rnd_algo_ptr,
    const bool print_hist
)
{
    return test_algo(title, rnd_algo_ptr, 3'217, 30'000'000, print_hist);
}


//===========================================================================
int main()
{
    bool ok{ true };

    {
        FastRand32 frand32;
        ok = test_algo("FastRand32", &frand32) && ok;
    }

    {
        FastRand63 frand63;
        ok = test_algo("FastRand63", &frand63) && ok;
    }

    {
        LFib78 lfib78;
        ok = test_algo("LFib78", &lfib78) && ok;
    }

    {
        LFib116 lfib116;
        ok = test_algo("LFib116", &lfib116) && ok;
    }

    {
        LFib668 lfib668;
        ok = test_algo("LFib668", &lfib668) && ok;
    }

    {
        LFib1340 lfib1340;
        ok = test_algo("LFib1340", &lfib1340) && ok;
    }

    {
        Mrg287 mrg287;
        ok = test_algo("Mrg287", &mrg287) && ok;
    }

    {
        Mrg1457 mrg1457;
        ok = test_algo("Mrg1457", &mrg1457) && ok;
    }

    {
        Mrg49507 mrg49507;
        ok = test_algo("Mrg49507", &mrg49507) && ok;
    }

    {
        Squares32 squares32;
        ok = test_algo("Squares32", &squares32) && ok;
    }

    {
        Squares64 squares64;
        ok = test_algo("Squares64", &squares64) && ok;
    }

    {
        Well512a well512a;
        ok = test_algo("Well512a", &well512a) && ok;
    }

    {
        Well1024a well1024a;
        ok = test_algo("Well1024a", &well1024a) && ok;
    }

    {
        Well19937c well19937c;
        ok = test_algo("Well19937c", &well19937c) && ok;
    }

    {
        Well44497b well44497b;
        ok = test_algo("Well44497b", &well44497b) && ok;
    }

    {
        Xoroshiro256 xoroshiro256;
        ok = test_algo("Xoroshiro256", &xoroshiro256) && ok;
    }

    {
        Xoroshiro512 xoroshiro512;
        ok = test_algo("Xoroshiro512", &xoroshiro512) && ok;
    }

    {
        Xoroshiro1024 xoroshiro1024;
        ok = test_algo("Xoroshiro1024", &xoroshiro1024) && ok;
    }

    if (ok)
        std::cout << "\n--> All tests PASSED\n\n";
    else
        std::cout << "\n>>>>> Some test FAILED <<<<<\n\n";
}
