#include "gaussian_noise.hpp"
#include <cmath>
#include <random>

namespace cps {

    GaussianNoise::GaussianNoise(double amplitude, int initialTimeSec, int durationSec)
    : Signal(amplitude, initialTimeSec, durationSec)
    {

    }

    double GaussianNoise::value(double /* x */) const
    {
        const double mean = 0;
        const double stddev = 1;
//        const double noise = exp(-pow(value - mean, 2) / (2 * pow(stddev, 2))) / (stddev * sqrt(2 * M_PI));

        std::random_device rd;
        std::mt19937 gen(rd());

        std::normal_distribution<> d(mean, stddev);
        const double value = d(gen);

        return value;
    }
}