#ifndef SIGNAL_PROCESSING_SIGNAL_HPP
#define SIGNAL_PROCESSING_SIGNAL_HPP

#include "signal_sampler.hpp"
#include <memory>

namespace cps
{
    class Signal
    {
    public:
        virtual ~Signal() = default;

        Signal(double amplitude, double initialTimeSec, double durationSec);

    public:
        virtual double value(double x) const = 0;

        int duration() const;

        int initialTime() const;

        SignalData data() const;

        double meanPower() const;

        double variance() const;

        double absMean() const;

        double mean() const;

        double rms() const;

        void setSamplingFrequency(int samplingFrequency);

    protected:
        double mAmplitude;
        double mInitialTimeSec;
        double mDurationSec;
        int mSamplingFrequency = 16;
    };
}

#endif //SIGNAL_PROCESSING_SIGNAL_HPP
