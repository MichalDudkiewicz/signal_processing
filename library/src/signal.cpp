#include "signal.hpp"
#include "signal_sampler.hpp"
#include <cmath>
#include <sstream>
#include "custom_signal.hpp"
#include "utils.hpp"

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

    SignalData Signal::data()
    {
        SignalSampler signalSampler(mSamplingFrequency);
        return signalSampler.sample(*this);
    }

    double Signal::mean() {
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < data.x.size(); i++) {
            sum += data.y[i];
        }
        return roundTo5(sum / size);
    }

    double Signal::absMean() {
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < size; i++) {
            sum += fabs(data.y[i]);
        }
        return roundTo5(sum / size);
    }

    double Signal::rms() {
        return roundTo5(sqrt(meanPower()));
    }

    double Signal::variance() {
        double mean = Signal::mean();
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < size; i++) {
            sum += pow(data.y[i] - mean, 2.0);
        }
        return roundTo5(sum / size);
    }

    double Signal::meanPower() {
        double sum = 0;
        const auto data = Signal::data();
        const unsigned int size = data.x.size();
        for (int i = 0; i < data.x.size(); i++) {
            sum += pow(data.y[i], 2.0);
        }
        return roundTo5(sum / size);
    }

    void Signal::setSamplingFrequency(int samplingFrequency) {
        mSamplingFrequency = samplingFrequency;
    }

    CustomSignal Signal::operator*(Signal& signal)
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

    CustomSignal Signal::operator-(Signal& signal)
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
        throw std::runtime_error("incorrect signals substracted");
    }

    CustomSignal Signal::operator+(Signal& signal)
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
        throw std::runtime_error("incorrect signals added");
    }

    CustomSignal Signal::operator/(Signal& signal)
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
        throw std::runtime_error("incorrect signals divided");
    }

    void Signal::serialize(std::ostream &stream) {
        stream.write(reinterpret_cast<const char*>(&mInitialTimeSec), sizeof mInitialTimeSec);
        stream.write(reinterpret_cast<const char*>(&mSamplingFrequency), sizeof mSamplingFrequency);
        const auto dataY = data().y;
        const auto size = dataY.size();
        stream.write(reinterpret_cast<const char*>(&size), sizeof size);
        for (const auto& y : dataY)
        {
            stream.write(reinterpret_cast<const char*>(&y), sizeof y);
        }
    }

    std::ostream &operator<<(std::ostream &os, Signal &signal) {
        const auto data = signal.data();
        os << "Initial time: " << signal.mInitialTimeSec << '\n'
        << "Sampling frequency: " << signal.mSamplingFrequency << '\n'
        << "Number of samples: " << data.y.size() - 1 << '\n';
        os << "Samples: " << '\n';
        for (const auto& y : data.y)
        {
            os << y << '\n';
        }
        return os;
    }

    HistogramData Signal::histogramData(unsigned int numberOfIntervals) {
        const auto dataCopy = data();
        const double min = minValue();
        const double max = maxValue();
        const double deltaY = (max - min) / numberOfIntervals;
        double y = min;
        HistogramData histogramData;
        while (y < max)
        {
            const double yEnd = y + deltaY;
            histogramData.intervals.emplace_back(y, yEnd);
            unsigned int occurrences = 0;
            for (const auto& signalY : dataCopy.y)
            {
                if (signalY >= y && signalY < yEnd)
                {
                    occurrences += 1;
                }
            }
            histogramData.occurrences.push_back(occurrences);
            y = yEnd;
        }
        histogramData.occurrences.back() += 1;
        return histogramData;
    }

    double Signal::maxValue() {
        const auto dataCopy = data();
        double max = dataCopy.y.front();
        for (int i = 1; i<=dataCopy.y.size(); i++)
        {
            const double y = dataCopy.y[i];
            if (y > max)
            {
                max = y;
            }
        }
        return max;
    }

    double Signal::minValue() {
        const auto dataCopy = data();
        double min = dataCopy.y.front();
        for (int i = 1; i<=dataCopy.y.size(); i++)
        {
            const double y = dataCopy.y[i];
            if (y < min)
            {
                min = y;
            }
        }
        return min;
    }

    std::string Signal::stringProperties() {
        std::ostringstream os;
        os << "mean value: " << mean() << '\n'
        << "abs mean value: " << absMean() << '\n'
        << "rms: " << rms() << '\n'
        << "variance: " << variance() << '\n'
        << "mean power: " << meanPower() << '\n';
        return os.str();
    }

    double Signal::amplitude() const {
        return mAmplitude;
    }
}