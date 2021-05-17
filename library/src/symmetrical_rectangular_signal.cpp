#include "symmetrical_rectangular_signal.hpp"

namespace cps {
    SymmetricalRectangularSignal::SymmetricalRectangularSignal(double amplitude, double initialTimeSec, double durationSec, double period, double kw)
    : RectangularSignal(amplitude, initialTimeSec, durationSec, period, kw)
    {

    }

    double SymmetricalRectangularSignal::value(double x) {
        return RectangularSignal::value(x) == 0 ? -mAmplitude : mAmplitude;
    }

}