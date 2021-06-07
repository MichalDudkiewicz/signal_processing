#include "custom_signal.hpp"
#include <stdexcept>
#include <utility>
#include <cmath>

namespace cps {

    double CustomSignal::value(double x) {
        const double step = mData.x[1] - mData.x.front();
        for (int i = 0; i<mData.x.size(); i++)
        {
            if (x >= mData.x[i] - step/2 - 0.00001 && x < mData.x[i] + step/2)
            {
                return mData.y[i];
            }
        }
        throw std::runtime_error("out of range");
    }

    SignalData CustomSignal::data() {
        return mData;
    }

    CustomSignal::CustomSignal(double amplitude, double initialTimeSec, double durationSec, SignalData data)
    : Signal(amplitude, initialTimeSec, durationSec), mData(std::move(data)) {

    }

    void CustomSignal::unserialize(std::istream &istream) {
        istream.read(reinterpret_cast<char*>(&mInitialTimeSec), sizeof mInitialTimeSec);
        istream.read(reinterpret_cast<char*>(&mSamplingFrequency), sizeof mSamplingFrequency);
        unsigned long numberOfSamples;
        istream.read(reinterpret_cast<char*>(&numberOfSamples), sizeof numberOfSamples);
        mDurationSec = ((double)numberOfSamples - 1.f) / mSamplingFrequency;
        double y;
        double amplitude = 0;
        double x = mInitialTimeSec;
        const double deltaX = mDurationSec / ((double)numberOfSamples - 1.f);
        while (x <= mDurationSec)
        {
            istream.read(reinterpret_cast<char*>(&y), sizeof y);
            mData.x.push_back(x);
            mData.y.push_back(y);
            if (fabs(y) > amplitude)
            {
                amplitude = fabs(y);
            }
            x += deltaX;
        }
        mAmplitude = amplitude;
    }

    CustomSignal::CustomSignal() : Signal(0, 0, 0), mData()
    {

    }
}