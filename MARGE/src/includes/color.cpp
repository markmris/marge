#include <algorithm>
#include "color.h"
#include "interval.h"

void writeColor(std::ostream& out, const color3 &color)
{
    auto r = color.x;
    auto g = color.y;
    auto b = color.z;

    int rbyte = std::clamp(int(255.999 * r), 0, 255);
    int gbyte = std::clamp(int(255.999 * g), 0, 255);
    int bbyte = std::clamp(int(255.999 * b), 0, 255);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}