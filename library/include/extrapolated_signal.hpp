#ifndef SIGNAL_PROCESSING_EXTRAPOLATED_SIGNAL_HPP
#define SIGNAL_PROCESSING_EXTRAPOLATED_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class ExtrapolatedSignal : public Signal {
    public:
        ExtrapolatedSignal(const SignalData& signalData);

        double value(double x) override;
    private:
        SignalData mSignalData;
    };
}

#endif //SIGNAL_PROCESSING_EXTRAPOLATED_SIGNAL_HPP
