#ifndef SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP
#define SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP

#include "signal.hpp"

namespace cps {
    class GaussianNoise : public Signal {
    public:
        GaussianNoise(double amplitude, int initialTimeSec, int durationSec);

    public:
        double value(double /* x */) const override;
    };
}

#endif //SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP
