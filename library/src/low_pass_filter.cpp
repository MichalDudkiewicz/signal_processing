#include "low_pass_filter.hpp"
#include "custom_signal.hpp"
#include <utility>
#include <cmath>
#include "high_pass_filter.hpp"

namespace cps {

    LowPassFilter::LowPassFilter(int M, double fo, std::shared_ptr<Window> window) : Filter(M, fo, std::move(window)) {

    }

    std::shared_ptr<CustomSignal> LowPassFilter::filter(const std::shared_ptr<Signal> &signalToFilter) {
        const int sampleFreq = signalToFilter->samplingFrequency();

//        if (dynamic_cast<HighPassFilter*>(this))
//        {
//            mFo = ((double)sampleFreq)/2 - mFo;
//        }

        const double initialTime = signalToFilter->initialTime();
        const double K = sampleFreq / mFo;
        SignalData newData;
        const auto data = signalToFilter->data();
        const int numberOfSamples = mM;

        int c = (mM - 1) / 2; /* center sample */

        double amplitude = 0;

        const double deltaX = data.x[1] - data.x[0];
        double x = 0;
        const double duration = (mM - 1) * deltaX;

        for (int i = 0; i < numberOfSamples; i++)
        {
            newData.x.push_back(x);

            double result;
            if (i == c) {
                result = 2.0 / K;
            } else {
                result = sin(2.0 * M_PI * (i - c) / K)
                         / (M_PI * (i - c));
            }
            result *= mWindow->value(i);

            result *= s(i);

            newData.y.push_back(result);
            if (fabs(newData.y[i]) > amplitude)
            {
                amplitude = fabs(newData.y[i]);
            }
            x += deltaX;
        }
        auto newSignal = std::make_shared<CustomSignal>(amplitude, initialTime, duration, newData);
        newSignal->setSamplingFrequency(sampleFreq);
        return newSignal;
    }

    int LowPassFilter::s(int n) const {
        return 1;
    }
}