#include "rectified_sinusoidal_signal.hpp"
#include <cmath>

namespace cps {

    RectifiedSinusoidalSignal::RectifiedSinusoidalSignal(double amplitude, int initialTimeSec, int durationSec,
                                                         double period) : SinusoidalSignal(amplitude, initialTimeSec,
                                                                                           durationSec, period) {

    }

    double RectifiedSinusoidalSignal::value(double x) const
    {
        const double value = mAmplitude * fabs(sin(2 * M_PI / mPeriod * (x - mInitialTimeSec)));
        return value;
    }
}