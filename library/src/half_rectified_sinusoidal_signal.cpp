#include "half_rectified_sinusoidal_signal.hpp"
#include <cmath>

namespace cps {

    HalfRectifiedSinusoidalSignal::HalfRectifiedSinusoidalSignal(double amplitude, double initialTimeSec, double durationSec,
                                                                 double period) : PeriodicSignal(amplitude,
                                                                                                   initialTimeSec,
                                                                                                   durationSec,
                                                                                                   period) {

    }

    double HalfRectifiedSinusoidalSignal::value(double x) {
        const double value = mAmplitude / 2 * ( sin(2 * M_PI / mPeriod * (x - mInitialTimeSec)) + fabs(sin(2 * M_PI / mPeriod * (x - mInitialTimeSec))));
        return value;
    }
}