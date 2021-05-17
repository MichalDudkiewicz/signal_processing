#include "signal_sampler.hpp"
#include "signal.hpp"
#include "utils.hpp"

namespace cps {

    cps::SignalSampler::SignalSampler(int samplingFrequency)
    : mSamplingFrequency(samplingFrequency) {

    }

    SignalData SignalSampler::sample(Signal& signal) const {
        double x = signal.initialTime();
        double xEnd = x + signal.duration();

        const double samplesNumber = signal.duration() * mSamplingFrequency;
        const double sampleDeltaTime = signal.duration() / (double)samplesNumber;
        SignalData sampledSignal;
        while (x <= xEnd)
        {
            sampledSignal.x.push_back(x);
            double y = signal.value(x);
            y = roundTo5(y);
            sampledSignal.y.push_back(y);
            x += sampleDeltaTime;
        }
        return sampledSignal;
    }

}