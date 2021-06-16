#ifndef SIGNAL_PROCESSING_LOW_PASS_FILTER_HPP
#define SIGNAL_PROCESSING_LOW_PASS_FILTER_HPP

#include "filter.hpp"

namespace cps {
    class LowPassFilter : public Filter {
    public:
        LowPassFilter(int M, double fo, std::shared_ptr<Window> window);

    public:
        std::shared_ptr<CustomSignal> filter(const std::shared_ptr<Signal> &signalToFilter) override;

    protected:
        virtual int s(int n) const;
    };
}

#endif //SIGNAL_PROCESSING_LOW_PASS_FILTER_HPP
