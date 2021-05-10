#include "impulse_noise.hpp"
#include <cmath>

namespace cps {

    ImpulseNoise::ImpulseNoise(double amplitude, double initialTimeSec, double durationSec, int samplingFrequency, double probability)
            : DiscreetSignal(amplitude, initialTimeSec, durationSec, samplingFrequency), mProbability(probability) {

    }

    double ImpulseNoise::value(double x) const
    {
        const double random = rand() / (RAND_MAX + 1.);
        if (random <= mProbability) {
            return mAmplitude;
        } else {
            return 0;
        }
    }
}