#include "signal.hpp"
#include "signal_sampler.hpp"
#include <cmath>
#include <sstream>
#include "custom_signal.hpp"
#include "utils.hpp"

namespace cps {

    bool isEqual(double a, double b)
    {
        return fabs(a - b) < 0.00001;
    }

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

    std::shared_ptr<CustomSignal> Signal::operator*(Signal& signal)
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
            return std::make_shared<CustomSignal>(amplitude, mInitialTimeSec, mDurationSec, newData);
        }
        throw std::runtime_error("incorrect signals multiplied");
    }

    std::shared_ptr<CustomSignal> Signal::operator-(Signal& signal)
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
            return std::make_shared<CustomSignal>(amplitude, mInitialTimeSec, mDurationSec, newData);
        }
        throw std::runtime_error("incorrect signals substracted");
    }

    std::shared_ptr<CustomSignal> Signal::operator+(Signal& signal)
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
            return std::make_shared<CustomSignal>(amplitude, mInitialTimeSec, mDurationSec, newData);
        }
        throw std::runtime_error("incorrect signals added");
    }

    std::shared_ptr<CustomSignal> Signal::operator/(Signal& signal)
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
            return std::make_shared<CustomSignal>(amplitude, mInitialTimeSec, mDurationSec, newData);
        }
        throw std::runtime_error("incorrect signals divided");
    }

    std::shared_ptr<CustomSignal> Signal::convolute(Signal& signal)
    {
        if (signal.mSamplingFrequency == mSamplingFrequency)
        {
            SignalData newData;
            const auto h = data();
            const auto x = signal.data();
            double amplitude = 0;
            const double initialTime = std::min(mInitialTimeSec, signal.initialTime());
            const double endTime = std::max(mInitialTimeSec + mDurationSec, signal.initialTime() + signal.duration());
            const double duration = endTime - initialTime;
            const int M = h.x.size();
            const int N = x.x.size();
            const int numberOfSamples = M + N - 1;
            const double deltaX = h.x[1] - h.x[0];
            double currentX = initialTime;
            for (int i = 0; i < numberOfSamples; i++)
            {
                newData.x.push_back(currentX);

                double sum = 0.0;
                int startK = std::max(0, i - N + 1);
                int endK = std::min(M, i + 1);
                for (unsigned long k = startK; k < endK; k++) {
                    sum += h.y[k] * x.y[i - k];
                }
                newData.y.push_back(sum);

                if (fabs(newData.y[i]) > amplitude)
                {
                    amplitude = fabs(newData.y[i]);
                }
                currentX += deltaX;
            }
            return std::make_shared<CustomSignal>(amplitude, initialTime, duration, newData);
        }
        throw std::runtime_error("incorrect signals correlated");
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
        const double min = roundTo5(minValue());
        const double max = roundTo5(maxValue());
        const double deltaY = roundTo5((max - min) / numberOfIntervals);
        double y = min;
        HistogramData histogramData;
        unsigned int intervalNumber = 1;
        while (y < max - 0.00001)
        {
            const double yEnd = roundTo5(y + deltaY);
            histogramData.intervals.emplace_back(y, yEnd);
            unsigned int occurrences = 0;
            for (const auto& signalY : dataCopy.y)
            {
                if (signalY >= y && signalY < yEnd)
                {
                    occurrences += 1;
                }
                else if (intervalNumber == numberOfIntervals && signalY == yEnd)
                {
                    occurrences++;
                }
            }
            histogramData.occurrences.push_back(occurrences);
            y = yEnd;
            intervalNumber++;
        }
        return histogramData;
    }

    double Signal::maxValue() {
        const auto dataCopy = data();
        double max = dataCopy.y.front();
        for (int i = 1; i<dataCopy.y.size(); i++)
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
        for (int i = 1; i<dataCopy.y.size(); i++)
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

    int Signal::samplingFrequency() const {
        return mSamplingFrequency;
    }
}