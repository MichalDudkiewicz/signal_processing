#include "utils.hpp"

#include <cmath>

namespace cps
{
    double round_up(double value, int decimal_places) {
        const double multiplier = std::pow(10.0, decimal_places);
        return std::ceil(value * multiplier) / multiplier;
    }

    double roundTo5(double value)
    {
        return round( value * 100000.0 ) / 100000.0;
    }

    double roundTo2(double value)
    {
        return round( value * 100.0 ) / 100.0;
    }
}
