#include "signal_sampler.hpp"
#include "signal.hpp"
#include <cmath>
#include "periodic_signal.hpp"

namespace cps {

    cps::SignalSampler::SignalSampler(int samplingFrequency)
    : mSamplingFrequency(samplingFrequency) {

    }

    SignalData SignalSampler::sample(const Signal& signal) const {
        double x = signal.initialTime();
        double xEnd = x + signal.duration();

        if (const auto* periodicSignal = dynamic_cast<const PeriodicSignal*>(&signal))
        {
            const double period = periodicSignal->period();
            const int periodMultiplicity = floor(xEnd / period);
            xEnd = periodMultiplicity * period;
        }

        const int samplesNumber = signal.duration() * mSamplingFrequency;
        const double sampleDeltaTime = (double)signal.duration() / (double)samplesNumber;
        SignalData sampledSignal;
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