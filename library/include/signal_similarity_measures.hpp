#ifndef SIGNAL_PROCESSING_SIGNAL_SIMILARITY_MEASURES_HPP
#define SIGNAL_PROCESSING_SIGNAL_SIMILARITY_MEASURES_HPP

#include "signal_sampler.hpp"

namespace cps {
    double meanSquaredError(const SignalData& result, const SignalData& origin);

    double signalToNoiseRatio(const SignalData& result, const SignalData& origin);

    double peakSignalToNoiseRatio(const SignalData& result, const SignalData& origin);

    double maximumDifference(const SignalData& result, const SignalData& origin);

    double effectiveNumberOfBits(const SignalData& result, const SignalData& origin);

    std::string signalComparisonInfo(const SignalData& result, const SignalData& origin);

    std::string signalComparisonInfoForQuantization(const SignalData& result, const SignalData& origin);
}

#endif //SIGNAL_PROCESSING_SIGNAL_SIMILARITY_MEASURES_HPP
