#include "signal.hpp"

namespace cps {

    Signal::Signal(int amplitude, int initialTimeSec, int durationSec)
    : mAmplitude(amplitude), mInitialTimeSec(initialTimeSec), mDurationSec(durationSec)
    {
    }

    int Signal::duration() const {
        return mDurationSec;
    }

    int Signal::initialTime() const {
        return mInitialTimeSec;
    }
}