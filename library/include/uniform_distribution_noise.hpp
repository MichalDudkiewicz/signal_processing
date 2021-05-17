#ifndef SIGNAL_PROCESSING_UNIFORM_DISTRIBUTION_NOISE_HPP
#define SIGNAL_PROCESSING_UNIFORM_DISTRIBUTION_NOISE_HPP

#include "signal.hpp"

namespace cps {
    class UniformDistributionNoise : public Signal {
    public:
        UniformDistributionNoise(double amplitude, double initialTimeSec, double durationSec);

    public:
        double value(double x) override;

    private:
        SignalData mData;
    };
}

#endif //SIGNAL_PROCESSING_UNIFORM_DISTRIBUTION_NOISE_HPP
