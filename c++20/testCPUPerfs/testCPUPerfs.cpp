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
#include <format>
#include <iostream>
#include <vector>

#include "cpprandlib.h"


//===========================================================================
/** @brief Evaluates the CPU time spent evaluating output values. */
template<typename SeedStateT, typename OutputT, const std::uint8_t OUTPUT_BITS>
void test_perf(
    const std::string& title,
    BaseRandom<SeedStateT, OutputT, OUTPUT_BITS>* rnd_algo,
    const std::size_t seed_value,
    std::size_t nb_loops,
    const std::size_t nb_repeats
)
{
    std::cout << "--- " << title << " ---" << std::endl;

    std::vector<std::uint64_t> perfs(nb_repeats);
    constexpr std::size_t LOOP_CLUSTER_SIZE{ 100 };

    const std::size_t loops_count{ nb_loops / LOOP_CLUSTER_SIZE };
    nb_loops = loops_count * LOOP_CLUSTER_SIZE;

    for (auto& p : perfs) {
        const std::uint64_t start{ utils::get_time_us() };

        for (std::size_t i = 0; i < loops_count; ++i) {
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
            rnd_algo->next();
        }

        const std::uint64_t end{ utils::get_time_us() };

        p = end - start;
    }

    const double nanoseconds{ 1000.0 / nb_loops };
    for (std::uint64_t p : perfs)
        std::cout << p * nanoseconds << ' ';
    std::cout << std::endl;

    std::cout << std::format("--> {:.4f} ns\n\n", *std::min_element(perfs.cbegin(), perfs.cend()) * nanoseconds);
}


//===========================================================================
int main()
{
    FastRand32 frand32;
    test_perf("FastRand32", &frand32, 0x3ca5'8796, 10'000'000, 15);

    FastRand63 frand63;
    test_perf("FastRand63", &frand63, 0x3ca5'8796'1f2e'b45a, 10'000'000, 15);

    LFib78 lfib68;
    test_perf("LFib78", &lfib68, 0x3ca5'8796'1f2e'b45a, 10'000'000, 15);

    LFib116 lfib116;
    test_perf("LFib116", &lfib116, 0x3ca5'8796'1f2e'b45a, 10'000'000, 15);

    LFib668 lfib668;
    test_perf("LFib668", &lfib668, 0x3ca5'8796'1f2e'b45a, 10'000'000, 15);

    LFib1340 lfib1340;
    test_perf("LFib1340", &lfib1340, 0x3ca5'8796'1f2e'b45a, 10'000'000, 15);

    Mrg287 mrg287;
    test_perf("Mrg287", &mrg287, 0x3ca5'8796, 10'000'000, 15);

    Mrg1457 mrg1457;
    test_perf("Mrg1457", &mrg1457, 0x3ca5'8796, 10'000'000, 15);

    Mrg49507 mrg49507;
    test_perf("Mrg49507", &mrg49507, 0x3ca5'8796, 10'000'000, 15);

}
