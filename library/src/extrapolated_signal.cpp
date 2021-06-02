#include "extrapolated_signal.hpp"

namespace cps {

    ExtrapolatedSignal::ExtrapolatedSignal(const SignalData &signalData) : Signal(0, signalData.x.front(), signalData.x.back() - signalData.x.front()) {
        mSignalData = signalData;
    }

    double ExtrapolatedSignal::value(double x) {
        for (auto i = mSignalData.x.size() - 1; i > 0; i--)
        {
            if (x > mSignalData.x[i] - 0.0000001)
            {
                return mSignalData.y[i];
            }
        }
        return mSignalData.y.front();
    }
}