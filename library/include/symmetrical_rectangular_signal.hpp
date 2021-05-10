#ifndef SIGNAL_PROCESSING_SYMMETRICAL_RECTANGULAR_SIGNAL_HPP
#define SIGNAL_PROCESSING_SYMMETRICAL_RECTANGULAR_SIGNAL_HPP

#include "rectangular_signal.hpp"

namespace cps {
    class SymmetricalRectangularSignal : public RectangularSignal {
    public:
        SymmetricalRectangularSignal(double amplitude, int initialTimeSec, int durationSec, double period, double kw);

    public:
        double value(double x) const override;

    };
}

#endif //SIGNAL_PROCESSING_SYMMETRICAL_RECTANGULAR_SIGNAL_HPP
