#ifndef SIGNAL_PROCESSING_PERIODIC_SIGNAL_HPP
#define SIGNAL_PROCESSING_PERIODIC_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class PeriodicSignal : public Signal {
    public:
        PeriodicSignal(double amplitude, double initialTimeSec, double durationSec, double periodSec);

    public:
        double period() const;

    protected:
        double mPeriod;
    };
}

#endif //SIGNAL_PROCESSING_PERIODIC_SIGNAL_HPP
