#ifndef SIGNAL_PROCESSING_SINUSOIDAL_SIGNAL_HPP
#define SIGNAL_PROCESSING_SINUSOIDAL_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class SinusoidalSignal : public Signal {
    public:
        SinusoidalSignal(double amplitude, int initialTimeSec, int durationSec, double period);

        double value(double x) const override;

    protected:
        double mPeriod;
    };
}

#endif //SIGNAL_PROCESSING_SINUSOIDAL_SIGNAL_HPP
