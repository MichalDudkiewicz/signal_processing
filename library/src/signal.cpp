#include "signal.hpp"
#include "signal_sampler.hpp"
#include <cmath>
#include "custom_signal.hpp"

namespace cps {

    Signal::Signal(double amplitude, double initialTimeSec, double durationSec)
    : mAmplitude(amplitude), mInitialTimeSec(initialTimeSec), mDurationSec(durationSec)
    {
    }

    double Signal::duration() const {
        return mDurationSec;
    }

    double Signal::initialTime() const {
        return mInitialTimeSec;
    }

    SignalData Signal::data() const
    {
        SignalSampler signalSampler(mSamplingFrequency);
        return signalSampler.sample(*this);
    }

    double Signal::mean() const {
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < data.x.size(); i++) {
            sum += data.y[i];
        }
        return sum / size;
    }

    double Signal::absMean() const {
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < size; i++) {
            sum += fabs(data.y[i]);
        }
        return sum / size;
    }

    double Signal::rms() const {
        return sqrt(meanPower());
    }

    double Signal::variance() const {
        double mean = Signal::mean();
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < size; i++) {
            sum += pow(data.y[i] - mean, 2.0);
        }
        return sum / size;
    }

    double Signal::meanPower() const {
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < data.x.size(); i++) {
            sum += pow(data.y[i], 2.0);
        }
        return sum / size;
    }

    void Signal::setSamplingFrequency(int samplingFrequency) {
        mSamplingFrequency = samplingFrequency;
    }

    CustomSignal Signal::operator*(const Signal& signal) const
    {
        if (signal.mSamplingFrequency == mSamplingFrequency && signal.initialTime() == mInitialTimeSec && signal.duration() == mDurationSec)
        {
            SignalData newData;
            const auto data1 = data();
            const auto data2 = signal.data();
            double amplitude = 0;
            for (int i = 0; i < data1.x.size(); i++)
            {
                newData.x.push_back(data1.x[i]);
                newData.y.push_back(data1.y[i] * data2.y[i]);
                if (fabs(newData.y[i]) > amplitude)
                {
                    amplitude = fabs(newData.y[i]);
                }
            }
            CustomSignal customSignal(amplitude, mInitialTimeSec, mDurationSec, newData);
            return customSignal;
        }
        throw std::runtime_error("incorrect signals multiplied");
    }

    CustomSignal Signal::operator-(const Signal& signal) const
    {
        if (signal.mSamplingFrequency == mSamplingFrequency && signal.initialTime() == mInitialTimeSec && signal.duration() == mDurationSec)
        {
            SignalData newData;
            const auto data1 = data();
            const auto data2 = signal.data();
            double amplitude = 0;
            for (int i = 0; i < data1.x.size(); i++)
            {
                newData.x.push_back(data1.x[i]);
                newData.y.push_back(data1.y[i] - data2.y[i]);
                if (fabs(newData.y[i]) > amplitude)
                {
                    amplitude = fabs(newData.y[i]);
                }
            }
            CustomSignal customSignal(amplitude, mInitialTimeSec, mDurationSec, newData);
            return customSignal;
        }
        throw std::runtime_error("incorrect signals multiplied");
    }

    CustomSignal Signal::operator+(const Signal& signal) const
    {
        if (signal.mSamplingFrequency == mSamplingFrequency && signal.initialTime() == mInitialTimeSec && signal.duration() == mDurationSec)
        {
            SignalData newData;
            const auto data1 = data();
            const auto data2 = signal.data();
            double amplitude = 0;
            for (int i = 0; i < data1.x.size(); i++)
            {
                newData.x.push_back(data1.x[i]);
                newData.y.push_back(data1.y[i] + data2.y[i]);
                if (fabs(newData.y[i]) > amplitude)
                {
                    amplitude = fabs(newData.y[i]);
                }
            }
            CustomSignal customSignal(amplitude, mInitialTimeSec, mDurationSec, newData);
            return customSignal;
        }
        throw std::runtime_error("incorrect signals multiplied");
    }

    CustomSignal Signal::operator/(const Signal& signal) const
    {
        if (signal.mSamplingFrequency == mSamplingFrequency && signal.initialTime() == mInitialTimeSec && signal.duration() == mDurationSec)
        {
            SignalData newData;
            const auto data1 = data();
            const auto data2 = signal.data();
            double amplitude = 0;
            for (int i = 0; i < data1.x.size(); i++)
            {
                newData.x.push_back(data1.x[i]);
                newData.y.push_back(data1.y[i] / data2.y[i]);
                if (fabs(newData.y[i]) > amplitude)
                {
                    amplitude = fabs(newData.y[i]);
                }
            }
            CustomSignal customSignal(amplitude, mInitialTimeSec, mDurationSec, newData);
            return customSignal;
        }
        throw std::runtime_error("incorrect signals multiplied");
    }
}