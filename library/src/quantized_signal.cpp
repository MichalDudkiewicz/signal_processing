#include "quantized_signal.hpp"
#include <cmath>

namespace cps {

    QuantizedSignal::QuantizedSignal(const SignalData &signalData) : Signal(0, signalData.x.front(), signalData.x.back() - signalData.x.front()),
                                                                     mSignalData(signalData) {

    }

    double QuantizedSignal::value(double x) {
        int index = (int) floor((x - mInitialTimeSec) / mDurationSec * mSignalData.x.size());
        return mSignalData.y[index];
    }
}