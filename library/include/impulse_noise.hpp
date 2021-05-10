#ifndef SIGNAL_PROCESSING_IMPULSE_NOISE_HPP
#define SIGNAL_PROCESSING_IMPULSE_NOISE_HPP

#include "discreet_signal.hpp"

namespace cps {
    class ImpulseNoise : public DiscreetSignal {
    public:
        ImpulseNoise(double amplitude, double initialTimeSec, double durationSec, int samplingFrequency, double probability);

    public:
        double value(double x) const override;

    private:
        double mProbability;
    };
}

#endif //SIGNAL_PROCESSING_IMPULSE_NOISE_HPP
