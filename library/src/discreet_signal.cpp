#include "discreet_signal.hpp"

namespace cps {

    DiscreetSignal::DiscreetSignal(double amplitude, int initialTimeSec, int durationSec, int samplingFrequency)
    : Signal(amplitude, initialTimeSec, durationSec), mSamplingFrequency(samplingFrequency)
    {

    }
}