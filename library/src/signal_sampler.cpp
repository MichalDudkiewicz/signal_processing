#include "signal_sampler.hpp"

namespace cps {

    cps::SignalSampler::SignalSampler(int samplingFrequency)
    : mSamplingFrequency(samplingFrequency) {

    }

    SampledSignal SignalSampler::sample(const Signal &signal) const {
        double x = signal.initialTime();
        const double xEnd = x + signal.duration();
        const int samplesNumber = signal.duration() * mSamplingFrequency;
        const double sampleDeltaTime = (double)signal.duration() / (double)samplesNumber;
        SampledSignal sampledSignal;
        while (x <= xEnd)
        {
            sampledSignal.x.push_back(x);
            const double y = signal.value(x);
            sampledSignal.y.push_back(y);
            x += sampleDeltaTime;
        }
        return sampledSignal;
    }

}