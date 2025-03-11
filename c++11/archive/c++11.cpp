// c++11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//===========================================================================
/** /
#include <array>
#include <cstring>
#include <vector>

#include "lfib78.h"
/**/

#include <exception>
#include <iostream>

#include "uint128.h"


//===========================================================================
template<typename T>
void test_eq(const T u, const T v)
{
    if (u != v)
        throw std::exception("TEST_EQ failed");
}


//===========================================================================
int main()
{
    //-----   Let's test 128-bits arithmetic   -----//
    std::cout << "Let's test 128-bits arithmetic" << std::endl;

    utils::UInt128 a, b;

    test_eq(a.data.i64.hi, 0ull);
    test_eq(a.data.i64.lo, 0ull);
    test_eq(b.data.i64.hi, 0ull);
    test_eq(b.data.i64.lo, 0ull);

    std::cout << "--> All tests PASSED" << std::endl;

    a = 0xffff'ffff'ffff'ffffull;
    test_eq(a.data.i64.hi, 0ull);
    test_eq(a.data.i64.lo, 0xffff'ffff'ffff'ffffull);

    a += 1ull;
    test_eq(a.data.i64.hi, 1ull);
    test_eq(a.data.i64.lo, 0ull);



    /** /
    //-----   Let's test LFib78   -----//

    LFib78 br{};

    std::cout << br() << std::endl;
    std::cout << br(5) << std::endl;

    std::vector<float> res{ br(std::vector<float>{1.f,2.f,3.f,4.f,5.1f}) };
    for (float r : res)
        std::cout << r << ' ';
    std::cout << std::endl;

    std::vector<double> res2{ br(std::vector<double>{1,2,3,4,5.1}, std::vector<double>{11,12,13,14}) };
    for (double r : res2)
        std::cout << r << ' ';
    std::cout << std::endl;

    std::vector<double> res3;
    res3 = br.n_evaluate(4);
    for (int i = 0; i < 4; ++i)
        std::cout << res3[i] << ' ';
    std::cout << std::endl;

    std::cout << "\n=====\n\n";
    LFib78 br1;
    br1.setstate(0.5);
    for (int i = 0; i < 47; ++i)
        br1.random();
    std::cout << br1() << std::endl;
    std::cout << br1(5) << std::endl;

    std::cout << br1.choice(std::vector<char>{'A', 'B', 'C', 'D'}) << std::endl;
    std::cout << br1.choice(std::array<char, 5>{'A', 'B', 'C', 'D', 'E'}) << std::endl;

    std::cout << br1.randrange(1, 12, 2) << std::endl;

    std::array<int, 7> out;
    std::array<int, 10> population{ 1,2,3,4,5,6,7,8,9,0 };
    br1.sample(out, population);
    for (int i = 0; i < out.size(); ++i)
        std::cout << out[i] << ' ';
    std::cout << std::endl;

    std::array<int, 9> out1;
    br1.sample(out1, population);
    for (int i = 0; i < out1.size(); ++i)
        std::cout << out1[i] << ' ';
    std::cout << std::endl;

    std::vector<int> population_v{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 10 };
    std::vector<int> out2;
    br1.sample(out2, population_v, 6);
    for (int i = 0; i < out2.size(); ++i)
        std::cout << out2[i] << ' ';
    std::cout << std::endl;

    br1.sample(out2, std::vector<int>{21, 22, 23}, std::vector<short>{1, 2, 3}, 4);
    for (int i = 0; i < out2.size(); ++i)
        std::cout << out2[i] << ' ';
    std::cout << std::endl;

    br1.sample(out, population, std::array<unsigned char, 10>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
    for (int i = 0; i < out.size(); ++i)
        std::cout << out[i] << ' ';
    std::cout << std::endl;

    br1.shuffle(population);
    for (auto p : population)
        std::cout << p << ' ';
    std::cout << std::endl;

    std::vector<int>pop_v{ 11,12,13,14,15,16,17,18,19,10 };
    br1.shuffle(pop_v);
    for (auto p : pop_v)
        std::cout << p << ' ';
    std::cout << std::endl;


    for (int i=0; i<5; ++i)
        std::cout << br1.betavariate(2.0, 1.5) << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.expovariate(1.5) << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.gammavariate(2.0, 1.5) << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.gauss() << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.gauss(2.0, 1.5) << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.lognormvariate() << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.lognormvariate(2.0, 1.5) << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.paretovariate(0.5) << ' ';
    std::cout << std::endl;

    std::cout << br1.triangular() << ' ';
    std::cout << br1.triangular(1, 6) << ' ';
    std::cout << br1.triangular(1, 6, 5) << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.vonmisesvariate(5.0, 0.5) << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
        std::cout << br1.weibullvariate(5.0, 0.5) << ' ';
    std::cout << std::endl;

    std::cout << std::endl;
    std::array<uint32_t, 6> hist{ 0 };
    for (size_t i = 0; i < 200'000'000; ++i)
        hist[br1.uniform(6)]++;
    for (int i = 0; i < 6; ++i)
        std::cout << hist[i] << ' ';
    std::cout << std::endl;
    /**/


    return 0;
}
