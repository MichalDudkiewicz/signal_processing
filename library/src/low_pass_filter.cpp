#include "low_pass_filter.hpp"
#include "custom_signal.hpp"
#include <utility>
#include <cmath>

namespace cps {

    LowPassFilter::LowPassFilter(int M, double fo, std::shared_ptr<Window> window) : Filter(M, fo, std::move(window)) {

    }

    std::shared_ptr<CustomSignal> LowPassFilter::filter(const std::shared_ptr<Signal> &signalToFilter) const {
        const double sampleFreq = signalToFilter->samplingFrequency();
        const double initialTime = signalToFilter->initialTime();
        const double duration = signalToFilter->duration();
        const double K = sampleFreq / mFo;
        SignalData newData;
        const auto data = signalToFilter->data();
        const int numberOfSamples = data.x.size();

        int c = (mM - 1) / 2; /* center sample */

        double amplitude = 0;

        for (int i = 0; i < numberOfSamples; i++)
        {
            newData.x.push_back(data.x[i]);

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
        }

        return std::make_shared<CustomSignal>(amplitude, initialTime, duration, newData);
    }

    int LowPassFilter::s(int n) const {
        return 1;
    }
}