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

        Signal(double amplitude, int initialTimeSec, int durationSec);

    public:
        virtual double value(double x) const = 0;

        int duration() const;

        int initialTime() const;

        SignalData data(int samplingFrequency) const;

    protected:
        double mAmplitude;
        int mInitialTimeSec;
        int mDurationSec;
    };
}

#endif //SIGNAL_PROCESSING_SIGNAL_HPP
