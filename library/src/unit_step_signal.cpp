#include "unit_step_signal.hpp"

namespace cps {

    double UnitStepSignal::value(double x) const {
        if (x > mStepTimeSec)
        {
            return mAmplitude;
        }
        else if (x == mStepTimeSec)
        {
            return mAmplitude / 2;
        }
        else
        {
            return 0;
        }
    }

    UnitStepSignal::UnitStepSignal(double amplitude, int initialTimeSec, int durationSec, int stepTimeSec)
    : Signal(amplitude, initialTimeSec, durationSec), mStepTimeSec(stepTimeSec)
    {

    }
}