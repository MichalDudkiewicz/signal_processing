#ifndef SIGNAL_PROCESSING_CUSTOM_SIGNAL_HPP
#define SIGNAL_PROCESSING_CUSTOM_SIGNAL_HPP

#include "signal.hpp"
#include "signal_sampler.hpp"

namespace cps {
    class CustomSignal : public Signal {
    public:
        explicit CustomSignal(double amplitude, double initialTimeSec, double durationSec, SignalData data);

    public:
        double value(double x) const override;

        SignalData data() const override;

    private:
        SignalData mData;
    };
}

#endif //SIGNAL_PROCESSING_CUSTOM_SIGNAL_HPP
