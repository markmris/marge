#include "marge.h"

interval::interval() : min(infinity), max(-infinity) {};
interval::interval(double min, double max) : min(min), max(max) {};

interval::interval(const interval& a, const interval& b)
{
    min = std::fmin(a.min, b.min);
    max = std::fmax(a.max, b.max);
}

double interval::size() const
{
    return max - min;
}

bool interval::contains(double x) const
{
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const
{
    return min < x && x < max;
}

interval interval::expand(double delta) const
{
    double padding = delta / 2;

    return interval(min - padding, max - padding);
}

const interval interval::empty = interval(infinity, -infinity);
const interval interval::universe = interval(-infinity, infinity);