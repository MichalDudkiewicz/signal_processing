#ifndef SIGNAL_PROCESSING_RECTANGULAR_SIGNAL_HPP
#define SIGNAL_PROCESSING_RECTANGULAR_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class RectangularSignal : public Signal {
    public:
        RectangularSignal(double amplitude, int initialTimeSec, int durationSec, double period, double kw);

    public:
        double value(double x) const override;

    protected:
        double mPeriod;
        double mKw;
    };
}

#endif //SIGNAL_PROCESSING_RECTANGULAR_SIGNAL_HPP
