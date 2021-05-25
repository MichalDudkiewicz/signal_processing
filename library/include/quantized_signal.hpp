#ifndef SIGNAL_PROCESSING_QUANTIZED_SIGNAL_HPP
#define SIGNAL_PROCESSING_QUANTIZED_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class QuantizedSignal : public Signal {
    public:
        explicit QuantizedSignal(const SignalData& signalData);

    public:
        double value(double x) override;

    private:
        SignalData mSignalData;
    };
}

#endif //SIGNAL_PROCESSING_QUANTIZED_SIGNAL_HPP
