#include "sinusoidal_signal.hpp"
#include <cmath>

namespace cps {
    SinusoidalSignal::SinusoidalSignal(double amplitude, int initialTimeSec, int durationSec, double period)
    : PeriodicSignal(amplitude, initialTimeSec, durationSec, period)
    {

    }

    double SinusoidalSignal::value(double x) const
    {
        double value = mAmplitude * sin(2 * M_PI / mPeriod * (x - mInitialTimeSec));
        return value;
    }
}