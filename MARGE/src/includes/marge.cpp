#include "marge.h"

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degAsRad(double degrees)
{
    return (degrees * pi) / 180;
}

// Generate a random real number in [0, 1)
inline double randomDouble()
{
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}

// Generator a random real number in [min, max)
inline double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}