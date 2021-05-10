#ifndef SIGNAL_PROCESSING_RECTANGULAR_SIGNAL_HPP
#define SIGNAL_PROCESSING_RECTANGULAR_SIGNAL_HPP

#include "periodic_signal.hpp"

namespace cps {
    class RectangularSignal : public PeriodicSignal {
    public:
        RectangularSignal(double amplitude, double initialTimeSec, double durationSec, double period, double kw);

    public:
        double value(double x) const override;

    protected:
        double mKw;
    };
}

#endif //SIGNAL_PROCESSING_RECTANGULAR_SIGNAL_HPP
