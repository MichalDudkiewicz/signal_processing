#ifndef SIGNAL_PROCESSING_FILTER_HPP
#define SIGNAL_PROCESSING_FILTER_HPP

#include "signal.hpp"
#include "custom_signal.hpp"
#include "window.hpp"
#include "rectangular_window.hpp"

#include <memory>

namespace cps {
    class Filter {
    public:
        Filter(int M, double fo, std::shared_ptr<Window> window = std::make_shared<RectangularWindow>());

    public:
        virtual std::shared_ptr<CustomSignal> filter(const std::shared_ptr<Signal>& signalToFilter) = 0;

    protected:
        int mM;
        double mFo;
        std::shared_ptr<Window> mWindow;
    };
}

#endif //SIGNAL_PROCESSING_FILTER_HPP
