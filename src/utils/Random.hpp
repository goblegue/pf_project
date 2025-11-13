#include <random>
#include <chrono>

std::random_device rd; // obtain a random number from hardware
inline std::mt19937 generate()
{
    std::seed_seq ss{static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    return std::mt19937{ss};
}
inline std::mt19937 random{generate()}; // object to generate random numbers
inline int getRand(int min, int max)
{
    std::uniform_int_distribution<int> distr(min, max); // defines the range
    return distr(random);
}