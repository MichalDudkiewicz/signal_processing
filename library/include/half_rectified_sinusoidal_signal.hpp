#ifndef SIGNAL_PROCESSING_HALF_RECTIFIED_SINUSOIDAL_SIGNAL_HPP
#define SIGNAL_PROCESSING_HALF_RECTIFIED_SINUSOIDAL_SIGNAL_HPP

#include "periodic_signal.hpp"

namespace cps {
    class HalfRectifiedSinusoidalSignal : public PeriodicSignal {
    public:
        HalfRectifiedSinusoidalSignal(double amplitude, int initialTimeSec, int durationSec, double period);

    public:
        double value(double x) const override;
    };
}

#endif //SIGNAL_PROCESSING_HALF_RECTIFIED_SINUSOIDAL_SIGNAL_HPP
