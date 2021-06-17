#include "discreet_fourier_transform.hpp"
#include <cmath>

namespace cps {

    TransformationResult DiscreetFourierTransform::transform(const SignalData &signalData) {
        const unsigned int N = signalData.x.size();

        double deltaT = signalData.x[1] - signalData.x[0];
        double f0 = 1 / (deltaT * N);

        TransformationResult result;
        result.result.reserve(N);
        result.f0 = f0;

        for(unsigned int k = 0; k < N; k++)
        {
            double imSum = 0;
            double reSum = 0;
            for(unsigned int n = 0; n < N; n++)
            {
                double b = -(2 * M_PI * k * n) / N;
                imSum += signalData.y[n] * sin(b);
                reSum += signalData.y[n] * cos(b);
            }
            result.result.emplace_back(reSum/N, imSum/N);
        }

        return result;
    }
}