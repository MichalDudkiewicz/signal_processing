#include "periodic_signal.hpp"

namespace cps {

    double PeriodicSignal::period() const {
        return mPeriod;
    }

    PeriodicSignal::PeriodicSignal(double amplitude, int initialTimeSec, int durationSec, double periodSec)
    : Signal(amplitude, initialTimeSec, durationSec), mPeriod(periodSec)
    {

    }
}