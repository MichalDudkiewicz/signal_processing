#ifndef SIGNAL_PROCESSING_UNIT_IMPULSE_SIGNAL_HPP
#define SIGNAL_PROCESSING_UNIT_IMPULSE_SIGNAL_HPP

#include "discreet_signal.hpp"

namespace cps {
    class UnitImpulseSignal : public DiscreetSignal {
    public:
        UnitImpulseSignal(double initialTimeSec, double durationSec,
                          int impulseSampleNumber, int samplingFrequency);

    public:
        double value(double x) override;

    private:
        double mImpulseSampleX;
    };
}

#endif //SIGNAL_PROCESSING_UNIT_IMPULSE_SIGNAL_HPP
