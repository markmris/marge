#include "color.h"
#include "vector3.h"

void write_color(std::ostream out, const vector3 &color)
{
    auto r = color.x;
    auto g = color.y;
    auto b = color.z;

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ';
}