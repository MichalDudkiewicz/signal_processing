#include "extrapolated_signal.hpp"

namespace cps {

    ExtrapolatedSignal::ExtrapolatedSignal(const SignalData &signalData) : Signal(0, signalData.x.front(), signalData.x.back() - signalData.x.front()) {
        mSignalData = signalData;
    }

    double ExtrapolatedSignal::value(double x) {
        for (int i = 0; i < mSignalData.x.size() - 1; i++)
        {
            if (x >= mSignalData.x[i] - 0.0000001 && x < mSignalData.x[i + 1] - 0.0000001)
            {
                return mSignalData.y[i];
            }
        }
        return mSignalData.y.back();
    }
}