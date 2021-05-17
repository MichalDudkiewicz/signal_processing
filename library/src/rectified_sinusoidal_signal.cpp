#include "rectified_sinusoidal_signal.hpp"
#include <cmath>

namespace cps {

    RectifiedSinusoidalSignal::RectifiedSinusoidalSignal(double amplitude, double initialTimeSec, double durationSec,
                                                         double period) : PeriodicSignal(amplitude, initialTimeSec,
                                                                                           durationSec, period) {

    }

    double RectifiedSinusoidalSignal::value(double x)
    {
        const double value = mAmplitude * fabs(sin(2 * M_PI / mPeriod * (x - mInitialTimeSec)));
        return value;
    }
}