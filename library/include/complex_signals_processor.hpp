#ifndef SIGNAL_PROCESSING_COMPLEX_SIGNALS_PROCESSOR_HPP
#define SIGNAL_PROCESSING_COMPLEX_SIGNALS_PROCESSOR_HPP

#include "discreet_fourier_transform.hpp"

struct ComplexSignalData
{
    std::vector<double> frequency;
    std::vector<double> realValues;
    std::vector<double> imaginValues;
};

namespace cps {
    class ComplexSignalsProcessor {
    private:
        ComplexSignalsProcessor() = default;

    public:
        static ComplexSignalData processAmplitudeData(const TransformationResult& result);

        static ComplexSignalData processComplexFactorsData(const TransformationResult& result);
    };
}

#endif //SIGNAL_PROCESSING_COMPLEX_SIGNALS_PROCESSOR_HPP
