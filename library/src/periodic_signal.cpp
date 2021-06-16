#include "periodic_signal.hpp"
#include <cmath>
#include "utils.hpp"

namespace cps {

    double PeriodicSignal::period() const {
        return mPeriod;
    }

    PeriodicSignal::PeriodicSignal(double amplitude, double initialTimeSec, double durationSec, double periodSec)
    : Signal(amplitude, initialTimeSec, roundTo2(floor(durationSec / periodSec) * periodSec)), mPeriod(periodSec)
    {
    }
}