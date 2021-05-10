#include "discreet_signal.hpp"

namespace cps {

    DiscreetSignal::DiscreetSignal(double amplitude, double initialTimeSec, double durationSec, int samplingFrequency)
    : Signal(amplitude, initialTimeSec, durationSec), mSamplingFrequency(samplingFrequency)
    {

    }
}