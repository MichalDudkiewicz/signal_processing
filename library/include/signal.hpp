#ifndef SIGNAL_PROCESSING_SIGNAL_HPP
#define SIGNAL_PROCESSING_SIGNAL_HPP

#include "signal_sampler.hpp"
#include <memory>
#include <ostream>

namespace cps
{
    class CustomSignal;

    class Signal
    {
    public:
        virtual ~Signal() = default;

        Signal(double amplitude, double initialTimeSec, double durationSec);

    public:
        virtual double value(double x) const = 0;

        double duration() const;

        double initialTime() const;

        virtual SignalData data() const;

        double meanPower() const;

        double variance() const;

        double absMean() const;

        double mean() const;

        double rms() const;

        void setSamplingFrequency(int samplingFrequency);

        CustomSignal operator*(const Signal& signal) const;

        CustomSignal operator/(const Signal& signal) const;

        CustomSignal operator+(const Signal& signal) const;

        CustomSignal operator-(const Signal& signal) const;

        void serialize(std::ostream &stream) const;

        friend std::ostream& operator<<(std::ostream& os, const Signal& signal);

    protected:
        double mAmplitude;
        double mInitialTimeSec;
        double mDurationSec;
        int mSamplingFrequency = 16;
    };
}

#endif //SIGNAL_PROCESSING_SIGNAL_HPP
