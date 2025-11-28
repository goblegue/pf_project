#include <random>
#include <chrono>

inline std::random_device rd; // obtain a random number from hardware (inline to avoid ODR violations)

/**
 * @brief generates a random number generator
 * @returns the random number generator
 */
inline std::mt19937 generate()
{
    std::seed_seq ss{static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    return std::mt19937{ss};
}

// name the engine `rng` to avoid collision with the C function `random()`
inline std::mt19937 rng{generate()}; // object to generate random numbers

/**
 * @brief gets a random integer in a range
 * @param min the minimum value
 * @param max the maximum value
 * @returns the random integer
 */
inline int getRand(int min, int max)
{
    std::uniform_int_distribution<int> distr(min, max); // defines the range
    return distr(rng);
}