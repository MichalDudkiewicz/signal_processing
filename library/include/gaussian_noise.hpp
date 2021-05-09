#ifndef SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP
#define SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP

#include "signal.hpp"

namespace cps {
    class GaussianNoise : public Signal {
    public:
        GaussianNoise(int amplitude, int initialTimeSec, int durationSec);

    public:
        double value(double /* x */) const override;

    private:
        double mMean;
        double mStdDev;
    };
}

#endif //SIGNAL_PROCESSING_GAUSSIAN_NOISE_HPP
