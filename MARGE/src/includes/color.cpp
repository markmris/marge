#include <algorithm>
#include <cmath>
#include "color.h"
#include "marge.h"

void writeColor(std::ostream& out, const color3& color)
{
    int rbyte = std::clamp(int(255.999 * linearToGamma(color.x)), 0, 255);
    int gbyte = std::clamp(int(255.999 * linearToGamma(color.y)), 0, 255);
    int bbyte = std::clamp(int(255.999 * linearToGamma(color.z)), 0, 255);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

double linearToGamma(double linearComponent)
{
    if (linearComponent > 0)
        return std::sqrt(linearComponent);

    return 0;
}

color3 randomColor()
{
    return color3(randomDouble(0, 1), randomDouble(0, 1), randomDouble(0, 1));
}

color3 randomColor(double min, double max)
{
    if (min < 0) min *= -1;
    if (max < 0) max *= -1;

    return color3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}