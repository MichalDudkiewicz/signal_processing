#ifndef SIGNAL_PROCESSING_EXTRAPOLATOR_HPP
#define SIGNAL_PROCESSING_EXTRAPOLATOR_HPP

#include "custom_signal.hpp"
#include "discreet_signal.hpp"
#include "quantizer.hpp"
#include <memory>
#include <algorithm>

namespace cps {
    class Extrapolator {
    private:
        Extrapolator() = default;

    public:
        template <std::size_t bitResolution>
        static std::shared_ptr<CustomSignal> extrapolate(QuantizedSignalData<bitResolution> quantizedSignalData, double minValue, double maxValue);

        template <std::size_t bitResolution>
        static SignalData extrapolateDiscreet(QuantizedSignalData<bitResolution> quantizedSignalData, double minValue, double maxValue);
    };

    double bitsetToValue(unsigned long intervalNumber, unsigned int numberOfIntervals, double minValue, double maxValue)
    {
        const double deltaY = (maxValue - minValue) / numberOfIntervals;

        const double value = minValue + intervalNumber * deltaY;

        return value;
    }

    template<std::size_t bitResolution>
    std::shared_ptr<CustomSignal> Extrapolator::extrapolate(QuantizedSignalData<bitResolution> quantizedSignalData, double minValue, double maxValue) {
        const double amplitude = std::max(fabs(minValue), fabs(maxValue));
        const double initialTime = quantizedSignalData.x.front();
        const double duration = quantizedSignalData.x.back() - initialTime;
        const unsigned int numberOfIntervals = pow(2, bitResolution);

        SignalData signalData;
        double x1 = quantizedSignalData.x.front();
        unsigned long intervalNumber = quantizedSignalData.y.front().to_ulong();
        double y1 = bitsetToValue(intervalNumber, numberOfIntervals, minValue, maxValue);
        signalData.x.push_back(x1);
        signalData.y.push_back(y1);
        for(int i = 1; i < quantizedSignalData.y.size(); i++)
        {
            x1 = quantizedSignalData.x[i];
            signalData.x.push_back(x1);
            signalData.y.push_back(y1);
            intervalNumber = quantizedSignalData.y[i].to_ulong();
            y1 = bitsetToValue(intervalNumber, numberOfIntervals, minValue, maxValue);
            signalData.x.push_back(x1);
            signalData.y.push_back(y1);
        }

        return std::make_shared<CustomSignal>(amplitude, initialTime, duration, signalData);
    }

    template <std::size_t bitResolution>
    SignalData Extrapolator::extrapolateDiscreet(QuantizedSignalData<bitResolution> quantizedSignalData, double minValue, double maxValue)
    {
        const double amplitude = std::max(fabs(minValue), fabs(maxValue));
        const double initialTime = quantizedSignalData.x.front();
        const double duration = quantizedSignalData.x.back() - initialTime;
        const unsigned int numberOfIntervals = pow(2, bitResolution);

        SignalData signalData;
        for(int i = 0; i < quantizedSignalData.y.size(); i++)
        {
            const double x1 = quantizedSignalData.x[i];
            const unsigned long intervalNumber = quantizedSignalData.y[i].to_ulong();
            const double y1 = bitsetToValue(intervalNumber, numberOfIntervals, minValue, maxValue);
            signalData.x.push_back(x1);
            signalData.y.push_back(y1);
        }

        return signalData;
    }
}

#endif //SIGNAL_PROCESSING_EXTRAPOLATOR_HPP
