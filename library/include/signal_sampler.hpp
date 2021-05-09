#ifndef SIGNAL_PROCESSING_SIGNAL_SAMPLER_HPP
#define SIGNAL_PROCESSING_SIGNAL_SAMPLER_HPP

#include <vector>

#include "signal.hpp"

namespace cps {
    struct SampledSignal
    {
        std::vector<double> x;
        std::vector<double> y;
    };

    class SignalSampler {
    public:
        explicit SignalSampler(int samplingFrequency);

        SampledSignal sample(const Signal& signal) const;

    private:
        int mSamplingFrequency;
    };
}

#endif //SIGNAL_PROCESSING_SIGNAL_SAMPLER_HPP
