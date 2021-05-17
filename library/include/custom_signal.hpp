#ifndef SIGNAL_PROCESSING_CUSTOM_SIGNAL_HPP
#define SIGNAL_PROCESSING_CUSTOM_SIGNAL_HPP

#include "signal.hpp"
#include "signal_sampler.hpp"
#include <istream>

namespace cps {
    class CustomSignal : public Signal {
    public:
        explicit CustomSignal(double amplitude, double initialTimeSec, double durationSec, SignalData data);

        CustomSignal();

    public:
        double value(double x) override;

        SignalData data() override;

        void unserialize(std::istream& istr);

    private:
        SignalData mData;
    };
}

#endif //SIGNAL_PROCESSING_CUSTOM_SIGNAL_HPP
