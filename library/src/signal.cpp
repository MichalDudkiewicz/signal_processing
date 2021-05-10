#include "signal.hpp"
#include "signal_sampler.hpp"
#include <cmath>

namespace cps {

    Signal::Signal(double amplitude, int initialTimeSec, int durationSec)
    : mAmplitude(amplitude), mInitialTimeSec(initialTimeSec), mDurationSec(durationSec)
    {
    }

    int Signal::duration() const {
        return mDurationSec;
    }

    int Signal::initialTime() const {
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

    }
}