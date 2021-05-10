#ifndef SIGNAL_PROCESSING_RECTIFIED_SINUSOIDAL_SIGNAL_HPP
#define SIGNAL_PROCESSING_RECTIFIED_SINUSOIDAL_SIGNAL_HPP

#include "periodic_signal.hpp"

namespace cps {
    class RectifiedSinusoidalSignal : public PeriodicSignal {
    public:
        RectifiedSinusoidalSignal(double amplitude, double initialTimeSec, double durationSec, double period);

    public:
        double value(double x) const override;
    };
}

#endif //SIGNAL_PROCESSING_RECTIFIED_SINUSOIDAL_SIGNAL_HPP
