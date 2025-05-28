#pragma once
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
#include <functional>
#include <numeric>
#include <vector>


//===========================================================================
/** @brief The class of histograms and their associated statistics evaluations. */
class Histogram
{
public:
    using value_type = std::uint32_t;
    using index_type = std::uint32_t;

    //-----------------------------------------------------------------------
    inline Histogram(const index_type entries_count)
    {
        reset(entries_count);
    }

    //-----------------------------------------------------------------------
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
    inline const bool is_mean_median_difference_ok(const std::uint64_t loops_nb) noexcept
    {
        const std::size_t entries_nb{ _data.size() };

        if (entries_nb == 0)
            return false;  // no empty histogram should not happen 

        const double expected_mean{ double(loops_nb) / entries_nb };
        const double expected_max_mean_median_diff{ expected_mean * 0.003 };  // i.e. difference should be less than 0.3 % of expected mean
        const double mean_median_diff{ std::abs(get_median() - get_mean())};
        
        return mean_median_diff <= expected_max_mean_median_diff;
    }

    //-----------------------------------------------------------------------
    inline const bool is_stdev_ok(const std::uint64_t loops_nb) noexcept
    {
        const std::size_t entries_nb{ _data.size() };

        if (entries_nb == 0)
            return false;  // no empty histogram should not happen 

        const double expected_max_stdev{ 1.05 * sqrt(double(loops_nb) / entries_nb) };  // i.e. +5 % max over expected stdandard deviation
        return get_stdev() <= expected_max_stdev;
    }
     
    //-----------------------------------------------------------------------
    inline const bool is_variance_ok() noexcept
    {
        constexpr double expected_max_variance{ 5.5 };  // this is the absolute value of the expected max on local variance
        const double _mean{ get_mean() };
        const double _stdev{ get_stdev() };
        
        for (value_type d : _data) {
            const double variance{ (d - _mean) / _stdev };
            if (std::abs(variance) > expected_max_variance)
                return false;
        }
        return true;
    }

    //-----------------------------------------------------------------------
    const double get_mean() noexcept
    {
        if (!_mean && _data.size() > 0) {
            _mean.value = std::accumulate(_data.cbegin(), _data.cend(), 0.0) / _data.size();
            _mean.evaluated = true;
        }

        return _mean ? _mean.value : 0.0;
    }

    //-----------------------------------------------------------------------
    const double get_median() noexcept
    {
        if (!_median && _data.size() > 0) {
            const std::uint32_t mid_index{ std::uint32_t(_data.size() / 2) };

            std::vector<value_type> copied_data{ _data };  // not to alter the original content of this histogram
            std::sort(copied_data.begin(), copied_data.end());

            if (copied_data.size() & 0x01)
                _median.value = double(copied_data[mid_index]);
            else
                _median.value = (copied_data[mid_index - 1] + copied_data[mid_index]) / 2.0;

            _median.evaluated = true;
        }

        return _median ? _median.value : 0.0;
    }

    //-----------------------------------------------------------------------
    void reset(const index_type entries_count)
    {
        _data.clear();
        _data.resize(entries_count);
        _mean.evaluated = _median.evaluated = _stdev.evaluated = false;
    }

    //-----------------------------------------------------------------------
    const double get_stdev()
    {
        if (!_stdev && _data.size() > 1) {
            const double m{ get_mean() };
            std::vector<double> diff_m(_data.size());

#if defined(_DEBUG) && defined(WIN32)  // due to strange behavior with VS2022, for which std::bind2nd is not defined!
            auto data_it{ _data.cbegin() };
            for (auto& dm : diff_m) {
                dm = *data_it++ - m;
            }
#else
            std::transform(
                _data.cbegin(), _data.cend(),
                diff_m.begin(),
                std::bind2nd(std::minus<double>(), m)
            );
#endif
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
