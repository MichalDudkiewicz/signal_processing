#include "uniform_distribution_noise.hpp"
#include <cstdlib>
#include <ctime>

namespace cps {

    UniformDistributionNoise::UniformDistributionNoise(int amplitude, int initialTimeSec, int durationSec) : Signal(
            amplitude, initialTimeSec, durationSec) {
        std::srand(time(nullptr));
    }

    double UniformDistributionNoise::value(double /* x */) const {
        return -mAmplitude + (double)(rand()) / ((double)(RAND_MAX/(mAmplitude + mAmplitude)));
    }
}