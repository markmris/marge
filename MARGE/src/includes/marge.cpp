#include "marge.h"

const double infinity = std::numeric_limits<double>::infinity();
const double pi = std::numbers::pi;

double degAsRad(double degrees)
{
    return (degrees * pi) / 180;
}

// Generate a random real number in [0, 1)
double randomDouble()
{
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}

// Generate a random real number in [min, max)
double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}

int randomInt()
{
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_int_distribution<int> distribution(0, 1);

    return distribution(generator);
}

int randomInt(int min, int max)
{
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}