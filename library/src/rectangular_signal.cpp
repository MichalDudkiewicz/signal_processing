#include "rectangular_signal.hpp"
#include <cmath>

namespace cps {

    RectangularSignal::RectangularSignal(double amplitude, int initialTimeSec, int durationSec, double period,
                                         double kw)
                                         : Signal(amplitude, initialTimeSec, durationSec), mPeriod(period), mKw(kw) {

    }

    double RectangularSignal::value(double x) const {
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