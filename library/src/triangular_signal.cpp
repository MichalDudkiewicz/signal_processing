#include "triangular_signal.hpp"
#include <cmath>

namespace cps {

    TriangularSignal::TriangularSignal(double amplitude, double initialTimeSec, double durationSec, double period, double kw)
            : RectangularSignal(amplitude, initialTimeSec, durationSec, period, kw) {

    }

    double TriangularSignal::value(double x) {
        const double termPosition = ((x - mInitialTimeSec) / mPeriod) - floor((x - mInitialTimeSec) / mPeriod);
        if (termPosition < mKw)
        {
            return termPosition / mKw * mAmplitude;
        }
        else
        {
            return (1 - (termPosition - mKw) / (1 - mKw)) * mAmplitude;
        }
    }
}