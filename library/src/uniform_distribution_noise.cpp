#include "uniform_distribution_noise.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace cps {

    UniformDistributionNoise::UniformDistributionNoise(double amplitude, double initialTimeSec, double durationSec) : Signal(
            amplitude, initialTimeSec, durationSec) {
        std::srand(time(nullptr));
    }

    double UniformDistributionNoise::value(double x) {
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
            mData.x.push_back(x);
            const double y = -mAmplitude + (double)(rand()) / ((double)(RAND_MAX/(mAmplitude + mAmplitude)));
            mData.y.push_back(y);
            return y;
        }
    }
}