#ifndef SIGNAL_PROCESSING_RECTIFIED_SINUSOIDAL_SIGNAL_HPP
#define SIGNAL_PROCESSING_RECTIFIED_SINUSOIDAL_SIGNAL_HPP

#include "sinusoidal_signal.hpp"

namespace cps {
    class RectifiedSinusoidalSignal : public SinusoidalSignal {
    public:
        RectifiedSinusoidalSignal(double amplitude, int initialTimeSec, int durationSec, double period);

    public:
        double value(double x) const override;
    };
}

#endif //SIGNAL_PROCESSING_RECTIFIED_SINUSOIDAL_SIGNAL_HPP
