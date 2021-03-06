#ifndef SIGNAL_PROCESSING_QUANTIZER_HPP
#define SIGNAL_PROCESSING_QUANTIZER_HPP

#include <bitset>
#include "signal.hpp"
#include <cmath>

namespace cps {

    template <size_t bitResolution>
    struct QuantizedSignalData
    {
        std::vector<double> x;

        std::vector<std::bitset<bitResolution>> y;
    };

    class Quantizer {
        Quantizer(size_t resolution);

        static const size_t mResolution;

    public:
        template <size_t bitResolution>
        static QuantizedSignalData<bitResolution> quantize(Signal& signal, int samplingFrequency);
    };

    template<size_t bitResolution>
    QuantizedSignalData<bitResolution> Quantizer::quantize(Signal &signal, int samplingFrequency) {
        signal.setSamplingFrequency(samplingFrequency);
        const auto signalData = signal.data();
        const double minVal = signal.minValue();
        const double maxVal = signal.maxValue();
        const double deltaY = (maxVal - minVal) / pow(2, bitResolution);

        QuantizedSignalData<bitResolution> quantizedSignalData;
        quantizedSignalData.x = signalData.x;

        for(const auto& y : signalData.y)
        {
            unsigned long intervalNumber = 0;
            for (double y2 = minVal; y2 < maxVal + 0.00001; y2 += deltaY)
            {
                if(y >= y2 - deltaY/2 && y < y2 + deltaY/2)
                {
                    if (intervalNumber >= pow(2, bitResolution))
                    {
                        quantizedSignalData.y.template emplace_back(intervalNumber - 1);
                        break;
                    }
                    quantizedSignalData.y.template emplace_back(intervalNumber);
                    break;
                }
                intervalNumber++;
            }
        }

        return quantizedSignalData;
    }

}

#endif //SIGNAL_PROCESSING_QUANTIZER_HPP
