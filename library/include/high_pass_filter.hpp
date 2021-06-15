#ifndef SIGNAL_PROCESSING_HIGH_PASS_FILTER_HPP
#define SIGNAL_PROCESSING_HIGH_PASS_FILTER_HPP

#include "low_pass_filter.hpp"

namespace cps {
    class HighPassFilter : public LowPassFilter {
    public:
        HighPassFilter(int M, double fo, std::shared_ptr<Window> window);

    private:
        int s(int n) const override;

    };
}

#endif //SIGNAL_PROCESSING_HIGH_PASS_FILTER_HPP
