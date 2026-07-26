#include <algorithm>
#include <cmath>
#include "color.h"

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