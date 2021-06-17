#include "complex_signals_processor.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace cps {

    ComplexSignalData ComplexSignalsProcessor::processAmplitudeData(const TransformationResult &result) {
        const unsigned int M = result.result.size();

        ComplexSignalData complexSignalData;
        complexSignalData.frequency.reserve(M);
        complexSignalData.realValues.reserve(M);
        complexSignalData.imaginValues.reserve(M);

        for (int m = 0; m < M; m++)
        {
            complexSignalData.frequency.push_back(m * result.f0);
            complexSignalData.realValues.push_back(result.result[m].first);
            complexSignalData.imaginValues.push_back(result.result[m].second);
        }

        return complexSignalData;
    }

    ComplexSignalData ComplexSignalsProcessor::processComplexFactorsData(const TransformationResult &result) {
        const unsigned int M = result.result.size();

        ComplexSignalData complexSignalData;
        complexSignalData.frequency.reserve(M);
        complexSignalData.realValues.reserve(M);
        complexSignalData.imaginValues.reserve(M);

        for (int m = 0; m < M; m++)
        {
            complexSignalData.frequency.push_back(m * result.f0);
            const double real = result.result[m].first;
            const double imag = result.result[m].second;
            complexSignalData.realValues.push_back(sqrt(pow(real, 2) + pow(imag, 2)));
            if (real == 0)
            {
                throw std::runtime_error("error");
            }
            complexSignalData.imaginValues.push_back(atan(imag/real));
        }

        return complexSignalData;
    }
}