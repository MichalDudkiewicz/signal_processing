#ifndef SIGNAL_PROCESSING_SIN_CARD_RECONSTRUCTED_SIGNAL_HPP
#define SIGNAL_PROCESSING_SIN_CARD_RECONSTRUCTED_SIGNAL_HPP

#include "signal_sampler.hpp"
#include "signal.hpp"

namespace cps {
    class SinCardReconstructedSignal : public Signal {
    public:
        SinCardReconstructedSignal(SignalData signalData, int numberOfNeigbourSamples);

    public:
        double value(double x) override;

    private:
        SignalData mSignalData;
        int mNumberOfNeigbourSamples;
    };
}

#endif //SIGNAL_PROCESSING_SIN_CARD_RECONSTRUCTED_SIGNAL_HPP
