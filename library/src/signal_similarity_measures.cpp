#include <stdexcept>
#include "signal_similarity_measures.hpp"
#include <cmath>
#include <cfloat>

namespace cps {
      double meanSquaredError(const SignalData& result, const SignalData& origin) {
        if (result.x.size() != origin.x.size()) {
            throw std::runtime_error("not same length");
        }

        double sum = 0.0;
        for (int i = 0; i < result.x.size(); i++) {
            sum += pow(result.y[i] - origin.y[i], 2.0);
        }

        return sum / result.x.size();
    }

      double signalToNoiseRatio(const SignalData& result, const SignalData& origin) {
        if (result.x.size() != origin.x.size()) {
            throw std::runtime_error("not same length");
        }

        double resultSquaredSum = 0.0;
        double diffSquaredSum = 0.0;
        for (int i = 0; i < result.x.size(); i++) {
            resultSquaredSum += pow(result.y[i], 2.0);
            diffSquaredSum += pow(result.y[i] - origin.y[i], 2.0);
        }

        return 10.0 * log10(resultSquaredSum / diffSquaredSum);
    }

      double peakSignalToNoiseRatio(const SignalData& result, const SignalData& origin) {
          if (result.x.size() != origin.x.size()) {
              throw std::runtime_error("not same length");
          }

        double resultMax = DBL_MIN;
        double diffSquaredSum = 0.0;
        for (int i = 0; i < result.x.size(); i++) {
            if (result.y[i] > resultMax) {
                resultMax = result.y[i];
            }
            diffSquaredSum += pow(result.y[i] - origin.y[i], 2.0);
        }

        return 10.0 * log10(resultMax / (diffSquaredSum / result.x.size()));
    }

      double maximumDifference(const SignalData& result, const SignalData& origin) {
          if (result.x.size() != origin.x.size()) {
              throw std::runtime_error("not same length");
          }

        double maxDiff = DBL_MIN;
        for (int i = 0; i < result.x.size(); i++) {
            double diff = fabs(result.y[i] - origin.y[i]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }

        return maxDiff;
    }

      double effectiveNumberOfBits(const SignalData& result, const SignalData& origin) {
        return (signalToNoiseRatio(result, origin) - 1.76) / 6.02;
    }

}