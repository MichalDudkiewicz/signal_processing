#include "utils.hpp"

#include <cmath>

namespace cps
{
    double roundTo5(double value)
    {
        return round( value * 100000.0 ) / 100000.0;
    }
}
