#include "custom_signal.hpp"
#include <stdexcept>
#include <utility>

namespace cps {

    double CustomSignal::value(double x) const {
        for (int i = 0; i<mData.x.size(); i++)
        {
            if (mData.x[i] == x)
            {
                return mData.y[i];
            }
        }
        throw std::runtime_error("out of range");
    }

    SignalData CustomSignal::data() const {
        return mData;
    }

    CustomSignal::CustomSignal(double amplitude, double initialTimeSec, double durationSec, SignalData data)
    : Signal(amplitude, initialTimeSec, durationSec), mData(std::move(data)) {

    }
}