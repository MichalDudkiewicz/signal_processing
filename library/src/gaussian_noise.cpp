#include "gaussian_noise.hpp"
#include <cmath>
#include <random>
#include <algorithm>

namespace cps {

    GaussianNoise::GaussianNoise(double amplitude, double initialTimeSec, double durationSec)
    : Signal(amplitude, initialTimeSec, durationSec)
    {

    }

    double GaussianNoise::value(double x)
    {
        const auto p = std::find (mData.x.begin(), mData.x.end(), x);
        if (p != mData.x.end())
        {
            for (int i = 0; i<mData.x.size(); i++)
            {
                if (mData.x[i] == x)
                {
                    return mData.y[i];
                }
            }
            throw std::runtime_error("out of range");
        }
        else
        {
            const double mean = 0;
            const double stddev = 1;
//        const double noise = exp(-pow(value - mean, 2) / (2 * pow(stddev, 2))) / (stddev * sqrt(2 * M_PI));

            std::random_device rd;
            std::mt19937 gen(rd());

            std::normal_distribution<> d(mean, stddev);
            const double value = d(gen);

            mData.x.push_back(x);
            mData.y.push_back(value);

            return value;
        }
    }
}