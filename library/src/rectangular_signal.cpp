#include "rectangular_signal.hpp"
#include <cmath>

namespace cps {

    RectangularSignal::RectangularSignal(double amplitude, double initialTimeSec, double durationSec, double period,
                                         double kw)
                                         : PeriodicSignal(amplitude, initialTimeSec, durationSec, period), mKw(kw) {

    }

    double RectangularSignal::value(double x) {
        if (((x - mInitialTimeSec) / mPeriod) - floor((x - mInitialTimeSec) / mPeriod) < mKw)
        {
            return mAmplitude;
        }
        else
        {
            return 0;
        }
    }
}