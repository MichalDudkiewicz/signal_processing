#ifndef SIGNAL_PROCESSING_DISCREET_FOURIER_TRANSFORM_HPP
#define SIGNAL_PROCESSING_DISCREET_FOURIER_TRANSFORM_HPP

#include <vector>
#include "signal_sampler.hpp"
#include <complex>

namespace cps {
    struct TransformationResult
    {
        std::vector<std::complex<double>> result;
        double f0;
    };

    class DiscreetFourierTransform {

    private:
        DiscreetFourierTransform() = default;

    public:
        static TransformationResult transform(const SignalData& signalData);
    };
}

#endif //SIGNAL_PROCESSING_DISCREET_FOURIER_TRANSFORM_HPP
