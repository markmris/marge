#include <algorithm>
#include "color.h"
#include "interval.h"

void writeColor(std::ostream& out, const color3& color)
{
    int rbyte = std::clamp(int(255.999 * color.x), 0, 255);
    int gbyte = std::clamp(int(255.999 * color.y), 0, 255);
    int bbyte = std::clamp(int(255.999 * color.z), 0, 255);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}