#ifndef SIGNAL_PROCESSING_DISCREET_SIGNAL_HPP
#define SIGNAL_PROCESSING_DISCREET_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class DiscreetSignal : public Signal {
    public:
        DiscreetSignal(double amplitude, int initialTimeSec, int durationSec, int samplingFrequency);

    protected:
        int mSamplingFrequency;

    };
}

#endif //SIGNAL_PROCESSING_DISCREET_SIGNAL_HPP
