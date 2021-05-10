#ifndef SIGNAL_PROCESSING_TRIANGULAR_SIGNAL_HPP
#define SIGNAL_PROCESSING_TRIANGULAR_SIGNAL_HPP

#include "rectangular_signal.hpp"

namespace cps {
    class TriangularSignal : public RectangularSignal {
    public:
        TriangularSignal(double amplitude, double initialTimeSec, double durationSec, double period, double kw);

    public:
        double value(double x) const override;
    };
}

#endif //SIGNAL_PROCESSING_TRIANGULAR_SIGNAL_HPP
