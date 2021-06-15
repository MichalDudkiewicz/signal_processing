#include "high_pass_filter.hpp"

#include <utility>
#include <cmath>

namespace cps {

    HighPassFilter::HighPassFilter(int M, double fo, std::shared_ptr<Window> window) : LowPassFilter(M, fo, std::move(window)) {

    }

    int HighPassFilter::s(int n) const {
        return pow(-1, n);
    }
}