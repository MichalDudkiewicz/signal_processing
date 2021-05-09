#ifndef SIGNAL_PROCESSING_UNIFORM_DISTRIBUTION_NOISE_HPP
#define SIGNAL_PROCESSING_UNIFORM_DISTRIBUTION_NOISE_HPP

#include "signal.hpp"

namespace cps {
    class UniformDistributionNoise : public Signal {
    public:
        UniformDistributionNoise(int amplitude, int initialTimeSec, int durationSec);

    public:
        double value(double /* x */) const override;
    };
}

#endif //SIGNAL_PROCESSING_UNIFORM_DISTRIBUTION_NOISE_HPP
