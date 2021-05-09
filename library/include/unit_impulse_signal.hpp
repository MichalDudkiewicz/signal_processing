#ifndef SIGNAL_PROCESSING_UNIT_IMPULSE_SIGNAL_HPP
#define SIGNAL_PROCESSING_UNIT_IMPULSE_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class UnitImpulseSignal : public Signal {
    public:
        UnitImpulseSignal(int initialTimeSec, int durationSec,
                          int impulseSampleNumber, int samplingFrequency);

    public:
        double value(double x) const override;

    private:
        int mSamplingFrequency;
        double mImpulseSampleX;
    };
}

#endif //SIGNAL_PROCESSING_UNIT_IMPULSE_SIGNAL_HPP
