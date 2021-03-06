#ifndef SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP
#define SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP

#include "signal.hpp"

namespace cps {
    class GaussianNoise : public Signal {
    public:
        GaussianNoise(double amplitude, double initialTimeSec, double durationSec);

    public:
        double value(double x) override;

    private:
        SignalData mData;
    };
}

#endif //SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP
