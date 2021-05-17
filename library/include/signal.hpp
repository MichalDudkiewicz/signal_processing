#ifndef SIGNAL_PROCESSING_SIGNAL_HPP
#define SIGNAL_PROCESSING_SIGNAL_HPP

#include "signal_sampler.hpp"
#include <memory>
#include <ostream>
#include <vector>

namespace cps
{
    class CustomSignal;

    struct HistogramData
    {
        std::vector<std::pair<double, double>> intervals;

        std::vector<unsigned int> occurrences;
    };

    class Signal
    {
    public:
        virtual ~Signal() = default;

        Signal(double amplitude, double initialTimeSec, double durationSec);

    public:
        virtual double value(double x) = 0;

        double duration() const;

        double initialTime() const;

        double amplitude() const;

        virtual SignalData data();

        HistogramData histogramData(unsigned int numberOfIntervals);

        double meanPower();

        double variance();

        double absMean();

        double mean();

        double rms();

        void setSamplingFrequency(int samplingFrequency);

        CustomSignal operator*(Signal& signal);

        CustomSignal operator/(Signal& signal);

        CustomSignal operator+(Signal& signal);

        CustomSignal operator-(Signal& signal);

        void serialize(std::ostream &stream);

        std::string stringProperties();

        friend std::ostream& operator<<(std::ostream& os, Signal& signal);

    private:
        double maxValue();

        double minValue();

    protected:
        double mAmplitude;
        double mInitialTimeSec;
        double mDurationSec;
        int mSamplingFrequency = 16;
    };
}

#endif //SIGNAL_PROCESSING_SIGNAL_HPP
