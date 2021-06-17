#include "discreet_fourier_transform.hpp"
#include <cmath>
#include <complex>

namespace cps {

    std::complex<double> wFactor(unsigned int m, unsigned int n, unsigned int N)
    {
        std::complex<double> complexNumber;
        const double fi = 2 * M_PI / N;
        complexNumber.real(cos(fi));
        complexNumber.imag(sin(fi));

        complexNumber = pow(complexNumber, -(m * n));

        return complexNumber;
    }

    TransformationResult DiscreetFourierTransform::transform(const SignalData &signalData) {
        const unsigned int N = signalData.x.size();

        double deltaT = signalData.x[1] - signalData.x[0];
        double f0 = 1 / (deltaT * N);

        TransformationResult result;
        result.result.reserve(N);
        result.f0 = f0;

//        for(unsigned int k = 0; k < N; k++)
//        {
//            double imSum = 0;
//            double reSum = 0;
//            for(unsigned int n = 0; n < N; n++)
//            {
//                double b = -(2 * M_PI * k * n) / N;
//                imSum += signalData.y[n] * sin(b);
//                reSum += signalData.y[n] * cos(b);
//            }
//            result.result.emplace_back(reSum/N, imSum/N);
//        }
//
//        return result;

        std::vector<std::vector<std::complex<double>>> dftMatrix;

        for (unsigned int m = 0; m < N; m++)
        {
            dftMatrix.emplace_back();
            dftMatrix[m].reserve(N);
            for (unsigned int n = 0; n < N; n++)
            {
                const auto complexFactor = wFactor(m, n, N);
                dftMatrix[m].push_back(complexFactor);
            }
        }

        for (unsigned int m = 0; m < N; m++)
        {
            std::complex<double> xm = 0;
            for (unsigned int n = 0; n < N; n++)
            {
                xm += dftMatrix[m][n] * signalData.y[n];
            }
            xm /= N;
            result.result.push_back(xm);
        }

        return result;
    }
}