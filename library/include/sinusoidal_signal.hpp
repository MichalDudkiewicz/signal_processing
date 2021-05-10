#ifndef SIGNAL_PROCESSING_SINUSOIDAL_SIGNAL_HPP
#define SIGNAL_PROCESSING_SINUSOIDAL_SIGNAL_HPP

#include "periodic_signal.hpp"

namespace cps {
    class SinusoidalSignal : public PeriodicSignal {
    public:
        SinusoidalSignal(double amplitude, int initialTimeSec, int durationSec, double period);

        double value(double x) const override;
    };
}

#endif //SIGNAL_PROCESSING_SINUSOIDAL_SIGNAL_HPP
