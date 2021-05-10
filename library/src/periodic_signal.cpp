#include "periodic_signal.hpp"
#include <cmath>

namespace cps {

    double PeriodicSignal::period() const {
        return mPeriod;
    }

    PeriodicSignal::PeriodicSignal(double amplitude, double initialTimeSec, double durationSec, double periodSec)
    : Signal(amplitude, initialTimeSec, floor(initialTimeSec + durationSec / periodSec) * periodSec), mPeriod(periodSec)
    {
    }
}