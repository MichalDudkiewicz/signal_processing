#include "quantized_signal.hpp"
#include <cmath>

namespace cps {

    QuantizedSignal::QuantizedSignal(const SignalData &signalData) : Signal(0, signalData.x.front(), signalData.x.back() - signalData.x.front()),
                                                                     mSignalData(signalData) {

    }

    double QuantizedSignal::value(double x) {
        int numberOfSamples = mSignalData.x.size();
        double step = mDurationSec / (numberOfSamples - 1);
        int indexCounter = 0;
        int nearestSampleIndex = 0;
        for (const auto& x2 : mSignalData.x)
        {
            if (x >= x2 - step/2 - 0.00001 && x < x2 + step/2)
            {
                nearestSampleIndex = indexCounter;
                break;
            }
            indexCounter++;
        }
        return mSignalData.y[nearestSampleIndex];
    }
}