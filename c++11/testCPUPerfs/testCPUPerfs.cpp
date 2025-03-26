/*
MIT License

Copyright (c) 2025 Philippe Schmouker, ph.schmouker (at) gmail.com

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
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

#include "cpprandlib.h"


//===========================================================================
/** @brief Evaluates the CPU time spent evaluating output values. */
template<typename StateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
void test_perf(
    const std::string& title,
    BaseRandom<StateT, OutputT, OUTPUT_BITS>* rnd_algo_ptr,
    std::size_t nb_loops = 10'000'000,
    const std::size_t nb_repeats = 20
)
{
    std::cout << "--- " << title << " ---" << std::endl;

    std::vector<std::uint64_t> perfs(nb_repeats);
    constexpr std::size_t LOOP_CLUSTER_SIZE{ 100 };

    const std::size_t loops_count{ nb_loops / LOOP_CLUSTER_SIZE };
    nb_loops = loops_count * LOOP_CLUSTER_SIZE;

    for (auto& p : perfs) {
        const std::uint64_t start{ utils::get_time_ns() };

        for (std::size_t i = 0; i < loops_count; ++i) {
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
            rnd_algo_ptr->next();
        }

        const std::uint64_t end{ utils::get_time_ns() };

        p = end - start;
    }

    const double nanoseconds{ 1.0 / nb_loops };
    for (std::uint64_t p : perfs)
        std::cout << p * nanoseconds << ' ';
    std::cout << std::endl;

    std::cout << "--> " << std::fixed << std::setprecision(4) << *std::min_element(perfs.cbegin(), perfs.cend()) * nanoseconds << " ns\n\n";
}


//===========================================================================
int main()
{
    {
        FastRand32 frand32(0x3ca5'8796ul);
        test_perf("FastRand32", &frand32);
    }

    {
        FastRand63 frand63(0x3ca5'8796'1f2e'b45aull);
        test_perf("FastRand63", &frand63);
    }

    {
        LFib78 lfib68(0x3ca5'8796'1f2e'b45aull);
        test_perf("LFib78", &lfib68);
    }

    {
        LFib116 lfib116(0x3ca5'8796'1f2e'b45aull);
        test_perf("LFib116", &lfib116);
    }

    {
        LFib668 lfib668(0x3ca5'8796'1f2e'b45aull);
        test_perf("LFib668", &lfib668);
    }

    {
        LFib1340 lfib1340(0x3ca5'8796'1f2e'b45aull);
        test_perf("LFib1340", &lfib1340);
    }

    {
        Mrg287 mrg287(0x3ca5'8796ul);
        test_perf("Mrg287", &mrg287);
    }

    {
        Mrg1457 mrg1457(0x3ca5'8796ul);
        test_perf("Mrg1457", &mrg1457);
    }

    {
        Mrg49507 mrg49507(0x3ca5'8796ul);
        test_perf("Mrg49507", &mrg49507);
    }

    {
        Squares32 squares32(0x3ca5'8796'1f2e'b45aull);
        test_perf("Squares32", &squares32);
    }

    {
        Well512a well512a(0x3ca5'8796ul);
        test_perf("Well512a", &well512a);
    }

    {
        Well1024a well1024a(0x3ca5'8796ul);
        test_perf("Well1024a", &well1024a);
    }

    {
        Well19937c well19937c(0x3ca5'8796ul);
        test_perf("Well19937c", &well19937c);
    }

    {
        Well44497b well44497b(0x3ca5'8796ul);
        test_perf("Well44497b", &well44497b);
    }

    {
        Xoroshiro256 xoroshiro256(0x3ca5'8796'1f2e'b45aull);
        test_perf("Xoroshiro256", &xoroshiro256);
    }

    {
        Xoroshiro512 xoroshiro512(0x3ca5'8796'1f2e'b45aull);
        test_perf("Xoroshiro512", &xoroshiro512);
    }

    {
        Xoroshiro1024 xoroshiro1024(0x3ca5'8796'1f2e'b45aull);
        test_perf("Xoroshiro1024", &xoroshiro1024);
    }

    {
        BaseXoroshiro<4> base_xoroshiro;
        test_perf("BaseXoroshiro<4>", &base_xoroshiro);
    }

    {
        BaseRandom<std::uint32_t> base_xoroshiro;
        test_perf("BaseRandom", &base_xoroshiro);
    }

}
