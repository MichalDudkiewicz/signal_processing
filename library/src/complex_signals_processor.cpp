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
            complexSignalData.realValues.push_back(result.result[m].real());
            complexSignalData.imaginValues.push_back(result.result[m].imag());
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
            const double real = result.result[m].real();
            const double imag = result.result[m].imag();
            const double modZ = sqrt(pow(real, 2) + pow(imag, 2));
            complexSignalData.realValues.push_back(modZ);
//            double argZ = 0;
//            if (modZ != 0)
//            {
//                argZ = asin(imag/modZ);
//            }
            double argZ = arg(result.result[m]);
            complexSignalData.imaginValues.push_back(argZ);
        }

        return complexSignalData;
    }
}