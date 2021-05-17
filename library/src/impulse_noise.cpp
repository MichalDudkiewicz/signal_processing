#include "impulse_noise.hpp"
#include <cmath>
#include <algorithm>

namespace cps {

    ImpulseNoise::ImpulseNoise(double amplitude, double initialTimeSec, double durationSec, int samplingFrequency, double probability)
            : DiscreetSignal(amplitude, initialTimeSec, durationSec, samplingFrequency), mProbability(probability) {

    }

    double ImpulseNoise::value(double x)
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
            const double random = rand() / (RAND_MAX + 1.);
            mData.x.push_back(x);
            if (random <= mProbability) {
                mData.y.push_back(mAmplitude);
                return mAmplitude;
            } else {
                mData.y.push_back(0);
                return 0;
            }
        }
    }
}