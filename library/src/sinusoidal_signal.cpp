#include "sinusoidal_signal.hpp"
#include <cmath>

namespace cps {
    SinusoidalSignal::SinusoidalSignal(int amplitude, int initialTimeSec, int durationSec, double period)
    : Signal(amplitude, initialTimeSec, durationSec), mPeriod(period)
    {

    }

    double SinusoidalSignal::value(double x) const
    {
        double value = mAmplitude * sin(2 * M_PI / mPeriod * (x - mInitialTimeSec));
        return value;
    }
}