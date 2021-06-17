#ifndef SIGNAL_PROCESSING_DISCREET_FOURIER_TRANSFORM_HPP
#define SIGNAL_PROCESSING_DISCREET_FOURIER_TRANSFORM_HPP

#include <vector>
#include "signal_sampler.hpp"

/*
 * First part is realis, second is imaginaris
 */
using ComplexNumber = std::pair<double, double>;

namespace cps {
    struct TransformationResult
    {
        std::vector<ComplexNumber> result;
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
