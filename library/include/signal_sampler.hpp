#ifndef SIGNAL_PROCESSING_SIGNAL_SAMPLER_HPP
#define SIGNAL_PROCESSING_SIGNAL_SAMPLER_HPP

#include <vector>

namespace cps {
    class Signal;

    struct SignalData
    {
        std::vector<double> x;
        std::vector<double> y;
    };

    class SignalSampler {
    public:
        explicit SignalSampler(int samplingFrequency);

        SignalData sample(const Signal& signal) const;

    private:
        int mSamplingFrequency;
    };
}

#endif //SIGNAL_PROCESSING_SIGNAL_SAMPLER_HPP
