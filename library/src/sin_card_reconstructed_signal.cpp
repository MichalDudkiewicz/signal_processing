#include "sin_card_reconstructed_signal.hpp"
#include <cmath>

namespace cps {
    double sinc(double t) {
        if (t == 0.0) {
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
        double deltaX = mDurationSec / numberOfSamples;

        int index = 0;
        int neigbourIndex = 0;
        for (const auto& x2 : mSignalData.x)
        {
            if (x >= x2 - deltaX/2 && x <= x2 + deltaX/2)
            {
                neigbourIndex = index;
                break;
            }
            index++;
        }

        /* find range of N (or less) samples */
        int firstSample0 = neigbourIndex - mNumberOfNeigbourSamples / 2;
        int lastSample0 = firstSample0 + mNumberOfNeigbourSamples;

        int firstSample = std::max(0, firstSample0);
        if (firstSample0 < 0)
        {
            lastSample0 -= firstSample0;
        }
        int lastSample = std::min(numberOfSamples - 1, lastSample0);
        if(lastSample0 > numberOfSamples - 1)
        {
            int sample = firstSample - (lastSample0 - (numberOfSamples - 1));
            firstSample = std::max(0, sample);
        }

        double sum = 0.0;
        for (int i = firstSample; i <= lastSample; i++) {
            sum += mSignalData.y[i] * sinc(x / deltaX - i);
        }

        return sum;
    }
}