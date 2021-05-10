#include "signal.hpp"
#include "signal_sampler.hpp"

namespace cps {

    Signal::Signal(double amplitude, int initialTimeSec, int durationSec)
    : mAmplitude(amplitude), mInitialTimeSec(initialTimeSec), mDurationSec(durationSec)
    {
    }

    int Signal::duration() const {
        return mDurationSec;
    }

    int Signal::initialTime() const {
        return mInitialTimeSec;
    }

    SignalData Signal::data(int samplingFrequency) const
    {
        SignalSampler signalSampler(samplingFrequency);
        return signalSampler.sample(*this);
    }
}