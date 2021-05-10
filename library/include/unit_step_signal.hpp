#ifndef SIGNAL_PROCESSING_UNIT_STEP_SIGNAL_HPP
#define SIGNAL_PROCESSING_UNIT_STEP_SIGNAL_HPP

#include "signal.hpp"

namespace cps {
    class UnitStepSignal : public Signal {
    public:
        UnitStepSignal(double amplitude, int initialTimeSec, int durationSec, int stepTimeSec);

    public:
        double value(double x) const override;

    private:
        int mStepTimeSec;
    };
}

#endif //SIGNAL_PROCESSING_UNIT_STEP_SIGNAL_HPP