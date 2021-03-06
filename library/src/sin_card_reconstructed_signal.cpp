#include "sin_card_reconstructed_signal.hpp"
#include <cmath>

namespace cps {
    double sinc(double t) {
        if (fabs(t) < 0.00001) {
            return 1.0;
        } else {
            return sin(M_PI * t) / (M_PI * t);
        }
    }

    SinCardReconstructedSignal::SinCardReconstructedSignal(SignalData signalData, int numberOfNeigbourSamples) : Signal(0, signalData.x.front(), signalData.x.back() - signalData.x.front()) {
        mSignalData = signalData;
        mNumberOfNeigbourSamples = numberOfNeigbourSamples;
    }

    double SinCardReconstructedSignal::value(double x) {
        int numberOfSamples = mSignalData.x.size();

        double step = mDurationSec / (numberOfSamples - 1);
        double sum = 0.0;

        int nearestSampleIndex = 0;
        int indexCounter = 0;
        for (const auto& x2 : mSignalData.x)
        {
            if (x >= x2 - step/2 && x < x2 + step/2)
            {
                nearestSampleIndex = indexCounter;
                break;
            }
            indexCounter++;
        }

        int startIndex = nearestSampleIndex - mNumberOfNeigbourSamples/2;
        startIndex = std::max(startIndex, 0);
        int endIndex = startIndex + mNumberOfNeigbourSamples;
        endIndex = std::min(endIndex, numberOfSamples - 1);

        for (int i = startIndex; i <= endIndex; i++) {
            sum += mSignalData.y[i] * sinc((x - mSignalData.x[i])/step);
        }

        return sum;
    }
}