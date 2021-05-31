#include <stdexcept>
#include "signal_similarity_measures.hpp"
#include <cmath>
#include <cfloat>
#include <sstream>

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

        double resultMax = result.y.front();
        double diffSquaredSum = 0.0;
        for (int i = 1; i < result.x.size(); i++) {
            if (result.y[i] > resultMax) {
                resultMax = result.y[i];
            }
            diffSquaredSum += pow(result.y[i] - origin.y[i], 2.0);
        }

        return 10.0 * log10(resultMax / meanSquaredError(result, origin));
    }

      double maximumDifference(const SignalData& result, const SignalData& origin) {
          if (result.x.size() != origin.x.size()) {
              throw std::runtime_error("not same length");
          }

        double maxDiff = fabs(result.y.front() - origin.y.front());
        for (int i = 1; i < result.x.size(); i++) {
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

    std::string signalComparisonInfo(const SignalData& result, const SignalData& origin)
    {
          std::stringstream os;
          os << "Mean squared error: " << meanSquaredError(result, origin) << '\n';
          os << "Signal to noise ratio: " << signalToNoiseRatio(result, origin) << '\n';
          os << "Peak signal to noise ratio: " << peakSignalToNoiseRatio(result, origin) << '\n';
          os << "Maximum difference: " << maximumDifference(result, origin) << '\n';
          return os.str();
    }

    std::string signalComparisonInfoForQuantization(const SignalData& result, const SignalData& origin)
    {
        std::stringstream os;
        os << signalComparisonInfo(result, origin);
        os << "Effective number of bits: " << effectiveNumberOfBits(result, origin) << '\n';
        return os.str();
    }
}