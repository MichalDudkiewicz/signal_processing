#include "gaussian_noise.hpp"
#include <cmath>

namespace cps {

    GaussianNoise::GaussianNoise(double amplitude, int initialTimeSec, int durationSec)
    : Signal(amplitude, initialTimeSec, durationSec)
    {

    }

    double GaussianNoise::value(double /* x */) const
    {
        const double mean = 0;
        const double stddev = 1;
        const double value = -mAmplitude + (double)(rand()) / ((double)(RAND_MAX/(mAmplitude + mAmplitude)));
        const double noise = exp(-pow(value - mean, 2) / (2 * pow(stddev, 2))) / (stddev * sqrt(2 * M_PI));
        return noise;
    }
}