#include "color.h"

void writecolor(std::ostream& out, const color3 &color)
{
    auto r = color.x;
    auto g = color.y;
    auto b = color.z;

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}