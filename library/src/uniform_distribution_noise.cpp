#include "uniform_distribution_noise.hpp"
#include <cstdlib>
#include <ctime>

namespace cps {

    UniformDistributionNoise::UniformDistributionNoise(double amplitude, double initialTimeSec, double durationSec) : Signal(
            amplitude, initialTimeSec, durationSec) {
        std::srand(time(nullptr));
    }

    double UniformDistributionNoise::value(double /* x */) const {
        return -mAmplitude + (double)(rand()) / ((double)(RAND_MAX/(mAmplitude + mAmplitude)));
    }
}